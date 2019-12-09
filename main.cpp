#include "mainwindow.h"
#include "GeoComponents.h"
#include "PointNode.h"
#include "LineNode.h"
#include "CircleNode.h"
#include "TriangleNode.h"
#include "TriangleCentersNode.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GeoComponents geo_components;

    // Demo Configuration
    int i = 1;
    for(; i<11; ++i){geo_components.add_construction(new PointNode(INDEPENDENT, i, i*i), "demo_"+std::to_string(i-1));}
    geo_components.add_construction(new CircleNode(POINT_POINT_POINT_THROUGH, geo_components.get_construction(0), geo_components.get_construction(1), geo_components.get_construction(2)),  "demo_"+std::to_string(i++ -1));
    geo_components.add_construction(new LineNode(POINT_CIRCLE_FIRST_TANGENT, geo_components.get_construction(5), geo_components.get_construction(10)),  "demo_"+std::to_string(i++ -1));
    geo_components.add_construction(new LineNode(POINT_CIRCLE_SECOND_TANGENT, geo_components.get_construction(5), geo_components.get_construction(10)),  "demo_"+std::to_string(i++ -1));
    geo_components.add_construction(new PointNode(INDEPENDENT, -10, 0), "demo_"+std::to_string(i++ -1));
    geo_components.add_construction(new TriangleNode(POINT_POINT_POINT_VERTICES, geo_components.get_construction(0), geo_components.get_construction(1), geo_components.get_construction(13)),  "demo_"+std::to_string(i++ -1));

    // Application Setup
    QApplication a(argc, argv);
    MainWindow w(&geo_components);
    w.show();
    return a.exec();
}
