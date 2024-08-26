#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>

// Class representing a product that can be sold in a vending machine
class Product {
private:
    std::string name;
    double price;

public:
    // Default constructor
    Product() : name(""), price(0.0) {}

    // Parameterized constructor
    Product(std::string name, double price) : name(name), price(price) {}

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

    // Getter for product name
    std::string getName() const {
        return this->name;
    }

    // Getter for product price
    double getPrice() const {
        return this->price;
    }
};

// Class representing a vending machine
class VendingMachine {
private:
    std::string name;
    std::vector<Product> products;

public:
    // Constructor: Initializes the vending machine with a name
    VendingMachine(std::string name) : name(name) {}

    // Adds a product to the vending machine
    void addProduct(const Product& product) {
        this->products.push_back(product);
        std::cout << "Added " << product.getName() << " to " << this->name << std::endl;
    }

    // Displays all products in the vending machine
    void displayProducts() {
        std::cout << "Products in " << this->name << ":" << std::endl;
        for (const auto& product : this->products) {
            product.displayInfo();
        }
    }

    // Applies a discount to all products
    void applyDiscountToAll(double discountPercent) {
        for (auto& product : this->products) {
            product.applyDiscount(discountPercent);
        }
    }
};

int main() {
    // Create an array of Product objects
    const int NUM_PRODUCTS = 5;
    Product productArray[NUM_PRODUCTS] = {
        Product("Chips", 1.50),
        Product("Candy", 1.00),
        Product("Soda", 2.00),
        Product("Chocolate", 1.75),
        Product("Gum", 0.75)
    };

    // Create a vending machine object
    VendingMachine snackMachine("Snack Machine");

    // Add products from the array to the vending machine
    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        snackMachine.addProduct(productArray[i]);
    }

    // Display all products in the vending machine
    snackMachine.displayProducts();

    // Apply a discount to all products
    snackMachine.applyDiscountToAll(10);

    // Display updated products
    snackMachine.displayProducts();

    return 0;
}
