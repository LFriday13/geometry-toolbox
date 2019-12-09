#ifndef ADDCIRCLECENTERRADIUS_H
#define ADDCIRCLECENTERRADIUS_H

#include <QDialog>

namespace Ui {
class AddCircleCenterRadius;
}

class AddCircleCenterRadius : public QDialog
{
    Q_OBJECT

public:
    explicit AddCircleCenterRadius(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddCircleCenterRadius();

signals:
    void add_circle(int, std::string, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);
    void on_point3ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddCircleCenterRadius *ui;

    std::string geo1;
    std::string geo2;
    std::string geo3;
    std::string label;
};

#endif // ADDCIRCLECENTERRADIUS_H
