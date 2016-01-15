#ifndef MYCHILD_H
#define MYCHILD_H

#include <QTextEdit>
#include <QWidget>
#include <QPrinter>

class MyChild : public QTextEdit
{
    Q_OBJECT
public:
    MyChild();
    ~MyChild();

    //新建操作
    void newFile();
    //提取文件名
    QString userFriendlyCurrentFile();
    //返回当前文件路径
    QString currentFile()
    {
        return curFile;
    }

    //加载文件的操作
    bool loadFile(const QString &fileName);

    //保存文件操作
    bool save();
    bool saveAs();
    bool saveFile(QString &fileName);

    //设置字体格式
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    //段落对齐设置
    void setAlign(int align);

    //子窗体设置段落标号、标号操作
    void setStyle(int style);

private:
    void setCurrentFile(const QString &fileName);

    //提醒用户保存
    bool maybeSave();

protected:
    //关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    //文档被更改时，窗口显示更改状态标识
    void documentWasModified();

private:
    //获取较短的绝对路径
    QString strippedName(const QString &fullFileName);
    //保存当前文件路径
    QString curFile;
    //作为当前文件是否被保存到硬盘上的标识
    bool isUntitled;
};

#endif  //MYCHILD_H
