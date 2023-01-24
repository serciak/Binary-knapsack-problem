#include <random>
#include <utility>
#include "Individual.h"
#include <iostream>
using namespace std;

Individual::Individual(int itemsAmount) {
    fitness = -1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);

    for(int i = 0; i < itemsAmount; i++) {
        genotype.push_back(distribution(gen));
    }
}

Individual::Individual(vector<int>&& genotype) {
    this->genotype = genotype;
    fitness = -1;
}

double Individual::calculateFitness(const KnapsackProblem& kp) {
    if(fitness > -1) {
        return fitness;
    }

    fitness = kp.evaluate(genotype);
    return fitness;
}

void Individual::mutate(const double mutProb) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(0, 1);

    for(int & i : genotype) {
        if(distribution(gen) < mutProb) {
            if(i == 0) i = 1;
            else i = 0;
        }
    }

    fitness = -1;
}

vector<Individual> Individual::cross(const Individual &other) const {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, genotype.size()-1);

    int index = distribution(gen);
    vector<int> g1, g2;

    for(int i = 0; i < index; i++) {
        g1.push_back(genotype[i]);
        g2.push_back(other.genotype[i]);
    }

    for(int i = index; i < genotype.size(); i++) {
        g1.push_back(other.genotype[i]);
        g2.push_back(genotype[i]);
    }

    return vector<Individual> {Individual(std::move(g1)), Individual(std::move(g2))};
}

vector<int> Individual::getGenotype() const {
    return genotype;
}
