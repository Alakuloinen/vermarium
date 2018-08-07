#include "glw.h"
#include "qinfo.h"
#include <QtWidgets/QApplication>
#include <QSurfaceFormat>
#include <QTranslator>

int main(int argc, char *argv[])
{
 	QApplication a(argc, argv);

	QTranslator translator;
	translator.load(QLocale(), "vermarium", QLatin1String("_"));
	a.installTranslator(&translator);

   QSurfaceFormat fmt;
    fmt.setSamples(2);
	fmt.setDepthBufferSize(0);
	fmt.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(fmt);

	QINFO w;
	w.show();
	return a.exec();
}
