#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class clientwidget;
}

class clientwidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientwidget(QWidget *parent = 0);
    ~clientwidget();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::clientwidget *ui;
    QTcpSocket *tcpsocket = NULL;
};

#endif // CLIENTWIDGET_H
