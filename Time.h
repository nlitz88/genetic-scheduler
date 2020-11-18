#ifndef TIME_H
#define TIME_H

#include <string>


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
        time = ((HH * 60) + MM) % 1440;

    }

    virtual ~Time() {}


    // Returns time in minutes
    virtual int t() const {
        return time;
    }


    virtual void setTime(int newTimeInMinutes) {
        // Prevents negative time
        time = newTimeInMinutes < 0 ? -1 * newTimeInMinutes % 1440 : newTimeInMinutes % 1440;
    }


    // Returns hour of time
    //
    virtual int HH() const {
        return time / 60;
    }


    // Returns minutes of time after hours
    //
    virtual int MM() const {
        return time % 60;
    }


    // Returns string representation of time
    virtual std::string get24HourTime() const {

        std::string result;
        result = (this->HH() < 10 ? "0" + std::to_string(this->HH()) : std::to_string(this->HH()))
               + ":"
               + (this->MM() < 10 ? "0" + std::to_string(this->MM()) : std::to_string(this->MM()));
        
        return result;
        
    }

    
    // Operator Overloads
    //

    bool operator == (int otherTime) {
        return this->time == otherTime;
    }
    bool operator == (const Time& otherTime) {
        return this->time == otherTime.time;
    }


    bool operator != (int otherTime) {
        return this->time != otherTime;
    }
    bool operator != (const Time& otherTime) {
        return this->time != otherTime.time;
    }


    bool operator >= (int otherTime) {
        return this->time >= otherTime;
    }
    bool operator >= (const Time& otherTime) {
        return this->time >= otherTime.time;
    }


    bool operator <= (int otherTime) {
        return this->time <= otherTime;
    }
    bool operator <= (const Time& otherTime) {
        return this->time <= otherTime.time;
    }


    bool operator > (int otherTime) {
        return this->time > otherTime;
    }
    bool operator > (const Time& otherTime) {
        return this->time > otherTime.time;
    }


    bool operator < (int otherTime) {
        return this->time < otherTime;
    }
    bool operator < (const Time& otherTime) {
        return this->time < otherTime.time;
    }



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