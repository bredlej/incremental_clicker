//
// Created by Patryk Szczypień on 12/11/2024.
//

#ifndef INCREMENTAL_CLICKER_HELPER_HPP
#define INCREMENTAL_CLICKER_HELPER_HPP

#include <cstdint>
#include <unordered_map>

struct AutomatedProduction {
    uint32_t invokes_every_ms;
    uint32_t time_since_last{0};
};


#endif //INCREMENTAL_CLICKER_HELPER_HPP
