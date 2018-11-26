#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "city.hpp"
#include "tour.hpp"
#include "population.hpp"
using namespace std;


constexpr int SHUFFLES = 64;
//Max longitude and latitude value;
constexpr int MAP_BOUNDRY = 1000;
//Asks user for number of cities in a tour
//returns int representing size of tours
static int get_tour_size(){
    int tour_size;
    cout<<"How many cities in a tour?" <<endl;
    cin>> tour_size;
    return tour_size;
}
//Asks user for number of tours in a population
//returns int representing size of population
static int get_population_size(){
    int pop_size;
    cout<<"How many tours in a population?" <<endl;
    cin>> pop_size;
    return pop_size;
}
//Setting constants for tour size and population size
const int CITIES_IN_TOUR = get_tour_size();
const int POPULATION_SIZE = get_population_size();
//Generates a random integer
//returns a random int
//@param min is min for random number
//@param max is max for random number
int random_int(const int & min, const int & max) {
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max);
    return uni(rng);
}
//Generates a new city
//Returns a city object
city create_cities(){
    city* new_city = new city(random_int(0, MAP_BOUNDRY), random_int(0, MAP_BOUNDRY));
    return *new_city;
}
//Generates a tour
//Returns a tour object
tour create_tour(){
    vector<city> tour_list;
    for(int i = 0; i < CITIES_IN_TOUR; i++){
        tour_list.push_back(create_cities());
    }
    tour* new_tour = new tour(tour_list);
    return *new_tour;
}
//Generates a population
//returns a population object
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
    //Creating a population
    population temp_pop = create_population();
    //Running genetic algorithm
    temp_pop.genetic_algorithm();
    return 0;
}