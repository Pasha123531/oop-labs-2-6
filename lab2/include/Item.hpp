#pragma once
#include "Entity.hpp"
#include <iostream>
#include <string>

class Item : public Entity {
protected:
    double weight_;
    int value_;
    static int objectCount_;

public:
    Item();
    Item(const std::string& name, double weight, int value);
    Item(const Item& other);
    Item(Item&& other) noexcept;

    ~Item() override;

    double weight() const;
    int value() const;

    void setWeight(double weight);
    void setValue(int value);

    std::string info() const override;
    void interact() const override;

    static int getObjectCount();

    bool operator!() const;
    Item operator+(const Item& other) const;

    Item& operator=(const Item& other);
    Item& operator=(Item&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};