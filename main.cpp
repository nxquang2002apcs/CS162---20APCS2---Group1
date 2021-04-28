#include "DataStructure.h"

int main() {
	ifstream in;
	int role = 1;
	string studentID;
	bool logSuccess = false;
	readAll();
	while (true)   {
		if (login(in, role, studentID)) {
			if (role == 1)
				StudentInterface(studentID);
			else StaffInterface();
		}
		else break;  
	}
	delete_everything();

	in.close();

	
	return 0;
}

