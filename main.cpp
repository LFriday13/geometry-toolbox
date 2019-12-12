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
    GeoComponents* geo = new GeoComponents;

    // Demo 1: Circles and Tangents
    int i = 0, k = 1;
    geo->add_construction(new PointNode(PointType::INDEPENDENT, 0.0, 0.0), "demo_"+std::to_string(i++));
    while(k<11){
        geo->add_construction(new PointNode(PointType::INDEPENDENT, 0.0, 10.0*k), "demo_"+std::to_string(i++));
        geo->add_construction(new CircleNode(CircleType::POINT_POINT_CENTER_THROUGH, geo->get_construction(0), geo->get_construction(i-1)), "demo_"+std::to_string(i)); ++i;
        geo->add_construction(new PointNode(PointType::INDEPENDENT, 10.0*k, 10.0*k), "demo_"+std::to_string(i++));
        geo->add_construction(new LineNode(LineType::POINT_CIRCLE_FIRST_TANGENT, geo->get_construction(i-1), geo->get_construction(i-2)), "demo_"+std::to_string(i));++i;
        geo->add_construction(new LineNode(LineType::POINT_CIRCLE_SECOND_TANGENT, geo->get_construction(i-2), geo->get_construction(i-3)), "demo_"+std::to_string(i));++i;
        geo->add_construction(new PointNode(PointType::INDEPENDENT, -10.0*k, -10.0*k), "demo_"+std::to_string(i++));
        geo->add_construction(new LineNode(LineType::POINT_CIRCLE_FIRST_TANGENT, geo->get_construction(i-1), geo->get_construction(i-5)), "demo_"+std::to_string(i));++i;
        geo->add_construction(new LineNode(LineType::POINT_CIRCLE_SECOND_TANGENT, geo->get_construction(i-2), geo->get_construction(i-6)), "demo_"+std::to_string(i));++i;
        ++k;
    }

    /*
    // Demo 2: Triangle, Triangle Centers and Perpendicular/Parallel lines.
    geo->add_construction(new PointNode(PointType::INDEPENDENT, -50.0, 0.0), "Vertex A");
    geo->add_construction(new PointNode(PointType::INDEPENDENT, 10, 70), "Vertex B");
    geo->add_construction(new PointNode(PointType::INDEPENDENT, 50.0, 0), "Vertex C");
    geo->add_construction(new TriangleNode(TriangleType::POINT_POINT_POINT_VERTICES, geo->get_construction(geo->get_pid("Vertex A")), geo->get_construction(geo->get_pid("Vertex B")), geo->get_construction(geo->get_pid("Vertex C"))), "Triangle");
    geo->add_construction(new LineNode(LineType::POINT_POINT_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex A")), geo->get_construction(geo->get_pid("Vertex B"))), "Side c");
    geo->add_construction(new LineNode(LineType::POINT_POINT_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex B")), geo->get_construction(geo->get_pid("Vertex C"))), "Side a");
    geo->add_construction(new LineNode(LineType::POINT_POINT_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex C")), geo->get_construction(geo->get_pid("Vertex A"))), "Side b");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::ORTHOCENTER, geo->get_construction(3)),"Orthocenter");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::CENTROID, geo->get_construction(3)),"Centroid");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::CIRCUMCENTER, geo->get_construction(3)),"Circumcenter");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::INCENTER, geo->get_construction(3)),"Incenter");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::LEMOINEPOINT, geo->get_construction(3)),"Lemoine");
    geo->add_construction(new TriangleCentersNode(TriangleCentersType::NINEPOINTCENTER, geo->get_construction(3)),"NineP");
    geo->add_construction(new LineNode(LineType::POINT_POINT_PERPENDICULAR_BISECTOR, geo->get_construction(geo->get_pid("Vertex A")), geo->get_construction(geo->get_pid("Vertex B"))), "Perpendicular c");
    geo->add_construction(new LineNode(LineType::POINT_POINT_PERPENDICULAR_BISECTOR, geo->get_construction(geo->get_pid("Vertex B")), geo->get_construction(geo->get_pid("Vertex C"))), "Perpendicular a");
    geo->add_construction(new LineNode(LineType::POINT_POINT_PERPENDICULAR_BISECTOR, geo->get_construction(geo->get_pid("Vertex C")), geo->get_construction(geo->get_pid("Vertex A"))), "Perpendicular b");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex A")), geo->get_construction(geo->get_pid("Perpendicular a"))), "Height a");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex B")), geo->get_construction(geo->get_pid("Perpendicular b"))), "Height b");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Vertex C")), geo->get_construction(geo->get_pid("Perpendicular c"))), "Height c");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Incenter")), geo->get_construction(geo->get_pid("Perpendicular a"))), "Incenter a");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Incenter")), geo->get_construction(geo->get_pid("Perpendicular b"))), "Incenter b");
    geo->add_construction(new LineNode(LineType::POINT_LINE_PARALLEL_LINE_THROUGH, geo->get_construction(geo->get_pid("Incenter")), geo->get_construction(geo->get_pid("Perpendicular c"))), "Incenter c");
    geo->add_construction(new PointNode(PointType::LINE_LINE_INTERSECTION, geo->get_construction(geo->get_pid("Incenter a")), geo->get_construction(geo->get_pid("Side a"))), "M_a");
    geo->add_construction(new PointNode(PointType::LINE_LINE_INTERSECTION, geo->get_construction(geo->get_pid("Incenter b")), geo->get_construction(geo->get_pid("Side b"))), "M_b");
    geo->add_construction(new PointNode(PointType::LINE_LINE_INTERSECTION, geo->get_construction(geo->get_pid("Incenter c")), geo->get_construction(geo->get_pid("Side c"))), "M_c");
    geo->add_construction(new CircleNode(CircleType::POINT_POINT_CENTER_THROUGH, geo->get_construction(geo->get_pid("Incenter")), geo->get_construction(geo->get_pid("M_a"))), "Incircle");
    geo->add_construction(new CircleNode(CircleType::POINT_POINT_CENTER_THROUGH, geo->get_construction(geo->get_pid("Circumcenter")), geo->get_construction(geo->get_pid("Vertex A"))), "Circumcircle");
    geo->add_construction(new LineNode(LineType::POINT_POINT_LINE_THROUGH, geo->get_construction(geo->get_pid("Orthocenter")), geo->get_construction(geo->get_pid("Centroid"))), "Euler's Line");
    */

    // Application Setup
    QApplication a(argc, argv);
    MainWindow w(geo);
    w.show();
    return a.exec();
}
