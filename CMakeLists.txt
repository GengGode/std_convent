cmake_minimum_required(VERSION 3.15)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(BUILD_TEST OFF CACHE BOOL "Build test")

set(BUILD_TEST ON)

project(std_convert)

add_library(std_convert INTERFACE include/std_convert.h)
target_include_directories(std_convert INTERFACE include)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

install(TARGETS std_convert
        EXPORT std_convert
        INCLUDES DESTINATION include
        )

set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
set(CMAKE_INSTALL_INCLUDEDIR include CACHE PATH "Output directory for headers")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/std_convert-config-version.cmake
        VERSION 1.0.0
        COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/std_convert-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/std_convert-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/std_convert
)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/std_convert-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/std_convert-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/std_convert
        )
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

