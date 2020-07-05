#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QString>

class replacedialog : public QDialog
{
    Q_OBJECT
public:
    explicit replacedialog(QWidget *parent = nullptr);

signals:
    void signal_replaceAllStr(QString, QString, bool);
    void signal_replaceCurOneStr(QString, QString);
    void signal_findReplaceStr(QString, bool);

public slots:
    void slot_choose_str();
    void slot_find_button_state();
    void slot_replace_one_button_state();
    void slot_repalce_all_button_state();

private:
    QLineEdit *find_str;
    QLineEdit *replace_str;
    QPushButton *find_next_button;
    QPushButton *replace_one_button;
    QPushButton *replace_all_button;
    QPushButton *cancel_button;
    QCheckBox *ignore_flag;
    QLabel *find_label;
    QLabel *replace_label;

};

#endif // REPLACEDIALOG_H
