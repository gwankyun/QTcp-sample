#include "mainwindow.h"
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::LocalHost, 9999))
    {
        qDebug() << server->errorString();
    }
    connect(server, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onNewConnection()
{
    qDebug() << __FUNCTION__;
    client = server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
}

void MainWindow::onReadyRead()
{
    qDebug() << __FUNCTION__;
    auto data = client->readAll();
    QString str(data);
    qDebug() << str;
    QString message("message from server");
    if (client->isWritable())
    {
        client->write(message.toUtf8());
        client->waitForBytesWritten();
    }
}
