//
// Created by Patryk Szczypień on 10/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP
#define INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP

class ITavernRepository {
public:
    virtual ~ITavernRepository() = default;
    virtual void sell_food() = 0;
    virtual void increase_food_capacity() = 0;
    virtual Gold get_gold_amount() = 0;
};
#endif //INCREMENTAL_CLICKER_TAVERN_REPOSITORY_HPP
