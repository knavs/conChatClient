#include "client.h"
#include <iostream>

//Client::Client()
//{
//    // подключаем сигналы точно также, как на сервере
//    socket = new QTcpSocket();

//}

void Client::connectToServer(const QHostAddress &host, int port)
{
    socket->connectToHost(QHostAddress(host), port);
    // подключаем сигналы точно также, как на сервере
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    if (socket->waitForConnected()) {
        qDebug() << "[OK] Connected to " << host << ":" << port <<" as sd:" << socket->socketDescriptor();
        sendToServer("Hello");
        socket->waitForReadyRead();


    } else {
        qDebug() << "[FAIL] can't connect to chatServer";
    }
}

void Client::sendToServer(QString message)
{
    socket->write(message.toStdString().c_str());
    socket->flush();

    socket->waitForReadyRead(1000);
    //qDebug() << " Client::sendToServer: " << message;
}

void Client::disconnectFromServer()
{
    qDebug() << "Disconnected from server";
    socket->deleteLater();
}

void Client::slotReadyRead()
{
    QByteArray data = socket->readAll();
    std::cout << data.toStdString();
}
