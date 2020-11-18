#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>

#include "Section.h"

class Schedule {

private:

    Section** sections;
    int sectionCount;

public:

    // Default Schedule constructor
    //
    Schedule();

    // Schedule destructor. Will deallocate all memory maintaining collection of sections.
    // Will also destroy the sections and meetings within those sections for now.
    // Could reuse sections to conserve memory, but that might be too much complexity for at the moment.
    //
    virtual ~Schedule();

    // Operation that will add section to collection of sections.
    //
    virtual void addSection(Section* newSection);

    // Operation that will remove section from collection of sections based on sectionId
    //
    virtual void removeSection(std::string idToRemove);

    // Operation that will remove all sections from schedule
    //
    virtual void removeAllSections();

    //
    

};


#endif