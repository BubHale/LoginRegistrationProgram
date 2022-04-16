/*
Purpose: Emulates a login/registration system where user can choose to login or register if they please. Login will take a username password
check it to make sure it follows username and password guidelines and compare it to lines from input file to see if there is a login that exists. If 
yes user is logged in. Registration does the same thing except it won't output users credentials if another username is the same and it does output if 
provided credentials are unique and pass the credential verification
Author: Samuel Hale
Creation Date: 4/23/22
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Menu() {
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << "                          Welcome to the login/registration program!                    \n";
	cout << "                          Please enter L to login; R to register; or X to quit          \n";
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
}

//Utility function
void loadFile(string fname, fstream& file)
{
	file.open(fname.c_str());
	if (file.fail())
	{
		cout << "Cannot open file " << fname << endl;
	}
}

//Purpose: Take username check for user name guidelines
//Input: Takes in a string for the userName
//Output: Outputs a boolean to tell the function true if username checks the guidelines or false if it does not check guidelines
bool UserName(string userName) {
	if (isalpha(userName.at(0)) && userName.size() >= 5) {
		return true;
	}
	else return false;
}

//Purpose: Takes password in and checks for password guidelines
//Input: Takes in string for password
//Output: Outputs true if password is good outputs false if password is not good
bool PassWord(string passWord) {
	if (isalpha(passWord.at(0)) && isupper(passWord.at(0)) && passWord.size() >= 8) {
		for (int i = 0; i < passWord.size(); i++) {
			if (isdigit(passWord.at(i))) {
				return true;
			}
		}
	}
	else return false;
}

//Purpose: Represents user account with username and password
struct UserAccount {
	string userName;
	string passWord;
};

//Purpose: Registers users credentials with provided username and password
//Input: user date type 
//Ouput: Outputs true if no other username like it exists and it was able to register false otherwise
bool Register(UserAccount user) {
	/*FILE LOADING*/
	string inputFilename = "Database.txt";
	string line;
	bool echo = true;
	fstream inputFile;
	loadFile(inputFilename, inputFile);
	/*Gets users username and password*/
	cout << "Please enter username:";
	cin >> user.userName;
	cout << endl;
	while (UserName(user.userName) != true) {
		cout << "Username must start with a letter and be longer than 5 characters! Please try again:";
		cin >> user.userName;
		cout << endl;
	}
	cout << "Please enter password:";
	cin >> user.passWord;
	cout << endl;
	while (PassWord(user.passWord) != true) {
		cout << "Password must start with a capital letter, contain a number and be longer than 8 characters! Please try again:";
		cin >> user.passWord;
		cout << endl;
	}
	/*SEARCHES FOR EXISTING USER CREDENTIALS PRIOR TO WRITING*/
	while (getline(inputFile, line)) { // Gets user password combo on a line
		stringstream lineSS(line); // throws that line in the stream
		string tempCompare; // variable for comparing current username/password to our users credentials
		getline(lineSS, tempCompare, ' '); // Gets the username or password from line onto our temp compare variable
		if (user.userName == tempCompare) { // compares username to temp compare
			cout << "USERNAME ALREADY EXISTS PLEASE TRY AGAIN WITH A NON EXISTING USERNAME!\n";
			return false;
		}
		else if (inputFile.eof()) { // checks if were at the end of the file because if so return false
			inputFile.close();
		}
	}
	/*WRITES USERS ACCOUNT INFO OUT TO FILE*/
	inputFile.open(inputFilename, ios_base::app);
	inputFile << endl << user.userName << " " << user.passWord;
	inputFile.close();
	return true;
}

//Purpose: Logs user in based on provided username and password
//Input: user data type
//Output: returns true if it was able to login false otherwise
bool LogIn(UserAccount user) {
	/*FILE LOADING*/
	string inputFilename = "Database.txt";
	string line;
	bool echo = true;
	fstream inputFile;
	loadFile(inputFilename, inputFile);
	/*Gets users username and password*/
	cout << "Please enter username:";
	cin >> user.userName;
	cout << endl;
	while (UserName(user.userName) != true) {
		cout << "Username must start with a letter and be longer than 5 characters! Please try again:";
		cin >> user.userName;
		cout << endl;
	}
	cout << "Please enter password:";
	cin >> user.passWord;
	cout << endl;
	while (PassWord(user.passWord) != true) {
		cout << "Password must start with a capital letter, contain a number and be longer than 8 characters! Please try again:";
		cin >> user.passWord;
		cout << endl;
	}
	/*COMPARATION PORTION OF LOGIN*/
	while (getline(inputFile, line)) { // Gets user password combo on a line
		stringstream lineSS(line); // throws that line in the stream
		string tempCompare; // variable for comparing current username/password to our users credentials
		getline(lineSS, tempCompare, ' '); // Gets the username or password from line onto our temp compare variable
		if (user.userName == tempCompare) { // compares username to temp compare
			getline(lineSS, tempCompare, ' '); // gets our password onto temp compare
			if (user.passWord == tempCompare) { // compares password to temp compare
				inputFile.close();
				return true; // returns true if it makes it here because password and username would be the same
			}
		}
		else if (inputFile.eof()) { // checks if were at the end of the file because if so return false
			inputFile.close();
			return false;
		}
	}
	return false;

}

//PURPOSE: Facilitates program functionality
int main() {
	/*VARIABLE DECLARATION*/
	UserAccount user;
	char userInput = 'I';

	/*START OF MAIN*/
	while (toupper(userInput) != 'X') {
		Menu();
		cin >> userInput;
		while (toupper(userInput) != 'L' && toupper(userInput) != 'R' && toupper(userInput) != 'X') {
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
			cout << "                          Incorrect input; Correct options are L;R;orX                  \n";
			cout << "                                      Please try again!                                 \n";
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
			cin >> userInput;
		}
		/*Handles Login Decision*/
		if (toupper(userInput) == 'L') {
			if (LogIn(user) == true) {
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				cout << "                          Congratulations you have logged into the server!              \n";
				cout << "                                      Enjoy your stay!                                  \n";
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
			}
			else {
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				cout << "                          That username and password do not exist                       \n";
				cout << "                          in our system would you like to register instead?             \n";
				cout << "                                            (Y/N?)                                      \n";
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				cin >> userInput;
				if (toupper(userInput) == 'Y') {
					if (Register(user) == true) {
						cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
						cout << "                          Congratulations you have registered to the server!            \n";
						cout << "                                      Enjoy your stay!                                  \n";
						cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
					}
				}
				else {
					cout << "Good bye!\n";
					system("pause");
					return 0;
				}
			}
		}
		else if (toupper(userInput) == 'R') {
			if (Register(user) == true) {
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				cout << "                          Congratulations you have registered to the server!            \n";
				cout << "                                      Enjoy your stay!                                  \n";
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
			}
		}
		else {
			cout << "Good bye!\n";
			system("pause");
			return 0;
		}
	}
	system("pause");

	return 0;
}