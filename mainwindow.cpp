#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QByteArray>
#include "cbor.h"
#include <QVariant>
#include <QVariantMap>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QTcpSocket *socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1",5001);
	socket->waitForConnected();
	QByteArray packet;
	packet.append((char)0xAA);
	QVariantMap map;
	map["key"] = "testkey";
	map["value"] = "testvalue";
	QByteArray mappacked = CBOR::pack(map);

	packet.append((unsigned char)(mappacked.size() << 8));
	packet.append((unsigned char)(mappacked.size()));
	packet.append(mappacked);
	packet.append((char)0x0);
	packet.append((char)0x0);
	socket->write(packet);
	socket->waitForBytesWritten();
}

MainWindow::~MainWindow()
{
	delete ui;
}
