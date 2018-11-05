#include "personcenter.h"
#include "ui_personcenter.h"
#include <QFile>
#include <QTextStream>
#include <QWheelEvent>
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
PersonCenter::PersonCenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonCenter)
{
    ui->setupUi(this);

    //读取样式文件
    QFile file(":/style/qss/personCenter.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();

    //创建图
    adj=new AdjList;
    CreateGraph(adj);

    //设置滚动条位置
    ui->vb->setMinimumHeight(900);
    ui->vb->move(1380-18,0);
}

PersonCenter::~PersonCenter()
{
    delete ui;
}
void PersonCenter::onCreate()
{
    getCenterPersonInfo("贾敬");
}

void PersonCenter::getCenterPersonInfo(QString name){

}
void PersonCenter::paintEvent(QPaintEvent *event)
{
    //圆心坐标
    int rx = 380;
    int ry = 360;
    //圆周坐标
    float x = rx;
    float y = ry;
    //半径
    int r = 200;

    int i = 0;//循环变量

    int interval = 0;//每组间隔距离
    int n = 0;//周围人物数

    //用于显示的数据
    QStringList list;
    QStringList sublist;

    EdgeNode *en = NULL;
    Relative *rlt = NULL;

    //清空list内容
    list.clear();
    sublist.clear();

    //按子代数查询
    if(index==0)
    {
        m = 0;//重新赋值
        start = 0;
        for(i = 1; i<=adj->VexNum;i++ )
        {
            if(adj->vertex[i].data == ui->name->text())//定位到目标人物
            {
                n = adj->vertex[i].firstedge->data.toInt();//得到周围人物数
                for(int j = 1;j<adj->VexNum;j++)
                {
                    if(index==0)//按子代数查询
                    {
                        if(adj->vertex[j].firstedge->data.toInt() == adj->vertex[i].firstedge->data.toInt())
                        {
                            list.append(adj->vertex[j].data);
                            m++;//得到组数
                        }
                    }
                }
            }
        }
    }

    int currentY = ui->vb->value();                         //获得滑块所在位置
    scrollMaxNum = 9000;//设置滑块的最大滑动值
    //初始化列表
    for(i = 1;i<adj->VexNum;i++)
    {
        if(adj->vertex[i].data!="")
            ui->list->addItem(adj->vertex[i].data);
    }
    //开始绘图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":img/images/per1.png");

    for(int j = 0;j<m;j++)
    {
        painter.drawPixmap(rx,interval+ry-currentY*10,pix.width(),pix.height(),pix);//中心人物
        painter.setPen(QPen(QColor(255, 0, 0), 2));
        painter.drawText(QRectF(rx-10,interval+ry-currentY*10+30,70,70),Qt::AlignCenter,list.at(j));//中心认为无名称
        painter.setPen(QPen(QColor(255, 0, 0), 2));
        sublist = getByNmame(adj,list.at(j));
         for(i = 0;i<n;i++)
         {
            //计算圆周坐标
             x = r*cos((-2*PI/n)*i)+rx;
             y = r*sin((-2*PI/n)*i)+ry;
             painter.drawPixmap(x,interval+y-currentY*10,pix.width(),pix.height(),pix);
             painter.drawText(QRectF(x-10,interval+y-currentY*10+30,70,70),Qt::AlignCenter,sublist.at(i));//中心认为无名称

             painter.setPen(QPen(QColor(203, 196, 152), 2));
             painter.drawLine(rx-2,interval+ry-currentY*10+40,x,interval+y-currentY*10+10);
             painter.setPen(QPen(QColor(255, 0, 0), 2));
         }

         painter.drawText(QRectF(1000,interval+y-currentY*10,70,70),Qt::AlignCenter,QStringLiteral("第")+QString::number(j+1)+QStringLiteral("组"));
         interval+=500;
    }

}

void PersonCenter::slot_ScroolWidget(int value)
{
  //  verticalScrollBar的信号valueChagned(int)发送来一个int参数
  //  该参数指明当前滑块所在的位置
  //  其中，滑块长度恒定为0-100，而该参数就是介于0-100之间
 //   double p=static_cast<double>(value)/static_cast<double>(ui->vb->maximum());
    ui->vb->setMaximum(scrollMaxNum*10+8000);
    ui->vb->move(width-18,0);
}
void PersonCenter::wheelEvent(QWheelEvent *event)
{
    ui->vb->setMaximum(scrollMaxNum*m+8000);

    int changpos = 30;//滑块活动距离
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

void PersonCenter::on_list_currentTextChanged(const QString &arg1)
{
    ui->name->setText(arg1);
}

void PersonCenter::on_so_clicked()
{
    update();
}

void PersonCenter::on_comboBox_currentIndexChanged(int index)
{
    this->index=index;
}

void PersonCenter::on_comboBox_currentTextChanged(const QString &arg1)
{
    itemText = arg1;
}

