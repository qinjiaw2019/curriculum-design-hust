#include "chart.h"
#include "ui_chart.h"

#include <QFile>
#include <QTextStream>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QPointF>

#include <QMessageBox>



QT_CHARTS_USE_NAMESPACE
Chart::Chart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);

    //读取样式文件
    QFile file(":/style/qss/chart.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();

    //创建图
    adj=new AdjList;
    CreateGraph(adj);

    //设置水平滚动条位置
    ui->srcollbar->setMinimumWidth(1200);
    ui->srcollbar->move(0,785);

    ui->soper->setText(QStringLiteral("贾敬"));//搜索框默认值
}

Chart::~Chart()
{
    delete ui;
}

void Chart::paintEvent(QPaintEvent *event)
{
    int i = 1;//循环变量

    //隐藏控件
    ui->hproessbar->hide();

    //相关度
    if(type==1)
    {
        //组件隐藏处理
        ui->sobtn->hide();
        ui->soper->hide();

        int currentX = ui->srcollbar->value();//获取滚动条的x的值
        EdgeNode * en;
        int minx = 50;//x轴单位刻度
        int miny = 10;

        int firstedgeCount = 0;

        //确定y轴最大高度
        int maxy = 0;
        //设置滚动条最大范围
        scrollMaxNum = adj->VexNum * 60+1000;

        childMax = adj->vertex[1].firstedge->data.toInt();
        //childMin = childMax;
        //获得临界点最大值
        for( i = 1;i<adj->VexNum;i++)
        {
            if(childMax<adj->vertex[i].firstedge->data.toInt())
                childMax=adj->vertex[i].firstedge->data.toInt();
        }

        //原点坐标
        int x0 = 80;
        int x,y;
        int y0 = 600;
        x = x0;
        y = y0;

        QPainter painter(this);
        //绘制坐标 x轴
        painter.drawLine(x0-currentX,y0,scrollMaxNum+20-currentX,y0);
        //绘制坐标 y轴
        painter.drawLine(x0-currentX,y0,x0-currentX,100);

        //图表符号说明
        painter.setBrush(QBrush(Qt::red));//设置画刷形式
        painter.drawRect(1000,80,50,30);
        painter.drawText(QRectF(1050,80,50,30),Qt::AlignCenter,QStringLiteral("最大值"));

        //设置图表标题
        painter.drawText(QRectF(400,100,300,20),Qt::AlignCenter,QStringLiteral("与该人物直接相关联人数"));

        //确定x轴刻度
        for( i = 1;i<=adj->VexNum;i++)
        {
            QString text=adj->vertex[i].data;
            int length=text.toLocal8Bit().length();
            x+=70;
            painter.drawLine(x-currentX,y0,x-currentX,y-5);//x轴刻度

            if(adj->vertex[i].firstedge->data.toInt()>maxy)
                maxy = adj->vertex[i].firstedge->data.toInt();//获得y轴高度

            //描点
            firstedgeCount = adj->vertex[i].firstedge->data.toInt()*30;

            //高亮显示最大值
            if(childMax==adj->vertex[i].firstedge->data.toInt())
                 painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
            else//回复原来颜色
                painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));//设置画刷形式

            painter.drawRect(x-currentX-70,y0-firstedgeCount,70,firstedgeCount);

            QString sp =QString::number(firstedgeCount/30,10);
            sp.append(firstedgeCount/30);
            //显示矩形的数量
            if(firstedgeCount/10!=0)
                painter.drawText(QRectF(x-currentX-58,y0-firstedgeCount-20,70,20),Qt::AlignCenter,sp);

            painter.drawText(QRectF(x-currentX-58,y0+10,70,20),Qt::AlignCenter, text);

        }

        x = x0;
        y = y0;
        //确定y轴刻度
        for( i = 1;i<=maxy+5;i++)
        {
            y-=30;
            painter.drawLine(x-currentX,y,x+5-currentX,y);
            painter.drawText(QRectF(x-currentX-20,y-10,20,20),Qt::AlignCenter, QString::number(i));

        }

        //绘制人物姓名数据
    }
    else if(type==2)
    {
        int flag = 1;//标识变量
        //圆心坐标
        int rx = 380;
        int ry = 360;
        //圆周坐标
        float x = rx;
        float y = ry;
        //半径
        int r = 200;

        //文字坐标
        float fontx = rx-10;
        float fonty = ry+40;

        EdgeNode *en=NULL;

        //开始绘图
        QPainter painter(this);
        QPixmap pix;

        QString personPic = ":img/images/per1.png";//人物头像类型

        //组件显示
        ui->sobtn->setVisible(true);
        ui->soper->setVisible(true);

        QString textname = ui->soper->text();//获得文本框内容
        textname = textname.simplified();
        textname = textname.trimmed();

        for(i=1;i<adj->VexNum;i++)
        {
            if(adj->vertex[i].data==textname)
            {
                en = adj->vertex[i].firstedge;
                break;
            }
        }

        if(en==NULL) return;
        pix.load(personPic);
        painter.drawPixmap(rx,ry,pix.width(),pix.height(),pix);
        painter.drawText(QRectF(fontx,fonty,70,70),Qt::AlignCenter,textname);//中心认为无名称
        int n = en->data.toInt();

        if(n>15 && n<=30)
            r *= 1.5;

        for(int j = 1;j<=n;j++)
        {
            en = en->next;
            //计算圆周坐标
             x = r*cos((-2*PI/n)*j)+rx;
             y = r*sin((-2*PI/n)*j)+ry;
             painter.drawPixmap(x,y,pix.width(),pix.height(),pix);

             fontx = x - 10;
             fonty = y + 40;

            for(int k = 1;k<=adj->VexNum;k++)
            {
                if(adj->vertex[k].id == en->data.toInt())
                {
                    painter.drawText(QRectF(fontx,fonty,70,70),Qt::AlignCenter,adj->vertex[k].data);
                }
            }

        }

    }
    else if(type==3)
    {
        //组件隐藏处理
        ui->sobtn->hide();
        ui->soper->hide();

        int currentX = ui->srcollbar->value();//获取滚动条的x的值
        EdgeNode * en;
        int minx = 50;//x轴单位刻度
        int miny = 10;

        int firstedgeCount = 0;

        //确定y轴最大高度
        int maxy = 0;
        //设置滚动条最大范围
        scrollMaxNum = adj->VexNum * 60;

        childMax = adj->vertex[1].firstedge->data.toInt();
        //childMin = childMax;
        //获得临界点最大值
        for( i = 1;i<adj->VexNum;i++)
        {
            if(childMax<adj->vertex[i].firstedge->data.toInt())
                childMax=adj->vertex[i].firstedge->data.toInt();
        }

        //原点坐标
        int x0 = 80;
        int x,y;
        int y0 = 600;
        x = x0;
        y = y0;

        double oldx = x0;//记录x,y的前一点的坐标
        double oldy = y0;
        QPainter painter(this);
        //绘制坐标 x轴
        painter.drawLine(x0-currentX,y0,scrollMaxNum-3500-currentX,y0);
        //绘制坐标 y轴
        painter.drawLine(x0-currentX,y0,x0-currentX,80);
        //说明文字
        painter.drawText(QRectF(x0+200,y0+20,200,100),Qt::AlignCenter, QStringLiteral("越靠近x轴越是主要人物"));

        //确定x轴刻度
        for( i = 1;i<=adj->VexNum;i++)
        {
            QString text=adj->vertex[i].data;
            int length=text.toLocal8Bit().length();
            x+=30;
            painter.drawLine(x-currentX,y0,x-currentX,y-5);

            if(adj->vertex[i].weight<600 )
            {

            painter.drawRect(x-currentX,y0-adj->vertex[i].weight,5,5);
            painter.drawLine(oldx,oldy,x-currentX,y0-adj->vertex[i].weight);
            painter.drawText(QRectF(x-currentX-20,y0-adj->vertex[i].weight-20,70,20),Qt::AlignCenter, text);

            if(adj->vertex[i].firstedge->data.toInt()>maxy)
                maxy = adj->vertex[i].firstedge->data.toInt();//获得y轴高度

            oldx = x-currentX;
            oldy = y0-adj->vertex[i].weight;
            }
        }

        x = x0;
        y = y0;
        //确定y轴刻度
        for( i = 1;i<=maxy+7;i++)
        {
            y-=30;
            painter.drawLine(x-currentX,y,x+5-currentX,y);
            painter.drawText(QRectF(x-currentX-20,y-10,20,20),Qt::AlignCenter, QString::number(i));
        }

    }
}

void Chart::slot_ScroolWidget(int value)
{
    ui->srcollbar->setMaximum(scrollMaxNum);
}
void Chart::wheelEvent(QWheelEvent *event)
{
    ui->srcollbar->setRange(0,scrollMaxNum);
    int changpos = 200;//滑块活动距离
    int para=event->angleDelta().y();//获得鼠标滚轮的滚动距离para，para<0向下滚动，>0向上滚动
    if (para<0)
    {
        //向下滚动，设定鼠标滚轮每滚动一个单位，滑块就移动20个单位
        //加入此判断的理由是，若当时滑块处于90的位置上，一旦继续下滑20个单位，就会超过最大范围100，show界面就会移动超出范围。
        if (ui->srcollbar->value()+changpos<=scrollMaxNum)
        {
            //发射verticalScrollBar的信号valueChange（value+20），连接到了我们之前写的slot_ScrollWidget(int)槽上
            emit ui->srcollbar->valueChanged(ui->srcollbar->value()+changpos);//verticalScrollBar的信号valueChange（value+20）;
             ui->srcollbar->setSliderPosition(ui->srcollbar->value()+changpos);
        }else
        {
            emit ui->srcollbar->valueChanged(ui->srcollbar->maximum());
            ui->srcollbar->setSliderPosition(ui->srcollbar->maximum());
        }
    }
    else
    {
        //向上滚动
        if (ui->srcollbar->value()-changpos>=0)
        {
            emit ui->srcollbar->valueChanged(ui->srcollbar->value()-changpos);
            ui->srcollbar->setSliderPosition(ui->srcollbar->value()-changpos);
        }
        else
        {
            emit ui->srcollbar->valueChanged(ui->srcollbar->minimum());
            ui->srcollbar->setSliderPosition(ui->srcollbar->minimum());
        }
    }
    update();//跟新窗口  重新绘图
}


void Chart::on_selectbtn_clicked()
{
    type = 1;
    update();
}

void Chart::on_selectbtn2_clicked()
{
    type = 2;
    update();
}

void Chart::on_sobtn_clicked()
{
    if(ui->soper->text().compare("")==0)
    {
        QMessageBox::information(NULL, QStringLiteral("提示："), QStringLiteral("请输入正确的值！"));
        ui->soper->setText(QStringLiteral("贾敬"));//搜索框默认值
    }
    update();
}
void Chart::mousePressEvent(QMouseEvent *event)
{

    mouseX = event->pos().x();
    mouseY = event->pos().y();
    update();
}

void Chart::on_selectbtn3_clicked()
{
    type = 3;
    update();
}
