#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include "graph.h"

namespace Ui {
class Statistics;
}

class Statistics : public QDialog
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = 0);
    ~Statistics();

    int getMain();//主要人物
    AdjList *adj;//图
    int getWeightMax(AdjList *adj);//获得权值最大的id
    void Statistics::quickSort(double *s, int l, int r);//快速排序

private:
    Ui::Statistics *ui;
};

#endif // STATISTICS_H
