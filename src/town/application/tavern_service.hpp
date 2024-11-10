//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP
#define INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP

#include <town/domain/ports/primary/tavern_service_port.hpp>
#include <town/domain/ports/secondary/tavern_repository.hpp>

class TavernService : public ITavernService{
public:
    explicit TavernService(ITavernRepository& repository)
            : repository(repository) {}

    void sell_food() override {
        repository.sell_food();
    }

    void increase_food_capacity() override {
        repository.increase_food_capacity();
    }

    [[nodiscard]] Gold get_gold_amount() const override {
        return repository.get_gold_amount();
    }

private:
    ITavernRepository& repository;
};
#endif //INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP
