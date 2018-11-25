
#include <ostream>
#include "city.hpp"
city::city(int x, int y):x{x}, y{y}, id{++serial_num} {

}
city::city(const city &c): id{c.id}, x{c.x}, y{c.y}{

}
city::~city(){

};
city& city::operator=(city city2){
    swap(*this, city2);
    return *this;
}
void swap(city& city1,city& city2){
    using std::swap;
    swap(city1.id, city2.id);
    swap(city1.x, city2.x);
    swap(city1.y, city2.y);
}
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
