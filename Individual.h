#ifndef LIST6_MINIPROJECT_INDIVIDUAL_H
#define LIST6_MINIPROJECT_INDIVIDUAL_H

#include <vector>
#include "KnapsackProblem.h"

using namespace std;

class Individual {
public:
    Individual(int itemsAmount);
    Individual(vector<int>&& genotype);
    double calculateFitness(const KnapsackProblem& kp);
    void mutate(double mutProb);
    vector<Individual> cross(const Individual& other) const;
    vector<int> getGenotype() const;

private:
    vector<int> genotype;
    double fitness;
};


#endif //LIST6_MINIPROJECT_INDIVIDUAL_H
