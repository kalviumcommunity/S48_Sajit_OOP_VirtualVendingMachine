#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract base class for items in the vending machine
// This class demonstrates abstraction by defining a common interface for all vending items
class VendingItem {
protected:
    // Protected members are accessible in derived classes, but not outside the class hierarchy
    string name;
    double price;
    int stockQuantity;

public:
    // Constructor
    VendingItem(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {}

    // Pure virtual functions define the interface that derived classes must implement
    virtual void displayInfo() const = 0; // Pure virtual function
    virtual double getPrice() const = 0; // Pure virtual function
    virtual bool purchase(int quantity) = 0; // Pure virtual function

    // Common getter methods
    string getName() const { return name; }
    int getStockQuantity() const { return stockQuantity; }

    // Virtual destructor ensures proper cleanup of derived classes
    virtual ~VendingItem() {}
};

// Concrete class inheriting from VendingItem
// This class provides a specific implementation of the VendingItem interface
class Product : public VendingItem {
private:
    double discount;

    // Private method to calculate discounted price
    double getDiscountedPrice() const {
        return price * (1 - discount / 100);
    }

public:
    // Constructor
    Product(string name, double price, int stockQuantity)
        : VendingItem(name, price, stockQuantity), discount(0.0) {}

    // Implementation of pure virtual functions from VendingItem
    void displayInfo() const override {
        cout << left << setw(15) << name
             << right << setw(10) << "$" << fixed << setprecision(2) << getDiscountedPrice()
             << right << setw(10) << discount << "%"
             << right << setw(10) << stockQuantity << endl;
    }

    double getPrice() const override {
        return getDiscountedPrice();
    }

    bool purchase(int quantity) override {
        if (quantity <= stockQuantity) {
            stockQuantity -= quantity;
            return true;
        }
        return false;
    }

    // Product-specific method
    void applyDiscount(double discountPercent) {
        discount = discountPercent;
    }
};

// VendingMachine class that works with the abstract VendingItem
class VendingMachine {
private:
    string name;
    vector<VendingItem*> items; // Using pointers to VendingItem allows for polymorphism
    double totalSales;

public:
    VendingMachine(string name) : name(name), totalSales(0.0) {}

    // Add an item to the vending machine
    void addItem(VendingItem* item) {
        items.push_back(item);
        cout << "Added " << item->getName() << " to " << name << endl;
    }

    // Display all items in the vending machine
    void displayItems() const {
        cout << "\nItems in " << name << ":\n";
        cout << left << setw(15) << "Item"
             << right << setw(10) << "Price"
             << right << setw(10) << "Discount"
             << right << setw(10) << "Stock" << endl;
        cout << "---------------------------------------------" << endl;
        for (const auto& item : items) {
            item->displayInfo(); // Polymorphic call to displayInfo
        }
    }

    // Apply random discounts to products
    void applyRandomDiscounts() {
        srand(time(0));
        for (auto& item : items) {
            // Dynamic casting to check if the item is a Product
            Product* product = dynamic_cast<Product*>(item);
            if (product) {
                double discount = rand() % 21;
                product->applyDiscount(discount);
            }
        }
    }

    // Allow user to select and purchase items
    double selectItems() {
        double total = 0.0;
        char continueChoice;

        do {
            int choice;
            cout << "Enter the number of the item you want (1-" << items.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(items.size())) {
                cout << "Invalid selection. Please choose a number between 1 and " << items.size() << "." << endl;
            } else {
                int quantity;
                cout << "Enter the quantity of " << items[choice - 1]->getName() << " you want to purchase: ";
                cin >> quantity;

                // Attempt to purchase the item
                if (items[choice - 1]->purchase(quantity)) {
                    double itemTotal = items[choice - 1]->getPrice() * quantity;
                    total += itemTotal;
                    totalSales += itemTotal;
                    cout << "You selected: " << items[choice - 1]->getName()
                         << " (Quantity: " << quantity << ")\n";
                    cout << "Total for this item: $" << fixed << setprecision(2) << itemTotal << endl;
                } else {
                    cout << "Sorry, not enough " << items[choice - 1]->getName() << " in stock." << endl;
                }
            }

            cout << "Do you want to select another item? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        return total;
    }

    // Getter for total sales
    double getTotalSales() const {
        return totalSales;
    }

    // Destructor to clean up dynamically allocated VendingItems
    ~VendingMachine() {
        for (auto item : items) {
            delete item;
        }
    }
};

int main() {
    VendingMachine snackMachine("Snack Machine");

    // Adding products to the vending machine
    // Note that we're adding Products, but the VendingMachine stores them as VendingItems
    snackMachine.addItem(new Product("Chips", 1.50, 10));
    snackMachine.addItem(new Product("Candy", 1.00, 15));
    snackMachine.addItem(new Product("Soda", 2.00, 8));
    snackMachine.addItem(new Product("Chocolate", 1.75, 12));
    snackMachine.addItem(new Product("Gum", 0.75, 20));

    snackMachine.displayItems();
    snackMachine.applyRandomDiscounts();
    cout << "\nAfter applying random discounts:\n" << endl;
    snackMachine.displayItems();

    double total = snackMachine.selectItems();
    cout << "\nTotal price: $" << fixed << setprecision(2) << total << endl;

    cout << "\nTotal Sales: $" << fixed << setprecision(2) << snackMachine.getTotalSales() << endl;

    return 0;
}