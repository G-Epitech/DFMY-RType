target_sources(${GAME_SDK} PRIVATE
        server.cpp
        server.hpp
        server.tpp
)

#[[
add_subdirectory(master)
]]
add_subdirectory(node)
#[[
add_subdirectory(room)
]]
