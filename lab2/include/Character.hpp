#pragma once
#include <iostream>
#include <string>

class Character {
    private:
    std::string name_;
    int hp_;
    int attack_;

    static int objectCount_;

    public:
    Character(); //делегування
    Character(std::string name, int hp = 100, int attack = 10);
   
    Character(const Character& other); //copy
    Character(Character&& other) noexcept; //move
   
    ~Character(); //destructor

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

    static int getObjectCount(); 

    bool operator!() const;

    Character operator+(const Character& other) const; 

    Character& operator=(const Character& other);

    Character& operator=(Character&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Character& character);
    friend std::istream& operator>>(std::istream& is, Character& character);
};
