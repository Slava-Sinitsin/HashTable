#pragma once

template<typename T>
class CCNode {
public:

    CCNode() {
        this->pNext = nullptr;
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

    CCNode<T> *getNext() const {
        return pNext;
    }

    void setNext(CCNode<T> *pNext_) {
        pNext = pNext_;
    }

private:
    unsigned long long key{};
    T value;
    CCNode<T> *pNext;
};