#ifndef _ACCOUNT_CLASS
#define _ACCOUNT_CLASS

const int NAME_SIZE = 15;
const int PASS_Size = 15;


class Account {
private :
	char first_name[NAME_SIZE];
	char last_name[NAME_SIZE];
	char password[PASS_Size];
	double balance;
	int account_number;

public :
	Account();
	~Account();
	int  recordNumber();
	void writeAccount();
	void readAccount();
	int  signIn();
	void signUp();
	void deposit(int);
	void withdraw(int);
	void displayInfo(int&);

	// ************* administrator functions ************
	//************************************************

	void displayAllAccounts();
	void modifyAccount();
	int  checkAccount(int&);
	void searchAccount();
	void deleteAccount();
	void resetTheDatabase();
};


#endif