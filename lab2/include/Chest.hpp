#pragma once
#include "Entity.hpp"
#include "Item.hpp"
#include <iostream>
#include <string>

class Chest : public Entity {
private:
    bool locked_;
    int gold_;
    Item item_; // Has-A relationship (composition)
    bool hasItem_;

    static int objectCount_;

public:
    Chest();
    Chest(const std::string& name, bool locked, int gold);
    Chest(const Chest& other);
    Chest(Chest&& other) noexcept;

    ~Chest() override; // destructor

    bool locked() const;
    int gold() const;
    bool hasItem() const;

    void lock();
    void unlock();

    void addGold(int amount);
    int takeGold(int amount);

    void putItem(const Item& item);
    Item takeItem();

    std::string info() const override;
    void interact() const override; // interact

    static int getObjectCount();

    bool operator!() const;
    Chest operator+(const Chest& other) const;

    Chest& operator=(const Chest& other);
    Chest& operator=(Chest&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Chest& chest);
};