#include "serialtool.h"
#include "ui_serialtool.h"

SerialTool::SerialTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialTool)
{
    ui->setupUi(this);

    ui->refresh_toolButton->setIcon(QIcon("/home/vinicius/Documents/work/desktop_app/Serial_Graph/refresh.jpeg"));
    ui->connect_Button->setEnabled(false);
    port_state = DISCONNECTED;

    id = id_count;
    id_count++;

    connect(&serial_port, SIGNAL(readyRead()), this, SLOT(readData()));

}

SerialTool::~SerialTool()
{
    delete ui;
}

// Combo Box Fill Up
void SerialTool::on_refresh_toolButton_clicked()
{
    listSerialDevices();
}

void SerialTool::listSerialDevices()
{
    ui->COM_comboBox->clear();
    serialPortInfoList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        ui->COM_comboBox->addItem(serialPortInfo.portName());
    }

    if(!ui->COM_comboBox->count())
    {
        ui->connect_Button->setEnabled(false);
        ui->port_Label->setText("Info: ");
        ui->br_Label->setText("Baud Rate: ");
        ui->busy_Label->setText("Ocupado: ");
        ui->status_Label->setText("Nenhum Dispositivo");
    }

    else
    {
        ui->status_Label->setText(QString::number(ui->COM_comboBox->count()) + " Dispositivos");
    }

}

void SerialTool::on_COM_comboBox_activated(const QString &arg1)
{
    int i =  ui->COM_comboBox->currentIndex();
    listSerialDevices();
    ui->COM_comboBox->setCurrentIndex(i);

    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        if(serialPortInfo.portName() == arg1)
        {
            serial_port.setPort(serialPortInfo);

            ui->port_Label->setText("Info: " + serialPortInfo.description());
            ui->br_Label->setText("Baud Rate: " + QString::number(serial_port.baudRate()));
            if(serialPortInfo.isBusy())
            {
                ui->busy_Label->setText("Ocupado: Sim");
                ui->connect_Button->setEnabled(false);
            }
            else
            {
                ui->busy_Label->setText("Ocupado: Não");
                ui->connect_Button->setEnabled(true);
            }
            return;
        }
    }
}

void SerialTool::on_connect_Button_clicked()
{
    switch(port_state)
    {
        case DISCONNECTED:
        if(serial_port.open(QIODevice::ReadWrite))
        {
            ui->status_Label->setText("Conectado!");
            ui->connect_Button->setText("Desconectar");
            ui->COM_comboBox->setEnabled(false);
            port_state = CONNECTED;
        }
        else
        {
            ui->status_Label->setText(serial_port.errorString());
            listSerialDevices();
        }
        return;

        case CONNECTED:
        serial_port.close();
        ui->status_Label->setText("Desconectado!");
        ui->connect_Button->setText("Conectar");
        ui->COM_comboBox->setEnabled(true);
        port_state = DISCONNECTED;
        return;
    }
}

void SerialTool::readData(void)
{
    static char data_buff[READ_BYTES];

    if(serial_port.bytesAvailable() >= READ_BYTES) // each point uint16_t so the buffer has 2 times POINTS
    {
        serial_port.read(data_buff,READ_BYTES);
        emit dataToRead(data_buff,id);
    }

}
