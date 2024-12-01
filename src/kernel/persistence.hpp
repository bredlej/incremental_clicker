//
// Created by Patryk Szczypień on 13/11/2024.
//

#ifndef INCREMENTAL_CLICKER_PERSISTENCE_HPP
#define INCREMENTAL_CLICKER_PERSISTENCE_HPP
#include <core.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include "kernel/generator.hpp"
#include <town/infrastructure/adapters/secondary/entt_tavern_repository_adapter.hpp>
#include <chrono>

class Persistence {
public:
    explicit Persistence(Core &core, EnttTavernRepositoryAdapter &tavern_repository) : _core{core}, _repository{tavern_repository} {};
    void save_state() {
        nlohmann::json json_components;
        _core.registry.view<GeneratorMap>().each([&json_components](auto entity, const GeneratorMap &generator) {
            generator.values.at(Resource::Food).to_json(json_components["Generator"]["Food"]);
        });
        _core.registry.view<std::unordered_map<Resource, AutomatedProduction>>().each([&json_components](auto entity, const std::unordered_map<Resource, AutomatedProduction> &apm) {
            if(apm.contains(Resource::Food)) {
                json_components["AutomatedProduction"]["Food"]["invokes_every_ms"] = apm.at(Resource::Food).invokes_every_ms;
            }
        });
        auto now = std::chrono::system_clock::now();
        json_components["Time"] = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        json_components["Gold"]["value"] = _repository.get_gold_amount().value.persistence().value;
        json_components["Gold"]["exp"] = _repository.get_gold_amount().value.persistence().exp;
        std::ofstream file("clicker_app.json");
        if (file.is_open()) {
            file << json_components.dump(4); // Pretty print with 4 spaces
            file.close();
        }
    }
    void restore_state() {
        std::ifstream file("clicker_app.json");
        if (!file.is_open()) return;

        nlohmann::json json_components;
        file >> json_components;

        Generator g{};
        g.from_json(json_components["Generator"]["Food"]);
        auto &rep = _repository.get_generator_map().values;

        rep[Resource::Food] = g;

        if (!json_components["AutomatedProduction"]["Food"].empty()) {
            _repository.hire_food_helper(json_components["AutomatedProduction"]["Food"]["invokes_every_ms"].get<uint32_t>());
        }

        if (!json_components["Gold"].empty()) {
            _repository.set_gold(Gold{BigNumber{json_components["Gold"]["value"], json_components["Gold"]["exp"]}});
        }


        if (!json_components["Time"].empty()) {
            long long saved_time = json_components["Time"];
            auto now = std::chrono::system_clock::now();
            auto current_time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

            auto &automated_production = _repository.get_automated_production_map();
            for (auto &[k,v] : automated_production) {
                v.time_since_last = current_time-saved_time;
            }
            std::printf("Time elapsed %lld.", current_time-saved_time);
        }
    }
private:
    Core &_core;
    EnttTavernRepositoryAdapter &_repository;
};
#endif //INCREMENTAL_CLICKER_PERSISTENCE_HPP
