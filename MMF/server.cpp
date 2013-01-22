#include "server.h"

#include <stdlib.h>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
}


void Server::incomingConnection(int socketDescriptor)
{

    CThread *handle = new CThread(socketDescriptor, this);
    connect(handle, SIGNAL(finished()), handle, SLOT(deleteLater()));
    //retransmit signal::slot
    connect(handle, SIGNAL(newData(QString,QString,QString)), this, SLOT(newDataS(QString,QString,QString)) );
    handle->start();
}

void Server::newDataS(QString user, QString file, QString data){
    emit newClient(user, file, data);
}

