#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMenu *menu;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
        QClipboard *clipb;
    int stt { 0};
    int skt {0};
    int bs {0};
    int p {0};
    int sktn {0};
    int pos { 0};
    int i {0};

private slots:
    void on_butIN_clicked();

    void on_butRUN_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_click_setting_config();
    void updatename();
    void Receiverchild();
signals:
    void SendNotifyClickMenuSetting();

private:
    void RUN();
    int checkcp(QString buff,int skt, int pos = 0);
    Ui::MainWindow *ui;
    QString wav {""};
    QString STRcopy {""};
    bool dk2 {false};
    QString BACKUP {""};
    QString _namefile {""};
    QString _pathfile {""};
    int count {0};

    void loaddata();

    Dialog *a {NULL};
};
#endif // MAINWINDOW_H
