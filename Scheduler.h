#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <time.h>

#include "Schedule.h"
#include "Section.h"
#include "Meeting.h"
// #include "Optimizer.h"


class Scheduler {

private:

    // Collection of base "shell" sections that each schedule will stem from.
    Section** baseSections;
    int sectionCount;

    // Population of schedules. (This may change)
    Schedule** schedules;
    int scheduleCount;

    // Vector of instructor names. This vector will be passed along to each schedule in order that Optimizer's rules can use it later.
    std::vector<std::string> instructors;


public:

    // Default Constructor.
    //
    Scheduler();


    // Constructor that accepts filename that will be used to import sections upon creation.
    //
    Scheduler(std::string sectionsFile);


    // Constructor that accepts pointer to collection of pre-existing sections.
    //
    Scheduler(Section** initSections, int numSections);


    // Destructor (should this destroy collections of sections that belong to it? I think so).
    //
    ~Scheduler();



    // Operation that will destroy all base section objects. Will also clear instructor vector along with it.
    //
    virtual void destroyAllSections();


    // Operation that will add new section object to collection of sections. These sections, however, will only serve as "base"/"shell" sections;
    // No meetings will be generated for them (that is only done for those copies of these that belong to a collection of sections within a schedule).
    //
    virtual void addSection(Section* newSection);


    // Operation that will import sections from file.
    //
    virtual void importSectionsFromFile(std::string sectionsFile);
    

    // Operation that will set sections to other collection provided by pointer
    //
    virtual void setNewSections(Section** newSections, int numSections);



    // Operation that will generate Meetings for sections of a particular schedule.
    //
    virtual void generateSectionMeetings(Section* section);


    // Operation that will generate a schedule by generating Meetings for each new schedule object that it has.
    // This is the "Generate Schedule" operation.
    //
    virtual void generateScheduleSections(Schedule* schedule);


    
    // SOMEWHERE DOWN HERE, IMPLEMENT OPERATION THAT WILL ACTUALLY GENERATE A POPULATION AND WHAT NOT.
    // ALSO, not sure how I want to maintain the contants yet. Maybe make them private members, or static members?


    // ALSO, GENETIC ALGORITHMS WILL BE DOWN HERE AS WELL IN SOME FORM.
    // Would need 
    //  A.) Population Vector
    //  B.) Elite Vector
    //  C.) Would need a sorting algorithm.
    //  D.) Would need an optimizer object to rank all of the schedules of the population vector/collection.
    
    


};


#endif