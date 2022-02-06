#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket= new QTcpSocket(this);
    mSocket->connectToHost("localhost",2000);


    if(mSocket->waitForConnected(3000))
    {
        ui->textEdit->append("connection is ok");
    }

    else
    {
        ui->textEdit->append("out of connection,\n\t\t please, try again.");

    }
 connect(mSocket,SIGNAL(readyRead()),this,SLOT(Read()));

}
void MainWindow::Read()
{
    QByteArray buffer;
    buffer.resize(mSocket->bytesAvailable());
    mSocket->read(buffer.data(),buffer.size());
    ui->textEdit->setReadOnly(true);
    ui->textEdit->append( "<font color=red>"+ QString(buffer)+"</font>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mSocket->write(ui->lineEdit->text().toUtf8().data(),ui->lineEdit->text().size());
    ui->textEdit->append( "\t\t\t" + ui->lineEdit->text());
    ui->lineEdit->clear();
}

