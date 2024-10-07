target_sources(abra PRIVATE
        server_tcp.cpp
        server_tcp.hpp
        server_tcp.tpp
)

add_subdirectory(session)
add_subdirectory(props)
