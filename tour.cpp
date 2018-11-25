#include "tour.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>

tour::tour(vector<city> tours): tour_list{move(tours)}{

}
tour::tour(const tour &tour1): tour_list{tour1.getTour_list()}, distance {tour1.getDistance()}, fitness{tour1.getFitness()}{
}
tour::~tour() {
}
void tour::shuffle_cities() {
    random_shuffle(tour_list.begin(), tour_list.end());
}
bool tour::contains_city(city &A) {
    for(city &i : tour_list){
        if(&i == &A){
            return true;
        }
    }
    return false;
}
void tour::add_city(city &A) {
    tour_list.push_back(A);
}
const vector<city> &tour::getTour_list() const {
    return tour_list;
}
double tour::get_tour_distance() {
    double tour_distance = 0;
    for(int i = 0; i < tour_list.size() - 1; i++){
        tour_distance += get_city_distance(tour_list[i], tour_list[i+1]);
    }
    distance = tour_distance;
    return tour_distance;
}
double tour::get_city_distance(city &a, city &b) {
    double city_distance = sqrt(pow((b.getX() - a.getX()), 2) + pow((b.getY()- a.getY()), 2));
    return city_distance;
}
void tour::determine_fitness() {
    double tour_distance = get_tour_distance();
    fitness = (1/tour_distance) * SCALAR;
}
tour& tour::operator=(tour tour2){
    swap(*this, tour2);
    return *this;
}
ostream& operator<<(ostream& os, const tour& A){
    for(const city &i: A.getTour_list())
      os << i ;
    os << "Fitness: " << A.getFitness() << " Distance: " << A.getDistance() << "\r\n";
    return os;
}
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
void swap(tour& tour1,tour& tour2){
    using std::swap;
    swap(tour1.tour_list, tour2.tour_list);
    swap(tour1.fitness, tour2.fitness);
    swap(tour1.distance, tour2.distance);
}
void tour::mutate(int pos) {
    city temp_city = tour_list[pos];
    tour_list[pos] = tour_list[pos+1];
    tour_list[pos+1] = temp_city;
}
double tour::getFitness() const {
    return fitness;
}
double tour::getDistance() const {
    return distance;
}
