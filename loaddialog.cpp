#include "loaddialog.h"
#include "ui_loaddialog.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
}

LoadDialog::~LoadDialog()
{
    delete ui;
}

void LoadDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}
