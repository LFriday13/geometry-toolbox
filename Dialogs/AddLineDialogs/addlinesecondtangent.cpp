#include "addlinesecondtangent.h"
#include "ui_addlinesecondtangent.h"

AddLineSecondTangent::AddLineSecondTangent(std::vector<std::string> *points, std::vector<std::string> *circles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineSecondTangent)
{
    connect(this, SIGNAL(add_line(int, std::string, std::string, std::string)), parent, SLOT(add_line(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->pointComboBox->addItem(QString::fromStdString(*it));
    }

    for(auto it = circles->begin(); it != circles->end(); ++it){
        ui->circleComboBox->addItem(QString::fromStdString(*it));
    }
}

AddLineSecondTangent::~AddLineSecondTangent()
{
    delete ui;
}

void AddLineSecondTangent::on_buttonBox_accepted()
{
    emit add_line(4, geo1, geo2, label);
}

void AddLineSecondTangent::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddLineSecondTangent::on_pointComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddLineSecondTangent::on_circleComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
