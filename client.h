#pragma once
#include <QTcpSocket>
#include <QHostAddress>


class Client : public QObject
{
    Q_OBJECT

public:
    Client() : socket(new QTcpSocket) {};


    void connectToServer(const QHostAddress &host, int port);
    void sendToServer(QString message);
    void disconnectFromServer();

private:
    QTcpSocket* socket;

public slots:
    //incom
    void slotReadyRead();
};
