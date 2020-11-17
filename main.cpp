#include <iostream>
#include <fstream>

#include "Section.h"


// This is where the various classes and scheduler optimization aglorithm will be tested.
// This file will eventually server as a broker to the various remote notes that it connects to?

int main() {


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


    for(int i = 0; i < s; ++i) {
        std::cout << sections[i]->getSectionId() << " " << sections[i]->getInstructorLName() << std::endl;
    }
    for(int i = 0; i < s; ++i) {
        delete sections[i];
    }

    Time bedTime(22, 30);
    std::cout << "BedTime: " << bedTime.HH() << ":" << bedTime.MM() << std::endl;
    std::cout << "Time: " << bedTime.t() << std::endl;

    return 0;

}