/***************************************************************************
This class, GeoNode, serves as an abstract base class from which all of
our geometric constructions are derived.
****************************************************************************/

#ifndef GEONODE_H_
#define GEONODE_H_

#include <iostream>
#include "ui_mainwindow.h"
#include "qcustomplot.h"

using namespace std;
class GeoNode {
    friend class GeoComponents; /**< @brief GeoComponents is the container class for all of our constructions. */

public:
    GeoNode(int num_parents = 0); /**< @brief Constructor, takes the number of constructions (parents) that define this construction (child). */

    virtual void access(double data[]) const = 0; /**< @brief Takes an array and sets it to be the data members of the construction, the size may vary. */
    string get_label() const; /**< @brief This function returns the label of the construction. */

    virtual ~GeoNode(); /**< @brief Destructor */
	
private:
    virtual void print() const = 0; /**< @brief Prints to console the data components of the construction (Debugging purposes only). */
    virtual void display(Ui::MainWindow* ui) = 0; /**< @brief Updates the figure representing the construction on the plot. */
    virtual void mutate(double data[]) = 0; /**< @brief Edits the data members of the construction. */
    virtual void update() = 0; /**< @brief Updates the constructions by recalculating the data to adjust to changes on the parents. */
    /** @brief Takes a collection of string vectors and adds the label of the construction to the corresponding vector. */
    virtual void labels(vector<string>* point_labels, vector<string>* line_labels, vector<string>* circle_labels, vector<string>* triangle_labels) const = 0;

    unsigned int pid {0}; /**< @brief Index at which this construction is located on the vector. (For developer use only) */
    string label {""}; /**< @brief Server as identifier of the construction. */

protected:
    const int num_parents {0}; /**< @brief Number of constructions that defines this construction. */
    const GeoNode** parents {nullptr}; /**< @brief Pointer to the array of constructions that define this construction. */
    bool well_defined {true}; /**< @brief Indicates whether the current configuration gives a well-defined construction. */
    bool need_display {true}; /**< @brief Indicates whether display of this construction on the plot is needed. */
    static const double EPSILON; /** @brief Sets the error tolerance used in our calculations. */
};

#endif /* GEONODE_H_ */
