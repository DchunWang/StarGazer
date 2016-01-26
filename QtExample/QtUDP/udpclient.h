#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class UdpClient : public QDialog
{
public:
    UdpClient(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~UdpClient();

private:
    QTextEdit *ReceiveTextEdit;
    QPushButton *CloseBtn;
    QVBoxLayout *mainLayout;

};

#endif // UDPCLIENT_H
