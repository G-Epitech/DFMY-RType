target_sources(${CLIENT_CORE_LIB} PRIVATE
        background.cpp
        background.hpp
#[[        player.hpp
        player.cpp]]
)
add_subdirectory(game)
