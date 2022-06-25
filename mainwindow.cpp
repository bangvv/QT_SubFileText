#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QTextStream>
#include <QIcon>
#include <QAction>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->maxkitu->setValidator( new QIntValidator(0, 20001, this) );

    clipb = QApplication::clipboard();
    this->setWindowIcon(QIcon(":/Icon/Untitled.ico"));

    menu = menuBar()->addMenu("&Setting");
    auto config = new QAction("Config",this);
    menu->addAction(config);
    connect(config,SIGNAL(triggered()),this,SLOT(on_click_setting_config()));

    loaddata();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatename()));
    timer->start(400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loaddata(){
    QString s;
    QFile f("data.json");
    if(f.exists()){
        f.open(QIODevice::ReadOnly);
        QJsonDocument Doc = QJsonDocument::fromJson(f.readAll());
        QJsonObject obj = (Doc.object());
        if((obj["Setting"]).toObject().contains("pathopen")){
            s = (obj["Setting"]).toObject().value("pathopen").toString();
            _namefile = (obj["Setting"]).toObject().value("name").toString();
            _pathfile = (obj["Setting"]).toObject().value("pathsave").toString();
        }
    }
    f.close();

    ui->Folderin->setText(s);
}
void MainWindow::Receiverchild(){
    this->show();
    loaddata();
}
void MainWindow::updatename() {
    QString name;
    QFile f(QString(_pathfile + "/Vbee - Text To Speech.wav"));
    if (!f.exists())
    {
        ui->Editstate->setText("-------NOK------");
    }
    else{
        count++;
        name =_pathfile +"/" + _namefile + "_p[" + QString::number(count) +"].wav";
        if(f.rename(name)){
            ui->Editstate->setText("OK");
        }
    }
    name = _namefile + "_p[" + QString::number(count+1) +"].wav";
    ui->Editnamefile->setText(name);

    if(a == NULL)
    {
        this->show();
        loaddata();
    }
}

void MainWindow::on_butIN_clicked()
{
    QString p;
    if(ui->Folderin->text() == ""){
        QDir path;
        p = path.path();
    }
    else{
        p = ui->Folderin->text();
    }
    QString dir = QFileDialog::getOpenFileName(this,tr("Chọn file input!"),p,"Text files (*.txt *.doc)");
    ui->Folderin->setText(dir);
}

void MainWindow::on_butRUN_clicked()
{
    if(ui->Folderin->text() == "")
    {
        QMessageBox::information(this,"THÔNG BÁO!","chưa có file input!");
    }
    else if(ui->maxkitu->text().toInt() <= 0)
    {
        QMessageBox::information(this,"THÔNG BÁO!","số kí tự tối đa lỗi!");
    }
    else
    {
        RUN();
    }
}
void MainWindow::RUN()
{
    QString path = ui->Folderin->text();
    QString name;
    for(int i = (int)path.size(); i > 0; --i)
    {
        if(path[i] == '\\' || path[i] == '/')
        {
            name = path.mid(i,((int)path.size()) - i);
        }
    }
    for(int i = (int)name.size(); i > 0; --i)
    {
        if(name[i] == '.')
            name = name.mid(0,i);
    }

    QFile f(path);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray buff = f.readAll();
    QString buffw(buff);
    int stt = 0;
    int skt = (ui->maxkitu->text().toInt());
    int bs = buffw.size();
    int p =  bs/skt;
    int sktn = skt;
    int pos = 0;
    QString pathout;
    QString exten;
    if(ui->rdoc->isChecked())
    {
        exten = ".doc";
    }
    else
        exten = ".txt";
    {
        for(int i = 0 ; i <= p; ++i)
        {
            QString fn = name + "(" + QString::number(stt) + ")"+ exten;
            QFile fout(fn);
            if(!fout.open(QIODevice::ReadWrite))
            {
                break;
            }
            if(i < p){
                QTextStream tout(&fout);
                sktn = checkcp(buff,skt,pos);
                tout.setCodec("UTF-8");
                //tout.setEncoding(QStringConverter::Utf16);
                tout << buffw.mid(pos,sktn-pos);
                pos += sktn-pos;
            }
            else if(i == p)
            {
                QTextStream tout(&fout);
                sktn = checkcp(buff,skt,pos);
                tout.setCodec("UTF-8");
                tout << buffw.mid(pos,bs - pos);
                pos += sktn;
            }
            ++stt;
            fout.close();
        }
    }
    f.close();
}

int MainWindow::checkcp(QString buff, int skt, int pos)
{
    int sktn = skt;
    for(int i = pos+skt; i > pos; --i){
        if(buff[i] == ' ')
        {
            sktn = i;
            break;
        }
    }
    return sktn;

}
void MainWindow::on_click_setting_config()
{
    a = new Dialog(NULL);
    a->show();
}
void MainWindow::on_pushButton_clicked()
{
     QString copy = "";
    {
        if(i < p){
            sktn = checkcp(STRcopy,skt,pos);
             copy = STRcopy.mid(pos,sktn-pos);
            pos += sktn-pos;
        }
        else if(i == p)
        {
            sktn = checkcp(STRcopy,skt,pos);
            copy = STRcopy.mid(pos,bs - pos);
            pos += sktn;
        }
        clipb->setText(copy, QClipboard::Clipboard);
        ++stt;
        ++i;
        ui->stt->setText(QString::number(i));
        BACKUP = copy;
    }
    if(copy.size() != 0)
        ui->lineEdit->setText("thành công!");
    else
       ui->lineEdit->setText("Lỗi!");

}


void MainWindow::on_pushButton_2_clicked()
{
    {
        QString path = ui->Folderin->text();
        QFile f(path);
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QByteArray buff = f.readAll();
        STRcopy = buff;
        f.close();

         stt = 0;
         skt = (ui->maxkitu->text().toInt());
         bs = STRcopy.size();
         p =  bs/skt;
         sktn = skt;
         pos = 0;
         i=0;
         if(bs%skt != 0)
            ui->tong->setText(QString::number(p+1));
         else
            ui->tong->setText(QString::number(p));
         ui->stt->setText(QString::number(i));
         wav = "Vbee - Text To Speech";
    }

}


