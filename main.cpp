#include "mainwindow.h"
#include "viewerwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    viewerWidget viewer;
    viewer.setWindowTitle("simple texture mapping");
    viewer.show();

    return a.exec();
}
