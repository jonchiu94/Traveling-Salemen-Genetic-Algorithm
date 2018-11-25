//
// Created by User on 11/22/2018.
//


#include "population.hpp"
population::population(vector<tour> population):population_list{move(population)} {

}
int population::random_int(const int & min, const int & max) {
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min,max);
    return uni(rng);
}

default_random_engine generator(time(nullptr));
double population::random_double(double min_double, double max_double) {
    uniform_real_distribution<double> distribution(min_double, max_double);
    double random_double = distribution(generator);
    return random_double;
}
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
tour population::get_elite_tour() {
    return population_list[elite_tour()];
}
void population::move_elite_tour() {
    int elite_pos = elite_tour();
    population_list.insert(population_list.begin(), population_list[elite_pos]);
    population_list.erase(population_list.begin()+(elite_pos+1));
}
tour population::two_parent_cross(tour tour1, tour tour2) {
    int pos =0;
    vector<city> temp;
    tour* temp_tour = new tour(temp);
    vector<city> temp_tour_list = tour1.getTour_list();
    vector<city> temp_tour_list2 = tour2.getTour_list();
    int rand = random_int(0, temp_tour_list.size());
    for(int i = 0; i <= rand; i++){
        temp_tour->add_city(temp_tour_list[i]);
    }
    for(int j = rand; j < temp_tour_list2.size(); j++){
        if(!temp_tour->contains_city(temp_tour_list2[j])){
            temp_tour->add_city(temp_tour_list2[j]);
        }
    }
    while(temp_tour->getTour_list().size() < temp_tour_list2.size()){
        if(!temp_tour->contains_city(temp_tour_list2[pos])){
            temp_tour->add_city(temp_tour_list2[pos]);
        }
        pos++;
    }
    return *temp_tour;

}
tour population::three_parent_cross(tour tour1, tour tour2, tour tour3) {
    int pos =0;
    vector<city> temp;
    tour* temp_tour = new tour(temp);
    vector<city> temp_tour_list = tour1.getTour_list();
    vector<city> temp_tour_list2 = tour2.getTour_list();
    vector<city> temp_tour_list3 = tour3.getTour_list();
    int rand = random_int(0, temp_tour_list.size());
    int rand2 = random_int(0, temp_tour_list.size());
    for(int i = 0; i <= rand; i++){
        temp_tour->add_city(temp_tour_list[i]);
    }
    for(int j = rand; j <= rand2; j++){
        if(!temp_tour->contains_city(temp_tour_list2[j])){
            temp_tour->add_city(temp_tour_list2[j]);
        }
    }
    for(int k = rand2; k < temp_tour_list3.size(); k++){
        if(!temp_tour->contains_city(temp_tour_list3[k])){
            temp_tour->add_city(temp_tour_list3[k]);
        }
    }
    while(temp_tour->getTour_list().size() < temp_tour_list3.size()){
        if(!temp_tour->contains_city(temp_tour_list3[pos])){
            temp_tour->add_city(temp_tour_list3[pos]);
        }
        pos++;
    }
    return *temp_tour;

}
bool population::is_same_parent_pool(vector<tour> A, vector<tour> B) {
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < B.size(); j++) {
            if (A[i] == B[j]) {
                return true;
            }
        }
    }
    return false;
}
void population::crossover() {
    move_elite_tour();
    double base_distance = population_list[0].get_tour_distance();
    for(int i = NUMBER_OF_ELITES; i < population_list.size(); i++){
        vector<tour> temp_pool = create_parent_pool();
        population* temp_pop = new population(temp_pool);
        vector<tour> temp_pool2 = create_parent_pool();
        population* temp_pop2 = new population(temp_pool);
        while(is_same_parent_pool(temp_pool, temp_pool2)){
            temp_pool = create_parent_pool();
            temp_pop = new population(temp_pool);
            temp_pool2 = create_parent_pool();
            temp_pop2 = new population(temp_pool);
        }
        temp_pop->tour_evaluate();
        temp_pop2->tour_evaluate();
        if(NUMBER_OF_PARENTS == 2){
            tour temp_tour = two_parent_cross(temp_pop->get_elite_tour(), temp_pop2->get_elite_tour());
            population_list[i]=(temp_tour);
        }
        else if(NUMBER_OF_PARENTS == 3){
            vector<tour> temp_pool3 = create_parent_pool();
            population* temp_pop3 = new population(temp_pool);
            temp_pop->tour_evaluate();
            tour temp_tour = three_parent_cross(temp_pop->get_elite_tour(), temp_pop2->get_elite_tour(), temp_pop3->get_elite_tour());
            population_list[i]=(temp_tour);
        }
    }
}
void population::mutate(){
    int rand_int = random_int(NUMBER_OF_ELITES, population_list.size());
    for(int i = 0; i < population_list[rand_int].getTour_list().size(); i++){
        double rand_double = random_double(0.0, 1.0);
        if (rand_double< MUTATION_RATE){
            population_list[rand_int].mutate(i);
        }
    }
}
vector<tour> population::create_parent_pool() {
    vector<tour> temp_pool;
    for(int i =NUMBER_OF_ELITES; i < PARENT_POOL_SIZE; ++i){
        int rand = random_int(NUMBER_OF_ELITES, population_list.size());
        while(find(temp_pool.begin(), temp_pool.end(), population_list[rand]) != temp_pool.end()) {
            rand = random_int(NUMBER_OF_ELITES, population_list.size());
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
