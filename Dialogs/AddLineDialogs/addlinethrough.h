#ifndef ADDLINETHROUGH_H
#define ADDLINETHROUGH_H

#include <QDialog>

namespace Ui {
class AddLineThrough;
}

class AddLineThrough : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineThrough(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddLineThrough();

signals:
    void add_line(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddLineThrough *ui;
    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDLINETHROUGH_H
