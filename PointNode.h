/***************************************************************************
This class, PointNode, defines a Point. It is derived from GeoNode.
****************************************************************************/

#ifndef POINTNODE_H_
#define POINTNODE_H_

#include "GeoNode.h"
/** @brief Types of Points */
enum class PointType {
    INDEPENDENT, //!< Point given by Cartesian coordinates.
    ON_LINE, //!< Point on a given line.
    ON_CIRCLE, //!< Point on a given circle.
    POINT_POINT_MIDPOINT, //!< Midpoint of the two given points.
    LINE_LINE_INTERSECTION, //!< Intersection of two given lines.
    LINE_CIRCLE_FIRST_INTERSECTION, //!< First intersection of a given line with a given circle.
    LINE_CIRCLE_SECOND_INTERSECTION, //!< Second intersection of a given line with a given circle.
    CIRCLE_CIRCLE_FIRST_INTERSECTION, //!< First intersection of the two given circles.
    CIRCLE_CIRCLE_SECOND_INTERSECTION //!< Second intersection of the two given circles.
};

class PointNode: public GeoNode {

public:
    PointNode(PointType type, double x, double y); /**< @brief Constructor of an independent point. */
    PointNode(PointType type, GeoNode* geo1, double x, double y); /**< @brief Constructor of a point with a single parent. */
    PointNode(PointType type, GeoNode* geo1, GeoNode* geo2); /**< @brief Constructor of a point with two parents. */

    virtual ~PointNode() override; /**< @brief Removes the associated figure (*point). */

private:
    //@{
    /** @brief Data members: x coordinate, y coordinate. */
    double x{0}, y{0};
    //@}
    QCPGraph *point {nullptr}; //!< Corresponding figure that represents the point on the plot.
    /** @brief Function pointer indicating the definition of the point. */
    void (PointNode::*definition)() {nullptr};

    virtual void print() const override; /**< @brief Prints all data components of the point (Debugging purposes only). */
    virtual void display(Ui::MainWindow* ui) override; /**< @brief Updates the corresponding figure on the plot (*point). */
    /** @brief Takes a collection of string vectors and adds the label of the point to the point_labels vector. */
    virtual void labels(vector<string>* point_labels, vector<string>*, vector<string>*, vector<string>*) const override;

    virtual void access(double data[]) const override; /**< @brief Sets the array data as {x coordinate, y coordinate}. */
    virtual void mutate(double data[]) override; /**< @brief Edits the point based on data = {new x coordinate, new y coordinate}. */

    virtual void update() override; /**< @brief Updates the construction to adjust for changes of the parents. */

    void independent(); /**< @brief Defines a point given by Cartesian coordinates. */
    void on_line(); /**< @brief Defines a point on a given line, taking the projection of the given Cartesian coordinates. */
    void on_circle(); /**< @brief Defines a point on a given circle, taking the projection of the given Cartesian coordinates. */
    void point_point_midpoint(); /**< @brief Defines a point as the midpoint of two given points. */
    void line_line_intersection(); /**< @brief Defines a point given by the intersection of two lines. */
    void line_circle_first_intersection(); /**< @brief Defines a point given by the first intersection of a lines and a circle. */
    void line_circle_second_intersection(); /**< @brief Defines a point given by the second intersection of a lines and a circle. */
    void circle_circle_first_intersection(); /**< @brief Defines a point given by the first intersection of two circles. */
    void circle_circle_second_intersection(); /**< @brief Defines a point given by the seconds intersection of two circles. */

};

#endif /* POINTNODE_H_ */
