#include "udpclient.h"
#include <QMessageBox>
#include <QHostAddress>

UdpClient::UdpClient(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    //设置窗体标题
    setWindowTitle(tr("UDP Client"));

    //初始化控件
    ReceiveTextEdit = new QTextEdit(this);
    CloseBtn = new QPushButton(tr("Close"), this);

    //设置布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ReceiveTextEdit);
    mainLayout->addWidget(CloseBtn);

    connect(CloseBtn,SIGNAL(clicked()), this, SLOT(CloseBtnClicked()));
    port = 5555;
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    bool result = udpSocket->bind(port);
    if(!result)
    {
        QMessageBox::information(this, tr("error"),tr("udp socket create error"));
        return;
    }

}


void UdpClient::CloseBtnClicked()
{
    close();
}

void UdpClient::dataReceived()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString msg = datagram.data();
        ReceiveTextEdit->insertPlainText(msg);
    }
}
UdpClient::~UdpClient()
{
}
