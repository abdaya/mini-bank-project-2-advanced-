#ifndef _ADMINISTRATOR_CLASS
#define _ADMINISTRATOR_CLASS

const int USERNAME_SIZE = 15;
const int ADMIN_PASS_Size = 15;


class Administrator {
private:
	char user_name[USERNAME_SIZE];
	char password[ADMIN_PASS_Size];

public:
	Administrator();
	~Administrator();
	int  recordNumber();
	void writeAdmin();
	void readAdmin();
	int  signIn();
	void signUp();
	void displayInfo(int&);

};


#endif