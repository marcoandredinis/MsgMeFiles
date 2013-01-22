#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(tr("Drop a file to send"));
    setAcceptDrops(TRUE);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setID(QString qs, QString me){
    this->id = qs;
    this->setWindowTitle(qs);
    this->me = me;
}

void Dialog::on_btnSend_clicked()
{
    connectAndSend(ui->txtSend->toPlainText().toUtf8(), "mensagem");
}

void Dialog::connectAndSend(QByteArray data, QString file){
    conn = FALSE;
    ui->statusbar->showMessage(tr("Connecting..."));
    this->file = file;
    qApp->processEvents();
    this-> a = data;
    this->client = new QTcpSocket();
    client->abort();
    connect( client, SIGNAL(connected()), this, SLOT(sendData()));

    client->connectToHost(id, 8282);

    client->waitForConnected();

    if( client->state() == QAbstractSocket::UnconnectedState)
        errorSending();

}

void Dialog::sendData(){
    conn = TRUE;
    ui->statusbar->showMessage(tr("Sending data..."));
    qApp->processEvents();

    QString data;
    data.append(me).append("|").append(file).append("|").append(a);
    client->write(data.toUtf8());

    client->disconnectFromHost();
    client->close();
    ui->statusbar->showMessage(tr("Data sent. Drop another file!"));

}

void Dialog::errorSending(){
    if(conn == FALSE)
        ui->statusbar->showMessage(tr("Connection timeout, try again."));
}


void Dialog::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void Dialog::dropEvent(QDropEvent *event)
{
    QList<QUrl> droppedUrls = event->mimeData()->urls();
    int droppedUrlCnt = droppedUrls.size();
    for(int i = 0; i < droppedUrlCnt; i++) {
        QString localPath = droppedUrls[i].toLocalFile();
        QFileInfo fileInfo(localPath);
        if(fileInfo.isFile()) {
            QFile file(fileInfo.absoluteFilePath());
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream in(&file);
            connectAndSend(in.readAll().toUtf8(), fileInfo.baseName());
            //QMessageBox::information(this, tr("Dropped file"), fileInfo.absoluteFilePath());
        }
    }

    event->acceptProposedAction();
}
