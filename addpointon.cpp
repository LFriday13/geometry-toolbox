#include "addpointon.h"
#include "ui_addpointon.h"

AddPointOn::AddPointOn(std::vector<std::string>* lines, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointOn)
{
    connect(this, SIGNAL(add_point(int, std::string, double, double, std::string)), parent, SLOT(add_point(int, std::string, double, double,std::string)));
    ui->setupUi(this);

    for(auto it = lines->begin(); it != lines->end(); ++it){
        ui->lineComboBox->addItem(QString::fromStdString(*it));
    }
}

AddPointOn::~AddPointOn()
{
    delete ui;
}

void AddPointOn::on_buttonBox_accepted()
{
    emit add_point(1, geo, x, y, label);
}

void AddPointOn::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointOn::on_xLineEdit_textEdited(const QString &arg1)
{
    x = arg1.toDouble();
}

void AddPointOn::on_yLineEdit_textEdited(const QString &arg1)
{
    y = arg1.toDouble();
}

void AddPointOn::on_lineComboBox_currentTextChanged(const QString &arg1)
{
    geo = arg1.toStdString();
}
