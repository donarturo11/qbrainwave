#ifndef MINDWAVE_H
#define MINDWAVE_H
#include <QWidget>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServer>


class Mindwave : public QObject
{
    Q_OBJECT
public:
    Mindwave();
    void startDeviceDiscovery();
    bool isConnected(){return connected; };
public slots:
    void connectDevice();
    void disconnectDevice();
signals:
    void connectStatus();
private:
    bool connected;
};

#endif // BLUETOOTHDEVICE_H
