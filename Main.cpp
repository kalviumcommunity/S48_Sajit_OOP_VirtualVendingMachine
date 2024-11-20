#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Price calculator class - handles all price-related calculations
class PriceCalculator {
public:
    static double calculateDiscountedPrice(double originalPrice, double discount) {
        return originalPrice * (1 - discount / 100);
    }

    static double convertCurrency(string currency, double price) {
        if(currency == "EUR") {
            return price * 1.1;  // EUR to USD
        } else if(currency == "GBP") {
            return price * 1.27; // GBP to USD
        }
        return price;
    }
};

// Inventory manager class - handles stock-related operations
class InventoryManager {
public:
    static bool checkAvailability(int requestedQuantity, int currentStock) {
        return requestedQuantity <= currentStock;
    }

    static int updateStock(int currentStock, int quantity, bool isAddition) {
        if(isAddition) {
            return currentStock + quantity;
        } else if(currentStock >= quantity) {
            return currentStock - quantity;
        }
        return currentStock;
    }
};

// Abstract Base Product class implementing core functionality
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
    virtual void displayInfo() const = 0;
    virtual double calculatePrice() const = 0;
    virtual string getCategory() const = 0;

    // Virtual function with default implementation
    virtual bool isAvailable() const {
        return stockQuantity > 0;
    }

    // Function Overloading - different ways to update price
    void updatePrice(double newPrice) {
        price = newPrice;
    }

    void updatePrice(double newPrice, double discount) {
        price = PriceCalculator::calculateDiscountedPrice(newPrice, discount);
    }

    void updatePrice(string currency, double newPrice) {
        price = PriceCalculator::convertCurrency(currency, newPrice);
    }

    bool purchase(int quantity) {
        if (InventoryManager::checkAvailability(quantity, stockQuantity)) {
            stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, false);
            return true;
        }
        cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
        return false;
    }

    double getPrice() const { return price; }
    string getName() const { return name; }

    // Operator Overloading for stock management
    Product& operator+=(int quantity) {
        stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, true);
        return *this;
    }

    Product& operator-=(int quantity) {
        stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, false);
        return *this;
    }

    virtual ~Product() {}
};

// Derived class for discounted products
class DiscountedProduct : public Product {
private:
    double discount;

public:
    DiscountedProduct(string name, double price, int stockQuantity, double discount)
        : Product(name, price, stockQuantity), discount(discount) {}

    void displayInfo() const override {
        cout << "Discounted Product: " << name
             << "\n  Original Price: $" << fixed << setprecision(2) << price
             << "\n  Discount: " << discount << "%"
             << "\n  Final Price: $" << calculatePrice()
             << "\n  Stock: " << stockQuantity << endl;
    }

    double calculatePrice() const override {
        return PriceCalculator::calculateDiscountedPrice(price, discount);
    }

    string getCategory() const override {
        return "Discounted Item";
    }
};

// Derived class for beverages
class Beverage : public Product {
private:
    bool isCarbonated;
    double volume;  // in liters

public:
    Beverage(string name, double price, int stockQuantity, bool isCarbonated, double volume)
        : Product(name, price, stockQuantity), isCarbonated(isCarbonated), volume(volume) {}

    void displayInfo() const override {
        cout << "Beverage: " << name
             << "\n  Price: $" << fixed << setprecision(2) << calculatePrice()
             << "\n  Volume: " << volume << "L"
             << "\n  Type: " << (isCarbonated ? "Carbonated" : "Non-carbonated")
             << "\n  Stock: " << stockQuantity << endl;
    }

    double calculatePrice() const override {
        return isCarbonated ? price * 1.1 : price;  // 10% premium for carbonated drinks
    }

    string getCategory() const override {
        return isCarbonated ? "Carbonated Beverage" : "Non-carbonated Beverage";
    }

    bool isAvailable() const override {
        return stockQuantity > 0 && volume > 0;
    }

    void updateVolume(double newVolume) {
        volume = newVolume;
    }

    void updateVolume(int milliliters) {
        volume = milliliters / 1000.0;
    }
};

// New derived class for limited time products
class LimitedTimeProduct : public Product {
private:
    time_t expiryDate;
    double specialPrice;

public:
    LimitedTimeProduct(string name, double price, int stockQuantity,
                      double specialPrice, int daysValid)
        : Product(name, price, stockQuantity),
          specialPrice(specialPrice) {
        expiryDate = time(0) + (daysValid * 24 * 60 * 60);
    }

    void displayInfo() const override {
        time_t now = time(0);
        int daysLeft = (expiryDate - now) / (24 * 60 * 60);

        cout << "Limited Time Product: " << name
             << "\n  Regular Price: $" << fixed << setprecision(2) << price
             << "\n  Special Price: $" << calculatePrice()
             << "\n  Days Left: " << daysLeft
             << "\n  Stock: " << stockQuantity << endl;
    }

    double calculatePrice() const override {
        time_t now = time(0);
        return now < expiryDate ? specialPrice : price;
    }

    string getCategory() const override {
        return "Limited Time Offer";
    }

    bool isAvailable() const override {
        return stockQuantity > 0 && time(0) < expiryDate;
    }
};

// Sales tracker class
class SalesTracker {
private:
    static double totalSales;
    static int totalTransactions;

public:
    static void recordSale(double amount) {
        totalSales += amount;
        totalTransactions++;
    }

    static void displayTotalSales() {
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    static void displayTransactionStats() {
        cout << "Total Transactions: " << totalTransactions << endl;
    }
};

double SalesTracker::totalSales = 0.0;
int SalesTracker::totalTransactions = 0;

// VendingMachine class manages the product inventory
class VendingMachine {
private:
    string name;
    vector<Product*> products;

public:
    VendingMachine(string name) : name(name) {}

    void addProduct(Product* product) {
        products.push_back(product);
        cout << "Added " << product->getName()
             << " (" << product->getCategory() << ")" << endl;
    }

    void displayProducts() const {
        cout << "\nProducts in " << name << ":\n" << endl;
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". ";
            products[i]->displayInfo();
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

            if (!products[choice - 1]->isAvailable()) {
                cout << "Product currently unavailable." << endl;
                continue;
            }

            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (products[choice - 1]->purchase(quantity)) {
                double itemTotal = products[choice - 1]->calculatePrice() * quantity;
                total += itemTotal;
                purchaseMade = true;
                cout << "Subtotal: $" << fixed << setprecision(2) << itemTotal << endl;
            }

            cout << "Select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        if (purchaseMade) {
            SalesTracker::recordSale(total);
        }

        return total;
    }

    ~VendingMachine() {
        for (auto product : products) {
            delete product;
        }
    }
};

int main() {
    VendingMachine* machine = new VendingMachine("Smart Vending");

    // Adding regular products
    machine->addProduct(new DiscountedProduct("Lays Chips", 2.50, 10, 15));        // 15% off
    machine->addProduct(new Beverage("Coca Cola", 2.00, 12, true, 0.33));          // carbonated, 330ml
    machine->addProduct(new DiscountedProduct("Protein Bar", 3.50, 8, 10));        // 10% off
    machine->addProduct(new Beverage("Mineral Water", 1.50, 15, false, 0.5));      // non-carbonated, 500ml
    machine->addProduct(new Beverage("Monster Energy", 3.50, 10, true, 0.473));    // carbonated, 473ml

    // Adding a new type of product (Limited Time Offer)
    machine->addProduct(new LimitedTimeProduct("Special Snack", 5.00, 5, 3.99, 7)); // 7-day offer

    cout << "\n=== Welcome to Smart Vending ===\n";
    machine->displayProducts();
    double total = machine->selectProducts();
    cout << "\nTotal amount: $" << fixed << setprecision(2) << total << endl;

    cout << "\n=== Sales Statistics ===\n";
    SalesTracker::displayTotalSales();
    SalesTracker::displayTransactionStats();

    delete machine;
    return 0;
}