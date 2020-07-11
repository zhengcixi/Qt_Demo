#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

clientwidget::clientwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwidget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    //分配空间，指定父对象
    tcpsocket = new QTcpSocket(this);
    //建立连接
    connect(tcpsocket, &QTcpSocket::connected,
        [=]() {
            ui->textEdit_recv->setText("成功和服务器建立了连接");
        }
    );
    //接收数据
    connect(tcpsocket, &QTcpSocket::readyRead,
        [=](){
            //获取对方发送的内容
            QByteArray array = tcpsocket->readAll();
            //追加到编辑区中
            ui->textEdit_recv->append(array);
        }
    );
    //断开连接
    connect(tcpsocket, &QTcpSocket::disconnected,
        [=](){
            ui->textEdit_recv->append("和服务器断开了连接");
        }
    );
}

clientwidget::~clientwidget()
{
    delete ui;
}

void clientwidget::on_pushButton_send_clicked()
{
    //获取编辑框内容
    QString str = ui->textEdit_send->toPlainText();
    //发送数据
    tcpsocket->write(str.toUtf8().data());
}

void clientwidget::on_pushButton_close_clicked()
{
    //主动和对方断开连接
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
}

void clientwidget::on_pushButton_connect_clicked()
{
    //获取服务器ip和端口
    QString ip = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toInt();
    //主动和服务器建立连接
    tcpsocket->connectToHost(QHostAddress(ip), port);
}
