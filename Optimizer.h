#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Rule.h"

class Optimizer {

private:

    // Maybe could statically allocate these? Don't we have a finite number of rules?
    Rule** rules;
    int ruleCount;

    // TEMPORARY FOR DEBUGGING
    int ruleFitnesses[9];
    std::string ruleNames[9] {"Rule_TimeConflict", "Rule_CampusTime", "Rule_NextDay", "Rule_TwoEvenings", "Rule_BackToBack", "Rule_AroundCommon", "Rule_ClassesPerDay", "Rule_LongClassesPerDay", "Rule_BadTime"};


public:

    Optimizer();

    ~Optimizer();


    // I think this functions job will be to find the sum of all of the rule objects getFitness() functions
    //
    virtual int getScheduleFitness(Schedule* schedule);


    // Operation that prints out results of Optimization of a schedule. Used primarily for debugging.
    //
    virtual void displayFitnessBreakdown(Schedule* schedule);

};

#endif