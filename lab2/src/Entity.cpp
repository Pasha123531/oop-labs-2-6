#include "Entity.hpp"
#include <utility>
#include <iostream>

Entity::Entity() : Entity("Unknown") {}

Entity::Entity(std::string name) : name_(std::move(name)) {}

Entity::Entity(const Entity& other) : name_(other.name_) {} // copy constructor

Entity::Entity(Entity&& other) noexcept : name_(std::move(other.name_)) { // move constructor
    other.name_ = "Moved-from";
}

Entity::~Entity() = default;

const std::string& Entity::name() const {
    return name_;
}

void Entity::setName(const std::string& name) {
    name_ = name;
}

std::string Entity::info() const {
    return "Entity {name='" + name_ + "'}";
}

void Entity::interact() const { // interact
    std::cout << name_ << " interacts like a generic entity.\n";
}

Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
        name_ = other.name_;
    }
    return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_);
        other.name_ = "Moved-from";
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Entity& entity) {
    os << entity.info();
    return os;
}