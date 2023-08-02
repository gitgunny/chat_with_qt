#include "chat_with_qt_server.h"

chat_with_qt_server_w::chat_with_qt_server_w(QWidget* parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	//QMessageBox::information(this, nullptr, "w");

	setFixedSize(500, 300);
	setWindowTitle("127.0.0.1 : 서버 실행 대기");

	textBrowser = new QTextBrowser(this);
	textBrowser->setGeometry(10, 10, 480, 220);

	pushButton1 = new QPushButton(this);
	pushButton1->setGeometry(10, 240, 230, 50);
	pushButton1->setText("서버 시작");

	pushButton2 = new QPushButton(this);
	pushButton2->setGeometry(260, 240, 230, 50);
	pushButton2->setText("서버 종료");
	pushButton2->setDisabled(true);

	connect(pushButton1, &QPushButton::clicked, this, &chat_with_qt_server_w::pushButton1Clicked);
	connect(pushButton2, &QPushButton::clicked, this, &chat_with_qt_server_w:: pushButton2Clicked);
}

chat_with_qt_server_w::~chat_with_qt_server_w()
{
	//QMessageBox::information(this, nullptr, "~w");
}

void chat_with_qt_server_w::initServer()
{
	/*
	//if (server.listen(QHostAddress::QHostAddress("127.0.0.1"), port) == false)
	if (server.listen(QHostAddress::Any, port) == false)
		QMessageBox::critical(this, nullptr, "서버 실행에 실패 하였습니다.");
	else
	{
		message += QString::QString("127.0.0.1 : %1 서버 실행\n").arg(port);

		while (server.isListening())
		{
			if (server.waitForNewConnection(-1))
			{
				client = server.nextPendingConnection();
				message += "클라이언트 접속\n"; ////////// 접속 클라이언트 아이피 포트 문구추가

				QString tmpMessage;
				if (client->waitForReadyRead())
					tmpMessage = client->readAll();

				message += tmpMessage;

				QTextStream stream(client);
				stream << tmpMessage;
				client->flush();
			}
		}
	}
	*/
}

void chat_with_qt_server_w::pushButton1Clicked()
{
	emit sendShow();
}

void chat_with_qt_server_w::receivePort(const int& port)
{
	this->port = port;
	setWindowTitle(QString::QString("127.0.0.1 : %1 서버 실행 중").arg(port));
	pushButton2->setEnabled(true);
	pushButton1->setDisabled(true);
}

void chat_with_qt_server_w::pushButton2Clicked()
{
	setWindowTitle("127.0.0.1 : 서버 실행 대기");
	pushButton1->setEnabled(true);
	pushButton2->setDisabled(true);

	//client->close();
	//client->deleteLater();
	//server.close();
	//server.deleteLater();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

chat_with_qt_server_d::chat_with_qt_server_d(QWidget* parent)
	: QDialog(parent)
{
	//ui.setupUi(this);
	//QMessageBox::information(this, nullptr, "d");

	setWindowTitle("서버 생성");
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
	textEdit2->setPlaceholderText("0~65535");

	pushButton = new QPushButton(this);

	pushButton->setGeometry(10, 80, 222, 30);
	pushButton->setText("생성");

	connect(pushButton, &QPushButton::clicked, this, &chat_with_qt_server_d::pushButtonClicked);
}

chat_with_qt_server_d::~chat_with_qt_server_d()
{
	//QMessageBox::information(this, nullptr, "~d");
}

void chat_with_qt_server_d::receiveShow()
{
	show();
}

void chat_with_qt_server_d::pushButtonClicked()
{
	if (textEdit2->toPlainText().toInt() == false)
		QMessageBox::warning(this, nullptr, "숫자만 입력 가능합니다.");
	else if (textEdit2->toPlainText().toInt() < 0 || textEdit2->toPlainText().toInt() > 65535)
		QMessageBox::warning(this, nullptr, "0~65535까지만 입력 가능합니다.");
	else
	{
		emit sendPort(textEdit2->toPlainText().toInt());
		close();
	}
}
