#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Base Product class representing a general product
class Product {
protected:
    string name;
    double price;
    int stockQuantity;

public:
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {}

    // Display product details
    virtual void displayInfo() const {
        cout << "Product: " << name << ", Price: $" << fixed << setprecision(2) << price
             << ", Stock Quantity: " << stockQuantity << endl;
    }

    // Process purchase and reduce stock if available
    bool purchase(int quantity) {
        if (quantity <= stockQuantity) {
            stockQuantity -= quantity;
            return true;
        } else {
            cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
            return false;
        }
    }

    double getPrice() const { return price; }
    string getName() const { return name; }
};

// DiscountedProduct class inherits from Product, adding a discount feature (Single Inheritance)
class DiscountedProduct : public Product {
private:
    double discount;

public:
    DiscountedProduct(string name, double price, int stockQuantity, double discount)
        : Product(name, price, stockQuantity), discount(discount) {
        applyDiscount();
    }

    // Apply discount to the product price
    void applyDiscount() {
        price *= (1 - discount / 100);
    }

    // Display discounted product details
    void displayInfo() const override {
        cout << "Discounted Product: " << name << ", Price after discount: $" << fixed
             << setprecision(2) << price << ", Discount: " << discount << "%, Stock Quantity: " << stockQuantity << endl;
    }
};

// Beverage class inherits from Product, adding carbonation info (Hierarchical Inheritance)
class Beverage : public Product {
private:
    bool isCarbonated;

public:
    Beverage(string name, double price, int stockQuantity, bool isCarbonated)
        : Product(name, price, stockQuantity), isCarbonated(isCarbonated) {}

    // Display beverage-specific details
    void displayInfo() const override {
        cout << "Beverage: " << name << ", Price: $" << fixed << setprecision(2) << price
             << ", Carbonated: " << (isCarbonated ? "Yes" : "No") << ", Stock Quantity: " << stockQuantity << endl;
    }
};

// Snack class inherits from Product, adding health info (Hierarchical Inheritance)
class Snack : public Product {
private:
    bool isHealthy;

public:
    Snack(string name, double price, int stockQuantity, bool isHealthy)
        : Product(name, price, stockQuantity), isHealthy(isHealthy) {}

    // Display snack-specific details
    void displayInfo() const override {
        cout << "Snack: " << name << ", Price: $" << fixed << setprecision(2) << price
             << ", Healthy: " << (isHealthy ? "Yes" : "No") << ", Stock Quantity: " << stockQuantity << endl;
    }
};

// VendingMachine class manages multiple products and tracks total sales and transactions
class VendingMachine {
private:
    string name;
    vector<Product*> products;

    // Static variables to track sales and transactions across all instances
    static double totalSales;
    static int totalTransactions;

public:
    VendingMachine(string name) : name(name) {}

    // Add a product to the vending machine's inventory
    void addProduct(Product* product) {
        products.push_back(product);
        cout << "Added " << product->getName() << " to " << name << endl;
    }

    // Display all products in the vending machine
    void displayProducts() const {
        cout << "Products in " << name << ":" << endl;
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". ";
            products[i]->displayInfo();
        }
    }

    // Allow user to select products and process purchases
    double selectProducts() {
        double total = 0.0;
        char continueChoice;
        bool purchaseMade = false;

        // Loop to handle multiple product selections
        do {
            int choice;
            cout << "Enter the number of the product you want (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size())) {
                cout << "Invalid selection. Please choose a number between 1 and " << products.size() << "." << endl;
            } else {
                int quantity;
                cout << "Enter the quantity of " << products[choice - 1]->getName() << " you want to purchase: ";
                cin >> quantity;

                // Process purchase if stock is sufficient
                if (products[choice - 1]->purchase(quantity)) {
                    total += products[choice - 1]->getPrice() * quantity;
                    purchaseMade = true;
                    cout << "Added " << products[choice - 1]->getName() << " to total, costing: $"
                         << fixed << setprecision(2) << products[choice - 1]->getPrice() * quantity << endl;
                }
            }

            cout << "Do you want to select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        // Update static totals if a purchase was made
        if (purchaseMade) {
            totalSales += total;
            totalTransactions++;
        }

        return total;
    }

    // Static methods to display cumulative sales and transaction statistics
    static void displayTotalSales() {
        cout << "Total Sales across all vending machines: $" << fixed << setprecision(2) << totalSales << endl;
    }

    static void displayTransactionStats() {
        cout << "Total number of successful transactions: " << totalTransactions << endl;
    }
};

// Initialize static variables
double VendingMachine::totalSales = 0.0;
int VendingMachine::totalTransactions = 0;

int main() {
    VendingMachine* machine = new VendingMachine("Snack Machine");

    // Adding different types of products to demonstrate inheritance
    machine->addProduct(new DiscountedProduct("Chips", 1.50, 10, 10));
    machine->addProduct(new Beverage("Soda", 2.00, 8, true));
    machine->addProduct(new Snack("Candy Bar", 1.75, 15, false));
    machine->addProduct(new Beverage("Water", 1.00, 12, false));
    machine->addProduct(new Snack("Granola Bar", 2.50, 20, true));

    // Display all products and allow selection
    machine->displayProducts();
    double total = machine->selectProducts();
    cout << "\nTotal price for selected products: $" << fixed << setprecision(2) << total << endl;

    // Display cumulative sales and transaction statistics
    VendingMachine::displayTotalSales();
    VendingMachine::displayTransactionStats();

    delete machine;
    return 0;
}
