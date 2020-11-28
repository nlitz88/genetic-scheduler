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


// Copy Constructor
//
Section::Section(const Section& otherSection) {

    sectionId = otherSection.sectionId;
    instructorLName = otherSection.instructorLName;

    meetings = new Meeting* [MEETING_STEP];
    meetingCount = 0;

}


// Section Destructor
//
Section::~Section() {

    // std::cout << sectionId << " being deleted. # of meetings: " << meetingCount << std::endl;

    // Release memory maintaining dynamically allocated Meeting objects
    removeAllMeetings();

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
        // std::cout << "Meeting " << meetingCount << " of " << sectionId << " destroyed" << std::endl;
        delete meetings[meetingCount--];
    }

}


// Get Meetings? (returns pointer to the collection of meetings) (Maybe this could be used to modify particular meetings)
// 
Meeting** Section::getMeetings() const {
    return meetings;
}


// Operation that returns meetingCount
//
int Section::getMeetingCount() const {
    return meetingCount;
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

    // for(int m = 0; m < meetingCount; ++m) {
    //     result += sectionId + "\n" + instructorLName + "\n" + meetings[m]->toString() + "\n\n";
    // }

    result += sectionId + "\n" + instructorLName + "\n";

    for(int m = 0; m < meetingCount; ++m) {
        result += meetings[m]->toString();
    }

    result += "\n" +meetings[0]->getStartTime().get24HourTime() + "-" + meetings[0]->getEndTime().get24HourTime() + "\n";

    return result;

}