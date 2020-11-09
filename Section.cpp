#include "Section.h"

#include <string>


Section::Section(std::string initId, std::string initLName) {

    sectionId = initId;
    instructorLName = initLName;

}


std::string Section::getSectionId() const {
    return sectionId;
}


void Section::setSectionId(std::string newId) {
    sectionId = newId;
}


std::string Section::getInstructorLName() const {
    return instructorLName;
}


void Section::setInstructorLName(std::string newLName) {
    instructorLName = newLName;
}