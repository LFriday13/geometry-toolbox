#ifndef REMOVE_H
#define REMOVE_H

#include <QDialog>

namespace Ui {
class Remove;
}

class Remove : public QDialog
{
    Q_OBJECT

public:
    explicit Remove(std::vector<std::string>* constructions [], int size, QWidget *parent = nullptr);
    ~Remove();

signals:
    void remove(std::string);

private slots:
    void on_buttonBox_accepted();
    void on_constructionComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Remove *ui;

    std::string geo;
};

#endif // REMOVE_H
