//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP
#define INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP

#include <town/domain/valueobjects/gold.hpp>

class ITavernService {
public:
    virtual ~ITavernService() = default;
    virtual void sell_food() = 0;
    virtual void increase_food_capacity() = 0;
    [[nodiscard]] virtual Gold get_gold_amount() const = 0;
};

#endif //INCREMENTAL_CLICKER_TAVERN_SERVICE_PORT_HPP
