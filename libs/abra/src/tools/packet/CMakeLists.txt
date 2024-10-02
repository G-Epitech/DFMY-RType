add_subdirectory(props)

target_sources(abra PRIVATE
        packet.cpp
        packet.hpp
        packet.tpp
        packet_builder.cpp
        packet_builder.hpp
        packet_builder.tpp
        packet_utils.cpp
        packet_utils.hpp
)
