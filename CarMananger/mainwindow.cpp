#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include "domxml.h"
#include <QFile>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("汽车管理系统");

    //创建空的xml文件，用于存放销售信息
    DomXML::create_xml("saleList.xml");
    //打开数据库，数据库存放厂家和车辆信息
    connectDB();
    //初始化数据
    initData();
    //开始，车辆管理页面
    on_action_car_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//车辆管理菜单
void MainWindow::on_action_car_triggered()
{
    //切换到车辆管理页面
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label_title->setText("车辆管理");
}

//销售统计菜单
void MainWindow::on_action_calc_triggered()
{
    //切换到销售统计页面
    ui->stackedWidget->setCurrentWidget(ui->calc);
    ui->label_title->setText("销售统计");
}

//连接数据库
void MainWindow::connectDB()
{
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("car");
    //打开数据库
    if (db.open() == false ) {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}

//初始化数据
void MainWindow::initData()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    queryModel->setQuery("select name from factory");  //sql语句

    //车辆管理页面初始化
    ui->comboBox_factory->setModel(queryModel);
    ui->label_last->setText("0");
    ui->lineEdit_total->setEnabled(false);
    ui->lineEdit_price->setEnabled(false);
    ui->pushButton_sure->setEnabled(false);

    //销售统计页面初始化
    ui->comboBox_sale_factory->setModel(queryModel);
}

//厂家下拉框槽函数
void MainWindow::on_comboBox_factory_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "请选择厂家") {
        //内容清空
        ui->comboBox_brand->clear();  //品牌下拉框
        ui->lineEdit_price->clear();  //报价清空
        ui->label_last->setText("0"); //剩余数量
        ui->lineEdit_total->clear();  //金额
        ui->spinBox_num->setValue(0); //数量
        ui->spinBox_num->setEnabled(false);
    } else {
        ui->comboBox_brand->clear();
        QSqlQuery query;
        QString sql = QString("select name from brand where factory = '%1'").arg(arg1);
        //执行sql语句
        query.exec(sql);
        //获取内容
        while (query.next()) {
            QString name = query.value("name").toString();
            ui->comboBox_brand->addItem(name);
        }
        ui->spinBox_num->setEnabled(true);
    }
}

void MainWindow::on_comboBox_brand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'").arg(ui->comboBox_factory->currentText()).arg(arg1);
    //执行sql语句
    query.exec(sql);
    //获取内容
    while (query.next()) {
        //获取报价
        int price = query.value("price").toInt();
        //获取剩余数
        int last = query.value("last").toInt();
        //更新到对应的控件
        ui->lineEdit_price->setText(QString::number(price));
        ui->label_last->setText(QString::number(last));
    }
}

void MainWindow::on_spinBox_num_valueChanged(int arg1)
{
    if (0 == arg1) {
        ui->pushButton_sure->setEnabled(false);
    } else {
        ui->pushButton_sure->setEnabled(true);
    }

    //获取现有数量
    //获取数据库下剩余数量
    //1)厂家
    QString factory_str = ui->comboBox_factory->currentText();
    //2)品牌
    QString brand_str = ui->comboBox_brand->currentText();
    QSqlQuery query;
    QString sql = QString("select last from brand where factory = '%1' and name = '%2'").arg(factory_str).arg(brand_str);
    //执行sql语句
    query.exec(sql);
    int last = 0;
    while (query.next()) {
        last = query.value("last").toInt(); //剩余
    }
    if (arg1 > last) {  //选择的数目大于剩余数目，中断程序
        ui->spinBox_num->setValue(last);
        return;
    }
    int temp_num = last - arg1;
    //更新剩余的数量
    ui->label_last->setText(QString::number(temp_num));
    //更新金额
    int price = ui->lineEdit_price->text().toInt();  //报价
    int total_price = price * arg1;  //总价
    //更新总价
    ui->lineEdit_total->setText(QString::number(total_price));
}

void MainWindow::on_pushButton_sure_clicked()
{
    //获取信息
    //1)数量
    int num = ui->spinBox_num->value();
    //2)剩余
    int last = ui->label_last->text().toInt();
    //3)获取数据库的销量
    QSqlQuery query;
    QString sql = QString("select sell from brand where factory = '%1' and name = '%2'")
            .arg(ui->comboBox_factory->currentText())
            .arg(ui->comboBox_brand->currentText());
    query.exec(sql);
    int sell = 0;
    while (query.next()) {
        sell = query.value("sell").toInt(); //剩余
    }
    //更新数据库：剩余数量、销售总量
    sell += num;
    sql = QString("update brand set sell = %1, last = %2 where factory = '%3' and name = '%4'")
            .arg(sell)
            .arg(last)
            .arg(ui->comboBox_factory->currentText())
            .arg(ui->comboBox_brand->currentText());
    query.exec(sql);

    //把确认后的数据更新到xml中
    QStringList list;
    list << ui->comboBox_factory->currentText()
         << ui->comboBox_brand->currentText()
         << ui->lineEdit_price->text()
         << QString::number(num)
         << ui->lineEdit_total->text();
    DomXML::append_xml("saleList.xml", list);

    //显示
    QStringList factory_list;
    QStringList brand_list;
    QStringList price_list;
    QStringList num_list;
    QStringList totalPrice_list;

    DomXML::read_xml("saleList.xml", factory_list, brand_list, price_list, num_list, totalPrice_list);
    for (int i = 0; i < factory_list.size(); i++) {
        QString str = QString("%1:%2:卖出数量：%3，单价：%4，总价：%5")
                .arg(factory_list.at(i))
                .arg(brand_list.at(i))
                .arg(num_list.at(i))
                .arg(price_list.at(i))
                .arg(totalPrice_list.at(i));
        ui->textEdit->append(str);
        qDebug() << str;
    }

    ui->pushButton_sure->setEnabled(false);
}

void MainWindow::on_pushButton_cancel_clicked()
{
    ui->comboBox_factory->setCurrentIndex(0);
}

void MainWindow::on_comboBox_sale_factory_currentIndexChanged(const QString &arg1)
{
    //销售统计页面的厂家下拉列表框发生变化
    if (arg1 == "请选择厂家") {
        //内容清空
        ui->comboBox_sale_brand->clear();  //品牌下拉框
    } else {
        //显示
        ui->comboBox_sale_brand->clear();
        //更新厂家品牌柱状图
        QSqlQuery query;
        QString sql = QString("select name, sell from brand where factory = '%1'").arg(arg1);
        query.exec(sql);
        QStringList brand_list;
        QStringList sell_list;
        QString name;
        QString sell;
        while(query.next()) {
            name = query.value("name").toString();
            sell = query.value("sell").toString();
            brand_list.append(name);
            sell_list.append(sell);
        }
        ui->comboBox_sale_brand->addItems(brand_list);

        QBarSet *barset = new QBarSet(arg1);
        for (int i = 0; i < sell_list.size(); i++) {
            barset->append(sell_list[i].toInt());
        }
        QBarSeries *series = new QBarSeries();
        series->append(barset);
        series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
        series->setLabelsVisible(true);
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("厂家品牌");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        //想图表轴添加类别
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(brand_list);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
        //设置图例
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        //可以显示图表的独立小部件
        ui->widget_factory->setChart(chart);
        ui->widget_factory->setRenderHint(QPainter::Antialiasing);
        ui->widget_factory->show();
    }
}

void MainWindow::on_comboBox_sale_brand_currentIndexChanged(const QString &arg1)
{
    //更新厂家品牌柱状图
    QSqlQuery query;
    QString sql = QString("select sell, last from brand where factory = '%1' and name = '%2'" ).arg(ui->comboBox_sale_factory->currentText()).arg(arg1);
    query.exec(sql);
    float sell;
    float last;
    while(query.next()) {
        sell = query.value("sell").toFloat();
        last = query.value("last").toFloat();
    }
    QPieSeries *series = new QPieSeries();
    QString name;
    name = name.sprintf("已出售: %.2f\%", sell/(sell+last)*100);
    series->append(name, sell);
    name = name.sprintf("剩余: %.2f\%", last/(sell+last)*100);
    series->append(name, last);
    series->setLabelsVisible(false);

    QPieSlice *slice = series->slices().at(1);
    slice->setExploded();
    slice->setLabelVisible(false);
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("品牌车辆");
    chart->legend()->setVisible(true);

    ui->widget_brand->setChart(chart);
    ui->widget_brand->setRenderHint(QPainter::Antialiasing);
    ui->widget_brand->show();
}
