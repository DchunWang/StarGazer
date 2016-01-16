#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QUdpSocket;
class Server;
#include <QTextCharFormat>

namespace Ui
{
    class Widget;
}

//定义一个枚举变量，用于区分不同的广播消息类型
enum MsgType{Msg, UsrEnter, UsrLeft, FileName, Refuse};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent, QString usrname);
    ~Widget();

protected:
    //处理新用户加入
    void usrEnter(QString usrname, QString ipaddr);
    //处理用户离开
    void usrLeft(QString usrname, QString time);
    //广播UDP消息
    void sndMsg(MsgType type, QString srvaddr = "");
    //获取用户名
    QString getUsr();
    //获取IP地址
    QString getIP();
    //获取聊天记录
    QString getMsg();

    void hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename);

    bool saveFile(const QString &filename);

    void closeEvent(QCloseEvent *);

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;
    QString uName;

    QString fileName;
    Server *srv;

    QColor color;

private slots:
    //接收UDP消息
    void processPendingDatagrams();

    void on_sendBtn_clicked();

    void getFileName(QString );
    void on_sendTBtn_clicked();
    void on_fontCbx_currentFontChanged(const QFont &f);
    void on_sizeCbx_currentIndexChanged(const QString &arg1);
    void on_boldTBtn_clicked();
    void on_boldTBtn_clicked(bool checked);
    void on_italicTBtn_clicked(bool checked);
    void on_underlineTBtn_clicked(bool checked);
    void on_colorTBtn_clicked();

    void curFmtChanged(const QTextCharFormat &fmt);
    void on_saveTBtn_clicked();
    void on_clearTBtn_clicked();
    void on_exitBtn_clicked();
};

#endif // WIDGET_H
