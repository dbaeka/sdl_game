cmake_minimum_required(VERSION 3.23)
project(core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(core Main.cpp Actor.cpp Actor.h Math.cpp Math.h Component.cpp Component.h Game.cpp Game.h SpriteComponent.cpp SpriteComponent.h AnimSpriteComponent.cpp AnimSpriteComponent.h BGSpriteComponent.cpp BGSpriteComponent.h Ship.cpp Ship.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})