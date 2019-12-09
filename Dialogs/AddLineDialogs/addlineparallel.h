#ifndef ADDLINEPARALLEL_H
#define ADDLINEPARALLEL_H

#include <QDialog>

namespace Ui {
class AddLineParallel;
}

class AddLineParallel : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineParallel(std::vector<std::string> *points, std::vector<std::string> *lines, QWidget *parent = nullptr);
    ~AddLineParallel();

signals:
    void add_line(int, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_pointComboBox_currentTextChanged(const QString &arg1);
    void on_lineComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddLineParallel *ui;
    std::string geo1;
    std::string geo2;
    std::string label;
};

#endif // ADDLINEPARALLEL_H
