#ifndef ADDCIRCLECENTERPOINT_H
#define ADDCIRCLECENTERPOINT_H

#include <QDialog>

namespace Ui {
class AddCircleCenterPoint;
}

class AddCircleCenterPoint : public QDialog
{
    Q_OBJECT

public:
    explicit AddCircleCenterPoint(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddCircleCenterPoint();

signals:
    void add_circle(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddCircleCenterPoint *ui;

    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDCIRCLECENTERPOINT_H
