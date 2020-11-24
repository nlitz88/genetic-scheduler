#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Rule.h"

class Optimizer {

private:

    // Maybe could statically allocate these? Don't we have a finite number of rules?
    Rule** rules;
    int ruleCount;

    long fitness;


public:

    Optimizer();

    ~Optimizer();


    // I think this functions job will be to find the sum of all of the rule objects getFitness() functions
    virtual long getScheduleFitness(Schedule* schedule);

};

#endif