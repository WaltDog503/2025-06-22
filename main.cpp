#include "main.h"

int main(int argc, char** argv)
{
	ItemList	inventory;
	char		fileName[] = "items.txt";

	// open file to read data and populate inventory
	ifstream in;
	in.open(fileName);
	if (!in)
	{
		cerr << "Fail to open " << fileName << " for input!" << endl;
		return 1;
	}
	inventory.readList(in);
	in.close();

	cout << "Current Inventory:" << endl;
	inventory.printList();

	InventoryItem match;
	char findName[MAX_CHAR];
	cout << endl << "Enter the item name to find: ";
	cin.getline(findName, MAX_CHAR);

	if (inventory.searchByName(findName, match))
	{
		cout << "Item found!" << endl;
		match.print();
	}
	else
	{
		cout << "Item not found!" << endl;
	}

	cout << endl << "To insert an item." << endl;
	char itemName[MAX_CHAR];
	float itemPrice;
	int year;
	int month;
	int day;
	char slash;

	cout << "Enter name of item: ";
	cin.getline(itemName, MAX_CHAR);
	cout << "Enter price of item: ";
	cin >> itemPrice;
	cout << "Enter expiry date of item: ";
	cin >> year >> slash >> month >> slash >> day;

	InventoryItem newItem;
	Date expDate;
	expDate.setDate(year, month, day);
	newItem.setItemName(itemName);
	newItem.setItemPrice(itemPrice);
	newItem.setExpDate(expDate);

	cout << endl;
	if (inventory.insertItem(newItem))
	{
		cout << "Item inserted. Updated list below:" << endl;
	}
	else
	{
		cout << "Item exists. List not updated:" << endl;
	}
	inventory.printList();

	return 0;
}
