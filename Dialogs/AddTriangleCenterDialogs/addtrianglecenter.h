#ifndef ADDTRIANGLECENTER_H
#define ADDTRIANGLECENTER_H

#include <QDialog>

namespace Ui {
class AddTriangleCenter;
}

class AddTriangleCenter : public QDialog
{
    Q_OBJECT

public:
    explicit AddTriangleCenter(std::vector<std::string> *points, QWidget *parent = nullptr);
    ~AddTriangleCenter();

signals:
    void add_triangle_center(int, std::string, std::string);

private slots:
    void on_labelLineEdit_textEdited(const QString &arg1);
    void on_triangleComboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_centerComboBox_currentIndexChanged(int index);

private:
    Ui::AddTriangleCenter *ui;

    int center;
    std::string triangle;
    std::string label;
};

#endif // ADDTRIANGLECENTER_H
