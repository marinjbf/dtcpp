#pragma once 
#include <dtcpp/Calendars/Interface.hpp>

namespace dtcpp {

    class WeekEndOffCalendar final: public BusinessCalendar {

        public:
            WeekEndOffCalendar(){};
            virtual bool isBusinessDay(const DateTime& referenceDate) const {
                std::tuple<int,int,int,int,int,int> civilTime_ = referenceDate.civilTime();
                int wk = toolbox::getWeekDayFromCivilDate(std::get<0>(civilTime_),std::get<1>(civilTime_),std::get<2>(civilTime_)); 
                return (wk==6 or wk==0) ? false : true;
            }; 
    };

}