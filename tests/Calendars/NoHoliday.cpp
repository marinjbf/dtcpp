#include <cassert>
#include <dtcpp/Calendars/NoHoliday.hpp>

using namespace dtcpp;

void templateTestAdjBusinessDay(const BusinessCalendar& calendar, const BusinessDayConvention& bdc, const std::vector<int>& raw, const std::vector<int>& result) {

    for (int i = 0; i<result.size(); i++) {

        DateTime newDateTime = calendar.adjustForBusiness(DateTime(raw[i], EpochTimestampType::SECONDS), bdc);
        assert(newDateTime.timestamp() == result[i]*1'000'000'000LL);
    }
}

int main() {

    std::vector<int> raw = {
        1761868800, 1777507200, 1793318400, 1809043200, 1824854400,
        1840665600, 1856476800, 1872201600, 1888012800, 1903737600,
        1919548800, 1935273600, 1951084800, 1966896000, 1982707200,
        1998432000, 2014243200, 2029968000, 2045779200, 2061504000,
        2077315200
    };


    templateTestAdjBusinessDay(dtcpp::NoHolidayCalendar(), BusinessDayConvention::FOLLOWING, raw, raw); 
 

    return 0;
}