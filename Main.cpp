#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract Base Product class implementing core functionality
// Made abstract by including pure virtual functions
class Product {
protected:
    string name;
    double price;
    int stockQuantity;

public:
    // Example of Constructor Overloading
    Product() : name("Unknown"), price(0.0), stockQuantity(0) {}
    Product(string name, double price) : name(name), price(price), stockQuantity(0) {}
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {}

    // Pure virtual functions - make Product an abstract class
    // Each derived class must implement these
    virtual void displayInfo() const = 0;
    virtual double calculatePrice() const = 0;

    // Regular virtual functions - can be overridden by derived classes
    virtual bool isAvailable() const {
        return stockQuantity > 0;
    }

    virtual string getCategory() const {
        return "General Product";
    }

    // Function Overloading - different ways to update price
    void updatePrice(double newPrice) {
        price = newPrice;
    }

    void updatePrice(double newPrice, double discount) {
        price = newPrice * (1 - discount/100);
    }

    void updatePrice(string currency, double newPrice) {
        if(currency == "EUR") {
            price = newPrice * 1.1;  // EUR to USD
        } else if(currency == "GBP") {
            price = newPrice * 1.27; // GBP to USD
        } else {
            price = newPrice;
        }
    }

    bool purchase(int quantity) {
        if (quantity <= stockQuantity) {
            stockQuantity -= quantity;
            return true;
        }
        cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
        return false;
    }

    double getPrice() const { return price; }
    string getName() const { return name; }

    // Operator Overloading for stock management
    Product& operator+=(int quantity) {
        stockQuantity += quantity;
        return *this;
    }

    Product& operator-=(int quantity) {
        if(stockQuantity >= quantity) {
            stockQuantity -= quantity;
        }
        return *this;
    }

    // Virtual destructor for proper cleanup of derived classes
    virtual ~Product() {}
};

// Derived class implementing the abstract class Product
class DiscountedProduct : public Product {
private:
    double discount;

public:
    DiscountedProduct(string name, double price, int stockQuantity, double discount)
        : Product(name, price, stockQuantity), discount(discount) {}

    // Implementation of pure virtual function - required by abstract class
    void displayInfo() const override {
        cout << "Discounted Product: " << name
             << "\n  Original Price: $" << fixed << setprecision(2) << price
             << "\n  Discount: " << discount << "%"
             << "\n  Final Price: $" << calculatePrice()
             << "\n  Stock: " << stockQuantity << endl;
    }

    // Implementation of pure virtual function for price calculation
    double calculatePrice() const override {
        return price * (1 - discount / 100);
    }

    // Override of regular virtual function
    string getCategory() const override {
        return "Discounted Item";
    }
};

// Another derived class implementing the abstract class Product
class Beverage : public Product {
private:
    bool isCarbonated;
    double volume;  // in liters

public:
    // Constructor Overloading with different parameter sets
    Beverage(string name, double price, int stockQuantity, bool isCarbonated, double volume)
        : Product(name, price, stockQuantity), isCarbonated(isCarbonated), volume(volume) {}

    // Implementation of pure virtual function - required by abstract class
    void displayInfo() const override {
        cout << "Beverage: " << name
             << "\n  Price: $" << fixed << setprecision(2) << calculatePrice()
             << "\n  Volume: " << volume << "L"
             << "\n  Type: " << (isCarbonated ? "Carbonated" : "Non-carbonated")
             << "\n  Stock: " << stockQuantity << endl;
    }

    // Implementation of pure virtual price calculation
    double calculatePrice() const override {
        // Premium pricing for carbonated drinks
        return isCarbonated ? price * 1.1 : price;
    }

    // Override of regular virtual functions
    string getCategory() const override {
        return isCarbonated ? "Carbonated Beverage" : "Non-carbonated Beverage";
    }

    bool isAvailable() const override {
        return stockQuantity > 0 && volume > 0;
    }

    // Function Overloading for volume updates
    void updateVolume(double newVolume) {
        volume = newVolume;
    }

    void updateVolume(int milliliters) {
        volume = milliliters / 1000.0;
    }
};

// VendingMachine class manages the product inventory
class VendingMachine {
private:
    string name;
    vector<Product*> products;  // Polymorphic container of abstract class pointers
    static double totalSales;
    static int totalTransactions;

public:
    VendingMachine(string name) : name(name) {}

    void addProduct(Product* product) {
        products.push_back(product);
        // Using virtual function getCategory()
        cout << "Added " << product->getName()
             << " (" << product->getCategory() << ")" << endl;
    }

    void displayProducts() const {
        cout << "\nProducts in " << name << ":\n" << endl;
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". ";
            // Using pure virtual functions through abstract class pointer
            products[i]->displayInfo();
            // Using virtual function isAvailable()
            cout << "   Status: " << (products[i]->isAvailable() ? "Available" : "Unavailable")
                 << "\n" << endl;
        }
    }

    double selectProducts() {
        double total = 0.0;
        char continueChoice;
        bool purchaseMade = false;

        do {
            int choice;
            cout << "Enter product number (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size())) {
                cout << "Invalid selection." << endl;
                continue;
            }

            // Using virtual function for availability check
            if (!products[choice - 1]->isAvailable()) {
                cout << "Product currently unavailable." << endl;
                continue;
            }

            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (products[choice - 1]->purchase(quantity)) {
                // Using pure virtual function for price calculation
                double itemTotal = products[choice - 1]->calculatePrice() * quantity;
                total += itemTotal;
                purchaseMade = true;
                cout << "Subtotal: $" << fixed << setprecision(2) << itemTotal << endl;
            }

            cout << "Select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        if (purchaseMade) {
            totalSales += total;
            totalTransactions++;
        }

        return total;
    }

    static void displayTotalSales() {
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    static void displayTransactionStats() {
        cout << "Total Transactions: " << totalTransactions << endl;
    }
};

double VendingMachine::totalSales = 0.0;
int VendingMachine::totalTransactions = 0;

int main() {
    VendingMachine* machine = new VendingMachine("Smart Vending");

    // Creating different types of products demonstrating abstract class implementation
    machine->addProduct(new DiscountedProduct("Lays Chips", 2.50, 10, 15));        // 15% off
    machine->addProduct(new Beverage("Coca Cola", 2.00, 12, true, 0.33));          // carbonated, 330ml
    machine->addProduct(new DiscountedProduct("Protein Bar", 3.50, 8, 10));        // 10% off
    machine->addProduct(new Beverage("Mineral Water", 1.50, 15, false, 0.5));      // non-carbonated, 500ml
    machine->addProduct(new Beverage("Monster Energy", 3.50, 10, true, 0.473));    // carbonated, 473ml

    cout << "\n=== Welcome to Smart Vending ===\n";
    machine->displayProducts();
    double total = machine->selectProducts();
    cout << "\nTotal amount: $" << fixed << setprecision(2) << total << endl;

    cout << "\n=== Sales Statistics ===\n";
    VendingMachine::displayTotalSales();
    VendingMachine::displayTransactionStats();

    delete machine;
    return 0;
}