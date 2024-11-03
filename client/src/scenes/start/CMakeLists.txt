target_sources(${CLIENT_CORE_LIB} PRIVATE
        start.hpp
        start.cpp
        create_room.cpp
        create_room.hpp
)

add_subdirectory(entities)
