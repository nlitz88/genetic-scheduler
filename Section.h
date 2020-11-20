#ifndef SECTION_H
#define SECTION_H

#include <string>

#include "Meeting.h"

class Section {

private:

    std::string sectionId;
    std::string instructorLName;

    // Collection of Meetings associated with this section
    Meeting** meetings;
    int meetingCount;

public:

    // Default Section Constructor
    //
    Section(std::string initId, std::string initLName);

    // Copy Constructor
    //
	Section(const Section& otherSection);

    // Section Destructor
    //
    virtual ~Section();

    // Operation that adds meeting to the section's collection of meetings
    //
    virtual void addMeeting(Meeting* newMeeting);

    // Operation that removes meeting from section's collection of meetings. Removed by Day?
    //
    virtual void removeMeeting(Day day);

    // Function that will remove all meetings from a section
    // 
    virtual void removeAllMeetings();



    // Get Meetings? (returns pointer to the collection of meetings) (Maybe this could be used to modify particular meetings)
    // 
    virtual Meeting** getMeetings() const;


    // Operation that returns meetingCount
    //
    virtual int getMeetingCount() const;


    // Also, get Num meetings?




    
    // DEVELOPMENTAL: This operation will, according to certain criteria, randomly generate meetings for this section
    //
    virtual void generateMeetings();





    virtual std::string getSectionId() const;
    virtual void setSectionId(std::string newId);

    virtual std::string getInstructorLName() const;
    virtual void setInstructorLName(std::string initLName);

    virtual std::string toString() const;


};

#endif