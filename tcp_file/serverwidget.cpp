#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器");

    //监听套接字
    tcpserver = new QTcpServer(this);
    //启动监听
    tcpserver->listen(QHostAddress::Any, 8888);

    //两个按钮都不能使用
    ui->pushButton_choose->setEnabled(false);
    ui->pushButton_send->setEnabled(false);

    //如果客户端成功和服务器连接
    connect(tcpserver, &QTcpServer::newConnection,
        [=](){
            //取出建立好连接的套接字
            tcpsocket = tcpserver->nextPendingConnection();
            //获取对方的IP和端口
            QString ip = tcpsocket->peerAddress().toString();
            quint16 port = tcpsocket->peerPort();
            QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
            ui->textEdit->append(str); //显示到编辑区
            //成功连接后，才能选择文件
            ui->pushButton_choose->setEnabled(true);
            ui->pushButton_send->setEnabled(false);
            connect(tcpsocket, &QTcpSocket::readyRead,
                [=]() {
                    //取客户端的消息
                    QByteArray buf = tcpsocket->readAll();
                    if (QString(buf) == "file done") {  //文件接收完毕
                        ui->textEdit->append("文件接收完成");
                        file.close();
                        //断开客户端端口
                        tcpsocket->disconnectFromHost();
                        tcpsocket->close();
                        ui->pushButton_choose->setEnabled(false);
                        ui->pushButton_send->setEnabled(false);
                    }
                }
            );
        }
    );
    //定时器事件
    connect(&timer, &QTimer::timeout,
        [=](){
            //关闭定时器
            timer.stop();
            //发送数据
            sendData();
        }
    );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//发送文件按钮
void ServerWidget::on_pushButton_send_clicked()
{
    //发送文件头信息
    QString head = QString("%1##%2").arg(filename).arg(filesize);
    qint64 len = tcpsocket->write(head.toUtf8());
    if (len > 0) {  //头部信息发送成功
        //防止TCP粘包问题，需要通过定时器样式
        timer.start(2000);
    } else {
        qDebug() << "send header data error!!!";
        file.close();
        ui->pushButton_choose->setEnabled(true);
        ui->pushButton_send->setEnabled(false);
    }
}

//选择文件按钮
void ServerWidget::on_pushButton_choose_clicked()
{
    //打开文件
    QString filepath = QFileDialog::getOpenFileName(this, "open", "../");
    if (false == filepath.isEmpty()) {  //选择文件路径有效
        filename.clear();
        filesize = 0;
        sendsize = 0;
        //获取文件信息 文件名 文件大小
        QFileInfo info(filepath);
        filename = info.fileName();
        filesize = info.size();
        //只读方式打开文件
        file.setFileName(filepath);
        bool isOK = file.open(QIODevice::ReadOnly);
        if (false == isOK) {
            qDebug() << "open file error!!!";
        }
        QString str = QString("已选择文件：%1").arg(filepath);
        ui->textEdit->append(str);
        //设置按钮属性
        ui->pushButton_choose->setEnabled(false);
        ui->pushButton_send->setEnabled(true);
    } else {
        qDebug() << "选择的文件路径无效！！！";
    }
}

//发送文件数据
void ServerWidget::sendData()
{
    ui->textEdit->append("正在发送文件...");
    qint64 len = 0;
    do {
        //每次发送数据的大小
        char buf[4*1024] = {0};
        //往文件中读数据
        len = file.read(buf, sizeof(buf));
        if (len <= 0) {
            break;
        }
        //发送数据，读多少，发多少
        len = tcpsocket->write(buf, len);
        //发送数据大小累加
        sendsize += len;
        qDebug() << "have send:" << len;
    } while (len > 0);
}
