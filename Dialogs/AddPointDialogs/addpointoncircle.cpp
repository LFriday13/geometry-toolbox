#include "addpointoncircle.h"
#include "ui_addpointoncircle.h"

AddPointOnCircle::AddPointOnCircle(std::vector<std::string>* circles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointOnCircle)
{
    connect(this, SIGNAL(add_point(int, std::string, double, double, std::string)), parent, SLOT(add_point(int, std::string, double, double,std::string)));
    ui->setupUi(this);

    for(auto it = circles->begin(); it != circles->end(); ++it){
        ui->circleComboBox->addItem(QString::fromStdString(*it));
    }

    ui->xLineEdit->setText("0");
    ui->yLineEdit->setText("0");
}

AddPointOnCircle::~AddPointOnCircle()
{
    delete ui;
}

void AddPointOnCircle::on_buttonBox_accepted()
{
    emit add_point(2, geo, x, y, label);
}

void AddPointOnCircle::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddPointOnCircle::on_xLineEdit_textEdited(const QString &arg1)
{
    x = arg1.toDouble();
}

void AddPointOnCircle::on_yLineEdit_textEdited(const QString &arg1)
{
    y = arg1.toDouble();
}

void AddPointOnCircle::on_circleComboBox_currentTextChanged(const QString &arg1)
{
    geo = arg1.toStdString();
}
