/***************************************************************************
This class, GeoNode, serves as an abstract data class from which all of
our geometric constructions are derived.
****************************************************************************/

#ifndef GEONODE_H_
#define GEONODE_H_

#include <iostream>
#include <cmath>
#ifndef SOLVER
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#endif
using namespace std;

enum GeoNodeType{
		POINT,
		LINE,
		CIRCLE,
		TRIANGLE,
		TRIANGLECENTERS,
		DEFAULT
};
class GeoNode {
    friend class GeoComponents; /**< @brief GeoComponents is the container class for all of our constructions. */
		bool operator == (const GeoNode &Node) const {
			if(type != Node.get_type() || type == DEFAULT || !well_defined || !Node.is_well_defined()) return false;
			if(type == POINT) {
				double data[2], compare_data[2];
				access(data);
				Node.access(compare_data);
				if(abs(data[0] - compare_data[0]) > 1e-8) return false;
				if(abs(data[1] - compare_data[1]) > 1e-8) return false;
				return true;
			}
			else if(type == CIRCLE || type == TRIANGLE) {
				double data[3], compare_data[3];
				access(data);
				Node.access(compare_data);
				if(abs(data[0] - compare_data[0]) > 1e-8) return false;
				if(abs(data[1] - compare_data[1]) > 1e-8) return false;
				if(abs(data[2] - compare_data[2]) > 1e-8) return false;
				return true;
			}
			else if(type == TRIANGLE || type == TRIANGLECENTERS) {
				double data[3], compare_data[3];
				access(data);
				Node.access(compare_data);
				double norm, compare_norm;
				norm = sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
				compare_norm = sqrt(compare_data[0] * compare_data[0] + compare_data[1] * compare_data[1] + compare_data[2] * compare_data[2]);
				if(norm < 1e-8 || compare_norm < 1e-8) {
					if(norm < 1e-8 && compare_norm < 1e-8) return true;
					else return false;
				}
				for(int i = 0; i < 3; i++){
					data[i] /= norm;
					compare_data[i] /= compare_norm;
				}
				if(abs(data[0] - compare_data[0]) > 1e-8) return false;
				if(abs(data[1] - compare_data[1]) > 1e-8) return false;
				if(abs(data[2] - compare_data[2]) > 1e-8) return false;
				return true;
			}
		}
public:
    GeoNode(int num_parents = 0); /**< @brief Constructor, takes the number of constructions (parents) that define this construction (child). */

    virtual void access(double data[]) const = 0; /**< @brief Takes an array and sets it to be the data members of the construction. */
    //!< The required size of the array and the data contained varies by construction (2 < size < 9).
    string get_label() const; /**< @brief This function returns the label of the construction. */

    virtual ~GeoNode(); /**< @brief Destructor */

		bool is_well_defined() const;
		GeoNodeType get_type() const;

private:
    virtual void print() const = 0; /**< @brief This function prints to console the data components of the construction (Debugging purposes only). */
    virtual void mutate(double data[]) = 0; /**< @brief This function can be used to edit the data members of the construction. */
    virtual void update() = 0; /**< @brief This function updates the constructions by recalculating the data to adjust to changes on the parents. */
    /** @brief The following function takes a collection of string vectors and adds the label of the construction to the corresponding one. */
    virtual void labels(vector<string>* point_labels, vector<string>* line_labels, vector<string>* circle_labels, vector<string>* triangle_labels) const = 0;

    unsigned int pid {0}; /**< @brief Index at which this construction is located on the vector. (For developer use only) */
    string label {""}; /**< @brief Server as identifyer of the construction. */

		#ifndef SOLVER
		virtual void display(Ui::MainWindow* ui) = 0; /**< @brief This function updates the figure representing the construction on the plot. */
		#endif
		GeoNodeType type{DEFAULT};
protected:
    const int num_parents {0}; /**< @brief Number of constructions that defines this construction. */
    const GeoNode** parents {nullptr}; /**< @brief Pointer to the array of constructions that define this construction. */
    bool well_defined {true}; /**< @brief Indicates wheter the current configuration gives a well defined construction. */
    bool need_display {true}; /**< @brief Indicates wheter we would like to display this construction on the plot. */

};

#endif /* GEONODE_H_ */
