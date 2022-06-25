#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void on_pushButton_clicked();

    void on_foldersave_clicked();

    void on_folderopen_clicked();
signals:
    void updateparent();
private:

    Ui::Dialog *ui;
    bool state {false};
};

#endif // DIALOG_H
