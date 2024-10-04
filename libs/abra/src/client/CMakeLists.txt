target_sources(abra PRIVATE
        interface_client.hpp
        client_tcp.cpp
        client_tcp.hpp
        client_tcp.tpp
        client_udp.cpp
        client_udp.hpp
        client_udp.tpp
)

add_subdirectory(props)
