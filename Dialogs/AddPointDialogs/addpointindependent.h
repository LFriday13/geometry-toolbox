#ifndef ADDPOINTINDEPENDENT_H
#define ADDPOINTINDEPENDENT_H

#include <QDialog>

namespace Ui {
class AddPointIndependent;
}

class AddPointIndependent : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointIndependent(QWidget *parent = nullptr);
    ~AddPointIndependent();

signals:
    void add_point(int,double,double,std::string);

private slots:
    void on_buttonBox_accepted();
    void on_labelLineEdit_textEdited(const QString &arg1);

    void on_xLineEdit_textEdited(const QString &arg1);

    void on_yLineEdit_textEdited(const QString &arg1);

private:
    Ui::AddPointIndependent *ui;
    std::string label;
    double x{0},y{0};
};

#endif // ADDPOINTINDEPENDENT_H
