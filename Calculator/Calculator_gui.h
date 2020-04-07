#pragma once
#include <QWidget>
#include <QStack>

class QLabel;
class QPushButton;

namespace Gui {
	class Calculator :public QWidget
	{
		Q_OBJECT

	public:
		Calculator(QWidget* parent = Q_NULLPTR);
		std::string GetExpression();
		~Calculator() { delete display; }

		using r_type = double;
	private slots:
		void slotButtonClicked();
		void slotShowResult(double);
	signals:
		void signalCalculate(QString);

	private:
		QPushButton* CreateButton(const QString&);


		void InitialState();

		
		bool is_Parentheses(const QString&);
		void ParenthesesHandler(const QString&);

		bool is_Operation(const QChar) const;
		void OperationsHandler(const QChar);
		bool AllowedPoint() const;


		QLabel* display;
		QString result;
		size_t parentheses_count = 0;
	};

}