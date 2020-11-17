#ifndef SECTION_H
#define SECTION_H

#include <string>

#include "Meeting.h"

class Section {

private:

    std::string sectionId;
    std::string instructorLName;

    // Collection of Meetings associated with this section
    Meeting** meetings;

public:

    Section(std::string initId, std::string initLName);

    virtual std::string getSectionId() const;
    virtual void setSectionId(std::string newId);

    virtual std::string getInstructorLName() const;
    virtual void setInstructorLName(std::string initLName);


};

#endif