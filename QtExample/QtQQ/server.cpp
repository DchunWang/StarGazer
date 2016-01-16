#include "server.h"
#include "ui_server.h"
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    //将对话框大小固定为400*207
    setFixedSize(400, 207);
    tPort = 5555;
    tSrv = new QTcpServer(this);
    connect(tSrv, SIGNAL(newConnection()), this, SLOT(sndMsg()));
    initSrv();
}

Server::~Server()
{
    delete ui;
}

void Server::initSrv()
{
    payloadSize = 64*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesTobeWrite = 0;
    ui->sStatusLbl->setText(tr("请选择要传送的文件"));
    ui->progressBar->reset();
    ui->sOpenBtn->setEnabled(true);
    ui->sSendBtn->setEnabled(false);
    tSrv->close();
}

//发送数据由sndMsg()槽函数完成
void Server::sndMsg()
{
    ui->sSendBtn->setEnabled(false);
    clntConn = tSrv->nextPendingConnection();
    connect(clntConn, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));
    ui->sStatusLbl->setText(tr("开始传送文件%1!").arg(theFileName));
    locFile = new QFile(fileName);
    //首先以只读方式打开选中的文件
    if(!locFile->open((QFile::ReadOnly)))
    {
        QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件%1:\n%2").arg(fileName)
                             .arg(locFile->errorString()));
        return ;
    }

    //通过QFile类的size()函数获取待发送文件的大小,并将该值暂存于totalBytes变量中
    totalBytes = locFile->size();

    //将发送缓存区outBlock封装在一个QDataStream变量中，这样做客方便地通过重载“<”
    //操作符填写文件头结构
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_7);

    //启动计时，time是QTime对象，用来统计传输所用的时间
    time.start();

    //这里通过QString类的right()函数去掉文件的路径部分，仅将文件部分保存在curFile变量中
    QString curFile = fileName.right(fileName.size()-fileName.lastIndexOf('/') - 1);

    //构造一个临时的文件头，将该值追加到totalBytes字段，从而完成实际需发送字节数的记录
    sendOut << qint64(0) << qint64(0) << curFile;
    totalBytes += outBlock.size();

    //将读写操作指向从头开始
    sendOut.device()->seek(0);

    //填写实际的总长度和文件长度
    sendOut << totalBytes << qint64((outBlock.size()-sizeof(qint64)*2));

    //将该文件头发出，同时修改待发送字节数bytesTobeWrite
    bytesTobeWrite = totalBytes - clntConn->write(outBlock);

    //清空发送缓存区以备下次使用
    outBlock.resize(0);
}

//更新进度条
void Server::updClntProgress(qint64 numBytes)
{
    //使得在传输大文件时使界面不会冻结
    qApp->processEvents();

    bytesWritten += (int)numBytes;
    if(bytesTobeWrite > 0)
    {
        outBlock = locFile->read(qMin(bytesTobeWrite, payloadSize));
        bytesTobeWrite -= (int)clntConn->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        locFile->close();
    }

    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);
    //通过time.elapsed()函数获取耗费的时间，进而在界面中显示传输速度等信息
    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->sStatusLbl->setText(tr("已发送%1MB(%2MB/s) \n 共%3MB 已用时：%4秒"
                               "\n 估计剩余时间：%5秒")
                               .arg(bytesWritten / (1024*1024))
                               .arg(speed * 1000 / (1024*1024), 0, 'f', 2)
                               .arg(totalBytes / (1024*1024))
                               .arg(useTime/1000, 0, 'f', 0)
                               .arg(totalBytes/speed/1000 - useTime/1000, 0, 'f',0));
    if(bytesWritten == totalBytes)
    {
        locFile->close();
        tSrv->close();
        ui->sStatusLbl->setText(tr("传送文件%1成功").arg(theFileName));
    }
}


void Server::on_sOpenBtn_clicked()
{
    /* 打击“打开...”按钮后弹出一个文件对话框，选择完要发送的文件后
     * 更新了文本标签sStatusLbl和按钮sSendBtn、sOpenBtn的状态
     */
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
        ui->sStatusLbl->setText(tr("要传送的文件为：%1").arg(theFileName));
        ui->sSendBtn->setEnabled(true);
        ui->sOpenBtn->setEnabled(false);
    }
}



void Server::on_sSendBtn_clicked()
{
    /* 在单击“发送”按钮后将服务器设置为监听状态，然后发送sndFileName()信号，
     * 在主界面类中将关联该信号并使用UDP广播将文件名发送给接收端
     */

    //开始监听
    if(!tSrv->listen(QHostAddress::Any,tPort))
    {
        qDebug() << tSrv->errorString();
        close();
        return ;
    }
    ui->sStatusLbl->setText(tr("等待对方接受......"));
    emit sndFileName(theFileName);
}



void Server::on_sCloseBtn_clicked()
{
    /* 单击“关闭”按钮后，首先关闭的是服务器，然后才关闭该对话框，
     * 系统关闭事件的处理函数也是通过调用“关闭”按钮单击信号槽实现的
     */
    if(tSrv->isListening())
    {
        tSrv->close();
        if(locFile->isOpen())
            locFile->close();
        clntConn->abort();
    }
    close();
}

void Server::closeEvent(QCloseEvent *)
{
    on_sCloseBtn_clicked();
}

//如果接收端拒绝接受该文件，则关闭服务器
void Server::refused()
{
    tSrv->close();
    ui->sStatusLbl->setText(tr("对方拒绝接受！"));
}
