target_sources(abra PRIVATE
        interface_client.hpp
        client_tcp.cpp
        client_tcp.hpp
        client_tcp.tpp
)

add_subdirectory(props)
