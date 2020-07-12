#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();
    void sendData(); //发送文件数据


private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_choose_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpserver = NULL;  //监听套接字
    QTcpSocket *tcpsocket = NULL;  //通信套接字
    QFile file;  //文件对象
    QString filename; //文件名
    qint64 filesize;  //文件大小
    qint64 sendsize;  //已发送文件大小
    QTimer timer;  //定时器

};

#endif // SERVERWIDGET_H
