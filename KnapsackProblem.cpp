#include "KnapsackProblem.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

KnapsackProblem::KnapsackProblem() {
    fileName = "";
    itemsAmount = 0;
    maxLoad = 0;
    isDataLoaded = false;
}

KnapsackProblem::KnapsackProblem(const string& fileName) {
    this->fileName = fileName;
    itemsAmount = 0;
    maxLoad = 0;
    isDataLoaded = false;
}

void KnapsackProblem::loadData() {
    if(isDataLoaded) {
        return;
    }

    string line;
    ifstream input(fileName);
    int lineNum = 1;

    if(!input.is_open()) {
        throw runtime_error("Error while opening file (" + fileName + ")");
    }

    if(!getline(input, line)) {
        throw runtime_error("Error empty file (" + fileName + ")");
    }

    stringstream ss(line);
    double temp;
    if(!(ss >> temp)) {
        throw runtime_error("Invalid max load type (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
    }

    maxLoad = temp;
    if(ss >> temp) {
        throw runtime_error("Invalid max load format (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
    }

    if(maxLoad <= 0) {
        throw runtime_error("Max load must be greater than 0 (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
    }

    double l, v;
    bool containsAnyItems = false;
    while(getline(input, line)) {
        lineNum++;
        containsAnyItems = true;
        ss.clear();
        ss.str(line);

        if(!(ss >> l >> v)) {
            throw runtime_error("Invalid load/value format in line (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
        }

        if(ss >> temp) {
            throw runtime_error("Invalid load/value format in line (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
        }

        if(l < 0 || v < 0) {
            throw runtime_error("Load/value must be grater than 0 (" + fileName + ")\n" + to_string(lineNum) + " | " + line);
        }

        loads.push_back(l);
        values.push_back(v);
        itemsAmount++;
    }

    if(!containsAnyItems) {
        throw runtime_error("Error file doesn't contain any item load/value (" + fileName + ")");
    }

    if(!input.eof()) {
        throw runtime_error("Error while reading file (" + fileName + ")");
    }

    input.close();
    isDataLoaded = true;
}

bool KnapsackProblem::getIsDataLoaded() const {
    return isDataLoaded;
}

double KnapsackProblem::evaluate(const vector<int>& genotype) const {
    double load = 0;
    double val = 0;
    for(int i = 0; i < genotype.size(); i++) {
        if(genotype[i] == 1) {
            load += loads[i];
            val += values[i];
        }
    }

    if(load > maxLoad)
        return 0;
    return val;
}

int KnapsackProblem::getItemsAmount() const {
    return itemsAmount;
}

double KnapsackProblem::getLoad(const vector<int> &genotype) const {
    double load = 0;
    for(int i = 0; i < genotype.size(); i++) {
        if(genotype[i] == 1) {
            load += loads[i];
        }
    }

    return load;
}

double KnapsackProblem::getMaxLoad() const {
    return maxLoad;
}
