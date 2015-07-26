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
    QString getPlotFunction();
    ~Dialog();

private slots:

    void on_pushButton_Plot_clicked();

    void on_pushButton_Clear2_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
