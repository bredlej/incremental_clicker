//
// Created by Patryk Szczypień on 08/11/2024.
//

#ifndef INCREMENTAL_CLICKER_GENERATOR_HPP
#define INCREMENTAL_CLICKER_GENERATOR_HPP

#include <cstdint>
#include <math.h>
#include <unordered_map>
#include <kernel/bignum.hpp>

enum class Resource :uint8_t {
    Gold
};

struct ResourceMap {
    std::unordered_map<uint8_t, BigNum> values;
};


template<Resource RESOURCE>
class Generator {
public:
    Generator(BigNum cost, double growth_coefficient, double productivity, double production_multipliers) : _cost{cost},
                                                                                                            _growth_coefficient{
                                                                                                                    growth_coefficient},
                                                                                                            _amount_owned{
                                                                                                                    0},
                                                                                                            _productivity{
                                                                                                                    productivity},
                                                                                                            _production_multipliers{
                                                                                                                    production_multipliers} {}

    void add() {
        _amount_owned += 1;
    }

    uint32_t amount() const { return _amount_owned; }

    BigNum next_cost() const {
        return _cost.multiply(std::pow(_growth_coefficient, _amount_owned));
    }

    double production_rate() const {
        return (_productivity * _amount_owned) * _production_multipliers;
    }

private:
    BigNum _cost;
    double _growth_coefficient;
    uint32_t _amount_owned;
    double _productivity;
    double _production_multipliers;
};

#endif //INCREMENTAL_CLICKER_GENERATOR_HPP
