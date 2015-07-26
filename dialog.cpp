#include "dialog.h"
#include "ui_dialog.h"
#include "graphwindow.h"
#include <iostream>
#include <string>

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



void Dialog::on_pushButton_Plot_clicked()
{
    GraphWindow graph;
    graph.setModal(true);

    graph.setFormulaString(ui->lineEdit_plot->text());
    graph.exec();

//    std::cout << "plain text @ plot : " << ui->lineEdit_plot->text().toStdString() << std::endl;
}

QString Dialog::getPlotFunction(){
    QString qs = ui->lineEdit_plot->text();
//    std::cout << "plain text : " << ui->lineEdit_plot->text().toStdString() << std::endl;
    return qs;
}

void Dialog::on_pushButton_Clear2_clicked()
{
    ui->lineEdit_plot->setText("");
}

void Dialog::on_pushButton_Clear_clicked()
{
    ui->textEdit_Formula->setText("");
    ui->textEdit_FormulaName->setText("");
}
