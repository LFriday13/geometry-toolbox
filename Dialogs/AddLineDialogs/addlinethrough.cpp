#include "addlinethrough.h"
#include "ui_addlinethrough.h"

AddLineThrough::AddLineThrough(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineThrough)
{
    connect(this, SIGNAL(add_line(int, std::string, std::string, std::string)), parent, SLOT(add_line(int, std::string, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->point1ComboBox->addItem(QString::fromStdString(*it));
        ui->point2ComboBox->addItem(QString::fromStdString(*it));
    }
}

AddLineThrough::~AddLineThrough()
{
    delete ui;
}

void AddLineThrough::on_buttonBox_accepted()
{
    emit add_line(0, geo1, geo2, label);
}

void AddLineThrough::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddLineThrough::on_point1ComboBox_currentTextChanged(const QString &arg1)
{
    geo1 = arg1.toStdString();
}

void AddLineThrough::on_point2ComboBox_currentTextChanged(const QString &arg1)
{
    geo2 = arg1.toStdString();
}
