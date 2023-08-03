#include "chat_with_qt_server.h"

serverWidget::serverWidget(QWidget* parent)
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

	connect(pushButton1, &QPushButton::clicked, this, &serverWidget::pushButton1Clicked);
	connect(pushButton2, &QPushButton::clicked, this, &serverWidget::pushButton2Clicked);
}

serverWidget::~serverWidget()
{
	//QMessageBox::information(this, nullptr, "~w");
}

void serverWidget::pushButton1Clicked()
{
	dialogShow();
}

void serverWidget::pushButton2Clicked()
{
	serverStop();
}

void serverWidget::setWidgetTitle(QString title)
{
	setWindowTitle(title);
}

void serverWidget::pushButton1Status(bool status)
{
	pushButton1->setEnabled(status);
}

void serverWidget::pushButton2Status(bool status)
{
	pushButton2->setEnabled(status);
}

void serverWidget::messageAppend(QString text)
{
	textBrowser->append(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

serverDialog::serverDialog(QWidget* parent)
	: QDialog(parent)
{
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
	textEdit2->setPlaceholderText("1~65535");

	pushButton = new QPushButton(this);

	pushButton->setGeometry(10, 80, 222, 30);
	pushButton->setText("생성");

	connect(pushButton, &QPushButton::clicked, this, &serverDialog::pushButtonClicked);
}

serverDialog::~serverDialog()
{
	//QMessageBox::information(this, nullptr, "~d");
}

void serverDialog::pushButtonClicked()
{
	if (textEdit2->toPlainText().toInt() == false)
		QMessageBox::warning(this, nullptr, "숫자만 입력 가능합니다.");
	else if (textEdit2->toPlainText().toInt() < 1 || textEdit2->toPlainText().toInt() > 65535)
		QMessageBox::warning(this, nullptr, "1~65535까지만 입력 가능합니다.");
	else
	{
		serverStart(textEdit2->toPlainText().toInt());
		close();
	}
}

void serverDialog::dialogShow()
{
	exec();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

serverClass::serverClass(QWidget* parent)
	: QWidget(parent)
{
	//QMessageBox::information(this, nullptr, "s");
}

serverClass::~serverClass()
{
	//QMessageBox::information(this, nullptr, "~s");
}

void serverClass::serverStart(const int& port)
{
	server server_socket;
	if (server_socket.listen(QHostAddress::QHostAddress("127.0.0.1"), port) == false)
	{
		QMessageBox::critical(nullptr, nullptr, "서버 생성에 실패 하였습니다.");
		return;
	}

	setWidgetTitle(QString::QString("127.0.0.1 : %1 서버 실행 중").arg(port));
	messageAppend(QString::QString("127.0.0.1 : %1 서버 시작").arg(port));
	pushButton1Status(false);
	pushButton2Status(true);

	//////////////////////////////////////////////////
	// 미구현
	//////////////////////////////////////////////////

	//*// 서버 소멸자로 이동
	server_socket.close();
	server_socket.deleteLater();
}

void serverClass::serverStop()
{
	//*// 서버 소멸자 실행?

	setWidgetTitle("127.0.0.1 : 서버 실행 대기");
	messageAppend("127.0.0.1 : 서버 종료");
	pushButton2Status(false);
	pushButton1Status(true);
}

void serverClass::sendMessage(QString text)
{
	messageAppend(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

server::server(QWidget* parent)
	: QTcpServer(parent)
{
	//QMessageBox::information(this, nullptr, "ss");
}

server::~server()
{
	//QMessageBox::information(this, nullptr, "~ss");
}

void server::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket* clientSocket = new QTcpSocket(this);
	clientSocket->setSocketDescriptor(socketDescriptor);
	clients.append(clientSocket);

	connect(clientSocket, &QTcpSocket::readyRead, this, &server::readClient);
	connect(clientSocket, &QTcpSocket::disconnected, this, &server::clientDisconnected);

	//*// 클라이언트 번호 및 아이피 포트번호 인자로 전달
	sendMessage("000.000.000.000 : 0000 클라이언트(0000) 접속");
}

void server::readClient()
{
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	if (clientSocket == nullptr)
		return;

	while (clientSocket->bytesAvailable() > 0)
	{
		QByteArray data = clientSocket->readAll();
		//*// 클라이언트 번호 인자로 전달
		sendMessage(QString::QString("클라이언트(0000) : %1").arg(data));

		// Echo the message back to all connected clients
		for (QTcpSocket* otherClient : clients)
		{
			if (otherClient != clientSocket)
			{
				otherClient->write(data);
			}
		}
	}
}

void server::clientDisconnected()
{
	QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
	if (clientSocket == nullptr)
		return;

	clients.removeOne(clientSocket);
	clientSocket->deleteLater();

	//*// 클라이언트 번호 및 아이피 포트번호 인자로 전달
	sendMessage("000.000.000.000 : 0000 클라이언트(0000) 접속 종료");
}
