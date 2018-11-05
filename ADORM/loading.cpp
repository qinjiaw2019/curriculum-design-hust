#include "loading.h"
#include "ui_loading.h"
#include <Windows.h>

#include "widget.h"

Loading::Loading(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    setMinimumSize(493,300);
    setMaximumSize(493,300);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setStyleSheet("border-image: url(:/bg/images/start.png);");//设置背景
    setWindowIcon(QIcon(":/img/images/icon.png"));
    setWindowTitle(QString::fromLocal8Bit("Loading... "));//设置标题
}

Loading::~Loading()
{
    delete ui;
}
