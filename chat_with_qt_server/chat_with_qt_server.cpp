#include "chat_with_qt_server.h"

chat_with_qt_server_w::chat_with_qt_server_w(QWidget* parent)
	: QWidget(parent)
{
	//ui.setupUi(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	setWindowTitle("127.0.0.1 : (포트번호)");
	setFixedSize(500, 300);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	textBrowser = new QTextBrowser(this);
	textBrowser->setGeometry(0, 0, 400, 200);
	textBrowser->setText(QString::number(port));
	//////////////////////////////////////////////////
	// 생성자 d -> w 아님 w -> d
	// 이로 인한 포트번호 인수전달 오류
	//////////////////////////////////////////////////
}

chat_with_qt_server_w::~chat_with_qt_server_w()
{}


chat_with_qt_server_d::chat_with_qt_server_d(QWidget* parent)
	: QDialog(parent)
{
	//ui.setupUi(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	setWindowTitle("서버 생성");
	setFixedSize(250, 120);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	label1 = new QLabel(this);
	textEdit1 = new QTextEdit(this);

	label1->move(12, 10);
	label1->setText("서버 주소");

	textEdit1->setGeometry(80, 7, 150, 26);
	textEdit1->setPlaceholderText("127.0.0.1");
	textEdit1->setDisabled(true);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	label2 = new QLabel(this);
	textEdit2 = new QTextEdit(this);

	label2->move(12, 45);
	label2->setText("서버 포트");

	textEdit2->setGeometry(80, 42, 150, 26);
	textEdit2->setPlaceholderText("1234");
	////////////////////////////////////////////////////////////////////////////////////////////////////
	pushButton = new QPushButton(this);

	pushButton->setGeometry(10, 80, 222, 30);
	pushButton->setText("생성");
	////////////////////////////////////////////////////////////////////////////////////////////////////

	connect(pushButton, &QPushButton::clicked, this, &chat_with_qt_server_d::pushButtonClicked);
}

chat_with_qt_server_d::~chat_with_qt_server_d()
{}

void chat_with_qt_server_d::pushButtonClicked()
{
	if (textEdit2->toPlainText().toInt())
	{
		w.port = textEdit2->toPlainText().toInt();
		w.show();
		close();
	}
	else
		QMessageBox::warning(this, nullptr, "숫자만 입력 가능합니다.");
}
