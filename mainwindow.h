#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mindwave.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void connectDevice();
    void disconnectDevice();
    void changeStatus();
    void changeDevice(const QString &text);
    void refreshDevices();

private:
    Ui::MainWindow *ui;
    Mindwave *mindwave;
    void initMindwave();

protected:

};
#endif // MAINWINDOW_H
