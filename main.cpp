#include <QCoreApplication>
#include <iostream>
#include "client.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    system("chcp 65001"); // с этой магической командой у меня под виндой таки
                          // показывает текст по-русски

    auto my_host = QHostAddress::LocalHost;
    auto my_port = 2323;


    Client chat_client;

    chat_client.connectToServer(my_host, my_port);



    // чуть более удобное чтение строк
    QTextStream QIn(stdin);
    QString line;

    while (true) {
        std::cout << "> ";
        // вот эта операцию чтения ввода блокирующая и пока нет ввода не сработает сигнал readyRead
        if (!QIn.readLineInto(&line) or line.startsWith("/qq")) break;


        chat_client.sendToServer(line);
        //chat_client.slotReadyRead();
    }
    return a.exec();
}
