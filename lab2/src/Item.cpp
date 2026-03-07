#include "Item.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

int Item::objectCount_ = 0;

Item::Item() : Item("Unknown") {} // делегування

Item::Item(std::string name, double weight, int value)
    : name_(std::move(name)), weight_(weight), value_(value) // список ініціалізації
{
    if (weight_ < 0) throw std::invalid_argument("Item weight cannot be negative");
    if (value_ < 0) throw std::invalid_argument("Item value cannot be negative");

    ++objectCount_;
}

Item::Item(const Item& other)
    : name_(other.name_), weight_(other.weight_), value_(other.value_) 
{
    ++objectCount_;
}

Item::Item(Item&& other) noexcept
    : name_(std::move(other.name_)), weight_(other.weight_), value_(other.value_)
{
    other.weight_ = 0;
    other.value_ = 0;
    ++objectCount_;
}

Item::~Item() {
    --objectCount_;
}

const std::string& Item::name() const { return name_; }
double Item::weight() const { return weight_; }
int Item::value() const { return value_; }

void Item::setName(const std::string& name) {
    this->name_ = name;
}

void Item::setWeight(double weight) {
    if (weight < 0) throw std::invalid_argument("Item weight cannot be negative");
    this->weight_ = weight;
}

void Item::setValue(int value) {
    if (value < 0) throw std::invalid_argument("Item value cannot be negative");
    this->value_ = value;
}

std::string Item::info() const {
    std::ostringstream oss;
    oss << "Item {name='" << name_
        << "', weight=" << weight_
        << ", value=" << value_
        << "}";
    return oss.str();
}

int Item::getObjectCount() {
    return objectCount_;
}

bool Item::operator!() const {
    return value_ == 0;
}

Item Item::operator+(const Item& other) const {
    std::string newName = name_ + "-" + other.name_;
    double newWeight = weight_ + other.weight_;
    int newValue = value_ + other.value_;

    return Item(newName, newWeight, newValue);
}

Item& Item::operator=(const Item& other) {
    if (this != &other) {
        this->name_ = other.name_;
        this->weight_ = other.weight_;
        this->value_ = other.value_;
    }
    return *this;
}

Item& Item::operator=(Item&& other) noexcept {
    if (this != &other) {
        this->name_ = std::move(other.name_);
        this->weight_ = other.weight_;
        this->value_ = other.value_;

        other.weight_ = 0;
        other.value_ = 0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.info();
    return os;
}

std::istream& operator>>(std::istream& is, Item& item) {
    std::string name;
    double weight;
    int value;

    std::cout << "Enter item name: ";
    is >> name;

    std::cout << "Enter weight: ";
    is >> weight;

    std::cout << "Enter value: ";
    is >> value;

    item.name_ = name;
    item.weight_ = weight;
    item.value_ = value;

    return is;
}