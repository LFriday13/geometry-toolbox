#include "mainwindow.h"
#include "GeoComponents.h"
#include "PointNode.h"
#include "LineNode.h"
#include "CircleNode.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GeoComponents geo_components;

    for(int i = 1; i<11; ++i){
        geo_components.add_construction(new PointNode(INDEPENDENT, i, i*i));
    }

    geo_components.add_construction(new CircleNode(POINT_POINT_POINT_THROUGH, geo_components.get_construction(0), geo_components.get_construction(1), geo_components.get_construction(2)));

    geo_components.add_construction(new LineNode(POINT_CIRCLE_FIRST_TANGENT, geo_components.get_construction(6), geo_components.get_construction(10)));

    QApplication a(argc, argv);
    MainWindow w(&geo_components);
    w.show();
    return a.exec();
}
