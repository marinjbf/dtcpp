#pragma once 
#include <dtcpp/Calendars/Interface.hpp>

namespace dtcpp {

    class NoHolidayCalendar final: public BusinessCalendar {

        public:
            NoHolidayCalendar(){};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {return true;}; 
    };

}