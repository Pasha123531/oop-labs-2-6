#pragma once
#include "Character.hpp"
#include <string>

class Player : public Character {
protected:
    int level_;

public:
    Player();
    Player(std::string name, int hp, int attack, int level);

    Player(const Player& other);
    Player(Player&& other) noexcept;

    ~Player() override;

    int level() const;
    void setLevel(int level);

    std::string info() const override;

    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;
};