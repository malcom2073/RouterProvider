#include "obdsimprovider.h"
#include "ui_obdsimprovider.h"
#include <QTcpSocket>
OBDSimProvider::OBDSimProvider(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OBDSimProvider)
{
	ui->setupUi(this);
	connect(ui->connectPushButton,SIGNAL(clicked(bool)),this,SLOT(connectButtonClicked()));
}

OBDSimProvider::~OBDSimProvider()
{
	delete ui;
}

void OBDSimProvider::connectButtonClicked()
{
	socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1",5001);
	socket->waitForConnected();
}
