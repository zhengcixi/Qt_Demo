#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器: 8888");

    //监听套接字，指定父对象，自动回收空间
    tcpserver = new QTcpServer(this);
    //启动监听
    tcpserver->listen(QHostAddress::Any, 8888);
    //等待连接
    connect(tcpserver, &QTcpServer::newConnection,
        [=]() {
            //取出建立好连接的套接字
            tcpsocket = tcpserver->nextPendingConnection();
            //获取对方的ip的端口
            QString ip = tcpsocket->peerAddress().toString();
            qint16 port = tcpsocket->peerPort();
            QString tmp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
            //在当前对话框显示谁和我连接了
            ui->textEdit_recv->setText(tmp);

            //接收数据
            connect(tcpsocket, &QTcpSocket::readyRead,
                [=](){
                    //从通信套接字中取出内容
                     QByteArray array = tcpsocket->readAll();
                     ui->textEdit_recv->append(array);
                }
            );
        }
    );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_pushButton_close_clicked()
{
    if (NULL == tcpsocket) {
        return;
    }
    //主动和客户端断开连接
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    tcpsocket = NULL;
}

void ServerWidget::on_pushButton_send_clicked()
{
    if (NULL == tcpsocket) {
        return;
    }
    //获取编辑区内容
    QString str = ui->textEdit_send->toPlainText();
    //给对方发送数据
    //QString -> char*
    tcpsocket->write(str.toUtf8().data());
}

