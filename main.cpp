#include <iostream>
#include <fstream>

#include <random>
#include <time.h>

#include "Section.h"


// This is where the various classes and scheduler optimization aglorithm will be tested.
// This file will eventually server as a broker to the various remote notes that it connects to?

int main() {

    // Seed random number generator
    srand(time(0));


    // Test reading in from file a collection of sections
    Section** sections = new Section* [50];

    std::ifstream fin;
    fin.open("sections.txt");
    
    int s = 0;
    std::string id, lname;
    while(!fin.eof()) {
        
        fin >> id >> lname;

        sections[s++] = new Section(id, lname);

        // NOTE: Should I check for duplicate sections in the provided list?
        //       I would imagine these should be ignored. Ask Hal about this later.

    }


    // for(int i = 0; i < s; ++i) {
    //     std::cout << sections[i]->getSectionId() << " " << sections[i]->getInstructorLName() << std::endl;
    // }

    // Pointer to test section
    Section* s1 = sections[0];

    std::cout << s1->getSectionId() << " meetings: \n\n";
    // s1->addMeeting(new Meeting(T, Time(9,05), Time(9,55)));
    // s1->addMeeting(new Meeting(R, Time(9,05), Time(9,55)));
    s1->generateMeetings();
    // std::cout << s1->toString();


    for(int i = 0; i < s; ++i) {
        delete sections[i];
    }

    return 0;

}