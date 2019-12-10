/***************************************************************************
This class, MainWindow, defines our GUI's main windows.
It serves as framework for all user-interactions in real-time.
The main possible interations are:
    - Selection of constructions via click. (Displays label on statusbar.)
    - Creation/Edition of constructions via actions of the menus.
    - Click and drag points that updates the plot in real-time.
****************************************************************************/

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
    MainWindow(GeoComponents *geo_components, QWidget *parent = nullptr); //!< @brief Takes a pointer to a dynamically-initialized GeoComponents object, and sets the figures on the plot.
    ~MainWindow(); //!< @brief Deletes the GeoComponents object.

private slots:
    /** @brief Sets the configuration/parameters of the plot displayed. */
    void make_plot();

    //@{
    /** @brief Identifies the object clicked and shows its label on the statusbar. */
    void graphClicked(QCPAbstractPlottable *point); //!< Handles identification of points, triangles and triangle centers.
    void itemClicked(QCPAbstractItem *figure); //!< Handles identification of lines and circles.
    //@}

    //@{
    /** @brief Handles edition of points by click and drag events. */
    void onMousePress(QMouseEvent*); //!< Identifies the underlying point, if any.
    void onMouseMove(QMouseEvent*); //!< Edits the point that is currently being dragged, if any.
    void onMouseRelease(); //!< Ends the drag event.
    //@}

    /** @brief Adjusts the proportion of the axis and updates the plot whenever the size of the window changes. */
    virtual void resizeEvent(QResizeEvent *event);

    //@{
    /** @brief Creates constructions from signals, allowing creation via dialogs. */
    void add_point(int, double, double, std::string);
    void add_point(int, std::string, double, double, std::string);
    void add_point(int, std::string, std::string, std::string);
    void add_line(int, std::string, std::string, std::string);
    void add_circle(int, std::string, std::string, std::string);
    void add_circle(int, std::string, std::string, std::string, std::string);
    void add_triangle(int, std::string, std::string, std::string, std::string);
    void add_triangle_center(int, std::string, std::string);
    //@}
    //@{
    /** @brief Edit/Remove constructions from signals, thus, allowing edition via dialogs. */
    void edit(std::string, double, double);
    void remove(std::string);
    //@}

    //@{
    /** @brief Handles menu actions by creating the corresponding dialogs. */
    // Add points.
    void add_point_independent();
    void add_point_on_line();
    void add_point_on_circle();
    void add_point_midpoint();
    void add_point_intersect();
    void add_point_second_intersect();
    // Add lines.
    void add_line_through();
    void add_line_parallel();
    void add_line_perpendicular_bisector();
    void add_line_first_tangent();
    void add_line_second_tangent();
    // Add circles.
    void add_circle_through_points();
    void add_circle_center_point();
    void add_circle_center_radius();
    // Add triangles.
    void add_triangle_points();
    // Add triangle centers.
    void add_triangle_center();
    // Edit Constructions.
    void edit_point();
    // Remove Constructions.
    void remove();
    //@}


private:
    Ui::MainWindow *ui; //!< Ui object of the MainWindow.
    /** @brief Pointer to the GeoComponents object containing the constructions. */
    GeoComponents* geo_components {nullptr};
    //@{
    /** @brief Temporarily stores the labels of the constructions for ease of use. */
    std::vector<std::string> point_labels, line_labels, circle_labels, triangle_labels;
    //@}
    /** @brief Used for labeling of constructions for which the user did not provide a label. */
    int next_label {0};
    //@{
    /** @brief This variables set the default ranges of the x and y axis. */
    int default_range_x {100}, default_range_y {100};
    //@}
    /** @brief Used for handling the resize event that occurs on creation of the main window. */
    boolean initialized {false};
    /** @brief This indicated the pid of the point that is being dragged on a click and drag event. */
    int point_to_drag {-1};

};

#endif // MAINWINDOW_H
