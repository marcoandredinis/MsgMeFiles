#ifndef CTHREAD_H
#define CTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMainWindow>
#include <QtGui>


class CThread : public QThread
{
    Q_OBJECT

public:
    CThread(int socketDescriptor, QObject *parent);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
    QTcpSocket *client;
    QTextStream *in;

signals:
    void newData(QString, QString, QString);
};

#endif
