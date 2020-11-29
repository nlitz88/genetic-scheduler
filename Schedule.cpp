#include "Schedule.h"

#include <iostream>
#include <vector>
#include <algorithm>


const int SECTION_STEP = 6;


// Default Schedule constructor
//
Schedule::Schedule() {

    // Establish new collection of pointers to Section objects to be defined later.
    sections = new Section* [SECTION_STEP];
    sectionCount = 0;

    fitness = 0;

}


// Constructor that accepts pointer to collection of pointers to sections that will be used to import those "shell sections"
//
Schedule::Schedule(Section** importSectionList, int importCount) {

    // Establish new collection of pointers to Section objects to be defined later.
    sections = new Section* [SECTION_STEP];
    sectionCount = 0;

    fitness = 0;

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

    --sectionCount;
    while(sectionCount > 0) {

        // This should call Section destructor
        delete sections[sectionCount--];

    }

    // for(int s = 0; s < sectionCount; ++s) {
    //     delete sections[s];
    // }

}



// Operation that will set the schedule's fitness value.
//
void Schedule::setFitness(int newFitness) {
    
    fitness = newFitness;

}


// Operation that will return schedule's fitness value.
//
int Schedule::getFitness() const {

    return fitness;

}



// Operation that will set vector of instructors provided vector. This may be changed mechanically slightly in future.
//
void Schedule::setInstructors(std::vector<std::string> newInstructors) {

    instructors = newInstructors;

}


// Operation that will return vector of instructors.
//
std::vector<std::string> Schedule::getInstructors() {

    return instructors;

}



std::string Schedule::toString() const {

    std::string result;

    for(int s = 0; s < sectionCount; ++s) {

        result += sections[s]->toString() + "\n\n";

    }

    return result;

}