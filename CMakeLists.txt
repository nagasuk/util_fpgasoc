cmake_minimum_required(VERSION 3.8)

# [ Project Setting ]
## Common
project(util_fpgasoc CXX)

## Options

# [ External libraries ]
## Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

# [ For building this projects ]
add_executable(util_fpgasoc)
target_sources(util_fpgasoc 
	PRIVATE
	fpgasoc.cpp
	fpgasoc_cmd.cpp
)
set_target_properties(util_fpgasoc PROPERTIES OUTPUT_NAME fpgasoc)

target_include_directories(util_fpgasoc PRIVATE .)
target_link_libraries(util_fpgasoc PRIVATE fpgasoc ${Boost_LIBRARIES})
target_compile_options(util_fpgasoc PRIVATE -Wall)
target_compile_features(util_fpgasoc PRIVATE cxx_std_11)

# [ Subdirectories ]
add_subdirectory(cmd_read)
add_subdirectory(cmd_write)

# [ Installation ]
install(TARGETS util_fpgasoc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

