#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "authorization.h"
#include "connectioncheck.h"
#include "client.h"
#include "generalpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void ConnectionCheckFunc();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Client *client_t;
};

#endif // MAINWINDOW_H
