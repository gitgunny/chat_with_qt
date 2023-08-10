#include "chat_with_qt_server.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	serverWidget w;
	serverDialog d;
	serverClass s;

	QObject::connect(&w, &serverWidget::dialogShow, &d, &serverDialog::dialogShow);
	QObject::connect(&d, &serverDialog::serverStart, &s, &serverClass::serverStart);
	QObject::connect(&w, &serverWidget::serverStop, &s, &serverClass::serverStop);
	QObject::connect(&s, &serverClass::setWidgetTitle, &w, &serverWidget::setWidgetTitle);
	QObject::connect(&s, &serverClass::textBrowserAppend, &w, &serverWidget::textBrowserAppend);
	QObject::connect(&s, &serverClass::pushButton1Status, &w, &serverWidget::pushButton1Status);
	QObject::connect(&s, &serverClass::pushButton2Status, &w, &serverWidget::pushButton2Status);

	w.show();

	return a.exec();
}
