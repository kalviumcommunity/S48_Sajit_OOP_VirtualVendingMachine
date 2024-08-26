```markdown
# Virtual Vending Machine Project

## Overview
This project implements a simple virtual vending machine system using C++. It demonstrates key object-oriented programming concepts including classes, objects, this pointer, and arrays of objects.

## Features
- Create and manage vending machines
- Add and display products in vending machines
- Apply discounts to products
- Use of array of objects for efficient product management

## Classes
- Product
- VendingMachine

### Product
Represents items that can be sold in a vending machine.
- Attributes: name, price
- Methods: displayInfo(), applyDiscount()

### VendingMachine
Represents a vending machine that can hold and manage products.
- Attributes: name, vector of products
- Methods: addProduct(), displayProducts(), applyDiscountToAll()

## Key Concepts Demonstrated

1. **Classes and Objects**
   - Two main classes: Product and VendingMachine
   - Objects of these classes are created and used in the main function

2. **This Pointer**
   - Used in both Product and VendingMachine classes
   - Demonstrates differentiation between member variables and parameters
   - Used for method chaining in VendingMachine class

3. **Array of Objects**
   - An array of Product objects is created in the main function
   - Demonstrates bulk initialization and management of objects

## How to Compile and Run
1. Ensure you have a C++ compiler installed (e.g., g++)
2. Compile the code:
   ```
   g++ -std=c++11 main.cpp -o vending_machine
   ```
3. Run the executable:
   ```
   ./vending_machine
   ```

## Sample Output
```
Added Chips to Snack Machine
Added Candy to Snack Machine
Added Soda to Snack Machine
Added Chocolate to Snack Machine
Added Gum to Snack Machine
Products in Snack Machine:
Product: Chips, Price: $1.50
Product: Candy, Price: $1.00
Product: Soda, Price: $2.00
Product: Chocolate, Price: $1.75
Product: Gum, Price: $0.75
Applied 10% discount to Chips. New price: $1.35
Applied 10% discount to Candy. New price: $0.90
Applied 10% discount to Soda. New price: $1.80
Applied 10% discount to Chocolate. New price: $1.58
Applied 10% discount to Gum. New price: $0.68
Products in Snack Machine:
Product: Chips, Price: $1.35
Product: Candy, Price: $0.90
Product: Soda, Price: $1.80
Product: Chocolate, Price: $1.58
Product: Gum, Price: $0.68
```

## Future Enhancements
- Implement a user interface for interaction with the vending machine
- Add functionality for purchasing items
- Implement inventory management and restocking features

## Contributors
Sajit Magesh

## License
MIT License
```

This README provides a comprehensive overview of the project, including its features, the key concepts demonstrated, how to compile and run the code, and a sample output. It also suggests potential future enhancements, which can be useful for further development or for demonstrating your forward-thinking approach in a project presentation.
