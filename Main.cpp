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
    // Method to calculate the discounted price based on a percentage discount
    static double calculateDiscountedPrice(double originalPrice, double discount) {
        return originalPrice * (1 - discount / 100);
    }

    // Method to convert the price to a different currency (EUR, GBP to USD)
    static double convertCurrency(string currency, double price) {
        if(currency == "EUR") {
            return price * 1.1;  // EUR to USD
        } else if(currency == "GBP") {
            return price * 1.27; // GBP to USD
        }
        return price;  // Default is USD
    }
};

// Inventory manager class - handles stock-related operations
class InventoryManager {
public:
    // Method to check if the requested quantity is available in stock
    static bool checkAvailability(int requestedQuantity, int currentStock) {
        return requestedQuantity <= currentStock;
    }

    // Method to update stock (add or subtract quantity)
    static int updateStock(int currentStock, int quantity, bool isAddition) {
        if(isAddition) {
            return currentStock + quantity;
        } else if(currentStock >= quantity) {
            return currentStock - quantity;
        }
        return currentStock;  // Return unchanged stock if there's insufficient stock
    }
};

// Abstract Base Product class implementing core functionality
class Product {
protected:
    string name;  // Product name
    double price; // Price of the product
    int stockQuantity; // Stock quantity of the product

public:
    // Default and parameterized constructors for initialization
    Product() : name("Unknown"), price(0.0), stockQuantity(0) {}
    Product(string name, double price) : name(name), price(price), stockQuantity(0) {}
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {}

    // Pure virtual functions - make Product an abstract class
    virtual void displayInfo() const = 0;  // Display product information
    virtual double calculatePrice() const = 0;  // Calculate the product price
    virtual string getCategory() const = 0;  // Get the product category

    // Virtual function with default implementation
    virtual bool isAvailable() const {
        return stockQuantity > 0;  // Available if stock is greater than 0
    }

    // Function Overloading - different ways to update the price
    void updatePrice(double newPrice) {
        price = newPrice;
    }

    void updatePrice(double newPrice, double discount) {
        price = PriceCalculator::calculateDiscountedPrice(newPrice, discount);
    }

    void updatePrice(string currency, double newPrice) {
        price = PriceCalculator::convertCurrency(currency, newPrice);
    }

    // Purchase method to check availability and update stock
    bool purchase(int quantity) {
        if (InventoryManager::checkAvailability(quantity, stockQuantity)) {
            stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, false);
            return true;
        }
        cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
        return false;
    }

    double getPrice() const { return price; } // Return the price of the product
    string getName() const { return name; }  // Return the name of the product

    // Operator Overloading for stock management (addition and subtraction)
    Product& operator+=(int quantity) {
        stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, true);
        return *this;
    }

    Product& operator-=(int quantity) {
        stockQuantity = InventoryManager::updateStock(stockQuantity, quantity, false);
        return *this;
    }

    virtual ~Product() {}  // Virtual destructor to allow proper cleanup
};

// Derived class for discounted products
class DiscountedProduct : public Product {
private:
    double discount;  // Discount percentage for the product

public:
    DiscountedProduct(string name, double price, int stockQuantity, double discount)
        : Product(name, price, stockQuantity), discount(discount) {}

    // Display information about the discounted product
    void displayInfo() const override {
        cout << "Discounted Product: " << name
             << "\n  Original Price: $" << fixed << setprecision(2) << price
             << "\n  Discount: " << discount << "%"
             << "\n  Final Price: $" << calculatePrice()
             << "\n  Stock: " << stockQuantity << endl;
    }

    // Calculate the discounted price
    double calculatePrice() const override {
        return PriceCalculator::calculateDiscountedPrice(price, discount);
    }

    string getCategory() const override {
        return "Discounted Item";  // Category for discounted product
    }

    // Override to check if the discounted product is available
    bool isAvailable() const override {
        return stockQuantity > 0;
    }
};

// Derived class for beverages (could be carbonated or not)
class Beverage : public Product {
private:
    bool isCarbonated;  // Whether the beverage is carbonated
    double volume;      // Volume of the beverage in liters

public:
    Beverage(string name, double price, int stockQuantity, bool isCarbonated, double volume)
        : Product(name, price, stockQuantity), isCarbonated(isCarbonated), volume(volume) {}

    // Display information about the beverage
    void displayInfo() const override {
        cout << "Beverage: " << name
             << "\n  Price: $" << fixed << setprecision(2) << calculatePrice()
             << "\n  Volume: " << volume << "L"
             << "\n  Type: " << (isCarbonated ? "Carbonated" : "Non-carbonated")
             << "\n  Stock: " << stockQuantity << endl;
    }

    // Calculate the price, with a premium for carbonated beverages
    double calculatePrice() const override {
        return isCarbonated ? price * 1.1 : price;  // 10% premium for carbonated drinks
    }

    string getCategory() const override {
        return isCarbonated ? "Carbonated Beverage" : "Non-carbonated Beverage";
    }

    // Override to check if the beverage is available
    bool isAvailable() const override {
        return stockQuantity > 0 && volume > 0;
    }

    // Update volume in liters
    void updateVolume(double newVolume) {
        volume = newVolume;
    }

    // Update volume in milliliters (convert to liters)
    void updateVolume(int milliliters) {
        volume = milliliters / 1000.0;
    }
};

// New derived class for limited time products (with expiration)
class LimitedTimeProduct : public Product {
private:
    time_t expiryDate;   // Expiry date (in time_t format)
    double specialPrice; // Special price during the offer period

public:
    LimitedTimeProduct(string name, double price, int stockQuantity,
                      double specialPrice, int daysValid)
        : Product(name, price, stockQuantity),
          specialPrice(specialPrice) {
        expiryDate = time(0) + (daysValid * 24 * 60 * 60); // Calculate the expiry date
    }

    // Display information about the limited-time product
    void displayInfo() const override {
        time_t now = time(0);
        int daysLeft = (expiryDate - now) / (24 * 60 * 60);  // Calculate remaining days

        cout << "Limited Time Product: " << name
             << "\n  Regular Price: $" << fixed << setprecision(2) << price
             << "\n  Special Price: $" << calculatePrice()
             << "\n  Days Left: " << daysLeft
             << "\n  Stock: " << stockQuantity << endl;
    }

    // Calculate price, with special pricing if within the valid period
    double calculatePrice() const override {
        time_t now = time(0);
        return now < expiryDate ? specialPrice : price; // Special price if within valid date range
    }

    string getCategory() const override {
        return "Limited Time Offer";  // Category for limited-time products
    }

    // Override to check if the limited-time product is available
    bool isAvailable() const override {
        return stockQuantity > 0 && time(0) < expiryDate;  // Check expiration and stock
    }
};

// Sales tracker class to track total sales and transactions
class SalesTracker {
private:
    static double totalSales;        // Total sales value
    static int totalTransactions;    // Total number of transactions

public:
    // Record a sale, updating the total sales and transactions
    static void recordSale(double amount) {
        totalSales += amount;
        totalTransactions++;
    }

    // Display total sales so far
    static void displayTotalSales() {
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    // Display the number of transactions made
    static void displayTransactionStats() {
        cout << "Total Transactions: " << totalTransactions << endl;
    }
};

// Initialize static variables for sales tracker
double SalesTracker::totalSales = 0.0;
int SalesTracker::totalTransactions = 0;

// Vending Machine class to handle products and user interaction
class VendingMachine {
private:
    string name;  // Name of the vending machine
    vector<Product*> products;  // List of products in the machine

public:
    VendingMachine(string name) : name(name) {}

    // Add a product to the vending machine
    void addProduct(Product* product) {
        products.push_back(product);
    }

    // Display all products in the vending machine
    void displayProducts() const {
        cout << "\nWelcome to " << name << "!\n";
        for (const auto& product : products) {
            product->displayInfo();
            cout << "----------------------------\n";
        }
    }

    // Let the user select and purchase products
    double selectProducts() {
        double total = 0.0;
        int productChoice, quantity;
        bool purchaseMade = false;

        cout << "\nSelect a product to purchase (0 to exit): ";
        while (cin >> productChoice && productChoice != 0) {
            if (productChoice > 0 && productChoice <= products.size()) {
                cout << "Enter quantity: ";
                cin >> quantity;
                if (products[productChoice - 1]->purchase(quantity)) {
                    total += products[productChoice - 1]->calculatePrice() * quantity;
                    purchaseMade = true;
                }
            }
            cout << "\nSelect another product or 0 to exit: ";
        }

        // Record the sale if purchase was made
        if (purchaseMade) {
            SalesTracker::recordSale(total);
        }

        return total;
    }

    // Destructor to clean up dynamically allocated memory
    ~VendingMachine() {
        for (auto product : products) {
            delete product;
        }
    }
};

// Main program to simulate vending machine usage
int main() {
    srand(time(0));  // Seed for random number generation

    VendingMachine machine("The Ultimate Vending Machine");

    // Add various products to the vending machine
    machine.addProduct(new DiscountedProduct("Laptop", 1200.00, 5, 15));  // 15% discount
    machine.addProduct(new Beverage("Coke", 1.50, 20, true, 0.5));        // 500ml Carbonated
    machine.addProduct(new LimitedTimeProduct("Smartwatch", 300.00, 10, 250.00, 7));  // Special price for 7 days

    machine.displayProducts();  // Display all products in the vending machine
    double total = machine.selectProducts();  // Let the user make purchases

    // Display total purchase amount and sales statistics
    cout << "\nTotal: $" << fixed << setprecision(2) << total << endl;
    SalesTracker::displayTotalSales();
    SalesTracker::displayTransactionStats();

    return 0;
}
