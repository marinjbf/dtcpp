#pragma once 
#include <dtcpp/Datetime.hpp>
#include <dtcpp/ToolBox.hpp>

namespace dtcpp {

    enum class BusinessDayConvention {
        FOLLOWING, 
        PRECEDING, 
        MODIFIED_FOLLOWING, 
        MODIFIED_PRECEDING
    };

    class BusinessCalendar {

        public:
            BusinessCalendar(){};
            virtual ~BusinessCalendar() = default; 

            virtual bool isBusinessDay(const DateTime& referenceDate) const = 0; 

            DateTime adjustForBusiness(const DateTime& referenceDate, BusinessDayConvention businessDayConvention) const {

                DateTime result = referenceDate;
                switch (businessDayConvention) {
                    case BusinessDayConvention::FOLLOWING: return adjustDateFollowingConvention(referenceDate);
                    case BusinessDayConvention::PRECEDING: return adjustDatePrecedingConvention(referenceDate);
                    case BusinessDayConvention::MODIFIED_FOLLOWING: return adjustDateModifiedFollowingConvention(referenceDate);
                    case BusinessDayConvention::MODIFIED_PRECEDING: return adjustDateModifiedPrecedingConvention(referenceDate);
                }
                return result;
            }

        private:

            DateTime adjustDateFollowingConvention(const DateTime& referenceDate) const {

                DateTime newDate = referenceDate;
                while (!isBusinessDay(newDate)) { newDate += TimeDelta{1,0,0,0,0,0,0}; }
                return newDate;
            }

            DateTime adjustDatePrecedingConvention(const DateTime& referenceDate) const {

                DateTime newDate = referenceDate;
                while (!isBusinessDay(newDate)) { newDate -= TimeDelta{1,0,0,0,0,0,0}; }
                return newDate;
            }

            DateTime adjustDateModifiedPrecedingConvention(const DateTime& referenceDate) const {

                DateTime modPrec = adjustDatePrecedingConvention(referenceDate);
                std::tuple<int,int,int,int,int,int> civilTime_ = referenceDate.civilTime(); 
                std::tuple<int,int,int,int,int,int> civilTime2_ = modPrec.civilTime(); 
                if (std::get<1>(civilTime2_)== std::get<1>(civilTime_)) return modPrec; 
                else return adjustDateFollowingConvention(referenceDate);
            }

            DateTime adjustDateModifiedFollowingConvention(const DateTime& referenceDate) const {

                DateTime modFol = adjustDateFollowingConvention(referenceDate); 
                std::tuple<int,int,int,int,int,int> civilTime_ = referenceDate.civilTime(); 
                std::tuple<int,int,int,int,int,int> civilTime2_ = modFol.civilTime(); 
                if (std::get<1>(civilTime2_)== std::get<1>(civilTime_)) return modFol; 
                else return adjustDatePrecedingConvention(referenceDate);
            }
    };

}