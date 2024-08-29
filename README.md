# Virtual Vending Machine

### Introduction

This C++ project simulates a vending machine, providing a realistic experience of selecting and purchasing products. Users can choose from various items, apply discounts, and manage their purchases.

### How to Use

**1. Compile:**
```bash
g++ vending_machine.cpp -o vending_machine
```

**2. Run:**
```bash
./vending_machine
```

### Features

- **Product Selection:** Users can choose products from a list.
- **Quantity Input:** Users can specify the desired quantity of each product.
- **Stock Management:** The program tracks product stock and prevents purchases when stock is insufficient.
- **Random Discounts:** Products may have randomly applied discounts.
- **Individual Product Totals:** The total cost for each selected product is displayed.
- **Overall Total:** The final total cost of all selected products is calculated.

### Code Structure

- **`Product` class:** Represents a single product with name, price, discount, and stock quantity.
- **`VendingMachine` class:** Manages a collection of products, handles product selection, and calculates the total cost.

### Additional Notes

- **Random Seed:** The program uses a random seed based on the current time for consistent discount application.
- **Error Handling:** Basic input validation is included to ensure user-entered data is within expected ranges.
- **Code Structure:** The code is organized into well-defined classes and functions for better readability and maintainability.

### Copyright and License

**© 2024 [Sajit Magesh](https://github.com/maverickOG)**

This code is protected by copyright laws. Unauthorized use, reproduction, or distribution is prohibited.

**Feel free to contribute to this project by submitting pull requests or raising issues on GitHub!**
