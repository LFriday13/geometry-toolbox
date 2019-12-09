#ifndef ADDPOINTONCIRCLE_H
#define ADDPOINTONCIRCLE_H

#include <QDialog>

namespace Ui {
class AddPointOnCircle;
}

class AddPointOnCircle : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointOnCircle(std::vector<std::string> *circles, QWidget *parent = nullptr);
    ~AddPointOnCircle();

signals:
    void add_point(int, std::string, double, double, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);

    void on_xLineEdit_textEdited(const QString &arg1);

    void on_yLineEdit_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

    void on_circleComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::AddPointOnCircle *ui;

    std::string label;
    double x,y;
    std::string geo;
};

#endif // ADDPOINTONCIRCLE_H
