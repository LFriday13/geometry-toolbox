/***************************************************************************
This class, TriangleNode, defines a Triangle. It is derived from GeoNode.
****************************************************************************/

#ifndef TRIANGLENODE_H_
#define TRIANGLENODE_H_

#include "GeoNode.h"
/** @brief Types of Triangle Centers */
enum class TriangleType {
    POINT_POINT_POINT_VERTICES //!< Triangle defined by three points.
};

class TriangleNode: public GeoNode {

public:
    TriangleNode(TriangleType type, GeoNode* geo1, GeoNode* geo2, GeoNode* geo3); /**< @brief Constructor of a triangle defined by three parents. */
    virtual ~TriangleNode() override; /**< @brief Removes the associated figure (*triangle). */

private:
    //@{
    /** @brief Data members: The length of the three sides of the triangle. */
    double side_a {0}, side_b {0}, side_c {0};
    //@}
    QCPCurve *triangle {nullptr}; //!< Corresponding figure that represents the triangle on the plot.
    /** @brief Function pointer indicating the definition of the triangle. */
    void (TriangleNode::*definition)() {nullptr};

    virtual void print() const override; /**< @brief Prints all data components of the triangle (Debugging purposes only). */
    virtual void display(Ui::MainWindow *ui) override; /**< @brief Updates the corresponding figure on the plot (*triangle). */
    virtual void access(double data[]) const override; /**< @brief Sets the array data as coordinates of the three ponts together with the lenght of the sides. */
    virtual void mutate(double data[]) override; /**< @brief Edits the triangle center based on data = {new side_a, new side_b, new side_c}. */
    virtual void update() override; /**< @brief Updates the construction to adjust for changes of the parents. */
    /** @brief Takes a collection of string vectors and adds the label of the triangle to the triangle_labels vector. */
    virtual void labels(vector<string>*, vector<string>*, vector<string>*, vector<string>*) const override;

    void point_point_point_vertices(); /**< @brief Defines a triangle given by the three vertices. */
};

#endif /* TRIANGLENODE_H_ */
