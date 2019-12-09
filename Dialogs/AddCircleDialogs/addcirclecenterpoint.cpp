#include "addcirclecenterpoint.h"
#include "ui_addcirclecenterpoint.h"

AddCircleCenterPoint::AddCircleCenterPoint(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCircleCenterPoint)
{
    connect(this, SIGNAL(add_circle(int, std::string, std::string, std::string)), parent, SLOT(add_circle(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->point1ComboBox->addItem(QString::fromStdString(*it));
        ui->point2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddCircleCenterPoint::~AddCircleCenterPoint()
{
    delete ui;
}

void AddCircleCenterPoint::on_buttonBox_accepted()
{
    emit add_circle(1, geo1, geo2, label);
}

void AddCircleCenterPoint::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddCircleCenterPoint::on_point1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddCircleCenterPoint::on_point2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
