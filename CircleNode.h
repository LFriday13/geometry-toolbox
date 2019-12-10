/***************************************************************************
This class, CircleNode, defines a Circle. It is derived from GeoNode.
****************************************************************************/

#ifndef CIRCLENODE_H_
#define CIRCLENODE_H_

#include "GeoNode.h"
/** @brief Types of Circles */
enum class CircleType {
    POINT_POINT_POINT_THROUGH, //!< Circle passing through 3 given Points
    POINT_POINT_CENTER_THROUGH, //!< Circle centered at Point 1 that passes through Point 2
    POINT_POINT_POINT_CENTER_RADIUS, //!< Circle centered at Point 1 that has as radius the distance between Point 2 and Point 3
};

class CircleNode: public GeoNode {

public:
    CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2); /**< @brief Constructor of a circle defined by 2 parents. */
    CircleNode(CircleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3); /**< @brief Constructor of a circle defined by 3 parents. */

    virtual ~CircleNode() override; /**< @brief Deletes the corresponding QCPItemEllipse that represents the circle from the plot. */

private:
    //@{
    /** @brief Data components: x coordinate of the center, y coordinate of the center, radius. */
    double center_x{0}, center_y{0}, radius{0};
    //@}
    QCPItemEllipse *circle {nullptr}; /**< @brief Corresponding figure that represents the circle on the plot. */
    /** @brief Function pointer indicating the definition of the circle. */
    void (CircleNode::*definition)() {nullptr};

    virtual void print() const override; /**< @brief Prints all data components of the circle (Debugging purposes only). */
    virtual void display(Ui::MainWindow* ui) override; /**< @brief Updates the corresponding figure on the plot (*circle). */
    /** @brief Takes a collection of string vectors and adds the label of the circle to the circle_labels vector. */
    virtual void labels(vector<string>*, vector<string>*, vector<string>* circle_labels, vector<string>*) const override;

    virtual void access(double data[]) const override; /**< @brief Sets the array data as {x coordinate of the center, y coordinate of the center, radius}. */
    virtual void mutate(double data[]) override; /**< @brief Edits the circle based on the data = {new x coordinate of the center, new y coordinate of the center, new radius}. */

    virtual void update() override; /**< @brief Updates the construction to adjust for changes of the parents. */

    void point_point_point_through(); /**< @brief Defines a circle passing through the 3 Points. */
    void point_point_point_center_radius(); /**< @brief Defines a circle centered at Point 1 that passes through Point 2. */
    void point_point_center_through(); /**< @brief Defines a circle centered at Point 1 that has as radius the distance between Point 2 and Point 3. */

};

#endif /* CIRCLENODE_H_ */
