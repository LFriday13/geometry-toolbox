#ifndef ADDPOINTON_H
#define ADDPOINTON_H

#include <QDialog>

namespace Ui {
class AddPointOn;
}

class AddPointOn : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointOn(std::vector<std::string>* lines, QWidget *parent = nullptr);
    ~AddPointOn();

signals:
    void add_point(int, std::string, double, double, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);

    void on_xLineEdit_textEdited(const QString &arg1);

    void on_yLineEdit_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

    void on_lineComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::AddPointOn *ui;

    std::string label;
    double x,y;
    std::string geo;
};

#endif // ADDPOINTON_H
