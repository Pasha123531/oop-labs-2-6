#include "Player.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

Player::Player() : Player("DefaultPlayer", 100, 15, 1) {}

Player::Player(std::string name, int hp, int attack, int level)
    : Character(std::move(name), hp, attack), level_(level)
{
    if (level_ < 1) {
        throw std::invalid_argument("Level must be at least 1");
    }
}

Player::Player(const Player& other) // copy constructor
    : Character(other), level_(other.level_) {}

Player::Player(Player&& other) noexcept // move consturcotr
    : Character(std::move(other)), level_(other.level_)
{
    other.level_ = 1;
}

Player::~Player() = default;

int Player::level() const {
    return level_;
}

void Player::setLevel(int level) {
    if (level < 1) {
        throw std::invalid_argument("Level must be at least 1");
    }
    level_ = level;
}

std::string Player::info() const {
    std::ostringstream oss;
    oss << "Player {name='" << name()
        << "', hp=" << hp()
        << ", attack=" << attack()
        << ", level=" << level_
        << "}";
    return oss.str();
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        Character::operator=(other);
        level_ = other.level_;
    }
    return *this;
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        Character::operator=(std::move(other));
        level_ = other.level_;
        other.level_ = 1;
    }
    return *this;
}