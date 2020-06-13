#include<iostream>
#include "Account.h"
#include "Admin.h"
								
using namespace std;

int main() {
	Account A,B;
	Administrator Admin;
	short choice1, choice2, choice3;
	char again1, again2, again3;
	
	//Admin.signUp();
	//use Admin.signUp() function to have the access to display,modify delete ... accounts
	do {
		cout << "\t\t1) Sign in" << endl;
		cout << "\t\t2) Sign up" << endl;
		cout << "\t\t3) Sign in as a Administrator" << endl;
		cout << "\t\t4)Quit" << endl;
		cout << "-->"; cin >> choice1;
		switch (choice1) {
		case 1: {
			int position = A.signIn();
			if (position == -1)
				cout << "The Account does not exist.";
			else {
				do {
					cout << "\t\t1) Display Info" << endl;
					cout << "\t\t2) Deposit" << endl;
					cout << "\t\t3) Withdraw" << endl;
					cout << "\t\t4) Quit" << endl;
					cout << "-->"; cin >> choice2;
					switch (choice2) {
					case 1: A.displayInfo(position); break;
					case 2: A.deposit(position); break;
					case 3: A.withdraw(position); break;
					case 4: {cout << "Thank you" << endl; exit(EXIT_SUCCESS); } break;
					default: cout << "The Number entered is not accurate" << endl;
					}
					cout << "Do you have another task ?: "; cin >> again2;
				} while (again2 == 'y' || again2 == 'Y');
			}
		}break;
		case 2: B.signUp(); break;
		case 3: {
			int position = Admin.signIn();
			if (position == -1) cout << "This Admin does not exist." << endl;
			else {
				do {
					cout << "\t\t1) Display all accounts" << endl;
					cout << "\t\t2) Search for an accout" << endl;
					cout << "\t\t3) Modify an account" << endl;
					cout << "\t\t4) Delete an account" << endl;
					cout << "\t\t5) Reset the Database" << endl;
					cout << "\t\t6) Quit" << endl;
					cout << "-->"; cin >> choice3;
					switch (choice3) {
						case 1: A.displayAllAccounts(); break;
						case 2: A.searchAccount(); break;
						case 3: A.modifyAccount(); break;
						case 4: A.deleteAccount(); break;
						case 5: A.resetTheDatabase(); break;
						case 6: {cout << "Thank you" << endl; exit(EXIT_SUCCESS); } break;
						default: cout << "The Number entered is not accurate" << endl;
					}
					cout << "Do you have another task ?: "; cin >> again3;
				} while (again3 == 'y' || again3 == 'Y');
			}
		} break;
		case 4: {cout << "Thank you" << endl; exit(EXIT_SUCCESS); } break;
		default : cout << "The Number entered is not accurate" << endl;
		}
		cout << "Do you have another task ?: "; cin >> again1;
	} while (again1 == 'y' || again1 == 'Y');
	
	cin.get();
}