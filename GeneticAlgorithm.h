#ifndef LIST6_MINIPROJECT_GENETICALGORITHM_H
#define LIST6_MINIPROJECT_GENETICALGORITHM_H

#include <vector>
#include "KnapsackProblem.h"
#include "Individual.h"

using namespace std;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int popSize, double mutProb, double crossProb, int generationsAmount, KnapsackProblem& kp);
    ~GeneticAlgorithm() = default;
    void run();
    tuple<double, double, vector<int>> getBestSolution();

private:
    void generatePopulation();
    void findBestSolution();
    void replacePopulation();
    vector<Individual> selection();
    int tournament();

    int popSize;
    double mutProb;
    double crossProb;
    int generationsAmount;
    double bestSolutionValue;
    KnapsackProblem kp;
    vector<int> bestSolution;
    vector<Individual> population;
};


#endif //LIST6_MINIPROJECT_GENETICALGORITHM_H
