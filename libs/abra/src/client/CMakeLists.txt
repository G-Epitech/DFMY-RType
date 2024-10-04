target_sources(abra PRIVATE
        interface_client.hpp
)

add_subdirectory(tcp)
add_subdirectory(udp)
