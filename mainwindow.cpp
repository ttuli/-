#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("文档处理");
    ui->label->hide();
    ui->label_name->hide();
    ui->lineEdit_name->hide();
    ui->lineEdit_pos->hide();
    ui->textEdit->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
    if(w)delete w;
    w=nullptr;
}

bool MainWindow::HasChanged()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Warning);
        box.setWindowIcon(QIcon(":/new/prefix1/res/office.png"));
        box.setText(tr("文件已更改,是否保存？"));
        QPushButton *yesbtn=box.addButton(tr("是"),QMessageBox::YesRole);
        box.addButton(tr("否"),QMessageBox::NoRole);
        QPushButton *cancelbtn=box.addButton(tr("取消"),QMessageBox::RejectRole);

        box.exec();

        if(box.clickedButton()==yesbtn)return saveFile();
        if(box.clickedButton()==cancelbtn)return false;
    }
    return true;
}

void MainWindow::showall()
{
    ui->label->show();
    ui->label_name->show();
    ui->lineEdit_name->show();
    ui->lineEdit_pos->show();
    ui->textEdit->show();
}

bool MainWindow::newopen()
{
    path=QFileDialog::getOpenFileName(this,"选择",
                        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    if(path.isEmpty())return false;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","打开失败:"+file.errorString(),QMessageBox::Yes);
        return false;
    }

    QFileInfo info(path);
    ui->lineEdit_name->setText(info.fileName());
    ui->lineEdit_pos->setText(path);

    ui->textEdit->setText(file.readAll());
    file.close();
    return true;
}

bool MainWindow::saveFile()
{
    if(ui->lineEdit_name->isHidden())return false;
    QString p;
    if(ui->lineEdit_pos->text().isEmpty())
    {
        p=QFileDialog::getSaveFileName(this,"选择保存位置",currentFileName);
        if(p.isEmpty())return false;
        ui->lineEdit_pos->setText(p);
    }
    else p=ui->lineEdit_pos->text();
    QFile file(p);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","保存失败:"+file.errorString(),QMessageBox::Yes);
        return false;
    }

    QTextStream stream(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    stream<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    return true;
}

void MainWindow::on_action_open_triggered()
{
    if(HasChanged())
    {
        if(newopen())
        {
            showall();
        }
    }
}


void MainWindow::on_action_add_triggered()
{
    if(!ui->lineEdit_name->isHidden())
    {
        if(HasChanged())
        {
            ui->lineEdit_name->setText("未命名.txt");
            ui->lineEdit_pos->setText("");
            ui->textEdit->clear();
        }
    }
    else
    {
        showall();
        ui->lineEdit_name->setText("未命名.txt");
    }
}


void MainWindow::on_action_save_triggered()
{
    saveFile();
}


void MainWindow::on_action_saveAs_triggered()
{
    QString p=QFileDialog::getSaveFileName(this,"选择保存位置",ui->lineEdit_name->text());

    QFile file(p);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","保存失败:"+file.errorString(),QMessageBox::Yes);
        return;
    }

    QTextStream stream(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    stream<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
}


void MainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_action_cut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_action_paste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_action_find_triggered()
{
    if(ui->lineEdit_name->isHidden())return;
    w=new FindFun;
    w->show();
    w->edit=ui->textEdit;
}


void MainWindow::on_action_back_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_action_next_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_action_atLeft_triggered()
{
    if(ui->action_atLeft->isChecked())
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_action_atMid_triggered()
{
    if(ui->action_atMid->isChecked())
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_action_atRight_triggered()
{
    if(ui->action_atRight->isChecked())
        ui->textEdit->setAlignment(Qt::AlignRight);
}


void MainWindow::on_action_underLine_triggered()
{
    QTextCursor cursor =ui->textEdit->textCursor();

    if ( !cursor.hasSelection() )
    {
        QFont font=ui->textEdit->font();
        font.setUnderline(ui->action_underLine->isChecked());
        ui->textEdit->setFont(font);
    }
    else
    {
        QTextCharFormat format;
        format.setFontUnderline(ui->action_underLine->isChecked());
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_action_Bold_triggered()
{
    QTextCursor cursor =ui->textEdit->textCursor();

    if ( !cursor.hasSelection() )
    {
        QFont font=ui->textEdit->font();
        font.setBold(ui->action_Bold->isChecked());
        ui->textEdit->setFont(font);
    }
    else
    {
        QTextCharFormat format;
        if(ui->action_Bold->isChecked())
        format.setFontWeight(QFont::Bold);
        else format.setFontWeight(QFont::Normal);
        cursor.mergeCharFormat(format);
    }

}


void MainWindow::on_action_Ita_triggered()
{
    QTextCursor cursor =ui->textEdit->textCursor();

    if ( !cursor.hasSelection() )
    {
        QFont font=ui->textEdit->font();
        font.setItalic(ui->action_Ita->isChecked());
        ui->textEdit->setFont(font);
    }
    else
    {
        QTextCharFormat format;
        format.setFontItalic(ui->action_Ita->isChecked());
        cursor.mergeCharFormat(format);
    }
}


void MainWindow::on_action_modify_triggered()
{
    bool u;
    QFont font=QFontDialog::getFont(&u);
    if(!u)return;

    QTextCursor cursor=ui->textEdit->textCursor();

    if(!cursor.hasSelection())
    {
        ui->textEdit->setFont(font);
        return;
    }
    QTextCharFormat format;
    format.setFont(font);

    cursor.mergeCharFormat(format);
}


void MainWindow::on_action_color_triggered()
{
    QTextCharFormat format=ui->textEdit->currentCharFormat();
    QColor color=QColorDialog::getColor(color,this,"请选择颜色");
    if(!color.isValid())return;
    QTextCursor cur=ui->textEdit->textCursor();
    if(!cur.hasSelection())
    cur.select(QTextCursor::Document);

    format.setForeground(color);
    cur.setCharFormat(format);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(w&&!w->isHidden())
        w->hide();
}

