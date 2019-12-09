#ifndef ADDPOINTMIDPOINT_H
#define ADDPOINTMIDPOINT_H

#include <QDialog>

namespace Ui {
class AddPointMidpoint;
}

class AddPointMidpoint : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointMidpoint(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddPointMidpoint();

signals:
    void add_point(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::AddPointMidpoint *ui;

    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDPOINTMIDPOINT_H
