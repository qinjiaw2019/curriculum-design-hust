#ifndef SOFTINFO_H
#define SOFTINFO_H

#include <QDialog>

namespace Ui {
class SoftInfo;
}

class SoftInfo : public QDialog
{
    Q_OBJECT

public:
    explicit SoftInfo(QWidget *parent = 0);
    ~SoftInfo();

private:
    Ui::SoftInfo *ui;
};

#endif // SOFTINFO_H
