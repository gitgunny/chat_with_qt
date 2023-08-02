#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTextBrowser>
#include "ui_chat_with_qt_server.h"

class chat_with_qt_server_w : public QWidget
{
	Q_OBJECT

public:
	chat_with_qt_server_w(QWidget* parent = nullptr);
	~chat_with_qt_server_w();

public:
	int port;

private:
	QTextBrowser* textBrowser;

public slots:

	//private:
	//    Ui::chat_with_qt_serverClass ui;
};

class chat_with_qt_server_d : public QDialog
{
	Q_OBJECT

public:
	chat_with_qt_server_d(QWidget* parent = nullptr);
	~chat_with_qt_server_d();

public:
	chat_with_qt_server_w w;

private:
	QLabel* label1, * label2;
	QTextEdit* textEdit1, * textEdit2;
	QPushButton* pushButton;

public slots:
	void pushButtonClicked();

	//private:
	//    Ui::chat_with_qt_serverClass ui;
};
