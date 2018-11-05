#include "loaddata.h"
#include "ui_loaddata.h"
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QWheelEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "personinfo.h"

loadData::loadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadData)
{
    ui->setupUi(this);

    connect(ui->vb,SIGNAL(valueChanged(int)),this,SLOT(slot_ScroolWidget(int)));

    //设置窗口尺寸
    QDesktopWidget *d=QApplication::desktop();
    width = 1380;
    height = d->height() * 0.8;
    this->setMinimumSize(width,height);
    this->setMaximumSize(width,height);

    //设置滚动条位置
    ui->vb->setMinimumHeight(height);
    ui->vb->move(width-18,0);

    //读取样式文件
    QFile file(":/style/qss/loaddata.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();

    setWindowIcon(QIcon(":/img/images/icon.png"));

    //创建图
    adj=new AdjList;
    CreateGraph(adj);

    //鼠标样式
    QCursor cursor;
    QPixmap pixmap(":/bg/images/cusor.png");
    cursor = QCursor(pixmap,-1,-1);

    setCursor(cursor);
}

loadData::~loadData()
{
    delete ui;
    destroyGraph(adj);
}

void loadData::paintEvent(QPaintEvent *event)
{
    int currentY = ui->vb->value();                         //获得滑块所在位置
    int i;                                                  //循环变量

    int arrowLenth = 15;                                    //箭头单边长度
    float arc = 0.5;                                        //箭头与线段角度
    float ax  = 0.0;                                        //箭头坐标
    float ay = 0.0;
    float ax2 = 0.0;
    float ay2 = 0.0;

    float fontx = 0.0;                                      //人物关系文字显示坐标X
    float fonty = 0.0;                                      //人物关系文字显示坐标Y

    //开始绘图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":img/images/tiltere.png");
    painter.drawPixmap(0,-currentY,pix.width(),pix.height(),pix);

    int n=adj->VexNum;                                      //顶点个数，后面要遍历每一个点点
    EdgeNode *q=NULL;
    Relative *rlt=NULL;
    int x,y;                                                //顶点坐标

    //线段的起点 终点
    int drawLinex = 0;
    int drawLiney = 0;
    int drawLinex2 = 0;
    int drawLiney2 = 0;

    //坐标修正
    int cx = 0;
    int cy = 0;

    QString personPic = ":img/images/per1.png";             //人物头像类型

    scrollMaxNum = adj->vertex[0].y * 10 + 1280;            //初始话滑动条最大范围

    for( i = 1;i<=n;i++)
    {
         pix.load(personPic);
         x =adj->vertex[i].x*20 + 40;
         y =  adj->vertex[i].y*20-currentY + 154;

         if(adj->vertex[i].data.compare("")!=0)             //名字不能为空
            painter.drawPixmap(x,y- 20,pix.width(),pix.height(),pix);
         rlt = adj->vertex[i].rlt;

          //链接关系
         while(rlt->next!=NULL)
         {
             rlt = rlt->next;
           {
                //坐标初始化
               drawLinex = adj->vertex[i].x*20 ;
               drawLiney = adj->vertex[i].y*20-currentY + 154;

               drawLinex2 = adj->vertex[rlt->id].x*20+ 40;
               drawLiney2 = adj->vertex[rlt->id].y*20-currentY + 154;

               painter.drawLine(x,y,drawLinex2,drawLiney2);

                //绘制箭头
                //计算箭头坐标
                ax = drawLinex2 - arrowLenth* cos(atan2((drawLiney2 - y) , (drawLinex2 - x)) - arc);
                ay = drawLiney2 - arrowLenth* sin(atan2((drawLiney2 - y) , (drawLinex2 - x)) - arc);
                ax2 = drawLinex2 - arrowLenth* sin(atan2((drawLinex2 - x) , (drawLiney2 - y)) - arc);
                ay2 = drawLiney2 - arrowLenth* cos(atan2((drawLinex2 - x) , (drawLiney2 - y)) - arc);

                //显示关系
                painter.setPen(QPen(QColor(255, 0, 0), 2));
                painter.drawText(QRectF((x+drawLinex2)/2.0,(y+drawLiney2)/2.0,40,40),Qt::AlignCenter,rlt->realtive);

                painter.setPen(QColor(0, 160, 230));
                painter.drawLine(ax,ay,drawLinex2,drawLiney2);

                painter.setPen(QPen(QColor(0, 160, 230), 2));
                painter.drawLine(ax2,ay2,drawLinex2,drawLiney2);

                painter.setPen(QColor(255, 160, 90));
                painter.drawLine(drawLinex2,drawLiney2,ax2,ay2);

           }
         }

    //设置文字样式
    QFont font;
    painter.setFont(font);
    //设置图片文字说明
    painter.setPen(QColor(0, 0, 0));
    painter.drawText(QRectF(x-10,y+20,70,70),Qt::AlignCenter,adj->vertex[i].data);
    painter.setPen(QColor(255, 160, 90));
    }
}

int loadData::readFile(QString filename)
{
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        msg("Open failed.");

    QTextStream txtInput(&f);
    QString lineStr;
    QString flagStr;                                    //标识名称  name id x y
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();

        lineStr = lineStr.simplified();                 //去掉两端的空白字符用当个空格代替
        lineStr = lineStr.trimmed();                    //去掉两端空白字符

        if(!lineStr.isEmpty() && lineStr.size()>0  )
            if(readFileImpl(lineStr)==-1)
                return -1;                              //出错
    }
    f.close();
    return 1;
}
int loadData::readFileImpl(QString str)
{
    QString lineStr;
    QString flagStr;                                    //标识名称  name id x y

    flagStr = str.mid(0,str.indexOf('='));
    lineStr = str.mid(str.indexOf('=')+1);              //mid从a位置到末尾   mid(a,b)
    qDebug() << flagStr<<"="<<lineStr << endl;
    return 1;
}
void loadData::slot_ScroolWidget(int value)
{
    double p=static_cast<double>(value)/static_cast<double>(ui->vb->maximum());
    ui->vb->setMaximum(scrollMaxNum);
    ui->vb->move(width-18,0);
}
void loadData::wheelEvent(QWheelEvent *event)
{
    int changpos = 80;//滑块活动距离
    int para=event->angleDelta().y();               //获得鼠标滚轮的滚动距离para，para<0向下滚动，>0向上滚动
    if (para<0)
    {
        //向下滚动，设定鼠标滚轮每滚动一个单位，滑块就移动20个单位
        //加入此判断的理由是，若当时滑块处于90的位置上，一旦继续下滑20个单位，就会超过最大范围100，show界面就会移动超出范围。
        if (ui->vb->value()+changpos<=scrollMaxNum)
        {
            //发射verticalScrollBar的信号valueChange（value+20），连接到了我们之前写的slot_ScrollWidget(int)槽上
            emit ui->vb->valueChanged(ui->vb->value()+changpos);//verticalScrollBar的信号valueChange（value+20）;
             ui->vb->setSliderPosition(ui->vb->value()+changpos);
        }else
        {
            emit ui->vb->valueChanged(ui->vb->maximum());
            ui->vb->setSliderPosition(ui->vb->maximum());
        }
    }
    else
    {
        //向上滚动
        if (ui->vb->value()-changpos>=0)
        {
            emit ui->vb->valueChanged(ui->vb->value()-changpos);
            ui->vb->setSliderPosition(ui->vb->value()-changpos);
        }
        else
        {
            emit ui->vb->valueChanged(ui->vb->minimum());
            ui->vb->setSliderPosition(ui->vb->minimum());
        }
    }
    update();
}
 void loadData::mouseMoveEvent(QMouseEvent *event)
 {
    int x = event->pos().x();
    int y = event->pos().y();
    str =str.append("x=").append(x).append(" y=").append(y);
 }

void loadData::mousePressEvent(QMouseEvent *event)
{
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    update();
}
