target_sources(${CLIENT_CORE_LIB} PRIVATE
        drawable.hpp
        drawable.cpp
)
add_subdirectory(events)
add_subdirectory(game)
