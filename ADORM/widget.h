#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "loaddata.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    //读取qss文件设置样式
    bool setStyles(QApplication* const app, QString const &skinFile);

    //设置窗体大小width*height
    int setWindowsSize(Widget  &w,int width,int height);

    //加载qss文件
    void setStyle(const QString &style);

private slots:
    void on_item1_clicked();

    void on_item2_clicked();

    void on_item3_clicked();

    void on_item6_clicked();

    void on_item5_clicked();

    void on_item7_clicked();

private:
    Ui::Widget *ui;

    loadData gpr;

};

#endif // WIDGET_H
