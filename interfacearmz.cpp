#include "interfacearmz.h"
#include "ui_interfacearmz.h"
#include <QtGui>
#include <objetos.h>
#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>

interfaceArmz::interfaceArmz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interfaceArmz)
{
    ui->setupUi(this);
}

interfaceArmz::~interfaceArmz()
{
    delete ui;
}

void interfaceArmz::iniciarUi(){
    ui->dia->setValidator(new QIntValidator(1, 31, this));
    ui->mes->setValidator(new QIntValidator(1, 12, this));
    ui->ano->setValidator(new QIntValidator(1901, 2099, this));
    ui->dia_2->setValidator(new QIntValidator(1, 31, this));
    ui->mes_2->setValidator(new QIntValidator(1, 12, this));
    ui->ano_2->setValidator(new QIntValidator(1901, 2099, this));
    ui->hora->setValidator(new QIntValidator(0, 24, this));
    ui->hora_2->setValidator(new QIntValidator(0, 24, this));
    ui->min->setValidator(new QIntValidator(0, 59, this));
    ui->min_2->setValidator(new QIntValidator(0, 59, this));
    ui->seg->setValidator(new QIntValidator(0, 59, this));
    ui->seg_2->setValidator(new QIntValidator(0, 59, this));
}

std::string zeroAdder(std::string temp, unsigned int n){
    while(temp.length() < n){
        temp = "0"+temp;
    }
    return temp;
}

void interfaceArmz::on_pushButton_clicked()
{
    std::string temp, data, hora, data1, data2, hora1, hora2;
    temp = ui->dia->text().toStdString();
    temp = zeroAdder(temp, 2);
    data = "-" + temp;
    temp = ui->mes->text().toStdString();
    temp = zeroAdder(temp, 2);
    data = "-" + temp + data;
    temp = ui->ano->text().toStdString();
    temp = zeroAdder(temp, 4);
    data = temp + data;
    data1 = data;

    temp = ui->dia_2->text().toStdString();
    temp = zeroAdder(temp, 2);
    data = "-" + temp;
    temp = ui->mes_2->text().toStdString();
    temp = zeroAdder(temp, 2);
    data = "-" + temp + data;
    temp = ui->ano_2->text().toStdString();
    temp = zeroAdder(temp, 4);
    data = temp + data;
    data2 = data;

    temp = ui->hora->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = temp + ":";
    temp = ui->min->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = hora + temp + ":";
    temp = ui->seg->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = hora + temp;
    hora1 = hora;

    temp = ui->hora_2->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = temp + ":";
    temp = ui->min_2->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = hora + temp + ":";
    temp = ui->seg_2->text().toStdString();
    temp = zeroAdder(temp, 2);
    hora = hora + temp;
    hora2 = hora;

    //fprintf(stderr, "DATA 1: %s h: %s \tDATA 2: %s h: %s\n", data1.c_str(), hora1.c_str(), data2.c_str(), hora2.c_str());
    dealQuery queryObj;
    queryObj.set_str("SELECT * FROM ap16 where TIMESTAMP between '" + data1 + " " + hora1 + "' and '" + data2 + " " + hora2 + "'");
    fprintf(stderr, "QUERY: %s\n", queryObj.get().c_str());

}

void interfaceArmz::on_actionCarregarMapa_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
}


bool interfaceArmz::sair () {
    QMessageBox msgBox(QMessageBox::Question, "Sair?", "Você tem certeza que deseja sair?", QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, "Sim");
    msgBox.setButtonText(QMessageBox::No, "Não");

    if (msgBox.exec() == QMessageBox::Yes) {
        return(1);
    }
    else return 0;
}

void interfaceArmz::on_actionSair_triggered()
{
    if(sair()) exit(1);
}

void interfaceArmz::on_pushButton_2_clicked()
{
    if(sair()) exit(1);
}
