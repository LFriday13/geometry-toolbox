/***************************************************************************
This class, GeoComponents, serves as the container of all our constructions
(GeoNodes), they are stored as a STL vector of pointers.
****************************************************************************/

#ifndef GEOCOMPONENTS_H_
#define GEOCOMPONENTS_H_

#include <vector>
#include "GeoNode.h"

class GeoComponents {

public:
    GeoComponents(); /**< @brief Constructor */
    /** @brief The following function takes a pointer to a construction and a label, updates the label of the construction and adds it to the back of the vector. */
    void add_construction(GeoNode* geo, string label = "");
    /** @brief The following function takes a pid of a construction and an array of data to update the construction. */
    void edit_construction(unsigned int pid, double data[]); //!< Only points have a degree of freedom, all other constructions are determined by the parents.
    /** @brief The following function takes a pid of a construction and removes it, along with any derived construction (childs) of this construction. */
    void remove_construction(unsigned int pid);
    /** @brief The following function updates all the figures representing the constructions on the plot. */
    void display_all_constructions(Ui::MainWindow *ui);
    /** @brief The following function takes a collection of string vectors and sets them to be the collection of labels of current constructions. */
    void update_ui_labels(vector<string> *point_labels, vector<string> *line_labels, vector<string> *circle_labels, vector<string> *triangle_labels);

    void print_all_constructions(); /**< @brief Prints the information of all the constructions (Debugging purposes only) */

    int get_pid(string label); /**< @brief Takes a label and returns the pid of the construction with the corresponding label, if there is no construction with that label resturns -1. */
    GeoNode* get_construction(unsigned int pid); /**< @brief Takes a pid of a construction and returns a pointer to it, if there is no construction at that index returns a nullptr. */

    virtual ~GeoComponents(); /**< @brief Deletes all constructions */

private:
    vector<GeoNode*> geo_components; /**< @brief STL vector containing pointer to all the constructions. */
    unsigned int next_pid {0}; /**< @brief The pid to be assigned to the next construction added to the vector.*/

};

#endif /* GEOCOMPONENTS_H_ */
