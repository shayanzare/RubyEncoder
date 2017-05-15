#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"

#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    Highlighter *highlighter = new Highlighter(ui->textEdit->document());
    Highlighter *highlighter2 = new Highlighter(ui->textEdit_2->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString base64_encode(QString string){
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    QString res = base64_encode(text);
    ui->textEdit_2->setText("require \"base64\"\n"
                            "code = \"" + res + "\"\n"
                            "dec_code = Base64.decode64(code)\n"
                            "result = eval(dec_code)\n"
                            "puts result\n");
}

void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::about(this, "About :", "\nCoded By Virus007\nTelegram ID: @Msf_Payload\n");
}

void MainWindow::on_actionOpen_Ruby_Script_triggered()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("Open Ruby File :") , "~/", tr("Ruby File (*.rb , *.rbw)"));
    qDebug() << fileUrl;

    //open file
    QFile file(fileUrl);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        ui->textEdit->setText(file.readAll());
    }
    else
    {
        QMessageBox::warning(this,"Error :" , "\nError To Opening File!");
    }
}

void MainWindow::on_actionClose_triggered()
{
    //clear all textbox
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
