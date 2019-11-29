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
    void add_point(int, double, double, std::string);
//    void add_point(int, GeoNode*, double, double, std::string);
//    void add_point(int, GeoNode*, GeoNode*);
//    void add_line(int, GeoNode*, GeoNode*, std::string);
//    void add_circle(int, GeoNode*, GeoNode*, std::string);
//    void add_circle(int, GeoNode*, GeoNode*, GeoNode*, std::string);

    void onMousePress(QMouseEvent*);
    void onMouseMove(QMouseEvent*);
    void onMouseRelease(QMouseEvent*);

    void graphClicked(QCPAbstractPlottable* point);

    void make_plot();
    void edit();
    void remove();

    void add_point_independent();

private:
    int edit_pid {-1};

    Ui::MainWindow *ui;
    QCPGraph *selected {nullptr};
    GeoComponents* geo_components;
    vector<string> point_labels, line_labels, circle_labels;

};

#endif // MAINWINDOW_H
