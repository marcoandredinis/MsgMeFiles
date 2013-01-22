#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QList>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTcpServer>
#include <QNetworkInterface>
#include <server.h>

namespace Ui {
class FriendList;
}

class FriendList : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FriendList(QWidget *parent = 0);
    ~FriendList();

private slots:
    void on_lstList_doubleClicked(const QModelIndex &index);
    void addDataRcvd(QString user, QString file, QString data);
    void removeTab();
    void maximizeWindow();
    void toggleShowHide();
    void on_btnAddIP_clicked();

private:
    Ui::FriendList *ui;
    Server *server;
    QSystemTrayIcon *tray;
};

#endif // FRIENDLIST_H
