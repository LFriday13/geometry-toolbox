#ifndef EDIT_H
#define EDIT_H

#include <QDialog>

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(std::vector<std::string>* points, QWidget *parent = nullptr);
    ~Edit();

signals:
    void edit_point(std::string, double, double);

private slots:
    void on_pointComboBox_currentTextChanged(const QString &arg1);

    void on_newXLineEdit_textEdited(const QString &arg1);

    void on_newYLineEdit_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::Edit *ui;

    double x,y;
    std::string geo;
};

#endif // EDIT_H
