#ifndef GLW_H
#define GLW_H

//#include <qopenglwidget.h>
#include "ncorp.h"
#include "ui_glw.h"
#include <list>
#include <qthread.h>
#include <QVector>
#include <QWaitCondition>


class FILA;
class OECOSYS;

//################################################################################
class GLW : public QOpenGLWidget
{
	friend class QINFO;
	Q_OBJECT

	OECOSYS *nc;
	OECOSYS* nc_copia;

	QTimer *timer;
	FILA* fila;
	FILA* fila_copia;

	QColor subst;
	QColor substrati[3];

	int vismod;

	bool add;

signals:
	void corp_sel();							// просигнализировать, что изменилось выделение
	void spec_add_quer(float x, float y);		// запросить инфу, как добавлять 
	void spec_add();							// просигнализировать, что порция успешно добавлена

public slots:
	void gen(int n, int nsp, int pattern, bool incest, int mod_rep);
	void spec_add_proc(float x, float y, GENE g, int n, float insdim);
	void regen();
	void nec();
	void import(QByteArray);
	void record(QByteArray&);

	void continua();
	void pausa();

	void attenua(int val) {		subst.setAlpha(255 - val); }
	void substcol(int val) {	subst = QColor(substrati[val].red(), substrati[val].green(), substrati[val].blue(), subst.alpha()); }

	void mod_vismod(int i) { vismod = i; }
	void add_mod(bool val);

    void animate();

	FILA* Fila() const { return fila; }

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

public:
	GLW(QWidget *parent = 0);
	~GLW();

	QColor genchroma (GENE gene);

	QColor gradient (float val, float min, float max);


private:
	Ui::GLW ui;
	unsigned long fps;
};

#endif // GLW_H
