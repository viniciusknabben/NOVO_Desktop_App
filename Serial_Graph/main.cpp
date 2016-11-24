#include "serialgraph.h"
#include <QApplication>

int SerialTool::id_count = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialGraph w;
    w.show();

    return a.exec();
}
