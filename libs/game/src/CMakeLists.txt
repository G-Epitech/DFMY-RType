target_sources(${GAME_SDK} PUBLIC
        dummy.cpp
        core.hpp
)

add_subdirectory(api)
add_subdirectory(stats)
add_subdirectory(types)
add_subdirectory(utils)
add_subdirectory(components)
