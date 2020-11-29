#include <iostream>
#include <fstream>

#include <random>
#include <time.h>
#include <chrono>

#include "Schedule.h"
#include "Scheduler.h"
#include "Optimizer.h"


// This is where the various classes and scheduler optimization aglorithm will be tested.
// This file will eventually server as a broker to the various remote notes that it connects to?

int main() {

    // Seed random number generator
    srand(time(0));

    auto startTime = std::chrono::high_resolution_clock::now();


    // Test reading in from file a collection of sections
    // Section** sections = new Section* [50];
    // int numSections = 0;

    // std::ifstream fin;
    // fin.open("sections.txt");
    
    // std::string id, lname;
    // while(!fin.eof()) {
        
    //     fin >> id >> lname;

    //     sections[numSections++] = new Section(id, lname);

    //     // NOTE: Should I check for duplicate sections in the provided list?
    //     //       I would imagine these should be ignored. Ask Hal about this later.

    // }


    // for(int i = 0; i < s; ++i) {
    //     std::cout << sections[i]->getSectionId() << " " << sections[i]->getInstructorLName() << std::endl;
    // }

    // Pointer to test section
    // Section* s1 = sections[0];

    // std::cout << s1->getSectionId() << " meetings: \n\n";
    // s1->addMeeting(new Meeting(T, Time(9,05), Time(9,55)));
    // s1->addMeeting(new Meeting(R, Time(9,05), Time(9,55)));
    // s1->generateMeetings();
    // std::cout << s1->toString();



    // Schedule* sched1 = new Schedule(sections, numSections);

    // sched1->generateSchedule();
    // std::cout << sched1->toString();

    // sched1->~Schedule();

    // for(int i = 0; i < numSections; ++i) {
    //     delete sections[i];
    // }

    // std::cout << "This section should still exist: " << s1->toString();



    // Rule_TimeConflict sameTimeRule;
    // Rule_BackToBack backToBackRule;
    // Rule_CampusTime campusTimeRule;
    // Rule_LongClassesPerDay longClassesPerDay;








    // const int POPULATION_SIZE = 1;

    // int overallFitness = 0;
    // int numBad = 0;
    // int numGood = 0;

    // Optimizer opt;

    // Schedule** schedules = new Schedule* [POPULATION_SIZE];

    // for(int s = 0; s < POPULATION_SIZE; ++s) {

    //     schedules[s] = new Schedule(sections, numSections);
    //     schedules[s]->generateSchedule();

    //     // Is this the functionality that we would wrap up in the optimizer's fitness function? (I.e. is this what the fitness function would essentially be responsible for)
    //     // Then, get fitness of shedule (in incorrect way for now)
    //     // sameTimeRule.getFitness(schedules[s]);
    //     // backToBackRule.getFitness(schedules[s]);
    //     // campusTimeRule.getFitness(schedules[s]);
    //     // longClassesPerDay.getFitness(schedules[s]);

    //     // overallFitness = longClassesPerDay.fitnessValue();
    //     // overallFitness = sameTimeRule.fitnessValue() + backToBackRule.fitnessValue() + campusTimeRule.fitnessValue();

    //     overallFitness = opt.getScheduleFitness(schedules[s]);

    //     if(overallFitness >= 1000000) {
    //         ++numBad;
    //     } else {
    //         ++numGood;
    //     }

    //     std::cout << "Fitness of schedule #" <<  s << " : " << overallFitness << std::endl;

    // }

    // std::cout << "Probability to getting schedule w/o time conflict: " << numGood << "\\" << numBad + numGood << "  ==  " << static_cast<double>(numGood)/(numBad + numGood) * 100 << "%" << std::endl;





    // *******************************************************************************
    //
    //                             Testing Scheduler
    //
    // *******************************************************************************



    std::cout << "\nNow testing Scheduler\n\n";


    // ************************** ALGORITHM CONSTANTS **************************


    // Defines how large a population should be. Initially this is how many random schedules to initially generate and then how many schedules need to be generated by the elite.
    const int POPULATION_SIZE = 1000;

    // Defines the number in the elite population to be used to create the next generation.
    const int ELITE_SIZE = 20;

    // Defines the number of times a new generation should be created in the event an optimal solution is not found.
    const int MAX_ITERATIONS = 1000;

    // Defines the maximum number of times a new population is created when there is no improvement in fitness. That is, if the same best fitness value occurs STABLE_ITERATIONS times in a row, the algorithm with terminate regardless if MAX_ITERATIONS is reached.
    const int STABLE_ITERATIONS = 5;






    // Optimizer object that will calculate fitness for each schedule.
    Optimizer optimizer;

    // Create new Scheduler. Pass in filename so that it can generate collection of sections.
    Scheduler scheduler = Scheduler("sections.txt");

    // Collection of Schedules for POPULATION and ELITE.
    Schedule** population = new Schedule* [POPULATION_SIZE];
    Schedule** elite = new Schedule* [ELITE_SIZE];
    

    // Generate initial population.
    population = scheduler.generateSchedules(POPULATION_SIZE);
    

    // Initial bestFit = population[0]
    Schedule* bestFit = population[0];
    
    int iterations = 0;
    int timesSame = 0;


    while(bestFit > 0 && iterations < MAX_ITERATIONS && timesSame < STABLE_ITERATIONS) {


        // Use Optimizer to get/assign fitness to each schedule.
        for(int s = 0; s < POPULATION_SIZE; ++s) {
            population[s]->setFitness(optimizer.getScheduleFitness(population[s]));
        }


        // Sort population by fitness from most fit --> least fit (i.e., smallest fitness to largest) (Selection sort)
        int mostFitIndex = 0;
        Schedule* temp;

        for(int start = 0; start < POPULATION_SIZE - 1; ++start) {

            mostFitIndex = start;

            for(int e = start; e < POPULATION_SIZE; ++e) {

                if(population[e]->getFitness() < population[mostFitIndex]->getFitness()) {
                    mostFitIndex = e;
                }

            }

            // If maxIndex != start, then a more fit schedule (smaller fitness) has been found, and a swap must be performed.
            if(mostFitIndex != start) {

                temp = population[start];
                population[start] = population[mostFitIndex];
                population[mostFitIndex] = temp;

            }
            
        }

        // Print out sorted result.
        // for(int s = 0; s < POPULATION_SIZE; ++s) {
        //     std::cout << "Fitness of Schedule " << s << ": " << population[s]->getFitness() << std::endl;
        // }
        // std::cout << std::endl << population[0]->toString() << std::endl;
        // std::cout << "Most Fit: " << population[0]->getFitness() << std::endl << std::endl;


        // Extract elite.
        for(int e = 0; e < ELITE_SIZE; ++e) {
            elite[e] = population[e];
        }
        // Print out Elite.
        std::cout << "Elite Schedule Fitnesses: \n";
        for(int e = 0; e < ELITE_SIZE; ++e) {
            std::cout << e << " : " << elite[e]->getFitness() << std::endl;
        }
        std::cout << "\n\n";




        // NOW, compare fitness of this generation's best to that of previous. Sort of just an intermediary step to track the progress of the genetic algorithm.

        // If best of newest generation same as last, ++timesSame.
        if(elite[0]->getFitness() == bestFit->getFitness()) {
            ++timesSame;
        } 
        // Otherwise, reset timesSame and examine the new best.
        else {

            timesSame = 0;

            // If most fit of newest generation is better than the rest so far, then set it as the new best.
            if(elite[0]->getFitness() < bestFit->getFitness()) {
                bestFit = elite[0];
            }

        }





        // THEN, HERE IS WHERE THE ACTUAL CROSSOVER/MUTATIONS SHOULD OCCUR. That way, when it loops around again, it will be examining the new population.
        


        // Also, depending on how this works, should I release memory of all other schedules left in the population?? (this should subequently have each's sections and meetings destroyed).


        // Then, perform crossover on schedules.


        // Crossover:
        //      For each elite schedule, choose another random schedule (from the elites (that's not the current)).
        //          Take one half of that other schedule (alphabetically) and give it to the current elite, and give the second half of the current to the other
        //          Maybe this is how it works???


        // First, (this is unecessary, but) place elites at top of population
        for(int e = 0; e < ELITE_SIZE; ++e) {

            population[e] = elite[e];

        }


        // Two Schedule pointers to maintain the two new Schedules that will be spliced together.
        Schedule* newSchedA = nullptr;
        Schedule* newSchedB = nullptr;

        // Two Schedule pointers to maintain the two random elites selected to take sections from.
        Schedule* eliteA = nullptr;
        Schedule* eliteB = nullptr;

        // Then, this is where we REGENERATE the rest of the population with new, hopefully BETTER schedules.
        // p += 2 here, as with each crossover, two new schedules are being created. Therefore, step through population and regenerate two at a time.
        for(int p = ELITE_SIZE - 1; p < POPULATION_SIZE; p += 2) {


            // First, release memory of old schedule objects
            delete population[p];

            // Then, crossover. Maybe if I have time introduce mutations somewhere in the algo.


            // Create new Schedule objects (this instructor just creates a Schedule with a blank collection of pointers to sections) (Use addSection to add).
            newSchedA = new Schedule();
            newSchedB = new Schedule();

            // Get two random elite Schedules.
            eliteA = elite[(rand() % ELITE_SIZE)];
            do {
                eliteB = elite[(rand() % ELITE_SIZE)];
            } while(eliteB == eliteA);
            

            // First, get a random section to act as the "split point."
            int splitPoint = rand() % eliteA->getNumSections();        // Just use one of the elites to get num sections.


            // Give newSchedA all sections from eliteA up to section splitPoint, and then all the rest after (and including) splitPoint to newSchedA from eliteB
            // And vice versa for newSchedB
            for(int s = 0; s < splitPoint; ++s) {

                // Add new Section object (copied from section of elite) to newSchedA.
                newSchedA->addSection(new Section(*(eliteA->getSections()[s])));

                
                // Will have to manually copy meetings over from each section to new section of newSchedA
                // Is it safe to make copy constructor handle this? Or should I make a custom function in Section that does this.

                // I think making a new Operation in Section to "CopyMeetingsFromOtherSection" or something like that would be good.
                // But BE CAREFUL; it would also have to create copies of each meeting. Otherwise, when sections get destroyed, then everything below them gets destroyed.

            }


        }




        ++iterations;


    }











    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    std::cout << "Main execution time: " << duration.count() << std::endl;

    return 0;

    // old: 9107634 microseconds
    // new: 

}