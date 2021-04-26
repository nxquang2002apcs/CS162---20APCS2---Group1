#include "DataStructure.h"

int main() {
	ifstream in;
	int role = 1;
	string studentID;
	if (login(in, role, studentID)) {
		readAll();
		if (role == 1)
			StudentInterface(studentID);
		else StaffInterface();
		delete_everything();
	}
	in.close();

	
	return 0;
}

