#include "Warrior.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

Warrior::Warrior() : Warrior("DefaultWarrior", 150, 30, 1, 20) {}

Warrior::Warrior(std::string name, int hp, int attack, int level, int armor)
    : Player(std::move(name), hp, attack, level), armor_(armor)
{
    if (armor_ < 0) {
        throw std::invalid_argument("Armor cannot be negative");
    }
}

Warrior::Warrior(const Warrior& other)
    : Player(other), armor_(other.armor_) {}

Warrior::Warrior(Warrior&& other) noexcept
    : Player(std::move(other)), armor_(other.armor_)
{
    other.armor_ = 0;
}

Warrior::~Warrior() = default;

int Warrior::armor() const {
    return armor_;
}

void Warrior::setArmor(int armor) {
    if (armor < 0) {
        throw std::invalid_argument("Armor cannot be negative");
    }
    armor_ = armor;
}

std::string Warrior::info() const {
    std::ostringstream oss;
    oss << "Warrior {name='" << name()
        << "', hp=" << hp()
        << ", attack=" << attack()
        << ", level=" << level()
        << ", armor=" << armor_
        << "}";
    return oss.str();
}

Warrior& Warrior::operator=(const Warrior& other) {
    if (this != &other) {
        Player::operator=(other);
        armor_ = other.armor_;
    }
    return *this;
}

Warrior& Warrior::operator=(Warrior&& other) noexcept {
    if (this != &other) {
        Player::operator=(std::move(other));
        armor_ = other.armor_;
        other.armor_ = 0;
    }
    return *this;
}