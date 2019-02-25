cmake_minimum_required(VERSION 3.3)
project(reversi CXX)
include(.eecs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        src/player.cpp
        src/move.cpp
        src/board.cpp
        src/model.cpp)

add_program(reversi
        src/reversi.cpp
        src/controller.cpp
        src/view.cpp
        ${MODEL_SRC})
target_link_libraries(reversi ge211)

add_test_program(model_test
        test/model_test.cpp
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

add_test_program(helper_test
        test/player_test.cpp
        test/move_test.cpp
        test/board_test.cpp
        ${MODEL_SRC})
target_link_libraries(helper_test ge211)
