cmake_minimum_required(VERSION 3.23)
project(core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GameMath REQUIRED)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${GAME_MATH_INCLUDE_DIRS})

add_executable(core Main.cpp Actor.cpp Actor.h Component.cpp Component.h Game.cpp Game.h SpriteComponent.cpp SpriteComponent.h AnimSpriteComponent.cpp AnimSpriteComponent.h BGSpriteComponent.cpp BGSpriteComponent.h Ship.cpp Ship.h MoveComponent.cpp MoveComponent.h Asteroid.cpp InputComponent.cpp InputComponent.h SpaceShip.cpp SpaceShip.h CircleComponent.cpp CircleComponent.h Laser.cpp Laser.h AIState.h AIComponent.cpp AIComponent.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${GAME_MATH_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} core_lib)
add_subdirectory(tests)