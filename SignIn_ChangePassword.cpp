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
