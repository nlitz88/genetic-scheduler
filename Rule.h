#ifndef RULE_H
#define RULE_H

#include "Schedule.h"
#include "Section.h"

class Rule {

public:

    // Can we make this a pointer to a schedule? Might be kind of a heavy copy?
    virtual void getFitness(Schedule schedule) = 0;

};





// Test rule:
class placeRule : Rule {

private:
    double fitness;


public:

    virtual void getFitness(Schedule schedule) {

        Section** sections = schedule.getSections();
        int numS

        // Process for calculating fitness based on whether or not instructor has overlapping sections

        // How can I calculate this?

        

    }

};

#endif