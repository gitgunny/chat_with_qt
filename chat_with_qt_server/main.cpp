#include "chat_with_qt_server.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//chat_with_qt_server_w w;
	chat_with_qt_server_d d;
	d.show();
	//w.show();
	return a.exec();
}
