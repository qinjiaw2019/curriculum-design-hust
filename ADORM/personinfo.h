#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QDialog>

#include "graph.h"
#include <QStringList>

namespace Ui {
class PersonInfo;
}

class PersonInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PersonInfo(QWidget *parent = 0);
    ~PersonInfo();

    //获得人物介绍信息
    void getPersonInfo(AdjList *adj,QString name);

    const QString DFAULT_PERSON_PICTURE = "default.png";//默认图片

    AdjList *adj;//图
    bool firstsearch = true;

    int type = 0;//查询条件标识
    QString realtive;//关系

    int findid;//查找是否成功 默认 -1  成功后为记录id

    void changText2Pinyin( );//将文本转换成拼音

    void getInfo(AdjList *adj,QString name);//获得信息



private slots:
    void on_sobtn_clicked();

    void on_selectper_currentIndexChanged(const QString &arg1);

    void on_selectper_2_currentIndexChanged(int index);

    void on_selectper_4_currentTextChanged(const QString &arg1);


    void on_clearbtn_clicked();

private:
    Ui::PersonInfo *ui;
};

#endif // PERSONINFO_H
