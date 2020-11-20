#ifndef RULE_H
#define RULE_H

#include <iostream>

#include "Schedule.h"
#include "Section.h"

class Rule {

public:

    // Can we make this a pointer to a schedule? Might be kind of a heavy copy?
    virtual void getFitness(Schedule schedule) = 0;

};





// Test rule:
class R_place : Rule {

private:
    double fitness;


public:

    virtual void getFitness(Schedule schedule) {

        Section** sections = schedule.getSections();
        int numSections = schedule.getNumSections();

        // Process for calculating fitness based on whether or not instructor has overlapping sections

        // Loop through all sections
        for(int cs = 0; cs < numSections; ++cs) {

            // For each section, compare against all other sections that are taught by same instructor (same lName)
            for(int os = cs + 1; os < numSections; ++os) {

                // If section is from the same instructor, then compare their meetings.
                if(sections[cs]->getInstructorLName() == sections[os]->getInstructorLName()) {


                    // Will have to compare meetings on each day of the week for between all of the different meetings on different days.
                    
                    int currSectMC = sections[cs]->getMeetingCount();
                    int othSectMC = sections[os] ->getMeetingCount();

                    // Compare each meeting of the current section to EACH meeting of the other section.
                    // If the days match between two meetings, THEN and only then will we compare their times.
                    bool matchingDays = false;

                    // For each meeting in the "Current" section
                    for(int csm = 0; csm < currSectMC; ++csm) {

                        // For each meeting in the "Other" section
                        for(int osm = 0; osm < othSectMC; ++osm) {

                            // Compare all meeting's days of current section to all meeting's days of other section
                            if(sections[cs]->getMeetings()[csm]->getDay() == sections[os]->getMeetings()[osm]->getDay()) {
                                
                                std::cout << "Two meetings occur on same day! Will compare the times they occur now!" << std::endl;

                            }

                        }

                    }


                }

            }

        }


        }
        

    }

};

#endif