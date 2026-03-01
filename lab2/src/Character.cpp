#include "Character.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

Character::Character() : Character("IronKnight") {}

Character::Character(std::string name, int hp, int attack)
    : name_(std::move(name)), hp_(hp), attack_(attack)
{
    if (hp_ < 0) throw std::invalid_argument("HP cannot be negative");
    if (attack_ < 0) throw std::invalid_argument("Attack cannot be negative");  
}

Character::Character(const Character& other)
    : name_(other.name_), hp_(other.hp_), attack_(other.attack_) {}

Character::~Character() = default;

const std::string& Character::name() const { return name_; }
int Character::hp() const { return hp_; }
int Character::attack() const { return attack_; }

void Character::setName(const std::string& name) { name_ = name; }

void Character::setHp(int hp) {
    if (hp < 0) throw std::invalid_argument("HP cannot be negative");
    hp_ = hp;
}

void Character::setAttack(int attack) {
    if (attack < 0) throw std::invalid_argument("Attack cannot be negative");
    attack_ = attack;
}

void Character::takeDamage(int dmg) {
    if (dmg < 0) return;
    hp_ = std::max(0, hp_ - dmg);
}

void Character::heal(int amount) {
    if (amount < 0) return;
    hp_ += amount;
}

bool Character::isAlive() const {
    return hp_ > 0;
}

std::string Character::info() const {
    std::ostringstream oss;
    oss << "Character {name='" << name_ << "', weight=" << hp_ << ", value=" << attack_ << "}";
    return oss.str();
}

