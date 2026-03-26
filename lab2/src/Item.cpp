#include "Item.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>
#include <iostream>

int Item::objectCount_ = 0;

Item::Item() : Item("Unknown Item", 0.1, 0) {}

Item::Item(const std::string& name, double weight, int value)
    : Entity(name), weight_(weight), value_(value)
{
    if (weight_ < 0) {
        throw std::invalid_argument("Item weight cannot be negative");
    }
    if (value_ < 0) {
        throw std::invalid_argument("Item value cannot be negative");
    }
    ++objectCount_;
}

Item::Item(const Item& other) // copy constructor
    : Entity(other), weight_(other.weight_), value_(other.value_)
{
    ++objectCount_;
}

Item::Item(Item&& other) noexcept // move constructor
    : Entity(std::move(other)), weight_(other.weight_), value_(other.value_)
{
    other.weight_ = 0;
    other.value_ = 0;
    ++objectCount_;
}

Item::~Item() {
    --objectCount_;
}

double Item::weight() const {
    return weight_;
}

int Item::value() const {
    return value_;
}

void Item::setWeight(double weight) {
    if (weight < 0) {
        throw std::invalid_argument("Item weight cannot be negative");
    }
    weight_ = weight;
}

void Item::setValue(int value) {
    if (value < 0) {
        throw std::invalid_argument("Item value cannot be negative");
    }
    value_ = value;
}

std::string Item::info() const {
    std::ostringstream oss;
    oss << "Item {name='" << name()
        << "', weight=" << weight_
        << ", value=" << value_
        << "}";
    return oss.str();
}

void Item::interact() const { // interact
    std::cout << "You inspect the item: " << name()
              << " (weight: " << weight_
              << ", value: " << value_ << ")\n";
}

int Item::getObjectCount() {
    return objectCount_;
}

bool Item::operator!() const {
    return value_ == 0;
}

Item Item::operator+(const Item& other) const {
    std::string newName = name() + "-" + other.name();
    double newWeight = weight_ + other.weight_;
    int newValue = value_ + other.value_;

    return Item(newName, newWeight, newValue);
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        Entity::operator=(other);
        weight_ = other.weight_;
        value_ = other.value_;
    }
    return *this;
}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        Entity::operator=(std::move(other));
        weight_ = other.weight_;
        value_ = other.value_;

        other.weight_ = 0;
        other.value_ = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.info();
    return os;
}
