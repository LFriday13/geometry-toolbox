#include "addlinefirsttangent.h"
#include "ui_addlinefirsttangent.h"

AddLineFirstTangent::AddLineFirstTangent(std::vector<std::string> *points, std::vector<std::string> *circles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineFirstTangent)
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

AddLineFirstTangent::~AddLineFirstTangent()
{
    delete ui;
}

void AddLineFirstTangent::on_buttonBox_accepted()
{
    emit add_line(3, geo1, geo2, label);
}

void AddLineFirstTangent::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddLineFirstTangent::on_pointComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddLineFirstTangent::on_circleComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
