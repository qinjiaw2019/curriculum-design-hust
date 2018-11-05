#ifndef CHART_H
#define CHART_H

#include <QDialog>
#include "graph.h"

//圆周率
const double PI = 3.14159265358979323846 ;

namespace Ui {
class Chart;
}

class Chart : public QDialog
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = 0);
    ~Chart();

    AdjList *adj;               //图

    int scrollMaxNum = 103*2;   //水平滚动条的最大滚动范围

    int childMax = 0;           //邻节点最大值
    int childSecMax = 0;        //邻节点第二大值

    int type=1;                 //图表编号

    //点击鼠标后鼠标的坐标
    int mouseX = -1;
    int mouseY = -1;

private slots:
    void slot_ScroolWidget(int value);

    void on_selectbtn_clicked();

    void on_selectbtn2_clicked();

    void on_sobtn_clicked();

    void on_selectbtn3_clicked();


private:
    Ui::Chart *ui;

    void paintEvent(QPaintEvent *);

    void wheelEvent(QWheelEvent *event);

    void mousePressEvent(QMouseEvent *);

};

#endif // CHART_H
