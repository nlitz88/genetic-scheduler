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

    }


    for(int i = 0; i < s; ++i) {
        std::cout << sections[i]->getSectionId() << " " << sections[i]->getInstructorLName() << std::endl;
    }

    return 0;

}