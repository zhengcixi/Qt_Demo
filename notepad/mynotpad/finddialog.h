#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QDialog>

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = nullptr);

signals:
    //参数：查找关键字、是否区分大小写、向前或向后查找
    void findTextDataButtonClickedSignal(QString, bool, bool);

public slots:
    void findButtonState();
    void findDataButtonClickedState();

private:
    QLineEdit *find_edit;
    QLabel *find_label, *ignore_label, *next_label, *back_label;
    QPushButton  *find_button;
    QRadioButton *next_radio;
    QRadioButton *back_radio;
    QCheckBox *ignore_flag;
};

#endif // FINDDIALOG_H
