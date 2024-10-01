target_sources(${SERVER_CORE_LIB} PRIVATE
        cli.cpp
        cli.hpp
)

add_subdirectory(handlers)
