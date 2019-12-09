#include "addpointmidpoint.h"
#include "ui_addpointmidpoint.h"

AddPointMidpoint::AddPointMidpoint(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointMidpoint)
{
    connect(this, SIGNAL(add_point(int, std::string, std::string, std::string)), parent, SLOT(add_point(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->point1ComboBox->addItem(QString::fromStdString(*it));
        ui->point2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddPointMidpoint::~AddPointMidpoint()
{
    delete ui;
}

void AddPointMidpoint::on_buttonBox_accepted()
{
    emit add_point(3, geo1, geo2, label);
}

void AddPointMidpoint::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointMidpoint::on_point1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddPointMidpoint::on_point2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}

