#pragma once
#include <iostream>
#include <string>

class Character {
    private:
    std::string name_;
    int hp_;
    int attack_;

    public:
    Character(); //делегування
    Character(std::string name, int hp = 100, int attack = 10);
    Character(const Character& other); //copy
    ~Character(); //деструктор

    const std::string& name() const;
    int hp() const;
    int attack() const;
    
    void setName(const std::string& name);
    void setHp(int hp);
    void setAttack(int attack);

    void takeDamage(int dmg);
    void heal(int amount);

    bool isAlive() const;

    std::string info() const;
};
