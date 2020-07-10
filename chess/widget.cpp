#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    chessX = -1;
    chessY = -1;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    gridX = width()/10;
    gridY = height()/10;
    startX = gridX;
    startY = gridY;

    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    p.setPen(pen);

    //画棋盘
    for (int i = 0; i <= 8; i++) {
        //画横线
        p.drawLine(startX, startY+gridY*i, startX+8*gridX, startY+gridY*i);
        //画竖线
        p.drawLine(startX+i*gridX, startY, startX+i*gridX, startY+gridY*8);
    }
    //画棋子
    if(chessX != -1 && chessY != -1) {
        p.drawPixmap(startX+chessX*gridX, startY+chessY*gridY, gridX, gridY, QPixmap(":/new/prefix1/image/face.png"));
    }

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //获取点击的坐标
    int x = event->x();
    int y = event->y();
    // 要保证点击点在棋盘范围里面
    if(x >= startX && x <= startX+8*gridX
       && y >= startY && y <= startX+8*gridY) {
        // 棋盘的位置转换转换为坐标下标值
        // 类似于a[i][j]的i和j
        chessX = (x - startX) / gridX;
        chessY = (y - startY) / gridY;
        qDebug() << chessX << chessY;
        //更新窗口，间接调用paintEvent()
        update();
    }
}
