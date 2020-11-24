#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <fstream>
#include <random>
#include <time.h>

#include "Schedule.h"
#include "Section.h"
#include "Meeting.h"
#include "Optimizer.h"

class Scheduler {

private:

    Section** baseSections;


public:

    // Default Constructor.
    //
    Scheduler();

    // Constructor that accepts name of sections file. Each Scheduler is specific to one group of sections until changed.
    //
    Scheduler(std::string sectionsFile);

    // Destructor.
    //
    ~Scheduler();

    //



    // Scheduler will:
    //      - Retrive sections from file. Will maintain a BASE collection of sections that each schedule will use in its own way.
    //      - MAYBE: Contains genetic algorithm for improvement? OR is that for the Optimizer?
    //      - Or does the genetic algorithm live here, and only use the Optimizer's functions for ranking, and then mutating/crossover?
    // 

    // For each schedule that it needs to generate it will:
        // create a new Schedule Object, passing in sections
        // This function will subsequently generate meetings for each section.






    // Operation that will generate Meetings for sections of a particular schedule.
    //
    virtual void generateSectionMeetings(Section* section) {


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


                // std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;


                // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection

                section->addMeeting(new Meeting(M, startTime, endTime));
                section->addMeeting(new Meeting(W, startTime, endTime));
                section->addMeeting(new Meeting(F, startTime, endTime));

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
                

                // std::cout << "Meeting Time: " << startTime.get24HourTime() << std::endl;

                // 3.) Then, instantiate and add new Meeting objects with the parameters to the section's "meetings" collection
                
                if(dayScheme == TR) {
                    section->addMeeting(new Meeting(T, startTime, endTime));
                    section->addMeeting(new Meeting(R, startTime, endTime));
                }
                else {
                    section->addMeeting(new Meeting(M, startTime, endTime));
                    section->addMeeting(new Meeting(W, startTime, endTime));
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
                
                // std::cout << "Any" << std::endl; 

                // 3.) Generate the random day on which the section will occur (limited to M-F)
                Day sectionDay = static_cast<Day>(rand() % 5);

                // 4.) Then, instantiate and add the single Meeting object with parameters to section's "meetings" collection
                section->addMeeting(new Meeting(sectionDay, startTime, endTime));

                break;
        }


        // std::string daySchemes[] {"MWF", "TR", "MW", "A"};
        // std::cout << "Day Scheme: " << daySchemes[dayScheme] << ". Will meet " << meetingCount << " time(s) per week." << std::endl;


    }


    // Operation that will generate a schedule by generating Meetings for each new schedule object that it has.
    //
    virtual void generateScheduleSections(Schedule* schedule) {

        // Essentially, just call generateSectionMeetings for each section to be in the provided schedule.
        for(int s = 0; s < schedule->getNumSections(); ++s) {

            // Generate meetings for each section within schedule.
            generateSectionMeetings(schedule->getSections()[s]);

        }

    }


};


#endif