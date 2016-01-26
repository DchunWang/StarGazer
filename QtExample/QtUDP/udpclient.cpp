#include "udpclient.h"

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


}

