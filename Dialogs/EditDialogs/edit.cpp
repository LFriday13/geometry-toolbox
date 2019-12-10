#include "edit.h"
#include "ui_edit.h"

Edit::Edit(std::vector<std::string> *points, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit)
{
    connect(this, SIGNAL(edit_point(std::string, double, double)), parent, SLOT(edit(std::string, double, double)));
    ui->setupUi(this);

    for(auto it = points->begin(); it != points->end(); ++it){
        ui->pointComboBox->addItem(QString::fromStdString(*it));
    }

    ui->newXLineEdit->setText("0");
    ui->newYLineEdit->setText("0");
}

Edit::~Edit()
{
    delete ui;
}

void Edit::on_buttonBox_accepted()
{
    emit edit_point(geo, x, y);
}

void Edit::on_newXLineEdit_textEdited(const QString &arg1)
{
    x = arg1.toDouble();
}

void Edit::on_newYLineEdit_textEdited(const QString &arg1)
{
    y = arg1.toDouble();
}

void Edit::on_pointComboBox_currentTextChanged(const QString &arg1)
{
    geo = arg1.toStdString();
}
