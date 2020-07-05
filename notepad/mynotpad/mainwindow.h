#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QTextEdit>
#include <QStatusBar>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "finddialog.h"
#include "replacedialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //常用函数
    void CreateMenu();  //创建主菜单
    void Creatslots();  //创建各组件的槽函数
    void save_file();   //保存文件

    /* 槽函数 */
    //菜单项--文件相关功能：新建、新建新窗口、打卡、保存、另存、打印、退出
    void slot_menu_file_new(void);
    void slot_menu_file_new_win(void);
    void slot_menu_file_open(void);
    void slot_menu_file_save(void);
    void slot_menu_file_save_as(void);
    void slot_menu_file_print(void);
    void slot_menu_file_quit(void);

    //菜单项--编辑相关功能：撤销、剪切、复制、粘贴、删除、查找、替换、全选
    void slot_menu_edit_undo(void);
    void slot_menu_edit_cut(void);
    void slot_menu_edit_copy(void);
    void slot_menu_edit_paste(void);
    void slot_menu_edit_delete(void);
    void slot_menu_edit_find();
    void slot_menu_edit_replace(void);
    void slot_menu_edit_all(void);

    //菜单项--格式相关功能：自动换行、格式
    void slot_menu_format_warp(void);
    void slot_menu_format_font(void);

    //菜单项--查看相关功能：放大、缩小、状态栏
    void slot_menu_view_zoon_in(void);
    void slot_menu_view_zoon_out(void);
    void slot_menu_view_status(void);

    //菜单项--帮助相关功能：查看帮助、关于
    void slot_menu_help_view(void);
    void slot_menu_help_about(void);

    //查找、替换
    void findAct(QString, bool, bool);
    void findReplace(QString, bool);
    void replaceCur(QString, QString);
    void replaceAll(QString, QString, bool);

    //文本状态发生变化时调用
    void slot_judge_text_state();
    //文本中的鼠标发生状态时调用
    void slot_cursor_change_state();

private:
    QTextEdit *textEdit;
    QString cur_file_name;
    QString sbar_str;  //状态栏

    /* 添加菜单栏 */
    QMenuBar *qBar;
    //菜单--文件
    QMenu *menu_file;
    QAction *menu_file_new;
    QAction *menu_file_new_win;
    QAction *menu_file_open;
    QAction *menu_file_save;
    QAction *menu_file_save_as;
    QAction *menu_file_print;
    QAction *menu_file_quit;

    //菜单--编辑
    QMenu *menu_edit;
    QAction *menu_edit_undo;
    QAction *menu_edit_cut;
    QAction *menu_edit_copy;
    QAction *menu_edit_paste;
    QAction *menu_edit_delete;
    QAction *menu_edit_find;
    QAction *menu_edit_replace;
    QAction *menu_edit_all;

    //菜单--格式
    QMenu *menu_format;
    QAction *menu_format_warp;
    QAction *menu_format_font;

    //菜单--查看
    QMenu *menu_view;
    QAction *menu_view_zoom_in;
    QAction *menu_view_zoom_out;
    QAction *menu_view_status;

    //菜单--帮助
    QMenu *menu_help;
    QAction *menu_help_view;
    QAction *menu_help_about;

    /* 添加状态栏 */
    QStatusBar *sbar;
    QLabel *label;

    /* 查找替换 */
    bool find;
    FindDialog *find_dialog;
    replacedialog *replace_dialog;

    /* 剪贴板 */
    QClipboard *clipboard;
};

#endif // MAINWINDOW_H
