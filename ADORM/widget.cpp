#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QIcon>
#include <QScrollArea>
#include <QCursor>
#include "loaddata.h"

#include "personinfo.h"
#include "chart.h"
#include "search.h"
#include "statistics.h"
#include "softinfo.h"
#include "personcenter.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);




    ui->bg_label->setMinimumSize(1200,800);
    ui->bg_label->setMaximumSize(1200,800);


    setStyleSheet(":/style/qss/mainwidget.qss");
   //this->setStyleSheet("border-image: url(:/bg/images/bg.png);");//设置背景
    setWindowTitle(QString::fromLocal8Bit("《红楼梦》人物关系分析--数据结构课程设计"));
    setWindowIcon(QIcon(":/img/images/icon.png"));

    //鼠标样式
    QCursor cursor;
    QPixmap pixmap(":/bg/images/cusor.png");
    cursor = QCursor(pixmap,-1,-1);

    setCursor(cursor);


}

Widget::~Widget()
{
    delete ui;
}
int Widget::setWindowsSize(Widget &w,int width,int height)
{
    //w.resize(width,height);
    w.setMinimumSize(width,height);
    w.setMaximumSize(width,height);

    return 1;
}
void Widget::setStyle(const QString &style) {
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

void Widget::on_item1_clicked()
{
    //设置窗口大小
    gpr.setMinimumSize(1200,800);
    gpr.setWindowTitle(QString::fromLocal8Bit("《红楼梦》人物关系图"));

    //this->hide();
    gpr.show();
    gpr.exec();
}

void Widget::on_item2_clicked()
{
    PersonInfo perInfo;
    //设置窗口大小
    perInfo.setMinimumSize(1200,800);
    perInfo.setMaximumSize(1200,800);
    perInfo.setWindowTitle(QString::fromLocal8Bit("《红楼梦》---介绍"));

    //this->hide();
    perInfo.show();
    perInfo.exec();
}

void Widget::on_item3_clicked()
{
    Chart chart;
    //设置窗口大小
    chart.setMinimumSize(1200,800);
    chart.setMaximumSize(1200,800);
    chart.setWindowTitle(QString::fromLocal8Bit("《红楼梦》---图表"));

    //this->hide();
    chart.show();
    chart.exec();
}



void Widget::on_item6_clicked()
{
    Statistics statis;
    //设置窗口大小
    statis.setMinimumSize(1200,800);
    statis.setMaximumSize(1200,800);
    statis.setWindowTitle(QString::fromLocal8Bit("《红楼梦》---分析统计"));

    //this->hide();
    statis.show();
    statis.exec();
}

void Widget::on_item5_clicked()
{
    SoftInfo softInfo;
    //设置窗口大小
    softInfo.setMinimumSize(1200,800);
    softInfo.setMaximumSize(1200,800);
    softInfo.setWindowTitle(QString::fromLocal8Bit("《红楼梦》---软件信息"));

    //this->hide();
    softInfo.show();
    softInfo.exec();
}

void Widget::on_item7_clicked()
{
    PersonCenter percenter;
    //设置窗口大小
    percenter.setMinimumSize(1380,900);
    percenter.setMaximumSize(1380,900);
    percenter.setWindowTitle(QString::fromLocal8Bit("《红楼梦》---小团体分析"));

    percenter.show();
    percenter.exec();

}
