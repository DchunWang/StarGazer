#include <QCoreApplication>
#include <QFile>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //打开一个文件，在构造函数中指定文件名
    QFile file("textFile1.txt");
    //已只读方式打开文件
    if(file.open(QIODevice::ReadOnly))
    {
        char buffer[2048];
        //在QFile中可以使用从QIODevice中继承的readLine()函数读取文本文件中的一行
        qint64 lineLen = file.readLine(buffer, sizeof(buffer));

        //如果读取成功，则readLine()函数返回实际读取的字节数，如果读取失败，则返回-1
        if(lineLen != -1)
        {
            qDebug() << buffer;
        }
    }

    return a.exec();
}
