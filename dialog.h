#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    QString getCheckedRadio();
    void setRadiosButtons(QStringList options);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
