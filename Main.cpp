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
    double discount;

public:
    Product(string name, double price, int stockQuantity)
    }

    // Process purchase and reduce stock if available
    bool purchase(int quantity) {
        if (quantity <= stockQuantity) {
            stockQuantity -= quantity;
            return true;
        } else {
            return false;
        }   
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
            cout << "Enter the number of the item you want (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size()) || choice <= 0) {
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

            cout << "Do you want to select another item? (y/n): ";
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
    VendingMachine::displayTotalSales();
    return 0;
}