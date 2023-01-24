#ifndef LIST6_MINIPROJECT_KNAPSACKPROBLEM_H
#define LIST6_MINIPROJECT_KNAPSACKPROBLEM_H

#include <vector>
#include <string>
#include <tuple>

using namespace std;

class KnapsackProblem {
public:
    KnapsackProblem();
    KnapsackProblem(const string& fileName);
    ~KnapsackProblem() = default;
    double evaluate(const vector<int>& genotype) const;
    int getItemsAmount() const;
    double getLoad(const vector<int>& genotype) const;
    bool getIsDataLoaded() const;
    void loadData();
    double getMaxLoad() const;

private:
    int itemsAmount;
    double maxLoad;
    vector<double> loads;
    vector<double> values;
    string fileName;
    bool isDataLoaded;
};


#endif //LIST6_MINIPROJECT_KNAPSACKPROBLEM_H
