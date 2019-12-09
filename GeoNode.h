/***************************************************************************
This class, GeoNode, serves as an abstract data class from which all of
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

    virtual void access(double data[]) const = 0; /**< @brief Takes an array and sets it to be the data members of the construction. */
    //!< The required size of the array and the data contained varies by construction (2 < size < 9).
    string get_label() const; /**< @brief This function returns the label of the construction. */

    virtual ~GeoNode(); /**< @brief Destructor */
	
private:
    virtual void print() const = 0; /**< @brief This function prints to console the data components of the construction (Debugging purposes only). */
    virtual void display(Ui::MainWindow* ui) = 0; /**< @brief This function updates the figure representing the construction on the plot. */
    virtual void mutate(double data[]) = 0; /**< @brief This function can be used to edit the data members of the construction. */
    virtual void update() = 0; /**< @brief This function updates the constructions by recalculating the data to adjust to changes on the parents. */
    /** @brief The following function takes a collection of string vectors and adds the label of the construction to the corresponding one. */
    virtual void labels(vector<string>* point_labels, vector<string>* line_labels, vector<string>* circle_labels, vector<string>* triangle_labels) const = 0;

    unsigned int pid {0}; /**< @brief Index at which this construction is located on the vector. (For developer use only) */
    string label {""}; /**< @brief Server as identifyer of the construction. */

protected:
    const int num_parents {0}; /**< @brief Number of constructions that defines this construction. */
    const GeoNode** parents {nullptr}; /**< @brief Pointer to the array of constructions that define this construction. */
    bool well_defined {true}; /**< @brief Indicates wheter the current configuration gives a well defined construction. */
    bool need_display {true}; /**< @brief Indicates wheter we would like to display this construction on the plot. */

};

#endif /* GEONODE_H_ */
