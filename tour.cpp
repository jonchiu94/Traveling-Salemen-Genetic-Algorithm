#include "tour.hpp"
#include <algorithm>
tour::tour(vector<city> tours): tour_list{move(tours)}{

}
void tour::shuffle_cities() {
    random_shuffle(tour_list.begin(), tour_list.end());
}
bool tour::contains_city() {

}
const vector<city> &tour::getTour_list() const {
    return tour_list;
}

double tour::getFitness() const {
    return fitness;
}
