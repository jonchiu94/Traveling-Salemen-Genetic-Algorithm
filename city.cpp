
#include <ostream>
#include "city.hpp"
//City constructor
//@param x is x coordinate
//@param y is y coordinate
//@param id is unique city id
city::city(int x, int y):x{x}, y{y}, id{++serial_num} {

}
//City copy constructor
//@param city is city object to be copied
city::city(const city &c): id{c.id}, x{c.x}, y{c.y}{

}
//city destructor
city::~city(){

};
//overloaded assignment operator
//@param city2 is city to be assigned
city& city::operator=(city city2){
    swap(*this, city2);
    return *this;
}
//friendly swap function
//@param city1 is city object
//@param city2 is city object
void swap(city& city1,city& city2){
    using std::swap;
    swap(city1.id, city2.id);
    swap(city1.x, city2.x);
    swap(city1.y, city2.y);
}
//Overloaded == operator
//@param A is city object to be compared
//@param B is city object to be compared
bool operator==(const city &A, const city &B){
    return((A.getId() == B.getId()) && (A.getX() == B.getX())&&(B.getY()== B.getY()));
}
bool operator!=(const city &A, const city &B){
    return !operator==(A,B);
}
ostream& operator<<(ostream& os, const city& A){
    os<< "ID: " << A.getId() << " X: " << A.getX() << " Y: "<< A.getY() << "\r\n";
    return os;
}
int city::getX() const {
    return x;
}

int city::getY() const {
    return y;
}

int city::getId() const {
    return id;
}
