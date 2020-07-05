#include "finddialog.h"
#include <QDebug>

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("查找");
    find_label  = new QLabel("查找");
    ignore_label= new QLabel("区分大小写");
    next_label  = new QLabel("向后");
    back_label  = new QLabel("向前");
    find_edit   = new QLineEdit;
    find_button = new QPushButton("查找下一个");
    next_radio  = new QRadioButton;
    back_radio  = new QRadioButton;
    ignore_flag = new QCheckBox;

    find_edit->setText("");

    QGridLayout *grid_layout = new QGridLayout(this);
    grid_layout->addWidget(find_label, 0, 0);
    grid_layout->addWidget(find_edit, 0, 1);
    grid_layout->addWidget(find_button, 0, 3);

    QHBoxLayout *ignore_layout = new QHBoxLayout;
    ignore_layout->setSpacing(10);
    ignore_layout->addWidget(ignore_label);
    ignore_layout->addWidget(ignore_flag);

    QHBoxLayout *radio_layout = new QHBoxLayout;
    radio_layout->addWidget(next_label);
    radio_layout->addWidget(next_radio);
    radio_layout->addWidget(back_label);
    radio_layout->addWidget(back_radio);

    QGroupBox *group_radio = new QGroupBox("方向", this);
    group_radio->setLayout(radio_layout);

    QHBoxLayout *do_radio = new QHBoxLayout;
    do_radio->addWidget(group_radio);

    grid_layout->addLayout(ignore_layout, 1, 0);
    grid_layout->addLayout(do_radio, 1, 1);

    this->setMaximumSize(400, 200);
    this->setMinimumSize(350, 150);
    next_radio->setCheckable(true);
    find_button->setEnabled(false);
    connect(find_edit,   &QLineEdit::textChanged, this, &FindDialog::findButtonState);
    connect(find_button, &QPushButton::clicked,   this, &FindDialog::findDataButtonClickedState);
}

void FindDialog::findButtonState()
{
    if (find_edit->text().isEmpty()) {
        find_button->setEnabled(false);
    } else {
        find_button->setEnabled(true);
    }
}
void FindDialog::findDataButtonClickedState()
{
    if (find_edit->text().isEmpty()) {
        return;
    }
    QString str = find_edit->text();
    if (next_radio->isChecked()) {
        if (ignore_flag->isChecked()) {
            emit findTextDataButtonClickedSignal(str, true, true);
        } else {
            emit findTextDataButtonClickedSignal(str, false, true);
        }
    }
    if (back_radio->isChecked()) {
        if (ignore_flag->isChecked()) {
            emit findTextDataButtonClickedSignal(str, true, false);
        } else {
            emit findTextDataButtonClickedSignal(str, false, false);
        }
    }
}



















