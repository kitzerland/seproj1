#ifndef XYZ_H
#define XYZ_H

#include <QDialog>

namespace Ui {
class xyz;
}

class xyz : public QDialog
{
    Q_OBJECT

public:
    explicit xyz(QWidget *parent = 0);
    ~xyz();

private slots:
    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::xyz *ui;
};

#endif // XYZ_H
