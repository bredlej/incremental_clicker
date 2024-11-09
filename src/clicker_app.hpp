//
// Created by Patryk Szczypień on 07/11/2024.
//

#ifndef INCREMENTAL_CLICKER_CLICKER_APP_HPP
#define INCREMENTAL_CLICKER_CLICKER_APP_HPP

#include <cstdio>
#include <raylib_context.hpp>
#include <core.hpp>
#include <unordered_map>
#include <generator.hpp>

class ClickerApp {
public:
    static void run();
private:
    Core _core;
};
#endif //INCREMENTAL_CLICKER_CLICKER_APP_HPP
