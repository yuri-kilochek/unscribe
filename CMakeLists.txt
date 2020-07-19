cmake_minimum_required(VERSION 3.17)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS VERSION)
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROJECT_VERSION)
project(unscribe VERSION ${PROJECT_VERSION} LANGUAGES CXX)

include(GNUInstallDirs)
include(CTest)


add_library(unscribe INTERFACE)

set(VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(VERSION_PATCH ${PROJECT_VERSION_PATCH})
configure_file(include/unscribe/version.hpp.in 
               include/unscribe/version.hpp)

target_include_directories(unscribe INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)


if(BUILD_TESTING)
    add_subdirectory(tests)
endif()


target_include_directories(unscribe INTERFACE
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
              "${CMAKE_CURRENT_BINARY_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    PATTERN "*.in" EXCLUDE
)
install(TARGETS unscribe EXPORT unscribe)
install(EXPORT unscribe
    DESTINATION "${CMAKE_INSTALL_DATADIR}/unscribe"
    NAMESPACE unscribe::
    FILE unscribe-config.cmake
)
export(EXPORT unscribe
    NAMESPACE unscribe::
    FILE unscribe-config.cmake
)

