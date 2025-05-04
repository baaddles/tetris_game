cmake_minimum_required(VERSION 3.10.0)
project(code-tetris-c-base VERSION 0.1.0 LANGUAGES C)

list(APPEND APP_SRCS  ${CMAKE_CURRENT_LIST_DIR}/main.c
                      ${CMAKE_CURRENT_LIST_DIR}/Tetris/tetris.c
                      ${CMAKE_CURRENT_LIST_DIR}/Tetris/tetrimino.c
)

list(APPEND APP_INCS  ${CMAKE_CURRENT_LIST_DIR}
                      ${CMAKE_CURRENT_LIST_DIR}/Tetris
)

add_executable(${PROJECT_NAME} ${APP_SRCS})
include_directories(${APP_INCS})

target_link_libraries(${PROJECT_NAME} ncurses)