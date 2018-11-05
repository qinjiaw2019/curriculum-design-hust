#include "statistics.h"
#include "ui_statistics.h"

#include <QFile>
#include <QTextStream>
#include <QStringListModel>
#include <qDebug>
#include <QMessageBox>
#include "chineseletterhelper.h"
Statistics::Statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);

    //读取样式文件
    QFile file(":/style/qss/statistics.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    setStyleSheet(stylesheet);
    file.close();

    //创建图
    adj=new AdjList;
    CreateGraph(adj);

    getMain();
}

Statistics::~Statistics()
{
    delete ui;
}

int Statistics::getMain()
{
    int i;


        QStringList list;

        double *arr = new double[adj->VexNum];
        for(i=1;i<=adj->VexNum;i++)
        {
            arr[i] = adj->vertex[i].weight;
        }

        quickSort(arr,0,adj->VexNum-1);

        for(i=1;i<=100;i++)
        {
            for(int j = 1;j<=adj->VexNum;j++)
            {
                if(arr[adj->VexNum-i]==adj->vertex[j].weight && adj->vertex[j].data!="")
                {
                    list<<QString(adj->vertex[j].data);
                }

            }
        }
         QStringListModel *model = new QStringListModel(list);
          ui->listView->setModel(model);

          ui->amount->setText(ui->amount->text().append(QString::number(adj->VexNum)));
          ui->per1->setText(list.at(0)+" ( "+ChineseLetterHelper::GetPinyins(list.at(0))+" )");
          ui->per2->setText(list.at(1)+" ( "+ChineseLetterHelper::GetPinyins(list.at(1))+" )");
          ui->per3->setText(list.at(2)+" ( "+ChineseLetterHelper::GetPinyins(list.at(2))+" )");
          ui->per4->setText(list.at(3)+" ( "+ChineseLetterHelper::GetPinyins(list.at(3))+" )");
          ui->per5->setText(list.at(4)+" ( "+ChineseLetterHelper::GetPinyins(list.at(4))+" )");
          ui->per6->setText(list.at(5)+" ( "+ChineseLetterHelper::GetPinyins(list.at(5))+" )");


    return 0;

}
void Statistics::quickSort(double *s, int l, int r)
{
    if (l< r)
    {
        int i = l, j = r;
        double x = s[l];
        while (i < j)
        {
            while(i < j && s[j]>= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i]< x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1); // 递归调用
        quickSort(s, i + 1, r);
    }
}


