#include "Optimizer.h"


Optimizer::Optimizer() {

    // Predetermined number of rules. Must use pointers, however, in order to take advantage of polymorphic nature of rule.
    ruleCount = 3;
    rules = new Rule* [ruleCount] {new Rule_TimeConflict(), new Rule_CampusTime(), new Rule_BackToBack()};

}

Optimizer::~Optimizer() {

    // Release memory maintaining each rule object
    for(int r = 0; r < ruleCount; ++r) {
        delete rules[r];
    }

    // Release memory maintaining each pointer to Rule object that make up our collection of rules.
    delete [] rules;

}


long Optimizer::getScheduleFitness(Schedule* schedule) {

    // Reset fitnes value
    fitness = 0;

    // Then, calculate fitness value using each rule
    for(int r = 0; r < ruleCount; ++r) {

        rules[r]->getFitness(schedule);
        fitness += rules[r]->fitnessValue();

    }

    return fitness;

}