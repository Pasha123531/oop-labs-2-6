#pragma once
#include "Entity.hpp"
#include <string>

class Item : public Entity {
protected:
    double weight_;
    int value_;

    static int objectCount_; // static

public:
    Item();
    Item(std::string name, double weight = 0.1, int value = 0);

    Item(const Item& other); // copy constructor
    Item(Item&& other) noexcept; // move constructor

    virtual ~Item(); // destructor

    double weight() const;
    int value() const;

    void setWeight(double weight);
    void setValue(int value);

    virtual std::string info() const;

    static int getObjectCount();

    bool operator!() const; // unary operator
    Item operator+(const Item& other) const; // binary operator

    Item& operator=(const Item& other);
    Item& operator=(Item&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};