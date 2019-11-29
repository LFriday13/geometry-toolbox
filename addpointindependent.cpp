#include "addpointindependent.h"
#include "ui_addpointindependent.h"

AddPointIndependent::AddPointIndependent(MainWindow* dummy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointIndependent)
{
    connect(this, SIGNAL(add_point(int, double, double, std::string)), dummy, SLOT(add_point(int,double,double,std::string)));
    ui->setupUi(this);
}

AddPointIndependent::~AddPointIndependent()
{
    delete ui;
}

void AddPointIndependent::on_button_box_accepted()
{
    emit add_point(0,x,y,label);
}

void AddPointIndependent::on_x_textEdited(const QString &arg1)
{
    x = arg1.toDouble();
}

void AddPointIndependent::on_y_textEdited(const QString &arg1)
{
    y = arg1.toDouble();
}

void AddPointIndependent::on_label_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}
