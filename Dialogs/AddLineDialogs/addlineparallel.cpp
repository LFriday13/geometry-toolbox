#include "addlineparallel.h"
#include "ui_addlineparallel.h"

AddLineParallel::AddLineParallel(std::vector<std::string> *points, std::vector<std::string> *lines, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineParallel)
{
    connect(this, SIGNAL(add_line(int, std::string, std::string, std::string)), parent, SLOT(add_line(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->pointComboBox->addItem(QString::fromStdString(*it));
    }

    for(auto it = lines->begin(); it != lines->end(); ++it){
        ui->lineComboBox->addItem(QString::fromStdString(*it));
    }
}

AddLineParallel::~AddLineParallel()
{
    delete ui;
}

void AddLineParallel::on_buttonBox_accepted()
{
    emit add_line(1, geo1, geo2, label);
}

void AddLineParallel::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddLineParallel::on_pointComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddLineParallel::on_lineComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
