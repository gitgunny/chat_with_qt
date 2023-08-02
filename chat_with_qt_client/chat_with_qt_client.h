#pragma once

#include <QtWidgets/QWidget>
#include "ui_chat_with_qt_client.h"

class chat_with_qt_client : public QWidget
{
    Q_OBJECT

public:
    chat_with_qt_client(QWidget *parent = nullptr);
    ~chat_with_qt_client();

private:
    Ui::chat_with_qt_clientClass ui;
};
