#include "GeneticAlgorithm.h"

#include <random>

GeneticAlgorithm::GeneticAlgorithm(int popSize, double mutProb, double crossProb, int generationsAmount, KnapsackProblem &kp) {
    if(popSize < 2) {
        throw runtime_error("Invalid population size: " + to_string(popSize) + ". Should be bigger than 1.");
    }
    if(mutProb < 0 || mutProb > 1) {
        throw runtime_error("Invalid mutation probability: " + to_string(mutProb) + ". Should be between 0 and 1.");
    }
    if(crossProb < 0 || crossProb > 1) {
        throw runtime_error("Invalid cross probability: " + to_string(crossProb) + ". Should be between 0 and 1.");
    }
    if(generationsAmount < 1) {
        throw runtime_error("Invalid amount of generations: " + to_string(generationsAmount) + ". Should be bigger than 0.");
    }
    if(!kp.getIsDataLoaded()) {
        throw runtime_error("Error data wasn't loaded to KnapsackProblem.");
    }

    this->popSize = popSize;
    this->mutProb = mutProb;
    this->crossProb = crossProb;
    this->generationsAmount = generationsAmount;
    this->kp = kp;
    bestSolutionValue = 0;
}

void GeneticAlgorithm::run() {
    generatePopulation();

    for(int i = 0; i < generationsAmount; i++) {
        findBestSolution();
        replacePopulation();
    }

    findBestSolution();
}

void GeneticAlgorithm::generatePopulation() {
    for(int i = 0; i < popSize; i++) {
        population.emplace_back(kp.getItemsAmount());
    }
}

void GeneticAlgorithm::replacePopulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(0, 1);

    vector<Individual> newPopulation;
    vector<Individual> parents;
    vector<Individual> children;

    while(newPopulation.size() != popSize) {
        parents = selection();

        if(popSize - newPopulation.size() == 1) {
            newPopulation.push_back(parents[round(distribution(gen))]);
        }
        else if(distribution(gen) < crossProb) {
            children = parents[0].cross(parents[1]);
            newPopulation.insert(newPopulation.end(), children.begin(), children.end());
        }
    }

    distribution.reset();
    for(Individual individual : newPopulation) {
        if(distribution(gen) < mutProb) {
            individual.mutate(mutProb);
        }
    }

    population = newPopulation;
}

void GeneticAlgorithm::findBestSolution() {
    int index = 0;
    double bestValue = 0;

    for(int i = 0; i < popSize; i++) {
        if(bestValue < population[i].calculateFitness(kp)) {
            index = i;
            bestValue = population[i].calculateFitness(kp);
        }
    }

    if(bestSolutionValue < bestValue) {
        bestSolutionValue = bestValue;
        bestSolution = population[index].getGenotype();
    }
}

tuple<double, double, vector<int>> GeneticAlgorithm::getBestSolution() {
    return make_tuple(bestSolutionValue, kp.getLoad(bestSolution), bestSolution);
}

vector<Individual> GeneticAlgorithm::selection() {
    int index1 = tournament();
    int index2 = tournament();

    while(index1 == index2) {
        index2 = tournament();
    }

    return vector<Individual> {population[index1], population[index2]};
}

int GeneticAlgorithm::tournament() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, popSize-1);

    int index1 = distribution(gen);
    int index2 = distribution(gen);

    if(population[index1].calculateFitness(kp) > population[index2].calculateFitness(kp)) {
        return index1;
    }
    return index2;
}
