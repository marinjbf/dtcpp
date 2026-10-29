add_library(dtcpp 
    STATIC
        src/DatetimeConstructors.cpp
        src/DatetimeOperators.cpp
        src/DatetimeFunctions.cpp
)

target_include_directories(dtcpp PUBLIC include)