#ifndef RULE_H
#define RULE_H

// #define DEBUG

#include <iostream>
#include <string>       // CampusTime
#include <vector>       // CampusTime
#include <algorithm>    // CampusTime

#include "Schedule.h"
#include "Section.h"
#include "Time.h"       // CampusTime
#include "Meeting.h"    // CampusTime

class Rule {

protected:

    long fitness;

public:

    // Can we make this a pointer to a schedule? Might be kind of a heavy copy?
    virtual void getFitness(Schedule* schedule) = 0;


    // Operation that returns fitness value of a particular rule
    virtual long fitnessValue() const {
        return fitness;
    }

};




const int WEIGHT_SAMETIME = 1000000;

// Rule that determines fitness according to whether or not the meetings of sections of the same professor overlap (the times at which they occur)
// NOTE: currently, this rule is only configured to add WEIGHT_SAMETIME to the calculated fitness ONCE (as soon as it finds an instance of this in a schedule)
//
class Rule_TimeConflict : public Rule {


public:

    Rule_TimeConflict() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule) {

        // Reset fitness value to evaluate schedule
        fitness = 0;

        Section** sections = schedule->getSections();
        int numSections = schedule->getNumSections();

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
#ifdef DEBUG
                                    std::cout << "TIME CONFLICT: BAD SCHEDULE!\n";
                                    std::cout << sections[cs]->getInstructorLName() << " teaches " << sections[cs]->getSectionId() << " on day "
                                          << currSectMeeting->toString() << " at "
                                          << currSectMeeting->getStartTime().get24HourTime() << "-" << currSectMeeting->getEndTime().get24HourTime() << std::endl;

                                    std::cout << sections[os]->getInstructorLName() << " teaches " << sections[os]->getSectionId() << " on day "
                                          << othSectMeeting->toString() << " at "
                                          << othSectMeeting->getStartTime().get24HourTime() << "-" << othSectMeeting->getEndTime().get24HourTime() << std::endl;
#endif
                                    tc = true;  // time conflict = true --> will break all outer loops. No more fitness evaluation needed


                                }
                                


                            }


                        }


                    }


                }


            }


        }
        

    }

};



const int WEIGHT_BACKTOBACK = 50;

// Rule that determines fitness according to whether or not meetings of sections of the same professor occur back-to-back
// NOTE: Currently configured to add WEIGHT_BACKTOBACK for every occurrence of this (every two  meetings on every day that this might occur)
//
class Rule_BackToBack : public Rule {

public:

    Rule_BackToBack() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule) {

        // Reset fitness value to evaluate schedule
        fitness = 0;

        // Get collections of sections from provided schedule
        Section** sections = schedule->getSections();
        int numSections = schedule->getNumSections();

        int currSectMC = 0;             // Current section meeting count.
        int othSectMC = 0;              // Other section meeting count.

        Meeting* currSectMeeting;       // Pointer to point to one of the current section's meeting object.
        Meeting* othSectMeeting;        // Pointer to point to one of the other sections' meeting object.


        // Compare each section with each subsequent section
        for(int cs = 0; cs < numSections; ++cs) {
            
            for(int os = cs + 1; os < numSections; ++os) {


                // Only concerned with analyzing sections of the same instructor. Check that here.
                if(sections[cs]->getInstructorLName() == sections[os]->getInstructorLName()) {

                    // Classes can only occur back to back if they're on the same day. Thus, must find meetings of each section that occur on the same day,
                    // and then can determine if they occur back to back.

                    currSectMC = sections[cs]->getMeetingCount();
                    othSectMC = sections[os]->getMeetingCount();

                    // To do this, compare each meeting of the current section to each other meeting of the other section
                    for(int csm = 0; csm < currSectMC; ++csm) {

                        for(int osm = 0; osm < othSectMC; ++osm) {


                            // Store current section meeting and other section meeting in pointers for further referencing
                            currSectMeeting = sections[cs]->getMeetings()[csm];
                            othSectMeeting = sections[os]->getMeetings()[osm];
                            
                            // Compare the meetings' days from each section
                            if(currSectMeeting->getDay() == othSectMeeting->getDay()) {

                                // Now, if they occur on the same day, determine if they determine back to back.

                                if(currSectMeeting->getEndTime() == othSectMeeting->getStartTime() ||
                                   othSectMeeting->getEndTime() == currSectMeeting->getStartTime()) {
                                    
                                       fitness += WEIGHT_BACKTOBACK;
#ifdef DEBUG
                                        // Report occurence
                                        std::cout << "BACK TO BACK MEETINGS BETWEEN SECTIONS!\n";
                                        std::cout << sections[cs]->getInstructorLName() << " teaches " << sections[cs]->getSectionId() << " on day "
                                                  << currSectMeeting->toString() << " at "
                                                  << currSectMeeting->getStartTime().get24HourTime() << "-" << currSectMeeting->getEndTime().get24HourTime() << std::endl;

                                        std::cout << sections[os]->getInstructorLName() << " teaches " << sections[os]->getSectionId() << " on day "
                                                  << othSectMeeting->toString() << " at "
                                                  << othSectMeeting->getStartTime().get24HourTime() << "-" << othSectMeeting->getEndTime().get24HourTime() << std::endl;
#endif
                                }


                            }


                        }

                    }


                }


            }

        }


    }

};



const int WEIGHT_CAMPUSTIME = 100;

// Rule that determines fitness according to whether or not the instructor must be on the campus for more than 9 hours
//
class Rule_CampusTime : public Rule {

public:

    Rule_CampusTime() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule) {

        // Reset fitness value to evaluate schedule
        fitness = 0;

        // Get collections of sections from provided schedule
        Section** sections = schedule->getSections();
        int numSections = schedule->getNumSections();

        

        int currSectMC = 0;             // Current section meeting count.
        int othSectMC = 0;              // Other section meeting count.

        Meeting* currSectMeeting;       // Pointer to point to one of the current section's meeting object.
        Meeting* othSectMeeting;        // Pointer to point to one of the other sections' meeting object.
        

        Time earliestStart;
        Time latestEnd;
        int sectionsUsed;               // Will be used to determine when to initialize earliest and latest.
        Time tempMeetingEnd;
        int duration;

        std::string currName;

        std::vector<std::string> instructors;


        // For each Section. This outer loop only really serves as a means of generating a list of instructors from the sections provided.
        // OR, think of it as "for each instructor"
        // NOTE: this could be avoided if this list was generated before hand, like in main. This is a very redundant 
        for(int s = 0; s < numSections; ++s) {

            currName = sections[s]->getInstructorLName();
            
            // As long as we haven't already seen this instructor, add them to the vector and analyze all of their sections.
            if(std::find(instructors.begin(), instructors.end(), currName) == instructors.end()) {
                
                // Add instructor's name to the vector
                instructors.push_back(currName);

                std::cout << "# " << instructors.size() << " - " << currName << ": \n";


                // For each day of the week, we want to examine all meetings of that day that the instructor has.
                for(int day = M; day <= F; ++day) {

                    std::string dayNames[] = {"M", "T", "W", "R", "F", "S", "U"};
                    std::cout << dayNames[day] << std::endl;

                    sectionsUsed = 0;

                    // For each section that the instructor has.
                    for(int cs = 0; cs < numSections; ++cs) {

                        // Must be a section of that instructor
                        if(sections[cs]->getInstructorLName() == currName) {

                            currSectMC = sections[cs]->getMeetingCount();

                            // For each meeting of this section of the instructor
                            for(int csm = 0; csm < currSectMC; ++csm) {

                                currSectMeeting = sections[cs]->getMeetings()[csm];

                                if(currSectMeeting->getDay() == day) {
                                    
                                    // This section has been "used" if it has a meeting on the day we're currently examining.
                                    ++sectionsUsed;
                                    
                                    // HERE, compare this meeting's time to that of the earliest and latest times.

                                    // If first section we're looking at, then initialize earliest and latest with only meeting's values.
                                    if(sectionsUsed == 1) {

                                        earliestStart = currSectMeeting->getStartTime();
                                        latestEnd = currSectMeeting->getEndTime();

                                    }

                                    // Otherwise, compare.
                                    else {

                                        // EarliestStartTime Comparisons
                                        if(currSectMeeting->getStartTime() < earliestStart) {
                                            earliestStart = currSectMeeting->getStartTime();
                                        }

                                        // LatestEndTime Comparisons

                                        // MUST ACCOUNT FOR WHEN ENDTIME BLEEDS OVER INTO NEXT DAY (UNREALISTIC, but will still occur)
                                        // UNLESS the generated times for meetings are adjusted and no longer roll over.
                                        if(currSectMeeting->getStartTime() + currSectMeeting->getMeetingDuration() > 1440) {
                                            tempMeetingEnd = currSectMeeting->getStartTime() + currSectMeeting->getMeetingDuration();
                                        }
                                        else {
                                            tempMeetingEnd = currSectMeeting->getEndTime();
                                        }

                                        if(tempMeetingEnd > latestEnd) {
                                            latestEnd = tempMeetingEnd;
                                        }


                                    }



                                    std::cout << sections[cs]->getSectionId() << ": ";
                                    std::cout << currSectMeeting->getStartTime().get24HourTime() << "-" << currSectMeeting->getEndTime().get24HourTime() << std::endl;
                                    
                                    // No need to examine any other meetings of this section. We only care about the meeting on the particular day.
                                    break;

                                }


                            }


                        }

                    }

                    // Only examine duration if any sections occurred on the day currentl being examined.
                    if(sectionsUsed != 0) {
                        
                        // For each day here, calculate duration that which the instructor's section's meeings span.
                        std::cout << "Earliest Start: " << earliestStart.t() << ". Latest End: " << latestEnd.t() << std::endl;
                        duration = latestEnd.t() - earliestStart.t();
                        if(duration > 540) {
                            fitness += 50;
                            std::cout << sections[s]->getInstructorLName() << " is on campus for more than 9 hours: first Starts @ " << earliestStart.get24HourTime() << ", last ends @ " << latestEnd.get24HourTime() << std::endl;
                        }

                    }

                    


                }

            }

        }


    }

};



#endif