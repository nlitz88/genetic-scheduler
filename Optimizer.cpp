// #define DEBUG_OPTIMIZER

#include "Optimizer.h"


Optimizer::Optimizer() {

    // Predetermined number of rules. Must use pointers, however, in order to take advantage of polymorphic nature of rule.
    ruleCount = 9;
    rules = new Rule* [ruleCount] {new Rule_TimeConflict(), new Rule_CampusTime(), new Rule_NextDay(), new Rule_TwoEvenings(), new Rule_BackToBack(), new Rule_AroundCommon(), new Rule_ClassesPerDay(), new Rule_LongClassesPerDay(), new Rule_BadTime()};

}

Optimizer::~Optimizer() {

    // Release memory maintaining each rule object
    // for(int r = 0; r < ruleCount; ++r) {
    //     delete rules[r];
    // }

    // Release memory maintaining each pointer to Rule object that make up our collection of rules.
    delete [] rules;

}


int Optimizer::getScheduleFitness(Schedule* schedule) {

    // Reset fitnes value
    int fitness = 0;

    // Then, calculate fitness value using each rule
    for(int r = 0; r < ruleCount; ++r) {

        // Optimization; once schedule's fitness exceeds the weight provided by a TIME CONFLICT, don't waste any more time running through other fitness calculations.
        // NOTE: MUST EXCLUDE THIS FOR DEBUGGING OTHER RULES;
        if(fitness >= WEIGHT_TIMECONFLICT) {
            break;
        }

        rules[r]->getFitness(schedule);
        fitness += rules[r]->fitnessValue();


        // // Set Schedule's fitness. (UPDATE: Just going to use return value for now)
        // schedule->setFitness(fitness);


#ifdef DEBUG_OPTIMIZER
        // print out fitness contributed by each Rule
        ruleFitnesses[r] = rules[r]->fitnessValue();
        std::cout << "Fitness contributed by " << ruleNames[r] << ": " << ruleFitnesses[r] << std::endl;
#endif

    }

    return fitness;

}