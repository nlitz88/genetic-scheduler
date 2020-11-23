#ifndef MEETING_H
#define MEETING_H

#include <string>

#include "Time.h"

enum Day {M, T, W, R, F, S, U};


class Meeting {

private:

    // Day of week as enumerated integer (Days from Sunday)
    Day day;

    // Start Time and Stop Time of Meeting
    Time startTime;
    Time endTime;

    // Meeting ID unique to each section
    // std::string meetingId;


public:

    // Default constructor for meeting
    //
    Meeting() {

        day = M;
        startTime = 0;
        endTime = 0;

    }

    // Meeting constructor for providing day, starTime, and endTime
    //
    Meeting(Day initDay, Time initStartTime, Time initEndTime) {

        day = initDay;
        startTime = initStartTime;
        endTime = initEndTime;
        
    }

    // Meeting constructor for providing day, starTime, and endTime (time in minutes as integers)
    //
    Meeting(Day initDay, int initStartTime, int initEndTime) {

        day = initDay;
        startTime = initStartTime;
        endTime = initEndTime;
        
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
    //
    virtual int getMeetingDuration() const {

        int duration;

        int i_endTime = endTime.t();
        int i_startTime = startTime.t();

        if(i_endTime - i_startTime < 0) {

            duration = i_endTime + (1440 - i_startTime);
            
        }
        else {

            duration = i_endTime - i_startTime;

        }
        
        return duration;
    }


    virtual std::string toString() const {

        std::string result;
        
        // result = dayNames[day] + "\n" + startTime.get24HourTime() + "-" + endTime.get24HourTime();
        std::string dayNames[] = {"M", "T", "W", "R", "F", "S", "U"};
        result = dayNames[day];

        return result;

    }


};


#endif