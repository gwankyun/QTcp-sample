#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void onNewConnection();
   void onReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *client;
};

#endif // MAINWINDOW_H
