#include "mychild.h"
#include <QtWidgets>

MyChild::MyChild()
{
    //设置在子窗口关闭时销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    //初始isUntitled为true
    isUntitled = true;


}

//实现newFile()函数
void MyChild::newFile()
{
    //设置窗口编号，因为编号会一直保存，所以需要使用静态变量
    static int sequenceNumber = 1;
    //新建的文档默认未命名
    isUntitled = true;
    //将当前文件命名为”文档+编号“的形式，编号先使用再加1
    curFile = tr("文档 %1").arg(sequenceNumber++);
    //设置窗口标题，使用[*]可以在文档被更改后在文件名后显示”*“号
    setWindowTitle(curFile + "[*]" + tr("- Qt Word"));
    //文档更改时发送contentsChanged()信号，执行documentWasModified()槽函数
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

}

//实现槽函数documentWasModified()
void MyChild::documentWasModified()
{
    //根据文档的isModified()函数的返回值，判断编辑器内容是否被更改
    setWindowModified(document()->isModified());
}

//实现userFriendlyCurrentFile()函数
QString MyChild::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

//实现strippedName()函数
QString MyChild::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

//实现closeEvent()函数
void MyChild::closeEvent(QCloseEvent *event)
{
    event->accept();
}


