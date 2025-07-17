#include <Arduino.h>

/**
 * @class Time
 * @brief Represents a point in time with year, month, day, hour, minute, second, and offset.
 * 
 * The Time class provides methods to manipulate and retrieve information about a specific point in time.
 * It supports conversion to and from ISO8601 format and UNIX timestamp.
 */
class Time {
    public:
        /**
         * Constructor for Time class.
         * Initializes the year, month, day, hour, minute, second, and offset to zero.
         * @param year The year component of the time.
         * @param month The month component of the time.
         * @param day The day component of the time.
         * @param hour The hour component of the time.
         * @param minute The minute component of the time.
         * @param second The second component of the time.
         * @param offset The timezone offset in hours (default is 0).
         */
        Time(int year, int month, int day, int hour, int minute, int second, int offset = 0) {
            this->year = year;
            this->month = month;
            this->day = day;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
            this->offset = offset;
        }

        /**
         * Default constructor for Time class.
         * Initializes the year, month, day, hour, minute, second, and offset to zero.
         */
        Time(){

        }

        /**
         * Parses an ISO8601 formatted string and sets the time components accordingly.
         * @param ISO8601 The ISO8601 formatted string to parse.
         */
        void fromISO8601(String ISO8601) {
            parseISO8601(ISO8601);
        }

        /**
         * Parses a UNIX timestamp and sets the time components accordingly.
         * @param UNIXTimestamp The UNIX timestamp to parse.
         */
        void fromUNIXTimestamp(String UNIXTimestamp) {
            parseUNIXTimestamp(UNIXTimestamp.toInt());
        }

        /**
         * Initialises the time components with the given values.
         * @param year The year component of the time.
         * @param month The month component of the time.
         * @param day The day component of the time.
         * @param hour The hour component of the time.
         * @param minute The minute component of the time.
         * @param second The second component of the time.
         * @param offset The timezone offset in hours (default is 0).
         */
        void fromComponents(int year, int month, int day, int hour, int minute, int second, int offset = 0) {
            this->year = year;
            this->month = month;
            this->day = day;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
            this->offset = offset;
        }



        /**
         * Returns the time in ISO8601 format.
         * @return The time in ISO8601 format.
         */
        String getISO8601() {
            char buffer[25];
            sprintf(buffer, "%04d-%02d-%02dT%02d:%02d:%02d%+03d:00", year, month, day, hour, minute, second, offset);
            return String(buffer);
        }

        /**
         * Returns the time in UNIX timestamp format.
         * @return The time in UNIX timestamp format.
         */
        String getUNIXTimestampString() {
            return String(getUNIXTimestamp());
        }

        /**
         * Returns the time in UNIX timestamp format.
         * @return The time in UNIX timestamp format.
         */
        unsigned long getUNIXTimestamp() {
            struct tm t =
            {
              0 /* tm_sec   */,
              0 /* tm_min   */,
              0 /* tm_hour  */,
              0 /* tm_mday  */,
              0 /* tm_mon   */,
              0 /* tm_year  */,
              0 /* tm_wday  */,
              0 /* tm_yday  */,
              0 /* tm_isdst */
            };
            t.tm_mon = month - 1;
            t.tm_mday = day;
            t.tm_year = year - 1900;
            t.tm_hour = hour;
            t.tm_min = minute;
            t.tm_sec = second;
            t.tm_isdst = -1;

            return mktime(&t);
        }

        /**
         * Returns the year component of the time.\
         * @param iso8601 The ISO8601 formatted string to parse. 
         */
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
        
        /**
         * Parses a UNIX timestamp and sets the time components accordingly.
         * @param unixTimestamp The UNIX timestamp to parse.
         */
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

        /**
         * Sets the year component of the time.
         * @param year The year component of the time.
         */
        void setYear(int year) { this->year = year; }
        
        /**
         * Sets the month component of the time.
         * @param month The month component of the time.
         */
        void setMonth(int month) { this->month = month; }

        /**
         * Sets the day component of the time.
         * @param day The day component of the time.
         */
        void setDay(int day) { this->day = day; }

        /**
         * Sets the hour component of the time.
         * @param hour The hour component of the time.
         */
        void setHour(int hour) { this->hour = hour; }

        /**
         * Sets the minute component of the time.
         * @param minute The minute component of the time.
         */
        void setMinute(int minute) { this->minute = minute; }

        /**
         * Sets the second component of the time.
         * @param second The second component of the time.
         */
        void setSecond(int second) { this->second = second; }

        /**
         * Sets the timezone offset of the time.
         * @param offset The timezone offset of the time.
         */
        void setOffset(int offset) { this->offset = offset; }

        /**
         * Returns the year component of the time.
         * @return The year component of the time.
         */
        int getYear() { return year; }

        /**
         * Returns the month component of the time.
         * @return The month component of the time.
         */
        int getMonth() { return month; }

        /**
         * Returns the day component of the time.
         * @return The day component of the time.
         */
        int getDay() { return day; }

        /**
         * Returns the hour component of the time.
         * @return The hour component of the time.
         */
        int getHour() { return hour; }

        /**
         * Returns the minute component of the time.
         * @return The minute component of the time.
         */
        int getMinute() { return minute; }

        /**
         * Returns the second component of the time.
         * @return The second component of the time.
         */
        int getSecond() { return second; }

        /**
         * Returns the timezone offset of the time.
         * @return The timezone offset of the time.
         */
        int getOffset() { return offset; }

private:
    int year, month, day, hour, minute, second, offset;
};