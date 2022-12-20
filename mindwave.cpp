#include "mindwave.h"
#include <QDebug>
#include <iostream>


Mindwave::Mindwave()
{
    qDebug() << "QDebug: Bluetooth constructor";
    qWarning() << "QWarning: Bluetooth constructor";
    fprintf(stderr, "Bluetooth c-tor\n");
    startDeviceDiscovery();
}
void Mindwave::startDeviceDiscovery()
{

}

void Mindwave::connectDevice()
{
    qDebug() << "Connect ";
    connected = true;
    emit connectStatus();

}

void Mindwave::disconnectDevice()
{
    qDebug() << "Disconnect: ";
    connected = false;
    emit connectStatus();
}
