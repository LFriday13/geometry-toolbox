#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addpointindependent.h"
#include "ui_addpointindependent.h"
MainWindow::MainWindow(GeoComponents* geo_components, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->geo_components = geo_components;
    ui->setupUi(this);

    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(edit()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remove()));

    connect(ui->custom_plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    connect(ui->custom_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)));
    connect(ui->custom_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(ui->custom_plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease(QMouseEvent*)));

    make_plot();
}


MainWindow::~MainWindow()
{
    delete geo_components;
    delete ui;
}

void MainWindow::make_plot(){
    // Set interactions
    ui->custom_plot->setInteractions(QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectPlottables);

    // Layers Setup
    ui->custom_plot->addLayer("abovemain", ui->custom_plot->layer("main"), QCustomPlot::limAbove);
    ui->custom_plot->addLayer("belowmain", ui->custom_plot->layer("main"), QCustomPlot::limBelow);
    ui->custom_plot->xAxis->grid()->setLayer("belowmain");
    ui->custom_plot->yAxis->grid()->setLayer("belowmain");

    geo_components->display_all_constructions(this->ui);

    // set some pens, brushes and backgrounds:
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

    ui->custom_plot->rescaleAxes();
    ui->custom_plot->yAxis->setRange(-100, 100);
    ui->custom_plot->xAxis->setRange(-100, 100);
}

void MainWindow::edit() {
    bool ok;
    int pid = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("PID:"), 25, 0, 100, 1, &ok);
    if(pid >= 0){
        double coor[2];
        coor[0]= QInputDialog::getDouble(this, tr("QInputDialog::getDuble()"), tr("x coordinate:"), 25, -100, 100, 1, &ok);
        coor[1]= QInputDialog::getDouble(this, tr("QInputDialog::getDuble()"), tr("y coordinate:"), 25, -100, 100, 1, &ok);
        geo_components->edit_construction(pid, coor);
        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}

void MainWindow::remove() {
    bool ok;
    int pid = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"), tr("PID:"), 25, 0, 100, 1, &ok);
    geo_components->remove_construction(pid);
    geo_components->display_all_constructions(ui);
    ui->custom_plot->replot();
}

void MainWindow::graphClicked(QCPAbstractPlottable* point) {
    selected = qobject_cast<QCPGraph*>(point);
    double value = selected->interface1D()->dataMainValue(0);
    double key = selected->interface1D()->dataMainKey(0);
    QString message = QString("Selected point '%1' with coordinates (%2,%3).").arg(selected->name()).arg(key).arg(value);
    ui->statusbar->showMessage(message, 2500);
}

void MainWindow::add_point_independent() {
   //TODO
}

void MainWindow::add_point(int type, double x, double y, std::string label) {
    geo_components->add_construction(new PointNode(static_cast<PointType>(type), x, y), label);
}

void MainWindow::onMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        QCPAbstractPlottable *plottable = ui->custom_plot->plottableAt(event->pos());
        if(plottable){
           QCPGraph *graph = qobject_cast<QCPGraph*>(plottable);
           if(graph){
               std::string label = graph->name().toStdString();
               this->edit_pid = geo_components->get_pid(label);
               QString message = QString("Selected point '%1'").arg(edit_pid);
               ui->statusbar->showMessage(message, 2500);
           }
        }
    } else {
        //TODO
    }
}

void MainWindow::onMouseMove(QMouseEvent* event){
    double data[2];
    data[0] = this->ui->custom_plot->xAxis->pixelToCoord(event->pos().x());
    data[1] = this->ui->custom_plot->yAxis->pixelToCoord(event->pos().y());

    if(edit_pid >= 0){
        geo_components->edit_construction(static_cast<unsigned int>(edit_pid), data);
        geo_components->display_all_constructions(ui);
        ui->custom_plot->replot();
    }
}

void MainWindow::onMouseRelease(QMouseEvent* event){
    edit_pid = -1;
}
