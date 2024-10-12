target_sources(${CLIENT_CORE_LIB} PRIVATE
        drawable.hpp
        drawable.cpp
        background.cpp
        background.hpp
)
add_subdirectory(events)
add_subdirectory(game)
