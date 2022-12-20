#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectDevice()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectDevice()));
    ui->chooseDeviceBox->insertItem(0, "Item 1");
    ui->chooseDeviceBox->insertItem(0, "Item 2");
    connect(ui->chooseDeviceBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeDevice(QString)));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(refreshDevices()));

    initMindwave();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMindwave()
{
    mindwave = new Mindwave();
    connect(mindwave, SIGNAL(connectStatus()), this, SLOT(changeStatus()));
}

void MainWindow::changeStatus()
{
    QString statusTxt="";
    statusTxt+="Connect status: ";
    if (mindwave->isConnected())
        statusTxt+="TRUE";
    else statusTxt+="FALSE";

    ui->connectStatus->setText(statusTxt);
    ui->debugView->append(statusTxt);
}
void MainWindow::connectDevice()
{
    qDebug() << "Connect pressed";
    mindwave->connectDevice();
}

void MainWindow::disconnectDevice()
{
    qDebug() << "Disconnect pressed";
    mindwave->disconnectDevice();
}

void MainWindow::changeDevice(const QString &text)
{
    qDebug() << "changed device" << text;
    ui->debugView->append(text);
}

void MainWindow::refreshDevices()
{
    qDebug() << "Refresh devices";
}
