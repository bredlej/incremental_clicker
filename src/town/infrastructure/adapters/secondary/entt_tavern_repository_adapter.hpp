//
// Created by Patryk Szczypień on 10/11/2024.
//

#ifndef INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP
#define INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP

#include <kernel/enums.hpp>
#include <kernel/automated_production.hpp>
#include <town/domain/ports/secondary/tavern_repository.hpp>
#include <town/domain/entities/tavern.hpp>
#include <cstdint>

class EnttTavernRepositoryAdapter : public ITavernRepository {
    using AutomatedProductionMap = std::unordered_map<Resource, AutomatedProduction>;
public:
    explicit EnttTavernRepositoryAdapter(Core &core) : _core{core}, _tavern{_core.registry.create()} {
        _core.registry.emplace<Gold>(_tavern.id(), BigNumber(0.0));

        GeneratorMap gm{std::unordered_map<Resource, Generator>{{Resource::Food, _tavern.food_sales()}}};
        _core.registry.emplace<GeneratorMap>(_tavern.id(), gm);

        AutomatedProductionMap apm{std::unordered_map<Resource, AutomatedProduction>{}};
        _core.registry.emplace<AutomatedProductionMap>(_tavern.id(), apm);
    }

    void sell_food() const override {
        auto current_gold = get_gold_amount().value;
        current_gold = current_gold.add(_food_sales_generator().production_rate());
        _core.registry.emplace_or_replace<Gold>(_tavern.id(), current_gold);
    }

    void increase_food_sales() const override {
        auto gold_generator = _food_sales_generator();
        if (gold_generator.amount().value == 0) {
            gold_generator.add();
        }
        auto current_gold = get_gold_amount().value;
        if (current_gold.compare(gold_generator.next_cost()) >= 0) {
            current_gold = current_gold.subtract(gold_generator.next_cost());
            _core.registry.emplace_or_replace<Gold>(_tavern.id(), current_gold);
            gold_generator.add();
        }
        GeneratorMap &gm = _core.registry.get<GeneratorMap>(_tavern.id());
        gm.values[Resource::Food] = gold_generator;
    }

    void hire_food_helper(const std::function<void()> &func) const override {
        auto &apm = _core.registry.get<AutomatedProductionMap>(_tavern.id());
        if (!apm.contains(Resource::Food)) {
            apm[Resource::Food] = {600, 0};
            _core.scheduler.attach([this, &func](auto delta, void *, auto succeed, auto fail) {
                auto &automated_production = _core.registry.get<AutomatedProductionMap>(_tavern.id())[Resource::Food];
                automated_production.time_since_last += delta;
                if (automated_production.time_since_last > automated_production.invokes_every_ms) {
                    sell_food();
                    automated_production.time_since_last -= automated_production.invokes_every_ms;
                }
            });
        }
    }

    [[nodiscard]] Amount amount_food_sales_generators() const override {
        return _food_sales_generator().amount();
    }

    Gold cost_of_next_food_sales_generator() const override {
        return amount_food_sales_generators().value == 0 ? Gold{0.0} : Gold{_food_sales_generator().next_cost()};
    }

    [[nodiscard]] Gold get_gold_amount() const override {
        return _core.registry.get<Gold>(_tavern.id());
    }

private:
    [[nodiscard]] Generator _food_sales_generator() const {
        return _core.registry.get<GeneratorMap>(_tavern.id()).values.at(Resource::Food);
    }

    Core &_core;
    Tavern<entt::entity> _tavern;
};

#endif //INCREMENTAL_CLICKER_ENTT_TAVERN_REPOSITORY_ADAPTER_HPP
