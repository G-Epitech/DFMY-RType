target_sources(${GAME_SDK} PUBLIC
        dummy.cpp
        core.hpp
)

add_subdirectory(api_common)
add_subdirectory(stats)
add_subdirectory(types)
add_subdirectory(utils)
