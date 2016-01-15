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
//void MyChild::closeEvent(QCloseEvent *event)
//{
//    event->accept();
//}

//加载文件操作的代码
bool MyChild::loadFile(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        if(!QFile::exists(fileName))
            return false;

        //新建Qfile对象
        QFile file(fileName);

        //以只读方式打开文件，出错则提示，并返回false
        if(!file.open(QFile::ReadOnly))
            return false;

        QByteArray data = file.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);

        if(Qt::mightBeRichText(str))
        {
            this->setHtml(str);
        }
        else
        {
            str = QString::fromLocal8Bit(data);
            this->setPlainText(str);
        }

        //设置当前文件
        setCurrentFile(fileName);
        connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

        return true;
    }
    else
        return false;
}

void MyChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();

    //文件已经被保存过
    isUntitled = false;

    //文档没有被更改过
    document()->setModified(false);

    //窗口不显示被更改标识
    setWindowModified(false);

    //设置窗口标题
    setWindowTitle(userFriendlyCurrentFile() + "[*]");

}

bool MyChild::save()
{
    if(isUntitled)
        return saveAs();
    else
        return saveFile(curFile);
}

bool MyChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), curFile,
                       tr("HTML文档(*.htm *.html);;所有文件(*.*)"));

    //获取文件路径，如果为空，则返回false,否则保存文件
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MyChild::saveFile(QString &fileName)
{
    if(!(fileName.endsWith(".htm", Qt::CaseInsensitive) || fileName.endsWith(
             "html", Qt::CaseInsensitive)))
    {
        fileName += ".html";        //默认保存HTML文档
    }

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(this->document());
    if(success)
        setCurrentFile(fileName);
    return success;
}

bool MyChild::maybeSave()
{
    if(!document()->isModified())
        return true;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("MySeld Qt Word"), tr("文档 ‘%1’已被修改，保存吗？")
                               .arg(userFriendlyCurrentFile()),QMessageBox::Save |
                               QMessageBox::Discard | QMessageBox::Cancel);
    if(ret == QMessageBox::Save)
        return save();
    else if(ret == QMessageBox::Cancel)
        return false;
    return true;
}

void MyChild::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        event->accept();

    }
    else
    {
        event->ignore();
    }
}

void MyChild::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = this->textCursor();
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void MyChild::setAlign(int align)
{
    if(align == 1)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if(align == 2)
        this->setAlignment(Qt::AlignHCenter);
    else if(align == 3)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if(align == 4)
        this->setAlignment(Qt::AlignJustify);
}

void MyChild::setStyle(int style)
{
    QTextCursor cursor = this->textCursor();
    if(style != 0)
    {
        //QTextListFormat主要用于描述文本标号、编号格式
        QTextListFormat::Style stylename = QTextListFormat::ListDisc;
        switch(style)
        {
        default:
        case 1:
            stylename = QTextListFormat::ListDisc;      //实心圆标号
            break;
        case 2:
            stylename = QTextListFormat::ListCircle;    //空心圆标号
            break;
        case 3:
            stylename = QTextListFormat::ListSquare;    //方形括号
            break;
        case 4:
            stylename = QTextListFormat::ListDecimal;   //十进制编号
            break;
        case 5:
            stylename = QTextListFormat::ListLowerAlpha;//小写字母编号
            break;
        case 6:
            stylename = QTextListFormat::ListUpperAlpha;//大写字母编号
            break;
        case 7:
            stylename = QTextListFormat::ListLowerRoman;//小写罗马编号
            break;
        case 8:
            stylename = QTextListFormat::ListUpperRoman;//大写罗马编号
            break;
        }

        //为支持撤销操作
        cursor.beginEditBlock();
        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;
        if(cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(stylename);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);      //合并格式
    }
}

MyChild::~MyChild()
{
}


