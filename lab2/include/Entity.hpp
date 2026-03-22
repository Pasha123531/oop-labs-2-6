#pragma once
#include <iostream>
#include <string>

class Entity {
protected:
    std::string name_;

public:
    Entity();
    Entity(std::string name);
    Entity(const Entity& other);
    Entity(Entity&& other) noexcept;
    virtual ~Entity();

    const std::string& name() const;
    void setName(const std::string& name);

    virtual std::string info() const;

    Entity& operator=(const Entity& other);
    Entity& operator=(Entity&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);
};