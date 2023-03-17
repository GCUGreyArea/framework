// ==================================================================
// Date.h
//
// NOTE:
// ==================================================================
#ifndef __DATE_CLASS__
#define __DATE_CLASS__

#include <iostream>
#include <ostream>
#include <ctime>

#include "Base.h"


class Date : public Base {
    public:
        constexpr static const char * DATE_NUM_FMAT = "%Y-%m-%d %H:%M:%S";
        constexpr static const char * DATE_NAM_FMAT = "%Y-%b-%d %H:%M:%S";

        Date();
        Date(time_t& dt);
        Date(struct tm& ttime);
        Date(Date& date);
        Date(const char * fmt);

        friend std::ostream& operator<<(std::ostream& os, const Date& dt);
        friend std::istream& operator>>(std::istream & is, Date & dt);

        void operator=(Date & date);
        bool operator> (const Date& lhs) {return mNow > lhs.mNow;}

        void assign(Date& date);
        void assign(std::string& str);

        std::string now();
        const char * toString();
        // bool fromString(std::string& str);

        static unsigned int getMonthNum(std::string & month);

    private:
        time_t mNow;
        struct tm mTime;
        std::string mFmat;
        std::string mDstr;
};

#endif//__DATE_CLASS__

