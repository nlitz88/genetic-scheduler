#include "Section.h"

#include <string>

#include <iostream>


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