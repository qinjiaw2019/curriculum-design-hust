#include "widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "loading.h"
#include "iostream"
#include "graph.h"



using namespace  std ;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    w.show();

    QFile file(":/style/qss/mainwidget.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    w.setStyleSheet(stylesheet);
    file.close();

    return a.exec();
}
