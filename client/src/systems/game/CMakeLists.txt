target_sources(${CLIENT_CORE_LIB} PRIVATE
        sync.cpp
        sync.hpp
        player.hpp
        player.cpp
        background.cpp
        background.hpp
)

add_subdirectory(texture_mapper)
add_subdirectory(chat)
