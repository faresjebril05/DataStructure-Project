# RAF Hypermarket System

## Compilation Instructions
To compile and run the program, follow these steps:

1. Save the code in a `.cpp` file.
2. Open a terminal or command prompt.
3. Use the following command to compile the code(assuming `g++` is installed):
  g++ - o HypermarketSystem HypermarketSystem.cpp
4. Run the program:
  ./HypermarketSystem

## License
This project is open-source and available under the MIT License. You can freely modify, distribute, and use it for personal or commercial purposes.

## Contributing
Contributions are welcome! If you would like to improve the system or add new features, feel free to fork the repository, create a branch, and submit a pull request.

## Acknowledgments
This project was developed as a basic hypermarket management system prototype. Special thanks to the contributors who helped in testing and refining the code.

## Overview
The RAF Hypermarket System is a C++ based application designed to manage a hypermarket's inventory and customer orders. It allows users to add and remove items from the market, track customer orders, and maintain a customer database. The system supports functionalities such as adding new customers, adding items to customer receipts, displaying current items in the market, and finalizing orders.

This system uses templates to handle a variety of item types (e.g., `string`, `float`), making it flexible for managing different types of market items and customer orders. The program utilizes linked lists for dynamic memory management of inventory items and customer records.

## Features

### Market Management
- **Add an Item to the Market:** Add a new item with a name and price to the market. The system prevents duplicates.
- **Remove an Item from the Market:** Delete an item from the market by its name.
- **View Market Inventory:** Display the current list of items in the market, showing their IDs, names, and prices.

### Customer Management
- **Create a New Customer:** Register a new customer with a unique customer ID.
- **Add Items to Customer Receipt:** Add items to a customer's receipt, calculating the total cost as items are added.
- **View Customer List:** Display a list of all registered customers by their customer IDs.
- **Delete Customer:** Remove a customer from the system, showing their order details and final cost before deletion.

### System Operations
- **Menu Validation:** Ensures that items cannot be added to the market if they already exist.
- **Dynamic Memory Management:** Uses linked list structures for dynamic memory management of market items and customers, ensuring efficient use of resources.
- **ID Management:** Automatically assigns incremental IDs to market items and customers.

## Key Data Structures

1. **ItemsNode:** This structure holds information about a market item, including its unique ID, name, price, and a pointer to the next item. It is used in a linked list to represent the market inventory.
2. **CustomerNode:** This structure holds customer information, including a unique ID, an array of ordered items, total cost, and a pointer to the next customer in the list. It tracks customer orders and receipt details.

## Class Structure

### RAFHypermarket<itemType>
Manages the hypermarket inventory. Template-based, allowing different types of items (e.g., `string` for item names).

#### Public Methods:
- `insertItemToMarket(itemType itemName, float itemPrice)`: Adds an item to the market.
- `deleteItemFromMarket(itemType itemName)`: Removes an item from the market.
- `printMenu()`: Displays the entire market inventory.
- `getItemPriceByName(itemType itemName)`: Fetches the price of an item by its name.
- `checkExistItem(itemType itemName, bool& exist)`: Checks if an item exists in the market.
- `updateItemIds()`: Updates the item IDs in the market after deletion.

### RAFCustomers<itemType>
Manages customer records and their orders. Template-based for flexibility.

#### Public Methods:
- `insertCustomer(int& customerId)`: Adds a new customer.
- `getCustomerById(customerNode<itemType>*& customer, int customerId)`: Retrieves customer details by ID.
- `insertItemToRecipt(int customerId, itemType itemName, RAFHypermarket<itemType>& Market)`: Adds an item to a customer's receipt.
- `printCustomersList()`: Displays all registered customers.
- `deleteCustomer(int customerId)`: Deletes a customer and shows their receipt and total cost.

## How to Use

1. **Start the Application:** Run the program and follow the prompts to manage the hypermarket.
2. **Add/Remove Market Items:** Select the option to add or remove items from the market.
3. **Create Customers:** Register customers and add items to their receipts.
4. **View/Manage Orders:** Print receipts, calculate total costs, and delete customers when their orders are complete.

### Example of Usage

```cpp
// Create hypermarket and customer systems
RAFHypermarket<string> market;
RAFCustomers<string> customers;

// Add a market item
market.insertItemToMarket("Pizza", 5.99);

// Create a new customer
int customerId;
customers.insertCustomer(customerId);

// Add items to customer receipt
customers.insertItemToRecipt(customerId, "Pizza", market);

// View current market inventory
market.printMenu();

// View customer list
customers.printCustomersList();
