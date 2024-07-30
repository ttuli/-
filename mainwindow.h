#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextStream>
#include <QTextCharFormat>
#include <QFontDialog>
#include <QColorDialog>
#include "findfun.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool HasChanged();
    void showall();
    bool newopen();
    bool saveFile();

    FindFun *w=nullptr;

private slots:
    void on_action_open_triggered();

    void on_action_add_triggered();

    void on_action_save_triggered();

    void on_action_saveAs_triggered();

    void on_action_copy_triggered();

    void on_action_cut_triggered();

    void on_action_paste_triggered();

    void on_action_find_triggered();

    void on_action_back_triggered();

    void on_action_next_triggered();

    void on_action_atLeft_triggered();

    void on_action_atMid_triggered();

    void on_action_atRight_triggered();

    void on_action_underLine_triggered();

    void on_action_Bold_triggered();

    void on_action_Ita_triggered();

    void on_action_modify_triggered();

    void on_action_color_triggered();

private:
    Ui::MainWindow *ui;

    QString currentFileName=tr("未命名.txt");
    QString path;

protected:
    void closeEvent(QCloseEvent *event) override;

};
#endif // MAINWINDOW_H
