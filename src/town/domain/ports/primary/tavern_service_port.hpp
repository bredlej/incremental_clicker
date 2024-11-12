//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP
#define INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP

#include <town/domain/valueobjects/gold.hpp>
#include "kernel/generator.hpp"

class ITavernService {
public:
    virtual ~ITavernService() = default;
    virtual void sell_food() const = 0;
    virtual void increase_food_sales() const = 0;
    virtual void hire_food_helper() const = 0;
    [[nodiscard]] virtual Amount amount_gold_generators() const = 0;
    [[nodiscard]] virtual Gold cost_of_next_gold_generator() = 0;
    [[nodiscard]] virtual Gold get_gold_amount() const = 0;
};

#endif //INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP
