#pragma once

#include <list>
#include <vector>
#include "city.hpp"
using namespace std;
constexpr double SCALAR = 1000.0;
class tour {
private:
    vector<city> tour_list;
    double fitness;
    double distance;
public:
    tour(vector<city> tours);
    tour(const tour &tour1);
    ~tour();
    const vector<city> &getTour_list() const;
    double getDistance() const;
    double getFitness() const;
    void shuffle_cities();
    double get_city_distance(city &A, city &B);
    double get_tour_distance();
    void determine_fitness();
    bool contains_city(city &A);
    void add_city(city &A);
    tour& operator=(tour tour2);
    friend bool operator==(const tour &A, const tour &B);
    friend ostream &operator<< (ostream &os, const tour &A);
    friend void swap(tour& tour1, tour& tour2);

};


