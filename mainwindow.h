#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClassGY39.h"
#include "ClassPR3000.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    ClassGY39 *m_GY39Device;
    ClassPR3000 *m_PR3000Device;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void alarm();
    void updateUI(); //更新界面
    void printLog(QString log1, QString log2 = "");

private slots:
    void on_pushButtonGetRandomData_clicked();
    void on_pushButtonClearLog_clicked();

    void on_hSliderWindSpeedLimit_actionTriggered();
    void on_hSliderTemperatureLimit_actionTriggered();
    void on_hSliderIlluminationLimit_actionTriggered();

    void on_groupBoxAlarm_clicked(bool checked);
};

#endif // MAINWINDOW_H
