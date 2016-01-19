#include "model.h"
#include <QApplication>
#include <QTableView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model w;
    QTableView view;
    view.setModel(&w);
    view.setWindowTitle(QObject::tr("Model"));
    view.resize(400, 400);
    view.show();

    return a.exec();
}
