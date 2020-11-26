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

    Section** baseSections;
    int sectionCount;


public:

    // Default Constructor.
    //
    Scheduler();


    // Constructor that accepts filename that will be used to import sections upon creation.
    //
    Scheduler(std::string sectionsFile);


    // Constructor that accepts pointer to collection of pre-existing sections.
    //
    Scheduler(Section** initSections);


    // Destructor (should this destroy collections of sections that belong to it? I think so).
    //
    ~Scheduler();





    // Scheduler will:
    //      - Retrive sections from file. Will maintain a BASE collection of sections that each schedule will use in its own way.
    //      - MAYBE: Contains genetic algorithm for improvement? OR is that for the Optimizer?
    //      - Or does the genetic algorithm live here, and only use the Optimizer's functions for ranking, and then mutating/crossover?
    // 

    // For each schedule that it needs to generate it will:
        // create a new Schedule Object, passing in sections
        // This function will subsequently generate meetings for each section.


    // Operation that will destroy all base section objects.
    //


    // Operation that will add new section object to collection of sections. These sections, however, will only serve as "base"/"shell" sections;
    // No meetings will be generated for them (that is only done for those copies of these that belong to a collection of sections within a schedule).
    //
    virtual void Scheduler::addSection(Section* newSection);


    // Static vector of instructors that will be populated with each new collection of sections.
    // May be used internally or externally. Externally used by a few Rule classes.
    static std::vector<std::string> instructors;


    // Operation that will import sections from file.
    //
    virtual void importSectionsFromFile(std::string sectionsFile);
    


    // Operation that will set sections to other collection provided by pointer
    //
    virtual void setNewSections(Section** newSections);


    // Operation that will generate Meetings for sections of a particular schedule.
    //
    virtual void generateSectionMeetings(Section* section);


    // Operation that will generate a schedule by generating Meetings for each new schedule object that it has.
    //
    virtual void generateScheduleSections(Schedule* schedule);


    
    // SOMEWHERE DOWN HERE, IMPLEMENT OPERATION THAT WILL ACTUALLY GENERATE A POPULATION AND WHAT NOT.
    // ALSO, not sure how I want to maintain the contants yet. Maybe make them private members, or static members?



    
    


};


#endif