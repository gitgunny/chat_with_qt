#include "chat_with_qt_server.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	chat_with_qt_server_w w;
	chat_with_qt_server_d d;

	QObject::connect(&w, &chat_with_qt_server_w::sendShow, &d, &chat_with_qt_server_d::receiveShow);
	QObject::connect(&d, &chat_with_qt_server_d::sendPort, &w, &chat_with_qt_server_w::receivePort);

	w.show();
	//d.exec();

	return a.exec();
}
