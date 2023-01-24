#include <iostream>
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"

int main() {
    try {
        KnapsackProblem kp("knapsack_problem.txt");
        kp.loadData();

        GeneticAlgorithm ga(200, 0.1, 0.8, 500, kp);
        ga.run();

        tuple<double, double, vector<int>> result = ga.getBestSolution();
        cout << "Result value: " << get<0>(result) << endl;
        cout << "Result load: " << get<1>(result) << "/" << kp.getMaxLoad() << endl;
        cout << "Result genotype: ";
        std::copy(get<2>(result).begin(),
                  get<2>(result).end(),
                  std::ostream_iterator<int>(std::cout, " "));
    }
    catch(exception& e) {
        cout << e.what();
        return -1;
    }

    return 0;
}
