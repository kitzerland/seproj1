#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = 0);
    void setFormula(QString);
    void fillXYZ(double, double, double);
    ~SaveDialog();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Ok_clicked();

private:
    Ui::SaveDialog *ui;
};

#endif // SAVEDIALOG_H
