target_sources(${CLIENT_CORE_LIB} PRIVATE
        menu.hpp
        menu.cpp
        game.hpp
        game.cpp
        settings.hpp
        settings.cpp
        lobby.cpp
        lobby.hpp
        leaderboard.cpp
        leaderboard.hpp
)

add_subdirectory(utils)
