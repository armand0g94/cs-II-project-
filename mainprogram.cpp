#include <iostream>
#include <cctype>

using namespace std;


void showMenu();

int main()
{
    showMenu();




    return 0;
}

void showMenu()
{
    char letter;

    cout << "******************" << endl
         << "Cookbook Inventory" << endl
         << "******************" << endl
         << "Enter a food style you would like to cook from the menu,\n"
         << "then select a plate and the number of people who wil be eating."
         << endl;

    //Menu
    cout << "------------------" << endl
         << "------------------" << endl
         << "(A) American" << endl
         << "(B) Asian " << endl
         << "(C) Mexican" << endl
         << "(D) German" << endl
         << "(E) QUIT" << endl << "Selection: ";

    //cin >> numItems;

    cin >> letter;

    while (toupper (letter) < 'A' || toupper(letter) > 'D')
    {
        cout << "That is not a valid letter." << endl
             << "Enter a letter from A to D: ";
        cin >> letter;
    }

    switch (letter)
    {
        case 'A':
            cout << "Choose a plate, press 5 to go back, press 6 to quit: "
                 << "(1) Hot Dog" << endl
                 << "(2) Pizza" << endl
                 << "(3) Chicken Fried Steak" << endl
                 << "(4) BBQ" << endl
                 << "(5) Go to Previous" << endl
                 << "(6) Quit";
            break;
        case 'B':
            cout << "dsdd";
            break;


        default: cout << "You did not enter A, B...";


    }






}
