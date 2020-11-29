#include "Scheduler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <random>
#include <vector>
#include <algorithm>

#include "Schedule.h"
#include "Section.h"
#include "Meeting.h"
#include "Optimizer.h"



const int SECTION_STEP = 50;


// Default Constructor.
//
Scheduler::Scheduler() {

    baseConstructor();

}


// Constructor that accepts filename that will be used to import sections upon creation.
//
Scheduler::Scheduler(std::string sectionsFile) {

    baseConstructor();

    importSectionsFromFile(sectionsFile);

}


// Constructor that accepts pointer to collection of pre-existing sections.
//
Scheduler::Scheduler(Section** initSections, int numSections) {

    baseConstructor();
    setNewSections(initSections, numSections);

}



// Operation that provides base functionality for all other constructors.
//
void Scheduler::baseConstructor() {


    baseSections = new Section* [SECTION_STEP];
    sectionCount = 0;


}


// Destructor (should this destroy collections of sections that belong to it? I think so).
//
Scheduler::~Scheduler() {

    destroyAllSections();
    delete [] baseSections;

}



// Operation that will release all memory maintaining sections maintained in baseSections collection.
//
void Scheduler::destroyAllSections() {

    --sectionCount;
    while(sectionCount > 0) {

        // This should call Section destructor
        delete baseSections[sectionCount--];

    }


    // Clear instructors vector.
    instructors.clear();


}



// Operation that will sort sections alphabetically based on sectionId.
//
void Scheduler::sortSections(Section** sections, int numSections) {


    Section* temp;
    int leastIndex;

    for(int start = 0; start < numSections - 1; ++start) {

        leastIndex = start;

        for(int e = start; e < numSections; ++e) {

            if(sections[e]->getSectionId() < sections[leastIndex]->getSectionId()) {
                leastIndex = e;
            }

        }

        if(leastIndex != start) {

            temp = sections[start];
            sections[start] = sections[leastIndex];
            sections[leastIndex] = temp;

        }

    }


    // Test: print out sorted sections.
    // for(int s = 0; s < numSections; ++s) {
    //     std::cout << sections[s]->getSectionId() << std::endl;
    // }


}



// Operation that will add section to collection of sections.
//
void Scheduler::addSection(Section* newSection) {


    // First, check to see if meeting collection must be expanded
    if(sectionCount % SECTION_STEP == 0) {

        Section** tempSections = new Section* [sectionCount + SECTION_STEP];

        for(int s = 0; s < sectionCount; ++s) {

            tempSections[s] = baseSections[s];

        }

        delete [] baseSections;
        baseSections = tempSections;

    }

    // As long as section collection large enough, add new section to collection
    baseSections[sectionCount++] = newSection;


    // Add instructor name to vector of names if it doesn't already exist.
    if(std::find(instructors.begin(), instructors.end(), newSection->getInstructorLName()) == instructors.end()) {

        instructors.push_back(newSection->getInstructorLName());

    }
     

}


// Operation that will import sections from file.
//
void Scheduler::importSectionsFromFile(std::string sectionsFile) {


    std::ifstream fin;
    fin.open(sectionsFile);

    std::string id, lname;

    while(!fin.eof()) {
        
        // Read in id and lname of each new section.
        fin >> id >> lname;

        // Add new section to collection of baseSections using addSection operation.
        addSection(new Section(id, lname));

    }

    // Then, sort sections alphabetically.
    sortSections(baseSections, sectionCount);


}


// Operation that will set sections to other collection provided by pointer
//
void Scheduler::setNewSections(Section** newSections, int numSections) {


    // Release memory maintaining old sections first.
    destroyAllSections();
    
    // Then, assign baseSections to new collection and set new count.
    baseSections = newSections;
    sectionCount = numSections;

    // Then, sort sections alphabetically.
    sortSections(baseSections, sectionCount);


}



// Operation that will generate Meetings for sections of a particular schedule.
//
void Scheduler::generateSectionMeetings(Section* section) {


    /*
        
        - Sections can only be scheduled as MWF, TR, MW or one day a week (any day)
        - MWF sections meets for 1 hr each day and can start on any hour BUT 12pm
        - TR and MW sections meet for 2 hours each day and can only start at 8am, 10am, 1pm, 3pm, 5pm, and 7pm
        - A one-day-a-week section meets for 3 hrs and can have any start time
        - No course may be scheduled such that it overlaps common hour which occurs 12-1 each day
    
    */


    // 1.) Randomly choose MWF, TR, MW, or A (any day) scheme. Set meetingCount accordingly
    
    enum DaySchemes {MWF, TR, MW, A};
    int dayScheme = rand() % 4;


    // 2.) Based on the randomly selected scheme, generate meeting times.

    // Variables for calculating meeting parameters
    Time startTime;
    Time endTime;
    
    switch(dayScheme) {
        

        case MWF:

            // Each meeting will start at the same time. So calculate random start time within the restraints
            do {
                
                // Get random start time in minutes of some hour in the day
                startTime = (rand() % 24) * 60;
                // MWF: meet for 1 hour a day (StartTime + 60 minutes)
                endTime = startTime + 60;
                
                // Don't have to check if it overlaps with common hour, as the only way that could happen is at 12pm, which we don't allow
            }while(startTime == 720);


            // std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;


            // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection

            section->addMeeting(new Meeting(M, startTime, endTime));
            section->addMeeting(new Meeting(W, startTime, endTime));
            section->addMeeting(new Meeting(F, startTime, endTime));

            // NOTE: meetingCount will be updated as these meetings are added

            break;
        

        case TR: case MW:

        
            // Each meeting will start at the same time. So calculate random start time within the restraints
            do{

                // Get random start time in minutes of some hour in the day
                startTime = (rand() % 24) * 60;
                // TR and MW sections meet for 2 hours each day
                endTime = startTime + 120;
                
                // Can only start at 8am, 10am, 1pm, 3pm, 5pm, and 7pm. Again, no need to check for overflow into common hour,
                // as startTime will control this.
            }while(startTime != 480 && startTime != 600 && startTime != 780 && startTime != 900 && startTime != 1020 && startTime != 1140);
            

            // std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;

            // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection
            
            if(dayScheme == TR) {
                section->addMeeting(new Meeting(T, startTime, endTime));
                section->addMeeting(new Meeting(R, startTime, endTime));
            }
            else {
                section->addMeeting(new Meeting(M, startTime, endTime));
                section->addMeeting(new Meeting(W, startTime, endTime));
            }

            break;
        

        case A:

            // Generate random start time within the restraints for once a week section.
            do{

                // Get random start time in minutes of some hour in the day
                startTime = (rand() % 24) * 60;
                // ANY day sections meet for 3 hours one day a week.
                endTime = startTime + 180;
            
            // Once a week courses (that occur ANY day) can start at any hour, but can't overlap with common hour.
            // Therefore, they can't start anytime after 9AM until 1PM
            }while(startTime > 540 && startTime < 780);
            
            // std::cout << "Any" << std::endl; 

            // 3.) Generate the random day on which the section will occur (limited to M-F)
            Day sectionDay = static_cast<Day>(rand() % 5);

            // 4.) Then, instantiate and add the single Meeting object with parameters to section's "meetings" collection
            section->addMeeting(new Meeting(sectionDay, startTime, endTime));

            break;
    }


    // std::string daySchemes[] {"MWF", "TR", "MW", "A"};
    // std::cout << "Day Scheme: " << daySchemes[dayScheme] << ". Will meet " << meetingCount << " time(s) per week." << std::endl;


}


// Operation that will generate a schedule by generating Meetings for each new schedule object that it has.
//
void Scheduler::generateScheduleSections(Schedule* schedule) {


    // Essentially, just call generateSectionMeetings for each section to be in the provided schedule.
    for(int s = 0; s < schedule->getNumSections(); ++s) {

        // Generate meetings for each section within schedule.
        generateSectionMeetings(schedule->getSections()[s]);

    }


}



// Operation that will create new schedule objects AND generate sections for that schedule. This is a comprehensive "Generate Schedule" operation.
//
Schedule* Scheduler::generateSchedule() {


    // Instantiate new Schedule Object with collection of base Sections.
    // Upon creation using this Schedule constructor, a collection of of COPIES of these provided sections will be provided.
    // These will be the Schedule's sections, which we can then generate meetings for.
    Schedule* newSchedule = new Schedule(baseSections, sectionCount);

    // Generate the meetings for the sections of schedule.
    generateScheduleSections(newSchedule);

    // Then, return pointer to new Schedule object.
    return newSchedule;


}


// Operation that generates and returns multiple schedules.
//
Schedule** Scheduler::generateSchedules(int numSchedules) {


    // Pointer to maintain collection of new Schedule objects.
    Schedule** newSchedules = new Schedule* [numSchedules];

    // Pointer to maintain address of new Schedule objects.
    Schedule* newSchedule;

    for(int s = 0; s < numSchedules; ++s) {

        // Generate new schedule.
        newSchedule = generateSchedule();
        // Add it to collection of new Schedules.
        newSchedules[s] = newSchedule;

    }

    return newSchedules;


}