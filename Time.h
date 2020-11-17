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


    // Returns time in minutes as an integer
    virtual int MM() const {
        return time;
    }


    virtual int HH() const {
        return time % 60;
    }


    virtual int SS() const {
        return time * 60;
    }

    virtual void setTime(int newTimeInMinutes) {
        time = newTimeInMinutes % 1440;
    }


    // Operator Overloads
    //

    Time operator = (const Time& otherTime) {
        this->time = otherTime.time;
        return *this;
    }

    Time operator = (int newTime) {
        this->time = newTime;
        return *this;
    }

    Time operator + (const Time& otherTime) {
        Time temp;
        temp.time = this->time + otherTime.time;
        return temp;
    }

    Time operator + (int otherTime) {
        Time temp;
        temp.time =  this->time + otherTime;
        return temp;
    }

    Time operator - (const Time& otherTime) {
        Time temp;
        temp.time = this->time - otherTime.time;
        return temp;
    }

    Time operator - (int otherTime) {
        Time temp;
        temp.time = this->time - otherTime;
        return temp;
    }
    
    Time operator % (const Time& otherTime) {
        Time temp;
        temp.time = this->time % otherTime.time;
        return temp;
    }

    Time operator % (int otherTime) {
        Time temp;
        temp.time = this->time % otherTime;
        return temp;
    }


    Time operator += (const Time& otherTime) {
        this->time += otherTime.time;
        return *this;
    }

    Time operator += (int additionalTime) {
        this->time += additionalTime;
        return *this;
    }

};


#endif