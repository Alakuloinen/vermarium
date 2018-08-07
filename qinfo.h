#ifndef QINFO_H
#define QINFO_H

//#include <QWidget>
#include "ui_qinfo.h"

struct CORP;

class QINFO : public QWidget
{
	Q_OBJECT

signals:
	void spec_add_info (float x, float y, GENE g, int n, float insdim);	//команда к ручному добавлению + данные по настройкам

public slots:

	void gen();
	void del();
	void mon_info();	//по таймеру обновить информацию
	void add_mod();		//включить по кнопке режим ручного добавления
	void spec_add_quer_resp(float x, float y);	//ответить на запрос о добавлении новой порции
	void gen_stoch_gen();

	void pau();

	void prepar_info();

	//открыть и сохранить
	void relege();
	void conserva();

	//перенастроить вклад генов по ползунку
	void spe_gen_part(int);

	//отобразить параметры выделеннного
	void sel_index();

	void tab_init (const char* nmn, float val, bool scal = false, float max = 0);
	void tab_rec (int index, CORP* c, bool edit = false);

	void gen_phaen (CORP* c);

public:

	// состояния системы
	enum MODUS { NUL, PND, ACT, ADD };
	MODUS modus;
	void remod ( MODUS m);

	QINFO(QWidget *parent = 0);
	~QINFO();

private:
	qulonglong tacta;

	Ui::QINFO ui;
};

#endif // QINFO_H
