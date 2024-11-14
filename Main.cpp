#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Product class handles individual item details and inventory management
class Product {
private:
    string name;
    double price;
    int stockQuantity;
    double discount;

public:
    Product(string name, double price, int stockQuantity)
        : name(name), price(price), discount(0.0), stockQuantity(stockQuantity) {}

    // Displays formatted product information including any active discounts
    void displayInfo() const {
        cout << left << setw(15) << name 
             << "Price: $" << fixed << setprecision(2) << price;
        if (discount > 0) {
            double discountedPrice = price * (1 - discount/100);
            cout << " (Original: $" << price 
                 << ", Discount: " << discount << "%, "
                 << "Final: $" << discountedPrice << ")";
        }
        cout << ", Stock: " << stockQuantity << endl;
    }

    // Applies discount and updates the price accordingly
    void applyDiscount(double discountPercent) {
        discount = discountPercent;
        
    }

    // Attempts to process a purchase, returns false if insufficient stock
    bool purchase(int purchaseQuantity) {
        if (purchaseQuantity <= stockQuantity) {
            stockQuantity -= purchaseQuantity;
            return true;
        } else {
            return false;
        }   
    }

    // Getter functions
    string getName() const { return name; }
    double getPrice()  { 
        return price * (1 - discount / 100); 
     }
    double getDiscount() const { return discount; }
    int getStockQuantity() const { return stockQuantity; }
    double getOriginalPrice(){
    return price;
}
};

// VendingMachine class manages products and tracks sales statistics
class VendingMachine {
private:
    string name;
    vector<Product> products;

    // Static variables for tracking performance across all machines
    static double totalSales;        // Tracks total revenue across all machines
    static int totalTransactions;    // Counts successful transactions across all machines

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

    // Applies random discounts between 0-20% to all products
    void applyRandomDiscounts() {
        for (size_t i = 0; i < products.size(); ++i) {
            double discount = rand() % 21;
            products[i].applyDiscount(discount);
        }
    }

    // Handles the product selection and purchase process
    double selectProducts() {
        vector<int> selectedIndices;
        vector<int> quantities;
        double total = 0.0;
        char continueChoice;
        bool hasSuccessfulPurchase = false;

        // Purchase loop - continues until user is done selecting products
        do {
            int choice;
            cout << "Enter the number of the item you want (1-" << products.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > static_cast<int>(products.size()) || choice <= 0) {
                cout << "Invalid selection. Please choose a number between 1 and " << products.size() << "." << endl;
            } else {
                int quantity;
                cout << "Enter the quantity of " << products[choice - 1].getName() << " you want to purchase: ";
                cin >> quantity;

                // Process purchase if stock is available
                if (products[choice - 1].purchase(quantity)) {
                    selectedIndices.push_back(choice - 1);
                    quantities.push_back(quantity);
                    total += products[choice - 1].getPrice() * quantity;
                    hasSuccessfulPurchase = true;

                    // Display purchase details
                    cout << "You selected: " << products[choice - 1].getName()
                         << " (Quantity: " << quantity << ")\n";
                    cout << "Total Product Total: $" << fixed << setprecision(2)
                         << products[choice - 1].getPrice() * quantity << endl;
                }
            }

            cout << "Do you want to select another item? (y/n): ";
            cin >> continueChoice;
        } while (continueChoice == 'y' || continueChoice == 'Y');

        // Display summary of purchases
        cout << "\nYou selected the following products:" << endl;
        for (size_t i = 0; i < selectedIndices.size(); ++i) {
            cout << "Product: " << products[selectedIndices[i]].getName()
                 << ", Price: $" << fixed << setprecision(2) << products[selectedIndices[i]].getPrice()
                 << ", Discount: " << products[selectedIndices[i]].getDiscount() << "%"
                 << ", Quantity: " << quantities[i] << endl;
            cout << "Total Product Amount: $" << fixed << setprecision(2)
                 << products[selectedIndices[i]].getPrice() * quantities[i] << endl;
        }

        // Update sales statistics if any purchases were successful
        if (hasSuccessfulPurchase) {
            totalSales += total;
            totalTransactions++;
        }

        return total;
    }

    // Static methods for displaying sales statistics
    static void displayTotalSales() {
        cout << "Total Sales across all vending machines: $" << fixed << setprecision(2) << totalSales << endl;
    }

    static void displayTransactionStats() {
        cout << "Total number of successful transactions: " << totalTransactions << endl;
        if (totalTransactions > 0) {
            cout << "Average transaction value: $" << fixed << setprecision(2)
                 << totalSales / totalTransactions << endl;
        }
    }
};

// Initialize static variables
double VendingMachine::totalSales = 0.0;
int VendingMachine::totalTransactions = 0;

int main() {
    // Seed the random number generator
    srand(time(0));
    // Create and initialize vending machine with products
    VendingMachine* snackMachine = new VendingMachine("Snack Machine");

    // Define a set of products with initial stock quantities
    const int NUM_PRODUCTS = 5;
    Product productArray[NUM_PRODUCTS] = {
        Product("Chips", 1.50, 10),
        Product("Candy", 1.00, 15),
        Product("Soda", 2.00, 8),
        Product("Chocolate", 1.75, 12),
        Product("Gum", 0.75, 20)
    };

    // Add products to the vending machine
    for (int i = 0; i < NUM_PRODUCTS; ++i) {
        snackMachine->addProduct(productArray[i]);
    }

    // Display products, apply random discounts, and show the discounted prices
    snackMachine->displayProducts();
    snackMachine->applyRandomDiscounts();
    cout << "\nAfter applying random discounts:\n" << endl;
    snackMachine->displayProducts();

    // Allow the user to select products and display the total price
    double total = snackMachine->selectProducts();

    // Display the total price
    cout << "\nTotal price: $" << fixed << setprecision(2) << total << endl;

    // Display total sales
    VendingMachine::displayTotalSales();

    // Delete dynamically allocated vending machine to free memory
    delete snackMachine;

    return 0;
}