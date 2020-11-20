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

        

        // Loop through all sections
        for(int s = 0; s < numSections; ++s) {

            // For each section, compare against all other sections that are taught by same instructor (same lName)
            for(int os = s + 1; os < numSections; ++os) {

                // If section is from the same instructor, then compare their meetings.
                if(sections[s]->getInstructorLName() == sections[os]->getInstructorLName()) {


                    // Will have to compare meetings on each day of the week for between all of the different meetings on different days.
                    
                    int currSectMC = sections[s]->getMeetingCount();
                    int othSectMC = sections[os] ->getMeetingCount();

                    
                    int mn = 0; // meeting number
                    // Compare each meeting of current section to each meeting of other section (or vice versa) until find ones that occur on same day
                    while(mn < (currSectMC > othSectMC ? currSectMC : othSectMC)) {
                        
                        // Then do ANOTHER NESTED FOR LOOP HERE TO LOOP THROUGH ALL OF THE MEETINGS OF THE OTHER SECTION
                        // NESTED LOOP STRUCTURE IS WHAT WE WANT HERE; NO LOGIC NEEDED THEN UP ABOVE.
                        // Only want to compare meeting times if the sections have meetings on the same day
                        if(sections[s]->getMeetings()[])

                    }

                    // Instead of that while loop:
                    bool matchingDays = false;

                    for(int csm = 0; csm < currSectMC; ++csm) {

                        for(int osm = 0; osm < othSectMC; ++osm) {

                            // Compare all meeting's days of current section to all meeting's days of other section

                        }

                    }


                }

            }

        }


        }
        

    }

};

#endif