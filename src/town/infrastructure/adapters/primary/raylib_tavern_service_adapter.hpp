//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_RAYLIB_TAVERN_SERVICE_ADAPTER_HPP
#define INCREMENTAL_CLICKER_RAYLIB_TAVERN_SERVICE_ADAPTER_HPP

#include "town/domain/ports/primary/tavern_service_port.hpp"

class RaylibTavernServiceAdapter {
public:
    explicit RaylibTavernServiceAdapter(ITavernService &tavern_service) : _tavern_service{tavern_service} {}

    void sell_food() {
        _tavern_service.sell_food();
    }

    void increase_food_price() {
        _tavern_service.increase_food_capacity();
    }

    void render_gold_amount() {
        DrawText(TextFormat("Gold: %s", _tavern_service.get_gold_amount().value.toString().c_str()), 100, 100, 50, YELLOW);
    }
private:
    ITavernService &_tavern_service;
};
#endif //INCREMENTAL_CLICKER_RAYLIB_TAVERN_SERVICE_ADAPTER_HPP
