#ifndef DIALOG_H
#define DIALOG_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtGui>

namespace Ui {
class Dialog;
}

class Dialog : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
    void setID(QString, QString);

private slots:
    void on_btnSend_clicked();
    void sendData();
    void errorSending();
    void connectAndSend(QByteArray, QString);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    Ui::Dialog *ui;

    QString id;
    QString me;
    QString file;
    bool conn;
    QTcpSocket *client;
    QByteArray a;
};

#endif // DIALOG_H
