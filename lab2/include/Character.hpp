#pragma once
#include "Entity.hpp"
#include <iostream>
#include <string>

class Character : public Entity {
protected:
    int hp_;
    int attack_;
    static int objectCount_;

public:
    Character();
    Character(const std::string& name, int hp, int attack);
    Character(const Character& other);
    Character(Character&& other) noexcept;

    virtual ~Character() override;

    int hp() const;
    int attack() const;

    void setHp(int hp);
    void setAttack(int attack);

    void takeDamage(int dmg);
    void heal(int amount);
    bool isAlive() const;

    std::string info() const override;

    virtual void interact() const override = 0;  // pure virtual function

    static int getObjectCount();

    bool operator!() const;

    Character& operator=(const Character& other);
    Character& operator=(Character&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Character& character);
};
