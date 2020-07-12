#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientWidget(QWidget *parent = 0);
    ~clientWidget();

private slots:
    void on_pushButton_connect_clicked();

private:
    Ui::clientWidget *ui;

    QTcpSocket *tcpsocket = NULL;  //通信套接字
    QFile file;  //文件对象
    QString filename; //文件名
    qint64 filesize = 0;  //文件大小
    qint64 recvsize = 0;  //已发送文件大小
    bool isStart; //开始接收文件标志位
};

#endif // CLIENTWIDGET_H
