#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"

class Chest {
    private:
    std::string title_;
    bool locked_;
    int gold_;
    Item item_;
    bool hasItem_;

    public:
    Chest();
    Chest(std::string title, bool locked = false, int gold = 0);
    Chest(const Chest& other);
    ~Chest();

    const std::string& title() const;
    bool locked() const;
    int gold() const;
    bool hasItem() const;

    void lock();
    void unlock();

    void addGold(int amount);
    int takeGold(int amount);

    void putItem(const Item& item);
    Item takeItem();

    std::string info() const;
};