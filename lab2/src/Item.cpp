#include "Item.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

Item::Item() : Item("Unknown") {} // делегування

Item::Item(std::string name, double weight, int value)
    : name_(std::move(name)), weight_(weight), value_(value) // список ініціалізації
{
    if (weight_ < 0) throw std::invalid_argument("Item weight cannot be negative");
    if (value_ < 0) throw std::invalid_argument("Item value cannot be negative");
}

Item::Item(const Item& other)
    : name_(other.name_), weight_(other.weight_), value_(other.value_) {}

Item::~Item() = default;

const std::string& Item::name() const { return name_; }
double Item::weight() const { return weight_; }
int Item::value() const { return value_; }

void Item::setName(const std::string& name) { name_ = name; }

void Item::setWeight(double weight) {
    if (weight < 0) throw std::invalid_argument("Item weight cannot be negative");
    weight_ = weight;
}

void Item::setValue(int value) {
    if (value < 0) throw std::invalid_argument("Item value cannot be negative");
    value_ = value;
}

std::string Item::info() const {
    std::ostringstream oss;
    oss << "Item{name='" << name_ << "', weight=" << weight_ << ", value=" << value_ << "}";
    return oss.str();
}