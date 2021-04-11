#include "DataStructure.h"

// Function to take valid username from user and their password. Then take password from username file to compare
void Read_Name_Pass(ifstream& in, string& username, string& password)
{
	string userfile, passfile;
	string path;

	in.open("notexist.txt");

	// Read in username and password
	while (!in.is_open())
	{
		cout << "Username: ";
		getline(cin, username);

		path = "data\\" + username + ".txt";

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

	while (password != passfile)
	{
		cout << "Incorrect password. Enter again!" << endl;
		cout << "Password: ";
		getline(cin, password);
	}
}

// Function to log in
// Function will run until logging in sucessfully
void login(ifstream& in, int& role)
{
	string username, password;	

	Read_Name_Pass(in, username, password);
	
	if ((int)username[0] >= 48 && (int)username[0] <= 57)
		role = 1;
	else
		role = 2;

	cout << "Log in successfully!" << endl;
}

// Function to check if the username entered by student is valid
bool checkStringofStu(string s)
{
	if (s.length() != 8)
		return false;

	for (int i = 0; i < (s.length()); ++i)
		if ((int)s[i] < 48 || (int)s[i] > 57)
			return false;

	return true;
}

// Function to check if the username entered by staff is valid
bool checkStringofStaff(string s)
{
	if (s.length() <= 6)
		return false;

	string compare = "admin@";

	for (int i = 0; i < 6; ++i)
		if (s[i] != compare[i])
			return false;

	return true;
}

// Function to register
void signup(ifstream& in, ofstream& out, int& role)
{
	string username, password;
	string path;
	bool check;

	cout << "1. Student" << endl;
	cout << "2. Staff" << endl;

	// Choose student or staff
	int choice;
	do
	{
		cout << "Enter your choice (1 or 2): ";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	
	role = choice;
	
	cin.ignore();

	// Read in username and password
	do
	{
		in.close(); // Close file after checking

		if (choice == 1)
		{
			// Read in the username with the required student ID number
			do
			{
				cout << "Username(username is your Student ID): ";
				getline(cin, username);

				check = checkStringofStu(username);

				if (!check)
					cout << "Username is your Student ID!" << endl;
			} while (!check);
		}
		else
		{
			// Read in the username with admin@ at beginning
			do
			{
				cout << "Username(start with admin@): ";
				getline(cin, username);

				check = checkStringofStaff(username);

				if (!check)
					cout << "Username must be started by admin@" << endl;
			} while (!check);

		}

		// Read in password
		cout << "Password: ";
		getline(cin, password);

		// Check whether username is used
		path = "data\\" + username + ".txt";
		in.open(path);
		if (in.is_open())
			cout << "Username is already taken!" << endl;
	} while (in.is_open());
	
	// Write username and password in username.txt
	out.open(path);
	if (!out.is_open())
	{
		cout << "Can not create file" << endl;
		return;
	}

	out << username << endl;
	out << password << endl;
	out.close();
	
	cout << "Sign up successfully! << endl;
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
		cout << "Can not create file" << endl;
		return;
	}

	out << username << endl;
	out << newpassword << endl;

	out.close();
}
