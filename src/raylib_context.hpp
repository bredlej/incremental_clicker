//
// Created by Patryk Szczypień on 07/11/2024.
//

#ifndef INCREMENTAL_CLICKER_RAYLIB_CONTEXT_HPP
#define INCREMENTAL_CLICKER_RAYLIB_CONTEXT_HPP

extern "C" {
#include <raylib.h>
};

#include <functional>
#include <core.hpp>

class RaylibContext {
public:
    RaylibContext() : _window_width{1600}, _window_height{1200}, pre_loop_func {[](Core&){}}, loop_func {[](Core&){}}, post_loop_func{[](Core&){}} {}
    void run(Core&);
    std::function<void(Core&)> pre_loop_func;
    std::function<void(Core&)> loop_func;
    std::function<void(Core&)> post_loop_func;
private:
    int _window_width;
    int _window_height;
};
#endif //INCREMENTAL_CLICKER_RAYLIB_CONTEXT_HPP
