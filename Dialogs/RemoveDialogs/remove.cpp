#include "remove.h"
#include "ui_remove.h"

Remove::Remove(std::vector<std::string>* constructions [], int size, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remove)
{
    connect(this, SIGNAL(remove(std::string)), parent, SLOT(remove(std::string)));
    ui->setupUi(this);

    for(int i = 0; i < size; ++i){
        for(auto it = constructions[i]->begin(); it != constructions[i]->end(); ++it){
            ui->constructionComboBox->addItem(QString::fromStdString(*it));
        }
    }
}

Remove::~Remove()
{
    delete ui;
}

void Remove::on_buttonBox_accepted()
{
    emit remove(geo);
}

void Remove::on_constructionComboBox_currentTextChanged(const QString &arg1)
{
    geo = arg1.toStdString();
}
