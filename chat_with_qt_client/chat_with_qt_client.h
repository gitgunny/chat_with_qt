#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QtNetwork/QTcpSocket>
#include "ui_chat_with_qt_client.h"

#include <QDebug> //*// 최종 디버그시 생성자 소멸자 순서 확인(X 클릭 종료시에도 확인)

class clientWidget : public QWidget
{
	Q_OBJECT

public:
	clientWidget(QWidget* parent = nullptr);
	~clientWidget();

private:
	QTextBrowser* textBrowser;
	QTextEdit* textEdit;
	QPushButton* pushButton1, * pushButton2, * pushButton3;

signals:
	void dialogShow();
	void serverDisconnect();
	void sendMessage(QString text);

public slots:
	void pushButton1Clicked();
	void pushButton2Clicked();
	void pushButton3Clicked();

	void setWidgetTitle(QString title);
	void pushButton1Status(bool status);
	void pushButton2Status(bool status);
	void pushButton3Status(bool status);
	void messageAppend(QString text);

	//private:
	//    Ui::chat_with_qt_clientClass ui;
};

class clientDialog : public QDialog
{
	Q_OBJECT

public:
	clientDialog(QWidget* parent = nullptr);
	~clientDialog();

private:
	QLabel* label1, * label2;
	QTextEdit* textEdit1, * textEdit2;
	QPushButton* pushButton;

signals:
	void serverConnect(const int& port);

public slots:
	void pushButtonClicked();

	void dialogShow();
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class clientClass : public QWidget
{
	Q_OBJECT

public:
	clientClass(QWidget* parent = nullptr);
	~clientClass();

private:
	QTcpSocket clientSocket;

signals:
	void setWidgetTitle(QString title);
	void pushButton1Status(bool status);
	void pushButton2Status(bool status);
	void pushButton3Status(bool status);
	void messageAppend(QString text);

public slots:
	void serverConnect(const int& port);
	void serverDisconnect();
	void sendMessage(QString text);
};
