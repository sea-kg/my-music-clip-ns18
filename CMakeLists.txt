cmake_minimum_required(VERSION 3.7)

project(my_clip_ns18)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

#### BEGIN_WSJCPP_APPEND
#### END_WSJCPP_APPEND

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${my_clip_ns18_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_INCLUDE_DIRS "src/game")
list (APPEND WSJCPP_INCLUDE_DIRS "src/render")

# source files
list (APPEND WSJCPP_SOURCES "src/main.cpp")
list (APPEND WSJCPP_SOURCES "src/main_controller.cpp")
list (APPEND WSJCPP_SOURCES "src/game/coordxy.cpp")
list (APPEND WSJCPP_SOURCES "src/game/game_state.cpp")
list (APPEND WSJCPP_SOURCES "src/game/state_ns18zoid.cpp")
list (APPEND WSJCPP_SOURCES "src/game/state_background.cpp")
list (APPEND WSJCPP_SOURCES "src/render/render.cpp")
list (APPEND WSJCPP_SOURCES "src/render/render_base.cpp")
list (APPEND WSJCPP_SOURCES "src/render/render_background.cpp")
list (APPEND WSJCPP_SOURCES "src/render/render_ns18zoid.cpp")
list (APPEND WSJCPP_SOURCES "src/render/render_window.cpp")


############################
# SDL2
find_package(SDL2 REQUIRED)
if ( SDL2_FOUND )
    list (APPEND WSJCPP_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
    list (APPEND WSJCPP_LIBRARIES ${SDL2_LIBRARIES})
endif( SDL2_FOUND )
############################


############################
# SDL2_image
find_package(SDL2_image REQUIRED)
if ( SDL2_image_FOUND )
    list (APPEND WSJCPP_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIRS})
    list (APPEND WSJCPP_LIBRARIES ${SDL2_IMAGE_LIBRARIES})
endif( SDL2_image_FOUND )
############################

############################
# SDL2_ttf
find_package(SDL2TTF REQUIRED)
if ( SDL2TTF_FOUND )
    list (APPEND WSJCPP_INCLUDE_DIRS ${SDL2TTF_INCLUDE_DIRS})
    list (APPEND WSJCPP_LIBRARIES ${SDL2TTF_LIBRARY})
endif( SDL2TTF_FOUND )
############################

############################
# SDL2_mixer
find_package(SDL2_mixer REQUIRED)
if ( SDL2_MIXER_FOUND )
    list (APPEND WSJCPP_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIRS})
    list (APPEND WSJCPP_LIBRARIES ${SDL2_MIXER_LIBRARY})
endif( SDL2_MIXER_FOUND )
############################

# include(FindPkgConfig)
# pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
# list (APPEND WSJCPP_LIBRARIES PkgConfig::SDL2_Mixer)

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (my_clip_ns18 ${WSJCPP_SOURCES})

target_link_libraries(my_clip_ns18 ${WSJCPP_LIBRARIES} )
