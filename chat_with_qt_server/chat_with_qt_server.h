#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "ui_chat_with_qt_server.h"

#include <QDebug> //*// 최종 디버그시 생성자 소멸자 순서 확인(X 클릭 종료시에도 확인)

class serverWidget : public QWidget
{
	Q_OBJECT

public:
	serverWidget(QWidget* parent = nullptr);
	~serverWidget();

private:
	QTextBrowser* textBrowser;
	QPushButton* pushButton1, * pushButton2;

signals:
	void dialogShow();
	void serverStop();

public slots:
	void pushButton1Clicked();
	void pushButton2Clicked();

	void setWidgetTitle(QString title);
	void textBrowserAppend(QString text);
	void pushButton1Status(bool status);
	void pushButton2Status(bool status);

	//private:
	//    Ui::chat_with_qt_serverClass ui;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class serverDialog : public QDialog
{
	Q_OBJECT

public:
	serverDialog(QWidget* parent = nullptr);
	~serverDialog();

private:
	QLabel* label1, * label2;
	QTextEdit* textEdit1, * textEdit2;
	QPushButton* pushButton;

signals:
	void serverStart(const int& port);

public slots:
	void catchEnter();
	void pushButtonClicked();

	void dialogShow();
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class serverClass : public QWidget
{
	Q_OBJECT

public:
	serverClass(QWidget* parent = nullptr);
	~serverClass();

private:
	QTcpServer serverSocket;
	QTcpSocket* clientSocket;

signals:
	void setWidgetTitle(QString title);
	void textBrowserAppend(QString text);
	void pushButton1Status(bool status);
	void pushButton2Status(bool status);

public slots:
	void newConnection();
	void readyRead();
	void disconnected();

	void serverStart(const int& port);
	void serverStop();
};
