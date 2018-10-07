cmake_minimum_required(VERSION 2.8.5)
project(pingus)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 7)
set(PROJECT_VERSION_PATCH 6)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")


file(GLOB sources
	external/tinygettext/tinygettext/*.cpp
	src/editor/*.cpp
	src/engine/display/*.cpp
	src/engine/display/delta/*.cpp
	src/engine/gui/*.cpp
	src/engine/input/*.cpp
	src/engine/resource/*.cpp
	src/engine/screen/*.cpp
	src/engine/sound/*.cpp
	src/engine/system/*.cpp
	src/lisp/*.cpp
	src/math/*.cpp
	src/pingus/*.cpp
	src/pingus/actions/*.cpp
	src/pingus/colliders/*.cpp
	src/pingus/components/*.cpp
	src/pingus/movers/*.cpp
	src/pingus/particles/*.cpp
	src/pingus/screens/*.cpp
	src/pingus/worldmap/*.cpp
	src/pingus/worldobjs/*.cpp
	src/util/*.cpp
	src/main.cpp
)
	
	
include_directories(src
	external
	external/tinygettext
	external/tinygettext/tinygettext
	src/editor
	src/engine/display
	src/engine/gui
	src/engine/input
	src/engine/resource
	src/engine/screen
	src/engine/sound
	src/engine/system
	src/lisp
	src/math
	src/pingus
	src/pingus/actions
	src/pingus/colliders
	src/pingus/components
	src/pingus/movers
	src/pingus/particles
	src/pingus/screens
	src/pingus/worldmap
	src/pingus/worldobjs
	src/util
)

add_executable(pingus ${sources})

target_compile_options(pingus PUBLIC -std=c++11 -DVERSION="${PROJECT_VERSION}")

find_package(PkgConfig)
pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(SDL_IMAGE REQUIRED SDL_image)
pkg_search_module(SDL_MIXER REQUIRED SDL_mixer)
pkg_search_module(PNG REQUIRED libpng)

find_package(Boost 1.56 REQUIRED COMPONENTS signals) 

target_include_directories(pingus SYSTEM PUBLIC
	${SDL_INCLUDE_DIRS}
	${SDL_IMAGE_INCLUDE_DIRS}
	${SDL_MIXER_INCLUDE_DIRS}
	${PNG_INCLUDE_DIRS}
	)
target_link_libraries(pingus
	${SDL_LIBRARIES}
	${SDL_IMAGE_LIBRARIES}
	${SDL_MIXER_LIBRARIES}
	${PNG_LIBRARIES}
)

target_link_libraries(pingus boost_signals)

install(TARGETS pingus DESTINATION bin)
install(DIRECTORY data/ DESTINATION share/pingus)
