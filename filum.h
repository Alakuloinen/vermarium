#pragma once
#include <list>
#include "ncorp.h"
#include <qthread.h>
#include <QVector>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QTimer>

//################################################################################
class FILUM : public QThread
{
	Q_OBJECT

	friend class FILA;
	int n1;
	int n2;
	FILA* p;

signals:
	void synchro();

protected:
	void run();
};

//################################################################################
class FILA : public QObject
{
	Q_OBJECT
	friend class FILUM;

	//синхронизация с паузой-рестартом
	QMutex syncpause;
	QWaitCondition wc;

	//синхронизация по барьеру самого длительного шага
	QMutex syncproc;
	int nprocs;
	QWaitCondition ws;

	//синхронизация по таймеру
	QMutex syncti;
	QWaitCondition wt;

	//потоки
	QVector<FILUM*> fila;

	//контейнер экосистемы
	OECOSYS* nc;

	//для точного расчёта времени между шагами
	QElapsedTimer et;
	quint64 nsec_init;

	// сихронный режим по таймеру
	int tsync;			
	QTimer timer;

public:

	bool	active()	const { return nc->in_actione(); }
	int		n()			const { return fila.size(); }
	float	tsec()		const { return (nc->in_actione() ? (nsec_init + et.nsecsElapsed()) : nsec_init)*0.001*0.001; }
	float	tnsec()		const { return et.nsecsElapsed(); }

signals:
	void gressus();

public slots:

	//перераспределить нагрузки потоков для нового количества существ
	void realloca(OECOSYS*_nc);

	//начало
	void lancea();

	//возобновить
    void resume();
 
	//приостановить
    void pause();
 
	//синхронизировать итоги лоскутов
	void synchro()	{ emit gressus();wt.wakeAll();	}

public:
	FILA(OECOSYS*_nc, int nfila, int tisync);
	~FILA();

};

