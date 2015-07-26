#include "savedialog.h"
#include "ui_savedialog.h"
#include "fileio.h"

QString fStr = "";
double xsave = 0;
double ysave = 0;
double zsave = 0;

void SaveDialog::fillXYZ(double x, double y, double z){
    ui->lineEdit_X->setText(QString::number(x));
    ui->lineEdit_Y->setText(QString::number(y));
    ui->lineEdit_Z->setText(QString::number(z));
}

void SaveDialog::setFormula(QString fs){
    fStr = fs;
    ui->lineEdit_Formula->setText(fStr);
}

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}
using namespace FileIO;
void SaveDialog::on_pushButton_Ok_clicked()
{
    string writeString = "";

    writeString += ui->lineEdit_name->text().toStdString();
    writeString += ":";
    writeString += ui->lineEdit_Formula->text().toStdString();
    writeString += ":";
    writeString += ui->lineEdit_X->text().toStdString();
    writeString += ",";
    writeString += ui->lineEdit_Y->text().toStdString();
    writeString += ",";
    writeString += ui->lineEdit_Z->text().toStdString();
    writeString += ",";

    write(writeString);

    this->close();
}
