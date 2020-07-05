#include "mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QPixmap>
#include <QTextCursor>
#include <QKeySequence>
#include <QFontDialog>
#include <QFont>
#include <QDesktopServices>
#include <QLatin1String>
#include <QTextCodec>
#include <QClipboard>
#include <QApplication>
#include <QTextCursor>
#include <QPoint>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //查找文本框
    find_dialog = new FindDialog(this);
    //替换文本框
    replace_dialog = new replacedialog(this);
    //剪贴板
    clipboard = QApplication::clipboard();

    this->resize(900, 700);
    CreateMenu();
    Creatslots();
}

void MainWindow::CreateMenu()
{
    /* 添加核心控件 */
    textEdit = new QTextEdit(this);
    this->setCentralWidget(textEdit);
    cur_file_name = "";
    sbar = statusBar();
    label = new QLabel(this);

    /* 添加菜单栏 */
    qBar = menuBar();
    //添加菜单--文件
    menu_file = qBar->addMenu("文件(F)");
    menu_file_new = menu_file->addAction("新建(N)");
    menu_file_new->setShortcut(QKeySequence::New);
    menu_file_new_win = menu_file->addAction("新窗口(W)");
    menu_file_open    = menu_file->addAction("打开(O)");
    menu_file_open->setShortcut(QKeySequence::Open);
    menu_file_save    = menu_file->addAction("保存(S)");
    menu_file_save->setShortcut(QKeySequence::Save);
    menu_file_save_as = menu_file->addAction("另存为(S)");
    menu_file_save_as->setShortcut(QKeySequence::SaveAs);
    menu_file->addSeparator();
    menu_file_print = menu_file->addAction("打印(P)");
    menu_file_print->setShortcut(QKeySequence::Print);
    menu_file->addSeparator();
    menu_file_quit  = menu_file->addAction("退出(X)");
    menu_file_quit->setShortcut(QKeySequence::Quit);

    //添加菜单项--编辑
    menu_edit = qBar->addMenu("编辑(E)");
    menu_edit_undo = menu_edit->addAction("撤销(U)");
    menu_edit_undo->setShortcut(QKeySequence::Undo);
    menu_edit_undo->setEnabled(false);
    menu_edit->addSeparator();
    menu_edit_cut    = menu_edit->addAction("剪切(T)");
    menu_edit_cut->setShortcut(QKeySequence::Cut);
    menu_edit_cut->setEnabled(false);
    menu_edit_copy   = menu_edit->addAction("复制(C)");
    menu_edit_copy->setShortcut(QKeySequence::Copy);
    menu_edit_copy->setEnabled(false);
    menu_edit_paste  = menu_edit->addAction("粘贴(P)");
    menu_edit_paste->setShortcut(QKeySequence::Paste);
    menu_edit_delete = menu_edit->addAction("删除(D)");
    menu_edit_delete->setShortcut(QKeySequence::Delete);
    menu_edit_delete->setEnabled(false);
    menu_edit_delete->setShortcut(QKeySequence::Delete);
    menu_edit->addSeparator();
    menu_edit_find    = menu_edit->addAction("查找(F)");
    menu_edit_find->setShortcut(QKeySequence::Find);
    menu_edit_replace = menu_edit->addAction("替换(R)");
    menu_edit_replace->setShortcut(QKeySequence::Replace);
    menu_edit->addSeparator();
    menu_edit_all = menu_edit->addAction("全选(A)");
    menu_edit_all->setShortcut(QKeySequence::SelectAll);

    //添加菜单项--格式
    menu_format = qBar->addMenu("格式(O)");
    menu_format_warp = menu_format->addAction("自动换行(W)");
    menu_format_font = menu_format->addAction("字体(F)");

    //添加菜单项--查看
    menu_view = qBar->addMenu("查看(V)");
    menu_view_zoom_in = menu_view->addAction("放大(Z)");
    menu_view_zoom_in->setShortcut(QKeySequence::ZoomIn);
    menu_view_zoom_out = menu_view->addAction("缩小(Z)");
    menu_view_zoom_out->setShortcut(QKeySequence::ZoomOut);
    menu_view_status = menu_view->addAction("状态栏(S)");

    //添加菜单项--帮助
    menu_help = qBar->addMenu("帮助(H)");
    menu_help_view = menu_help->addAction("查看帮助(H)");
    menu_help_about = menu_help->addAction("关于记事本(A)");
}

void MainWindow::Creatslots()
{
    //菜单 -- 文件
    connect(menu_file_new,     &QAction::triggered, this, &MainWindow::slot_menu_file_new);
    connect(menu_file_new_win, &QAction::triggered, this, &MainWindow::slot_menu_file_new_win);
    connect(menu_file_open,    &QAction::triggered, this, &MainWindow::slot_menu_file_open);
    connect(menu_file_save,    &QAction::triggered, this, &MainWindow::slot_menu_file_save);
    connect(menu_file_save_as, &QAction::triggered, this, &MainWindow::slot_menu_file_save_as);
    connect(menu_file_print,   &QAction::triggered, this, &MainWindow::slot_menu_file_print);
    connect(menu_file_quit,    &QAction::triggered, this, &MainWindow::slot_menu_file_quit);

    //菜单 -- 编辑
    connect(menu_edit_delete,  &QAction::triggered, this, &MainWindow::slot_menu_edit_delete);
    connect(menu_edit_undo,    &QAction::triggered, textEdit, &textEdit->undo);  //使用QTextEdit自带的槽函数
    connect(menu_edit_cut,     &QAction::triggered, textEdit, &textEdit->cut);
    connect(menu_edit_copy,    &QAction::triggered, textEdit, &textEdit->copy);
    connect(menu_edit_paste,   &QAction::triggered, textEdit, &textEdit->paste);
    connect(menu_edit_find,    &QAction::triggered, this, &MainWindow::slot_menu_edit_find);
    connect(menu_edit_replace, &QAction::triggered, this, &MainWindow::slot_menu_edit_replace);
    connect(menu_edit_all,     &QAction::triggered, textEdit, &textEdit->selectAll);

    //菜单 -- 格式
    connect(menu_format_warp, &QAction::triggered, this, &MainWindow::slot_menu_format_warp);
    connect(menu_format_font, &QAction::triggered, this, &MainWindow::slot_menu_format_font);

    //菜单 -- 查看
    connect(menu_view_zoom_in, &QAction::triggered, textEdit, &textEdit->zoomIn);
    connect(menu_view_zoom_out,&QAction::triggered, textEdit, &textEdit->zoomOut);
    connect(menu_view_status,  &QAction::triggered, this, &MainWindow::slot_menu_view_status);

    //菜单 -- 帮助
    connect(menu_help_view,  &QAction::triggered, this, &MainWindow::slot_menu_help_view);
    connect(menu_help_about, &QAction::triggered, this, &MainWindow::slot_menu_help_about);

    //查找、替换
    connect(find_dialog, &FindDialog::findTextDataButtonClickedSignal, this, &MainWindow::findAct);
    connect(replace_dialog, &replacedialog::signal_findReplaceStr, this, &MainWindow::findReplace);
    connect(replace_dialog, &replacedialog::signal_replaceCurOneStr, this, &MainWindow::replaceCur);
    connect(replace_dialog, &replacedialog::signal_replaceAllStr, this, &MainWindow::replaceAll);

    //判断文本框是否已经改变
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::slot_judge_text_state);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::slot_cursor_change_state);
}

//菜单项--文件
void MainWindow::slot_menu_file_new(void)
{
    /*
    * 1、如果文本框是空白的，就直接新建；
    * 2、如果文本框有内容，但内容未修改，则直接新建；
    * 3、如果文本框有内容，且内容被修改过，则询问是否保存。
    */
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton button = QMessageBox::information(this,
        "未保存", "是否保存？", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (button) {
            case QMessageBox::Save:
                save_file();
                if (textEdit->document()->isModified()) {
                    return;
                }
                break;
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Discard:
                break;
            default:
                break;
        }
    }
    textEdit->clear();
}
void MainWindow::slot_menu_file_new_win(void)
{
    MainWindow *new_win = new MainWindow();
    new_win->show();
}
void MainWindow::slot_menu_file_open(void)
{
    /*
    * 1、如果文本框是空的，则直接打开文件；
    * 2、如果文本框有内容，且内容被修改过，则询问是否保存，再打开文件。
    */
    if (textEdit->document()->isModified())
    {
        QMessageBox::StandardButton button = QMessageBox::information(this,
        "未保存", "是否保存？", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (button) {
            case QMessageBox::Save:
                save_file();
                if (textEdit->document()->isModified()) {
                    return;
                }
                break;
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Discard:
                break;
            default:
                break;
        }
    }

    QString file_name = QFileDialog::getOpenFileName(this, "open file", "../", "文本文档(*.txt);;所有文件(*.*)");
    cur_file_name = file_name;
    if (!file_name.isEmpty()) {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QMessageBox::critical(this, "错误", "不能打开文件");
            return;
        }
        QTextStream ins(&file);
        textEdit->setText(ins.readAll());
        file.close();
    }
}
void MainWindow::slot_menu_file_save(void)
{
    /*
    * 1、如果文本框是空的，则直接返回；
    * 2、如果文本框中存在内容，且没有在一个文件中，则询问是否新建个文件保存；
    * 3、如果文本框中存在内容，且已经在一个文件中，则将内容保存进文件。
    */
    if (textEdit->toPlainText().isEmpty()) {
        return;
    }

    if (cur_file_name.isEmpty()) {
        QString file_name =QFileDialog::getSaveFileName(this, "保存文件", "../", "文本文档(*.txt);;所有文件(*.*)");
        if (!file_name.isEmpty()) {
            QFile file(file_name);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, "错误", "不能打开文件");
                return;
            }
            QTextStream outs(&file);
            outs<<textEdit->toPlainText();
            outs.flush();
            file.close();
        }
    } else {
        QFile file(cur_file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "错误", "不能打开文件");
            return;
        }
        QTextStream outs(&file);
        outs<<textEdit->toPlainText();
        outs.flush();
        file.close();
    }
}
void MainWindow::slot_menu_file_save_as(void)
{
    /*
    * 1、如果文本框是空的，则直接返回；
    * 2、如果文本框中存在内容，则询问是否保存。
    */
    if (textEdit->toPlainText().isEmpty()) {
        return;
    }
    QString file_name =QFileDialog::getSaveFileName(this, "保存文件", "../", "文本文档(*.txt);;所有文件(*.*)");
    if (!file_name.isEmpty()) {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "错误", "不能打开文件");
            return;
        }
        QTextStream outs(&file);
        outs << textEdit->toPlainText();
        outs.flush();
        file.close();
    }
}
void MainWindow::slot_menu_file_print(void)
{
    if (textEdit->toPlainText().isEmpty()) {
        return;
    }
    QPrinter printer;
    QString printer_name = printer.printerName();
    QPrintDialog print_dlg(&printer, this);
    if (printer_name.size() == 0) {
        return;
    }
    if (textEdit->textCursor().hasSelection()) {
        print_dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    if (print_dlg.exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
}
void MainWindow::slot_menu_file_quit(void)
{
    this->close();
}

//菜单项--编辑
void MainWindow::slot_menu_edit_delete(void)
{
    textEdit->cut();
    clipboard->setText("");
}
void MainWindow::slot_menu_edit_replace(void)
{
    replace_dialog->show();
}
void MainWindow::slot_menu_edit_find(void)
{
    find_dialog->show();
}

//菜单项--格式
void MainWindow::slot_menu_format_warp(void)
{

}
void MainWindow::slot_menu_format_font(void)
{
    QFontDialog font_dialog;
    font_dialog.show();
    QFont inifont = textEdit->font();
    bool ok = false;
    QFont font = font_dialog.getFont(&ok, inifont);
    if (ok) {
        textEdit->setFont(font);
    }
    font_dialog.close();
}

//菜单项--查看
void MainWindow::slot_menu_view_status(void)
{

}

//菜单项--帮助
void MainWindow::slot_menu_help_view(void)
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://www.cnblogs.com/mrlayfolk/p/13167219.html")));
}
void MainWindow::slot_menu_help_about(void)
{
    QMessageBox message(QMessageBox::NoIcon, "关于", ("version: v1.0\nauthor: zzq\nqq: 544705365"));
    message.exec();
}


//保存文件
void MainWindow::save_file()
{
    if (cur_file_name.isEmpty()) {
        QString file_name =QFileDialog::getSaveFileName(this, "保存文件", "../", "文本文档(*.txt);;所有文件(*.*)");
        if (!file_name.isEmpty()) {
            QFile file(file_name);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, "错误", "不能打开文件");
                return;
            }
            QTextStream outs(&file);
            outs<<textEdit->toPlainText();
            outs.flush();
            file.close();
            textEdit->document()->setModified(false);
        }
    } else {
        QFile file(cur_file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "错误", "不能打开文件");
            return;
        }
        QTextStream outs(&file);
        outs<<textEdit->toPlainText();
        outs.flush();
        file.close();
        textEdit->document()->setModified(false);
    }
}

//查找
void MainWindow::findAct(QString str_key, bool ignore_case, bool choose_direction)
{
    /*
    * 参数str_key：查找的关键字，支持中文
    * 参数ignore_case：是否区分大小写
    * 参数choose_direction：向前或向后查找，true：向前；false：先后；
    */
    bool find_flag;
    if (!str_key.isEmpty()) {
        if (choose_direction) {
            if (ignore_case) {
                find_flag = textEdit->find(str_key, QTextDocument::FindCaseSensitively);
            } else {
                find_flag = textEdit->find(str_key);
            }
        } else {
            if (ignore_case) {
                find_flag = textEdit->find(str_key, QTextDocument::FindBackward|QTextDocument::FindCaseSensitively);
            } else {
                find_flag = textEdit->find(str_key, QTextDocument::FindBackward);
            }
        }
        if (!find_flag) {
            QMessageBox::information(this, "结果", "没有找到查找内容", QMessageBox::Yes);
        }
    }
}
//替换
void MainWindow::findReplace(QString find_str, bool ignore_flg)
{
    /*
    * 参数find_str：查找关键字
    * 参数ignore_flg：区分大小写
    */
    bool find_flag;
    if (ignore_flg) {
        find_flag = textEdit->find(find_str, QTextDocument::FindCaseSensitively);
    } else {
        find_flag = textEdit->find(find_str);
    }
    if (!find_flag) {
        QMessageBox::information(this, "结果", "没有找到查找内容", QMessageBox::Yes);
    } else {
        find = true;
    }
}
void MainWindow::replaceCur(QString find_str, QString replace_str)
{
    /*
    * 参数find_str：查找的关键字；
    * 参数replace_str：替换的关键字
    */
    QTextCursor text_cursor;
    if (find) {
        text_cursor = textEdit->textCursor();
        text_cursor.insertText(replace_str);
    } else {
        QMessageBox::information(this, "结果", "没有内容，不能替换"+find_str, QMessageBox::Yes);
    }
    find = false;
}
void MainWindow::replaceAll(QString find_str, QString replace_str, bool ignore_flg)
{
    /*
    * 参数find_str：查找关键字
    * 参数replace_str：替换关键字
    * 参数ignore_flg：是否忽略大小写
    */
    QTextCursor text_cursor;
    if (!ignore_flg) {
        bool haf = textEdit->find(find_str);
        if (haf) {
            text_cursor = textEdit->textCursor();
            text_cursor.insertText(replace_str);
            while (textEdit->find(find_str)) {
                text_cursor = textEdit->textCursor();
                text_cursor.insertText(replace_str);
            }
            while (textEdit->find(find_str, QTextDocument::FindBackward)) {
                text_cursor = textEdit->textCursor();
                text_cursor.insertText(replace_str);
            }
        } else {
            QMessageBox::information(this, "结果", "没有内容，不能替换"+find_str, QMessageBox::Yes);
        }
    } else {
        bool haf = textEdit->find(find_str, QTextDocument::FindCaseSensitively);
        if (haf) {
            text_cursor = textEdit->textCursor();
            text_cursor.insertText(replace_str);
            while (textEdit->find(find_str, QTextDocument::FindCaseSensitively)) {
                text_cursor = textEdit->textCursor();
                text_cursor.insertText(replace_str);
            }
            while (textEdit->find(find_str, QTextDocument::FindCaseSensitively|QTextDocument::FindBackward)) {
                text_cursor = textEdit->textCursor();
                text_cursor.insertText(replace_str);
            }
        } else {
            QMessageBox::information(this, "结果", "没有内容，不能替换"+find_str, QMessageBox::Yes);
        }
    }
}

void MainWindow::slot_judge_text_state()
{
    if (textEdit->toPlainText().isEmpty()) {
        menu_edit_undo->setEnabled(false);
        menu_edit_cut->setEnabled(false);
        menu_edit_copy->setEnabled(false);
        menu_edit_delete->setEnabled(false);
    } else {
        menu_edit_undo->setEnabled(true);
        menu_edit_cut->setEnabled(true);
        menu_edit_copy->setEnabled(true);
        menu_edit_delete->setEnabled(true);
    }
}

void MainWindow::slot_cursor_change_state()
{
    /* 添加状态栏 */
    int pos;
    pos = textEdit->textCursor().position();
    sbar_str = QString("第%1个字符").arg(pos);
    sbar->showMessage(sbar_str);
}

MainWindow::~MainWindow()
{

}


