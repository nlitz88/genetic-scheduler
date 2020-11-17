#ifndef MEETINGTIME_H
#define MEETINGTIME_H

#include "Time.h"

enum Day {M, T, W, R, F, S, U};


class MeetingTime : public Time {

protected:

    // Day of week as enumerated integer (Days from Sunday)
    Day dayOfWeek;
    // Start Time and Stop Time of Meeting
    Time startTime;
    Time endTime;

public:

    virtual Day getDay() const {
        return dayOfWeek;
    }

    virtual Time getStartTime() const {
        return startTime;
    }

    virtual Time getEndTime() const {
        return endTime;
    }


    // Returns time ellapsed of meeting in minutes
    virtual int getMeetingDuration() const {
        int d;
        return d = endTime.getTimeInMinutes() - startTime.getTimeInMinutes() < 0 ? (-1 * d) : d;
    }

    // Consider adding overloads for operators here to manipulate days of week

};


#endif