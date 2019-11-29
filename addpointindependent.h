#ifndef ADDPOINTINDEPENDENT_H
#define ADDPOINTINDEPENDENT_H

#include <QDialog>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddPointIndependent; }
QT_END_NAMESPACE

class AddPointIndependent : public QDialog
{
    Q_OBJECT

signals:
    void add_point(int type, double x, double y, std::string label);

public:
    AddPointIndependent(MainWindow* dummy, QWidget *parent = nullptr);
    ~AddPointIndependent();

private:
    Ui::AddPointIndependent *ui;
    double x,y;
    std::string label;

private slots:
    void on_button_box_accepted();
    void on_x_textEdited(const QString &arg1);
    void on_y_textEdited(const QString &arg1);
    void on_label_textEdited(const QString &arg1);
};

#endif // ADDPOINTINDEPENDENT_H
