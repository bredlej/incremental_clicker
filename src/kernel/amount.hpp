//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_AMOUNT_HPP
#define INCREMENTAL_CLICKER_AMOUNT_HPP

#include <vector>
#include <cstdint>

class Amount {
public:

private:
    std::vector<uint32_t> _thousands;
    uint32_t _value;
    uint32_t _index;
};
#endif //INCREMENTAL_CLICKER_AMOUNT_HPP
