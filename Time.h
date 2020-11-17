#ifndef TIME_H
#define TIME_H


class Time {

protected:

    // Time in minutes
    int time;

public:

    // Default Constructor: Default Time == 0;
    Time() {
        time = 0;
    }

    // Constructor accepting preset time
    Time(int initTimeInMinutes) {
        time = initTimeInMinutes;
    }

    // Constructor accepting preset time in format HH, MM (24 Hour)
    Time(int HH, int MM) {
        
        // Max time cannot exceed 1440 minutes (1440 minutes in a day)
        time = (HH * 60 + MM) % 1440;

    }

    virtual ~Time() {}


    virtual int getTimeInMinutes() const {
        return time;
    }

    virtual int getTimeInHours() const {
        return time % 60;
    }

    virtual int getTimeInSeconds() const {
        return time * 60;
    }

};


#endif