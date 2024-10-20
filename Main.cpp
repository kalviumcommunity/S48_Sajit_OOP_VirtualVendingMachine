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
    VendingItem(string name, double price, int stockQuantity)
        : name(name), price(price), stockQuantity(stockQuantity) {}

    virtual void displayInfo() const = 0; // Pure virtual function
    virtual double getPrice() const = 0; // Pure virtual function
    virtual bool purchase(int quantity) = 0; // Pure virtual function

    string getName() const { return name; }
    int getStockQuantity() const { return stockQuantity; }

    virtual ~VendingItem() {} // Silent destructor
};

// Concrete class inheriting from VendingItem
class Product : public VendingItem {
private:
    double discount;

    double getDiscountedPrice() const {
        return price * (1 - discount / 100);
    }

public:
    Product(string name, double price, int stockQuantity)
        : VendingItem(name, price, stockQuantity), discount(0.0) {}

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

    void applyDiscount(double discountPercent) {
        discount = discountPercent;
    }

    double getDiscount() const {
        return discount;
    }

    ~Product() override {} // Silent destructor
};

// VendingMachine class that works with the abstract VendingItem
class VendingMachine {
private:
    string name;
    vector<VendingItem*> items; // Using pointers to VendingItem allows for polymorphism
    double totalSales;

public:
    VendingMachine(string name) : name(name), totalSales(0.0) {}

    void addItem(VendingItem* item) {
        items.push_back(item);
        cout << "Added " << item->getName() << " to " << name << endl;
    }

    void displayItems() const {
        cout << "\nItems in " << name << ":\n";
        cout << left << setw(15) << "Item"
             << right << setw(10) << "Price"
             << right << setw(10) << "Discount"
             << right << setw(10) << "Stock" << endl;
        cout << "---------------------------------------------" << endl;
        for (const auto& item : items) {
            item->displayInfo();
        }
    }

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

    // Structure to hold purchased product details
    struct PurchasedProduct {
        string productName;
        double productPrice;
        double discount;
        int quantity;
        double totalProductPrice;
    };

    double selectItems() {
        double total = 0.0;
        char continueChoice;
        vector<PurchasedProduct> purchases; // Vector to track purchased products

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

                    // Store the purchase details in the purchases vector
                    PurchasedProduct purchase = {
                        items[choice - 1]->getName(),
                        items[choice - 1]->getPrice(),
                        static_cast<Product*>(items[choice - 1])->getDiscount(),
                        quantity,
                        itemTotal
                    };
                    purchases.push_back(purchase);

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

        // Display summary of purchased products
        cout << "\nYou selected the following products:\n";
        for (const auto& purchase : purchases) {
            cout << "Product: " << purchase.productName
                 << ", Price: $" << fixed << setprecision(2) << purchase.productPrice
                 << ", Discount: " << purchase.discount << "%"
                 << ", Quantity: " << purchase.quantity << endl;
            cout << "Total Product Price: $" << fixed << setprecision(2) << purchase.totalProductPrice << endl;
        }

        return total;
    }

    double getTotalSales() const {
        return totalSales;
    }

    ~VendingMachine() {
        for (auto item : items) {
            delete item;
        }
    }
};

int main() {
    VendingMachine snackMachine("Snack Machine");

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
    cout << "\nTotal Price: $" << fixed << setprecision(2) << total << endl;

    cout << "\nTotal Sales: $" << fixed << setprecision(2) << snackMachine.getTotalSales() << endl;

    return 0;
}
