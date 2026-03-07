#pragma once
#include <iostream>
#include <string>

class Item {
    private:
    std::string name_;
    double weight_;
    int value_;

    static int objectCount_;

    public:
    Item();
    Item(std::string name, double weight = 0.1, int value = 0);

    Item(const Item& other); //copy
    Item(Item&& other) noexcept; //move

    ~Item(); //destructor

    const std::string& name() const;
    double weight() const;
    int value() const;

    void setName(const std::string& name);
    void setWeight(double weight);
    void setValue(int value);

    std::string info() const;

    static int getObjectCount();

    bool operator!() const;

    Item operator+(const Item& other) const;

    Item& operator=(const Item& other);
    Item& operator=(Item&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend std::istream& operator>>(std::istream& is, Item& item);
};