/***************************************************************************
This class, TriangleCentersNode, defines a triangle center.
It is derived from GeoNode.
****************************************************************************/

#ifndef TRIANGLECENTERSNODE_H_
#define TRIANGLECENTERSNODE_H_

#include "GeoNode.h"
/** @brief Types of Triangle Centers */
enum class TriangleCentersType {
    CENTROID, //!< The intersection of the medians.
    INCENTER, //!< The intersection of the angle bisectors.
    CIRCUMCENTER, //!< The intersecion of the perpendicular bisectors.
    ORTHOCENTER, //!< The intersection of the heights.
    NINEPOINTCENTER, //!< The center of the nine-point circle.
    LEMOINEPOINT //!< The intersection of the symmedians.
};

class TriangleCentersNode: public GeoNode {

public:
    TriangleCentersNode(TriangleCentersType type,GeoNode* geo1); /**< @brief Constructor of a triangle center with a single parent (The triangle). */
    virtual ~TriangleCentersNode() override; /**< @brief Removes the associated figure (*center). */

private:
    //@{
    /** @brief Data members: The Barycentric Coordinates of the point is given by [barycoeff_a : barycoeff_b : barycoeff_c]. */
    double barycoeff_a {0}, barycoeff_b {0}, barycoeff_c {0};
    //@}
    QCPGraph *center {nullptr}; //!< Corresponding figure that represents a triangle center on the plot.
    /** @brief Function pointer indicating the definition of the point. */
    void (TriangleCentersNode::*definition)() {nullptr};

    virtual void print() const override; /**< @brief Prints all data components of the triangle center (Debugging purposes only). */
    virtual void display(Ui::MainWindow *ui) override; /**< @brief Updates the corresponding figure on the plot (*center). */
    virtual void access(double data[]) const override; /**< @brief Sets the array data as {x coordinate, y coordinate} of the triangle center. */
    virtual void mutate(double data[]) override; /**< @brief Edits the triangle center based on data = {new bary_a, new bary_b, new bary_c}. */

    virtual void update() override; /**< @brief Updates the construction to adjust for changes of the parents. */
    /** @brief Takes a collection of string vectors and adds the label of the line to the point_labels vector. */
    virtual void labels(vector<string>*point_labels, vector<string>*, vector<string>*, vector<string>*) const override;

    void cartesian(double data []) const; /**< @brief Performs conversion from barycentric coordinates to cartesian. */

    void centroid(); /**< @brief Defines a triangle center that corresponds to the centroid. */
    void incenter(); /**< @brief Defines a triangle center that corresponds to the incenter. */
    void circumcenter(); /**< @brief Defines a triangle center that corresponds to the circumcenter. */
    void orthocenter(); /**< @brief Defines a triangle center that corresponds to the orthocenter. */
    void ninepointcenter(); /**< @brief Defines a triangle center that corresponds to the nine-point center. */
    void symmedian(); /**< @brief Defines a triangle center that corresponds to the Lemoine point. */

};

#endif /* TRIANGLECENTERSNODE_H_ */
