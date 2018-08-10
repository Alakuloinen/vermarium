#include "glw.h"
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QPaintEvent>
#include <QtConcurrent>
#include "filum.h"
#include "ncorp.h"
#include <algorithm>
#include <omp.h>
#include <functional>




GLW::GLW(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
    setAutoFillBackground(false);

	//таймер для синхронной отрисовки
    timer = new QTimer(this);
   connect(timer, &QTimer::timeout, this, &GLW::animate);
	timer->start(10); 

	//цвета фона
	substrati[0] = QColor(0,0,0);
	substrati[1] = QColor(255,255,255);
	substrati[2] = QColor(127,127,127);
	subst = QColor(0,0,0,5);

	nc = 0;
	nc_copia = 0;
	fila = 0;
	fps = 0;
	vismod = 0;
	add = false;

	//заполнить названия генов для внешнего пользования и коэффициенты для фенотипа
	OECOSYS::init_gen();

}

GLW::~GLW()
{
	if(fila) delete fila;
	timer->stop(); 
	if(nc){ delete nc; }
}

//=========================================================================================================
// сгенерировать цвет для гена
//=========================================================================================================
QColor GLW::genchroma (GENE gene)
{
	if(gene == DEGENE) return Qt::white;
	std::hash<GENE> h;
	int v = h(gene); 
	int r = v&255;
	int g = (v>>8)&255;
	int b = (v>>16)&255;
	QColor c(v);
	if(r+g+b<255) c = QColor(255-r,255-g,255-b);
	return c;
}



//=========================================================================================================
// градиент цвета по значению - стырено
//=========================================================================================================
QColor GLW::gradient (float val, float min, float max)
{
	const int NUM_COLORS = 4;
	static float color[NUM_COLORS][3] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };
    // A static array of 4 colors:  (blue,   green,  yellow,  red) using {r,g,b} for each.
 
	float v = (val-min)/(max-min);
	int idx1;        // |-- Our desired color will be between these two indexes in "color".
	int idx2;        // |
	float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.
 
	if(v <= 0)      {  idx1 = idx2 = 0;            }    // accounts for an input <=0
	else if(v >= 1)  {  idx1 = idx2 = NUM_COLORS-1; }    // accounts for an input >=0
	else
	{
		v = v * (NUM_COLORS-1);				// Will multiply value by 3.
		idx1  = floor(v);					// Our desired color will be after this index.
		idx2  = idx1+1;						// ... and before this index (inclusive).
		fractBetween = v - float(idx1);		// Distance between the two indexes (0-1).
	}

	QColor ret;
	ret.setRedF((color[idx2][0] - color[idx1][0])*fractBetween + color[idx1][0]);
	ret.setGreenF((color[idx2][1] - color[idx1][1])*fractBetween + color[idx1][1]);
	ret.setBlueF((color[idx2][2] - color[idx1][2])*fractBetween + color[idx1][2]);
  
	return ret;
}




//=========================================================================================================
// переключение в режим ручного добавления и обратно
//=========================================================================================================
void GLW::add_mod(bool val)
{ 
	//переход в режим ручного добавления - породить пустую
	if(val)
	{
		if(!nc)
			gen(0,0,0,true, 0);
	}

	//переход в обычный режим
	else
	{
		//если за время режима создано что-то
		if(nc->n()>0)
		{
			//породить резервную копию текущей экосистемы
			if(nc_copia) delete nc_copia;
			nc_copia = new OECOSYS(*nc);
		}

		//иначе выпилить пустую
		else nec();
	}
	add = val;
}

//=========================================================================================================
// породить экосистему
//=========================================================================================================
void GLW::gen(int q, int nsp, int pattern, bool incest, int mod_rep)
{
	//способ передачи генов
	CORP::modusReplicandi((CORP::MODUS_REPLICANDI)mod_rep);

	//породить контейнер экосистемы
	if(nc){ delete nc; }
	nc = new OECOSYS(-400, -400, 400, 400);
	nc->incest(incest);
	if(q>0)
	{
		nc->gen(q, nsp, pattern);

		//породить резервную копию текущей экосистемы
		if(nc_copia) delete nc_copia;
		nc_copia = new OECOSYS(*nc);
	}

	//породить менеджер потоков и сразу выдеклить/запустить все потоки
	if(!fila)
	{	fila = new FILA(nc, std::max(QThread::idealThreadCount()-1,1), 0);
		fila->lancea();
		if(!fila->n()) { timer->stop();	timer->start(0); }
	}
		else fila->realloca(nc);


	//прорисовать начальную позицию экосистемы
	update();
}

//=========================================================================================================
// переродить экосистему из копии
//=========================================================================================================
void GLW::regen()
{
	//затормозить, если выполняется
	if(nc) pausa();

	//восстановить контейнер экосистемы
	if(!nc_copia) return;
	nc = new OECOSYS(*nc_copia);
	fila->realloca(nc); 

	//прорисовать начальную позицию экосистемы
	update();
}

//=========================================================================================================
// импортировать
//=========================================================================================================
void GLW::import(QByteArray arch)
{
	//затормозить, если выполняется
	if(nc) pausa();

	//восстановить контейнер экосистемы
	nc = new OECOSYS(arch.toStdString());

	//породить резервную копию текущей экосистемы
	if(nc_copia) delete nc_copia;
	nc_copia = new OECOSYS(*nc);

	//породить менеджер потоков и сразу выдеклить/запустить все потоки
	if(!fila)
	{	fila = new FILA(nc, std::max(QThread::idealThreadCount()-1,1), 0);
		fila->lancea();
		if(!fila->n()) { timer->stop();	timer->start(0); }
	}
		else fila->realloca(nc);

	//прорисовать начальную позицию экосистемы
	update();
}

//=========================================================================================================
//записать в файл
//=========================================================================================================
void GLW::record(QByteArray& arch)
{
	std::string dst;
	nc->arch(dst);
	arch = QByteArray::fromStdString(dst);
}

//=========================================================================================================
// уничтожить экосистему (но есть резервная копия)
//=========================================================================================================
void GLW::nec()
{ 
	//затормозить, если выполняется
	pausa();

	//удалить
	if(nc)	{ 	delete nc;	nc = 0;	} 

	//прорисовать черноту
	update();
}

//=========================================================================================================
//продолжить
//=========================================================================================================
void GLW::continua()
{ 
	if(fila->n())	fila->resume();
	else
	{
		nc->resume();
		nc->presync();
	}
}

//=========================================================================================================
//остановить
//=========================================================================================================
void GLW::pausa()
{ 
	if(fila->n())	fila->pause();
	else			nc->cessa();
}

//=========================================================================================================
//вызов по таймеру
//=========================================================================================================
void GLW::animate()
{
	//собственно рисовать
    update();

	if(!nc) return;
	if(!fila->n() && nc->in_actione())
	{
		nc->iteratio(fila->tnsec());
	}

	fps++;
}

//=========================================================================================================
//добавить комок нужного вида в ответ на посылку инфы
//=========================================================================================================
void GLW::spec_add_proc(float x, float y, GENE g, int n, float insdim)
{
	nc->add(g, n, x, y, insdim);
	fila->realloca(nc);
	update();
	emit spec_add();
}


//=========================================================================================================
//событие клаца мышкой
//=========================================================================================================
void GLW::mousePressEvent(QMouseEvent *event)
{
	//режим ручного добавления
	if(add)
	{
		//понячть, где добавлять
		float x = event->x()-this->rect().center().x();
		float y = event->y()-this->rect().center().y();

		//запросить инфу, как создавать
		emit spec_add_quer(x,y);
	}
	//режим выделения
	else
	{
		if(!nc) return;

		//правая кнопка - развыделить
		nc->deselecta();
		update();
		if(event->button() == Qt::RightButton)
		{
			emit corp_sel();
			return;
		}

		//поиск ближайшего к месту клика
		nc->selecta(event->x()-this->rect().center().x(), event->y()-this->rect().center().y());
		emit corp_sel();
	}
	update();
}

//=========================================================================================================
//событие перерисовки
//=========================================================================================================
void GLW::paintEvent(QPaintEvent *event)
{
	QPainter painter;
    painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect rr (event->rect());

	//при пустом
	if(!nc)
	{
		painter.fillRect(event->rect(),subst);
		painter.end();
		return;
	}

	//стереть старое
	painter.fillRect(rr,subst);
	painter.translate(event->rect().center());


	//отобразить маркером специальным выделенное
	if(nc->selectum())
	{
		painter.setPen(Qt::black);
		painter.setBrush(subst);
		painter.drawRect (nc->selectum()->x-6,nc->selectum()->y-6,12,12);
		painter.setPen(Qt::white);
		painter.drawRect (nc->selectum()->x-5,nc->selectum()->y-5,10,10);
	}

	for(auto i = nc->corp.begin(); i != nc->corp.end(); i++ )
	{

		if(i->est)
		{

			painter.setBrush	(Qt::black);
			switch(vismod)
			{ 
			case 0:
							painter.setPen		(genchroma (i->gen_spe) );
				if(i->e>0)	painter.setBrush	(painter.pen().color());
				break;

			case 1:
							painter.setPen		(gradient(i->e/i->m, 0,1));
				if(i->e>0)	painter.setBrush	(painter.pen().color());
				break;

			case 2:
							painter.setPen		(gradient(i->v, 0, nc->longaevitas()));
				if(i->e>0)	painter.setBrush	(painter.pen().color());
				break;

			case 3:
							painter.setPen		(gradient(i->gener, 0, nc->max_gener()));
				if(i->e>0)	painter.setBrush	(painter.pen().color());
				break;
			}

			float r = 0.5*(1+sqrt(i->m));
			painter.drawEllipse (QPointF(i->x,i->y),r,r);
		}
	}
	
	painter.end();
}