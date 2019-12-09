#ifndef ADDLINEFIRSTTANGENT_H
#define ADDLINEFIRSTTANGENT_H

#include <QDialog>

namespace Ui {
class AddLineFirstTangent;
}

class AddLineFirstTangent : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineFirstTangent(std::vector<std::string> *points, std::vector<std::string> *circles, QWidget *parent = nullptr);
    ~AddLineFirstTangent();

signals:
    void add_line(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_pointComboBox_currentTextChanged(const QString &arg1);
    void on_circleComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddLineFirstTangent *ui;
    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDLINEFIRSTTANGENT_H
