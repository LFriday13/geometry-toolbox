#ifndef ADDPOINTSECONDINTERSECT_H
#define ADDPOINTSECONDINTERSECT_H

#include <QDialog>

namespace Ui {
class AddPointSecondIntersect;
}

class AddPointSecondIntersect : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointSecondIntersect(std::vector<std::string> *lines, std::vector<std::string> *circles, QWidget *parent = nullptr);
    ~AddPointSecondIntersect();

signals:
    void add_point(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_construction1ComboBox_currentTextChanged(const QString &arg1);
    void on_construction2ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddPointSecondIntersect *ui;

    int type;
    std::string geo1;
    std::string geo2;
    std::string label;

    std::vector<std::string> *lines;
};

#endif // ADDPOINTSECONDINTERSECT_H
