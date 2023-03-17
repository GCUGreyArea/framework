// ==================================================================
// Date.cpp
//
// NOTE:
// ==================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <stdio.h>
#include <string.h>
#include <time.h>


#include "Date.h"

Date::Date() : Base("Date") {
    mFmat = DATE_NAM_FMAT;
    now();
}

Date::Date(time_t& dt) : Base("Date"),
                         mNow(dt) {
    mFmat = DATE_NAM_FMAT;
}

Date::Date(Date & date) : Base("Date") {
    mFmat = DATE_NAM_FMAT;
    this->assign(date);
}

Date::Date(struct tm& ttime) : Base("Date") {
    memcpy(&mTime,&ttime,sizeof(struct tm));
}

Date::Date(const char * fmt) : Base("Date") {
    mFmat = fmt;
    now();
}

std::string Date::now() {
    mNow  = time(0);
    struct tm * ptm = std::localtime(&mNow);

    memcpy(&mTime,ptm,sizeof(mTime));
    mDstr = toString();
    return mDstr;
}

std::ostream& operator<<(std::ostream& os, const Date & dt) {
    // ((Date&) dt).toString();
    os << dt.mDstr;

    return os;
}

/**
 * @brief  Read a date time object in from a stream (such as a text file)
 * @note   http://www.cplusplus.com/reference/ctime/strftime/
 * @param  is: Input Stream
 * @param  dt: Date tinme object
 * @retval Continuance of the imput stream passed into the function.
 */
std::istream& operator>>(std::istream& is, Date & dt) {
    char sep;

    int year,month,day,h,m,s = 0;

    // if(is >> dt.dayName >> dt.month >> dt.dayNum >> dt.h >> sep >> dt.m >> sep >> dt.s >> dt.year) {
    if(is >> year >> sep >> month >> sep >> day >> h >> sep >> m >> sep >> s ) {
        // struct tm breakdown = {0};
        dt.mTime.tm_year = year - 1900; /* years since 1900 */
        dt.mTime.tm_mon = month;
        dt.mTime.tm_mday = day;
        dt.mTime.tm_hour = h;
        dt.mTime.tm_min = m;
        dt.mTime.tm_sec = s;

        dt.mNow = mktime(&dt.mTime);
        // dt.mDstr = ctime(&dt.mNow);

        dt.toString();
        // Remove the carage return
        // dt.mDstr[dt.mDstr.length()-1] = ' ';
    }

    return is;
}

void Date::operator=(Date & date) {
    this->assign(date);
}

void Date::assign(Date & date) {
    mFmat  = date.mFmat;
    mDstr  = date.mDstr;
    memcpy(&mTime,&date.mTime,sizeof(mTime));
    memcpy(&mNow,&date.mNow,sizeof(mNow));
}

void Date::assign(std::string& str) {
    int year,month,day,h,m,s = 0;
    if(sscanf("%d-%d-%d %d:%d:%d", str.c_str(), &year,&month,&day,&h,&m,&s) == 6) {
        std::cout << "Assigning from [string " << str << "]" << std::endl;
        std::cout << std::setfill('0') << std::setw(4);
        std::cout << "Read in [" << (year - 1900) << "-" << std::setw(2) << month << "-" << day << "- " << h << ":" << m << ":" << s << "]" << std::endl;

        memset(&mTime,0,sizeof(mTime));

        mTime.tm_year = year - 1900;
        mTime.tm_mon  = month;
        mTime.tm_mday = day;
        mTime.tm_hour = h;
        mTime.tm_min  = m;
        mTime.tm_sec  = s;

        mNow = mktime(&mTime);
    }
}

const char * Date::toString() {
    char buffer[32] = {0};

    std::strftime(buffer, 32, mFmat.c_str(), &(mTime));
    std::cout << "Date::toString [buffer " << buffer << " / ";
    std::cout << "mFmat " << mFmat << " / ";
    std::cout << std::endl;

    mDstr = buffer;
    return mDstr.c_str();
}

unsigned int Date::getMonthNum(std::string & mon) {
    if(mon == "Jan") return 1;
    if(mon == "Feb") return 2;
    if(mon == "Mar") return 3;
    if(mon == "Apr") return 4;
    if(mon == "May") return 5;
    if(mon == "Jun") return 6;
    if(mon == "Jul") return 7;
    if(mon == "Aug") return 8;
    if(mon == "Sep") return 9;
    if(mon == "Oct") return 10;
    if(mon == "Nov") return 11;
    if(mon == "Dec") return 12;

    // Bit of a sticky wicket here if this fails,
    // but we syill need a valid fail state!
    return 15;
}

