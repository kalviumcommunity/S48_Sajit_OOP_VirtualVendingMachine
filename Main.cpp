#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class to represent a product in the vending machine
class Product {
private:
    string name;
    double price;
    double discount;
    int stockQuantity;

public:
    // Constructor to initialize the product with name, price, and stock quantity
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), discount(0.0), stockQuantity(stockQuantity) {}

    // Function to display product information including name, price, discount, and stock quantity
    void displayInfo() const {
        cout << "Product: " << name << ", Price: $" << fixed << setprecision(2) << price;
        if (discount > 0) {
            cout << ", Discount: " << discount << "%";
        }
        cout << ", Stock Quantity: " << stockQuantity << endl;
    }

    // Function to apply a discount to the product
    void applyDiscount(double discountPercent) {
        discount = discountPercent;
        price *= (1 - discount / 100);
    }

    // Function to handle the purchase of the product
    // Returns true if the purchase is successful, false if there isn't enough stock
    bool purchase(int purchaseQuantity) {
        if (purchaseQuantity <= stockQuantity) {
            stockQuantity -= purchaseQuantity; // Reduce stock by the purchased quantity
            return true; // Purchase successful
        } else {
            cout << "Sorry, not enough " << name << " in stock. Available: " << stockQuantity << endl;
            return false; // Purchase failed due to insufficient stock
        }
    }

    // Getter functions to access private members
    string getName() const { return name; }
    double getPrice() const { return price; }
    double getDiscount() const { return discount; }
    int getStockQuantity() const { return stockQuantity; }
};

// Class to represent a vending machine that holds a collection of products
class VendingMachine {
private:
    string name;
    vector<Product> products;

public:
    // Constructor to initialize the vending machine with a name
    VendingMachine(string name) : name(name) {}

    // Function to add a product to the vending machine
    void addProduct(const Product& product) {
        products.push_back(product);
        cout << "Added " << product.getName() << " to " << name << endl;
    }

    // Function to display all the products in the vending machine
    void displayProducts() const {
        cout << "Products in " << name << ":" << endl;
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". ";
            products[i].displayInfo();
        }
    }

    // Function to apply random discounts to all products in the vending machine
    void applyRandomDiscounts() {
        srand(time(0));
        for (size_t i = 0; i < products.size(); ++i) {
            double discount = rand() % 21; // Random discount between 0% and 20%
            products[i].applyDiscount(discount);
        }
    }

    // Function to allow the user to select and purchase products
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
                // Handle invalid product selection
                cout << "Invalid selection. Please choose a number between 1 and " << products.size() << "." << endl;
            } else {
                // Handle valid product selection
                int quantity;
                cout << "Enter the quantity of " << products[choice - 1].getName() << " you want to purchase: ";
                cin >> quantity;

                // Attempt to purchase the selected quantity of the product
                if (products[choice - 1].purchase(quantity)) {
                    selectedIndices.push_back(choice - 1);
                    quantities.push_back(quantity);
                    total += products[choice - 1].getPrice() * quantity;
                    cout << "You selected: " << products[choice - 1].getName()
                         << " (Quantity: " << quantity << ")\n";
                    cout << "Total Product Total: $" << fixed << setprecision(2) << products[choice - 1].getPrice() * quantity << endl;
                } else {
                    // Purchase failed due to insufficient stock
                    cout << "Sorry, not enough " << products[choice - 1].getName() << " in stock. Available: " << products[choice - 1].getStockQuantity() << endl;
                }
            }

            cout << "Do you want to select another product? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        // Display the final selection of products and their details
        cout << "\nYou selected the following products:" << endl;
        for (size_t i = 0; i < selectedIndices.size(); ++i) {
            cout << "Product: " << products[selectedIndices[i]].getName()
                 << ", Price: $" << fixed << setprecision(2) << products[selectedIndices[i]].getPrice()
                 << ", Discount: " << products[selectedIndices[i]].getDiscount() << "%"
                 << ", Quantity: " << quantities[i] << endl;
            cout << "Total Product Total: $" << fixed << setprecision(2) << products[selectedIndices[i]].getPrice() * quantities[i] << endl;
        }

        return total;
    }
};

int main() {
    // Define a set of products with initial stock quantities
    const int NUM_PRODUCTS = 5;
    Product productArray[NUM_PRODUCTS] = {
        Product("Chips", 1.50, 10),
        Product("Candy", 1.00, 15),
        Product("Soda", 2.00, 8),
        Product("Chocolate", 1.75, 12),
        Product("Gum", 0.75, 20)
    };

    // Create a vending machine and add the products to it
    VendingMachine snackMachine("Snack Machine");

    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        snackMachine.addProduct(productArray[i]);
    }

    // Display products, apply random discounts, and show the discounted prices
    snackMachine.displayProducts();
    snackMachine.applyRandomDiscounts();
    cout << "\nAfter applying random discounts:\n" << endl;
    snackMachine.displayProducts();

    // Allow the user to select products and display the total price
    double total = snackMachine.selectProducts();

    cout << "\nTotal price: $" << fixed << setprecision(2) << total << endl;

    return 0;
}
