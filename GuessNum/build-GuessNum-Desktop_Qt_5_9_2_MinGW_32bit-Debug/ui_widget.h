/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *pageSet;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_enter;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_quit;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_3;
    QWidget *pageGame;
    QProgressBar *progressBar;
    QWidget *widget_3;
    QPushButton *pushButton_0;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_rollback;
    QPushButton *pushButton_notice;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QTextEdit *textEdit;
    QWidget *pageWin;
    QGridLayout *gridLayout;
    QLabel *label_win;
    QWidget *pageLose;
    QGridLayout *gridLayout_4;
    QLabel *label_lose;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(620, 418);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(11, 13, 571, 383));
        pageSet = new QWidget();
        pageSet->setObjectName(QStringLiteral("pageSet"));
        gridLayout_3 = new QGridLayout(pageSet);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(190, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        label = new QLabel(pageSet);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(189, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 1, 1, 1);

        widget_2 = new QWidget(pageSet);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_8 = new QSpacerItem(189, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(189, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        comboBox = new QComboBox(widget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 2, 1, 1);


        gridLayout_3->addWidget(widget_2, 3, 0, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 57, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 4, 1, 1, 1);

        widget = new QWidget(pageSet);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        pushButton_enter = new QPushButton(widget);
        pushButton_enter->setObjectName(QStringLiteral("pushButton_enter"));

        horizontalLayout->addWidget(pushButton_enter);

        horizontalSpacer_5 = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        pushButton_quit = new QPushButton(widget);
        pushButton_quit->setObjectName(QStringLiteral("pushButton_quit"));

        horizontalLayout->addWidget(pushButton_quit);

        horizontalSpacer_7 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        gridLayout_3->addWidget(widget, 5, 0, 1, 3);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 6, 1, 1, 1);

        stackedWidget->addWidget(pageSet);
        pageGame = new QWidget();
        pageGame->setObjectName(QStringLiteral("pageGame"));
        progressBar = new QProgressBar(pageGame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(40, 30, 521, 23));
        progressBar->setValue(24);
        widget_3 = new QWidget(pageGame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(11, 252, 571, 131));
        pushButton_0 = new QPushButton(widget_3);
        pushButton_0->setObjectName(QStringLiteral("pushButton_0"));
        pushButton_0->setGeometry(QRect(30, 10, 61, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(false);
        font.setWeight(50);
        pushButton_0->setFont(font);
        pushButton_1 = new QPushButton(widget_3);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(110, 10, 61, 51));
        QFont font1;
        font1.setPointSize(18);
        pushButton_1->setFont(font1);
        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 10, 61, 51));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(270, 10, 61, 51));
        pushButton_3->setFont(font1);
        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(350, 10, 61, 51));
        pushButton_4->setFont(font1);
        pushButton_rollback = new QPushButton(widget_3);
        pushButton_rollback->setObjectName(QStringLiteral("pushButton_rollback"));
        pushButton_rollback->setGeometry(QRect(430, 10, 111, 51));
        pushButton_rollback->setFont(font1);
        pushButton_notice = new QPushButton(widget_3);
        pushButton_notice->setObjectName(QStringLiteral("pushButton_notice"));
        pushButton_notice->setGeometry(QRect(430, 70, 111, 51));
        pushButton_notice->setFont(font1);
        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(110, 70, 61, 51));
        pushButton_6->setFont(font1);
        pushButton_8 = new QPushButton(widget_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(270, 70, 61, 51));
        pushButton_8->setFont(font1);
        pushButton_9 = new QPushButton(widget_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(350, 70, 61, 51));
        pushButton_9->setFont(font1);
        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(30, 70, 61, 51));
        pushButton_5->setFont(font1);
        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(190, 70, 61, 51));
        pushButton_7->setFont(font1);
        textEdit = new QTextEdit(pageGame);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(40, 80, 511, 151));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(18);
        textEdit->setFont(font2);
        stackedWidget->addWidget(pageGame);
        pageWin = new QWidget();
        pageWin->setObjectName(QStringLiteral("pageWin"));
        gridLayout = new QGridLayout(pageWin);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_win = new QLabel(pageWin);
        label_win->setObjectName(QStringLiteral("label_win"));

        gridLayout->addWidget(label_win, 0, 0, 1, 1);

        stackedWidget->addWidget(pageWin);
        pageLose = new QWidget();
        pageLose->setObjectName(QStringLiteral("pageLose"));
        gridLayout_4 = new QGridLayout(pageLose);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_lose = new QLabel(pageLose);
        label_lose->setObjectName(QStringLiteral("label_lose"));

        gridLayout_4->addWidget(label_lose, 0, 0, 1, 1);

        stackedWidget->addWidget(pageLose);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600;\">\347\214\234\346\225\260\345\255\227\346\270\270\346\210\217</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\350\257\267\350\256\276\347\275\256\346\225\260\345\255\227\346\227\266\351\227\264\357\274\210\347\247\222\357\274\211", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "20", Q_NULLPTR)
         << QApplication::translate("Widget", "40", Q_NULLPTR)
         << QApplication::translate("Widget", "60", Q_NULLPTR)
         << QApplication::translate("Widget", "80", Q_NULLPTR)
         << QApplication::translate("Widget", "120", Q_NULLPTR)
         << QApplication::translate("Widget", "180", Q_NULLPTR)
         << QApplication::translate("Widget", "240", Q_NULLPTR)
        );
        pushButton_enter->setText(QApplication::translate("Widget", "\350\277\233\345\205\245\346\270\270\346\210\217", Q_NULLPTR));
        pushButton_quit->setText(QApplication::translate("Widget", "\351\200\200\345\207\272\346\270\270\346\210\217", Q_NULLPTR));
        pushButton_0->setText(QApplication::translate("Widget", "0", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("Widget", "1", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "2", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Widget", "3", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Widget", "4", Q_NULLPTR));
        pushButton_rollback->setText(QApplication::translate("Widget", "<--", Q_NULLPTR));
        pushButton_notice->setText(QApplication::translate("Widget", "\346\217\220\347\244\272", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("Widget", "6", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("Widget", "8", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("Widget", "9", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Widget", "5", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("Widget", "7", Q_NULLPTR));
        label_win->setText(QString());
        label_lose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
