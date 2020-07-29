#include "domxml.h"
#include <QFile>
#include <QDomComment> //文件
#include <QDomProcessingInstruction> //格式头部
#include <QDomElement> //元素
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

DomXML::DomXML()
{
}

void DomXML::create_xml(QString file_path)
{
    QFile file(file_path);  //关联文件名字
    if (true == file.exists()) {  //如果存在不创建
        cout << "文件已经存在";
        return;
    }
    //只写方式打开文件
    bool isOK = file.open(QIODevice::WriteOnly);
    if (false == isOK) {
        cout << "writeOnly error";
        return;
    }
    //创建xml文档对象
    QDomDocument doc;
    //创建xml头部格式：<?xml version='1.0' encoding='utf-8'?>
    QDomProcessingInstruction ins;
    ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'utf-8\'");
    //追加元素
    doc.appendChild(ins);
    //创建根节点元素
    QDomElement root = doc.createElement("日销售清单");
    doc.appendChild(root);
    //保存
    QTextStream stream(&file);  //文本流关联文件
    doc.save(stream, 4);  //4 缩进字符

    //关闭文件
    file.close();
}

void DomXML::append_xml(QString file_path, QStringList list)
{
    QFile file(file_path);  //关联文件名字
    //只读方式打开文件
    bool isOK = file.open(QIODevice::ReadOnly);
    if (false == isOK) {
        cout << "ReadOnly error";
        return;
    }
    //文件file和xml关联
    QDomDocument doc;
    isOK = doc.setContent(&file);
    if (false == isOK) {
        cout << "setContent error";
    }
    //关联成功后，可以关闭文件
    file.close();
    //获取根节点元素
    QDomElement root = doc.documentElement();
    //获取当前时间
    QDateTime date = QDateTime::currentDateTime();
    QString date_str = date.toString("yyyy-MM-dd"); //2020-07-21
    //判断根节点下有没有子节点
    if (root.hasChildNodes()) {  //如果有子节点
        //查找最后一个子节点
        QDomElement last_elem = doc.lastChildElement();
        if (last_elem.attribute("date") == date_str) {
            //有没有当天的日期
            write_xml(doc, last_elem, list);
        } else {
            //没有当前的日期
            //创建<日期>子节点
            QDomElement date_elem = doc.createElement("日期");
            //设置<日期>属性
            QDomAttr date_attr = doc.createAttribute("date");
            //设定属性的值
            date_attr.setNodeValue(date_str);
            //节点和属性关联
            date_elem.setAttributeNode(date_attr);
            //把<日期>节点追加到根节点上
            root.appendChild(date_elem);
            //写有效数据
            write_xml(doc, date_elem, list);
        }
    } else {  //没有子节点
        //创建<日期>子节点
        QDomElement date_elem = doc.createElement("日期");
        //设置<日期>属性
        QDomAttr date_attr = doc.createAttribute("date");
        //设定属性的值
        date_attr.setNodeValue(date_str);
        //节点和属性关联
        date_elem.setAttributeNode(date_attr);
        //把<日期>节点追加到根节点上
        root.appendChild(date_elem);
        //写有效数据
        write_xml(doc, date_elem, list);
    }
    //保存文件
    isOK = file.open(QIODevice::WriteOnly);
    if (false == isOK) {
        cout << "writeOnly error";
        return;
    }
    QTextStream stream(&file);
    doc.save(stream, 4);
    file.close();
}

void DomXML::write_xml(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    //当前时间获取
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("hh:mm:ss"); //16:05:24
    //创建<时间>节点元素
    QDomElement time_elem = doc.createElement("时间");
    //创建<时间>属性
    QDomAttr time_attr = doc.createAttribute("time");
    //给属性设置值
    time_attr.setNodeValue(time_str);
    //时间元素和属性关联
    time_elem.setAttributeNode(time_attr);
    //时间节点加到日期节点后面
    root.appendChild(time_elem);

    //创建<厂家><品牌><报价><数量><金额>节点元素
    QDomText text;
    QDomElement factory_elem = doc.createElement("厂家");
    text = doc.createTextNode(list.at(0));
    factory_elem.appendChild(text);
    QDomElement brand_elem = doc.createElement("品牌");
    text = doc.createTextNode(list.at(1));
    brand_elem.appendChild(text);
    QDomElement price_elem = doc.createElement("报价");
    text = doc.createTextNode(list.at(2));
    price_elem.appendChild(text);
    QDomElement num_elem = doc.createElement("数量");
    text = doc.createTextNode(list.at(3));
    num_elem.appendChild(text);
    QDomElement totalPrice_elem = doc.createElement("金额");
    text = doc.createTextNode(list.at(4));
    totalPrice_elem.appendChild(text);
    //追加到<时间>节点后面
    time_elem.appendChild(factory_elem);
    time_elem.appendChild(brand_elem);
    time_elem.appendChild(price_elem);
    time_elem.appendChild(num_elem);
    time_elem.appendChild(totalPrice_elem);
}

void DomXML::read_xml(QString file_path,
                     QStringList &factory_list,
                     QStringList &brand_list,
                     QStringList &price_list,
                     QStringList &num_list,
                     QStringList &totalPrice_list)
{
    QFile file(file_path);  //关联文件名字
    //只读方式打开文件
    bool isOK = file.open(QIODevice::ReadOnly);
    if (false == isOK) {
        cout << "ReadOnly error";
        return;
    }
    //文件file和xml关联
    QDomDocument doc;
    isOK = doc.setContent(&file);
    if (false == isOK) {
        cout << "setContent error";
    }
    //关联成功后，可以关闭文件
    file.close();
    //获取根节点
    QDomElement root = doc.documentElement();

    QDateTime date = QDateTime::currentDateTime();
    QString date_str = date.toString("yyyy-MM-dd");
    if (root.hasChildNodes()) {  //有没有子节点
        QDomElement last_elem = root.lastChildElement();
        if (last_elem.attribute("date") == date_str) {  //判断是否有当前日期
            //找出当前日期下所有时间子节点
            QDomNodeList list = last_elem.childNodes();
            for (int i = 0; i < list.size(); i++) {
                //转换为元素，找到时间节点下的所有子节点
                QDomNodeList sublist = list.at(i).toElement().childNodes();
                //厂家
                QString factory = sublist.at(0).toElement().text();
                factory_list.append(factory);
                //品牌
                QString brand = sublist.at(1).toElement().text();
                brand_list.append(brand);
                //单价
                QString price = sublist.at(2).toElement().text();
                price_list.append(price);
                //数量
                QString num = sublist.at(3).toElement().text();
                num_list.append(num);
                //金额
                QString totalPrice = sublist.at(4).toElement().text();
                totalPrice_list.append(totalPrice);
            }
        } else {
            cout << "没有当天日期";
            return;
        }
    } else {  //没有子节点
        cout << "没有子节点";
        return;
    }

}
