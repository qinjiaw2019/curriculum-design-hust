#ifndef PERSONCENTER_H
#define PERSONCENTER_H

#include <QDialog>
#include "graph.h"

namespace Ui {
class PersonCenter;
}

class PersonCenter : public QDialog
{
    Q_OBJECT

public:
    explicit PersonCenter(QWidget *parent = 0);
    ~PersonCenter();

    int scrollMaxNum = 20;//设置滑块的最大滑动值

    AdjList *adj;//图

    //当前窗体尺寸设置
    int width = 1200;
    int height = 800;
    //圆周率
    const double PI = 3.14159265358979323846 ;

    void getCenterPersonInfo(QString name);//获取与中心人物有关的人

    void onCreate();

    int index = 0; //列表id
    QString itemText;//列表选项
    int m = 0;//组数
    int start = 0;//翻页开始位置

private slots:
    void slot_ScroolWidget(int value);

    void on_list_currentTextChanged(const QString &arg1);

    void on_so_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);


private:
    Ui::PersonCenter *ui;

    void wheelEvent(QWheelEvent *event);

    void paintEvent(QPaintEvent *);
};

#endif // PERSONCENTER_H
