target_sources(${CLIENT_CORE_LIB} PRIVATE
        blink.hpp
        blink.cpp
)
add_subdirectory(game)
add_subdirectory(leaderboard)
add_subdirectory(utils)
add_subdirectory(register)
