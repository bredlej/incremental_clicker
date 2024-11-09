//
// Created by Patryk Szczypień on 07/11/2024.
//
#include <raylib_context.hpp>

void RaylibContext::run(Core &core) {
    InitWindow(_window_width, _window_height, "Clicker");
    pre_loop_func(core);
    while (!WindowShouldClose()) {
        loop_func(core);
    }
    post_loop_func(core);
    CloseWindow();
}