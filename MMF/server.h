#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QTabWidget>
#include <QMap>
#include <cthread.h>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

public slots:

private slots:
    void newDataS(QString user, QString file, QString data);

signals:
    void newClient(QString, QString, QString);
};

#endif
