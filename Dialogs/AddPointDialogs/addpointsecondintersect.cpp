#include "addpointsecondintersect.h"
#include "ui_addpointsecondintersect.h"

AddPointSecondIntersect::AddPointSecondIntersect(std::vector<std::string> *lines, std::vector<std::string> *circles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointSecondIntersect),
    lines(lines)
{
    connect(this, SIGNAL(add_point(int, std::string, std::string, std::string)), parent, SLOT(add_point(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = lines->begin(); it != lines->end(); ++it){
        ui->construction1ComboBox->addItem(QString::fromStdString(*it));
    }

    for(auto it = circles->begin(); it != circles->end(); ++it){
        ui->construction1ComboBox->addItem(QString::fromStdString(*it));
        ui->construction2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddPointSecondIntersect::~AddPointSecondIntersect()
{
    delete ui;
}

void AddPointSecondIntersect::on_buttonBox_accepted()
{
    bool is_line1 = false;
    for(auto it = lines->begin(); it != lines->end(); ++it){
        if(geo1 == (*it)){is_line1 = true;}
    }

    if(is_line1){
        emit add_point(6, geo1, geo2, label);
    } else {
        emit add_point(8, geo1, geo2, label);
    }

}

void AddPointSecondIntersect::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointSecondIntersect::on_construction1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddPointSecondIntersect::on_construction2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
