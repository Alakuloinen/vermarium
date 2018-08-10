/********************************************************************************
** Form generated from reading UI file 'qinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QINFO_H
#define UI_QINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glw.h"

QT_BEGIN_NAMESPACE

class Ui_QINFO
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    GLW *openGLWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QDoubleSpinBox *doubleSpinBox_insdim;
    QCheckBox *checkBox_mortal;
    QLabel *label_9;
    QLabel *label_7;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_mod_rep;
    QCheckBox *checkBox_incest;
    QSpinBox *spinBox_vl;
    QSpinBox *spinBox_n;
    QSpinBox *spinBox_nsp;
    QLabel *label_4;
    QSlider *horizontalSlider_spe_gen_part;
    QLabel *label_3;
    QPushButton *pushButton_gengen;
    QLineEdit *lineEdit_selgen;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *doubleSpinBox_mutpro;
    QDoubleSpinBox *doubleSpinBox_mutprospe;
    QLabel *label_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_gen;
    QPushButton *pushButton_add;
    QPushButton *pushButton_destr;
    QPushButton *pushButton_start;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_import;
    QPushButton *pushButton_export;
    QTableWidget *tableWidget_species;
    QTableWidget *tableWidget_cur;
    QGridLayout *gridLayout_2;
    QLabel *label_fps;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcdNumber_gps;
    QLCDNumber *lcdNumber_fps;
    QLCDNumber *lcdNumber_fila;
    QLabel *label_8;
    QLabel *label_11;
    QSlider *horizontalSlider_erase;
    QLabel *label_6;
    QLabel *label_10;
    QLabel *label_12;
    QLCDNumber *lcdNumber_temp;
    QLCDNumber *lcdNumber_tact;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *comboBox_subst;
    QComboBox *comboBox_vismod;
    QLCDNumber *lcdNumber_n;
    QLabel *label_5;

    void setupUi(QWidget *QINFO)
    {
        if (QINFO->objectName().isEmpty())
            QINFO->setObjectName(QStringLiteral("QINFO"));
        QINFO->resize(1164, 926);
        verticalLayout_3 = new QVBoxLayout(QINFO);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, -1, -1);
        openGLWidget = new GLW(QINFO);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(810, 810));

        horizontalLayout->addWidget(openGLWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(-1, 3, -1, -1);
        doubleSpinBox_insdim = new QDoubleSpinBox(QINFO);
        doubleSpinBox_insdim->setObjectName(QStringLiteral("doubleSpinBox_insdim"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox_insdim->sizePolicy().hasHeightForWidth());
        doubleSpinBox_insdim->setSizePolicy(sizePolicy1);
        doubleSpinBox_insdim->setMinimumSize(QSize(46, 0));
        doubleSpinBox_insdim->setMaximum(1);
        doubleSpinBox_insdim->setSingleStep(0.01);
        doubleSpinBox_insdim->setValue(0.1);

        gridLayout->addWidget(doubleSpinBox_insdim, 6, 1, 1, 1);

        checkBox_mortal = new QCheckBox(QINFO);
        checkBox_mortal->setObjectName(QStringLiteral("checkBox_mortal"));
        checkBox_mortal->setChecked(true);

        gridLayout->addWidget(checkBox_mortal, 4, 0, 1, 1);

        label_9 = new QLabel(QINFO);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        label_7 = new QLabel(QINFO);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        comboBox = new QComboBox(QINFO);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(1, 0));

        gridLayout->addWidget(comboBox, 3, 1, 1, 1);

        label = new QLabel(QINFO);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox_mod_rep = new QComboBox(QINFO);
        comboBox_mod_rep->setObjectName(QStringLiteral("comboBox_mod_rep"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_mod_rep->sizePolicy().hasHeightForWidth());
        comboBox_mod_rep->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(comboBox_mod_rep, 5, 1, 1, 1);

        checkBox_incest = new QCheckBox(QINFO);
        checkBox_incest->setObjectName(QStringLiteral("checkBox_incest"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(checkBox_incest->sizePolicy().hasHeightForWidth());
        checkBox_incest->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(checkBox_incest, 5, 0, 1, 1);

        spinBox_vl = new QSpinBox(QINFO);
        spinBox_vl->setObjectName(QStringLiteral("spinBox_vl"));
        spinBox_vl->setMaximum(100000000);
        spinBox_vl->setSingleStep(10);
        spinBox_vl->setValue(100);

        gridLayout->addWidget(spinBox_vl, 4, 1, 1, 1);

        spinBox_n = new QSpinBox(QINFO);
        spinBox_n->setObjectName(QStringLiteral("spinBox_n"));
        spinBox_n->setMinimum(1);
        spinBox_n->setMaximum(10000);
        spinBox_n->setValue(150);

        gridLayout->addWidget(spinBox_n, 1, 1, 1, 1);

        spinBox_nsp = new QSpinBox(QINFO);
        spinBox_nsp->setObjectName(QStringLiteral("spinBox_nsp"));
        spinBox_nsp->setMinimum(1);
        spinBox_nsp->setMaximum(16);
        spinBox_nsp->setValue(4);

        gridLayout->addWidget(spinBox_nsp, 0, 1, 1, 1);

        label_4 = new QLabel(QINFO);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        horizontalSlider_spe_gen_part = new QSlider(QINFO);
        horizontalSlider_spe_gen_part->setObjectName(QStringLiteral("horizontalSlider_spe_gen_part"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(horizontalSlider_spe_gen_part->sizePolicy().hasHeightForWidth());
        horizontalSlider_spe_gen_part->setSizePolicy(sizePolicy5);
        horizontalSlider_spe_gen_part->setMinimumSize(QSize(10, 10));
        horizontalSlider_spe_gen_part->setBaseSize(QSize(0, 10));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 170, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 213, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 191, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 85, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 113, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(127, 212, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        horizontalSlider_spe_gen_part->setPalette(palette);
        horizontalSlider_spe_gen_part->setMinimum(1);
        horizontalSlider_spe_gen_part->setMaximum(16);
        horizontalSlider_spe_gen_part->setPageStep(1);
        horizontalSlider_spe_gen_part->setValue(16);
        horizontalSlider_spe_gen_part->setOrientation(Qt::Horizontal);
        horizontalSlider_spe_gen_part->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_spe_gen_part->setTickInterval(1);

        gridLayout->addWidget(horizontalSlider_spe_gen_part, 7, 1, 1, 1);

        label_3 = new QLabel(QINFO);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        pushButton_gengen = new QPushButton(QINFO);
        pushButton_gengen->setObjectName(QStringLiteral("pushButton_gengen"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_gengen->sizePolicy().hasHeightForWidth());
        pushButton_gengen->setSizePolicy(sizePolicy6);
        pushButton_gengen->setMinimumSize(QSize(0, 10));
        pushButton_gengen->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(pushButton_gengen, 9, 0, 1, 1);

        lineEdit_selgen = new QLineEdit(QINFO);
        lineEdit_selgen->setObjectName(QStringLiteral("lineEdit_selgen"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(lineEdit_selgen->sizePolicy().hasHeightForWidth());
        lineEdit_selgen->setSizePolicy(sizePolicy7);
        lineEdit_selgen->setMinimumSize(QSize(0, 10));
        lineEdit_selgen->setMaximumSize(QSize(16777215, 20));
        lineEdit_selgen->setInputMethodHints(Qt::ImhDigitsOnly);
        lineEdit_selgen->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_selgen, 9, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        doubleSpinBox_mutpro = new QDoubleSpinBox(QINFO);
        doubleSpinBox_mutpro->setObjectName(QStringLiteral("doubleSpinBox_mutpro"));
        doubleSpinBox_mutpro->setMaximum(1);
        doubleSpinBox_mutpro->setSingleStep(0.01);
        doubleSpinBox_mutpro->setValue(0.02);

        horizontalLayout_5->addWidget(doubleSpinBox_mutpro);

        doubleSpinBox_mutprospe = new QDoubleSpinBox(QINFO);
        doubleSpinBox_mutprospe->setObjectName(QStringLiteral("doubleSpinBox_mutprospe"));
        doubleSpinBox_mutprospe->setMaximum(1);
        doubleSpinBox_mutprospe->setSingleStep(0.01);

        horizontalLayout_5->addWidget(doubleSpinBox_mutprospe);


        gridLayout->addLayout(horizontalLayout_5, 8, 1, 1, 1);

        label_2 = new QLabel(QINFO);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        line = new QFrame(QINFO);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        pushButton_gen = new QPushButton(QINFO);
        pushButton_gen->setObjectName(QStringLiteral("pushButton_gen"));

        horizontalLayout_3->addWidget(pushButton_gen);

        pushButton_add = new QPushButton(QINFO);
        pushButton_add->setObjectName(QStringLiteral("pushButton_add"));
        pushButton_add->setCheckable(true);

        horizontalLayout_3->addWidget(pushButton_add);

        pushButton_destr = new QPushButton(QINFO);
        pushButton_destr->setObjectName(QStringLiteral("pushButton_destr"));

        horizontalLayout_3->addWidget(pushButton_destr);

        pushButton_start = new QPushButton(QINFO);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy8);
        pushButton_start->setMinimumSize(QSize(21, 0));
        pushButton_start->setMaximumSize(QSize(40, 16777215));
        pushButton_start->setSizeIncrement(QSize(0, 0));
        pushButton_start->setBaseSize(QSize(20, 0));
        QPalette palette1;
        QBrush brush9(QColor(255, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        pushButton_start->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        pushButton_start->setFont(font);
        pushButton_start->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0)"));
        pushButton_start->setCheckable(true);
        pushButton_start->setChecked(false);

        horizontalLayout_3->addWidget(pushButton_start);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        pushButton_import = new QPushButton(QINFO);
        pushButton_import->setObjectName(QStringLiteral("pushButton_import"));

        horizontalLayout_4->addWidget(pushButton_import);

        pushButton_export = new QPushButton(QINFO);
        pushButton_export->setObjectName(QStringLiteral("pushButton_export"));

        horizontalLayout_4->addWidget(pushButton_export);


        verticalLayout->addLayout(horizontalLayout_4);

        tableWidget_species = new QTableWidget(QINFO);
        if (tableWidget_species->columnCount() < 3)
            tableWidget_species->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_species->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_species->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_species->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_species->setObjectName(QStringLiteral("tableWidget_species"));
        tableWidget_species->setEnabled(true);
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(tableWidget_species->sizePolicy().hasHeightForWidth());
        tableWidget_species->setSizePolicy(sizePolicy9);
        tableWidget_species->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_species->setCornerButtonEnabled(false);
        tableWidget_species->horizontalHeader()->setDefaultSectionSize(60);
        tableWidget_species->horizontalHeader()->setMinimumSectionSize(60);
        tableWidget_species->horizontalHeader()->setStretchLastSection(true);
        tableWidget_species->verticalHeader()->setDefaultSectionSize(25);
        tableWidget_species->verticalHeader()->setMinimumSectionSize(25);

        verticalLayout->addWidget(tableWidget_species);

        tableWidget_cur = new QTableWidget(QINFO);
        if (tableWidget_cur->columnCount() < 1)
            tableWidget_cur->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_cur->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        if (tableWidget_cur->rowCount() < 4)
            tableWidget_cur->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_cur->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_cur->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_cur->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_cur->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_cur->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_cur->setItem(1, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_cur->setItem(2, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_cur->setItem(3, 0, __qtablewidgetitem11);
        tableWidget_cur->setObjectName(QStringLiteral("tableWidget_cur"));
        tableWidget_cur->setSizeIncrement(QSize(0, 0));
        QFont font1;
        font1.setPointSize(8);
        tableWidget_cur->setFont(font1);
        tableWidget_cur->setFrameShape(QFrame::Box);
        tableWidget_cur->setFrameShadow(QFrame::Plain);
        tableWidget_cur->setLineWidth(6);
        tableWidget_cur->setMidLineWidth(0);
        tableWidget_cur->setCornerButtonEnabled(false);
        tableWidget_cur->horizontalHeader()->setMinimumSectionSize(46);
        tableWidget_cur->horizontalHeader()->setStretchLastSection(true);
        tableWidget_cur->verticalHeader()->setDefaultSectionSize(21);
        tableWidget_cur->verticalHeader()->setMinimumSectionSize(21);

        verticalLayout->addWidget(tableWidget_cur);

        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 3);

        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        label_fps = new QLabel(QINFO);
        label_fps->setObjectName(QStringLiteral("label_fps"));
        sizePolicy2.setHeightForWidth(label_fps->sizePolicy().hasHeightForWidth());
        label_fps->setSizePolicy(sizePolicy2);
        label_fps->setMinimumSize(QSize(0, 0));
        label_fps->setMaximumSize(QSize(16777215, 16777215));
        label_fps->setFrameShape(QFrame::NoFrame);
        label_fps->setFrameShadow(QFrame::Sunken);
        label_fps->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_fps->setWordWrap(false);

        gridLayout_2->addWidget(label_fps, 0, 8, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lcdNumber_gps = new QLCDNumber(QINFO);
        lcdNumber_gps->setObjectName(QStringLiteral("lcdNumber_gps"));
        sizePolicy3.setHeightForWidth(lcdNumber_gps->sizePolicy().hasHeightForWidth());
        lcdNumber_gps->setSizePolicy(sizePolicy3);
        lcdNumber_gps->setFrameShadow(QFrame::Sunken);
        lcdNumber_gps->setMidLineWidth(1);
        lcdNumber_gps->setDigitCount(4);
        lcdNumber_gps->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_2->addWidget(lcdNumber_gps);

        lcdNumber_fps = new QLCDNumber(QINFO);
        lcdNumber_fps->setObjectName(QStringLiteral("lcdNumber_fps"));
        sizePolicy3.setHeightForWidth(lcdNumber_fps->sizePolicy().hasHeightForWidth());
        lcdNumber_fps->setSizePolicy(sizePolicy3);
        lcdNumber_fps->setMaximumSize(QSize(16777215, 16777215));
        lcdNumber_fps->setFrameShadow(QFrame::Sunken);
        lcdNumber_fps->setLineWidth(1);
        lcdNumber_fps->setMidLineWidth(1);
        lcdNumber_fps->setSmallDecimalPoint(false);
        lcdNumber_fps->setDigitCount(4);
        lcdNumber_fps->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_fps->setProperty("intValue", QVariant(999));

        horizontalLayout_2->addWidget(lcdNumber_fps);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 8, 1, 1);

        lcdNumber_fila = new QLCDNumber(QINFO);
        lcdNumber_fila->setObjectName(QStringLiteral("lcdNumber_fila"));
        sizePolicy6.setHeightForWidth(lcdNumber_fila->sizePolicy().hasHeightForWidth());
        lcdNumber_fila->setSizePolicy(sizePolicy6);
        lcdNumber_fila->setMaximumSize(QSize(40, 16777215));
        lcdNumber_fila->setDigitCount(2);
        lcdNumber_fila->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdNumber_fila, 1, 5, 1, 1);

        label_8 = new QLabel(QINFO);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy4.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy4);
        label_8->setMaximumSize(QSize(16777215, 16777215));
        label_8->setWordWrap(false);

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        label_11 = new QLabel(QINFO);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);
        label_11->setMinimumSize(QSize(0, 0));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11->setWordWrap(true);

        gridLayout_2->addWidget(label_11, 0, 4, 1, 1);

        horizontalSlider_erase = new QSlider(QINFO);
        horizontalSlider_erase->setObjectName(QStringLiteral("horizontalSlider_erase"));
        sizePolicy4.setHeightForWidth(horizontalSlider_erase->sizePolicy().hasHeightForWidth());
        horizontalSlider_erase->setSizePolicy(sizePolicy4);
        horizontalSlider_erase->setMaximum(255);
        horizontalSlider_erase->setValue(250);
        horizontalSlider_erase->setOrientation(Qt::Horizontal);
        horizontalSlider_erase->setTickPosition(QSlider::TicksBelow);

        gridLayout_2->addWidget(horizontalSlider_erase, 1, 2, 1, 1);

        label_6 = new QLabel(QINFO);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy4.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy4);
        label_6->setMaximumSize(QSize(16777215, 16777215));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setWordWrap(true);

        gridLayout_2->addWidget(label_6, 0, 6, 1, 1);

        label_10 = new QLabel(QINFO);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);
        label_10->setMaximumSize(QSize(16777215, 16777215));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_10->setWordWrap(true);

        gridLayout_2->addWidget(label_10, 0, 5, 1, 1);

        label_12 = new QLabel(QINFO);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        lcdNumber_temp = new QLCDNumber(QINFO);
        lcdNumber_temp->setObjectName(QStringLiteral("lcdNumber_temp"));
        sizePolicy3.setHeightForWidth(lcdNumber_temp->sizePolicy().hasHeightForWidth());
        lcdNumber_temp->setSizePolicy(sizePolicy3);
        lcdNumber_temp->setMinimumSize(QSize(0, 0));
        lcdNumber_temp->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdNumber_temp, 1, 4, 1, 1);

        lcdNumber_tact = new QLCDNumber(QINFO);
        lcdNumber_tact->setObjectName(QStringLiteral("lcdNumber_tact"));
        sizePolicy3.setHeightForWidth(lcdNumber_tact->sizePolicy().hasHeightForWidth());
        lcdNumber_tact->setSizePolicy(sizePolicy3);
        lcdNumber_tact->setMinimumSize(QSize(0, 0));
        lcdNumber_tact->setMaximumSize(QSize(16777215, 16777215));
        lcdNumber_tact->setSmallDecimalPoint(false);
        lcdNumber_tact->setDigitCount(7);
        lcdNumber_tact->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_tact->setProperty("intValue", QVariant(0));

        gridLayout_2->addWidget(lcdNumber_tact, 1, 6, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        comboBox_subst = new QComboBox(QINFO);
        comboBox_subst->setObjectName(QStringLiteral("comboBox_subst"));

        horizontalLayout_6->addWidget(comboBox_subst);

        comboBox_vismod = new QComboBox(QINFO);
        comboBox_vismod->setObjectName(QStringLiteral("comboBox_vismod"));

        horizontalLayout_6->addWidget(comboBox_vismod);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        lcdNumber_n = new QLCDNumber(QINFO);
        lcdNumber_n->setObjectName(QStringLiteral("lcdNumber_n"));
        lcdNumber_n->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_2->addWidget(lcdNumber_n, 1, 3, 1, 1);

        label_5 = new QLabel(QINFO);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        retranslateUi(QINFO);

        comboBox->setCurrentIndex(1);
        comboBox_mod_rep->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(QINFO);
    } // setupUi

    void retranslateUi(QWidget *QINFO)
    {
        QINFO->setWindowTitle(QApplication::translate("QINFO", "QINFO", 0));
        checkBox_mortal->setText(QApplication::translate("QINFO", "si mortales, vivunt donec", 0));
        label_9->setText(QApplication::translate("QINFO", "mutationis probabilitas", 0));
        label_7->setText(QApplication::translate("QINFO", "insulae dimensio partialis", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QINFO", "chaos", 0)
         << QApplication::translate("QINFO", "insulae", 0)
         << QApplication::translate("QINFO", "rete", 0)
         << QApplication::translate("QINFO", "rete per speciem", 0)
        );
        label->setText(QApplication::translate("QINFO", "quantitas in specie", 0));
        comboBox_mod_rep->clear();
        comboBox_mod_rep->insertItems(0, QStringList()
         << QApplication::translate("QINFO", "effectivitas", 0)
         << QApplication::translate("QINFO", "parens casualis", 0)
         << QApplication::translate("QINFO", "cruciamentum", 0)
        );
        checkBox_incest->setText(QApplication::translate("QINFO", "incesti, modus replicandi", 0));
        label_4->setText(QApplication::translate("QINFO", "genomatis specierum pars", 0));
        label_3->setText(QApplication::translate("QINFO", "modus ponendi", 0));
        pushButton_gengen->setText(QApplication::translate("QINFO", "genea species: regenerare", 0));
        label_2->setText(QApplication::translate("QINFO", "quantitas specierum", 0));
        pushButton_gen->setText(QApplication::translate("QINFO", "Genera", 0));
        pushButton_add->setText(QApplication::translate("QINFO", "Manu adde", 0));
        pushButton_destr->setText(QApplication::translate("QINFO", "Destrue", 0));
        pushButton_start->setText(QApplication::translate("QINFO", ">", 0));
        pushButton_import->setText(QApplication::translate("QINFO", "Importa", 0));
        pushButton_export->setText(QApplication::translate("QINFO", "Exporta", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_species->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QINFO", "#", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_species->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QINFO", "populatio", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_species->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QINFO", "massa", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_cur->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("QINFO", "in selecto", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_cur->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("QINFO", "generatio", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_cur->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("QINFO", "massa", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_cur->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("QINFO", "stamina", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_cur->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("QINFO", "aetas", 0));

        const bool __sortingEnabled = tableWidget_cur->isSortingEnabled();
        tableWidget_cur->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_cur->item(0, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("QINFO", "vivus", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_cur->item(1, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("QINFO", "0", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_cur->item(2, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("QINFO", "0", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_cur->item(3, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("QINFO", "0", 0));
        tableWidget_cur->setSortingEnabled(__sortingEnabled);

        label_fps->setText(QApplication::translate("QINFO", "gradus/picturae per secundam", 0));
        label_8->setText(QApplication::translate("QINFO", "attenuatio evanescendi", 0));
        label_11->setText(QApplication::translate("QINFO", "secundae elapsae", 0));
        label_6->setText(QApplication::translate("QINFO", "gressus currens", 0));
        label_10->setText(QApplication::translate("QINFO", "processi", 0));
        label_12->setText(QApplication::translate("QINFO", "substratum / modus colorandi", 0));
        comboBox_subst->clear();
        comboBox_subst->insertItems(0, QStringList()
         << QApplication::translate("QINFO", "nigrum", 0)
         << QApplication::translate("QINFO", "album", 0)
         << QApplication::translate("QINFO", "cinereum", 0)
        );
        comboBox_vismod->clear();
        comboBox_vismod->insertItems(0, QStringList()
         << QApplication::translate("QINFO", "species", 0)
         << QApplication::translate("QINFO", "stamina", 0)
         << QApplication::translate("QINFO", "vitae longitudo", 0)
         << QApplication::translate("QINFO", "generatio", 0)
        );
        label_5->setText(QApplication::translate("QINFO", "quantitas vivorum", 0));
    } // retranslateUi

};

namespace Ui {
    class QINFO: public Ui_QINFO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QINFO_H
