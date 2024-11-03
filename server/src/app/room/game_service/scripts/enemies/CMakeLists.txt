target_sources(${SERVER_CORE_LIB} PRIVATE
        enemy_default_script.cpp
        enemy_default_script.hpp
        void_eater_script.cpp
        void_eater_script.hpp
)

add_subdirectory(movement)
