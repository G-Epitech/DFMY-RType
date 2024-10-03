# External dependencies
find_package(Boost REQUIRED COMPONENTS system)

IF(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

target_link_libraries(abra PUBLIC Boost::system)