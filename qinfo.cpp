#include "qinfo.h"
#include "ncorp.h"
#include "filum.h"
#include <QTimer>
#include <QProgressBar>
#include <QFileDialog>
#include <omp.h>
#include <QTranslator>

//=========================================================================================================
//заполнить данные по фенотипическим параметрам
//=========================================================================================================
void OECOSYS::init_gen()
{
	add_gen(QT_TR_NOOP("socialitas"),			SUI_PHILIA,			0,	1);
	add_gen(QT_TR_NOOP("sociophobia"),			SUI_PHOBIA,			0,	1);
	add_gen(QT_TR_NOOP("aggressio"),			OPP_PHILIA,			0,	1);
	add_gen(QT_TR_NOOP("fuga"),					OPP_PHOBIA,			0,	1);
	add_gen(QT_TR_NOOP("vis errandi soli"),		STOCH_MOT_INTENT,	0,	1);
	add_gen(QT_TR_NOOP("vis errandi publici"),	STOCH_MOT_BASIS,	0,	1);
	add_gen(QT_TR_NOOP("vicini optimi"),		MAX_VIC_VIS,		2,	128.0 );
	add_gen(QT_TR_NOOP("massa reproductiva"),	MIN_REPRODUCT_MASS,	0.6,4.0 );
	add_gen(QT_TR_NOOP("sphaera visionis"),		MAX_DIST_VIS,		30, 200 );
	add_gen(QT_TR_NOOP("sphaera unae praedae"),	MAX_DIST_ACT,		4,	20 );
	add_gen(QT_TR_NOOP("sphaera devorandi"),	MAX_DIST_DEVOR,		1,	3 );
	add_gen(QT_TR_NOOP("sphaera copulandi"),	MAX_DIST_FUCK,		2,	3 );
	add_gen(QT_TR_NOOP("paedophilia"),			PAEDOPHILIA,		0,	1 );
	add_gen(QT_TR_NOOP("necrophagia"),			NECROPHAGIA,		0,	1 );
	add_gen(QT_TR_NOOP("longaevitas"),			TEMPUS_VITAE,		0,	1 );
}


QINFO::QINFO(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);


	ui.tableWidget_cur->hide();
	for(int i=0;i<N_GENES;i++)
	{
		tab_init(
			OECOSYS::gen_info(i).nomen,
			OECOSYS::gen_info(i).praesum,
			OECOSYS::gen_info(i).praesum == 0,
			1000);
	}

	remod(NUL);

    connect(ui.pushButton_gen, SIGNAL(clicked()), this, SLOT(gen()));
 	connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(pau()));
	connect(ui.pushButton_add, SIGNAL(clicked()), this, SLOT(add_mod()));
	connect(ui.pushButton_destr, SIGNAL(clicked()), this, SLOT(del()));
	connect(ui.pushButton_import, SIGNAL(clicked()), this, SLOT(relege()));
	connect(ui.pushButton_export, SIGNAL(clicked()), this, SLOT(conserva()));
	connect(ui.horizontalSlider_spe_gen_part, SIGNAL(valueChanged(int)), this, SLOT(spe_gen_part(int)));
    connect(ui.pushButton_gengen, SIGNAL(clicked()), this, SLOT(gen_stoch_gen()));

	connect(ui.openGLWidget, SIGNAL(corp_sel()), this, SLOT(sel_index()));

	connect(ui.openGLWidget, SIGNAL(spec_add_quer(float,float)), this, SLOT(spec_add_quer_resp(float,float)));
	connect(this, SIGNAL(spec_add_info(float,float,GENE,int,float)), ui.openGLWidget, SLOT(spec_add_proc(float,float,GENE,int,float)));
	connect(ui.openGLWidget, SIGNAL(spec_add()), this, SLOT(prepar_info()));

	connect(ui.comboBox_vismod, SIGNAL(currentIndexChanged(int)), ui.openGLWidget, SLOT(mod_vismod(int)));
	connect(ui.comboBox_subst, SIGNAL(currentIndexChanged(int)), ui.openGLWidget, SLOT(substcol(int)));
	connect(ui.horizontalSlider_erase, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(attenua(int)));

	ui.tableWidget_species->setColumnWidth(1, 100);
	ui.tableWidget_cur->horizontalHeader()->hide();

	QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QINFO::mon_info);
    timer->start(500);

	//режим пустой сцены
	modus = NUL;

	//произвольный ген
	ui.lineEdit_selgen->setText(QString::number(stoch()));

	this->setWindowTitle("Vermarium");
}

//=========================================================================================================
//окончательный результат ручного добавления
//=========================================================================================================
void QINFO::prepar_info()
{
	ui.tableWidget_species->clearContents();
	ui.tableWidget_species->setRowCount (ui.openGLWidget->nc->species.size());	// количество строк под виды
	ui.lcdNumber_tact->display(0);												// обнулить число отсчитанных тактов
	ui.lcdNumber_fila->display(ui.openGLWidget->Fila()->n());					// показать число потоков

	//заполнение и раскраска таблицы видов
	for(int i=0; i<ui.openGLWidget->nc->species.size(); i++)
	{
		ui.tableWidget_species->setItem(i,0,new QTableWidgetItem);
		ui.tableWidget_species->setCellWidget(i,1,new QProgressBar);
		ui.tableWidget_species->setCellWidget(i,2,new QProgressBar);
		ui.tableWidget_species->item(i,0)->setBackgroundColor(ui.openGLWidget->genchroma(ui.openGLWidget->nc->species[i].g));
	}
	mon_info();
}

//=========================================================================================================
//изменить контролы согласно режиму
//=========================================================================================================
void QINFO::remod ( MODUS m)
{
	ui.pushButton_add		-> setText(tr("Manu adde"));// кнопка добавить в ручную
	ui.pushButton_import	-> setEnabled(false);		// кнопка открыть
	ui.pushButton_export	-> setEnabled(false);		// кнопка сохранить
	ui.pushButton_destr		-> setEnabled(false);		// кнопка уничтожить
	switch(m)
	{
	//экосистемы не создано
	case NUL:
		ui.pushButton_add		-> setEnabled(true);		// кнопка добавить в ручную
		ui.pushButton_start		-> setText("*");			// кнопка пуск/стоп
		ui.pushButton_start		-> setEnabled(false);		// кнопка пуск/стоп
		ui.pushButton_start		-> setChecked(false);		// кнопка пуск/стоп
		ui.pushButton_gen		-> setEnabled(true);		// кнопка породить/переродить
		ui.pushButton_gen		-> setText(tr("Genera"));	// кнопка породить/переродить
		ui.pushButton_import	-> setEnabled(true);		// кнопка открыть
		ui.pushButton_export	-> setEnabled(false);		// кнопка сохранить
		ui.spinBox_n			-> setEnabled(true);		// ввод числа существ
		ui.spinBox_nsp			-> setEnabled(true);		// ввод числа существ
		ui.comboBox				-> setEnabled(true);		// тип размещения
		ui.checkBox_incest		-> setEnabled(true);		// инцест
		ui.comboBox_mod_rep		-> setEnabled(true);		// тип репликации
		ui.checkBox_mortal		-> setEnabled(true);		// смертны
		ui.tableWidget_species	-> setRowCount(0);			// очистить таблицу видов 
		ui.tableWidget_cur		-> hide();					// скрыть таблицу текуще выделенного 
	break;

	//экосистема создана, но остановлена/не запущена
	case PND:
		ui.pushButton_destr		-> setEnabled(true);		// кнопка уничтожить
		ui.pushButton_add		-> setEnabled(false);		// кнопка добавить в ручную
		ui.pushButton_start		-> setEnabled(true);		// кнопка пуск/стоп
		ui.pushButton_start		-> setChecked(false);		// кнопка пуск/стоп
		ui.pushButton_start		-> setText(">");			// кнопка пуск/стоп
		ui.pushButton_gen		-> setEnabled(true);		// кнопка породить/переродить
		ui.pushButton_gen		-> setText(tr("Restaura"));	// кнопка породить/переродить
		ui.pushButton_import	-> setEnabled(false);		// кнопка открыть
		ui.pushButton_export	-> setEnabled(true);		// кнопка сохранить
		ui.spinBox_n			-> setEnabled(false);		// ввод числа существ
		ui.spinBox_nsp			-> setEnabled(false);		// ввод числа существ
		ui.comboBox				-> setEnabled(false);		// тип размещения
		ui.checkBox_incest		-> setEnabled(false);		// инцест
		ui.comboBox_mod_rep		-> setEnabled(false);		// тип репликации
		ui.checkBox_mortal		-> setEnabled(false);		// смертны

		//если переход с нуля, то есть создание экосистемы
		if(modus == NUL) prepar_info();
		break;

	//экосистема в процессе выполнения
	case ACT:
		ui.pushButton_add		-> setEnabled(false);		// кнопка добавить в ручную
		ui.pushButton_start		-> setEnabled(true);		// кнопка пуск/стоп
		ui.pushButton_start		-> setChecked(true);		// кнопка пуск/стоп
		ui.pushButton_start		-> setText("||");			// кнопка пуск/стоп
		ui.pushButton_gen		-> setEnabled(false);		// кнопка породить/переродить
		ui.pushButton_gen		-> setText(tr("Restaura"));	// кнопка породить/переродить
		ui.spinBox_n			-> setEnabled(false);		// ввод числа существ
		ui.spinBox_nsp			-> setEnabled(false);		// ввод числа существ
		ui.comboBox				-> setEnabled(false);		// тип размещения
		ui.checkBox_incest		-> setEnabled(false);		// инцест
		ui.comboBox_mod_rep		-> setEnabled(false);		// тип репликации
		ui.checkBox_mortal		-> setEnabled(false);		// смертны
		break;

	//режим ручного добавления
	case ADD:
		ui.pushButton_start		-> setEnabled(false);		// кнопка пуск/стоп
		ui.pushButton_add		-> setEnabled(true);				// кнопка добавить в ручную
		ui.pushButton_add		-> setText(tr("Fini addendum"));	// кнопка добавить в ручную
		ui.pushButton_start		-> setEnabled(false);		// кнопка пуск/стоп
		ui.pushButton_start		-> setText("*");			// кнопка пуск/стоп
		ui.pushButton_start		-> setChecked(false);		// кнопка пуск/стоп
		ui.pushButton_gen		-> setEnabled(false);		// кнопка породить/переродить
		ui.pushButton_gen		-> setText(tr("Genera"));	// кнопка породить/переродить
		ui.spinBox_n			-> setEnabled(true);		// ввод числа существ
		ui.spinBox_nsp			-> setEnabled(false);		// ввод числа видов
		ui.comboBox				-> setEnabled(false);		// тип размещения
		ui.checkBox_incest		-> setEnabled(true);		// инцест
		ui.comboBox_mod_rep		-> setEnabled(true);		// тип репликации
		ui.checkBox_mortal		-> setEnabled(true);		// смертны
		ui.tableWidget_cur		-> hide();					// скрыть таблицу текуще выделенного 
	break;
	}
	modus = m; 

}


QINFO::~QINFO()
{

}

void QINFO::pau()
{
	//остановка
	if(!ui.pushButton_start->isChecked())
	{
		remod(PND);
		ui.openGLWidget->pausa();
	}
	//запуск
	else
	{
		remod(ACT);
		ui.openGLWidget->continua();
	}
}

//=========================================================================================================
//режим ручного добавления
//=========================================================================================================
void QINFO::add_mod()		
{
	//стандарнтный режим
	if(!ui.pushButton_add->isChecked())
	{
		if(ui.openGLWidget->nc)
		{
			mon_info();
			remod(PND);
		}
		else
			remod(NUL);
		ui.openGLWidget->add_mod(false);
	}
	//добавление
	else
	{
		//начинать добавление можно только с чистого листа
		if(modus == NUL)
		{
			remod(ADD);
			ui.openGLWidget->add_mod(true);
		}
		else
			ui.pushButton_add->setChecked(false);
	}
}

//=========================================================================================================
//ответить на запрос о добавлении новой порции
//=========================================================================================================
void QINFO::spec_add_quer_resp(float x, float y)	
{
	//произвольный ген
	if(ui.lineEdit_selgen->text().isEmpty() || ui.lineEdit_selgen->text().toULongLong()==0)
		emit spec_add_info (x, y, stoch(), ui.spinBox_n->value(), ui.doubleSpinBox_insdim->value());

	//введенный/прошлый ген
	else
		emit spec_add_info (x, y, ui.lineEdit_selgen->text().toULongLong(), ui.spinBox_n->value(), ui.doubleSpinBox_insdim->value());
}


//=========================================================================================================
//команда породить экосистему
//=========================================================================================================
void QINFO::gen()
{
	if(modus == NUL)
		ui.openGLWidget->gen(	ui.spinBox_n->value(),
								ui.spinBox_nsp->value(),
								ui.comboBox->currentIndex(),
								ui.checkBox_incest->isChecked(),
								ui.comboBox_mod_rep->currentIndex());
	else
	{	pau();	ui.openGLWidget->regen();	}

	if(ui.checkBox_mortal->isChecked())		ui.openGLWidget->nc->longaevitas(ui.spinBox_vl->value());
	else									ui.openGLWidget->nc->longaevitas(0);

	//переформатировать
	remod(PND);
}

//=========================================================================================================
//команда убить экосистему
//=========================================================================================================
void QINFO::del()
{
	//если просчёт активен, сначала его завершить
	if(modus == ACT) pau();

	//убить
	ui.openGLWidget->nec();

	//переформатировать
	remod(NUL);
}

//=========================================================================================================
//динамически обновить вклад генов
//=========================================================================================================
void QINFO::spe_gen_part(int n)
{
	CORP::spe_gen_part = n;
}

void QINFO::gen_stoch_gen()
{
	//произвольный ген
	ui.lineEdit_selgen->setText(QString::number(stoch()));
}

//=========================================================================================================
//ежесекундно отображать статистику
//=========================================================================================================
void QINFO::mon_info()
{
	if(ui.openGLWidget->nc)
	{
		//предрасчитать статистику
		ui.openGLWidget->nc->calcul();

		for(int i=0; i<ui.openGLWidget->nc->species.size(); i++)
		{
			//вывести число
			ui.tableWidget_species->item(i,0)->setText( QString::number(ui.openGLWidget->nc->species[i].qnt) );

			//покрасить
			ui.tableWidget_species->item(i,0)->setBackgroundColor(ui.openGLWidget->genchroma(ui.openGLWidget->nc->species[i].g));

			//вывести соотношение
			QProgressBar* pb = (QProgressBar*)ui.tableWidget_species->cellWidget(i,1);
			pb->setMaximum(ui.openGLWidget->nc->populatio());
			pb->setValue(ui.openGLWidget->nc->species[i].qnt);

			double ratio = ui.openGLWidget->nc->species[i].m/ui.openGLWidget->nc->biomassa();
			pb = (QProgressBar*)ui.tableWidget_species->cellWidget(i,2);
			pb->setMaximum(1000);
			pb->setValue((int)(1000*ratio));
		}

		//динамически отображить
		ui.lcdNumber_n->display(ui.openGLWidget->nc->populatio());
		ui.lcdNumber_fps->display((int)ui.openGLWidget->fps*2);
		ui.lcdNumber_gps->display((int)(ui.openGLWidget->nc->gressus() - tacta)*2);
		ui.lcdNumber_tact->display((int)ui.openGLWidget->nc->gressus());
		ui.openGLWidget->fps = 0;
		tacta = (int)ui.openGLWidget->nc->gressus();
		ui.lcdNumber_temp->display((double)ui.openGLWidget->Fila()->tsec()*0.001);

		//отображать параметры выделенного, которые меняются со временем
		if(ui.openGLWidget->nc->selectum())
		{
			ui.tableWidget_cur->item(1,0)->setText(QString::number(ui.openGLWidget->nc->selectum()->m));
			ui.tableWidget_cur->item(2,0)->setText(QString::number(ui.openGLWidget->nc->selectum()->e));
			ui.tableWidget_cur->item(3,0)->setText(QString::number(ui.openGLWidget->nc->selectum()->v));
		}
		else ui.tableWidget_cur->item(0,0)->setText(tr("mortuus"));

		//ui.spinBox_nsp->setValue(ui.openGLWidget->nc->dt);
	}
}

//=========================================================================================================
//отобразить ген
//=========================================================================================================
void QINFO::gen_phaen (CORP* c)
{
	for(int i=0;i<N_GENES;i++)
	{
		tab_rec (i, c);
	}
}


//=========================================================================================================
//немедленно отобразить параметры выделеннного, которые не меняются со временем
//=========================================================================================================
void QINFO::sel_index()
{
	if(!ui.openGLWidget->nc->selectum())
		ui.tableWidget_cur->hide();
	else
	{
		ui.tableWidget_cur->show();

		//отобразить поколение
		ui.tableWidget_cur->item(0,0)->setText(QString::number(ui.openGLWidget->nc->selectum()->gener));

		//рамка по цвету вида
		QColor qc = ui.openGLWidget->genchroma(ui.openGLWidget->nc->selectum()->gen_spe);
		QString ss = QString("QTableWidget { border: 5px solid rgb(%1,%2,%3);}").arg(qc.red()).arg(qc.green()).arg(qc.blue());
		ui.tableWidget_cur->setStyleSheet(ss);

		//численное представление видового гена
		ui.lineEdit_selgen->setText(QString::number(ui.openGLWidget->nc->selectum()->gen_spe));

		//обобразить фенотип выделенного
		gen_phaen(ui.openGLWidget->nc->selectum());

		ui.tableWidget_species->selectRow(ui.openGLWidget->nc->sel_species());
	}
}

//=========================================================================================================
//создать поле таблицы соответствующее воплощению гена
//=========================================================================================================
void QINFO::tab_init (const char* nmn, float val, bool scal, float max)
{
	ui.tableWidget_cur->insertRow(ui.tableWidget_cur->rowCount());
	ui.tableWidget_cur->setVerticalHeaderItem (ui.tableWidget_cur->rowCount()-1, new QTableWidgetItem);
	ui.tableWidget_cur->verticalHeaderItem (ui.tableWidget_cur->rowCount()-1)->setText( QApplication::translate("OECOSYS",nmn) );
	if(scal)
	{
		QSlider *s = new QSlider;
		s->setOrientation(Qt::Horizontal);
		s->setMinimum(0);
		s->setTickInterval(max/10);
		s->setTickPosition(QSlider::TicksBelow);
		s->setMaximum(max);
		s->setValue(val);
		QPalette p = s->palette();
		s->setEnabled(false);
		p.setCurrentColorGroup(QPalette::Active);
		s->setPalette(p);
		ui.tableWidget_cur->setCellWidget (ui.tableWidget_cur->rowCount()-1, 0, s);
	}
	else
	{
		ui.tableWidget_cur->setItem (ui.tableWidget_cur->rowCount()-1, 0, new QTableWidgetItem);
		ui.tableWidget_cur->item (ui.tableWidget_cur->rowCount()-1, 0)->setText(QString::number(val));
	}
}
//=========================================================================================================
//записать поле таблицы соответствующее воплощению гена данного существа
//=========================================================================================================
void QINFO::tab_rec (int index, CORP* c, bool edit)
{
	if(ui.tableWidget_cur->cellWidget(4+index,0))
	{
		QSlider *s = (QSlider*)ui.tableWidget_cur->cellWidget(4+index,0);
		s->setEnabled(edit);
		s->setValue(c->phaeno(index)*1000.0);
	}
	else
	{
		ui.tableWidget_cur->item (4+index, 0)->setText(QString::number(c->phaeno(index)));
		ui.tableWidget_cur->item (4+index, 0)->setBackgroundColor(Qt::white);
	}
}

//=========================================================================================================
//прочитьать из файла
//=========================================================================================================
void QINFO::relege()
{
	QString fn = QFileDialog::getOpenFileName(this, QString(), QString(), tr("Oecosystema (*.huy)"));
	if(fn.length()>0)
	{

		QFile f(fn);
		f.open(QIODevice::ReadOnly);
		QByteArray ba = f.readAll();
		f.close();

		ui.openGLWidget->import(ba);

		remod(PND);

		//вывести сохраненное из файла время жизни
		ui.spinBox_vl->setValue(ui.openGLWidget->nc->longaevitas());
		ui.checkBox_mortal->setChecked(ui.openGLWidget->nc->longaevitas()>0);
	}
}

//=========================================================================================================
//сохранить
//=========================================================================================================
void QINFO::conserva()
{
	QString fn = QFileDialog::getSaveFileName(this, QString(), QString(), tr("Oecosystema (*.huy)"));
	if(fn.length()>0)
	{
		QFile f(fn);
		f.open(QIODevice::WriteOnly);
		QByteArray dst;
		ui.openGLWidget->record(dst);
		f.write(dst.data(),dst.size());
		f.close();
	}
}

