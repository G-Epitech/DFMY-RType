add_subdirectory(props)

target_sources(r-type_network_sdk PRIVATE
        packet.cpp
        packet.hpp
        packet.tpp
        packet_builder.cpp
        packet_builder.hpp
        packet_builder.tpp
)
