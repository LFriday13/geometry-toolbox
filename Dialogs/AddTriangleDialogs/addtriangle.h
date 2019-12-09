#ifndef ADDTRIANGLE_H
#define ADDTRIANGLE_H

#include <QDialog>

namespace Ui {
class AddTriangle;
}

class AddTriangle : public QDialog
{
    Q_OBJECT

public:
    explicit AddTriangle(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddTriangle();

signals:
    void add_triangle(int, std::string, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_pointAComboBox_currentTextChanged(const QString &arg1);
    void on_pointBComboBox_currentTextChanged(const QString &arg1);
    void on_pointCComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddTriangle *ui;

    int type = 0;
    std::string geo1;
    std::string geo2;
    std::string geo3;
    std::string label;
};

#endif // ADDTRIANGLE_H
