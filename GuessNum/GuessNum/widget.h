#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QMovie>

namespace Ui {
class Widget;
}

//目的：实现一个猜字游戏
//说明：
//

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //槽函数
    void on_PushButtonStart_clicked();
    void on_PushButtonQuit_clicked();
    void on_PushButtonRollback_clicked();
    void on_PushButtonNotice_clicked();
    void dealNum();
    void timerEvent(QTimerEvent *event);

private:
    int gameTime;
    int gameTimerId;   //游戏定时器
    int loseTimerId;   //输了
    int winTimerId;    //赢了
    QString randStr;   //随机数
    QString resultStr; //结果数
    QMovie winMovie;   //赢了的动画
    QMovie loseMovie;  //输了的动画


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
