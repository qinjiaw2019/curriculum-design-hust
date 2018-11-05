#ifndef LOADDATA_H
#define LOADDATA_H

#include <QDialog>
#include <QScrollArea>
#include "graph.h"
namespace Ui {
class loadData;
}

class loadData : public QDialog
{
    Q_OBJECT

public:
    explicit loadData(QWidget *parent = 0);
    ~loadData();
    //读取数据文件
    //filename:读取的文件名
    //flag:文件格式数组
    //flagSize：flag数组大小
    int readFile(QString filename);
    int readFileImpl(QString str);//readFile执行事件

    AdjList *adj;//图

    int scrollMaxNum = 20;//设置滑块的最大滑动值

    //当前窗体尺寸设置
    int width = 1200;
    int height = 800;

    QString str;//辅助 变量 可去掉

    //鼠标单击是的位置坐标
    int mouseX = -1;
    int mouseY = -1;


private slots:
    void slot_ScroolWidget(int value);

private:
    Ui::loadData *ui;

    void paintEvent(QPaintEvent *);

    void wheelEvent(QWheelEvent *event);

    void mouseMoveEvent(QMouseEvent *);

    void mousePressEvent(QMouseEvent *event);
};

#endif // LOADDATA_H
