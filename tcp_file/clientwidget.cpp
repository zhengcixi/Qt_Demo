#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
#include <QIODevice>

clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");

    isStart = true;
    ui->progressBar->setValue(0);  //当前值

    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket, &QTcpSocket::readyRead,
        [=](){
            //取出接收的内容
            qDebug() << "isstart:" << isStart;
            QByteArray buf = tcpsocket->readAll();
            if (isStart == true) {  //接收到头部信息
                isStart = false;
                //解析头部信息  初始化
                filename = QString(buf).section("##", 0, 0);  //文件名
                filesize = QString(buf).section("##", 1, 1).toInt();  //文件大小
                recvsize = 0;   //已经接收文件大小
                qDebug() << "fileName" << filename << "filesize" << filesize;
                //打开文件
                file.setFileName(filename);
                bool isOK = file.open(QIODevice::WriteOnly);
                if (false == isOK) {
                    qDebug() << "open error!!!";
                    //关闭连接
                    tcpsocket->disconnectFromHost();
                    tcpsocket->close();
                    return;
                }
                //弹出对话框，显示接收文件信息
                QString str = QString("接收的文件：[%1:%2kb]").arg(filename).arg(filesize/1024);
                QMessageBox::information(this, "文件信息", str);
                //设置进度条
                ui->progressBar->setMinimum(0);
                ui->progressBar->setMaximum(filesize/1024);
                ui->progressBar->setValue(0);
                QString str1 = QString("开始接收文件%1，大小为%2bytes").arg(filename).arg(filesize);
                ui->textEdit->append(str1);
            } else { //真正的文件信息
                qDebug() << "start write data";
                qint64 len = file.write(buf);
                if (len > 0) {
                    recvsize += len;
                    qDebug() << len;
                }
                qDebug() << "recvsize" << recvsize << "filesize" << filesize;
                //更新进度条
                ui->progressBar->setValue(recvsize/1024);
                if (recvsize == filesize) {  //文件接收完成
                    qDebug() << "recvsize" << recvsize << "filesize" << filesize;
                    //先向服务器发送接收文件完成的信息
                    tcpsocket->write("file done");
                    QMessageBox::information(this, "完成", "文件接收完成");
                    file.close();
                    tcpsocket->disconnectFromHost();
                    tcpsocket->close();
                }
            }
        }
    );
    connect(tcpsocket, &QTcpSocket::connected,
        [=](){
            ui->textEdit->clear();
            ui->textEdit->append("已经和服务器建立了连接，等待服务器传输文件...");
            ui->pushButton_connect->setEnabled(false);
        }
    );
    connect(tcpsocket, &QTcpSocket::disconnected,
        [=](){
            ui->textEdit->append("已经和服务器断开了连接");
            ui->pushButton_connect->setEnabled(true);
        }
    );
}

clientWidget::~clientWidget()
{
    delete ui;
}

void clientWidget::on_pushButton_connect_clicked()
{
    //获取服务器的ip和端口
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->lineEdit_port->text().toInt();
    //主动和服务器建立连接
    tcpsocket->connectToHost(QHostAddress(ip), port);
    isStart = true;
    //设置进度条
    ui->progressBar->setValue(0);
}
