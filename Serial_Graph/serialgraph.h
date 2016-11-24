#ifndef SERIALGRAPH_H
#define SERIALGRAPH_H

#include <QMainWindow>
#include <QTimer>
#include <QtMath>

#include "serialtool.h"

#define MAX_DATA_LENGHT 512
#define coef 0.009490966

#define STOPPED 0
#define RUNNING 1

namespace Ui {
class SerialGraph;
}

class SerialGraph : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialGraph(QWidget *parent = 0);
    ~SerialGraph();

public slots:

    void readSerialData(char *, int);

    void refreshGraph();

private slots:

    void on_start_plot_button_clicked();

    void on_stop_plot_button_clicked();

    void on_s1_setup_Button_clicked();

    void on_s2_setup_Button_clicked();

    void on_clear_graph_button_clicked();

    void on_scale_graph_spinBox_editingFinished();

    void on_s1_visible_cb_stateChanged(int arg1);

    void on_s2_visible_cb_stateChanged(int arg1);

private:
    Ui::SerialGraph *ui;

    int status;

    SerialTool s1,s2;

    QVector<double> s1_data,s2_data,index;

    QTimer timer;
};

#endif // SERIALGRAPH_H
