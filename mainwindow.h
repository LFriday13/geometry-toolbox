#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GeoComponents.h"
#include "PointNode.h"
#include "LineNode.h"
#include "CircleNode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GeoComponents *geo_components, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void make_plot();
    // A lot of buttons or menus

private:
    // a lot of dialog boxes

    Ui::MainWindow *ui;
    GeoComponents* geo_components;
    vector<string> point_labels, line_labels, circle_labels;

};

#endif // MAINWINDOW_H
