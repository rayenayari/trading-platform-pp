#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    //ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{   qv_x.append(x);
    qv_y.append(y);

}

void MainWindow::clearData()
{   qv_x.clear();
    qv_y.clear();


}

void MainWindow::plot()
{   ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->xAxis->setRangeUpper(*std::max_element(qv_x.begin(),qv_x.end())*1.25);
    ui->plot->yAxis->setRangeUpper(*std::max_element(qv_y.begin(),qv_y.end())*1.25);
    ui->plot->replot();
    ui->plot->update(); //updates data

}


void MainWindow::on_btn_add_clicked()
{   addPoint(ui->bx_x->value(),ui->bx_y->value());
    plot();

}
void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
      addPoint(key,sin(key));
      ui->plot->xAxis->setRangeLower(key-10);
      plot();
  }}
void MainWindow::on_btn_clear_clicked()
{

}
