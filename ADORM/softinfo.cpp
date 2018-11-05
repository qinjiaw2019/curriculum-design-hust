#include "softinfo.h"
#include "ui_softinfo.h"

#include <QFile>
#include <QTextStream>

SoftInfo::SoftInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoftInfo)
{
    ui->setupUi(this);

    //读取样式文件
    QFile file(":/style/qss/softInfo.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();
}

SoftInfo::~SoftInfo()
{
    delete ui;
}
