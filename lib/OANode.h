#pragma once

#include <iostream>

enum states {
    free_ = 'f',
    busy_ = 'b',
    deleted_ = 'd'
};

template<typename T>
class OANode {
public:

    OANode() {
        state = free_;
    }

    [[nodiscard]] const unsigned long long &getKey() const {
        return key;
    }

    void setKey(const unsigned long long &key_) {
        key = key_;
    }

    T getValue() const {
        return value;
    }

    void setValue(T value_) {
        value = value_;
    }

    [[nodiscard]] states getState() const {
        return state;
    }

    void setState(states state_) {
        state = state_;
    }

private:
    unsigned long long key{};
    T value;
    states state;
};