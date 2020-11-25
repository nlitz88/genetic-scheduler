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




const int WEIGHT_TIMECONFLICT = 1000000;

// Rule that determines fitness according to whether or not the meetings of sections of the same professor overlap (the times at which they occur)
// NOTE: currently, this rule is only configured to add WEIGHT_TIMECONFLICT to the calculated fitness ONCE (as soon as it finds an instance of this in a schedule)
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

                                    fitness = WEIGHT_TIMECONFLICT;
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



const int WEIGHT_CAMPUSTIME = 100;

// Rule that determines fitness according to whether or not the instructor must be on the campus for more than 9 hours
// Should add 100 for EVERY AFTER beyond 9 hours that they're on campus
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

#ifdef DEBUG
                std::cout << "# " << instructors.size() << " - " << currName << ": \n";
#endif


                // For each day of the week, we want to examine all meetings of that day that the instructor has.
                for(int day = M; day <= F; ++day) {

#ifdef DEBUG
                    std::string dayNames[] = {"M", "T", "W", "R", "F", "S", "U"};
                    std::cout << dayNames[day] << std::endl;
#endif

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
                                        if(currSectMeeting->getEndTime() > latestEnd) {
                                            latestEnd = currSectMeeting->getEndTime();
                                        }

                                        // // MUST ACCOUNT FOR WHEN ENDTIME BLEEDS OVER INTO NEXT DAY (UNREALISTIC, but will still occur)
                                        // // UNLESS the generated times for meetings are adjusted and no longer roll over.             ---> NOW IMPLEMENTED
                                        // if(currSectMeeting->getStartTime() + currSectMeeting->getMeetingDuration() > 1440) {
                                        //     tempMeetingEnd = currSectMeeting->getStartTime() + currSectMeeting->getMeetingDuration();
                                        // }
                                        // else {
                                        //     tempMeetingEnd = currSectMeeting->getEndTime();
                                        // }

                                        // if(tempMeetingEnd > latestEnd) {
                                        //     latestEnd = tempMeetingEnd;
                                        // }


                                    }


#ifdef DEBUG
                                    std::cout << sections[cs]->getSectionId() << ": ";
                                    std::cout << currSectMeeting->getStartTime().get24HourTime(false) << "-" << currSectMeeting->getEndTime().get24HourTime(false) << std::endl;
#endif
                                    // No need to examine any other meetings of this section. We only care about the meeting on the particular day.
                                    break;

                                }


                            }


                        }

                    }

                    // Only examine duration if any sections occurred on the day currentl being examined.
                    if(sectionsUsed != 0) {
                        
                        // For each day here, calculate duration that which the instructor's section's meeings span.
#ifdef DEBUG
                        std::cout << "Earliest Start: " << earliestStart.get24HourTime(false) << ". Latest End: " << latestEnd.get24HourTime(false) << std::endl;
#endif
                        duration = latestEnd.t() - earliestStart.t();
                        if(duration > 540) {
                            // Must add WEIGHT_CAMPUSTIME for EVERY HOUR BEYOND 9 hours.
                            fitness += ((duration - 540) / 60) * WEIGHT_CAMPUSTIME;
#ifdef DEBUG
                            std::cout << sections[s]->getInstructorLName() << " is on campus for more than 9 hours: " << duration << " - first Starts @ " << earliestStart.get24HourTime(false) << ", last ends @ " << latestEnd.get24HourTime(false) << std::endl;
#endif
                        }

                    } 


                }

            }

        }


    }

};



const int WEIGHT_NEXTDAY = 100;

// Rule that determines fitness based on if instructor is on campus after 6 pm and there the next morning before 11 am
// Adds WEIGHT_NEXTDAY for EVERY HOUR before 11 AM that an instructor must arrive if they teach at 6pm the day before.
//
class Rule_NextDay : public Rule {

public:

    Rule_NextDay() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule) {

        // Reset fitness value to evaluate schedule.
        fitness = 0;

        Section** sections = schedule->getSections();
        int numSections = schedule->getNumSections();

        int currSectMC = 0;             // Current section meeting count.
        int othSectMC = 0;              // Other section meeting count.

        Meeting* currSectMeeting;       // Pointer to point to one of the current section's meeting object.
        Meeting* othSectMeeting;        // Pointer to point to one of the other sections' meeting object.


        for(int cs = 0; cs < numSections; ++cs) {


            // Get number of meetings in current section.
            currSectMC = sections[cs]->getMeetingCount();

            for(int csm = 0; csm < currSectMC; ++csm) {


                // Get meeting of current section.
                currSectMeeting = sections[cs]->getMeetings()[csm];

                // Check if this meeting starts at or goes past 6 PM (1080) (BUT NOT IF THE MEETING IS ON FRIDAY)
                if(currSectMeeting->getDay() != F && (currSectMeeting->getStartTime() >= 1080 ||
                   currSectMeeting->getStartTime() + currSectMeeting->getMeetingDuration() > 1080)) {

                    
                    // Now, we want to check if any other sections of the SAME INSTRUCTOR have meetings on the NEXT day.
                    for(int os = 0; os < numSections; ++os) {       // All other sections (not just those after current)

                        // Don't bother examining if same section as current (they will never have meetings on back to back days) (Remove if this rule changed);
                        // if(os == cs) {continue;}

                        if(sections[os]->getInstructorLName() == sections[cs]->getInstructorLName()) {

                            othSectMC = sections[os]->getMeetingCount();

                            // For each meeting in other section.
                            for(int osm = 0; osm < othSectMC; ++osm) {


                                othSectMeeting = sections[os]->getMeetings()[osm];

                                // If day of other section is one past the day of the current section (the next day).
                                if(othSectMeeting->getDay() == currSectMeeting->getDay() + 1) {

                                    // Then, check if this meeting the next day occurs before 11 AM (660).
                                    if(othSectMeeting->getStartTime() < 660) {

                                        // If so, add WEIGHT_NEXTDAY to fitness for every hour before 11 that it occurs.
                                        fitness += ((660 - othSectMeeting->getStartTime().t()) / 60) * WEIGHT_NEXTDAY;

#ifdef DEBUG

                                        // Report details of occurence.
                                        // REPORT:
                                        //      Instructor First
                                        //      Section: Current meeting that occurs after 6PM and the day that it occurs on:
                                        //      Section: Other meeting that occurs (the day after)
                                        std::cout << "COURSE OCCURS AFTER 6PM DAY BEFORE\n";
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

    }

};



const int WEIGHT_TWOEVENINGS = 50;
const int EVENINGTIME = 1080;
const int EVENINGTHRESHOLD = 2;

// Consider adding functionality to extend this Rule so that it can have different weights past different times.

// Rule that determines fitness according to how many evenings an instructor is scheduled.
// Adds WEIGHT_TWOEVENINGS for every evening beyond two that an instructor is schedule.
//
class Rule_TwoEvenings : public Rule {


public:
    
    Rule_TwoEvenings() {
        fitness = 0;
    }

    virtual void getFitness(Schedule* schedule) {

        // Reset fitness value to evaluate schedule.
        fitness = 0;

        Section** sections = schedule->getSections();
        int numSections = schedule->getNumSections();

        int currSectMC = 0;             // Current section meeting count.

        Meeting* currSectMeeting;       // Pointer to point to one of the current section's meeting object.

        std::string currName;
        std::vector<std::string> instructors;

        int eveCount = 0;
        

        // For each instructor. This outer loop serves as a means of generating a list of professors. This could be avoided if this was generated beforehand.
        for(int s = 0; s < numSections; ++s) {

            currName = sections[s]->getInstructorLName();
            
            // As long as we haven't already seen this instructor, add them to the vector and analyze all of their sections.
            if(std::find(instructors.begin(), instructors.end(), currName) == instructors.end()) {
                
                // Add instructor's name to the vector
                instructors.push_back(currName);

#ifdef DEBUG
                std::cout << "# " << instructors.size() << " - " << currName << ": \n";
#endif


                // For each section.
                for(int cs = 0; cs < numSections; ++cs) {


                    // If section is by the current instructor.
                    if(sections[cs]->getInstructorLName() == currName) {

                        currSectMC = sections[cs]->getMeetingCount();
                        
                        // For each meeting in current section.
                        for(int csm = 0; csm < currSectMC; ++csm) {


                            // Get current meeting.
                            currSectMeeting = sections[cs]->getMeetings()[csm];
                            
                            // If current meeting starts at or after 6 PM (1080).
                            if(currSectMeeting->getStartTime() >= EVENINGTIME) {

                                ++eveCount;

#ifdef DEBUG
                                std::cout << sections[cs]->getSectionId() << ": ";
                                std::cout << currSectMeeting->getStartTime().get24HourTime(false) << "-" << currSectMeeting->getEndTime().get24HourTime(false) << std::endl;
#endif

                            }


                        }


                    }


                }

                // Once all sections that an instructor could have are examined, determine number of evenings they must be on campus. If > 2,
                // add WEIGHT_TWOEVENINGS for each after 2.
                if(eveCount > EVENINGTHRESHOLD) {

                    fitness += (eveCount - EVENINGTHRESHOLD) * WEIGHT_TWOEVENINGS;

#ifdef DEBUG
                    std::cout << currName << " is on campus " << eveCount << " days at/after 6PM\n"; 
#endif

                }

                // Reset eveCount to continue examining sections of other instructors.
                eveCount = 0;
                
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



const int WEIGHT_AROUNDCOMMON = 50;
const int COMMONHOURSTART = 720;
const int COMMONHOUREND = 780;

// Rule that determines fitness according to if they teach (have meetings from two different sections) before AND after common hour.
//
class Rule_AroundCommon : public Rule {

public:

    Rule_AroundCommon() {
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


        // For each section.
        for(int cs = 0; cs < numSections; ++cs) {


            // For each other section.
            for(int os = 0; os < numSections; ++os) {

                
                // If sections are from the same instructor.
                if(sections[os]->getInstructorLName() == sections[cs]->getInstructorLName()) {

                    // Get meeting counts for the current section and other section.
                    currSectMC = sections[cs]->getMeetingCount();
                    othSectMC = sections[os]->getMeetingCount();
                    
                    // Now, compare all meetings of current section to all meetings of other section. Want to examine the times of meetings of the two sections that occur on the SAME DAY.
                    for(int csm = 0; csm < currSectMC; ++csm) {


                        for(int osm = 0; osm < othSectMC; ++osm) {
                            
                            // Get current meeting and other meeting.
                            currSectMeeting = sections[cs]->getMeetings()[csm];
                            othSectMeeting = sections[os]->getMeetings()[osm];

                            // Only want to compare times of meeings if they occur on the same day.
                            if(othSectMeeting->getDay() == currSectMeeting->getDay()) {


                                // If csm ends immediately before common hour and osm starts immediately after OR vice versa, add WEIGHT_AROUNDCOMMON to fitness.
                                // Note: this will only occur once for a particular day. Thus, add WEIGHT_AROUNDCOMMON for that day.

                                if((currSectMeeting->getEndTime() == COMMONHOURSTART && othSectMeeting->getStartTime() == COMMONHOUREND) ||
                                    (othSectMeeting->getEndTime() == COMMONHOURSTART && currSectMeeting->getStartTime() == COMMONHOUREND)) {

                                    fitness += WEIGHT_AROUNDCOMMON;
                                        
                                }



                            }


                        }


                    }


                }


            }


        }
   
    }

};



// Also implement rule of my own that adds a significant amount whenever a course ends after 9pm or starts before 7 AM (no matter the instructor, just in general)


#endif