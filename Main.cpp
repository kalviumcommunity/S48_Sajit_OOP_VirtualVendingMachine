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

public:
    Product(string name, double price) : name(name), price(price), discount(0.0) {}

    void displayInfo() const {
        cout << "Product: " << name << ", Price: $" << fixed << setprecision(2) << price;
        if (discount > 0) {
            cout << ", Discount: " << discount << "%";
        }
        cout << endl;
    }

    void applyDiscount(double discountPercent) {
        discount = discountPercent;
        price *= (1 - discount / 100);
    }

    string getName() const { return name; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }
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
        double total = 0.0;
        char continueChoice;

        do {
            int choice;
            cout << "Enter the number of the product you want (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size())) {
                cout << "Invalid selection. Please choose a number between 1 and " << products.size() << "." << endl;
            } else {
                selectedIndices.push_back(choice - 1);
                total += products[choice - 1].getPrice();
                cout << "You selected: ";
                products[choice - 1].displayInfo();
            }

            cout << "Do you want to select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        cout << "\nYou selected the following products:" << endl;
        for (size_t i = 0; i < selectedIndices.size(); ++i) {
            products[selectedIndices[i]].displayInfo();
        }

        return total;
    }
};

int main() {
    const int NUM_PRODUCTS = 5;
    Product productArray[NUM_PRODUCTS] = {
        Product("Chips", 1.50),
        Product("Candy", 1.00),
        Product("Soda", 2.00),
        Product("Chocolate", 1.75),
        Product("Gum", 0.75)
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
