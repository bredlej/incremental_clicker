//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP
#define INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP

#include <town/domain/ports/primary/tavern_service_port.hpp>
#include <town/domain/ports/secondary/tavern_repository.hpp>
#include <cstdint>
class TavernService : public ITavernService {
public:
    explicit TavernService(ITavernRepository &repository)
            : repository(repository) {}

    void sell_food() const override {
        repository.sell_food();
    }

    void increase_food_sales() const override {
        repository.increase_food_sales();
    }

    void hire_food_helper() const override {
        repository.hire_food_helper();
    }

    Amount amount_gold_generators() const override {
        return repository.amount_food_sales_generators();
    }

    Gold cost_of_next_gold_generator() override {
        return repository.cost_of_next_food_sales_generator();
    }

    [[nodiscard]] Gold get_gold_amount() const override {
        return repository.get_gold_amount();
    }

private:
    ITavernRepository &repository;
};

#endif //INCREMENTAL_CLICKER_TAVERN_SERVICE_HPP
