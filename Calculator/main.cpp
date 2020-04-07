#include "Calculator_gui.h"
#include <QtWidgets/QApplication>
#include "Connecter.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	/*Gui::Calculator calculator;

	calculator.setWindowTitle("Calculator");
	

	calculator.show();*/

	QPushButton* pb = new QPushButton("Menu");
	QMenu* mn = new QMenu(pb);
	
	mn->addAction("QQuitt", &app, SLOT(quit()));
	pb->setMenu(mn);
	pb->show();



	Connecter c;
	

	c.show();

	return app.exec();
}
