#pragma once
#include "Entity.hpp"
#include <iostream>
#include <string>

class Character : public Entity { // Public inheritance
protected:
    int hp_;
    int attack_;

    static int objectCount_; // static

public:
    Character();
    Character(std::string name, int hp = 100, int attack = 10);

    Character(const Character& other); // copy constructor
    Character(Character&& other) noexcept; // move constructor

    virtual ~Character(); // destructor

    int hp() const;
    int attack() const;

    void setHp(int hp);
    void setAttack(int attack);

    void takeDamage(int dmg);
    void heal(int amount);
    bool isAlive() const;

    virtual std::string info() const override;

    static int getObjectCount();

    bool operator!() const; // unary operator

    Character operator+(const Character& other) const; // binary operator

    Character& operator=(const Character& other);
    Character& operator=(Character&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Character& character);
};
