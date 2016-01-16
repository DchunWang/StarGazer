#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>
class QTcpSocket;


namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    //获取发送端IP地址
    void setHostAddr(QHostAddress addr);
    //获取文件保存路径
    void setFileName(QString name);

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Client *ui;

    QTcpSocket *tClnt;          //客户端套接字类
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;
    qint64 totalBytes;          //总共需接受的字节数
    qint64 bytesReceived;       //已接收的字节数
    qint64 fileNameSize;
    QString fileName;
    QFile *locFile;             //待接受的文件
    QByteArray inBlock;         //缓存一次接受的数据
    QTime time;

private slots:
    //连接到服务器
    void newConn();
    //读取文件数据
    void readMsg();
    //显示错误信息
    void displayErr(QAbstractSocket::SocketError);
    void on_cCancleBtn_clicked();
    void on_cCloseBtn_clicked();
};

#endif // CLIENT_H
