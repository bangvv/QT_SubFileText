#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDataStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString pathfolder1 = "";
    QString pathfolder2 = "";
    QString name = "";
    QFile f("data.json");
    if(f.exists()){
        f.open(QIODevice::ReadOnly);
        QJsonDocument Doc = QJsonDocument::fromJson(f.readAll());
        QJsonObject obj = (Doc.object());
        if((obj["Setting"]).toObject().contains("pathopen")){
            pathfolder1 = (obj["Setting"]).toObject().value("pathopen").toString();
            name = (obj["Setting"]).toObject().value("name").toString();
            pathfolder2 = (obj["Setting"]).toObject().value("pathsave").toString();
        }
    }
    f.close();
    ui->editfoldersave->setText(pathfolder2);
    ui->editfolderopen->setText(pathfolder1);
    ui->editnamefile->setText(name);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->editnamefile->text() == "")
        ui->editnamefile->setText("Truyen_P");
    if(ui->editfoldersave->text() == "" || ui->editfolderopen->text() == "")
        QMessageBox::information(this,"THÔNG BÁO LỖI!","Folder save and open file!");
    else{
        QJsonObject obj;
        obj["pathsave"] = ui->editfoldersave->text();
        obj["name"] = ui->editnamefile->text();
        obj["pathopen"] = ui->editfolderopen->text();
        QJsonObject r;
        r["Setting"] = obj;

        QJsonDocument doc(r);

        QString s(doc.toJson());

        QString buff = s;

        //SAVE FILE JSON
        QFile f("data.json");
        if(!f.open(QIODevice::ReadWrite))
            return;
        QTextStream out(&f);
        out << buff;
        f.close();
        this->close();
    }

}


void Dialog::on_foldersave_clicked()
{
    QFile f("data.json");

    QString pathfolder;
    if(f.exists()){
        f.open(QIODevice::ReadOnly);
        QJsonDocument Doc = QJsonDocument::fromJson(f.readAll());
        QJsonObject obj = (Doc.object());
        if((obj["Setting"]).toObject().contains("pathsave")){
            pathfolder = (obj["Setting"]).toObject().value("pathsave").toString();
        }
    }
    else{
        QDir path;
        pathfolder = path.path();
    }
    //QString dir = QFileDialog::getOpenFileName(this,tr("Chọn file input!"),path.path(),"Text files (*.txt *.doc)");
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),pathfolder,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->editfoldersave->setText(dir);
}


void Dialog::on_folderopen_clicked()
{
    QFile f("data.json");

    QString pathfolder;
    if(f.exists()){
        f.open(QIODevice::ReadOnly);
        QJsonDocument Doc = QJsonDocument::fromJson(f.readAll());
        QJsonObject obj = (Doc.object());
        if((obj["Setting"]).toObject().contains("pathopen")){
            pathfolder = (obj["Setting"]).toObject().value("pathopen").toString();
        }
    }
    else{
        QDir path;
        pathfolder = path.path();
    }
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),pathfolder,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->editfolderopen->setText(dir);
}

