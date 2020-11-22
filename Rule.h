#ifndef RULE_H
#define RULE_H

#include <iostream>

#include "Schedule.h"
#include "Section.h"

class Rule {

protected:

    long fitness;

public:

    // Can we make this a pointer to a schedule? Might be kind of a heavy copy?
    virtual void getFitness(Schedule schedule) = 0;


    // Operation that returns fitness value of a particular rule
    virtual long fitnessValue() const {
        return fitness;
    }

};




const int WEIGHT_SAMETIME = 1000000;

// Rule that determines fitness according to whether or not the meetings of sections of the same professor overlap (the times at which they occur)
// NOTE: currently, this rule is only configured to add WEIGHT_SAMETIME to the calculated fitness ONCE (as soon as it finds an instance of this in a schedule)
//
class Rule_SameTime : public Rule {


public:

    Rule_SameTime() {
        fitness = 0;
    }

    virtual void getFitness(Schedule schedule) {

        Section** sections = schedule.getSections();
        int numSections = schedule.getNumSections();

        int currSectMC = 0;             // Current section meeting count.
        int othSectMC = 0;              // Other section meeting count.

        Meeting* currSectMeeting;       // Pointer to point to one of the current section's meeting object.
        Meeting* othSectMeeting;        // Pointer to point to one of the other sections' meeting object.

        bool tc = false;                // time conflict.


        // Process for calculating fitness based on whether or not instructor has overlapping sections

        // Loop through all sections
        for(int cs = 0; cs < numSections && !tc; ++cs) {

            // std::cout << "Section #" << cs << std::endl;

            // For each section, compare against all other sections that are taught by same instructor (same lName)
            for(int os = cs + 1; os < numSections && !tc; ++os) {

                // If section is from the same instructor, then compare their meetings.
                if(sections[cs]->getInstructorLName() == sections[os]->getInstructorLName()) {


                    // Will have to compare meetings on each day of the week for between all of the different meetings on different days.
                    
                    currSectMC = sections[cs]->getMeetingCount();
                    othSectMC = sections[os] ->getMeetingCount();


                    // Compare each meeting of the current section to EACH meeting of the other section.
                    // If the days match between two meetings, THEN and only then will we compare their times.
                    // bool matchingDays = false;

                    // For each meeting in the "Current" section
                    for(int csm = 0; csm < currSectMC && !tc; ++csm) {

                        // For each meeting in the "Other" section
                        for(int osm = 0; osm < othSectMC && !tc; ++osm) {
                            
                            // Store current section meeting and other section meeting in pointers for further referencing
                            currSectMeeting = sections[cs]->getMeetings()[csm];
                            othSectMeeting = sections[os]->getMeetings()[osm];

                            // Compare all meeting's days of current section to all meeting's days of other section
                            if(currSectMeeting->getDay() == othSectMeeting->getDay()) {
                                
                                
                                // std::cout << "Two meetings of different sections occur on same day! Will compare the times of the meetings now!" << std::endl;
 

                                // std::cout << sections[cs]->getInstructorLName() << " teaches " << sections[cs]->getSectionId() << " on day "
                                //           << currSectMeeting->toString() << " at "
                                //           << currSectMeeting->getStartTime().get24HourTime() << "-" << currSectMeeting->getEndTime().get24HourTime() << std::endl;

                                // std::cout << sections[os]->getInstructorLName() << " teaches " << sections[os]->getSectionId() << " on day "
                                //           << othSectMeeting->toString() << " at "
                                //           << othSectMeeting->getStartTime().get24HourTime() << "-" << othSectMeeting->getEndTime().get24HourTime() << std::endl;



                                // NOW, compare the times of the two meetings to see if they overlap

                                // If the two meetings start at the same time --> fitness = 1000000
                                // OR
                                // If the current section's meeting starts BEFORE the other meeting and ENDS after the other section's startTime
                                // OR
                                // If the current section's meeting starts AFTER other meeting startTime AND starts before the other one ends
                                if(currSectMeeting->getStartTime() == othSectMeeting->getStartTime() ||
                                   (currSectMeeting->getStartTime() < othSectMeeting->getStartTime() && currSectMeeting->getEndTime() > othSectMeeting->getStartTime()) ||
                                   (currSectMeeting->getStartTime() > othSectMeeting->getStartTime() && currSectMeeting->getStartTime() < othSectMeeting->getEndTime())) {

                                    fitness = WEIGHT_SAMETIME;

                                    std::cout << "TIME CONFLICT: BAD SCHEDULE!\n";
                                    std::cout << sections[cs]->getInstructorLName() << " teaches " << sections[cs]->getSectionId() << " on day "
                                          << currSectMeeting->toString() << " at "
                                          << currSectMeeting->getStartTime().get24HourTime() << "-" << currSectMeeting->getEndTime().get24HourTime() << std::endl;

                                    std::cout << sections[os]->getInstructorLName() << " teaches " << sections[os]->getSectionId() << " on day "
                                          << othSectMeeting->toString() << " at "
                                          << othSectMeeting->getStartTime().get24HourTime() << "-" << othSectMeeting->getEndTime().get24HourTime() << std::endl;

                                    tc = true;  // time conflict = true --> will break all outer loops. No more fitness evaluation needed


                                } else {
                                    
                                    fitness = 0;

                                }
                                


                            }


                        }


                    }


                }


            }


        }
        

    }

};



const int BACKTOBACK_WEIGHT = 50;

// Rule that determines fitness according to whether or not meetings of sections of the same professor occur back-to-back
// NOTE: Currently configured to add BACKTOBACK_WEIGHT for every occurrence of this (every two  meetings on every day that this might occur)
//
class Rule_BackToBack : public Rule {

public:

    Rule_BackToBack() {
        fitness = 0;
    }

    virtual void getFitness(Schedule schedule) {

        // Get collections of sections from provided schedule
        Section** sections = schedule.getSections();
        int numSections = schedule.getNumSections();

        //


    }


};





#endif