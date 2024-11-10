//
// Created by Patryk Szczypień on 09/11/2024.
//

#ifndef INCREMENTAL_CLICKER_TAVERN_HPP
#define INCREMENTAL_CLICKER_TAVERN_HPP

template<typename ID>
class Tavern {
public:
    explicit Tavern(ID id) : _id{id} {};

    ID id() const { return _id; }

private:
    ID _id;
};

#endif //INCREMENTAL_CLICKER_TAVERN_HPP
