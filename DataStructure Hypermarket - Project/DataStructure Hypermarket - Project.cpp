#include <iostream>
#include <string>
using namespace std;

//Hypermarket
template <class itemType>
struct itemsNode {
	int itemId;
	static int currentId;
	int itemStock;
	float itemPrice;
	itemType itemName;
	itemsNode<itemType>* next;
};

template <class itemType>
class RAFHypermarket {
private:
	int marketItems;
	itemsNode<itemType>* itemsList;
public:
	RAFHypermarket();
	~RAFHypermarket();
	void makeMarketEmpty();
	bool isFull()const;
	void insertItemToMarket(itemType itemName, float itemPrice, int itemStock);
	void deleteItemFromMarket(itemType itemName);
	void checkExistItem(itemType itemName, bool& exist);
	float getItemPriceByName(itemType itemName);
	int getStock(itemType itemName);
	void decreaseStock(itemType itemName);
	void updateItemIds();
	void printItems();
};

template <class itemType>
RAFHypermarket<itemType>::RAFHypermarket() {
	marketItems = 0;
	itemsList = NULL;
}

template <class itemType>
RAFHypermarket<itemType>::~RAFHypermarket() {
	makeMarketEmpty();
}

template <class itemType>
int itemsNode<itemType>::currentId = 1;

template <class itemType>
void RAFHypermarket<itemType>::makeMarketEmpty() {
	itemsNode<itemType>* tempPointer;
	while (itemsList != NULL) {
		tempPointer = itemsList;
		itemsList = itemsList->next;
		delete tempPointer;
	}
	marketItems = 0;
}

template <class itemType>
bool RAFHypermarket<itemType>::isFull()const {
	itemsNode<itemType>* fullPointer = new itemsNode<itemType>;
	if (fullPointer == NULL) return true;
	else {
		delete fullPointer;
		return false;
	}
}

template <class itemType>
void RAFHypermarket<itemType>::insertItemToMarket(itemType itemName, float itemPrice, int itemStock) {
	if (!isFull()) {
		bool exist = false;
		checkExistItem(itemName, exist);
		if (exist) {
			cout << endl << "The item \"" << itemName << "\" already exists in the market!" << endl << endl;
			return;
		}
		else {
			itemsNode<itemType>* location = itemsList;
			itemsNode<itemType>* preLocation = NULL;
			itemsNode<itemType>* insertPointer = new itemsNode<itemType>;
			bool foundLocation = false;
			insertPointer->itemId = insertPointer->currentId++;
			insertPointer->itemName = itemName;
			insertPointer->itemPrice = itemPrice;
			insertPointer->itemStock = itemStock;
			insertPointer->next = NULL;
			while (location != NULL && !foundLocation) {
				if (insertPointer->itemId < location->itemId) foundLocation = true;
				else {
					preLocation = location;
					location = location->next;
				}
			}
			if (preLocation == NULL) {
				insertPointer->next = itemsList;
				itemsList = insertPointer;
			}
			else {
				preLocation->next = insertPointer;
				insertPointer->next = location;
			}
			marketItems++;
			cout << endl << "The item \"" << itemName << "\" with price " << itemPrice << " JD, has been successfully added to the market." << endl << endl;
		}
	}
	else {
		cout << "The market is full. Unable to add more items." << endl;
	}
}

template <class itemType>
void RAFHypermarket<itemType>::deleteItemFromMarket(itemType itemName) {
	itemsNode<itemType>* location = itemsList;
	itemsNode<itemType>* tempLocation = NULL;
	bool exist = false;
	checkExistItem(itemName, exist);
	if (!exist) {
		cout << endl << "The item \"" << itemName << "\" could not be found in the market." << endl << endl;
		return;
	}
	else {
		if (location->itemName == itemName) {
			tempLocation = location;
			itemsList = itemsList->next;
		}
		else {
			while (location->next != NULL && itemName != (location->next)->itemName) {
				location = location->next;
			}
			if (location->next != NULL && itemName == (location->next)->itemName) {
				tempLocation = location->next;
				location->next = tempLocation->next;
			}
		}
		if (tempLocation != NULL) {
			cout << endl << "The item \"" << itemName << "\" has been successfully deleted from the market." << endl << endl;
			delete tempLocation;
			updateItemIds();
			marketItems--;
		}
	}
}

template <class itemType>
void RAFHypermarket<itemType>::checkExistItem(itemType itemName, bool& exist) {
	itemsNode<itemType>* items = itemsList;
	exist = false;
	while (items != NULL) {
		if (itemName == items->itemName) {
			exist = true;
			return;
		}
		else items = items->next;
	}
}

template <class itemType>
int RAFHypermarket<itemType>::getStock(itemType itemName) {
	itemsNode<itemType>* items = itemsList;
	while (items != NULL) {
		if (itemName == items->itemName) {
			return items->itemStock;
		}
		else items = items->next;
	}
}

template <class itemType>
void RAFHypermarket<itemType>::decreaseStock(itemType itemName) {
	itemsNode<itemType>* items = itemsList;
	while (items != NULL) {
		if (itemName == items->itemName) {
			items->itemStock--;
			return;
		}
		else items = items->next;
	}
}

template <class itemType>
float RAFHypermarket<itemType>::getItemPriceByName(itemType itemName) {
	bool exist;
	checkExistItem(itemName, exist);
	if (!exist) {
		return 0;
	}
	else {
		itemsNode<itemType>* items = itemsList;
		while (items != NULL) {
			if (items->itemName == itemName) {
				return items->itemPrice;
			}
			else items = items->next;
		}
	}
}

template <class itemType>
void RAFHypermarket<itemType>::updateItemIds() {
	itemsNode<itemType>* tempItems = itemsList;
	int id = 1;
	while (tempItems != NULL) {
		tempItems->itemId = id++;
		tempItems = tempItems->next;
	}
	tempItems->currentId--;
}

template <class itemType>
void RAFHypermarket<itemType>::printItems() {
	itemsNode<itemType>* items = itemsList;
	cout << endl << "*******************************" << endl;
	cout << "         RAF Hypermarket        " << endl;
	cout << "*******************************" << endl << endl;
	if (items == NULL) {
		cout << "The market is currently empty. Please add items to the market." << endl << endl;
		return;
	}
	else {
		while (items != NULL) {
			cout << items->itemId << ". " << items->itemName << " - " << items->itemPrice << " JD - Stock: " << items->itemStock << " units" << endl;
			items = items->next;
		}
	}
	cout << endl;
}

//Customer
template <class itemType>
struct customerNode {
	int customerId;
	static int currentId;
	itemType items[20];
	float finalCost = 0;
	int itemsNumber = 0;
	customerNode<itemType>* next;
};

template <class itemType>
class RAFCustomers {
private:
	int customersLength;
	customerNode<itemType>* customersList;
public:
	RAFCustomers();
	~RAFCustomers();
	void makeEmpty();
	bool isMarketFull()const;
	void insertCustomer(int& customerId);
	void getCustomerById(customerNode<itemType>*& customer, int customerId);
	void insertItemToRecipt(int customerId, itemType itemName, RAFHypermarket<itemType>& market);
	void printCustomersList();
	void deleteCustomer(int customerId);
};

template <class itemType>
int customerNode<itemType>::currentId = 1;

template <class itemType>
RAFCustomers<itemType>::RAFCustomers() {
	customersLength = 0;
	customersList = NULL;
}

template <class itemType>
RAFCustomers<itemType>::~RAFCustomers() {
	makeEmpty();
}

template <class itemType>
void RAFCustomers<itemType>::makeEmpty() {
	customerNode<itemType>* tempPointer;
	while (customersList != NULL) {
		tempPointer = customersList;
		customersList = customersList->next;
		delete tempPointer;
	}
	customersLength = 0;
}

template <class itemType>
bool RAFCustomers<itemType>::isMarketFull()const {
	customerNode<itemType>* fullPointer = new customerNode<itemType>;
	if (fullPointer == NULL) return true;
	else {
		delete fullPointer;
		return false;
	}
}

template <class itemType>
void RAFCustomers<itemType>::insertCustomer(int& customerId) {
	if (!isMarketFull()) {
		customerNode<itemType>* location = customersList;
		customerNode<itemType>* preLocation = NULL;
		customerNode<itemType>* insertPointer = new customerNode<itemType>;
		bool foundLocation = false;
		insertPointer->customerId = insertPointer->currentId++;
		insertPointer->next = NULL;
		customerId = insertPointer->customerId;
		while (location != NULL && !foundLocation) {
			if (insertPointer->customerId < location->customerId) foundLocation = true;
			else {
				preLocation = location;
				location = location->next;
			}
		}
		if (preLocation == NULL) {
			insertPointer->next = customersList;
			customersList = insertPointer;
		}
		else {
			preLocation->next = insertPointer;
			insertPointer->next = location;
		}
		customersLength++;
		cout << endl << "A new customer with ID " << customerId << " has been successfully created!" << endl << endl;
	}
	else {
		cout << endl << "The Market is full. Unable to add more customers." << endl << endl;
	}
}

template <class itemType>
void RAFCustomers<itemType>::getCustomerById(customerNode<itemType>*& customer, int customerId) {
	customerNode<itemType>* customers = customersList;
	while (customers != NULL) {
		if (customers->customerId == customerId) {
			customer = customers;
			return;
		}
		else customers = customers->next;
	}
}

template <class itemType>
void RAFCustomers<itemType>::insertItemToRecipt(int customerId, itemType itemName, RAFHypermarket<itemType>& market) {
	customerNode<itemType>* myCustomer = NULL;
	getCustomerById(myCustomer, customerId);
	float itemPrice = market.getItemPriceByName(itemName);
	if (myCustomer == NULL) {
		cout << endl << "Error: The customer with ID " << customerId << " does not exist in the system." << endl << endl;
		return;
	}
	else {
		bool exist;
		market.checkExistItem(itemName, exist);
		if (exist) {
			if (market.getStock(itemName) != 0) {
				if (myCustomer->itemsNumber < 20) {
					myCustomer->items[myCustomer->itemsNumber++] = itemName;
					myCustomer->finalCost += itemPrice;
					cout << endl << "Successfully added \"" << itemName << "\" to the receipt of customer ID " << myCustomer->customerId << "." << endl;
					cout << "Item Price: " << itemPrice << " JD" << endl << endl;
					market.decreaseStock(itemName);
				}
				else cout << "Sorry, the customer cannot purchase more than 20 items." << endl;
			}
			else {
				cout << "Sorry, this item is out of stock and unavailable for purchase at the moment." << endl << endl;
				market.deleteItemFromMarket(itemName);
			}
		}
		else cout << endl << "Error: The item \"" << itemName << "\" does not exist on the market." << endl << endl;
	}
}

template <class itemType>
void RAFCustomers<itemType>::printCustomersList() {
	customerNode<itemType>* myCustomer = customersList;
	if (myCustomer == NULL) {
		cout << endl << "No customers found in the system." << endl << endl;
		return;
	}
	else {
		cout << endl << "List of Customers:" << endl << endl;
		while (myCustomer != NULL) {
			cout << "Customer ID: " << myCustomer->customerId << " is registered in the system." << endl;
			myCustomer = myCustomer->next;
		}
		cout << endl << "End of customer list." << endl << endl;
	}
}

template <class itemType>
void RAFCustomers<itemType>::deleteCustomer(int customerId) {
	customerNode<itemType>* location = customersList;
	customerNode<itemType>* tempLocation = NULL;
	customerNode<itemType>* myCustomer = NULL;
	getCustomerById(myCustomer, customerId);
	if (myCustomer == NULL) {
		cout << endl << "The customer with ID " << customerId << " does not exist in the system." << endl << endl;
		return;
	}
	else {

		cout << endl << "Here is the receipt for Customer ID " << myCustomer->customerId << ":" << endl;
		for (int i = 0; i < myCustomer->itemsNumber; i++) {
			cout << (i + 1) << ". " << myCustomer->items[i] << endl;
		}
		cout << endl << "The final cost is: " << myCustomer->finalCost << " JD." << endl << endl;

		if (location->customerId == myCustomer->customerId) {
			tempLocation = location;
			customersList = customersList->next;
		}
		else {
			while (location->next != NULL && myCustomer->customerId != (location->next)->customerId) {
				location = location->next;
			}
			if (location->next != NULL && myCustomer->customerId == (location->next)->customerId) {
				tempLocation = location->next;
				location->next = tempLocation->next;
			}
		}
		if (tempLocation != NULL) {
			delete tempLocation;
			customersLength--;
			cout << "Customer ID " << customerId << " has been successfully deleted from the system." << endl << endl;
		}
	}
}

int main() {
	system("title RAF Hypermarket System v0.1");
	RAFHypermarket<string> market;
	RAFCustomers<string> customers;
	char choice = NULL;
	int customerId;
	do {
		cout << "Welcome to the RAF Hypermarket System" << endl;
		cout << "Please choose an option to proceed:" << endl;
		cout << "--------------------" << endl;
		cout << "1. Add an item to the market" << endl;
		cout << "2. Remove an item from the market" << endl;
		cout << "3. View the current market items" << endl;
		cout << "4. Create a new customer" << endl;
		cout << "5. Add an item to a customer's receipt" << endl;
		cout << "6. View the customer list" << endl;
		cout << "7. Print a customer's receipt and finalize the order" << endl << endl;
		cout << "Q. Exit the system" << endl;
		cout << "--------------------" << endl << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case '1': {
			string itemName;
			float itemPrice;
			int itemStock;
			cout << "Please enter the name of the item: ";
			cin.ignore();
			getline(cin, itemName);
			cout << "Please enter the price of the item: ";
			cin >> itemPrice;
			cout << "Please enter the current stock quantity for the item: ";
			cin >> itemStock;
			market.insertItemToMarket(itemName, itemPrice, itemStock);
			break;
		}
		case '2': {
			string itemName;
			cout << "Please enter the name of the item you wish to remove: ";
			cin.ignore();
			getline(cin, itemName);
			market.deleteItemFromMarket(itemName);
			break;
		}
		case '3': {
			market.printItems();
			break;
		}
		case '4': {
			customers.insertCustomer(customerId);
			break;
		}
		case '5': {
			string itemName;
			int itemPrice, customerId;
			cout << "Please enter the customer ID: ";
			cin >> customerId;
			cout << "Please enter the name of the item from the menu: ";
			cin.ignore();
			getline(cin, itemName);
			customers.insertItemToRecipt(customerId, itemName, market);
			break;
		}
		case '6': {
			customers.printCustomersList();
			break;
		}
		case '7': {
			int customerId;
			cout << "Please enter the customer ID you wish to remove: ";
			cin >> customerId;
			customers.deleteCustomer(customerId);
			break;
		}
		case 'Q':
		case 'q':
			break;
		default:
			cout << "Invalid choice. Please select a valid option." << endl << endl;
		}
	} while (choice != 'Q' && choice != 'q');

	return 0;
}