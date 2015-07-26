#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "xyz.h"
#include "formulator.h"

double xxx = 0;double yyy = 0;double zzz=0;
bool xyzFlag = 0;

//create string named "value" for add formula as a string
QString value = "";
QString ans = "";

//create temp value for undo perpose ..
QString temp = "";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Open Graph Window
void MainWindow::on_pushButton_Graphs_clicked()
{
    Dialog graphWindow;
    graphWindow.setModal(true);
    graphWindow.exec();
}

void MainWindow::setXYZ(double a,double b, double c){
    xxx=a;
    yyy=b;
    zzz=c;
    xyzFlag = 1;

}



// Codes below help to add charactors to Qstring ..
void MainWindow::on_pushButton_0_clicked()
{
    value = value + "0";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Point_clicked()
{
    value = value + ".";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_1_clicked()
{
    value = value + "1";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_2_clicked()
{
    value = value + "2";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_3_clicked()
{
    value = value + "3";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_4_clicked()
{
    value = value + "4";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_5_clicked()
{
    value = value + "5";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_6_clicked()
{
    value = value + "6";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_7_clicked()
{
    value = value + "7";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_8_clicked()
{
    value = value + "8";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_9_clicked()
{
    value = value + "9";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Add_clicked()
{
    value = value + "+";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Subtract_clicked()
{
    value = value + "-";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_multiply_clicked()
{
    value = value + "x";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Devide_clicked()
{
    value = value + "÷";
    ui->lineEdit->setText(value);
}


void MainWindow::on_pushButton_Del_clicked()
{
    int l = value.length();
    value = value.left(l-1);
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_AC_clicked()
{
    temp = value;
    value = "";
    ui->lineEdit->setText(value);
    ui->lineEdit_2->setText(value);
}

void MainWindow::on_pushButton_LBracket_clicked()
{
    value = value + "(";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_RBracket_clicked()
{
    value = value + ")";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Pi_clicked()
{
    value = value + "π";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Log_clicked()
{
    value = value + "log(";
    ui->lineEdit->setText(value);
}


void MainWindow::on_pushButton_Tan_clicked()
{
    value = value + "tan(";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_X1_clicked()
{
    value = value + "!";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Power_clicked()
{
    value = value + "^";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Cos_clicked()
{
    value = value + "cos(";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_X2_clicked()
{
    value = value + "^2";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Squre_clicked()
{
    value = value + "√";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Sin_clicked()
{
    value = value + "sin(";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Tenp_clicked()
{
    value = value + "10^";
    ui->lineEdit->setText(value);
}

using namespace Formulator;
void MainWindow::on_pushButton_Equals_clicked()
{
    QString toAns = "";
    try{
        QString str = value;
        str.replace(QString("÷"), QString("/"));
        str.replace(QString("π"), QString("pi"));
        FormulaElement *fe = fe->parseFormula(str.toStdString());


        if(xxx > 0)fe->setVariableValue("X", xxx);
        if(yyy > 0)fe->setVariableValue("Y", yyy);
        if(zzz > 0)fe->setVariableValue("Z", zzz);

        if(xyzFlag){

            QString xString = QString::number(xxx);
            QString yString = QString::number(yyy);
            QString zString = QString::number(zzz);
            QString xyzInfo = "";
            if(xxx > 0 || yyy > 0 || zzz > 0)xyzInfo += "[ ";
            if(xxx > 0)xyzInfo += "X = " + xString + "";
            if(xxx > 0 && (yyy > 0 || zzz > 0))xyzInfo += ", ";
            if(yyy > 0)xyzInfo += "Y = " + yString + "";
            if(yyy > 0 && zzz > 0)xyzInfo += ", ";
            if(zzz > 0)xyzInfo += "Z = " + zString + "";
            if(xxx > 0 || yyy > 0 || zzz > 0)xyzInfo += "]";

            if(fe->isFullyGrounded()){
                ui->lineEdit_2->setText(value + xyzInfo);
                QString evaluatedAnswer = QString::number(fe->evaluate());
                ui->lineEdit->setText(evaluatedAnswer);
                toAns = evaluatedAnswer;
            }else{
                ui->lineEdit_2->setText(value);
                ui->lineEdit->setText(QString::fromStdString(fe->toString()));
                toAns = QString::fromStdString(fe->toString());
            }


        }else{
            ui->lineEdit_2->setText(value);
            ui->lineEdit->setText(QString::fromStdString(fe->toString()));
            toAns = QString::fromStdString(fe->toString());
        }
        ans = toAns;
    }catch(exception e){

    }

    value = "";
}

void MainWindow::on_pushButton_History_clicked()
{
    xyz openXyz;
    openXyz.setModal(true);
    openXyz.exec();

}

void MainWindow::on_pushButton_Up_clicked()
{
    xyzFlag = 0;
    QString mys = QString::number(xxx);
    ui->lineEdit->setText(mys);
}

void MainWindow::on_pushButton_X_clicked()
{
    value = value + "X";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Y_clicked()
{
    value = value + "Y";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Z_clicked()
{
    value = value + "Z";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_ToH_clicked()
{
    value = value + "%";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Exp_clicked()
{
    value = value + "exp(";
    ui->lineEdit->setText(value);
}

void MainWindow::on_pushButton_Ans_clicked()
{
    value = ans;
}
