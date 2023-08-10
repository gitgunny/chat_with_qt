#include "chat_with_qt_client.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	clientWidget w;
	clientDialog d;
	clientClass c;

	QObject::connect(&w, &clientWidget::dialogShow, &d, &clientDialog::dialogShow);
	QObject::connect(&d, &clientDialog::serverConnect, &c, &clientClass::serverConnect);
	QObject::connect(&w, &clientWidget::serverDisconnect, &c, &clientClass::serverDisconnect);
	QObject::connect(&w, &clientWidget::sendMessage, &c, &clientClass::sendMessage);
	QObject::connect(&c, &clientClass::setWidgetTitle, &w, &clientWidget::setWidgetTitle);
	QObject::connect(&c, &clientClass::textBrowserAppend, &w, &clientWidget::textBrowserAppend);
	QObject::connect(&c, &clientClass::pushButton1Status, &w, &clientWidget::pushButton1Status);
	QObject::connect(&c, &clientClass::pushButton2Status, &w, &clientWidget::pushButton2Status);
	QObject::connect(&c, &clientClass::pushButton3Status, &w, &clientWidget::pushButton3Status);

	w.show();

	return a.exec();
}
