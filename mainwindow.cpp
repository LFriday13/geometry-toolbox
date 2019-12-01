#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addpointindependent.h"
#include "addpointon.h"
#include "addpointoncircle.h"
#include "addpointmidpoint.h"

MainWindow::MainWindow(GeoComponents* geo_components, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Set GeoComponents object
    this->geo_components = geo_components;
    geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

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
    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(edit()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remove()));

    //Draw the plot
    make_plot();
}


MainWindow::~MainWindow()
{
    delete geo_components; // Deleted Geo_Components here, in reality only figure pointers need to be cleaned...

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

    // Scaling of the axis (Proportion should probably be fixed 1:1 [corresponding to the window?])
    ui->custom_plot->rescaleAxes();
    ui->custom_plot->yAxis->setRange(-default_range, default_range);
    ui->custom_plot->xAxis->setRange(-default_range, default_range);
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
}

// Display Info of Item Clicked
void MainWindow::itemClicked(QCPAbstractItem *item){
    QCPItemStraightLine *line = qobject_cast<QCPItemStraightLine*>(item);
    if(line){
        //TODO: Resolve Line Name
        std::string name = "";
        QString message = QString("Selected line '%1'.").arg(QString::fromStdString(name));
        ui->statusbar->showMessage(message, 3000);
        return;
    }

    QCPItemEllipse *circle = qobject_cast<QCPItemEllipse*>(item);
    if(circle){
        //TODO: Resolve Circle Name
        std::string name = "";
        QString message = QString("Selected circle '%1'.").arg(QString::fromStdString(name));
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
    if(point_to_drag >= 0){
        double data[2];
        data[0] = this->ui->custom_plot->xAxis->pixelToCoord(event->pos().x());
        data[1] = this->ui->custom_plot->yAxis->pixelToCoord(event->pos().y());

        geo_components->edit_construction(static_cast<unsigned int>(point_to_drag), data);

        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}

void MainWindow::onMouseRelease(){
    if(point_to_drag >= 0){
        point_to_drag = -1;
        ui->custom_plot->setInteraction(QCP::iRangeDrag, true);
        ui->statusbar->clearMessage();
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
    GeoNode* parent_1 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo)));

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new PointNode(static_cast<PointType>(type), parent_1, x, y), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created point '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

void MainWindow::add_point(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo1)));
    GeoNode *parent_2 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo2)));

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new PointNode(static_cast<PointType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created point '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

// Lines
void MainWindow::add_line(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo1)));
    GeoNode *parent_2 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo2)));

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new LineNode(static_cast<LineType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created line '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

// Circles
void MainWindow::add_circle(int type, std::string geo1, std::string geo2, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo1)));
    GeoNode *parent_2 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo2)));

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new CircleNode(static_cast<CircleType>(type), parent_1, parent_2), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created circle '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}

void MainWindow::add_circle(int type, std::string geo1, std::string geo2, std::string geo3, std::string label){
    GeoNode *parent_1 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo1)));
    GeoNode *parent_2 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo2)));
    GeoNode *parent_3 = geo_components->get_construction(static_cast<unsigned int>(geo_components->get_pid(geo3)));

    if(label == ""){label = "default_" + std::to_string(next_label++);}

    geo_components->add_construction(new CircleNode(static_cast<CircleType>(type), parent_1, parent_2, parent_3), label);

    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();

    QString message = QString("Created circle '%1'").arg(QString::fromStdString(label));
    ui->statusbar->showMessage(message,3000);
}


// Actions of the menus
    // Points
void MainWindow::add_point_independent() {
   AddPointIndependent *dialog = new AddPointIndependent(this);
   dialog->show();
}

void MainWindow::add_point_on_line() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

   AddPointOn *dialog = new AddPointOn(&line_labels, this);
   dialog->show();
}

void MainWindow::add_point_on_circle() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

   AddPointOnCircle *dialog = new AddPointOnCircle(&circle_labels, this);
   dialog->show();
}

void MainWindow::add_point_midpoint() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

   AddPointMidpoint *dialog = new AddPointMidpoint(&point_labels, this);
   dialog->show();
}

void MainWindow::add_point_intersect() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

}

void MainWindow::add_point_second_intersect() {
   geo_components->update_ui_labels(&point_labels, &line_labels, &circle_labels);

}

    // Edit
void MainWindow::edit() {
    bool ok;
    std::string label = (QInputDialog::getText(this,tr("Edit Construction"),tr("Label:"), QLineEdit::Normal,"default_0", &ok)).toStdString();
    int to_edit = geo_components->get_pid(label);
    if(to_edit >= 0){
        double coor[2];
        coor[0]= QInputDialog::getDouble(this, tr("QInputDialog::getDuble()"), tr("x coordinate:"), 0, -100, 100, 2, &ok);
        coor[1]= QInputDialog::getDouble(this, tr("QInputDialog::getDuble()"), tr("y coordinate:"), 0, -100, 100, 2, &ok);
        geo_components->edit_construction(static_cast<unsigned int>(to_edit),coor);
        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}

    //Remove
void MainWindow::remove() {
    bool ok;
    std::string label = (QInputDialog::getText(this,tr("Remove Construction"),tr("Label:"), QLineEdit::Normal,"default_0", &ok)).toStdString();
    int to_remove = geo_components->get_pid(label);
    if(to_remove >= 0){
        geo_components->remove_construction(static_cast<unsigned int>(to_remove));
        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}
