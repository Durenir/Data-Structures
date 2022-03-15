#include <iostream>
#include <string>
#include "passserver.h"

// ***************************************************************************
// * Name: Proj5.cpp                                                         *
// * Description: Driver that test functionality of the implementation of    *
// *    a HashTable and a PassServer. Driver displays a menu for the user to *
// *    selection from and processes commands accordingly. Options include   *
// *    loading a file, adding a user, removing a user, changing the password*
// *    of a user, finding a user, dumping the hashtable, displaying the size*
// *    of the hashtable, writing a file, and exiting the program.           *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/09/2020                                                        *
// ***************************************************************************
using namespace cop4530;
using namespace std;

void Menu();
int getServerSize();
char getMenuChoice();
pair<string, string> getUserPass();
const char LOAD = 'l', ADD = 'a', REMOVE = 'r', CHANGE = 'c', FIND = 'f',
        DUMP = 'd', SIZE = 's', WRITE = 'w', EXIT = 'x';

int main() {
    PassServer ps(getServerSize());
    char mChoice = ' ';
    string file, user, newpass;
    pair<string, string> userpass;
    while(mChoice != EXIT) {
        mChoice = getMenuChoice();
        switch(mChoice) {
            case LOAD:
                cout << "Enter password file name to load from: ";
                cin >> file;
                if(!ps.load(file.c_str()))
                {
                    cout << "*****Error: Cannot open file: " << file << endl;
                }
                break;
            case ADD:
                userpass = getUserPass();
                if (ps.addUser(pair<string, string>(userpass))) {
                    cout << "\nUser " << userpass.first << " added." << endl;
                } else {
                    cout << "\n*****Error: User already exist. Could not add user." << endl;
                }
                break;
            case REMOVE:
                cout << "Enter username: ";
                cin >> user;
                if (ps.removeUser(user)) {
                    cout << "User " << user << " deleted." << endl;
                } else {
                    cout << "*****Error: User not found. Could not delete user." << endl;
                }
                break;
            case CHANGE:
                userpass = getUserPass();
                cout << "\nEnter new password: ";
                cin >> newpass;
                if (ps.changePassword(pair<string, string>(userpass), newpass)) {
                    cout << "\nPassword changed for user " << userpass.first << endl;
                } else {
                    cout << "\n*****Error: Could not change user password." << endl;
                }
                break;
            case FIND:
                cout << "Enter username: ";
                cin >> user;
                if(ps.find(user))
                {
                    cout << "\nUser '" << user << "' found." << endl;
                } else {
                    cout << "\nUser '" << user << "' not found." << endl;
                }
                break;
            case DUMP:
                ps.dump();
                break;
            case SIZE:
                cout << "Size of hashtable: " << ps.size() << endl;
                break;
            case WRITE:
                cout << "Enter password file name to write to: ";
                cin >> file;
                if(!ps.write_to_file(file.c_str()))
                {
                    cout << "*****Error: Could not write to file." << endl;
                }
                break;
            case EXIT:
                break;
            default:
                break;
        }
    }
    return 0;
}

// *****************************************************************
// * Function Name: getUserPass                                    *
// * Description: Prompts a user for an input username and         *
// *    password. Returns the username and password as a pair.     *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
pair<string, string> getUserPass()
{
    string user, pass;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;
    return pair<string, string>(user, pass);
}

// *****************************************************************
// * Function Name: getMenuChoice                                  *
// * Description: Displays a menu and prompts a user for a menu    *
// *    selection. Continues to prompt for a new selection until a *
// *    valid selection is made. Returns the selection.            *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
char getMenuChoice()
{
    char choice;
    Menu();
    cin >> choice;
    while(tolower(choice) != LOAD && tolower(choice) != ADD && tolower(choice) != REMOVE &&
        tolower(choice) != CHANGE && tolower(choice) != FIND && tolower(choice) != DUMP &&
        tolower(choice) != SIZE && tolower(choice) != WRITE && tolower(choice) != EXIT)
    {
        cout << "*****Error: Invalid entry. Try again.";
        Menu();
        cin >> choice;
    }
    return char(tolower(choice));
}

// *****************************************************************
// * Function Name: Menu                                           *
// * Description: Displays a menu of options for the user.         *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Unknown. Supplied by Dr. David A. Gaitros.            *
// * References: Assignment 5 in Module 5.                         *
// *****************************************************************
void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

// *****************************************************************
// * Function Name: getServerSize                                  *
// * Description: Prompts the user for a hash table capacity and   *
// *    returns it.                                                *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
int getServerSize()
{
    int serverSize;
    cout << "Enter preferred hash table capacity: ";
    cin >> serverSize;
    return serverSize;
}
