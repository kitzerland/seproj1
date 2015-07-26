#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    void setFormulaString(QString);
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;

private slots:
    void makePlot();
};

#endif // GRAPHWINDOW_H
