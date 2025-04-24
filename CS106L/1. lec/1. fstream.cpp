#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
	// read from file
	ifstream file("test.txt");
	int newInt;
	file >> newInt; 
	cout << newInt << endl;

	// open error
	ifstream file2("newbee.txt");
	if (!file2.is_open())
		cerr << "file cannot be opened" << endl;

	// write in file
	ofstream writeFile("test.txt");
	writeFile << "Hello World!";

	return 0;
}
