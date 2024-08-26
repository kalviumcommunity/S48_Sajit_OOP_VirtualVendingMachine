#include <iostream>
#include <string>
#include <map>
#include <iomanip>

// Class representing a vending machine
class VendingMachine {
private:
    std::string name;
    std::map<std::string, int> inventory;

public:
    // Constructor: Initializes the vending machine with a name
    VendingMachine(std::string machineName) : name(machineName) {}

    // Adds an item to the vending machine's inventory
    void addItem(std::string item, int quantity) {
        inventory[item] += quantity;
        std::cout << "Added " << quantity << " " << item << "(s) to " << name << std::endl;
    }

    // Displays the current inventory of the vending machine
    void displayInventory() {
        std::cout << "Inventory for " << name << ":" << std::endl;
        for (const auto& item : inventory) {
            std::cout << item.first << ": " << item.second << std::endl;
        }
    }
};

// Class representing a product that can be sold in a vending machine
class Product {
private:
    std::string name;
    double price;

public:
    // Constructor: Initializes a product with a name and price
    Product(std::string productName, double productPrice) : name(productName), price(productPrice) {}

    // Displays information about the product
    void displayInfo() {
        std::cout << "Product: " << name << ", Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
    }

    // Applies a discount to the product's price
    void applyDiscount(double discountPercent) {
        price *= (1 - discountPercent / 100);
        std::cout << "Applied " << discountPercent << "% discount to " << name << ". New price: $"
                  << std::fixed << std::setprecision(2) << price << std::endl;
    }
};

int main() {
    // Create a vending machine object
    VendingMachine snackMachine("Snack Machine");

    // Add items to the vending machine
    snackMachine.addItem("chips", 10);
    snackMachine.addItem("candy", 15);
    snackMachine.addItem("soda", 20);

    // Display the vending machine's inventory
    snackMachine.displayInventory();

    // Create a product object
    Product chips("Potato Chips", 1.50);

    // Display product information
    chips.displayInfo();

    // Apply a discount to the product
    chips.applyDiscount(10);

    return 0;
}
