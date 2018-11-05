#include "personinfo.h"
#include "ui_personinfo.h"
#include <QFile>
#include <QMessageBox>
#include <QFont>
#include <QFontDatabase>
#include "chineseletterhelper.h"
#include <QTextStream>

PersonInfo::PersonInfo(QWidget *parent):
    QDialog(parent),
    ui(new Ui::PersonInfo)
{
    ui->setupUi(this);

    //设置窗口大小
    setMinimumSize(1200,800);
    setMaximumSize(1200,800);

    //读取样式文件
    QFile file(":/style/qss/personinfo.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();

    //创建图
    adj=new AdjList;
    CreateGraph(adj);

    ui->search->setText(QStringLiteral("贾蓉"));

    //设置显示信息描述的文本框只读属性
    ui->pertext->setReadOnly(true);

    QString name = ui->search->text();//获取搜索框的值
    getPersonInfo(adj,name);

    findid = -1;

    //隐藏组件
    ui->selectper_31->hide();
    ui->tip->hide();
    ui->selectper_4->hide();
    ui->clearbtn->hide();
}

PersonInfo::~PersonInfo()
{
    delete ui;
}

void PersonInfo::getPersonInfo(AdjList *adj ,QString name)
{

    if(adj==NULL)
        return ;//如果图未创建 直接返回

    int j;
    //获取list列表
    for( j = 2;j<=adj->vertex[0].id;j++)
    {
        if(adj->vertex[j].data.compare("")!=0)                  //去掉无效的内容
        {
            ui->selectper->addItem(adj->vertex[j].data);

        }
    }
    // 设置默认值
    if(firstsearch)
    {
        ui->search->setText(QStringLiteral("贾蓉"));
        firstsearch = false;
    }



    //显示图片
    int flag = 1;
    QString picname=":/person/images/person/";
    QString s="";
    QString defaultpic = ":/person/images/person/";
    int i = 1;//保存匹配到的顶点位置
    defaultpic.append(DFAULT_PERSON_PICTURE);

    for(i = 1;i<=adj->VexNum && flag==1;i++)
    {
        QString pn = adj->vertex[i].data;

        //type==0 按名字查找
        if(pn.compare(name)==0 && type==0)
        {
            if(adj->vertex[i].pic.compare("")!=0)
                picname.append(adj->vertex[i].pic);
            //判断文件是否存在
            QFile pic(picname);
            if(pic.exists() && adj->vertex[i].pic.endsWith(".png"))//如果文件存在则使用
            {
                ui->showpic->setPixmap(QPixmap(picname));
                getInfo(adj,name);
                ui->name->setText(adj->vertex[i].data);
                ui->pingyin->setText(ChineseLetterHelper::GetPinyins(adj->vertex[i].data));
                ui->weight->setText(QString::number(adj->vertex[i].weight));
            }
            else
            {
                ui->showpic->setPixmap(QPixmap(":/person/images/person/default.jpg"));
                ui->pertext->setText("Null");
                ui->name->setText("NULL");
                ui->pingyin->setText("NULL");
                ui->weight->setText("0");
            }
            flag = 0;
        }

        //type==1 按名字查找
        else if(adj->vertex[i].id == ui->search->text().toInt() && type==1)
        {
            if(adj->vertex[i].pic.compare("")!=0)
                picname.append(adj->vertex[i].pic);
            //判断文件是否存在
            QFile pic2(picname);
            if(pic2.exists() && adj->vertex[i].pic.endsWith(".png"))//如果文件存在则使用
            {
                ui->showpic->setPixmap(QPixmap(picname));
                getInfo(adj,adj->vertex[i].data);
                ui->name->setText(adj->vertex[i].data);
                ui->pingyin->setText(ChineseLetterHelper::GetPinyins(adj->vertex[i].data));
                ui->weight->setText(QString::number(adj->vertex[i].weight));
            }
            else
            {
                ui->showpic->setPixmap(QPixmap(":/person/images/person/default.jpg"));
                ui->pertext->setText("Null");
                ui->pertext->setText("Null");
                ui->name->setText("NULL");
                ui->pingyin->setText("NULL");
                ui->weight->setText("0");
            }
            flag = 0;
        }
        //type==2 按名字查找
        else if(type==2)
        {
            int count;
            QByteArray str = ui->search->text().toLatin1();
            const char *s = str.data();
            while(*s && *s>='0' && *s<='9') s++;

            if(*s)
                return;
            else
                count = ui->search->text().toInt();

           // qDebug()<<"id="<<adj->vertex[j].firstedge->data<<" "<<"count="<<count<<endl;

            for(int j= 1;j<=adj->VexNum;j++)
            {
                if(adj->vertex[j].firstedge->data.toInt()==count &&adj->vertex[j].data!="")
                    ui->selectper_4->addItem(adj->vertex[j].data);

            }
            type = 0;
        }

    }
}
//获得信息
void PersonInfo::getInfo(AdjList *adj,QString name)
{
    int j=-1;
    for( j = 2;j<=adj->vertex[0].id;j++)
    {
        if(adj->vertex[j].data.compare(name)==0)                  //去掉无效的内容
        {
            break;
        }
    }
    if(j<0) return;

    QString filename=":/personInfo/data/description/";
    filename.append(QString::number(j-1)).append(".txt");
    //获得信息
    QFile info(filename);
    if(!info.open(QIODevice::ReadOnly | QIODevice::Text))
        msg("File Open fail!");
    QTextStream txtInput(&info);
    QString lineStr;
    QString flagStr;//标识名称  name id x y
    //初始化表头结点
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();

        lineStr = lineStr.simplified();//去掉两端的空白字符用当个空格代替
        lineStr = lineStr.trimmed();//去掉两端空白字符

        flagStr = lineStr.mid(0,lineStr.indexOf('='));
        lineStr = lineStr.mid(lineStr.indexOf('=')+1);//mid从a位置到末尾   mid(a,b)

        if(!lineStr.isEmpty() && lineStr.size()>0  )
        {
            ui->pertext->setText(lineStr);
        }
    }
    info.close();
    j = -1;

}

void PersonInfo::on_sobtn_clicked()
{
    QString text = ui->search->text();//获取搜索框的值
    findid = -1;
    text = text.simplified();
    text = text.trimmed();
    if(text.compare("")==0)//如果为空
    {
        QMessageBox::information(NULL, QStringLiteral("提示："), QStringLiteral("请输入正确的值！"));
    }
    else
    {
        getPersonInfo(adj,text);
        //更改窗口标题
        //setWindowTitle();
    }

    update();

}

void PersonInfo::on_selectper_currentIndexChanged(const QString &arg1)
{
    ui->search->setText(arg1) ;
}



void PersonInfo::on_selectper_2_currentIndexChanged(int index)
{
    type = index;
    if(type==0)
    {
        ui->selectper->setVisible(true);
        ui->search->setText("");
        ui->tip->hide();
        ui->selectper_4->hide();
        ui->clearbtn->hide();

    }
    else if(type==1)
    {
        ui->selectper->hide();
        ui->search->setText("0");
        ui->selectper->hide();
        ui->selectper_31->hide();
        ui->tip->hide();
        ui->selectper_4->hide();
        ui->clearbtn->hide();

    }
    else if(type==2)
    {
        ui->selectper_31->hide();
        ui->selectper->hide();
        ui->search->setText("");
        ui->tip->setVisible(true);
        ui->search->setText("2");
        ui->selectper_4->setVisible(true);
        ui->search->setText("0");
        ui->selectper_4->clear();
        ui->clearbtn->setVisible(true);

    }
    else if(type==3)
    {
        ui->selectper_31->setVisible(true);
        ui->selectper->hide();
        ui->search->setText("");
        ui->tip->hide();
        ui->search->setText("2");
        ui->selectper_4->setVisible(true);
        ui->search->setText("0");
        ui->selectper_4->clear();
        ui->clearbtn->setVisible(true);
    }
}



void PersonInfo::on_selectper_4_currentTextChanged(const QString &arg1)
{
    ui->search->setText(arg1);
}

void PersonInfo::on_clearbtn_clicked()
{
    ui->selectper_4->clear();
    type=2;
    update();
}
