#include <cassert>
#include <dtcpp/Finance/BondScheduler.hpp>
#include <dtcpp/Calendars/NoHoliday.hpp>

int main() {


    using namespace dtcpp::fin; 
    using namespace dtcpp; 
    Tenor tenorFreq{3,TenorType::MONTHS};
    Tenor tenorMaturity{5,TenorType::YEARS};
    dtcpp::DateTime startDate(2026,1,30);
    NoHolidayCalendar hcal = NoHolidayCalendar(); 
    dtcpp::BusinessDayConvention bdconv = dtcpp::BusinessDayConvention::FOLLOWING; 

    dtcpp::fin::BondScheduler schedule(startDate,tenorFreq,tenorMaturity, bdconv, hcal);
    assert(schedule.size() == 19);
    assert(schedule[7] == DateTime(2028,1,30)); 
    assert(schedule[12] == DateTime(2029,4,30));
    assert(schedule[13] == DateTime(2029,7,30));
    assert(schedule.startDate() == startDate); 
    assert(schedule.maturityDate() == DateTime(2031,1,30));

    tenorFreq = {7,TenorType::MONTHS};

    schedule = dtcpp::fin::BondScheduler(startDate,tenorFreq,tenorMaturity, bdconv, hcal);
    assert(schedule.size() == 0);

    return 0;
}