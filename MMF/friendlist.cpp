#include "friendlist.h"
#include "ui_friendlist.h"
#include "dialog.h"

FriendList::FriendList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendList)
{

    QString myIP = tr("127.0.0.1");
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            myIP = ipAddressesList.at(i).toString();
            break;
        }
    }


    //QString myIP = tr("192.168.1.3");
    ui->setupUi(this);

    server = new Server(ui->tabRequest);
    if( !server->listen(QHostAddress(myIP), 8282) ){
        QMessageBox::critical(this, tr("Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server->errorString()));
        close();
        delete ui;
    }
    ui->statusBar->showMessage(tr("Your IP: ").append(myIP));
    connect(server, SIGNAL(newClient(QString,QString,QString)), this, SLOT(addDataRcvd(QString,QString,QString)));

    QList<QString>* list = new QList<QString>();
    list->push_back("192.168.1.2");
    list->push_back("192.168.1.3");
    list->push_back("192.168.1.4");
    list->push_back("192.168.1.5");
    list->push_back("192.168.1.6");
    /*list->push_back("192.168.1.7");
    list->push_back("192.168.1.8");
    list->push_back("192.168.1.9");
    list->push_back("192.168.1.10");*/

    int i = 0;

    QStandardItemModel *model = new QStandardItemModel(i, list->size());
    model->clear();

    foreach (QString elem, *list) {
        model->insertRow(i, new QStandardItem(elem));
        i++;
    }
    ui->lstList->setModel(model);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(tr(":/images/tray.ico")));
    tray->show();

    connect(tray, SIGNAL(messageClicked()), this, SLOT(maximizeWindow()));
    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(toggleShowHide()));


}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::maximizeWindow(){
    this->setVisible(TRUE);
    setWindowState(Qt::WindowMaximized);
}

void FriendList::toggleShowHide(){
    if( windowState().testFlag(Qt::WindowMaximized)){
        setWindowState(Qt::WindowMinimized);
    }else{
        setWindowState(Qt::WindowMaximized);
    }

    if( this->isVisible()){
        this->setVisible(FALSE);
    }else{
        this->setVisible(TRUE);
    }


}

void FriendList::on_lstList_doubleClicked(const QModelIndex &index)
{
    Dialog *d = new Dialog();
    d->setID(index.data().toString(), ui->txtNick->text());
    d->setGeometry(600, 200, 250, 170);
    d->show();
    d->setFixedSize(d->size());

}

void FriendList::addDataRcvd(QString user, QString file, QString data){
    QWidget *aux = new QWidget();

    QLabel *lblFile = new QLabel(aux);
    lblFile->setObjectName(QString::fromUtf8("lblFile"));
    lblFile->setGeometry(5, 5, 100, 23);
    lblFile->setText(tr("File: ").append(file));

    QTextEdit *txtData = new QTextEdit(aux);
    txtData->setObjectName(QString::fromUtf8("txtData"));
    txtData->setGeometry(5, 25, 232, 160);
    txtData->setText(data);
    txtData->setReadOnly(TRUE);

    QPushButton *btnRmv = new QPushButton(aux);
    btnRmv->setObjectName(QString::fromUtf8("btnRmv"));
    btnRmv->setGeometry(135, 5, 100, 23);
    btnRmv->setText(tr("Remove"));

    connect(btnRmv, SIGNAL(clicked()), this, SLOT(removeTab()));

    ui->tabRequest->addTab(aux, user);

    if( ui->tabRequest->count() == 1){
        ui->pngShare->setVisible(FALSE);
    }
    tray->showMessage(tr("New file"), tr("You've received a new file: ").append(file));

}

void FriendList::removeTab(){
    ui->tabRequest->removeTab(ui->tabRequest->currentIndex());
    if( ui->tabRequest->count() == 0){
        ui->pngShare->setVisible(TRUE);
    }
}

void FriendList::on_btnAddIP_clicked()
{
    //ui->lstList->model()->insertRow(0, new QStandardItem(ui->txtAddIP->text()));
    QStandardItemModel *model = (QStandardItemModel *) ui->lstList->model();
    model->insertRow(0, new QStandardItem(ui->txtAddIP->text()));

}
