#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class Product {
private:
    string name;
    double price;
    double discount;
    int stockQuantity;

    // New private method to calculate discounted price
    // This enhances encapsulation by keeping price calculation internal
    double getDiscountedPrice() const {
        return price * (1 - discount / 100);
    }

public:
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), discount(0.0), stockQuantity(stockQuantity) {}

    void displayInfo() const {
        cout << left << setw(15) << name
             // Use getDiscountedPrice() instead of directly accessing price
             << right << setw(10) << "$" << fixed << setprecision(2) << getDiscountedPrice()
             << right << setw(10) << discount << "%"
             << right << setw(10) << stockQuantity << endl;
    }

    // Modified to only set the discount percentage, not modify the price directly
    void applyDiscount(double discountPercent) {
        discount = discountPercent;
        // Removed: price *= (1 - discount / 100);
        // This change maintains the original price and calculates discount when needed
    }

    bool purchase(int purchaseQuantity) {
        if (purchaseQuantity <= stockQuantity) {
            stockQuantity -= purchaseQuantity;
            return true;
        } else {
            cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
            return false;
        }
    }

    // Getter methods - provide controlled access to private members
    string getName() const { return name; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }
    int getStockQuantity() const { return stockQuantity; }
};

class VendingMachine {
private:
    string name;
    vector<Product> products;
    // Changed from static to instance variable to improve encapsulation
    double totalSales;

public:
    // Constructor now initializes totalSales
    VendingMachine(string name) : name(name), totalSales(0.0) {}

    void addProduct(const Product& product) {
        products.push_back(product);
        cout << "Added " << product.getName() << " to " << name << endl;
    }

    void displayProducts() const {
        cout << "\nProducts in " << name << ":\n";
        cout << left << setw(15) << "Product"
             << right << setw(10) << "Price"
             << right << setw(10) << "Discount"
             << right << setw(10) << "Stock" << endl;
        cout << "---------------------------------------------" << endl;
        for (const auto& product : products) {
            product.displayInfo();
        }
    }

    void applyRandomDiscounts() {
        srand(time(0));
        for (auto& product : products) {
            double discount = rand() % 21;
            product.applyDiscount(discount);
        }
    }

    double selectProducts() {
        double total = 0.0;
        char continueChoice;

        do {
            int choice;
            cout << "Enter the number of the product you want (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size())) {
                cout << "Invalid selection. Please choose a number between 1 and " << products.size() << "." << endl;
            } else {
                int quantity;
                cout << "Enter the quantity of " << products[choice - 1].getName() << " you want to purchase: ";
                cin >> quantity;

                if (products[choice - 1].purchase(quantity)) {
                    // Use getDiscountedPrice() method to get the correct price
                    double productTotal = products[choice - 1].getDiscountedPrice() * quantity;
                    total += productTotal;
                    totalSales += productTotal;
                    cout << "You selected: " << products[choice - 1].getName()
                         << " (Quantity: " << quantity << ")\n";
                    cout << "Total for this product: $" << fixed << setprecision(2) << productTotal << endl;
                }
            }

            cout << "Do you want to select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        return total;
    }

    // New method to get total sales, providing controlled access to private data
    double getTotalSales() const {
        return totalSales;
    }
};

int main() {
    // Create VendingMachine on the stack instead of using dynamic allocation
    VendingMachine snackMachine("Snack Machine");

    snackMachine.addProduct(Product("Chips", 1.50, 10));
    snackMachine.addProduct(Product("Candy", 1.00, 15));
    snackMachine.addProduct(Product("Soda", 2.00, 8));
    snackMachine.addProduct(Product("Chocolate", 1.75, 12));
    snackMachine.addProduct(Product("Gum", 0.75, 20));

    snackMachine.displayProducts();
    snackMachine.applyRandomDiscounts();
    cout << "\nAfter applying random discounts:\n" << endl;
    snackMachine.displayProducts();

    double total = snackMachine.selectProducts();
    cout << "\nTotal price: $" << fixed << setprecision(2) << total << endl;

    // Use getTotalSales() method to access total sales
    cout << "\nTotal Sales: $" << fixed << setprecision(2) << snackMachine.getTotalSales() << endl;

    // No need to delete snackMachine as it's not dynamically allocated

    return 0;
}