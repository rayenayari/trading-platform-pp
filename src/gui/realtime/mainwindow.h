#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint( double x, double y);
    void clearData();
    void plot();



private slots:
    void on_btn_add_clicked();
    void realtimeDataSlot();
    void on_btn_clear_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x,qv_y;
    QTimer dataTimer;
};
#endif // MAINWINDOW_H
