#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// define a data structure
struct InventoryRecord
{
  string name;   // inventory item name
  int qty;       // how many are in stock
  double cost;   // the cost
};

// const for the max size of the record array
const int MAX_SIZE = 9;

// function prototypes
void addData(InventoryRecord list[], int& size);
void dispData(const InventoryRecord list[], int size);
void saveFile(const InventoryRecord list[], int size);
void openFile(InventoryRecord list[], int& size);
char getMenuResponse();


int main(int argc, char *argv[])
{
  InventoryRecord recList[MAX_SIZE];
  int numOfRecs = 0;
  bool run = true;
  do
  {
    cout << "Inventory Program - " << numOfRecs << " items in stock" << endl;
  	switch ( getMenuResponse() )
  	{
	    case 'A': addData(recList, numOfRecs); break;
  		case 'D': dispData(recList, numOfRecs); break;
  		case 'O': openFile(recList, numOfRecs); break;
  		case 'S': saveFile(recList, numOfRecs); break;
  		case 'Q': run = false; break;
  		default : cout << "That is NOT a valid choice" << endl;
  	}
  } while (run);
  cout << endl << "Program Terminated" << endl;

  // system("PAUSE"); // Program exits immediatly upon "Quit" if commented out
  return EXIT_SUCCESS;
}

// Task:     Allow data entry of one inventory item
// Accepts:  References to the inventory array and its size
// Returns:  Nothing
// Modifies: The array and size 'actual parameter'
// NOTE:     Could be modified to allow entry of more than one item
void addData(InventoryRecord list[], int& size)
{
  InventoryRecord tmp; // declare a temp item that we will load before putting in the array
  char response;
  char str[256]; // needed for cin.getline; we are going to use a char array
  if (size < MAX_SIZE) {
    system("cls");
    cout << "Enter Inventory Records" << endl << endl;
    cout << "Name:     ";
    // Get up to 256 characters from the keyboard including white space.
    // Stop reading if encounter the \n first. If there's any chance of
    // more than 256 characters you will have to clean up cin with
    // cin.ignore before the next input.
    cin.getline(str, 256, '\n'); // for char arrays; different from the other getline
    tmp.name = str;
    cout << "Quantity: ";
    cin >> tmp.qty;
    cout << "Cost:     ";
    cin >> tmp.cost;
    cout << endl;
    // see if this record should be added to the array
    cout << "Add the record to inventory? (y/n) ";
    cin >> response;
    if (toupper(response) == 'Y')
      list[size++] = tmp;
  } else {
    cout << "Inventory at full; cannot enter more unit." << endl;
    system("pause");
  }
  system("cls");
}

void dispData(const InventoryRecord list[], int size)
{
  system("cls");
  double cost = 0;

  if(size < 1) {
    cout << "Nothing to display" << endl;
  } else {
    cout << "All Inventory item has been shown" << endl << endl;
    cout << fixed << setprecision(2);
    cout << "Item Name              Qty     Cost" << endl;
    cout << "~~~~~~~~~~~~~~~~~~" << endl;

    cout << left;
    for (int i = 0; i < size; i++) {
      cout << setw(21) << list[i].name << right
           << setw(4)  << list[i].qty
           << setw(10) << list[i].cost << left << endl;
           cost = cost + list[i].cost * list[i].qty;
    }

    cout << "~~~~~~~~~~~~~~~~~~~" << endl;
    cout << right << setw(3) << size;
    cout << " items listed";
    cout << right << setw(19) << cost << endl << endl;
  }

  system("PAUSE");
  system("cls");
}

// Save records to disc
void saveFile(const InventoryRecord list[], int size) {
  ofstream outfi("Inventory.txt");

  // make sure the file stream is open before doing IO
  if (!outfi.fail()) {
    system("cls");
    cout << "Saving inventory to the disc ";

    for(int i = 0; i < size; i++) {
      outfi << list[i].name << ';'
            << list[i].qty << ';'
            << list[i].cost;
      // Start a new line after all but the last record
      // Simplifies reading the file as EOF is at end of last line
      if (i < size-1) outfi << endl;
    }
    cout << endl << size << " records writen to the disc." << endl;
    outfi.close();
    system("PAUSE");
    system("cls");
  }
  else {
    cout << "ERROR: problem with file" << endl;
    system("PAUSE");
    system("cls");
  }
}

// Open file and load array
void openFile(InventoryRecord list[], int& size)
{
  ifstream infi("Inventory.txt");
  string str;
  stringstream strstrm;

  // make sure the file stream is open before doing IO
  if (!infi.fail()) {

    system("cls");
    cout << "Reading inventory from the disc ";

    size = 0; // overwrite any existing records
    while(!infi.eof() && size < MAX_SIZE) {
      // get and store the name
      getline(infi, str, ';');
      list[size].name = str;

      // get, convert and store the quantity
      getline(infi, str, ';');
      strstrm.str(""); strstrm.clear(); // empty and clear the stringstream
      strstrm << str;
      strstrm >> list[size].qty;

      // get, convert and store the cost
      getline(infi, str);
      strstrm.str(""); strstrm.clear(); // empty and clear the stringstream
      strstrm << str;
      strstrm >> list[size++].cost;
    }
    cout << endl << size << " records read from the disc." << endl;

    system("PAUSE");
    system("cls");
  }
  else { // something went wrong with opening the file
    cout << "ERROR: problem with file" << endl;
    system("PAUSE");
    system("cls");
  }

}

char getMenuResponse()
// Task:     Put the menu on screen and get a response
// Accepts:  Nothing
// Returns:  The users response
// Modifies: Nothing
// NOTE:     Characters are far more intuitive at the command
//           line than numbers; avoid using numbers.
{
	char response;
	cout << endl << "Make your selection" << endl
		 << "(A)dd Record, (D)isplay Records, (O)pen File, (S)ave File, (Q)uit" << endl
		 << "> ";
	cin >> response;
	cin.ignore(256, '\n');
	// clean-up up to 256 chars including the delimiter specified (\n, the endl)
	// OR stop when the \n is encountered after removing it.
	return toupper(response);
}
