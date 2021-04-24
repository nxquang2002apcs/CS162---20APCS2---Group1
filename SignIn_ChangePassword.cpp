#include "DataStructure.h"

// Function to take valid username from user and their password. Then take password from username file to compare
bool Read_Name_Pass(ifstream& in, string& username, string& password)
{
	string userfile, passfile;
	string path;

	in.open("notexist.txt");

	// Read in username and password
	while (!in.is_open())
	{
		gotoXY(40, 8);
		cout << "Username: ";
		getline(cin, username);

		path = "data\\Username_password\\" + username + ".txt";

		gotoXY(40, 10);
		cout << "Password: ";
		getline(cin, password);

		in.open(path);

		if (!in.is_open())
			cout << "Invadid Username. Enter again!" << endl;
	}

	// Read username and password from file to compare
	getline(in, userfile);
	getline(in, passfile);

	in.close();
	
	int wrong_pass = 0;
	while (password != passfile)
	{
		wrong_pass++;
		if (wrong_pass > 5) {
			cout << "You are failed in login for five times! Cannot try anymore!";
			_getch();
			return false;
		}
		cout << "Incorrect password. Enter again!" << endl;
		cout << "Password: ";
		getline(cin, password);
	}
	return true;
}


// Function to log in
// Function will run until logging in sucessfully
bool login(ifstream& in, int& role, string& studentID)
{
	string username, password;

	if (Read_Name_Pass(in, username, password)) {
		if ((int)username[0] >= 48 && (int)username[0] <= 57) {
			role = 1;
			studentID = username;
		}
		else
			role = 2;
		gotoXY(40, 12);
		cout << "Log in successfully!" << endl;
		cout << endl;
		gotoXY(40, 15);
		cout <<"Please waiting! Loading ";
		Nocursortype();
		for (int i = 0; i <= 100; ++i) {
			gotoXY(65, 15);
			cout << i << "%";
			Sleep(30);
		}
		UnNocursortype();
		return true;
	}
	else return false;
	
}


// Function to change password
void changePassword(ifstream& in, ofstream& out)
{
	string username, password, newpassword;

	Read_Name_Pass(in, username, password);

	cout << "New password: ";
	getline(cin, newpassword);

	string path = "data\\" + username + ".txt";
	out.open(path);
	if (!out.is_open())
	{
		cout << "Can not open file" << endl;
		cout << "Changing password failed!" << endl;
		return;
	}

	out << username << endl;
	out << newpassword << endl;

	out.close();

	cout << "Change password successfully." << endl;
}
