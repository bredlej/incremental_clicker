//
// Created by Patryk Szczypień on 10/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP
#define INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP

#include <town/domain/valueobjects/gold.hpp>
#include "kernel/generator.hpp"
#include "kernel/generator_map.hpp"
#include <functional>
#include <cstdint>

class ITavernRepository {
public:
    virtual ~ITavernRepository() = default;
    virtual void sell_food() const = 0;
    virtual void increase_food_sales() const = 0;
    virtual void hire_food_helper(const std::function<void()>&) const = 0;
    virtual Amount amount_food_sales_generators() const = 0;
    virtual Gold cost_of_next_food_sales_generator() const = 0;
    virtual Gold get_gold_amount() const = 0;
};
#endif //INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP
