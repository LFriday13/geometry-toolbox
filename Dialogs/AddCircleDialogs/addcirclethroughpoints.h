#ifndef ADDCIRCLETHROUGHPOINTS_H
#define ADDCIRCLETHROUGHPOINTS_H

#include <QDialog>

namespace Ui {
class AddCircleThroughPoints;
}

class AddCircleThroughPoints : public QDialog
{
    Q_OBJECT

public:
    explicit AddCircleThroughPoints(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddCircleThroughPoints();

signals:
    void add_circle(int, std::string, std::string, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_point1ComboBox_currentTextChanged(const QString &arg1);
    void on_point2ComboBox_currentTextChanged(const QString &arg1);
    void on_point3ComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddCircleThroughPoints *ui;

    std::string geo1;
    std::string geo2;
    std::string geo3;
    std::string label;
};

#endif // ADDCIRCLETHROUGHPOINTS_H
