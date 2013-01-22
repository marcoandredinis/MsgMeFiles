#include "cthread.h"

#include <QtNetwork>

CThread::CThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}



void CThread::run()
{
    client = new QTcpSocket();
    if (!client->setSocketDescriptor(socketDescriptor)) {
        emit error(client->error());
        return;
    }

    //qDebug() << tr("New conn");

    client->waitForReadyRead();
    in = new QTextStream(client);

    QString dataR = in->readAll();
    //QString ip = client->peerAddress().toString();
    //int sd = socketDescriptor;
    QString user = dataR.split("|").at(0);
    QString file = dataR.split("|").at(1);
    QString data = dataR.remove(0, user.length()+file.length()+2);

    //qDebug() << tr("User: ").append(user).append(" (").append(QString::number(sd)).append(") is sending you a file: ").append(file);
    //qDebug() << tr("Data: ").append(data);


    emit newData(user, file, data);

    //and, finally, close connection
    client->disconnectFromHost();
    client->close();
}
