#pragma once
#include "Item.hpp"

class Weapon : public Item {
private:
    int damage_;

public:
    Weapon();
    Weapon(std::string name, double weight, int value, int damage);

    Weapon(const Weapon& other);
    Weapon(Weapon&& other) noexcept;

    ~Weapon() override;

    int damage() const;
    void setDamage(int damage);

    std::string info() const override;

    Weapon& operator=(const Weapon& other);
    Weapon& operator=(Weapon&& other) noexcept;
};