#include "chat_with_qt_client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chat_with_qt_client w;
    w.show();
    return a.exec();
}
