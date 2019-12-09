#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GeoComponents.h"
#include "PointNode.h"
#include "LineNode.h"
#include "CircleNode.h"
#include "TriangleNode.h"
#include "TriangleCentersNode.h"

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
    void add_point(int, std::string, double, double, std::string);
    void add_point(int, std::string, std::string, std::string);
    void add_line(int, std::string, std::string, std::string);
    void add_circle(int, std::string, std::string, std::string);
    void add_circle(int, std::string, std::string, std::string, std::string);
    void add_triangle(int, std::string, std::string, std::string, std::string);
    void add_triangle_center(int, std::string, std::string);
    void edit(std::string, double, double);
    void remove(std::string);

    void onMousePress(QMouseEvent*);
    void onMouseMove(QMouseEvent*);
    void onMouseRelease();

    void graphClicked(QCPAbstractPlottable *point);
    void itemClicked(QCPAbstractItem *figure);

    void make_plot();
    void edit_point();
    void remove();

    void add_point_independent();
    void add_point_on_line();
    void add_point_on_circle();
    void add_point_midpoint();
    void add_point_intersect();
    void add_point_second_intersect();

    void add_triangle_points();
    void add_triangle_center();

    void add_line_through();
    void add_line_parallel();
    void add_line_perpendicular_bisector();
    void add_line_first_tangent();
    void add_line_second_tangent();

    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;

    // Data Components
    GeoComponents* geo_components;

    // Labels
    std::vector<std::string> point_labels, line_labels, circle_labels, triangle_labels;

    // Label Management
    int next_label {0};

    // Axis Range
    int default_range_x {100}, default_range_y {100};
    boolean initialized {false};

    // Point to drag (set to a negative if none)
    int point_to_drag {-1};

};

#endif // MAINWINDOW_H
