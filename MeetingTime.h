#ifndef MEETINGTIME_H
#define MEETINGTIME_H

#include "Time.h"

enum Day {M, T, W, R, F, S, U};


class MeetingTime {

protected:

    // Day of week as enumerated integer (Days from Sunday)
    Day dayOfWeek;
    // Start Time and Stop Time of Meeting
    Time startTime;
    Time endTime;

public:

    // Default Constructor
    MeetingTime() {

        // All values default
        dayOfWeek = M;
        startTime = 0;
        endTime = 0;

    }


    // Constructor that will accept day of week only
    MeetingTime(Day initDayOfWeek) {

        dayOfWeek = initDayOfWeek;
        startTime = 0;
        endTime = 0;
        
    }


    // Constructor that will accept start time and end time only (as Time Objects)
    MeetingTime(Time initStartTime, Time initEndTime) {
        
        dayOfWeek = M;
        startTime = initStartTime;
        endTime = initEndTime;

    }

    // Constructor that will accept start time and end time only (as time in minutes as integers)
    MeetingTime(int initStartTimeInMinutes, int initEndTimeInMinutes) {

        dayOfWeek = M;
        startTime = initStartTimeInMinutes;
        endTime = initEndTimeInMinutes;

    }


    // Constructor that will accept day of week, start time, and end time
    MeetingTime(Day initDayofWeek, Time initStartTime, Time initEndTime) {

        dayOfWeek = initDayofWeek;
        startTime = initStartTime;
        endTime = initEndTime;

    }

    // Constructor that will accept day of week, start time, and end time (start time and end time as integers)
    MeetingTime(Day initDayofWeek, int initStartTimeInMinutes, int initEndTimeInMinutes) {

        dayOfWeek = initDayofWeek;
        startTime = initStartTimeInMinutes;
        endTime = initEndTimeInMinutes;

    }


    virtual ~MeetingTime() {}


    virtual Day getDay() const {
        return dayOfWeek;
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


    // Consider adding overloads for operators here to manipulate days of week

};


#endif