// BaseItem.h
#ifndef BASEITEM_H
#define BASEITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class BaseItem {
public:
    virtual ~BaseItem() = default; // Virtual destructor for proper cleanup

    virtual std::string getName() const = 0; // Pure virtual method
    virtual int getPrice() const = 0;         // Pure virtual method
    virtual int getStock() const = 0;         // Pure virtual method
    virtual void setStock(int newStock) = 0; // Pure virtual method
    virtual void display() const = 0;         // Pure virtual method

    // Additional methods as needed
};

#endif // BASEITEM_H
