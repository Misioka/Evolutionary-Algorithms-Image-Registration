#include "dialog.h"
#include "ui_dialog.h"
#include <QRadioButton>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setRadiosButtons(QStringList options) {
    QVBoxLayout *vbox = new QVBoxLayout;
    bool first = true;
    foreach(QString option, options) {
        QRadioButton *button = new QRadioButton(option);
        if (first) {
            button->setChecked(true);
            first = false;
        }
        vbox->addWidget(button);
    }
    ui->matVars->setLayout(vbox);
}

QString Dialog::getCheckedRadio() {
    QList<QRadioButton *> allButtons = ui->matVars->findChildren<QRadioButton *>();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        if (allButtons.at(i)->isChecked()) {
            return allButtons.at(i)->text();
        }
    }
    return QString("");
}
