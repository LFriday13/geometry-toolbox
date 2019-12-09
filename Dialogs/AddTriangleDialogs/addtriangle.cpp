#include "addtriangle.h"
#include "ui_addtriangle.h"

AddTriangle::AddTriangle(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTriangle)
{
    connect(this, SIGNAL(add_triangle(int, std::string, std::string, std::string, std::string)), parent, SLOT(add_triangle(int, std::string, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->pointAComboBox->addItem(QString::fromStdString(*it));
        ui->pointBComboBox->addItem(QString::fromStdString(*it));
        ui->pointCComboBox->addItem(QString::fromStdString(*it));
    }
}

AddTriangle::~AddTriangle()
{
    delete ui;
}

void AddTriangle::on_buttonBox_accepted()
{
    emit add_triangle(type, geo1, geo2, geo3, label);
}

void AddTriangle::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddTriangle::on_pointAComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddTriangle::on_pointBComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}

void AddTriangle::on_pointCComboBox_currentTextChanged(const QString &arg1)
{
    geo3 = arg1.toStdString();
}
