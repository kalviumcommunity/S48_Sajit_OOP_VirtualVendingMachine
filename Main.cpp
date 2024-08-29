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

public:
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), discount(0.0), stockQuantity(stockQuantity) {}

    void displayInfo() const {
        cout << "Product: " << name << ", Price: $" << fixed << setprecision(2) << price;
        if (discount > 0) {
            cout << ", Discount: " << discount << "%";
        }
        cout << ", Stock Quantity: " << stockQuantity << endl;
    }

    void applyDiscount(double discountPercent) {
        discount = discountPercent;
        price *= (1 - discount / 100);
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

    string getName() const { return name; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }
    int getStockQuantity() const { return stockQuantity; }
};

class VendingMachine {
private:
    string name;
    vector<Product> products;

public:
    VendingMachine(string name) : name(name) {}

    void addProduct(const Product& product) {
        products.push_back(product);
        cout << "Added " << product.getName() << " to " << name << endl;
    }

    void displayProducts() const {
        cout << "Products in " << name << ":" << endl;
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". ";
            products[i].displayInfo();
        }
    }

    void applyRandomDiscounts() {
        srand(time(0));
        for (size_t i = 0; i < products.size(); ++i) {
            double discount = rand() % 21; // Random discount between 0% and 20%
            products[i].applyDiscount(discount);
        }
    }

    double selectProducts() {
        vector<int> selectedIndices;
        vector<int> quantities;
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
                    selectedIndices.push_back(choice - 1);
                    quantities.push_back(quantity);
                    total += products[choice - 1].getPrice() * quantity;
                    cout << "You selected: " << products[choice - 1].getName()
                         << " (Quantity: " << quantity << ")\n";
                }
            }

            cout << "Do you want to select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        cout << "\nYou selected the following products:" << endl;
        for (size_t i = 0; i < selectedIndices.size(); ++i) {
            cout << "Product: " << products[selectedIndices[i]].getName()
                 << ", Price: $" << fixed << setprecision(2) << products[selectedIndices[i]].getPrice()
                 << ", Discount: " << products[selectedIndices[i]].getDiscount() << "%"
                 << ", Quantity: " << quantities[i] << endl;
        }

        return total;
    }
};

int main() {
    const int NUM_PRODUCTS = 5;
    Product productArray[NUM_PRODUCTS] = {
        Product("Chips", 1.50, 10),
        Product("Candy", 1.00, 15),
        Product("Soda", 2.00, 8),
        Product("Chocolate", 1.75, 12),
        Product("Gum", 0.75, 20)
    };

    VendingMachine snackMachine("Snack Machine");

    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        snackMachine.addProduct(productArray[i]);
    }

    snackMachine.displayProducts();
    snackMachine.applyRandomDiscounts();
    cout << "\nAfter applying random discounts:\n" << endl;
    snackMachine.displayProducts();

    double total = snackMachine.selectProducts();

    cout << "\nTotal price: $" << fixed << setprecision(2) << total << endl;

    return 0;
}
