#ifndef RULE_H
#define RULE_H

#include "Schedule.h"
#include "Section.h"

class Rule {

public:

    // Can we make this a pointer to a schedule? Might be kind of a heavy copy?
    virtual void getFitness(Schedule schedule) = 0;

};





// Test rule:
class placeRule : Rule {

private:
    double fitness;


public:

    virtual void getFitness(Schedule schedule) {

        Section** sections = schedule.getSections();
        int numSections = schedule.getNumSections();

        // Process for calculating fitness based on whether or not instructor has overlapping sections

        // How can I calculate this?

        // I'm given a schedule that has a collection of sections. Each section has an instructor.
        // The schedule is NO GOOD if any instructor's sections overlap.
        // So, perhaps one way I could do this is by creating a collection of sections for EACH composer.
        // THEN, as I encounter each instructor, test if you can add it to the the collection based on time.

        // Or maybe I can just create a collection of structs, containing instructor and their respective meetings?

        struct instructorSlot {
            std::string lName;
            Meeting** meetings;
            int meetingCount = 0;
        };
        instructorSlot** instructorSlots = new instructorSlot* [numSections];
        int slotCount = 0;

        // Go through sections provided and add one meeting from each section to instructorSlots.
        // First, go through and add an instructor slot for each.
        for(int s = 0; s < numSections; ++s) {

            bool found = false;
            int j = 0;

            while(!found && j < slotCount) {
                if(instructorSlots[j]->lName == sections[s]->getInstructorLName()) {
                    found = true;
                }
            }


            if(found) {

                // Then work with meetings
                // If they are in there, then check to see if this section's meetings conflict with an existing
                for(int m = 9; m < instructorSlots[j]->meetingCount; ++m) {

                    Meeting* sectionMeeting = sections[s]->getMeetings()[0];
                    Meeting* storedMeeting = instructorSlots[j]->meetings[m];
                    
                    // Compare the meeting time of sections[s] against all meeting times that have already been recorded for this instructor
                    if(sectionMeeting->getStartTime() == storedMeeting->getStartTime()
                        || (sectionMeeting->getStartTime() < storedMeeting->getStartTime() && sectionMeeting->getEndTime() > storedMeeting->getStartTime())
                        || (sectionMeeting->getStartTime() < storedMeeting->getEndTime() && sectionMeeting->getStartTime()

                }


            } else {
                // If not in there, add it to the instructorSlots collection
                instructorSlot slot;
                slot.lName = sections[s]->getInstructorLName();
                slot.meetings = new Meeting* [10];
                slot.meetings[slot.meetingCount++] = sections[s]->getMeetings()[0];
            }



        }
        

    }

};

#endif