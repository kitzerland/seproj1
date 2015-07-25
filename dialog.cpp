#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Dialog::makePlot();
}

Dialog::~Dialog()
{

    delete ui;
}

void Dialog::makePlot(){
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica",9));
    // set locale to english, so we get english decimal separator:
    ui->customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // add confidence band graphs:
    ui->customPlot->addGraph();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    pen.setColor(QColor(180,180,180));
    ui->customPlot->graph(0)->setName("Confidence Band 68%");
    ui->customPlot->graph(0)->setPen(pen);
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
    ui->customPlot->addGraph();
    ui->customPlot->legend->removeItem(ui->customPlot->legend->itemCount()-1); // don't show two confidence band graphs in legend
    ui->customPlot->graph(1)->setPen(pen);
    ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1));
    // add theory curve graph:
    ui->customPlot->addGraph();
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    ui->customPlot->graph(2)->setPen(pen);
    ui->customPlot->graph(2)->setName("Theory Curve");
    // add data point graph:
    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    ui->customPlot->graph(3)->setErrorType(QCPGraph::etValue);
    ui->customPlot->graph(3)->setErrorPen(QPen(QColor(180,180,180)));
    ui->customPlot->graph(3)->setName("Measurement");

    // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
    QVector<double> x0(250), y0(250);
    QVector<double> yConfUpper(250), yConfLower(250);
    for (int i=0; i<250; ++i)
    {
      x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
      y0[i] = qSin(x0[i])/x0[i]; // sinc function
      yConfUpper[i] = y0[i]+0.15;
      yConfLower[i] = y0[i]-0.15;
      x0[i] *= 1000;
    }
    QVector<double> x1(50), y1(50), y1err(50);
    for (int i=0; i<50; ++i)
    {
      // generate a gaussian distributed random number:
      double tmp1 = rand()/(double)RAND_MAX;
      double tmp2 = rand()/(double)RAND_MAX;
      double r = qSqrt(-2*qLn(tmp1))*qCos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
      // set y1 to value of y0 plus a random gaussian pertubation:
      x1[i] = (i/50.0-0.5)*30+0.25;
      y1[i] = qSin(x1[i])/x1[i]+r*0.15;
      x1[i] *= 1000;
      y1err[i] = 0.15;
    }
    // pass data to graphs and let Qui->customPlot determine the axes ranges so the whole thing is visible:
    ui->customPlot->graph(0)->setData(x0, yConfUpper);
    ui->customPlot->graph(1)->setData(x0, yConfLower);
    ui->customPlot->graph(2)->setData(x0, y0);
    ui->customPlot->graph(3)->setDataValueError(x1, y1, y1err);
    ui->customPlot->graph(2)->rescaleAxes();
    ui->customPlot->graph(3)->rescaleAxes(true);
    // setup look of bottom tick labels:
    ui->customPlot->xAxis->setTickLabelRotation(30);
    ui->customPlot->xAxis->setAutoTickCount(9);
    ui->customPlot->xAxis->setNumberFormat("ebc");
    ui->customPlot->xAxis->setNumberPrecision(1);
    ui->customPlot->xAxis->moveRange(-10);
    // make top right axes clones of bottom left axes. Looks prettier:
    ui->customPlot->axisRect()->setupFullAxesBox();
}

void Dialog::on_pushButton_Plot_clicked()
{

}

void Dialog::on_pushButton_Clear2_clicked()
{
    ui->textEdit_Plot->setText("");
}

void Dialog::on_pushButton_Clear_clicked()
{
    ui->textEdit_PlotSave->setText("");
}
