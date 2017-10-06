#include "gpssimprovider.h"
#include "ui_gpssimprovider.h"
#include <QTcpSocket>
#include "cbor.h"
#include "packetizer.h"
GPSSimProvider::GPSSimProvider(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GPSSimProvider)
{
	ui->setupUi(this);
	connect(ui->connectPushButton,SIGNAL(clicked(bool)),this,SLOT(connectButtonClicked()));
	connect(ui->sendSinglePushButton,SIGNAL(clicked(bool)),this,SLOT(sendSingleClicked()));
	connect(ui->sendRepeatPushButton,SIGNAL(clicked(bool)),this,SLOT(sendRepeatClicked()));
}

GPSSimProvider::~GPSSimProvider()
{
	delete ui;
}

void GPSSimProvider::connectButtonClicked()
{
	socket = new QTcpSocket(this);
	m_packetizer = new Packetizer(socket);
	socket->connectToHost("127.0.0.1",5001);
	socket->waitForConnected();
}

void GPSSimProvider::sendSingleClicked()
{
	QVariantMap map;
	map["type"] = "data";
	QVariantMap datamap;
	datamap["domain"] = "Nav.Parameters";
	datamap["name"] = "GGA";
	datamap["value"] = "$GPGGA 12.52";
	map["value"] = datamap;
	QByteArray mappacked = CBOR::pack(map);
	QByteArray packet = m_packetizer->generatePacket(mappacked);

	socket->write(packet);
	socket->waitForBytesWritten();
}

void GPSSimProvider::sendRepeatClicked()
{

}
