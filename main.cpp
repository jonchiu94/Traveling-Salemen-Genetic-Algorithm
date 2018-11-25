#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "city.hpp"
#include "tour.hpp"
#include "population.hpp"
using namespace std;

constexpr int CITIES_IN_TOUR = 32;
constexpr int POPULATION_SIZE = 32;
constexpr int SHUFFLES = 64;
constexpr int MAP_BOUNDRY = 1000;




int random_int(const int & min, const int & max) {
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max);
    return uni(rng);
}
city create_cities(){
    city* new_city = new city(random_int(0, MAP_BOUNDRY), random_int(0, MAP_BOUNDRY));
    return *new_city;
}
tour create_tour(){
    vector<city> tour_list;
    for(int i = 0; i < CITIES_IN_TOUR; i++){
        tour_list.push_back(create_cities());
    }
    tour* new_tour = new tour(tour_list);
    return *new_tour;
}
population create_population(){
    vector<tour> population_list;
    tour new_tour = create_tour();
    for(int i = 0; i <= POPULATION_SIZE; i++){
        new_tour.shuffle_cities();
        population_list.push_back(new_tour);
    }
    population* new_population= new population(population_list);
    return *new_population;
}

int main() {
    population temp_tour = create_population();
    temp_tour.tour_evaluate();
    cout << temp_tour << "\r\n";

    return 0;
}