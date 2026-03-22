#include "Chest.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

int Chest::objectCount_ = 0;

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

    ++objectCount_;
}

Chest::Chest(const Chest& other)
    : title_(other.title_),
      locked_(other.locked_),
      gold_(other.gold_),
      item_(other.item_),
      hasItem_(other.hasItem_)
{
    ++objectCount_;
}

Chest::Chest(Chest&& other) noexcept
    : title_(std::move(other.title_)),
      locked_(other.locked_),
      gold_(other.gold_),
      item_(std::move(other.item_)),
      hasItem_(other.hasItem_)
{
    other.gold_ = 0;
    other.hasItem_ = false;
    ++objectCount_;
}

Chest::~Chest() {
    --objectCount_;
}

const std::string& Chest::title() const { return title_; }
bool Chest::locked() const { return locked_; }
int Chest::gold() const { return gold_; }
bool Chest::hasItem() const { return hasItem_; }

void Chest::lock() { locked_ = true; }
void Chest::unlock() { locked_ = false; }

void Chest::addGold(int amount)
{
    if (amount > 0)
        this->gold_ += amount;
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

int Chest::getObjectCount() {
    return objectCount_;
}

bool Chest::operator!() const {
    return locked_;
}

Chest Chest::operator+(const Chest& other) const {
    Chest result("Merged Chest");
    result.gold_ = this->gold_ + other.gold_;
    result.locked_ = this->locked_ || other.locked_;
    return result;
}

Chest& Chest::operator=(const Chest& other) {
    if (this != &other) {
        this->title_ = other.title_;
        this->locked_ = other.locked_;
        this->gold_ = other.gold_;
        this->item_ = other.item_;
        this->hasItem_ = other.hasItem_;
    }
    return *this;
}

Chest& Chest::operator=(Chest&& other) noexcept {
    if (this != &other) {
        this->title_ = std::move(other.title_);
        this->locked_ = other.locked_;
        this->gold_ = other.gold_;
        this->item_ = std::move(other.item_);
        this->hasItem_ = other.hasItem_;

        other.gold_ = 0;
        other.hasItem_ = false;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Chest& chest) {
    os << chest.info();
    return os;
}