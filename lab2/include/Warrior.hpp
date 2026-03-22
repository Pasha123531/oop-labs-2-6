#pragma once
#include "Player.hpp"
#include <string>

class Warrior : public Player {
private:
    int armor_;

public:
    Warrior();
    Warrior(std::string name, int hp, int attack, int level, int armor);

    Warrior(const Warrior& other);
    Warrior(Warrior&& other) noexcept;

    ~Warrior() override;

    int armor() const;
    void setArmor(int armor);

    std::string info() const override;

    Warrior& operator=(const Warrior& other);
    Warrior& operator=(Warrior&& other) noexcept;
};