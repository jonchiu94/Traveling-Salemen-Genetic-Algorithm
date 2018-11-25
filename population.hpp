//
// Created by User on 11/22/2018.
//

#pragma once
#include <vector>
#include "tour.hpp"
#include <random>
#include <algorithm>

constexpr int PARENT_POOL_SIZE = 5;
const int NUMBER_OF_ELITES = 1;
const int NUMBER_OF_PARENTS = 2;
constexpr int ITERATIONS = 1000;
constexpr double MUTATION_RATE = 0.05;

class population {
private:
    vector<tour>population_list;

public:
    const vector<tour> &getPopulation_list() const;
    population(vector<tour> population);
    int elite_tour();
    tour get_elite_tour();
    void move_elite_tour();
    void crossover();
    int random_int(const int & min, const int & max);
    double random_double(double min_double, double max_double);
    tour two_parent_cross(tour tour1, tour tour2);
    tour three_parent_cross(tour tour1, tour tour2, tour tour3);
    void mutate();
    void tour_evaluate();
    bool is_same_parent_pool(vector<tour> A, vector<tour> B);
    vector<tour> create_parent_pool();
    friend ostream &operator<<(ostream &os, const population &A);
};



