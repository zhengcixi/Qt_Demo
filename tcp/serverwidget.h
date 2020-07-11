#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>  //监听套接字
#include <QTcpSocket>  //通信套接字

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *tcpserver = NULL;  //监听套接字
    QTcpSocket *tcpsocket = NULL;  //通信套接字
};

#endif // SERVERWIDGET_H
