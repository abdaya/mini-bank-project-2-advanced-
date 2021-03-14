#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio> //for calling remove() and rename() for files
#include "Account.h"
using std::fstream;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

fstream account_object;
const char* account_file_name = "account.dat";



Account::Account() {
	strcpy_s(first_name,"unkown");
	strcpy_s(last_name, "unkown");
	strcpy_s(password, "unkown");
	account_number = 0;
	balance = 0.0f;
}
Account::~Account() {
}

void Account::writeAccount() {
	cout << "Enter the first name	  : "; cin >> first_name;
	cout << "Enter the last name	  : "; cin >> last_name;
	cout << "Enter the account number : "; cin >> account_number;
	cout << "Enter the password		  : "; cin >> password;
}

void Account::readAccount() {
	cout << "the first name		: "<<first_name<<endl;
	cout << "the last name		: "<<last_name << endl;
	cout << "the account number      : "<< account_number << endl;
	cout << "the Balance	        : $" << balance << endl;
}

// to calculates the number of records in the file.
int Account::recordNumber() {
	int nb = 0;
	account_object.open(account_file_name, ios::binary | ios::in);
	if (!account_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		account_object.seekg(0, ios::end);
		nb = account_object.tellg() / sizeof(*this);
		account_object.close();
	}
	return nb;
}

//sign up() is a function that add a record to the file.
void Account::signUp() {
	account_object.open(account_file_name, ios::binary | ios::app);
	if (!account_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		this->writeAccount();
		account_object.write(reinterpret_cast<char*>(this), sizeof(*this));
		account_object.close();
	}
}
//signIn() is a function that opens a session for the user if the account exist.
int Account::signIn() {
	int nb = recordNumber();
	char lastName[NAME_SIZE];
	char pass[PASS_Size];
	int position = -1;
	account_object.open(account_file_name, ios::binary | ios::in);
	if (!account_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		if (nb == 0) cout << "The Database is comletely empty." << endl;
		else {
			cout << "The number of account is : " << nb << endl;
			cout << "last name : "; cin >> lastName;
			cout << "password  : "; cin >> pass;

			int i = 0;
			account_object.seekg(0, ios::beg);
			account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
			while (i < nb) {
				if ((strcmp(this->last_name, lastName) == 0) && (strcmp(this->password, pass) == 0)) {
					position = i;
					break;
				}
				else {
					i++;
					account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
				}
			}
		}
		
		account_object.close();
	}
	return position;
}

void Account::displayInfo(int& position) {
	account_object.open(account_file_name, ios::binary | ios::in);
	if (!account_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		account_object.seekg(position * sizeof(*this), ios::beg);
		account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		cout << "the account Information are : " << endl;
		this->readAccount();
		account_object.close();
	}
}

//deposit function will take the postition that the function signIn return to 
//make the user able only to deposit an amount into mirely his account

void Account::deposit(int position) {
	account_object.open(account_file_name, ios::binary | ios::in | ios::out) ;
	if (account_object.fail())
		cout << "ERROR" << endl;
	else {
		double amount;
		cout << "Enter the amount you want to deposit : "; cin >> amount;
		while (amount < 0) {
			cout << "The amount entered is not correct. try again : ";
			cin >> amount;
		}
		
		account_object.seekg(position * sizeof(*this), ios::beg);
		account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		this->balance += amount;
		account_object.seekp(position * sizeof(*this), ios::beg);
		account_object.write(reinterpret_cast<char*>(this), sizeof(*this));
		account_object.close();
	}
}

//withdraw function will take the postition that the function signIn return to 
//make the user able only to withdraw an amount from mirely his account

void Account::withdraw(int position) {
	account_object.open(account_file_name, ios::binary | ios::out | ios::in);
	if (account_object.fail())
		cout << "ERROR" << endl;
	else {
		double amount;	
		cout << "Enter the amount : "; cin >> amount;
		while ((amount < 0) || (amount > (this->balance))) {
			cout << "The amount entered is not correct. try again : ";
			cin >> amount;
		}
		account_object.seekg(position * sizeof(*this), ios::beg);
		account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		this->balance -= amount;
		account_object.seekp(position * sizeof(*this), ios::beg);
		account_object.write(reinterpret_cast<char*>(this), sizeof(*this));
		account_object.close();
	}
}

//********************************************************************
//these functions are accessed by only the administrator
//*****************************************************************

void Account::displayAllAccounts() {
	int n = recordNumber();
	account_object.open(account_file_name, ios::binary | ios::in);
	if (account_object.fail())
		cout << "ERROR" << endl;
	else {
		if (n == 0) cout << "the file is completely ampty" << endl;
		else {
			//account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
			for (int i = 0; i < n; i++) {
				cout << "Record : " << i + 1 << endl<<endl;
				account_object.seekg(i * sizeof(*this),ios::beg);
				account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
				this->readAccount();
				cout << "The password is         : " << this->password << endl;
				cout << endl;
			}
		}
		account_object.close();
	}
}
//check() is a function that checks if and account exist and returns its position :

int Account::checkAccount(int& accN) {
	int n = recordNumber();
	int position = -1;
	account_object.open(account_file_name, ios::binary | ios::in);
	if (account_object.fail())
		cout << "ERROR" << endl;
	else {
		int i = 0;
		account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (i < n) {
			if (this->account_number == accN) {
				position = i;
				break;
			}
			else {
				i++;
				account_object.read(reinterpret_cast<char*>(this), sizeof(*this));			
			}
		}	
		account_object.close();
	}
	return position;
}


// modifyAccount()

void Account::modifyAccount() {
	int accN;
	cout << "Enter the account number : "; cin >> accN;
	int position = checkAccount(accN);
	account_object.open(account_file_name, ios::binary | ios::in | ios::out);
	if (account_object.fail())
		cout << "ERROR" << endl;
	else {
		if (position == -1) cout << "the Account does not exist" << endl;
		else {	
			cout << "Modify the account : " << endl;
			this->writeAccount();
			account_object.seekp(position * sizeof(*this), ios::beg);
				account_object.write(reinterpret_cast<char*>(this), sizeof(*this));
				cout << "Modification is done. " << endl;
				cout << endl;
		}
		account_object.close();
	}
}


// searchAccount() is a function that search for an account if it exist
//and return its info to the admin

void Account::searchAccount() {
	int accN;
	cout << "Enter the Account Number : "; cin >> accN;
	int position = checkAccount(accN);
	if (position == -1) {
		cout << "The account does not Exist" << endl;
	}
	else {
		account_object.open(account_file_name, ios::in | ios::binary);
		account_object.seekg(position * sizeof(*this), ios::beg);
		account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		this->readAccount();
		account_object.close();
	}
}

// delete an account from the database::

void Account::deleteAccount() {
	int n = recordNumber();
	int accN;
	cout << "Enter the Account Number of the account you want to delete : "; cin >> accN;
	int position = checkAccount(accN);
	if (position == -1) cout << "The account does not exist." << endl;
	else {
		account_object.open(account_file_name, ios::binary | ios::in);
		if (!account_object.is_open()) {
			cout << "ERROR" << endl;
		}
		else {
			fstream account_object2;
			const char* account_file_name2 = "accountCopy.dat";
			account_object2.open(account_file_name2, ios::binary |ios::out | ios::app);
			//account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
			for (int i = 0; i < n; i++) {
				account_object.seekg(i * sizeof(*this), ios::beg);
				account_object.read(reinterpret_cast<char*>(this), sizeof(*this));
				if (position == i)
					continue;
				else {
					account_object2.write(reinterpret_cast<char*>(this), sizeof(*this));					
				}
			}
			account_object2.close();
			account_object.close();
			remove("account.dat");
			rename("accountCopy.dat", "account.dat");
			cout << "Deletion is done." << endl;
		}		
	}
}

// reset the database.
void Account::resetTheDatabase() {
	remove("account.dat");
	cout << "the Database is formated" << endl;
	account_object.open(account_file_name, ios::out | ios::binary | ios::app); //create a new file with the same name
	account_object.close();
}
