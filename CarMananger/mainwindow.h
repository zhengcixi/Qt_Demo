#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //连接数据库
    void connectDB();
    //初始化
    void initData();

private slots:
    void on_action_car_triggered();

    void on_action_calc_triggered();

    void on_comboBox_factory_currentIndexChanged(const QString &arg1);

    void on_comboBox_brand_currentIndexChanged(const QString &arg1);

    void on_spinBox_num_valueChanged(int arg1);

    void on_pushButton_sure_clicked();

    void on_pushButton_cancel_clicked();

    void on_comboBox_sale_factory_currentIndexChanged(const QString &arg1);

    void on_comboBox_sale_brand_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
