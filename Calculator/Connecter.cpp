#include "Connecter.h"
#include "RPNconverter.h"
#include <QDebug>

Connecter::Connecter() :
	gui(new Gui::Calculator)
{
	gui->setWindowTitle("Calculator_with_stack_beta");
	QObject::connect(gui, &Gui::Calculator::signalCalculate, this, &Connecter::Calculate);
	QObject::connect(this, &Connecter::signalforgui, gui, &Gui::Calculator::slotShowResult);
}

void Connecter::Calculate(const QString& str) {
	std::string expr = str.toStdString();

	//by default std::deque<std::string>
	try {
		auto s = RPNCalculator::Converter::Converte(expr);
		auto result = calculator.Calculate(s.begin(), s.end());
		emit signalforgui(result);
	}
	catch (const std::logic_error& ex) {
		qDebug() << "logic error" << ex.what();
	}
	catch (const std::exception& ex) {
		qDebug()  << ex.what();
	}
	catch (...) {
		qDebug() << "unknown error";
	}
	
}

Connecter::~Connecter()
{
	delete gui;
}
