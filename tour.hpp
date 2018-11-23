#pragma once

#include <list>
#include <vector>
#include "city.hpp"
using namespace std;
constexpr double SCALAR = 10.0;
class tour {
private:
    vector<city> tour_list;
    double fitness;
    double distance;
public:
    const vector<city> &getTour_list() const;

    double getFitness() const;
    tour(vector<city> tours);
    void shuffle_cities();
    double get_tour_distance();
    double determine_fitness();
    bool contains_city();

};


