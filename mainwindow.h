#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTcpSocket;
class Packetizer;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void connectButtonClicked();
	void reqDataButtonClicked();
	void socketReadyRead();
	void newPacket(QObject *ident,QByteArray packet);
private:
	Ui::MainWindow *ui;
	QTcpSocket *socket;
	Packetizer *m_packetizer;

};

#endif // MAINWINDOW_H
