add_subdirectory(props)

target_sources(r-type_network_sdk PUBLIC
        packet.cpp
        packet.hpp
        packet_builder.cpp
        packet_builder.hpp
)
