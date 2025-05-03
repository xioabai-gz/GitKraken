#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClassGY39.h"
#include "ClassPR3000.h"
#include <QRandomGenerator>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("气象检测站");

    m_GY39Device = new ClassGY39();
    m_PR3000Device = new ClassPR3000();

    ui->labelAlarm->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete m_GY39Device;
    delete m_PR3000Device;
    delete ui;
}

void MainWindow::printLog(QString log1, QString log2)
{
    QString time = QDateTime::currentDateTime().time().toString();     //获取当前时间
    QString log = QString("%1  %2  %3").arg(time).arg(log1).arg(log2); //生成日志内容
    ui->textEditLog->append(log);                                      //输出日志
    ui->textEditLog->setReadOnly(true);
}

void MainWindow::on_pushButtonClearLog_clicked()
{
    ui->textEditLog->clear();
}

void MainWindow::alarm()
{
    int nAlarmFlag = 0; //标志位，不为零则需要报警
    QByteArray qbaLogText;

    if (m_GY39Device->getTemperature() > ui->hSliderTemperatureLimit->value())
    {
        nAlarmFlag = 1;
        qbaLogText.append("温度 ");
    }
    if (m_GY39Device->getIllumination() > ui->hSliderIlluminationLimit->value() * 1000)
    {
        nAlarmFlag = 1;
        qbaLogText.append("照度 ");
    }
    if (m_PR3000Device->getWindSpeed() > ui->hSliderWindSpeedLimit->value())
    {
        nAlarmFlag = 1;
        qbaLogText.append("风速 ");
    }

    if (nAlarmFlag == 1)
    {
        ui->labelAlarm->setVisible(true); //显示报警图片
        printLog(qbaLogText, "超过限值，正在报警");
    }
    else
    {
        ui->labelAlarm->setVisible(false);
    }
}

void MainWindow::updateUI()
{
    //更新标签文字
    ui->labelHumidity->setText(QString::number(m_GY39Device->getHumidity()));
    ui->labelTemperature->setText(QString::number(m_GY39Device->getTemperature()));
    ui->labelPressure->setText(QString::number(m_GY39Device->getPressure()));
    ui->labelIllumination->setText(QString::number(m_GY39Device->getIllumination() / 1000));
    ui->labelAltitude->setText(QString::number(m_GY39Device->getAltitude()));
    ui->labelWindSpeed->setText(QString::number(m_PR3000Device->getWindSpeed()));

    //更新进度条
    ui->progressBarHumidity->setValue(m_GY39Device->getHumidity());
    ui->progressBarTemperature->setValue(m_GY39Device->getTemperature());
    ui->progressBarPressure->setValue(m_GY39Device->getPressure());
    ui->progressBarIllumination->setValue(m_GY39Device->getIllumination() / 1000);
    ui->progressBarWindSpeed->setValue(m_PR3000Device->getWindSpeed());
    ui->progressBarAltitude->setValue(m_GY39Device->getAltitude());

    //更新风向图片
    QPixmap *pix;
    switch ((m_PR3000Device->getWindDirection() + 23) / 45)
    {
    case 0:
        pix = new QPixmap("./res/0.png");
        ui->labelWindDirection->setText("北");
        break;
    case 1:
        pix = new QPixmap("./res/45.png");
        ui->labelWindDirection->setText("东北");
        break;
    case 2:
        pix = new QPixmap("./res/90.png");
        ui->labelWindDirection->setText("东");
        break;
    case 3:
        pix = new QPixmap("./res/135.png");
        ui->labelWindDirection->setText("东南");
        break;
    case 4:
        pix = new QPixmap("./res/180.png");
        ui->labelWindDirection->setText("南");
        break;
    case 5:
        pix = new QPixmap("./res/225.png");
        ui->labelWindDirection->setText("西南");
        break;
    case 6:
        pix = new QPixmap("./res/270.png");
        ui->labelWindDirection->setText("西");
        break;
    case 7:
        pix = new QPixmap("./res/315.png");
        ui->labelWindDirection->setText("西北");
        break;
    }
    ui->labelWindDirectionIcon->setPixmap(*pix); //显示风向图片
}

void MainWindow::on_hSliderWindSpeedLimit_actionTriggered()
{
    ui->labelWindSpeedLimit->setText(QString::number(ui->hSliderWindSpeedLimit->value()));
}

//用来更新滑动条后面的参数
//使用滑动条自带的槽函数
void MainWindow::on_hSliderTemperatureLimit_actionTriggered()
{
    ui->labelTemperatureLimit->setText(QString::number(ui->hSliderTemperatureLimit->value()));
}

void MainWindow::on_hSliderIlluminationLimit_actionTriggered()
{
    ui->labelIlluminationLimit->setText(QString::number(ui->hSliderIlluminationLimit->value()));
}

void MainWindow::on_groupBoxAlarm_clicked(bool checked)
{
    if (checked == false)
    {
        ui->labelAlarm->setVisible(false);
    }
}

void MainWindow::on_pushButtonGetRandomData_clicked()
{
    int nSeed = QDateTime::currentDateTime().toSecsSinceEpoch();
    QRandomGenerator generator(nSeed);

    m_GY39Device->setIllumination(generator.bounded(0, 200000));
    m_GY39Device->setTemperature(generator.bounded(-20, 45));
    m_GY39Device->setPressure(generator.bounded(90000, 110000)/1000.0);
    m_GY39Device->setHumidity(generator.bounded(0, 100));
    m_GY39Device->setAltitude(generator.bounded(-200, 9000));

    m_PR3000Device->setWindSpeed(generator.bounded(0, 20));
    m_PR3000Device->setWindDirection(generator.bounded(0, 359));

    printLog("生成模拟数据", QString("温度%1℃，湿度%2%RH，海拔%3m，气压%4kPa，照度%5lux，风速%6m/s，风向%7°")
                                 .arg(m_GY39Device->getTemperature())
                                 .arg(m_GY39Device->getHumidity())
                                 .arg(m_GY39Device->getAltitude())
                                 .arg(m_GY39Device->getPressure())
                                 .arg(m_GY39Device->getIllumination())
                                 .arg(m_PR3000Device->getWindSpeed())
                                 .arg(m_PR3000Device->getWindDirection()));

    if (ui->groupBoxAlarm->isChecked())
    {
        alarm();
    }
    updateUI();
}


