//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_HPP
#define INCREMENTAL_CLICKER_TAVERN_HPP
#include <kernel/enums.hpp>
#include <kernel/generator.hpp>

template<typename ID>
class Tavern {
    using FoodSales = Generator;
public:
    constexpr explicit Tavern(ID id) : _id{id},
        _food_sales{Generator{Resource::Gold, 4.0f, 1.07f, 1.67f, 100000.0f}} {};

    constexpr ID id() const { return _id; }

    constexpr FoodSales food_sales() const { return _food_sales; };

private:
    ID _id;

    Gold _total_gold;
    FoodSales _food_sales;
};

#endif //INCREMENTAL_CLICKER_TAVERN_HPP
