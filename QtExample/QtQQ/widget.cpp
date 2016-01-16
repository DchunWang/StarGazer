#include "widget.h"
#include "ui_widget.h"
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include "server.h"
#include "client.h"
#include <QFileDialog>
#include <QColorDialog>

Widget::Widget(QWidget *parent, QString usrname)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    uName = usrname;
    udpSocket = new QUdpSocket(this);
    port = 23232;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDategrams()));
    sndMsg(UsrEnter);

    srv = new Server(this);
    connect(srv, SIGNAL(sndFileName(QString)), this, SLOT(getFileName(QString)));

    connect(ui->msgTxtEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), this,
            SLOT(curFmtChanged(const QTextCharFormat)));
}

Widget::~Widget()
{

}

//发送各种UDP广播消息
void Widget::sndMsg(MsgType type, QString srvaddr)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString address = getIP();

    /*向要发送的数据中写入信息类型type、用户名（使用getUsr()函数获取),
     * 其中，type用于接收端区分信息类型，从而可以对不同类型的信息进行
     * 不同的处理
     */
    out << type << getUsr();

    switch(type)
    {
    case Msg:
        /* 对于普通的聊天消息Msg,首先判断发送的消息是否为空，如果为空，
         * 则进行警告；然后向发送的数据中写入本机的IP地址和用户输入的
         * 聊天信息文本
         */
        if(ui->msgTxtEdit->toPlainText() == "")
        {
            QMessageBox::warning(0, tr("警告"), tr("发送内容不能为空"),
                                 QMessageBox::Ok);
            return;
        }
        out << address << getMsg();
        ui->msgBrowser->verticalScrollBar()->setValue(
                    ui->msgBrowser->verticalScrollBar()->maximum());
        break;
    case UsrEnter:
        //对于新用户加入UsrEnter，只是简单地向数据中写入IP地址
        out << address;
        break;
    case UsrLeft:
        //对于用户离开UsrLeft,不需要进行其他操作
        break;
    case FileName:
    {
        //对于发送文件名FileName和拒绝接受文件Refuse，这里先不进行处理，稍后添加
        int row = ui->usrTblWidget->currentRow();
        QString clntaddr = ui->usrTblWidget->item(row, 1)->text();
        out << address << clntaddr << fileName;
        break;
    }
    case Refuse:
    {
        out << srvaddr;
        break;
    }
    }
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

//用于接受UDP广播发送来的消息
void Widget::processPendingDatagrams()
{
    //接受函数首先调用QUdpSocket类的成员函数hasPendingDatagrams()
    //以判断是否有可供读取的数据
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        /* 如果有可供读取的数据，则通过pendingDatagrams()函数获取当前可供读取的
         * UDP报文大小，并据此大小分配接受缓冲区datagram,最后使用QUdpSocket类的
         * 成员函数readDatagram()读取相应数据
         */
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int msgType;
        //首先获取信息类型，然后对不同信息类型进行不同的操作
        in >> msgType;
        QString usrName, ipAddr, msg;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(msgType)
        {
        case Msg:
            /* 如果是普通的聊天消息Msg,那么久获取其中的用户名、IP地址和内容信息等数据，
             * 然后将用户名和聊天内容显示在界面左上角的信息浏览器msgBrowser中，在显示
             * 聊天信息的同时还显示系统当前日期时间，系统当前日期时间利用
             * QDateTime::currentDateTime()
             * 获取
             */
            in >> usrName >> ipAddr >> msg;
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
            ui->msgBrowser->append("[" + usrName + "]" + time);
            ui->msgBrowser->append(msg);
            break;
        case UsrEnter:
            /* 如果是新用户加入UsrEnter，那么久获取其中的用户名和IP地址信息，
             * 然后使用usrEnter()函数进行新用户登录的处理
             */
            in >> usrName >>ipAddr;
            usrEnter(usrName, ipAddr);
            break;
        case UsrLeft:
            /* 如果是用户退出UsrLeft,那么获取其中的用户名，然后使用usrLeft()函数
             * 进行用户离开的处理
             */
            in >> usrName;
            usrLeft(usrName, time);
            break;
        case FileName:
        {
            in >> usrName >> ipAddr;
            QString clntAddr, fileName;
            in >> clntAddr >> fileName;
            hasPendingFile(usrName, ipAddr, clntAddr, fileName);
            break;
        }
        case Refuse:
        {

            in >> usrName;
            QString srvAddr;
            in >> srvAddr;
            QString ipAddr = getIP();
            if(ipAddr == srvAddr)
            {
                srv->refused();
            }
            break;
        }
        }
    }
}

//用来处理新用户的加入
void Widget::usrEnter(QString usrname, QString ipaddr)
{
    bool isEmpty = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *usr = new QTableWidgetItem(usrname);
        QTableWidgetItem *ip = new QTableWidgetItem(ipaddr);
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0, 0, usr);
        ui->usrTblWidget->setItem(0, 1, ip);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->msgBrowser->append(tr("%1 在线！").arg(usrname));
        ui->usrNumLbl->setText(tr("在线人数： %1").arg(ui->usrTblWidget->rowCount()));
        sndMsg(UsrEnter);
    }
}

//处理用户离开事件
void Widget::usrLeft(QString usrname, QString time)
{
    int rowNum = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).first()->row();
    ui->usrTblWidget->removeRow(rowNum);
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->msgBrowser->append(tr("%1 于%2离开!").arg(usrname).arg(time));
    ui->usrNumLbl->setText(tr("在线人数:%1").arg(ui->usrTblWidget->rowCount()));
}

//获取IP地址
QString Widget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, list)
    {
        if(addr.protocol() == QAbstractSocket::IPv4Protocol)
            return addr.toString();
    }
    return 0;
}

//获取用户名
QString Widget::getUsr()
{
    return uName;
}

//获取用户输入的聊天消息并进行一些设置
QString Widget::getMsg()
{
    QString msg = ui->msgTxtEdit->toHtml();
    ui->msgTxtEdit->clear();
    ui->msgTxtEdit->setFocus();
    return msg;
}

//void Widget::on_sendBtn_clicked()
//{
//    sndMsg(Msg);
//}

void Widget::on_sendBtn_clicked()
{
    sndMsg(Msg);
}

void Widget::getFileName(QString name)
{
    fileName = name;        //首先获取文件名，
    sndMsg(FileName);       //然后发送FileName类型的UDP广播
}




void Widget::on_sendTBtn_clicked()
{
    if(ui->usrTblWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("选择用户"), tr("请先选择目标用户！"), QMessageBox::Ok);
        return;
    }
    srv->show();
    srv->initSrv();
}

void Widget::hasPendingFile(QString usrname, QString srvaddr, QString clntaddr,
                            QString filename)
{
    QString ipAddr = getIP();
    if(ipAddr == clntaddr)
    {
        int btn = QMessageBox::information(this, tr("接收文件"),
                                           tr("来自%1(%2)的文件：%3,是否接收？")
                                           .arg(usrname)
                                           .arg(srvaddr)
                                           .arg(filename),
                                           QMessageBox::Yes, QMessageBox::No);
        if(btn == QMessageBox::Yes)
        {
            QString name = QFileDialog::getSaveFileName(0, tr("保存文件"), filename);
            if(!name.isEmpty())
            {
                Client *clnt = new Client(this);
                clnt->setFileName(name);
                clnt->setHostAddr(QHostAddress(srvaddr));
                clnt->show();
            }
        }
        else
        {
            sndMsg(Refuse, srvaddr);
        }
    }
}


void Widget::on_fontCbx_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setCurrentFont(f);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}


void Widget::on_boldTBtn_clicked(bool checked)
{
    if(checked)
        ui->msgTxtEdit->setFontWeight(QFont::Bold);
    else
        ui->msgTxtEdit->setFontWeight(QFont::Normal);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_italicTBtn_clicked(bool checked)
{
    ui->msgTxtEdit->setFontItalic(checked);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_underlineTBtn_clicked(bool checked)
{
    ui->msgTxtEdit->setFontUnderline(checked);
    ui->msgTxtEdit->setFocus();
}

void Widget::on_colorTBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if(color.isValid())
    {
        ui->msgTxtEdit->setTextColor(color);
        ui->msgTxtEdit->setFocus();
    }
}

void Widget::curFmtChanged(const QTextCharFormat &fmt)
{
    ui->fontCbx->setCurrentFont(fmt.font());
    //如果字体大小出错，则使用12
    if(fmt.fontPointSize() < 8)
    {
        ui->sizeCbx->setCurrentIndex(4);
    }
    else
    {
        ui->sizeCbx->setCurrentIndex(ui->sizeCbx->findText(QString::number(fmt.fontPointSize())));
    }
    ui->boldTBtn->setChecked(fmt.font().bold());
    ui->italicTBtn->setChecked(fmt.font().italic());
    ui->underlineTBtn->setChecked(fmt.font().underline());
    color = fmt.foreground().color();
}


void Widget::on_saveTBtn_clicked()
{
    if(ui->msgBrowser->document()->isEmpty())
    {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空， 无法保存！"), QMessageBox::Ok);
    }
    else
    {
        QString fname = QFileDialog::getSaveFileName(this, tr("保存聊天记录"),
                                                     tr(
                                                         "文本（*.txt);;所有文件(*.*)"));
        if(!fname.isEmpty())
            saveFile(fname);
    }
}

bool Widget::saveFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("保存文件"), tr("无法保存文件%1:\n%2")
                             .arg(filename)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->msgBrowser->toPlainText();
    return true;
}
void Widget::on_clearTBtn_clicked()
{
    ui->msgBrowser->clear();
}

void Widget::on_exitBtn_clicked()
{
    close();
}

void Widget::closeEvent(QCloseEvent *e)
{
    sndMsg(UsrLeft);
    QWidget::closeEvent(e);
}
