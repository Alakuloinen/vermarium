/********************************************************************************
** Form generated from reading UI file 'glw.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLW_H
#define UI_GLW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QOpenGLWidget>

QT_BEGIN_NAMESPACE

class Ui_GLW
{
public:

    void setupUi(QOpenGLWidget *GLW)
    {
        if (GLW->objectName().isEmpty())
            GLW->setObjectName(QStringLiteral("GLW"));
        GLW->resize(810, 810);

        retranslateUi(GLW);

        QMetaObject::connectSlotsByName(GLW);
    } // setupUi

    void retranslateUi(QOpenGLWidget *GLW)
    {
        GLW->setWindowTitle(QApplication::translate("GLW", "GLW", 0));
    } // retranslateUi

};

namespace Ui {
    class GLW: public Ui_GLW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLW_H
