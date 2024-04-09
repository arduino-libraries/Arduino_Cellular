#include <Arduino.h>

class Time {
public:
    Time(int year, int month, int day, int hour, int minute, int second, int offset = 0) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
        this->offset = offset;
    }

    Time(){

    }

    void fromISO8601(String ISO8601) {
        parseISO8601(ISO8601);
    }

    void fromUNIXTimestamp(String UNIXTimestamp) {
        parseUNIXTimestamp(UNIXTimestamp.toInt());
    }

    void fromComponents(int year, int month, int day, int hour, int minute, int second, int offset = 0) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
        this->offset = offset;
    }




    String getISO8601() {
        char buffer[25];
        sprintf(buffer, "%04d-%02d-%02dT%02d:%02d:%02d%+03d:00", year, month, day, hour, minute, second, offset);
        return String(buffer);
    }

    String getUNIXTimestampString() {
        // Simple conversion to UNIX timestamp, not accounting for leap years or time zones
        long timestamp = second + minute*60 + hour*3600 + day*86400 + (month-1)*2629743 + (year-1970)*31556926;
        return String(timestamp);
    }

    unsigned long getUNIXTimestamp() {
        // Simple conversion to UNIX timestamp, not accounting for leap years or time zones
        unsigned long timestamp = second + minute*60 + hour*3600 + day*86400 + (month-1)*2629743 + (year-1970)*31556926;
        return timestamp;
    }

    void parseISO8601(String iso8601) {
        // Simplified parsing, assuming format "YYYY-MM-DDTHH:MM:SS+00:00"
        year = iso8601.substring(0, 4).toInt();
        month = iso8601.substring(5, 7).toInt();
        day = iso8601.substring(8, 10).toInt();
        hour = iso8601.substring(11, 13).toInt();
        minute = iso8601.substring(14, 16).toInt();
        second = iso8601.substring(17, 19).toInt();
        // This does not parse the timezone offset correctly, just a placeholder
        offset = 0;
        // TODO: don't use substrings, use index of comma, dash etc
    }

    void parseUNIXTimestamp(long unixTimestamp) {
        // Simplified conversion, not accounting for leap years or time zones
        second = unixTimestamp % 60;
        minute = (unixTimestamp / 60) % 60;
        hour = (unixTimestamp / 3600) % 24;
        day = (unixTimestamp / 86400) % 30; // Simplification
        month = (unixTimestamp / 2629743) % 12 + 1; // Approximation
        year = (unixTimestamp / 31556926) + 1970; // Approximation
        // This does not set the timezone offset, as UNIX timestamp is typically considered UTC
        offset = 0;
    }

    void setYear(int year) { this->year = year; }
    void setMonth(int month) { this->month = month; }
    void setDay(int day) { this->day = day; }
    void setHour(int hour) { this->hour = hour; }
    void setMinute(int minute) { this->minute = minute; }
    void setSecond(int second) { this->second = second; }
    void setOffset(int offset) { this->offset = offset; }

    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }
    int getHour() { return hour; }
    int getMinute() { return minute; }
    int getSecond() { return second; }
    int getOffset() { return offset; }

private:
    int year, month, day, hour, minute, second, offset;
};