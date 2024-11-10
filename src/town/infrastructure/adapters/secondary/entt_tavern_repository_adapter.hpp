//
// Created by Patryk Szczypień on 10/11/2024.
//

#ifndef INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP
#define INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP

#include <town/domain/ports/secondary/tavern_repository.hpp>
#include <town/domain/entities/tavern.hpp>

class EnttTavernRepositoryAdapter : public ITavernRepository {
public:
    explicit EnttTavernRepositoryAdapter(entt::registry &registry) : _registry{registry}, _tavern{registry.create()} {
        _registry.emplace<Gold>(_tavern.id(), BigNum(0.0));
        _registry.emplace<Generator<Resource::Gold>>(_tavern.id(), 4.0f, 1.07f, 1.67f, 1.0f);
    }

    void sell_food() override {
        auto current_gold = get_gold_amount().value;
        current_gold = current_gold.add(_gold_generator().production_rate());
        _registry.emplace_or_replace<Gold>(_tavern.id(), current_gold);
    }

    void increase_food_capacity() override {
        auto gold_generator = _gold_generator();
        if (gold_generator.amount() == 0) {
            gold_generator.add();
        }
        auto current_gold = get_gold_amount().value;
        if (current_gold.compare(gold_generator.next_cost()) >= 0) {
            current_gold = current_gold.subtract(gold_generator.next_cost());
            _registry.emplace_or_replace<Gold>(_tavern.id(), current_gold);
            gold_generator.add();
        }
        _registry.emplace_or_replace<Generator<Resource::Gold>>(_tavern.id(), gold_generator);
    }

    Gold get_gold_amount() override {
        return _registry.get<Gold>(_tavern.id());
    }

private:
    [[nodiscard]] Generator<Resource::Gold> _gold_generator() const {
        return _registry.get<Generator<Resource::Gold>>(_tavern.id());
    }

    entt::registry &_registry;
    Tavern<entt::entity> _tavern;
};

#endif //INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP
