#ifndef OBDSIMPROVIDER_H
#define OBDSIMPROVIDER_H

#include <QWidget>

namespace Ui {
class OBDSimProvider;
}
class QTcpSocket;
class OBDSimProvider : public QWidget
{
	Q_OBJECT

public:
	explicit OBDSimProvider(QWidget *parent = 0);
	~OBDSimProvider();
private slots:
	void connectButtonClicked();
private:
	Ui::OBDSimProvider *ui;
	QTcpSocket *socket;
};

#endif // OBDSIMPROVIDER_H
