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

struct ItemLabel{
    QCPAbstractItem *item;
    std::string label;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GeoComponents *geo_components, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_point(int, double, double, std::string);
    void add_point(int, GeoNode*, double, double, std::string);
    void add_point(int, GeoNode*, GeoNode*, std::string);
    void add_line(int, GeoNode*, GeoNode*, std::string);
    void add_circle(int, GeoNode*, GeoNode*, std::string);
    void add_circle(int, GeoNode*, GeoNode*, GeoNode*, std::string);

    void onMousePress(QMouseEvent*);
    void onMouseMove(QMouseEvent*);
    void onMouseRelease();

    void graphClicked(QCPAbstractPlottable *point);
    void itemClicked(QCPAbstractItem *figure);

    void make_plot();
    void edit();
    void remove();

    void add_point_independent();

private:
    Ui::MainWindow *ui;

    // Data Components
    GeoComponents* geo_components;
    vector<string> point_labels;

    // Ui Labeling of lines and circles
    QVector<ItemLabel> line_labels, circle_labels;

    // Label Management
    int next_label {0};

    // Point to drag (set to a negative if none)
    int point_to_drag {-1};

};

#endif // MAINWINDOW_H
