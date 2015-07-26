#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setXYZ(double, double, double);
    ~MainWindow();

private slots:



    void on_pushButton_Graphs_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_Point_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Subtract_clicked();

    void on_pushButton_multiply_clicked();

    void on_pushButton_Devide_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_LBracket_clicked();

    void on_pushButton_RBracket_clicked();

    void on_pushButton_Pi_clicked();

    void on_pushButton_Log_clicked();

    void on_pushButton_Tan_clicked();

    void on_pushButton_X1_clicked();

    void on_pushButton_Power_clicked();

    void on_pushButton_Cos_clicked();

    void on_pushButton_X2_clicked();

    void on_pushButton_Squre_clicked();

    void on_pushButton_Sin_clicked();

    void on_pushButton_Tenp_clicked();

    void on_pushButton_Equals_clicked();

    void on_pushButton_History_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_X_clicked();

    void on_pushButton_Y_clicked();

    void on_pushButton_Z_clicked();

    void on_pushButton_ToH_clicked();

    void on_pushButton_Exp_clicked();

    void on_pushButton_Ans_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
