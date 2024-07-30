#ifndef FINDFUN_H
#define FINDFUN_H

#include <QWidget>
#include <QTextEdit>
#include <QCloseEvent>
#include <iostream>
#include <QMessageBox>

namespace Ui {
class FindFun;
}

class FindFun : public QWidget
{
    Q_OBJECT

public:
    explicit FindFun(QWidget *parent = nullptr);
    ~FindFun();
    QString content;

    void findFun();

    const QTextEdit *edit=nullptr;

    QTextCursor cur;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::FindFun *ui;

    QList<int> list;

    void highcontent(int listpos);

    int currentpos;

    bool p=false;

protected:
    void closeEvent(QCloseEvent *event) override;

};

#endif // FINDFUN_H
