#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Dialogs/AddPointDialogs/addpointindependent.h"
#include "Dialogs/AddPointDialogs/addpointon.h"
#include "Dialogs/AddPointDialogs/addpointoncircle.h"
#include "Dialogs/AddPointDialogs/addpointmidpoint.h"
#include "Dialogs/AddPointDialogs/addpointintersect.h"
#include "Dialogs/AddPointDialogs/addpointsecondintersect.h"
#include "Dialogs/AddTriangleDialogs/addtriangle.h"
#include "Dialogs/AddTriangleCenterDialogs/addtrianglecenter.h"
#include "Dialogs/AddLineDialogs/addlinethrough.h"
#include "Dialogs/AddLineDialogs/addlineparallel.h"
#include "Dialogs/AddLineDialogs/addlineperpendicularbisector.h"
#include "Dialogs/AddLineDialogs/addlinefirsttangent.h"
#include "Dialogs/AddLineDialogs/addlinesecondtangent.h"
#include "Dialogs/AddCircleDialogs/addcirclethroughpoints.h"
#include "Dialogs/AddCircleDialogs/addcirclecenterpoint.h"
#include "Dialogs/AddCircleDialogs/addcirclecenterradius.h"
#include "Dialogs/EditDialogs/edit.h"
#include "Dialogs/RemoveDialogs/remove.h"

MainWindow::MainWindow(GeoComponents* geo_components, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Set GeoComponents object
    this->geo_components = (geo_components == nullptr)? new GeoComponents: geo_components;

    //Setup Ui
    ui->setupUi(this);

    //Connect on ClickGraph for displaying Info
    connect(ui->custom_plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
    connect(ui->custom_plot, SIGNAL(itemClick(QCPAbstractItem*, QMouseEvent*)), this, SLOT(itemClicked(QCPAbstractItem*)));

    //Setup Connections for Click&Drag
    connect(ui->custom_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)));
    connect(ui->custom_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(ui->custom_plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease()));

    //Connect the Actions of the Menus
    connect(ui->actionIndependent, SIGNAL(triggered()), this, SLOT(add_point_independent()));
    connect(ui->actionOn_line, SIGNAL(triggered()), this, SLOT(add_point_on_line()));
    connect(ui->actionOn_Circle, SIGNAL(triggered()), this, SLOT(add_point_on_circle()));
    connect(ui->actionMidpoint, SIGNAL(triggered()), this, SLOT(add_point_midpoint()));
    connect(ui->actionIntersect, SIGNAL(triggered()), this, SLOT(add_point_intersect()));
    connect(ui->actionSecond_Intersect, SIGNAL(triggered()), this, SLOT(add_point_second_intersect()));
    connect(ui->actionNew_Triangle, SIGNAL(triggered()), this, SLOT(add_triangle_points()));
    connect(ui->actionAdd_Triangle_Center, SIGNAL(triggered()), this, SLOT(add_triangle_center()));
    connect(ui->actionLine_Through, SIGNAL(triggered()), this, SLOT(add_line_through()));
    connect(ui->actionParallel, SIGNAL(triggered()), this, SLOT(add_line_parallel()));
    connect(ui->actionPerpendicular_Bisector, SIGNAL(triggered()), this, SLOT(add_line_perpendicular_bisector()));
    connect(ui->actionFirst_Tangent, SIGNAL(triggered()), this, SLOT(add_line_first_tangent()));
    connect(ui->actionSecond_Tangent, SIGNAL(triggered()), this, SLOT(add_line_second_tangent()));
    connect(ui->actionCircle_Through_Points, SIGNAL(triggered()), this, SLOT(add_circle_through_points()));
    connect(ui->actionCircle_Center_Point, SIGNAL(triggered()), this, SLOT(add_circle_center_point()));
    connect(ui->actionCircle_Center_Radius, SIGNAL(triggered()), this, SLOT(add_circle_center_radius()));
    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(edit_point()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remove()));

    //Draw the plot
    make_plot();
}


MainWindow::~MainWindow()
{
    delete geo_components;
    delete ui;
}

void MainWindow::make_plot(){
    // Set interactions
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectPlottables | QCP::iSelectItems);

    // Layers Setup
    ui->custom_plot->addLayer("front", ui->custom_plot->layer("main"), QCustomPlot::limAbove);
    ui->custom_plot->addLayer("back", ui->custom_plot->layer("main"), QCustomPlot::limBelow);

    // Send axis to the back
    ui->custom_plot->xAxis->grid()->setLayer("back");
    ui->custom_plot->yAxis->grid()->setLayer("back");

    // Draw the constructions
    geo_components->display_all_constructions(this->ui);

    // Set some pens, brushes and backgrounds
    ui->custom_plot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->custom_plot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->custom_plot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->custom_plot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->custom_plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->custom_plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->custom_plot->xAxis->setTickLabelColor(Qt::white);
    ui->custom_plot->yAxis->setTickLabelColor(Qt::white);
    ui->custom_plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->custom_plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->custom_plot->xAxis->grid()->setSubGridPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->custom_plot->yAxis->grid()->setSubGridPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->custom_plot->xAxis->grid()->setSubGridVisible(true);
    ui->custom_plot->yAxis->grid()->setSubGridVisible(true);
    ui->custom_plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->custom_plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->custom_plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->custom_plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    // Backgrounds
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->custom_plot->setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->custom_plot->axisRect()->setBackground(axisRectGradient);

    // Scaling of the axis (Proportion should remain fixed corresponding to the window.)
    ui->custom_plot->rescaleAxes();
    ui->custom_plot->yAxis->setRange(-default_range_y, default_range_y);
    ui->custom_plot->xAxis->setRange(-default_range_x, default_range_x);
}

// Display Info of Point Clicked
void MainWindow::graphClicked(QCPAbstractPlottable *plottable) {
    QCPGraph *point = qobject_cast<QCPGraph*>(plottable);
    if(point){
        double value = point->interface1D()->dataMainValue(0);
        double key = point->interface1D()->dataMainKey(0);
        QString message = QString("Selected point '%1' with coordinates (%2,%3).").arg(point->name()).arg(key).arg(value);
        ui->statusbar->showMessage(message, 3000);
        return;
    }

    QCPCurve *triangle = qobject_cast<QCPCurve*>(plottable);
    if(triangle){
        QString message = QString("Selected triangle '%1'.").arg(triangle->name());
        ui->statusbar->showMessage(message, 3000);
        return;
    }
}

// Display Info of Item Clicked
void MainWindow::itemClicked(QCPAbstractItem *item){
    QCPItemStraightLine *line = qobject_cast<QCPItemStraightLine*>(item);
    if(line){
        QString message = QString("Selected line '%1'.").arg(line->objectName());
        ui->statusbar->showMessage(message, 3000);
        return;
    }

    QCPItemEllipse *circle = qobject_cast<QCPItemEllipse*>(item);
    if(circle){
        QString message = QString("Selected circle '%1'.").arg(circle->objectName());
        ui->statusbar->showMessage(message, 3000);
        return;
    }
}

// Drag&Drop Functions
void MainWindow::onMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        QCPAbstractPlottable *plottable = ui->custom_plot->plottableAt(event->pos());
        if(plottable){
            QCPGraph *graph = qobject_cast<QCPGraph*>(plottable);
            if(graph){
                ui->custom_plot->setInteraction(QCP::iRangeDrag, false);
                std::string label = graph->name().toStdString();
                this->point_to_drag = geo_components->get_pid(label);
                QString message = QString("Dragging point '%1'").arg(QString::fromStdString(label));
                ui->statusbar->showMessage(message);
           }
        }
    }
}

void MainWindow::onMouseMove(QMouseEvent* event){
    if(point_to_drag != static_cast<unsigned int>(-1)){
        double data[2];
        data[0] = this->ui->custom_plot->xAxis->pixelToCoord(event->pos().x());
        data[1] = this->ui->custom_plot->yAxis->pixelToCoord(event->pos().y());

        geo_components->edit_construction(point_to_drag, data);

        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}

void MainWindow::onMouseRelease(){
    if(point_to_drag != static_cast<unsigned int>(-1)){
        point_to_drag = static_cast<unsigned int>(-1);
        ui->custom_plot->setInteraction(QCP::iRangeDrag, true);
        ui->statusbar->clearMessage();
    }
}

// Resize of the axis to fit the window.
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    if(initialized){
        int h = ui->custom_plot->size().height();
        int w = ui->custom_plot->size().width();
        default_range_y = 100 * h / w;
        ui->custom_plot->rescaleAxes();
        ui->custom_plot->yAxis->setRange(-default_range_y, default_range_y);
        ui->custom_plot->xAxis->setRange(-default_range_x, default_range_x);
        ui->custom_plot->replot();
    } else {
        initialized = true;
    }
}
// Construction Creation Slots (This way dialogs only need to emit a signal for creation)

// Points

void MainWindow::add_point(int type, double x, double y, std::string label) {
    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new PointNode(static_cast<PointType>(type), x, y), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created point '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

void MainWindow::add_point(int type, std::string geo, double x, double y, std::string label){
    GeoNode* parent_1 = geo_components->get_construction(geo_components->get_pid(geo));
    if(parent_1 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new PointNode(static_cast<PointType>(type), parent_1, x, y), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created point '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

void MainWindow::add_point(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo1));
    GeoNode *parent_2 = geo_components->get_construction(geo_components->get_pid(geo2));
    if(parent_1 == nullptr || parent_2 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new PointNode(static_cast<PointType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created point '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

// Lines

void MainWindow::add_line(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo1));
    GeoNode *parent_2 = geo_components->get_construction(geo_components->get_pid(geo2));
    if(parent_1 == nullptr || parent_2 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new LineNode(static_cast<LineType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created line '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

// Circles

void MainWindow::add_circle(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo1));
    GeoNode *parent_2 = geo_components->get_construction(geo_components->get_pid(geo2));
    if(parent_1 == nullptr || parent_2 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new CircleNode(static_cast<CircleType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created circle '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

void MainWindow::add_circle(int type, std::string geo1, std::string geo2, std::string geo3, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo1));
    GeoNode *parent_2 = geo_components->get_construction(geo_components->get_pid(geo2));
    GeoNode *parent_3 = geo_components->get_construction(geo_components->get_pid(geo3));
    if(parent_1 == nullptr || parent_2 == nullptr || parent_3 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new CircleNode(static_cast<CircleType>(type), parent_1, parent_2, parent_3), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created circle '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

//Triangles
void MainWindow::add_triangle(int type, std::string geo1, std::string geo2, std::string geo3, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo1));
    GeoNode *parent_2 = geo_components->get_construction(geo_components->get_pid(geo2));
    GeoNode *parent_3 = geo_components->get_construction(geo_components->get_pid(geo3));
    if(parent_1 == nullptr || parent_2 == nullptr || parent_3 == nullptr){
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new TriangleNode(static_cast<TriangleType>(type), parent_1, parent_2, parent_3), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created triangle '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

//Triangle Centers

void MainWindow::add_triangle_center(int type, std::string geo, std::string label) {
    GeoNode *parent_1 = geo_components->get_construction(geo_components->get_pid(geo));
    if(parent_1 == nullptr) {
        QString message = QString("Invalid parameters.");
        ui->statusbar->showMessage(message,3000);
        return;
    }

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new TriangleCentersNode(static_cast<TriangleCentersType>(type), parent_1), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created triangle center '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

// Edit

void MainWindow::edit(std::string geo, double x, double y){
    unsigned int to_edit = geo_components->get_pid(geo);
    double data [2] = {x,y};

    geo_components->edit_construction(to_edit, data);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Edited point '%1'").arg(QString::fromStdString(geo));
    ui->statusbar->showMessage(message,3000);
}

// Remove
void MainWindow::remove(std::string geo){
    unsigned int to_remove = geo_components->get_pid(geo);
    geo_components->remove_construction(to_remove);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Removed construction '%1'").arg(QString::fromStdString(geo));
    ui->statusbar->showMessage(message,3000);
}

// Actions of the menus

// Points

void MainWindow::add_point_independent() {
   AddPointIndependent *Add_Point = new AddPointIndependent(this);
   Add_Point->show();
}

void MainWindow::add_point_on_line() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddPointOn *Add_Point = new AddPointOn(&line_labels, this);
   Add_Point->show();
}

void MainWindow::add_point_on_circle() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddPointOnCircle *Add_Point = new AddPointOnCircle(&circle_labels, this);
   Add_Point->show();
}

void MainWindow::add_point_midpoint() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddPointMidpoint *Add_Point = new AddPointMidpoint(&point_labels, this);
   Add_Point->show();
}

void MainWindow::add_point_intersect() {
    geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

    AddPointIntersect *Add_Point = new AddPointIntersect(&line_labels, &circle_labels, this);
    Add_Point->show();
}

void MainWindow::add_point_second_intersect() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddPointSecondIntersect *Add_Point = new AddPointSecondIntersect(&line_labels, &circle_labels, this);
   Add_Point->show();
}

// Triangles

void MainWindow::add_triangle_points() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddTriangle *Add_Triangle = new AddTriangle(&point_labels, this);
   Add_Triangle->show();
}

//Triangle Centers

void MainWindow::add_triangle_center() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddTriangleCenter *Add_Triangle_Center = new AddTriangleCenter(&triangle_labels, this);
   Add_Triangle_Center->show();
}

// Lines

void MainWindow::add_line_through() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddLineThrough *Add_Line = new AddLineThrough(&point_labels, this);
   Add_Line->show();
}

void MainWindow::add_line_parallel() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddLineParallel *Add_Line = new AddLineParallel(&point_labels, &line_labels, this);
   Add_Line->show();
}

void MainWindow::add_line_perpendicular_bisector() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddLinePerpendicularBisector *Add_Line = new AddLinePerpendicularBisector(&point_labels, this);
   Add_Line->show();
}

void MainWindow::add_line_first_tangent() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddLineFirstTangent *Add_Line = new AddLineFirstTangent(&point_labels, &circle_labels, this);
   Add_Line->show();
}

void MainWindow::add_line_second_tangent() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddLineSecondTangent *Add_Line = new AddLineSecondTangent(&point_labels, &circle_labels, this);
   Add_Line->show();
}

//Circles

void MainWindow::add_circle_through_points() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddCircleThroughPoints *Add_Circle = new AddCircleThroughPoints(&point_labels, this);
   Add_Circle->show();
}

void MainWindow::add_circle_center_point() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddCircleCenterPoint *Add_Circle = new AddCircleCenterPoint(&point_labels, this);
   Add_Circle->show();
}

void MainWindow::add_circle_center_radius() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

   AddCircleCenterRadius *Add_Circle = new AddCircleCenterRadius(&point_labels, this);
   Add_Circle->show();
}

// Edit

void MainWindow::edit_point() {
    geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels);

    Edit *edit_point = new Edit(&point_labels, this);
    edit_point->show();
}

//Remove
void MainWindow::remove() {
    geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels, &triangle_labels, true);
    std::vector<std::string>* labels [4] = {&point_labels, &line_labels, &circle_labels, &triangle_labels};

    Remove *remove = new Remove(labels, 4, this);
    remove->show();
}
