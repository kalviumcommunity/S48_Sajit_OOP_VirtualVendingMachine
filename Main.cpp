#include <iostream>
#include <string>
#include <map>
#include <iomanip>

// Class representing a vending machine
class VendingMachine {
private:
    std::string name;
    std::map<std::string, int> inventory;
    double totalSales;

public:
    // Constructor: Initializes the vending machine with a name
    VendingMachine(std::string name) : name(name), totalSales(0.0) {
        // Using 'this' pointer to differentiate between parameter and member variable
        this->name = name;
    }

    // Adds an item to the vending machine's inventory
    void addItem(std::string item, int quantity) {
        this->inventory[item] += quantity;  // Using 'this' to explicitly access the member variable
        std::cout << "Added " << quantity << " " << item << "(s) to " << this->name << std::endl;
    }

    // Displays the current inventory of the vending machine
    void displayInventory() {
        std::cout << "Inventory for " << this->name << ":" << std::endl;
        for (const auto& item : this->inventory) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }

    // Simulates selling an item
    bool sellItem(std::string item, double price) {
        if (this->inventory[item] > 0) {
            this->inventory[item]--;
            this->totalSales += price;
            return true;
        }
        return false;
    }

    // Returns the current object for method chaining
    VendingMachine* updateAndDisplay(std::string item, int quantity) {
        this->addItem(item, quantity);
        this->displayInventory();
        return this;  // Returning 'this' pointer for method chaining
    }
};

// Class representing a product that can be sold in a vending machine
class Product {
private:
    std::string name;
    double price;

public:
    // Constructor: Initializes a product with a name and price
    Product(std::string name, double price) : name(name), price(price) {
        this->name = name;  // Using 'this' pointer to differentiate between parameter and member variable
        this->price = price;
    }

    // Displays information about the product
    void displayInfo() {
        std::cout << "Product: " << this->name << ", Price: $" << std::fixed << std::setprecision(2) << this->price << std::endl;
    }

    // Applies a discount to the product's price
    void applyDiscount(double discountPercent) {
        this->price *= (1 - discountPercent / 100);
        std::cout << "Applied " << discountPercent << "% discount to " << this->name << ". New price: $"
                  << std::fixed << std::setprecision(2) << this->price << std::endl;
    }
};

int main() {
    // Create a vending machine object
    VendingMachine snackMachine("Snack Machine");

    // Use method chaining with 'this' pointer
    snackMachine.updateAndDisplay("chips", 10)->updateAndDisplay("candy", 15);

    // Create a product object
    Product chips("Potato Chips", 1.50);

    // Display product information and apply discount
    chips.displayInfo();
    chips.applyDiscount(10);

    return 0;
}
