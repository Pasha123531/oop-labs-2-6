#include "Character.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

int Character::objectCount_ = 0; // static

Character::Character() : Character("IronKnight", 120, 25) {}

Character::Character(std::string name, int hp, int attack)
    : Entity(std::move(name)), hp_(hp), attack_(attack)
{
    if (hp_ < 0) {
        throw std::invalid_argument("HP cannot be negative");
    }
    if (attack_ < 0) {
        throw std::invalid_argument("Attack cannot be negative");
    }
    ++objectCount_;
}

Character::Character(const Character& other) // copy constuctor
    : Entity(other), hp_(other.hp_), attack_(other.attack_)
{
    ++objectCount_;
}

Character::Character(Character&& other) noexcept // move contructor
    : Entity(std::move(other)), hp_(other.hp_), attack_(other.attack_)
{
    other.hp_ = 0;
    other.attack_ = 0;
    ++objectCount_;
}

Character::~Character() {
    --objectCount_;
}

int Character::hp() const {
    return hp_;
}

int Character::attack() const {
    return attack_;
}

void Character::setHp(int hp) {
    if (hp < 0) {
        throw std::invalid_argument("HP cannot be negative");
    }
    hp_ = hp;
}

void Character::setAttack(int attack) {
    if (attack < 0) {
        throw std::invalid_argument("Attack cannot be negative");
    }
    attack_ = attack;
}

void Character::takeDamage(int dmg) {
    if (dmg < 0) {
        return;
    }
    hp_ = std::max(0, hp_ - dmg);
}

void Character::heal(int amount) {
    if (amount < 0) {
        return;
    }
    hp_ += amount;
}

bool Character::isAlive() const {
    return hp_ > 0;
}

std::string Character::info() const {
    std::ostringstream oss;
    oss << "Character {name='" << name()
        << "', hp=" << hp_
        << ", attack=" << attack_
        << "}";
    return oss.str();
}

int Character::getObjectCount() {
    return objectCount_;
}

bool Character::operator!() const { // unary operator
    return !isAlive();
}

Character Character::operator+(const Character& other) const { // binary operator
    std::string newName = name() + "-" + other.name();
    int newHp = hp_ + other.hp_;
    int newAttack = attack_ + other.attack_;
    return Character(newName, newHp, newAttack);
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        Entity::operator=(other);
        hp_ = other.hp_;
        attack_ = other.attack_;
    }
    return *this;
}

Character& Character::operator=(Character&& other) noexcept {
    if (this != &other) {
        Entity::operator=(std::move(other));
        hp_ = other.hp_;
        attack_ = other.attack_;

        other.hp_ = 0;
        other.attack_ = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
    os << character.info();
    return os;
}
