#include "friendlist.h"
#include "dialog.h"
#include <QApplication>
#include <QTcpServer>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FriendList w;
    w.setGeometry(400, 100, 270, 410);
    w.setFixedSize(w.size());

    w.show();
    return a.exec();
}
