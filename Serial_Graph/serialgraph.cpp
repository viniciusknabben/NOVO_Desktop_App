#include "serialgraph.h"
#include "ui_serialgraph.h"

SerialGraph::SerialGraph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialGraph)
{
    ui->setupUi(this);

    status = STOPPED;

    // Configuração do layout do gráfico

    ui->customPlot->xAxis->setLabel("Pontos");
    ui->customPlot->yAxis->setLabel("VPK");

    index.resize(MAX_DATA_LENGHT);
    for(int x = 0; x<MAX_DATA_LENGHT;x++)
    {
        index[x] = x -255;
    }

    s1_data.resize(MAX_DATA_LENGHT);
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));

    s2_data.resize(MAX_DATA_LENGHT);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));

    ui->s1_visible_cb->setChecked(true);
    ui->s2_visible_cb->setChecked(true);

    ui->customPlot->xAxis->setRange(-256,256);
    ui->customPlot->yAxis->setRange(-350,350);

    // Serial config button icon
    QPixmap pix("/home/vinicius/Documents/work/desktop_app/Serial_Graph/options.jpeg");
    QIcon icon(pix);
    ui->s1_setup_Button->setIcon(icon);
    ui->s1_setup_Button->setIconSize(pix.size());
    ui->s2_setup_Button->setIcon(icon);
    ui->s2_setup_Button->setIconSize(pix.size());

    // Serial tool window name
    s1.setWindowTitle("Serial 1");
    s2.setWindowTitle("Serial 2");

    // Signals setup

    connect(&timer,SIGNAL(timeout()),this,SLOT(refreshGraph()));

    connect(&s1,SIGNAL(dataToRead(char *,int)),this,SLOT(readSerialData(char *,int)));
    connect(&s2,SIGNAL(dataToRead(char *,int)),this,SLOT(readSerialData(char *,int)));

}

SerialGraph::~SerialGraph()
{
    delete ui;
}

void SerialGraph::refreshGraph()
{
    ui->customPlot->replot();
}

void SerialGraph::readSerialData(char * data, int id)
{
    u_int16_t *tmp;
    tmp = (u_int16_t*)data;

    if(!status)
        return;

    switch (id)
    {
        case 0:
            for(int x=0;x<READ_BYTES/2;x++)
            {
                s1_data.removeFirst();
                s1_data.append((*tmp)*coef-311);
                tmp++;
            }
            ui->customPlot->graph(0)->setData(index,s1_data);
        break;

        case 1:
            for(int x=0;x<READ_BYTES/2;x++)
            {
                s2_data.removeFirst();
                s2_data.append((*tmp)*coef-311);
                tmp++;
            }
            ui->customPlot->graph(1)->setData(index,s2_data);
        break;

        default:
        break;
    }

    //ui->customPlot->replot();
}

void SerialGraph::on_start_plot_button_clicked()
{
    status = RUNNING;
    ui->status_Label->setText("Running");
    timer.start(1000);
    ui->start_plot_button->setEnabled(false);    
}

void SerialGraph::on_stop_plot_button_clicked()
{
    status = STOPPED;
    ui->status_Label->setText("Stopped");
    timer.stop();
    ui->start_plot_button->setEnabled(true);
}

void SerialGraph::on_s1_setup_Button_clicked()
{
    s1.show();
}

void SerialGraph::on_s2_setup_Button_clicked()
{
    s2.show();
}

void SerialGraph::on_clear_graph_button_clicked()
{
    ui->customPlot->graph(0)->clearData();
    ui->customPlot->graph(1)->clearData();
    ui->customPlot->replot();
    emit(on_stop_plot_button_clicked());
}


void SerialGraph::on_scale_graph_spinBox_editingFinished()
{
   ui->customPlot->xAxis->setRange(ui->scale_graph_spinBox->value()*-1,ui->scale_graph_spinBox->value());
   ui->customPlot->replot();
}

void SerialGraph::on_s1_visible_cb_stateChanged(int arg1)
{
    ui->customPlot->graph(0)->setVisible((arg1 == Qt::Checked));
    ui->customPlot->replot();
}

void SerialGraph::on_s2_visible_cb_stateChanged(int arg1)
{
    ui->customPlot->graph(1)->setVisible((arg1 == Qt::Checked));
    ui->customPlot->replot();
}
