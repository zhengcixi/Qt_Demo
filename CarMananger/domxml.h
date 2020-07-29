#ifndef DOMXML_H
#define DOMXML_H
#include <QString>
#include <QStringList>
#include <QDomDocument>


class DomXML
{
public:
    DomXML();

    //创建xml空文件
    static void create_xml(QString file_path);
    //list.at(0) =
    static void append_xml(QString file_path, QStringList list);

    static void write_xml(QDomDocument &doc, QDomElement &root, QStringList &list);
    static void read_xml(QString file_path,
                         QStringList &factory_list,
                         QStringList &brand_list,
                         QStringList &price_list,
                         QStringList &num_list,
                         QStringList &totalPrice_list);
};

#endif // DOMXML_H
