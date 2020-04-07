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


	Connecter c;
	

	c.show();

	return app.exec();
}
