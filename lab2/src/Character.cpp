#include "Character.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

int Character::objectCount_ = 0;

Character::Character() : Character("IronKnight") {}

Character::Character(std::string name, int hp, int attack)
    : name_(std::move(name)), hp_(hp), attack_(attack)
{
    if (hp_ < 0) {
        throw std::invalid_argument("HP cannot be negative");
    }
    if (attack_ < 0) {
        throw std::invalid_argument("Attack cannot be negative");
    }
    ++objectCount_;
}

Character::Character(const Character& other)
    : name_(other.name_), hp_(other.hp_), attack_(other.attack_) 
{
    ++objectCount_;
}

Character::Character(Character&& other) noexcept
    : name_(std::move(other.name_)), hp_(other.hp_), attack_(other.attack_)
{
    other.hp_ = 0;
    other.attack_ = 0;
    other.name_ = "Moved-from";
    ++objectCount_;
}

Character::~Character() {
    --objectCount_;
}

const std::string& Character::name() const {
    return name_;
}

int Character::hp() const {
    return hp_;
}

int Character::attack() const {
    return attack_;
}

void Character::setName(const std::string& name) {
    this->name_ = name;
}

void Character::setHp(int hp) {
    if (hp < 0) {
        throw std::invalid_argument("HP cannot be negative");
    }
    this->hp_ = hp;
}

void Character::setAttack(int attack) {
    if (attack < 0) {
        throw std::invalid_argument("Attack cannot be negative");
    }
    this->attack_ = attack;
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
    oss << "Character {name='" << name_
        << "', hp=" << hp_
        << ", attack=" << attack_
        << "}";
    return oss.str();
}

int Character::getObjectCount() {
    return objectCount_;
}

bool Character::operator!() const {
    return !isAlive();
}

Character Character::operator+(const Character& other) const {
    std::string newName = name_ + "-" + other.name_;
    int newHp = hp_ + other.hp_;
    int newAttack = attack_ + other.attack_;
    return Character(newName, newHp, newAttack);
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        this->name_ = other.name_;
        this->hp_ = other.hp_;
        this->attack_ = other.attack_;
    }
    return *this;
}

Character& Character::operator=(Character&& other) noexcept {
    if (this != &other) {
        this->name_ = std::move(other.name_);
        this->hp_ = other.hp_;
        this->attack_ = other.attack_;

        other.name_ = "Moved-from";
        other.hp_ = 0;
        other.attack_ = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
    os << "Name: " << character.name_
       << ", HP: " << character.hp_
       << ", Attack: " << character.attack_;
    return os;
}

std::istream& operator>>(std::istream& is, Character& character) {
    std::string name;
    int hp;
    int attack;

    std::cout << "Enter name: ";
    is >> name;
    std::cout << "Enter hp: ";
    is >> hp;
    std::cout << "Enter attack: ";
    is >> attack;

    if (hp < 0 || attack < 0) {
        throw std::invalid_argument("HP and attack cannot be negative");
    }

    character.name_ = name;
    character.hp_ = hp;
    character.attack_ = attack;

    return is;
}

