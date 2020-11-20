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
void Schedule::generateSchedule(Section** sectionList, int numSectionsToAdd) {


    // ATTEMPT 1: COULD BE TOTALLY WRONG

    // Pull in collection of sections from file (or that will be done in main and this will just use a pointer to that collection)

    // This part will be done for POPULATION_SIZE
    //      Copy section from main section to here to generate unique meetings for this one in particular, as that section may be used again differently in another schedule
    //      Then generate meetings for that copy instance (all the copy needs is the Lastname and sectionID) (copy constructor??)
    //      Then, add that generated section to the sections collection


    // 1.) Create new section objects using sectionID and InstructorName from Section's from sectionList
    //          CONSIDER MAKING THIS IT'S OWN FUNCTION!!
    //
    for(int s = 0; s < numSectionsToAdd; ++s) {
        addSection(new Section(*(sectionList[s])));
        // addSection(new Section(sectionList[s]->getSectionId(), sectionList[s]->getInstructorLName()));
    }

    // 2.) Generate meetings for each of the sections pulled in
    //
    for(int s = 0; s < sectionCount; ++s) {
        std::cout << "Generate meetings for " << sections[s]->getSectionId() << std::endl;
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