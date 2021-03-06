project(blox)

cmake_minimum_required(VERSION 2.8)

if (DEFINED CMAKE_INSTALL_PREFIX)
  add_definitions(-DGAME_HOME="${CMAKE_INSTALL_PREFIX}/share/games/blox")
endif(DEFINED CMAKE_INSTALL_PREFIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

file(GLOB pngs assets/*.png)
file(COPY ${pngs} DESTINATION "${CMAKE_BINARY_DIR}/assets")

file(COPY assets/GentiumPlus-I.ttf DESTINATION "${CMAKE_BINARY_DIR}/assets")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS}
  ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} src/include)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES}
  ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})
set (CMAKE_BUILD_TYPE Debug)

INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")
INSTALL(DIRECTORY "${CMAKE_BINARY_DIR}/assets" DESTINATION "share/games/blox")
