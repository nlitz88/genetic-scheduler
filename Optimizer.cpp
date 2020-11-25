#include "Optimizer.h"


Optimizer::Optimizer() {

    // Predetermined number of rules. Must use pointers, however, in order to take advantage of polymorphic nature of rule.
    ruleCount = 7;
    rules = new Rule* [ruleCount] {new Rule_TimeConflict(), new Rule_CampusTime(), new Rule_NextDay(), new Rule_TwoEvenings(), new Rule_BackToBack(), new Rule_AroundCommon(), new Rule_ClassesPerDay()};

}

Optimizer::~Optimizer() {

    // Release memory maintaining each rule object
    // for(int r = 0; r < ruleCount; ++r) {
    //     delete rules[r];
    // }

    // Release memory maintaining each pointer to Rule object that make up our collection of rules.
    delete [] rules;

}


long Optimizer::getScheduleFitness(Schedule* schedule) {

    // Reset fitnes value
    long fitness = 0;

    // Then, calculate fitness value using each rule
    for(int r = 0; r < ruleCount; ++r) {

        // Optimization; once schedule's fitness exceeds the weight provided by a TIME CONFLICT, don't waste any more time running through other fitness calculations.
        // NOTE: MUST EXCLUDE THIS FOR DEBUGGING OTHER RULES;
        // if(fitness >= WEIGHT_TIMECONFLICT) {
        //     break;
        // }

        rules[r]->getFitness(schedule);
        fitness += rules[r]->fitnessValue();

#ifdef DEBUG
        // print out fitness contributed by each Rule
        ruleFitnesses[r] = rules[r]->fitnessValue();
        std::cout << "Fitness contributed by " << ruleNames[r] << ": " << ruleFitnesses[r] << std::endl << std::endl;
#endif

    }

    return fitness;

}