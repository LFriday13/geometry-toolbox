#include "addpointindependent.h"
#include "ui_addpointindependent.h"
#include "mainwindow.h"

AddPointIndependent::AddPointIndependent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointIndependent)
{
    connect(this, SIGNAL(add_point(int, double, double, std::string)), parent, SLOT(add_point(int, double, double,std::string)));
    ui->setupUi(this);
}

AddPointIndependent::~AddPointIndependent()
{
    delete ui;
}

void AddPointIndependent::on_buttonBox_accepted()
{
    emit add_point(0, x, y, label);
}

void AddPointIndependent::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointIndependent::on_xLineEdit_textEdited(const QString &arg1)
{
    x = arg1.toDouble();
}

void AddPointIndependent::on_yLineEdit_textEdited(const QString &arg1)
{
    y = arg1.toDouble();
}
