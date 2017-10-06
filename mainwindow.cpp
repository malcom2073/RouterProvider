#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QByteArray>
#include "cbor.h"
#include <QVariant>
#include <QVariantMap>
#include "packetizer.h"
#include "gpssimprovider.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->connectPushButton,SIGNAL(clicked(bool)),this,SLOT(connectButtonClicked()));
	connect(ui->reqDataListButton,SIGNAL(clicked(bool)),this,SLOT(reqDataButtonClicked()));
	GPSSimProvider *provider = new GPSSimProvider();
	provider->show();

	ui->tableWidget->setColumnCount(3);
	ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
	ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Value"));
	ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Count"));


	ui->debugTableWidget->setColumnCount(2);
	ui->debugTableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Source"));
	ui->debugTableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Message"));
}
void MainWindow::connectButtonClicked()
{
	socket = new QTcpSocket(this);
	m_packetizer = new Packetizer(socket);
	connect(m_packetizer,SIGNAL(newPacket(QObject*,QByteArray)),this,SLOT(newPacket(QObject*,QByteArray)));
	socket->connectToHost("127.0.0.1",5001);
	socket->waitForConnected();
	connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadyRead()));

}

void MainWindow::reqDataButtonClicked()
{
	/*
	QVariantMap map;
	map["type"] = "data";
	QVariantMap datamap;
	datamap["domain"] = "Engine.Parameters";
	datamap["name"] = "RPM";
	datamap["value"] = "125";
	map["value"] = datamap;
	QByteArray mappacked = CBOR::pack(map);
	Packetizer linepacket;
	QByteArray packet = linepacket.generatePacket(mappacked);

	socket->write(packet);
	socket->waitForBytesWritten();
*/
	QVariantMap map;
	map["type"] = "debug";
	QVariantMap datamap;
	datamap["debugtype"] = "AllParams";
	map["value"] = datamap;
	QByteArray mappacked = CBOR::pack(map);
	QByteArray packet = m_packetizer->generatePacket(mappacked);

	socket->write(packet);
	socket->waitForBytesWritten();
}

MainWindow::~MainWindow()
{
	delete ui;
}
void MainWindow::socketReadyRead()
{
	m_packetizer->parseBuffer(socket->readAll());
}
void MainWindow::newPacket(QObject *ident,QByteArray packet)
{
	QVariant packetvariant = CBOR::unpack(packet.mid(0,packet.size()-1));
	QVariantMap result = packetvariant.toMap();
	qDebug() << "New Packet" << result;
	if (result.value("type") == "data")
	{
		QVariantMap dataresult = result.value("value").toMap();
		QList<QTableWidgetItem *> findlist = ui->tableWidget->findItems(dataresult.value("domain").toString() + "." + dataresult.value("name").toString(),Qt::MatchExactly);
		if (findlist.size() > 0)
		{
			int count = ui->tableWidget->item(findlist.at(0)->row(),2)->text().toInt();
			ui->tableWidget->item(findlist.at(0)->row(),2)->setText(QString::number(count+1));
			ui->tableWidget->item(findlist.at(0)->row(),1)->setText(dataresult.value("value").toString());
		}
		else
		{
			ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
			ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(dataresult.value("domain").toString() + "." + dataresult.value("name").toString()));
			ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(dataresult.value("value").toString()));
			ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem("1"));
		}

	}
	else if (result.value("type") == "debug")
	{
		result.value("value").toString();
		ui->debugTableWidget->setRowCount(ui->debugTableWidget->rowCount()+1);
		ui->debugTableWidget->setItem(ui->debugTableWidget->rowCount()-1,0,new QTableWidgetItem("Core"));
		ui->debugTableWidget->setItem(ui->debugTableWidget->rowCount()-1,1,new QTableWidgetItem(result.value("value").toString()));
	}
}
