/***************************************************************************
This class, LineNode, defines a Line. It is derived from GeoNode.
****************************************************************************/

#ifndef LINENODE_H_
#define LINENODE_H_

#include "GeoNode.h"
/** @brief Types of Lines */
enum LineType {
    POINT_POINT_LINE_THROUGH, //!< Line passing through the given points.
    POINT_LINE_PARALLEL_LINE_THROUGH, //!< Line Passing through a given Point that is parallel to the given Line.
    POINT_POINT_PERPENDICULAR_BISECTOR, //!< Perpedicular bisector of the segment defined by the two points.
    POINT_CIRCLE_FIRST_TANGENT, //!< First tangent from the given point to the given circle.
    POINT_CIRCLE_SECOND_TANGENT //!< Second tangent from the given point to the given circle.
};

class LineNode: public GeoNode {

public:
    LineNode(LineType type, GeoNode* geo1, GeoNode* geo2); /**< @brief Constructor of a line defined by 2 parents. */

    virtual ~LineNode() override; /**< @brief Destructor. */

private:
    double x_coeff{0}, y_coeff{0}, c_coeff{0}; // Data components: The line equation is given by (x_coeff)*x + (y_coeff)*y + (c_coeff) = 0.
    QCPItemStraightLine *line {nullptr}; //!< Corresponding figure that represents the line on the plot.

    virtual void print() const override; /**< @brief Prints all data components of the line (Debugging purposes only). */
    virtual void display(Ui::MainWindow* ui) override; /**< @brief Updates the corresponding figure on the plot (*line). */
    /** @brief The following function takes a collection of string vectors and adds the label of the line to the line_labels vector. */
    virtual void labels(vector<string>*, vector<string>* line_labels, vector<string>*, vector<string>*) const override;

    virtual void access(double data[]) const override; /**< @brief Sets the array data as {x_coeff, y_coeff, c_coeff}. */
    virtual void mutate(double data[]) override; /**< @brief Edits the line based on data = {new x_coeff, new y_coeff, new c_coeff}. */

    virtual void update() override; /**< @brief Updates the construction to adjust for changes of the parents. */
    void (LineNode::*definition)() {nullptr}; /**< @brief Function pointer indicating the definition of the line. */

    void point_point_line_through(); /**< @brief Defines a line passing through 2 points. */
    void point_line_parallel_line_through(); /**< @brief Defines a line passing through a given point that is parallel to a given line. */
    void point_point_perpendicular_bisector(); /**< @brief Defines a line that is the perpedicular bisector of the segment given by the 2 points. */
    void point_circle_first_tangent(); /**< @brief Defines a line as the first tangent from the given point to the given circle. */
    void point_circle_second_tangent(); /**< @brief Defines a line as the second tangent from the given point to the given circle. */

};

#endif /* LINENODE_H_ */
