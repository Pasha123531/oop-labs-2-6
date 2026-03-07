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

    static int objectCount_;

    public:
    Chest();
    Chest(std::string title, bool locked = false, int gold = 0);

    Chest(const Chest& other); //copy
    Chest(Chest&& other) noexcept; //move

    ~Chest(); //destructor

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

    static int getObjectCount();

    bool operator!() const;

    Chest operator+(const Chest& other) const;

    Chest& operator=(const Chest& other);
    Chest& operator=(Chest&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Chest& chest);
    friend std::istream& operator>>(std::istream& is, Chest& chest);
};