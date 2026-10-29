include(CTest)

set(TESTS

    dtcpp-tests-toolbox tests/ToolBox.cpp
    dtcpp-tests-timedelta tests/TimeDelta.cpp
    dtcpp-tests-datetime tests/Datetime.cpp
    dtcpp-tests-sequence tests/TimeSequence.cpp
    dtcpp-tests-timeserie tests/TimeSerie.cpp
    dtcpp-tests-calendars-noholiday tests/Calendars/NoHoliday.cpp
    dtcpp-tests-calendars-wkoff tests/Calendars/WeekEndOff.cpp
    dtcpp-tests-calendars-usfed tests/Calendars/USFederalReserve.cpp
    dtcpp-tests-finance-tenor tests/Finance/Tenor.cpp
    dtcpp-tests-finance-daycount tests/Finance/DayCount.cpp
    dtcpp-tests-finance-bondscheduler tests/Finance/BondScheduler.cpp

)

while(TESTS)
    list(POP_FRONT TESTS test_name test_file)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE dtcpp)

    add_test(NAME ${test_name} COMMAND ${test_name})
endwhile()