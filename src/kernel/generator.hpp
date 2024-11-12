//
// Created by Patryk Szczypień on 08/11/2024.
//

#ifndef INCREMENTAL_CLICKER_GENERATOR_HPP
#define INCREMENTAL_CLICKER_GENERATOR_HPP

#include <cstdint>
#include <cmath>
#include <unordered_map>
#include <kernel/bignum.hpp>
#include <kernel/enums.hpp>


struct Amount {
    uint32_t value;
};

struct GrowthCoefficient {
    double value;
};

struct Productivity {
    double value;
};

struct ProductionMultiplier {
    double value;
};

class Generator {
public:
    constexpr Generator() = default;
    constexpr Generator(Generator const &generator) = default;
    constexpr Generator(Generator &) = default;
    constexpr Generator(Resource product, BigNumber cost, double growth_coefficient, double productivity,
              double production_multipliers) : _product{product}, _cost{cost},
                                               _growth_coefficient{
                                                       growth_coefficient},
                                               _amount_owned{
                                                       0},
                                               _productivity{
                                                       productivity},
                                               _production_multiplier{
                                                       production_multipliers} {}

    constexpr void add() {
        _amount_owned.value += 1;
    }

    constexpr Resource produces() const { return _product; }

    [[nodiscard]] constexpr Amount amount() const { return _amount_owned; }

    [[nodiscard]] constexpr BigNumber next_cost() const {
        return _cost.multiply(std::pow(_growth_coefficient.value, _amount_owned.value));
    }

    constexpr double production_rate() const {
        return (_productivity.value * _amount_owned.value) * _production_multiplier.value;
    }

private:
    Resource _product;
    BigNumber _cost;
    GrowthCoefficient _growth_coefficient;
    Amount _amount_owned;
    Productivity _productivity;
    ProductionMultiplier _production_multiplier;
};

#endif //INCREMENTAL_CLICKER_GENERATOR_HPP
