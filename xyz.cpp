#include "xyz.h"
#include "ui_xyz.h"
#include "mainwindow.h"

double a,b,c;
xyz::xyz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xyz)
{
    ui->setupUi(this);
}

xyz::~xyz()
{
    delete ui;
}

void xyz::on_pushButton_Ok_clicked()
{
    a = ui->lineEdit->text().toDouble();
    b = ui->lineEdit_2->text().toDouble();
    c = ui->lineEdit_3->text().toDouble();
    MainWindow obj;
    obj.setXYZ(a,b,c);
    this->close();
}

void xyz::on_pushButton_Cancel_clicked()
{
    this->close();
}
