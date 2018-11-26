//
// Created by User on 11/22/2018.
//


#include <iostream>
#include "population.hpp"
//Population constructor
population::population(vector<tour> population):population_list{move(population)} {

}
//Random integer generator
//Returns a random int
//@param min is min for random number
//@param max is max for random number
int population::random_int(const int & min, const int & max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max);
    return uni(rng);
}
//Seed for uniform double generation
default_random_engine generator(time(nullptr));
//Random double generator
//Returns a random double
//@param min is min_double for random number
//@param max is max_double for random number
double population::random_double(double min_double, double max_double) {
    uniform_real_distribution<double> distribution(min_double, max_double);
    double random_double = distribution(generator);
    return random_double;
}
//Finds the fittest tour and returns position
int population::elite_tour() {
    double fitness = 0.0;
    int pos = 0;
    for(int i = 0; i < population_list.size(); i++){
        population_list[i].determine_fitness();
        if(fitness < population_list[i].getFitness()){
            fitness = population_list[i].getFitness();
            pos = i;
        }
    }
    return pos;
}
//Returns the fittest tour
tour population::get_elite_tour() {
    return population_list[elite_tour()];
}
//Moves elite tour to front of population
void population::move_elite_tour() {
    int elite_pos = elite_tour();
    population_list.insert(population_list.begin(), population_list[elite_pos]);
    population_list.erase(population_list.begin()+(elite_pos+1));
}

tour population::five_parent_cross(tour tour1, tour tour2, tour tour3, tour tour4, tour tour5) {
    int pos =0;
    vector<city> temp;
    tour* temp_tour = new tour(temp);
    vector<city> temp_tour_list = tour1.getTour_list();
    vector<city> temp_tour_list2 = tour2.getTour_list();
    vector<city> temp_tour_list3 = tour3.getTour_list();
    vector<city> temp_tour_list4 = tour3.getTour_list();
    vector<city> temp_tour_list5 = tour3.getTour_list();
    int rand = random_int(0, temp_tour_list.size());
    int rand2 = random_int(0, temp_tour_list.size());
    int rand3 = random_int(0, temp_tour_list.size());
    int rand4 = random_int(0, temp_tour_list.size());
    int rand5 = random_int(0, temp_tour_list.size());
    for(int i = 0; i <= rand; i++){
        temp_tour->add_city(temp_tour_list[i]);
    }
    for(int j = 0; j <= rand2; j++){
        if(!temp_tour->contains_city(temp_tour_list2[j])){
            temp_tour->add_city(temp_tour_list2[j]);
        }
    }
    for(int k = 0; k < rand3; k++){
        if(!temp_tour->contains_city(temp_tour_list3[k])){
            temp_tour->add_city(temp_tour_list3[k]);
        }
    }
    for(int l = 0; l < rand4; l++){
        if(!temp_tour->contains_city(temp_tour_list4[l])){
            temp_tour->add_city(temp_tour_list4[l]);
        }
    }
    for(int m = 0; m < rand5; m++){
        if(!temp_tour->contains_city(temp_tour_list5[m])){
            temp_tour->add_city(temp_tour_list5[m]);
        }
    }
    while(temp_tour->getTour_list().size() < temp_tour_list5.size()){
        if(!temp_tour->contains_city(temp_tour_list5[pos])){
            temp_tour->add_city(temp_tour_list5[pos]);
        }
        pos++;
    }
    return *temp_tour;

}

void population::crossover() {
    move_elite_tour();
    for(int i = NUMBER_OF_ELITES; i < population_list.size(); i++){
        vector<tour> temp_pool = create_parent_pool();
        vector<tour> temp_pool2 = create_parent_pool();
        vector<tour> temp_pool3 = create_parent_pool();
        vector<tour> temp_pool4 = create_parent_pool();
        vector<tour> temp_pool5 = create_parent_pool();
        population* temp_pop = new population(temp_pool);
        population* temp_pop2 = new population(temp_pool);
        population* temp_pop3 = new population(temp_pool);
        population* temp_pop4 = new population(temp_pool);
        population* temp_pop5 = new population(temp_pool);
        temp_pop->tour_evaluate();
        temp_pop2->tour_evaluate();
        temp_pop3->tour_evaluate();
        temp_pop4->tour_evaluate();
        temp_pop5->tour_evaluate();
        for(int i = 0; i < NUMBER_OF_PARENTS; i++){

            tour temp_tour = five_parent_cross(temp_pop->get_elite_tour(), temp_pop2->get_elite_tour(), temp_pop3->get_elite_tour(), temp_pop4->get_elite_tour(), temp_pop5->get_elite_tour());
            population_list[i]=(temp_tour);
        }
    }
}
void population::mutate(){
    int rand_int = random_int(NUMBER_OF_ELITES, population_list.size()-1);
    for(int i = 0; i < population_list[rand_int].getTour_list().size()-1; i++){
        double rand_double = random_double(0.0, 1.0);
        if (rand_double< MUTATION_RATE){
            population_list[rand_int].mutate(i);
        }
    }
}
void population::genetic_algorithm() {
    int num = 0;
    tour_evaluate();
    move_elite_tour();
    double base_distance = population_list[0].get_tour_distance();
    double best_distance = population_list[0].get_tour_distance();
    improvement_percentage = (best_distance/base_distance) *100;
    while(num < ITERATIONS){
        cout<< "Iteration #: " << num << "\r\n";
        tour_evaluate();
        crossover();
        mutate();
        tour_evaluate();
        move_elite_tour();
        best_distance = population_list[0].get_tour_distance();
        improvement_percentage = (best_distance/base_distance-1) * 100;
        cout<< improvement_percentage <<  "% \r\n";
        num++;
    }
    cout<<"Best tour \r\n";
    cout<<get_elite_tour() << endl;
}
vector<tour> population::create_parent_pool() {
    vector<tour> temp_pool;
    temp_pool.clear();
    for(int i =NUMBER_OF_ELITES; i < PARENT_POOL_SIZE; ++i){
        int rand = random_int(NUMBER_OF_ELITES, population_list.size()-1);
        while(find(temp_pool.begin(), temp_pool.end(), population_list[rand]) != temp_pool.end()) {
            rand = random_int(NUMBER_OF_ELITES, population_list.size()-1);
        }
        temp_pool.push_back(population_list[rand]);
    }
    return temp_pool;
}
void population::tour_evaluate() {
    for(tour& i : population_list){
        i.determine_fitness();
    }
}
ostream &operator<<(ostream &os, const population &A){
    for(const tour& i: A.getPopulation_list()){
        os << i;
    }
}

const vector<tour> &population::getPopulation_list() const {
    return population_list;
}
