#include "dialog.h"
#include "ui_dialog.h"
#include "graphwindow.h"

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
    graph.exec();

}

void Dialog::on_pushButton_Clear2_clicked()
{
    ui->textEdit_Plot->setText("");
}

void Dialog::on_pushButton_Clear_clicked()
{
    ui->textEdit_Formula->setText("");
    ui->textEdit_FormulaName->setText("");
}
