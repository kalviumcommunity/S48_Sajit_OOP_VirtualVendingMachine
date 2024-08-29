# Virtual Vending Machine

## Overview

A C++ project simulating a simple virtual vending machine. It demonstrates object-oriented programming concepts using classes, objects, `this` pointer, and arrays of objects.

## Features

* Create and manage multiple vending machines.
* Add, remove, and display products in each machine.
* Apply discounts to individual products or all products in a machine.
* Efficiently manage products using arrays of objects.

## Classes

* **`Product`**
    * Attributes: name, price, quantity
    * Methods: `displayInfo()`, `applyDiscount()`
* **`VendingMachine`**
    * Attributes: name, array of products
    * Methods: `addProduct()`, `removeProduct()`, `displayProducts()`, `applyDiscountToAll()`

## Key Concepts Demonstrated

* **Classes and Objects:** Encapsulation of data and behavior.
* **`this` Pointer:** Referencing the current object within its methods.
* **Arrays of Objects:** Efficiently storing and managing multiple products.

## How to Use

1. **Compile:** `g++ main.cpp -o vending_machine`
2. **Run:** `./vending_machine`

## Sample Output

```
Created a new vending machine: Snack Machine
Added Chips to Snack Machine
Added Candy to Snack Machine
Displaying products in Snack Machine:
Product: Chips, Price: $1.50, Quantity: 5
Product: Candy, Price: $1.00, Quantity: 10
Applied 10% discount to all products in Snack Machine
```

## Future Enhancements

* Implement a user interface for interaction with the vending machine.
* Add functionality for purchasing products.
* Implement inventory management and restocking.
* Consider using more advanced data structures like linked lists or trees for better product management.

## Contributors

Sajit Magesh

### License

MIT License

### Additional Tips

* **Code Clarity:** Use meaningful variable and function names, consistent indentation, and comments to improve code readability.
* **Error Handling:** Implement error handling mechanisms to prevent unexpected behavior (e.g., handling invalid input or out-of-stock products).
* **Testing:** Write unit tests to ensure the correctness of your code.
* **Efficiency:** Consider optimizing your code for performance, especially if dealing with large datasets.

By following these guidelines, you can create a well-structured and maintainable virtual vending machine project. Good luck with your coding! 🚀
