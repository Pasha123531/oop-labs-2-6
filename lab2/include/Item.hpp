#pragma once
#include <iostream>
#include <string>

class Item {
    private:
    std::string name_;
    double weight_;
    int value_;

    public:
    Item();
    Item(std::string name, double weight = 0.1, int value = 0);
    Item(const Item& other);
    ~Item();

    const std::string& name() const;
    double weight() const;
    int value() const;

    void setName(const std::string& name);
    void setWeight(double weight);
    void setValue(int value);

    std::string info() const;
};