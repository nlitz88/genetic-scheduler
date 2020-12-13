#ifndef RULE_H
#define RULE_H


#include "Schedule.h"


class Rule {

protected:

    int fitness;

public:

    // Operation that determines the fitness of a particular schedule per this rule.
    virtual void getFitness(Schedule* schedule) = 0;


    // Operation that returns fitness value of a particular rule.
    virtual int fitnessValue() const {
        return fitness;
    }

};




const int WEIGHT_TIMECONFLICT = 1000000;

// Rule that determines fitness according to whether or not the meetings of sections of the same professor overlap (the times at which they occur)
// NOTE: currently, this rule is only configured to add WEIGHT_TIMECONFLICT to the calculated fitness ONCE (as soon as it finds an instance of this in a schedule)
//
class Rule_TimeConflict : public Rule {


public:

    Rule_TimeConflict() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_CAMPUSTIME = 100;

// Rule that determines fitness according to whether or not the instructor must be on the campus for more than 9 hours
// Should add 100 for EVERY HOUR AFTER 9 hours that they're on campus
//
class Rule_CampusTime : public Rule {

public:

    Rule_CampusTime() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_NEXTDAY = 100;

// Rule that determines fitness based on if instructor is on campus after 6 pm and there the next morning before 11 am
// Adds WEIGHT_NEXTDAY for EVERY HOUR before 11 AM that an instructor must arrive if they teach at 6pm the day before.
//
class Rule_NextDay : public Rule {

public:

    Rule_NextDay() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_TWOEVENINGS = 50;
const int EVENINGTIME = 1080;
const int EVENINGTHRESHOLD = 2;

// Rule that determines fitness according to how many evenings an instructor is scheduled.
// Adds WEIGHT_TWOEVENINGS for every evening beyond two that an instructor is schedule.
//
class Rule_TwoEvenings : public Rule {


public:
    
    Rule_TwoEvenings() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_BACKTOBACK = 50;

// Rule that determines fitness according to whether or not meetings of sections of the same professor occur back-to-back.
// NOTE: Currently configured to add WEIGHT_BACKTOBACK for every occurrence of this (every two  meetings on every day that this might occur)
//
class Rule_BackToBack : public Rule {

public:

    Rule_BackToBack() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_AROUNDCOMMON = 50;
const int COMMONHOURSTART = 720;
const int COMMONHOUREND = 780;

// Rule that determines fitness according to if they teach (have meetings from two different sections) before AND after common hour.
//
class Rule_AroundCommon : public Rule {

public:

    Rule_AroundCommon() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_CLASSESPERDAY = 50;
const int CLASSESPERDAY = 3;

// Rule that determines fitness according to whether or not there are more than CLASSESPERDAY classes on a given day for a particular instructor.
//
class Rule_ClassesPerDay : public Rule {

public:

    Rule_ClassesPerDay() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_LONGCLASSESPERDAY = 1000;
const int LONGCLASSLENGTH = 180;
const int LONGCLASSESPERDAY = 1;

// Rule that determines fitness according to whether or not there are more than CLASSESPERDAY LONG classes (have length LONGCLASSLENGTH or more) on a given day for a particular instructor.
//
class Rule_LongClassesPerDay : public Rule {

public:

    Rule_LongClassesPerDay() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



const int WEIGHT_BADTIME = 100;
const int EARLY_THRESHOLD = 420;
const int LATE_THRESHOLD = 1260;

// Rule that determines fitness according to how late before or after early and late thresholds respectively the start and end times of a meeting are.
// Will add WEIGHT_BADTIME for every hour before the EARLY_THRESHOLD that a section's meeting starts OR for every hour after LATE_THRESHOLD a section ends.

class Rule_BadTime : public Rule {

public:

    Rule_BadTime() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule);

};



#endif