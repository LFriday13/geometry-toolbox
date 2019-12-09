#ifndef ADDLINEPERPENDICULARBISECTOR_H
#define ADDLINEPERPENDICULARBISECTOR_H

#include <QDialog>

namespace Ui {
class AddLinePerpendicularBisector;
}

class AddLinePerpendicularBisector : public QDialog
{
    Q_OBJECT

public:
    explicit AddLinePerpendicularBisector(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddLinePerpendicularBisector();

signals:
    void add_line(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddLinePerpendicularBisector *ui;
    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDLINEPERPENDICULARBISECTOR_H
