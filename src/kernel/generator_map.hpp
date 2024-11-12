//
// Created by Patryk Szczypień on 12/11/2024.
//

#ifndef INCREMENTAL_CLICKER_GENERATOR_MAP_HPP
#define INCREMENTAL_CLICKER_GENERATOR_MAP_HPP

#include <unordered_map>

class GeneratorMap {
public:
    explicit GeneratorMap(std::unordered_map<Resource, Generator> &&values): values {std::move(values)} {};
    std::unordered_map<Resource, Generator> values;
};
#endif //INCREMENTAL_CLICKER_GENERATOR_MAP_HPP
