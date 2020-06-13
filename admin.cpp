#include <iostream>
#include <fstream>
#include <cstring>
#include "Admin.h"
using std::fstream;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

fstream admin_object;
const char* admin_file_name = "admin.dat";



Administrator::Administrator() {
	strcpy_s(user_name, "unkown");
	strcpy_s(password, "unkown");
}
Administrator::~Administrator() {

}

void Administrator::writeAdmin() {
	cout << "Enter the first name	  : "; cin >> user_name;
	cout << "Enter the password		  : "; cin >> password;
}

void Administrator::readAdmin() {
	cout << "the first name		: " << user_name << endl;
	cout << "the password		: " << password << endl;
}

int Administrator::recordNumber() {
	int nb = 0;
	admin_object.open(admin_file_name, ios::binary | ios::in);
	if (!admin_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		admin_object.seekg(0, ios::end);
		nb = admin_object.tellg() / sizeof(*this);
		admin_object.close();
	}
	return nb;
}

void Administrator::signUp() {
	admin_object.open(admin_file_name, ios::binary | ios::app);
	if (!admin_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		this->writeAdmin();
		admin_object.write(reinterpret_cast<char*>(this), sizeof(*this));
		admin_object.close();
	}
}

int Administrator::signIn() {
	int nb = recordNumber();
	char userName[USERNAME_SIZE];
	char pass[ADMIN_PASS_Size];
	int position = -1;
	admin_object.open(admin_file_name, ios::binary | ios::in);
	if (!admin_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		cout << "The number of Admin accounts is : " << nb << endl;
		cout << "user name : "; cin >> userName;
		cout << "password  : "; cin >> pass;

		int i = 0;
		admin_object.seekg(0, ios::beg);
		admin_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (i < nb) {
			if ((strcmp(this->user_name, userName) == 0) && (strcmp(this->password, pass) == 0)) {
				cout << "welcome\nAdministrator : " << this->user_name << endl;
				position = i;
				break;
			}
			else {
				i++;
				admin_object.read(reinterpret_cast<char*>(this), sizeof(*this));
			}
		}

		admin_object.close();
	}
	return position;
}

void Administrator::displayInfo(int& position) {
	admin_object.open(admin_file_name, ios::binary | ios::in);
	if (!admin_object.is_open()) {
		cout << "ERROR" << endl;
	}
	else {
		admin_object.seekg(position * sizeof(*this), ios::beg);
		admin_object.read(reinterpret_cast<char*>(this), sizeof(*this));
		cout << "the account Information are : " << endl;
		this->readAdmin();
		admin_object.close();
	}
}

