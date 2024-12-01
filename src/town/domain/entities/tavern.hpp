//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_HPP
#define INCREMENTAL_CLICKER_TAVERN_HPP

#include <kernel/enums.hpp>
#include <kernel/generator.hpp>
#include <kernel/automated_production.hpp>

template<typename ID>
class Tavern {
    using FoodSales = Generator;
    using FoodHelper = AutomatedProduction;
public:
    constexpr explicit Tavern(ID id) : _id{id} {};

    constexpr ID id() const { return _id; }

    [[nodiscard]] constexpr static FoodSales food_sales() {
        return {Resource::Gold, 4.0f, 1.07f, 1.67f, 1.0f};
    };

    [[nodiscard]] constexpr static FoodHelper food_helper() {
        return {600};
    };
private:
    ID _id;
};

#endif //INCREMENTAL_CLICKER_TAVERN_HPP
