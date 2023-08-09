#include "chat_with_qt_client.h"

clientWidget::clientWidget(QWidget* parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	//QMessageBox::information(this, nullptr, "w");

	setFixedSize(500, 300);
	setWindowTitle("127.0.0.1 : 서버 접속 대기");

	textBrowser = new QTextBrowser(this);
	textBrowser->setGeometry(10, 10, 400, 240);

	textEdit = new QTextEdit(this);
	textEdit->setGeometry(10, 260, 400, 30);

	pushButton1 = new QPushButton(this);
	pushButton1->setGeometry(415, 10, 80, 120);
	pushButton1->setText("서버 접속");
	pushButton1->setEnabled(true);

	pushButton2 = new QPushButton(this);
	pushButton2->setGeometry(415, 130, 80, 120);
	pushButton2->setText("접속 종료");
	pushButton2->setEnabled(false);

	pushButton3 = new QPushButton(this);
	pushButton3->setGeometry(415, 260, 80, 30);
	pushButton3->setText("전송");
	pushButton3->setEnabled(false);

	connect(pushButton1, &QPushButton::clicked, this, &clientWidget::pushButton1Clicked);
	connect(pushButton2, &QPushButton::clicked, this, &clientWidget::pushButton2Clicked);
	connect(pushButton3, &QPushButton::clicked, this, &clientWidget::pushButton3Clicked);
}

clientWidget::~clientWidget()
{
	//QMessageBox::information(this, nullptr, "~w");
}

void clientWidget::pushButton1Clicked()
{
	dialogShow();
}

void clientWidget::pushButton2Clicked()
{
	serverDisconnect();
}

void clientWidget::pushButton3Clicked()
{
	sendMessage(textEdit->toPlainText());
	textEdit->setText("");
}

void clientWidget::setWidgetTitle(QString title)
{
	setWindowTitle(title);
}

void clientWidget::pushButton1Status(bool status)
{
	pushButton1->setEnabled(status);
}

void clientWidget::pushButton2Status(bool status)
{
	pushButton2->setEnabled(status);
}

void clientWidget::pushButton3Status(bool status)
{
	pushButton3->setEnabled(status);
}

void clientWidget::messageAppend(QString text)
{
	textBrowser->append(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

clientDialog::clientDialog(QWidget* parent)
	: QDialog(parent)
{
	//QMessageBox::information(this, nullptr, "d");

	setWindowTitle("서버 접속");
	setFixedSize(250, 120);

	label1 = new QLabel(this);
	textEdit1 = new QTextEdit(this);

	label1->move(12, 10);
	label1->setText("서버 주소");

	textEdit1->setGeometry(80, 7, 150, 26);
	textEdit1->setPlaceholderText("127.0.0.1");
	textEdit1->setDisabled(true);

	label2 = new QLabel(this);
	textEdit2 = new QTextEdit(this);

	label2->move(12, 45);
	label2->setText("서버 포트");

	textEdit2->setGeometry(80, 42, 150, 26);
	textEdit2->setPlaceholderText("1~65535");

	pushButton = new QPushButton(this);

	pushButton->setGeometry(10, 80, 222, 30);
	pushButton->setText("접속");

	connect(pushButton, &QPushButton::clicked, this, &clientDialog::pushButtonClicked);
}

clientDialog::~clientDialog()
{
	//QMessageBox::information(this, nullptr, "~d");
}

void clientDialog::pushButtonClicked()
{
	if (textEdit2->toPlainText().toInt() == false)
		QMessageBox::warning(this, nullptr, "숫자만 입력 가능합니다.");
	else if (textEdit2->toPlainText().toInt() < 1 || textEdit2->toPlainText().toInt() > 65535)
		QMessageBox::warning(this, nullptr, "1~65535까지만 입력 가능합니다.");
	else
	{
		serverConnect(textEdit2->toPlainText().toInt());
		close();
	}
}

void clientDialog::dialogShow()
{
	exec();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

clientClass::clientClass(QWidget* parent)
	: QWidget(parent)
{
	//QMessageBox::information(this, nullptr, "s");
}

clientClass::~clientClass()
{
	//QMessageBox::information(this, nullptr, "~s");
}

void clientClass::serverConnect(const int& port)
{
	clientSocket.connectToHost(QHostAddress::QHostAddress("127.0.0.1"), port);

	if (clientSocket.waitForConnected() == false)
	{
		QMessageBox::critical(nullptr, nullptr, "서버 연결에 실패 하였습니다.");
		return;
	}

	setWidgetTitle(QString::QString("127.0.0.1 : %1 서버 접속 중").arg(port));
	messageAppend(QString::QString("127.0.0.1 : %1 서버 접속").arg(port));
	pushButton1Status(false);
	pushButton2Status(true);
	pushButton3Status(true);
}

void clientClass::serverDisconnect()
{
	if (clientSocket.isOpen() == false)
		return;

	clientSocket.close();

	setWidgetTitle("127.0.0.1 : 서버 접속 대기");
	messageAppend("127.0.0.1 : 접속 종료");
	pushButton1Status(true);
	pushButton2Status(false);
	pushButton3Status(false);
}

void clientClass::sendMessage(QString text)
{
	messageAppend(text);
}
