target_sources(abra PRIVATE
        interface_client.cpp
        interface_client.hpp
        client_tcp.cpp
        client_tcp.hpp
)

add_subdirectory(props)
