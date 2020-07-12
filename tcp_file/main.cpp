#include "serverwidget.h"
#include <QApplication>
#include "clientwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    clientWidget w2;
    w.show();
    w2.show();

    return a.exec();
}
