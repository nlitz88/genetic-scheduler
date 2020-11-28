#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>

#include "Section.h"

class Schedule {

private:

    Section** sections;
    int sectionCount;

    int fitness;

    // List of instructors from sections that a schedule will be generated from. This will later be used by Optimizer's rules.
    // For now, I think it would be copied from Scheduler (where it originates) to each schedule object.
    std::vector<std::string> instructors;

public:

    // Default Schedule constructor
    //
    Schedule();

    // Constructor that accepts pointer to collection of pointers to sections that will be used to import those "shell sections"
    //
    Schedule(Section** importSectionList, int importCount);


    // Schedule destructor. Will deallocate all memory maintaining collection of sections.
    // Will also destroy the sections and meetings within those sections for now.
    // Could reuse sections to conserve memory, but that might be too much complexity for at the moment.
    //
    virtual ~Schedule();



    // Operation that will add section to collection of sections.
    //
    virtual void addSection(Section* newSection);


    // Operation that will add multiple sections from a provided collection of Sections
    //
    virtual void importSections(Section** importSectionList, int importCount);


    // Operation that returns pointer to collection of Sections
    //
    virtual Section** getSections() const;


    // Operation that returns number of sections in a Schedule's collection of sections
    //
    virtual int getNumSections() const;


    // Operation that will remove section from collection of sections based on sectionId
    //
    virtual void removeSection(std::string idToRemove);


    // Operation that will remove all sections from schedule
    //
    virtual void removeAllSections();


    
    // Operation that will set the schedule's fitness value.
    //
    virtual void setFitness(int newFitness);


    // Operation that will return schedule's fitness value.
    //
    virtual int getFitness() const;



    // Operation that will set vector of instructors provided vector. This may be changed mechanically slightly in future.
    //
    virtual void setInstructors(std::vector<std::string> newInstructors);


    // Operation that will return vector of instructors.
    //
    virtual std::vector<std::string> getInstructors();


    virtual std::string toString() const;
    

};


#endif