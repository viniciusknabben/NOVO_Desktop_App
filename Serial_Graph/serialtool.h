#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <QMainWindow>
#include <QIcon>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDataStream>
#include <QBuffer>

#define DISCONNECTED 0
#define CONNECTED    1

#define READ_BYTES 128 // Numero de bytes lidos por vez

namespace Ui {
class SerialTool;
}

class SerialTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialTool(QWidget *parent = 0);
    ~SerialTool();

    static int id_count;

signals:

    void dataToRead(char *,int);


private slots:

    void on_refresh_toolButton_clicked();

    void on_COM_comboBox_activated(const QString &arg1);

    void on_connect_Button_clicked();

    void readData();

private:
    Ui::SerialTool *ui;

    QList<QSerialPortInfo> serialPortInfoList;
    QSerialPort serial_port;
    int id;
    int port_state;
    void listSerialDevices();
};

#endif // SERIALTOOL_H
