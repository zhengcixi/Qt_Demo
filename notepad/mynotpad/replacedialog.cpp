#include "replacedialog.h"
#include <QString>
#include <QDialog>

replacedialog::replacedialog(QWidget *parent) : QDialog(parent)
{
    find_label         = new QLabel("替换内容");
    replace_label      = new QLabel("替换为");
    find_str           = new QLineEdit();
    replace_str        = new QLineEdit();
    find_next_button   = new QPushButton("查找下一个");
    replace_one_button = new QPushButton("替换");
    replace_all_button = new QPushButton("全部替换");
    cancel_button      = new QPushButton("取消");
    ignore_flag        = new QCheckBox("区分大小写");

    QGridLayout *gridly = new QGridLayout(this);
    QVBoxLayout *vboxly = new QVBoxLayout();

    vboxly->addWidget(replace_all_button);
    vboxly->addWidget(cancel_button);
    gridly->addWidget(find_label, 0, 0);
    gridly->addWidget(find_str, 0, 1);
    gridly->addWidget(find_next_button, 0, 2);
    gridly->addWidget(replace_label, 1, 0);
    gridly->addWidget(replace_str, 1, 1);
    gridly->addWidget(replace_one_button, 1, 2);
    gridly->addWidget(ignore_flag, 2, 1);
    gridly->addLayout(vboxly, 2, 2);

    find_str->setText("");
    replace_str->setText("");
    find_next_button->setEnabled(false);
    replace_one_button->setEnabled(false);
    replace_all_button->setEnabled(false);

    this->setMaximumSize(350, 150);
    this->setMinimumSize(300, 100);

    connect(find_str,         &QLineEdit::textChanged, this, &replacedialog::slot_choose_str);
    connect(cancel_button,      &QPushButton::clicked, this, &replacedialog::close);
    connect(find_next_button,   &QPushButton::clicked, this, &replacedialog::slot_find_button_state);
    connect(replace_one_button, &QPushButton::clicked, this, &replacedialog::slot_replace_one_button_state);
    connect(replace_all_button, &QPushButton::clicked, this, &replacedialog::slot_repalce_all_button_state);

}

void replacedialog::slot_choose_str()
{
    if (!find_str->text().isEmpty()) {
        find_next_button->setEnabled(true);
        replace_one_button->setEnabled(true);
        replace_all_button->setEnabled(true);
    } else {
        find_next_button->setEnabled(false);
        replace_one_button->setEnabled(false);
        replace_all_button->setEnabled(false);
    }
}
void replacedialog::slot_find_button_state()
{
    if (ignore_flag->isChecked()) {
        emit signal_findReplaceStr(find_str->text(), true);
    } else {
        emit signal_findReplaceStr(find_str->text(), false);
    }
}
void replacedialog::slot_replace_one_button_state()
{
    emit signal_replaceCurOneStr(find_str->text(), replace_str->text());
}
void replacedialog::slot_repalce_all_button_state()
{
    if (ignore_flag->isChecked()) {
        emit signal_replaceAllStr(find_str->text(), replace_str->text(), true);
    } else {
        emit signal_replaceAllStr(find_str->text(), replace_str->text(), false);
    }
}
