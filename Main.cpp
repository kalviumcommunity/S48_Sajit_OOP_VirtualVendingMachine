#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Abstract base class for items in the vending machine
class VendingItem {
protected:
    string name;
    double price;
    int stockQuantity;

public:
    // Default constructor
    VendingItem() : name("Unnamed"), price(0.0), stockQuantity(0) {
        cout << "Default constructor for VendingItem called\n";
    }

    // Parameterized constructor
    VendingItem(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {
        cout << "Parameterized constructor for VendingItem called\n";
    }

    // Pure virtual functions define the interface that derived classes must implement
    virtual void displayInfo() const = 0;
    virtual double getPrice() const = 0;
    virtual bool purchase(int quantity) = 0;

    string getName() const { return name; }
    int getStockQuantity() const { return stockQuantity; }

    // Virtual destructor ensures proper cleanup of derived classes
    virtual ~VendingItem() {
        cout << "Destructor for VendingItem called for " << name << endl;
    }
};

// Concrete class inheriting from VendingItem
class Product : public VendingItem {
private:
    double discount;

    // Private method to calculate discounted price
    double getDiscountedPrice() const {
        return price * (1 - discount / 100);
    }

public:
    // Default constructor
    Product() : VendingItem("Unnamed", 0.0, 0), discount(0.0) {
        cout << "Default constructor for Product called\n";
    }

    // Parameterized constructor
    Product(string name, double price, int stockQuantity)
        : VendingItem(name, price, stockQuantity), discount(0.0) {
        cout << "Parameterized constructor for Product called\n";
    }

    // Copy constructor
    Product(const Product& other) : VendingItem(other.name, other.price, other.stockQuantity), discount(other.discount) {
        cout << "Copy constructor for Product called\n";
    }

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

    // Destructor for Product class
    ~Product() override {
        cout << "Destructor for Product called for " << name << endl;
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

    double getTotalSales() const {
        return totalSales;
    }

    // Destructor to clean up dynamically allocated VendingItems
    ~VendingMachine() {
        for (auto item : items) {
            delete item;
        }
        cout << "Destructor for VendingMachine called\n";
    }
};

int main() {
    VendingMachine snackMachine("Snack Machine");

    // Adding products to the vending machine
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