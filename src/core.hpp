//
// Created by Patryk Szczypień on 08/11/2024.
//

#ifndef INCREMENTAL_CLICKER_CORE_HPP
#define INCREMENTAL_CLICKER_CORE_HPP
#include <entt/entt.hpp>

class Core {
public:
    entt::scheduler scheduler;
    entt::registry registry;
    entt::dispatcher dispatcher;
};
#endif //INCREMENTAL_CLICKER_CORE_HPP
