#include "addtrianglecenter.h"
#include "ui_addtrianglecenter.h"

AddTriangleCenter::AddTriangleCenter(std::vector<std::string> *triangles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTriangleCenter)
{
    connect(this, SIGNAL(add_triangle_center(int, std::string, std::string)), parent, SLOT(add_triangle_center(int, std::string, std::string)));

    ui->setupUi(this);

    for(auto it = triangles->begin(); it != triangles->end(); ++it){
        ui->triangleComboBox->addItem(QString::fromStdString(*it));
    }

    ui->centerComboBox->addItem("Centroid");
    ui->centerComboBox->addItem("Incenter");
    ui->centerComboBox->addItem("Circumcenter");
    ui->centerComboBox->addItem("Orthocenter");
    ui->centerComboBox->addItem("Nine-Point Center");
    ui->centerComboBox->addItem("Lemoine Point");
}

AddTriangleCenter::~AddTriangleCenter()
{
    delete ui;
}

void AddTriangleCenter::on_buttonBox_accepted()
{
    emit add_triangle_center(center, triangle, label);
}

void AddTriangleCenter::on_labelLineEdit_textEdited(const QString &arg1)
{
    label = arg1.toStdString();
}

void AddTriangleCenter::on_triangleComboBox_currentTextChanged(const QString &arg1){
    triangle = arg1.toStdString();
}

void AddTriangleCenter::on_centerComboBox_currentIndexChanged(int index)
{
    center = index;
}
