#include "addpointintersect.h"
#include "ui_addpointintersect.h"

AddPointIntersect::AddPointIntersect(std::vector<std::string> *lines, std::vector<std::string> *circles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointIntersect),
    lines(lines)
{
    connect(this, SIGNAL(add_point(int, std::string, std::string, std::string)), parent, SLOT(add_point(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = lines->begin(); it != lines->end(); ++it){
        ui->construction1ComboBox->addItem(QString::fromStdString(*it));
        ui->construction2ComboBox->addItem(QString::fromStdString(*it));
    }

    for(auto it = circles->begin(); it != circles->end(); ++it){
        ui->construction1ComboBox->addItem(QString::fromStdString(*it));
        ui->construction2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddPointIntersect::~AddPointIntersect()
{
    delete ui;
}

void AddPointIntersect::on_buttonBox_accepted()
{
    bool is_line1 = false, is_line2 = false;
    for(auto it = lines->begin(); it != lines->end(); ++it){
        if(geo1 == (*it)){is_line1 = true;}
        if(geo2 == (*it)){is_line2 = true;}
    }

    if(is_line1 && is_line2){
        emit add_point(4, geo1, geo2, label);
        return;
    }

    if(is_line1 && (!is_line2)){
        emit add_point(5, geo1, geo2, label);
        return;
    }

    if((!is_line1) && is_line2){
        emit add_point(5, geo2, geo1, label);
        return;
    }

    if((!is_line1) && (!is_line2)){
        emit add_point(7, geo1, geo2, label);
        return;
    }
}

void AddPointIntersect::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointIntersect::on_construction1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddPointIntersect::on_construction2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
