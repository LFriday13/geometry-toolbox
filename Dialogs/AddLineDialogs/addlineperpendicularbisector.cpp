#include "addlineperpendicularbisector.h"
#include "ui_addlineperpendicularbisector.h"

AddLinePerpendicularBisector::AddLinePerpendicularBisector(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLinePerpendicularBisector)
{
    connect(this, SIGNAL(add_line(int, std::string, std::string, std::string)), parent, SLOT(add_line(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->point1ComboBox->addItem(QString::fromStdString(*it));
        ui->point2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddLinePerpendicularBisector::~AddLinePerpendicularBisector()
{
    delete ui;
}

void AddLinePerpendicularBisector::on_buttonBox_accepted()
{
    emit add_line(2, geo1, geo2, label);
}

void AddLinePerpendicularBisector::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddLinePerpendicularBisector::on_point1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddLinePerpendicularBisector::on_point2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
