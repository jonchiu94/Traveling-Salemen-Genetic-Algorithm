
#include <ostream>
#include "city.hpp"
city::city(int x, int y):x{x}, y{y}, id{++serial_num} {

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
