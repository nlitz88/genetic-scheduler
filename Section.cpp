#include "Section.h"

#include <string>
#include <random>
#include <time.h>
#include <iostream>

#include "Time.h"


const int MEETING_STEP = 3;


// Default Section Constructor
//
Section::Section(std::string initId, std::string initLName) {

    sectionId = initId;
    instructorLName = initLName;

    meetings = new Meeting* [MEETING_STEP];
    meetingCount = 0;

}


// Section Destructor
//
Section::~Section() {

    // Release memory maintaining dynamically allocated Meeting objects
    for(int m = 0; m < meetingCount; ++m) {

        std::cout << "Meeting " << m << " of " << sectionId <<" destroyed" << std::endl;
        delete meetings[m];

    }

    // Finally, release memory maintaining collection of Meetings
    delete [] meetings;

    meetingCount = 0;

}



// Operation that adds meeting to the section's collection of meetings
//
void Section::addMeeting(Meeting* newMeeting) {

    // Could add additional checking up here and status reporting. Not sure how necessarry that'll be

    // First, check to see if meeting collection must be expanded
    if(meetingCount % MEETING_STEP == 0) {

        Meeting** tempMeetings = new Meeting* [MEETING_STEP + meetingCount];

        for(int m = 0; m < meetingCount; ++m) {

            tempMeetings[m] = meetings[m];

        }

        delete [] meetings;
        meetings = tempMeetings;

    }

    // As long as array large enough, add event
    meetings[meetingCount++] = newMeeting;

}


// Operation that removes meeting from section's collection of meetings. Removed by Day?
//
void Section::removeMeeting(Day day) {

    bool found = false;
    int m = 0;
    
    while(!found) {
        if(meetings[m]->getDay() == day) {
            delete meetings[m];
            found = true;
        }
        else {++m;}
    }

}


// Function that will remove all meetings from a section
// 
void Section::removeAllMeetings() {

    while(meetingCount > 0) {
        delete meetings[meetingCount--];
    }

}



// DEVELOPMENTAL: This operation will, according to certain criteria, randomly generate meetings for this section
//
void Section::generateMeetings() {

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


            std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;


            // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection

            this->addMeeting(new Meeting(M, startTime, endTime));
            this->addMeeting(new Meeting(W, startTime, endTime));
            this->addMeeting(new Meeting(F, startTime, endTime));

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
            

            std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;

            // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection
            
            if(dayScheme == TR) {
                this->addMeeting(new Meeting(T, startTime, endTime));
                this->addMeeting(new Meeting(R, startTime, endTime));
            }
            else {
                this->addMeeting(new Meeting(M, startTime, endTime));
                this->addMeeting(new Meeting(W, startTime, endTime));
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
            
            std::cout << "Any" << std::endl; 

            // 3.) Generate the random day on which the section will occur (limited to M-F)
            Day sectionDay = static_cast<Day>(rand() % 5);

            // 4.) Then, instantiate and add the single Meeting object with parameters to section's "meetings" collection
            this->addMeeting(new Meeting(sectionDay, startTime, endTime));

            break;
    }


    // Just for debugging
    std::string daySchemes[] {"MWF", "TR", "MW", "A"};
    std::cout << "Day Scheme: " << daySchemes[dayScheme] << ". Will meet " << meetingCount << " time(s) per week." << std::endl;

}



std::string Section::getSectionId() const {
    return sectionId;
}


void Section::setSectionId(std::string newId) {
    sectionId = newId;
}


std::string Section::getInstructorLName() const {
    return instructorLName;
}


void Section::setInstructorLName(std::string newLName) {
    instructorLName = newLName;
}


std::string Section::toString() const {

    std::string result;

    for(int m = 0; m < meetingCount; ++m) {
        result += sectionId + "\n" + instructorLName + "\n" + meetings[m]->toString() + "\n\n";
    }
     

    return result;

}