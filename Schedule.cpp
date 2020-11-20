#include "Schedule.h"


const int SECTION_STEP = 6;


// Default Schedule constructor
//
Schedule::Schedule() {

    // Establish new collection of pointers to Section objects to be defined later.
    sections = new Section* [SECTION_STEP];
    sectionCount = 0;

}


// Schedule destructor. Will deallocate all memory maintaining collection of sections.
// Will also destroy the sections and meetings within those sections for now.
// Could reuse sections to conserve memory, but that might be too much complexity for at the moment.
//
Schedule::~Schedule() {



}



// Operation that will add section to collection of sections.
//
void Schedule::addSection(Section* newSection) {

    // First, check to see if meeting collection must be expanded
    if(sectionCount % SECTION_STEP == 0) {

        Section** tempSections = new Section* [sectionCount + SECTION_STEP];

        for(int s = 0; s < sectionCount; ++s) {

            tempSections[s] = sections[s];

        }

        delete [] sections;
        sections = tempSections;

    }

    // As long as section collection large enough, add new section to collection
    sections[sectionCount++] = newSection;


}

// Operation that will remove section from collection of sections based on sectionId
//
void Schedule::removeSection(std::string idToRemove) {}

// Operation that will remove all sections from schedule
//
void Schedule::removeAllSections() {}




// Operation that will generate non-overlapping, limited number of sections that will comprise the schedule (STUDENT SCHEDULE)
//
void Schedule::generateSchedule() {}


std::string Schedule::toString() const {

    std::string result;

    for(int s = 0; s < sectionCount; ++s) {

        result += sections[s]->toString() + "\n\n";

    }

    return result;

}