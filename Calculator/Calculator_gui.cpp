#include "Calculator_gui.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QChar>

using namespace Gui;

Calculator::Calculator(QWidget* parent/*=0*/) :
	QWidget(parent),
	display(new QLabel)
{
	/*display->setSegmentStyle(QLCDNumber::Filled);*/
	display->setFrameStyle(1);

	QFont font; font.setPointSize(20);
	display->setFont(font);
	display->setMinimumSize(150, 150);
	display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


	QChar buttons[5][4] = {
		{'^','(',')','%'},
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','+'},
		{'0','.','=','-'}
	};

	//Layout's
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(display, 0, 0, 1, 4);
	layout->addWidget(this->CreateButton("CE"), 1, 3);
	layout->addWidget(this->CreateButton("<-"), 1, 2);
	layout->addWidget(this->CreateButton("()"), 1, 1);

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			layout->addWidget(this->CreateButton(buttons[i][j]), i + 2, j);
		}
	}

	QWidget::setLayout(layout);
}

std::string Gui::Calculator::GetExpression()
{
	return display->text().toStdString();
}

QPushButton* Calculator::CreateButton(const QString& str)
{
	QPushButton* cmd = new QPushButton(str);
	cmd->setMinimumSize(40, 40);
	connect(cmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
	return cmd;
}


void Calculator::InitialState()
{
	result.clear();
	parentheses_count = 0;
	display->setText(result);
}


bool Calculator::is_Parentheses(const QString& str)
{
	return str == '(' || str == ')' || str == "()";
}

void Calculator::ParenthesesHandler(const QString& str)
{
	auto addOpener = [&]() {
		if (!result.isEmpty() && (result.back().isDigit() || result.back() == ')'))
			result += '*';
		result += '(';
		parentheses_count++;
	};
	auto addCloser = [&]() {
		/*if (QRegExp(QString(result.back())).exactMatch("\\D(?)?"))*/
		if(!result.back().isDigit() && result.back() != '(' && result.back() != ')')
			result.chop(1);
		result += ')';
		parentheses_count--;
	};

	if (str == '(') {
		addOpener();
	}
	else if (str == ')') {
		if (parentheses_count != 0)
			addCloser();
	}
	else if (str == "()") {
		if (!result.isEmpty() && result.back() != '(' && parentheses_count != 0)
			addCloser();
		else addOpener();
	}

}

bool Calculator::is_Operation(const QChar ch) const
{
	//operator==(QString&,QChar)
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
		ch == '%' || ch == '^';
}

void Calculator::OperationsHandler(const QChar op)
{
	auto PasteOp = [&]() {
		if (result.isEmpty())
		{
			if (op == '-') result += op;
		}
		else if (result.back() == '(')
		{
			if (op == '-')
				result += op;
			return;
		}
		else
			result += op;
	};

	if (!result.isEmpty()) {
		if (is_Operation(result.back()) || result.back() == '.')
		{
			result.chop(1);
			PasteOp();
		}
		else
			PasteOp();
	}
	else PasteOp();
}

bool Calculator::AllowedPoint() const
{
	if (result.isEmpty() || !result.back().isDigit()) return false;
	for (QString::const_reverse_iterator it = result.crbegin(); it != result.crend(); ++it)
	{
		if (/*QRegExp("[0-9]").exactMatch(*it)*/it->isDigit()) continue;
		else if (*it == '.') return false;
		else return true;
	}
	return true;
}

void Calculator::slotButtonClicked() {
	QString str = qobject_cast<QPushButton*>(sender())->text();

	if (str == "=")
	{
		emit signalCalculate(display->text());
		return;
	}
	if (str == "CE") {
		InitialState();
		return;
	}
	if (str == "<-") {
		if (result.isEmpty()) return;
		if (result.back() == '(') parentheses_count--;
		if (result.back() == ')') parentheses_count++;
		result.chop(1);
		display->setText(result);
		return;
	}
	if (is_Parentheses(str)) {
		ParenthesesHandler(str);
		display->setText(result);
		return;
	}


	Q_ASSERT(str.size() == 1);
	const QChar ch = str.front();

	if (is_Operation(ch)) {
		OperationsHandler(ch);
	}
	else if (ch == '.') {
		if (AllowedPoint())
			result += ch;//append
	}
	else if (ch.isDigit())
	{
		result.append(ch);
	}

	display->setText(result);
}


void Calculator::slotShowResult(double result_value) {
	this->result = QString::number(result_value);
	display->setText(this->result);
}




