#include "formulator.h"
#include "graphwindow.h"
#include "ui_graphwindow.h"
#include "dialog.h"
using namespace Formulator;

QString formulaStr = "";
void GraphWindow::setFormulaString(QString fs){
    formulaStr = fs;
    GraphWindow::makePlot();
    std::cout << "Formula String New : " << fs.toStdString();
}

GraphWindow::GraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{

    ui->setupUi(this);

}

GraphWindow::~GraphWindow()
{

    delete ui;
}



void GraphWindow::makePlot(){
    Dialog objPF;
    QString strPF = objPF.getPlotFunction();
    if(formulaStr.toStdString().length() == NULL){
        this->close();
    }else{
        cout << "formula Str Global : " << formulaStr.toStdString() << endl;
        FormulaElement *fe = fe->parseFormula(formulaStr.toStdString());



        QVector<double> x(101), y(101); // initialize with entries 0..100
        for (int i=0; i<101; ++i)
        {
//          x[i] = i/50.0 - 1; // x goes from -1 to 1
            x[i] = i - 50;
    //      y[i] = x[i]*x[i]; // let's plot a quadratic function

          fe->setVariableValue("X" , x[i]);
          fe->setVariableValue("Y" , x[i]);
          fe->setVariableValue("Z" , x[i]);

          y[i] = fe->evaluate();
        }
        // create graph and assign data to it:
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("x");
        ui->customPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        ui->customPlot->xAxis->setRange(-50, 50);
        ui->customPlot->yAxis->setRange(-50, 50);
        ui->customPlot->replot();

    }
//    cout << "formula Str Global : " << formulaStr.toStdString() << endl;


//    FormulaElement *fe = fe->parseFormula(strPF.toStdString());

    // generate some data:

}
