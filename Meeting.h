#ifndef MEETING_H
#define MEETING_H

#include "Time.h"

enum Day {M, T, W, R, F, S, U};


class Meeting {

protected:

    // Day of week as enumerated integer (Days from Sunday)
    Day day;

    // Start Time and Stop Time of Meeting
    Time startTime;
    Time endTime;

public:

    Meeting() {

    }

    virtual Day getDay() const {
        return day;
    }


    virtual void setDay(Day newDay) {
        day = newDay;
    }


    virtual Time getStartTime() const {
        return startTime;
    }


    virtual void setStartTime(Time newTime) {
        startTime = newTime;
    }
    virtual void setStartTime(int newTime) {
        startTime = newTime;
    }


    virtual Time getEndTime() const {
        return endTime;
    }


    virtual void setEndTime(Time newTime) {
        endTime = newTime;
    }
    virtual void setEndTime(int newTime) {
        endTime = newTime;
    }


    // Returns time ellapsed of meeting in minutes
    virtual int getMeetingDuration() const {
        int d;
        return d = endTime.MM() - startTime.MM() < 0 ? (-1 * d) : d;
    }


};

#endif