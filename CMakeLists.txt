cmake_minimum_required(VERSION 3.8)

# [ Project Setting ]
## Common
project(util_fpgasoc VERSION 1.0.1 LANGUAGES CXX)

## Options

# [ External libraries ]
## Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS program_options)

## libfpgasoc
find_package(fpgasoc 1.0.1)

# [ For building this projects ]
add_executable(util_fpgasoc)
target_sources(util_fpgasoc 
	PRIVATE
	fpgasoc.cpp
	fpgasoc_cmd.cpp
)
set_target_properties(util_fpgasoc PROPERTIES OUTPUT_NAME fpgasoc)

target_include_directories(util_fpgasoc PRIVATE .)
target_link_libraries(util_fpgasoc PRIVATE fpgasoc::fpgasoc ${Boost_LIBRARIES})
target_compile_options(util_fpgasoc PRIVATE -Wall)
target_compile_features(util_fpgasoc PRIVATE cxx_std_11)

# [ Subdirectories ]
add_subdirectory(cmd_read)
add_subdirectory(cmd_write)

# [ Installation ]
include(GNUInstallDirs)

install(TARGETS util_fpgasoc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts/ DESTINATION ${CMAKE_INSTALL_BINDIR})

