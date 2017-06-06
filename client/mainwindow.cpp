#include "mainwindow.h"
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::LocalHost, 9999);
    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onConnected()
{
    qDebug() << __FUNCTION__;
    QString message("message from client");
    if (socket->isWritable())
    {
        socket->write(message.toUtf8());
        socket->waitForBytesWritten();
    }
}

void MainWindow::onReadyRead()
{
    qDebug() << __FUNCTION__;
    auto data = socket->readAll();
    QString message(data);
    qDebug() << message;
}
