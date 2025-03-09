cmake_minimum_required(VERSION 3.5.0)
project(xpick)

include(FindPkgConfig)
pkg_check_modules(
    XCB_LIBS
        xcb
    REQUIRED
)

if(WITH_DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")
endif()

add_executable(
    xpick
        demo/demo.c
        src/xpick.c
)

target_include_directories(
    xpick
    PRIVATE
        src/
)

target_link_libraries(
    xpick
        xcb
)

install(
    TARGETS
        xpick
    DESTINATION
        bin
)
