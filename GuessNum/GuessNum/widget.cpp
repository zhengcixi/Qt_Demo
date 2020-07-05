#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //显示第一个页面，设置页面
    ui->stackedWidget->setCurrentWidget(ui->pageSet);
    //失败动画
    loseMovie.setFileName(":/new/prefix1/image/over.gif");
    ui->label_lose->setMovie(&loseMovie);//给标签设置动画
    ui->label_lose->setScaledContents(true);//让动画自动适应标签大小
    //胜利动画
    winMovie.setFileName(":/new/prefix1/image/win.gif");
    ui->label_win->setMovie(&winMovie);
    ui->label_win->setScaledContents(true);

    //启动游戏
    connect(ui->pushButton_enter, &QPushButton::clicked, this, &Widget::on_PushButtonStart_clicked);
    //退出游戏
    connect(ui->pushButton_quit,  &QPushButton::clicked, this, &Widget::close);
    //删除前一个数字
    connect(ui->pushButton_rollback, &QPushButton::clicked, this, &Widget::on_PushButtonRollback_clicked);
    //提示
    connect(ui->pushButton_notice, &QPushButton::clicked, this, &Widget::on_PushButtonNotice_clicked);

    //对数字按钮的处理使用同一个槽函数
    connect(ui->pushButton_0, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Widget::dealNum);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &Widget::dealNum);
}

void Widget::on_PushButtonStart_clicked()
{
    //获取下拉框时间，并将字符串转换为整数
    gameTime = ui->comboBox->currentText().toInt();
    qDebug() << gameTime << "s";

    //切换到游戏界面
    ui->stackedWidget->setCurrentWidget(ui->pageGame);

    int num;
    //从0时0分0秒到现在的秒数为种子
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    //调用全局的qsrand()函数生成随机数，对10000取余，保证位于10000的范围内
    while((num = qrand()%10000) < 999);
    randStr = QString::number(num);
    qDebug() << "randNum" << randStr;

    //设置进度条
    ui->progressBar->setMinimum(0); //最小值
    ui->progressBar->setMaximum(gameTime);  //最大值
    ui->progressBar->setValue(gameTime); //当前值

    //启动定时器
    gameTimerId = startTimer(1000);  //以1000ms为间隔
    resultStr.clear();
    ui->textEdit->clear();
}

void Widget::on_PushButtonRollback_clicked()
{
    //退格按钮，删除最后一个数字
    if(resultStr.size() == 1) {
        resultStr.clear();
        ui->textEdit->clear();
    } else {
        resultStr.chop(1); //截断最后一位字符
        ui->textEdit->setText(resultStr);
    }
}

void Widget::on_PushButtonNotice_clicked()
{
    //提示
    resultStr.clear();
    QString str = "正确答案为：" + randStr;
    ui->textEdit->setText(str);
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == gameTimerId) {  //游戏时间
        gameTime--;
        //设置进度条
        ui->progressBar->setValue(gameTime); //当前值
        //时间到
        if(0 == gameTime) {
            //关闭定时器
            killTimer(gameTimerId);
            QMessageBox::information(this, "失败", "时间到了啊！！！");
            loseMovie.start();//启动动画
            //切换失败动画页面
            ui->stackedWidget->setCurrentWidget(ui->pageLose);
            loseTimerId = startTimer(5000); //启动定时器
        }
    } else if(event->timerId() == loseTimerId) {  //失败动画时间
        //停止动画，停止定时器，回到游戏设置页面
        loseMovie.stop();//停止动画
        killTimer(loseTimerId);  //停止定时器
        //切换到游戏设置页面
        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    } else if(event->timerId() == winTimerId) {  //胜利动画时间
        winMovie.stop();//停止动画
        killTimer(winTimerId);  //停止定时器
        //切换到游戏设置页面
        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }
}

void Widget::dealNum()
{
    //获取信号发送者
    QObject *mysender = sender();
    //转换为按钮类型
    QPushButton *pb = (QPushButton *)mysender;
    if (NULL != pb) {
        //获取按钮内容
        QString numStr = pb->text();
        resultStr += numStr;
        //数字不能以0开始
        if (resultStr.size() == 1 && resultStr=="0") {
            resultStr.clear();
        }
        //保证显示结果为4位
        if(resultStr.size() <= 4) {
            ui->textEdit->setText(resultStr);
            if (resultStr.size() == 4) {
                if (resultStr > randStr) {
                    ui->textEdit->append("数字大了点!!!");
                } else if (resultStr < randStr) {
                    ui->textEdit->append("数字小了点!!!");
                } else {
                    ui->textEdit->append("恭喜你答对了!!!");
                    //停止定时器
                    killTimer(gameTimerId);
                    QMessageBox::information(this, "胜利", "恭喜你!!!");
                    //启动win页面
                    winMovie.start();
                    ui->stackedWidget->setCurrentWidget(ui->pageWin);
                    //启动定时器
                    winTimerId = startTimer(5000); //5s
                }
                //初始化字符串结果，清空
                resultStr.clear();
            }
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
