#include "Schedule.h"

#include <iostream>


const int SECTION_STEP = 6;


// Default Schedule constructor
//
Schedule::Schedule() {

    // Establish new collection of pointers to Section objects to be defined later.
    sections = new Section* [SECTION_STEP];
    sectionCount = 0;

}


// Constructor that accepts pointer to collection of pointers to sections that will be used to import those "shell sections"
//
Schedule::Schedule(Section** importSectionList, int importCount) {

    // Establish new collection of pointers to Section objects to be defined later.
    sections = new Section* [SECTION_STEP];
    sectionCount = 0;

   importSections(importSectionList, importCount);
    
}


// Schedule destructor. Will deallocate all memory maintaining collection of sections.
// Will also destroy the sections and meetings within those sections for now.
// Could reuse sections to conserve memory, but that might be too much complexity for at the moment.
//
Schedule::~Schedule() {

    removeAllSections();
    delete [] sections;

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


// Operation that will add multiple sections from a provided collection of Sections
//
void Schedule::importSections(Section** importSectionList, int importCount) {

    // sectionCount will increase as each additional section is added
    for(int s = 0; s < importCount; ++s) {
        // This essentially creates new Section Object based on an existing Section object. 
        // The only data copied from one Section to another, however, is the ID and LName.
        addSection(new Section(*(importSectionList[s])));
    }

}


// Operation that returns pointer to collection of Sections
//
Section** Schedule::getSections() const {
    return sections;
}


// Operation that returns number of sections in a Schedule's collection of sections
//
int Schedule::getNumSections() const {
    return sectionCount;
}


// Operation that will remove section from collection of sections based on sectionId
//
void Schedule::removeSection(std::string idToRemove) {


    bool found = false;
    int s = 0;

    while(!found) {
        if(sections[s]->getSectionId() == idToRemove) {
            delete sections[s];
            found = true;
        }
        else {++s;}
    }

}


// Operation that will remove all sections from schedule
//
void Schedule::removeAllSections() {

    while(sectionCount > 0) {

        // This should call Section destructor
        delete sections[sectionCount--];

    }

}




// Operation that will generate non-overlapping, limited number of sections that will comprise the schedule (STUDENT SCHEDULE)
// UPDATE: NOT EXACTLY SURE WHAT KIND OF SCHEDULE THIS IS SUPPOSED TO BE YET
//
void Schedule::generateSchedule() {


    // ATTEMPT 1: COULD BE TOTALLY WRONG

    // 1.) When the schedule is first created, a sectionList (from main, imported from file) can be passed in to import those "shell" sections to the schedule
    //     OR, these can be imported using an external call as well.

    // 2.) THEN, within here, we generate meetings for all of those schedules in our sectons collection.


    // 2.) Generate meetings for each of the sections pulled in
    //
    for(int s = 0; s < sectionCount; ++s) {
        // std::cout << "Generate meetings for " << sections[s]->getSectionId() << std::endl;
        // Generate meetings for each section
        sections[s]->generateMeetings();
    }


}




std::string Schedule::toString() const {

    std::string result;

    for(int s = 0; s < sectionCount; ++s) {

        result += sections[s]->toString() + "\n\n";

    }

    return result;

}