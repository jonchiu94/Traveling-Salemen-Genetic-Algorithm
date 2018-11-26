#include "tour.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>
//Tour constructor
//@param tours is a vector of city objects
tour::tour(vector<city> tours): tour_list{move(tours)}{

}
//Tour copy constructor
//@param tour1 as tour object to be copied
tour::tour(const tour &tour1): tour_list{tour1.getTour_list()}, distance {tour1.getDistance()}, fitness{tour1.getFitness()}{
}
//Tour destructor
tour::~tour() {
}
//Shuffles the city in tour list
void tour::shuffle_cities() {
    random_shuffle(tour_list.begin(), tour_list.end());
}
//Checks to see if city object exists in tour list
//@param A as city object
bool tour::contains_city(city &A) {
    for(city &i : tour_list){
        if(i == A){
            return true;
        }
    }
    return false;
}
//Adds city to tour list
//@param A as city object to be added
void tour::add_city(city &A) {
    tour_list.push_back(A);
}
//Getter for tour list
//returns tour list
const vector<city> &tour::getTour_list() const {
    return tour_list;
}
//Calculates the tour distance
//returns tour distance as double
double tour::get_tour_distance() {
    double tour_distance = 0;
    for(int i = 0; i < tour_list.size() - 1; i++){
        tour_distance += get_city_distance(tour_list[i], tour_list[i+1]);
    }
    distance = tour_distance;
    return tour_distance;
}
//Calculates city distance
//@param a as city object
//@param b as city object
double tour::get_city_distance(city &a, city &b) {
    double city_distance = sqrt(pow((b.getX() - a.getX()), 2) + pow((b.getY()- a.getY()), 2));
    return city_distance;
}
//Calculates the fitness of tour
void tour::determine_fitness() {
    double tour_distance = get_tour_distance();
    fitness = (1/tour_distance) * SCALAR;
}
//overloaded assignment operator
//@param tour2 is tour object to be assigned
tour& tour::operator=(tour tour2){
    swap(*this, tour2);
    return *this;
}
//overloaded insertion operator
//@param os as ostream object
//@param a as tour object
ostream& operator<<(ostream& os, const tour& A){
    for(const city &i: A.getTour_list())
      os << i ;
    os << "Fitness: " << A.getFitness() << " Distance: " << A.getDistance() << "\r\n";
    return os;
}
//overloaded == operator
//@param a as tour object
//@param b as tour object
bool operator==(const tour &A, const tour &B){
    vector<city> tour_list1 =  A.getTour_list();
    vector<city> tour_list2 =  B.getTour_list();
    for(int i = 0; i < tour_list1.size(); i++){
        if(tour_list1[i] != tour_list2[i]){
            return false;
        }
    }
    return true;
}
//Swap function to swap tour objects
//@param tour1 as tour object to be swapped
//@param tour2 as tour object to be swapped
void swap(tour& tour1,tour& tour2){
    using std::swap;
    swap(tour1.tour_list, tour2.tour_list);
    swap(tour1.fitness, tour2.fitness);
    swap(tour1.distance, tour2.distance);
}
//Mutate function
//@param pos a city to be mutated
void tour::mutate(int pos) {
    city temp_city = tour_list[pos];
    tour_list[pos] = tour_list[pos+1];
    tour_list[pos+1] = temp_city;
}
//getter for fitness
//returns fitness as double
double tour::getFitness() const {
    return fitness;
}
//getter for distance
//returns distance as double
double tour::getDistance() const {
    return distance;
}
