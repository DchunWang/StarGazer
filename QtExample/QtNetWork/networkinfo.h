#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QHostInfo>
#include <QNetworkInterface>

class NetWorkInfo : public QWidget
{
    Q_OBJECT

public:
    NetWorkInfo(QWidget *parent = 0);
    ~NetWorkInfo();

    void getHostInformation();
public slots:
    void slotDetail();

private:
    QLabel *hostLabel;
    QLineEdit *LineEditLocalHostName;
    QLabel *ipLabel;
    QLineEdit *LineEditAddress;
    QPushButton *detailBtn;
    QGridLayout *mainLayout;
};

#endif // NETWORKINFO_H
