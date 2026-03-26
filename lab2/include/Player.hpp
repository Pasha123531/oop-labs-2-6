#pragma once
#include "Character.hpp"
#include <string>

class Player : public Character {
protected:
    int level_;

public:
    Player();
    Player(const std::string& name, int hp, int attack, int level);
    Player(const Player& other);
    Player(Player&& other) noexcept;

    ~Player() override;

    int level() const;
    void setLevel(int level);

    std::string info() const override;
    void interact() const override;   // interact

    Player& operator=(const Player& other);
    Player& operator=(Player&& other) noexcept;
};