#ifndef GPSSIMPROVIDER_H
#define GPSSIMPROVIDER_H

#include <QWidget>

namespace Ui {
class GPSSimProvider;
}
class QTcpSocket;
class Packetizer;
class GPSSimProvider : public QWidget
{
	Q_OBJECT

public:
	explicit GPSSimProvider(QWidget *parent = 0);
	~GPSSimProvider();
private slots:
	void connectButtonClicked();
	void sendSingleClicked();
	void sendRepeatClicked();
private:
	Ui::GPSSimProvider *ui;
	QTcpSocket *socket;
	Packetizer *m_packetizer;
};

#endif // GPSSIMPROVIDER_H
