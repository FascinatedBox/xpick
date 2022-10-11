project(xpick)
cmake_minimum_required(VERSION 3.5.0)

if(WITH_DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")
endif()

include(FindPkgConfig)

pkg_check_modules(
    XCB_LIBS
        xcb
    REQUIRED
)

include_directories(src)

add_executable(
    xpick
        src/demo.c
        src/xpick.c
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
