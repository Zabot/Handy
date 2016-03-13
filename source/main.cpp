#include <QApplication>
#include "tutorwidget.h"

#include "SignListener.h"
#include "LeapMotion.h"

int main(int argc, char **argv)
{
	QApplication app (argc, argv);

	tutorwidget wdg;
	wdg.show();

	SignListener sign(wdg);
	LeapMotion leap(sign);

	return app.exec();
}

