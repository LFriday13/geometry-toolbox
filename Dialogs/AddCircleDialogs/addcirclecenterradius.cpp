#include "addcirclecenterradius.h"
#include "ui_addcirclecenterradius.h"

AddCircleCenterRadius::AddCircleCenterRadius(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCircleCenterRadius)
{
    connect(this, SIGNAL(add_circle(int, std::string, std::string, std::string, std::string)), parent, SLOT(add_circle(int, std::string, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->point1ComboBox->addItem(QString::fromStdString(*it));
        ui->point2ComboBox->addItem(QString::fromStdString(*it));
        ui->point3ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddCircleCenterRadius::~AddCircleCenterRadius()
{
    delete ui;
}

void AddCircleCenterRadius::on_buttonBox_accepted()
{
    emit add_circle(2, geo1, geo2, geo3, label);
}

void AddCircleCenterRadius::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddCircleCenterRadius::on_point1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddCircleCenterRadius::on_point2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}

void AddCircleCenterRadius::on_point3ComboBox_currentTextChanged(const QString &arg1)
{
    geo3 = arg1.toStdString();
}
