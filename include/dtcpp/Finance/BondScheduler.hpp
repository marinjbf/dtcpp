#pragma once 
#include <dtcpp/TimeSequence.hpp>
#include <dtcpp/Finance/Tenor.hpp>
#include <dtcpp/Calendars/Interface.hpp>

namespace dtcpp::fin {

    class BondScheduler: public TimeSequence {

        public: 
            BondScheduler(
                DateTime startDate_, 
                Tenor frequencyTenor_, 
                Tenor maturityTenor_,
                BusinessDayConvention businessDayConvention_,
                const BusinessCalendar& businessCalendar_): 
            TimeSequence(), _startDate(std::move(startDate_)) {

                int n = maturityTenor_.getMultiple(frequencyTenor_); 

                for (int i = 0; i<n-1; i++) {

                    DateTime unadjustedDate = frequencyTenor_.getForwardDate(_startDate, i+1);
                    insert(businessCalendar_.adjustForBusiness(unadjustedDate, businessDayConvention_));
                }

                _maturityDate = businessCalendar_.adjustForBusiness(maturityTenor_.getForwardDate(_startDate, 1), businessDayConvention_);
            }

            DateTime maturityDate() const {return _maturityDate;}

            DateTime startDate() const {return _startDate;}

        private:
            DateTime _startDate; 
            DateTime _maturityDate;

    };

}