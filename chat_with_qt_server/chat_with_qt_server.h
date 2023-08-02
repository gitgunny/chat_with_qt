#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTextBrowser>
//#include <QtNetwork/QTcpServer>
//#include <QtNetwork/QTcpSocket>
#include "ui_chat_with_qt_server.h"

class chat_with_qt_server_w : public QWidget
{
	Q_OBJECT

public:
	chat_with_qt_server_w(QWidget* parent = nullptr);
	~chat_with_qt_server_w();

private:
	int port = 0;
	QString message;
	QTextBrowser* textBrowser;
	QPushButton* pushButton1, * pushButton2;
	//QTcpServer server;
	//QTcpSocket* client;

public:
	void initServer();

signals:
	void sendShow();

public slots:
	void pushButton1Clicked();
	void receivePort(const int& port);
	void pushButton2Clicked();

	//private:
	//    Ui::chat_with_qt_serverClass ui;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class chat_with_qt_server_d : public QDialog
{
	Q_OBJECT

public:
	chat_with_qt_server_d(QWidget* parent = nullptr);
	~chat_with_qt_server_d();

private:
	QLabel* label1, * label2;
	QTextEdit* textEdit1, * textEdit2;
	QPushButton* pushButton;

signals:
	void sendPort(const int& port);

public slots:
	void receiveShow();
	void pushButtonClicked();

	//private:
	//    Ui::chat_with_qt_serverClass ui;
};
