target_sources(${SERVER_CORE_LIB} PRIVATE
        options.cpp
        options.hpp
)

add_subdirectory(args)
add_subdirectory(handlers)
