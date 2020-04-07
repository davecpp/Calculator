#pragma once
#include "Calculator.h"
#include "Calculator_gui.h"
#include <QObject>



class Connecter : public QObject {
	Q_OBJECT
public:
	Connecter();
	void show() {
		gui->show();
	}
	~Connecter();
public slots:
	void Calculate(const QString&);
signals:
	void signalforgui(RPNCalculator::op_type);
private:
	Gui::Calculator* gui;
	RPNCalculator::RPNCalculator calculator;

};

