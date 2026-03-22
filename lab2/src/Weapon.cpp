#include "Weapon.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

Weapon::Weapon() : Weapon("Wooden Sword", 2.0, 20, 10) {}

Weapon::Weapon(std::string name, double weight, int value, int damage)
    : Item(std::move(name), weight, value), damage_(damage) {
    if (damage_ < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
}

Weapon::Weapon(const Weapon& other)
    : Item(other), damage_(other.damage_) {}

Weapon::Weapon(Weapon&& other) noexcept
    : Item(std::move(other)), damage_(other.damage_) {
    other.damage_ = 0;
}

Weapon::~Weapon() = default;

int Weapon::damage() const {
    return damage_;
}

void Weapon::setDamage(int damage) {
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
    damage_ = damage;
}

std::string Weapon::info() const {
    std::ostringstream oss;
    oss << "Weapon {name='" << name()
        << "', weight=" << weight()
        << ", value=" << value()
        << ", damage=" << damage_
        << "}";
    return oss.str();
}

Weapon& Weapon::operator=(const Weapon& other) {
    if (this != &other) {
        Item::operator=(other);
        damage_ = other.damage_;
    }
    return *this;
}

Weapon& Weapon::operator=(Weapon&& other) noexcept {
    if (this != &other) {
        Item::operator=(std::move(other));
        damage_ = other.damage_;
        other.damage_ = 0;
    }
    return *this;
}