#include "findfun.h"
#include "ui_findfun.h"

FindFun::FindFun(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FindFun)
{
    ui->setupUi(this);
}

FindFun::~FindFun()
{
    delete ui;
}

void FindFun::findFun()
{
    if(p)return;
    list.clear();
    p=true;
    QString tofind=ui->lineEdit->text();
    if(tofind.isEmpty())return;
    content=edit->toPlainText();

    QString test=content;

    int removenum=0;
    while(1)
    {
        int u=test.indexOf(tofind);
        if(u==-1)break;
        test.remove(0,u+tofind.size());
        list<<u+removenum;
        removenum+=u+tofind.size();

    }

    cur=edit->textCursor();
    int curpos=cur.position();

    int l=0,r=list.size()-1;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(list.at(mid)>=curpos)r=mid;
        else l=mid+1;
    }

    currentpos=r;
    highcontent(currentpos);
}

void FindFun::on_pushButton_clicked()
{
    findFun();
    if(!list.size())
    {
        QMessageBox::information(this,"提示","未找到!",QMessageBox::Yes);
    }
}


void FindFun::on_pushButton_2_clicked()
{
    if(!p)return;
    p=false;
    QString tofind=ui->lineEdit->text();
    QString toreplace=ui->lineEdit_2->text();
    if(toreplace.isEmpty()||!list.size())return;

    cur.setPosition(list.at(currentpos));
    cur.setPosition(list.at(currentpos)+tofind.size(),QTextCursor::KeepAnchor);

    cur.removeSelectedText();
    cur.insertText(toreplace);
    findFun();
}


void FindFun::on_pushButton_3_clicked()
{
    if(!list.size()||!p)return;
    if(currentpos-1<=-1)return;
    highcontent(--currentpos);
}


void FindFun::on_pushButton_4_clicked()
{
    if(!list.size()||!p)return;
    if(currentpos+1>=list.size())return;
    highcontent(++currentpos);
}

void FindFun::highcontent(int listpos)
{
    if(-1>=listpos||listpos>=list.size())return;
    QString tofind=ui->lineEdit->text();
    QTextCharFormat format;
    format.setBackground(Qt::white);
    cur.mergeCharFormat(format);
    cur.setPosition(list.at(listpos));
    cur.setPosition(list.at(listpos)+tofind.size(),QTextCursor::KeepAnchor);

    format.setBackground(Qt::yellow);
    cur.mergeCharFormat(format);
}

void FindFun::closeEvent(QCloseEvent *event)
{
    cur.setPosition(0);
    cur.setPosition(std::max((int)edit->toPlainText().size()-1,0),QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setBackground(Qt::white);
    cur.mergeCharFormat(format);
    p=false;
}

