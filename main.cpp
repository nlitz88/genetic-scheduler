#include <iostream>
#include <fstream>

#include <random>
#include <time.h>
#include <chrono>

#include "Section.h"
#include "Schedule.h"
// #include "Rule.h"
#include "Optimizer.h"


// This is where the various classes and scheduler optimization aglorithm will be tested.
// This file will eventually server as a broker to the various remote notes that it connects to?

int main() {

    // Seed random number generator
    srand(time(0));

    auto startTime = std::chrono::high_resolution_clock::now();


    // Test reading in from file a collection of sections
    Section** sections = new Section* [50];
    int numSections = 0;

    std::ifstream fin;
    fin.open("sections.txt");
    
    std::string id, lname;
    while(!fin.eof()) {
        
        fin >> id >> lname;

        sections[numSections++] = new Section(id, lname);

        // NOTE: Should I check for duplicate sections in the provided list?
        //       I would imagine these should be ignored. Ask Hal about this later.

    }


    // for(int i = 0; i < s; ++i) {
    //     std::cout << sections[i]->getSectionId() << " " << sections[i]->getInstructorLName() << std::endl;
    // }

    // Pointer to test section
    Section* s1 = sections[0];

    // std::cout << s1->getSectionId() << " meetings: \n\n";
    // s1->addMeeting(new Meeting(T, Time(9,05), Time(9,55)));
    // s1->addMeeting(new Meeting(R, Time(9,05), Time(9,55)));
    // s1->generateMeetings();
    // std::cout << s1->toString();



    Schedule* sched1 = new Schedule(sections, numSections);

    sched1->generateSchedule();
    // std::cout << sched1->toString();

    // sched1->~Schedule();

    // for(int i = 0; i < numSections; ++i) {
    //     delete sections[i];
    // }

    // std::cout << "This section should still exist: " << s1->toString();



    // Rule_TimeConflict sameTimeRule;
    // Rule_BackToBack backToBackRule;
    // Rule_CampusTime campusTimeRule;

    long overallFitness = 0;
    int numBad = 0;
    int numGood = 0;

    Optimizer opt;

    Schedule** schedules = new Schedule* [20000];

    for(int s = 0; s < 20000; ++s) {

        schedules[s] = new Schedule(sections, numSections);
        schedules[s]->generateSchedule();

        // Is this the functionality that we would wrap up in the optimizer's fitness function? (I.e. is this what the fitness function would essentially be responsible for)
        // Then, get fitness of shedule (in incorrect way for now)
        // sameTimeRule.getFitness(schedules[s]);
        // backToBackRule.getFitness(schedules[s]);
        // campusTimeRule.getFitness(schedules[s]);

        // overallFitness = sameTimeRule.fitnessValue();
        // overallFitness = sameTimeRule.fitnessValue() + backToBackRule.fitnessValue() + campusTimeRule.fitnessValue();

        overallFitness = opt.getScheduleFitness(schedules[s]);

        if(overallFitness >= 1000000) {
            ++numBad;
        } else {
            ++numGood;
        }

        // std::cout << "Fitness of schedule #" <<  s << " : " << overallFitness << std::endl;

    }

    std::cout << "Probability to getting schedule w/o time conflict: " << numGood << "\\" << numBad + numGood << "  ==  " << static_cast<double>(numGood)/(numBad + numGood) * 100 << "%" << std::endl;



    // for(int s = 0; s < sched1->getNumSections(); ++s) {
    //     std::cout << "Section " << s << " of sched1 has " << sched1->getSections()[s]->getMeetingCount() << " meetings\n";
    // }

    



    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    std::cout << "Main execution time: " << duration.count() << std::endl;

    return 0;

    // old: 9107634 microseconds
    // new: 

}