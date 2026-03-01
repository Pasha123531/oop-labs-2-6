#include "Chest.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

Chest::Chest() : Chest("Old Chest") {}

Chest::Chest(std::string title, bool locked, int gold)
    : title_(std::move(title)),
      locked_(locked),
      gold_(gold),
      item_(),
      hasItem_(false)
{
    if (gold_ < 0)
        throw std::invalid_argument("Gold cannot be negative");
}

Chest::Chest(const Chest& other)
    : title_(other.title_),
      locked_(other.locked_),
      gold_(other.gold_),
      item_(other.item_),
      hasItem_(other.hasItem_)
{
}

Chest::~Chest() = default;

const std::string& Chest::title() const { return title_; }
bool Chest::locked() const { return locked_; }
int Chest::gold() const { return gold_; }
bool Chest::hasItem() const { return hasItem_; }

void Chest::lock() { locked_ = true; }
void Chest::unlock() { locked_ = false; }

void Chest::addGold(int amount)
{
    if (amount > 0)
        gold_ += amount;
}

int Chest::takeGold(int amount)
{
    if (locked_)
        throw std::runtime_error("Chest is locked");

    if (amount < 0)
        return 0;

    int taken = std::min(gold_, amount);
    gold_ -= taken;
    return taken;
}

void Chest::putItem(const Item& item)
{
    if (locked_)
        throw std::runtime_error("Chest is locked");

    item_ = item;
    hasItem_ = true;
}

Item Chest::takeItem()
{
    if (locked_)
        throw std::runtime_error("Chest is locked");

    if (!hasItem_)
        throw std::runtime_error("Chest is empty");

    hasItem_ = false;
    return item_;
}

std::string Chest::info() const
{
    std::ostringstream oss;

    oss << "Chest {title='" << title_
        << "', locked=" << (locked_ ? "true" : "false")
        << ", gold=" << gold_
        << ", hasItem=" << (hasItem_ ? "true" : "false");

    if (hasItem_)
        oss << ", item=" << item_.info();

    oss << "}";

    return oss.str();
}