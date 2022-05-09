/*
Author: Melissa Paul
Creation Date: 12/1/18
Last Modification Date: 12/14/18
Purpose: To build a simple banking application
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct account {
	int accountNumber;
	int pin;
	string first;
	string last;
	float balance;
};

// Function prototypes

void readAccountData(ifstream&, account[], int&);
void balance(account[], int);
int searchAccount(int, account[], int);
void deposit(account[], int);
void withdrawal(account[], int);
void transfer(account[], int);
void newAccount(account[], int&);
void changePinNumber(account[], int);
void quit(ofstream&, account[], int);

/*
Author: Melissa Paul
Creation Date: 12/1/18
Last Modification Date: 12/14/18
Purpose: To call the function that creates the array with bank info, display the banking system menu, and call the 
function for each banking operation
*/
int main() {
	const int SIZE = 500;
	account mybank[SIZE];
	int actualSize;
	ifstream accountData;
	ofstream newAccountData;
	char choice;

	readAccountData(accountData, mybank, actualSize);

	cout << "----------------------------------------------------------------------" << endl;
	cout << "                    WELCOME TO THE BANKING SYSTEM                     " << endl;
	cout << "----------------------------------------------------------------------" << endl;

	do {
		cout << endl << "A.) Balance" << endl;
		cout << "B.) Deposit" << endl;
		cout << "C.) Withdrawal" << endl;
		cout << "D.) Transfer" << endl;
		cout << "E.) New Account" << endl;
		cout << "F.) Change PIN Number" << endl;
		cout << "G.) Quit" << endl;
		cout << "----------------------------------------------------------------------" << endl;

		cout << endl << "Please select an operation: ";
		cin >> choice;

		switch(toupper(choice)) {
			case 'A':
				balance(mybank, actualSize);
				break;
			case 'B':
				deposit(mybank, actualSize);
				break;
			case 'C':
				withdrawal(mybank, actualSize);
				break; 
			case 'D':
				transfer(mybank, actualSize);
				break; 
			case 'E':
				newAccount(mybank, actualSize);
				break;
			case 'F':
				changePinNumber(mybank, actualSize);
				break;
			case 'G':
				quit(newAccountData, mybank, actualSize);
				break;
			default:
				cout << "Error: Invalid choice. Please enter an option A-G." << endl;
		}

	} while (toupper(choice) != 'G');

	system("pause");
	return 0;
}

// Function definitions

/*
Author: Melissa Paul
Input: File of account data "bank.txt"
Output: The function returns nothing, but an array mybank of type account and its actual size passed by reference are 
created
Purpose: To open the file "bank.txt," read data from it, and assign it to an array mybank of type account, 
closing the file at the end
*/
void readAccountData(ifstream& ins, account mybank[], int& actualSize) {
	ins.open("bank.txt");
	actualSize = 0;

	while (!ins.eof()) {
		ins >> mybank[actualSize].accountNumber;
		ins >> mybank[actualSize].pin;
		ins >> mybank[actualSize].first;
		ins >> mybank[actualSize].last;
		ins >> mybank[actualSize].balance;
		actualSize++;
	}

	ins.close();
}

/*
Author: Melissa Paul
Input: The array mybank of type account and its size
Output: The function returns nothing but displays the balance or an error message
Purpose: To ask users for their account and PIN number, use a search function to see if the account exists,
and display the balance or an appropriate error message
*/
void balance(account mybank[], int size) {
	int accountNumber, pin, i;

	cout << endl << "Please provide the account number: ";
	cin >> accountNumber;

	cout << "Please provide the PIN number: ";
	cin >> pin;

	i = searchAccount(accountNumber, mybank, size);

	if ((i != -1) && (mybank[i].pin == pin)) {
		cout << "The balance in your account is: $" << mybank[i].balance << endl;
	}
	else if ((i != -1) && (mybank[i].pin != pin)) {
		cout << "Sorry! Incorrect PIN" << endl;
	}
	else {
		cout << "Sorry! The account number you provided does not exist!" << endl;
	}
}

/*
Author: Melissa Paul
Input: The account number, array mybank of type account, and the array's size
Output: The index i of where the account number is located in the array or -1 if it is not found
Purpose: To search if the account number exists in the array, returning its index if it is found and
-1 if it is not
*/
int searchAccount(int accountNumber, account mybank[], int size) {
	for (int i = 0; i < size; i++) {
		if (mybank[i].accountNumber == accountNumber) {
			return i;
		}
	}

	return -1;
}

/*
Author: Melissa Paul
Input: The array mybank of type account and the its size
Output: The function returns nothing but displays whether the deposit was successful or an error message
Purpose: To ask users for their account number, PIN number, and amount to deposit, verifying whether 
the account exists and either performing the deposit or displaying an error message
*/
void deposit(account mybank[], int size) {
	int accountNumber, pin, i;
	float depositAmount;

	cout << endl << "Please provide the account number: ";
	cin >> accountNumber;

	cout << "Please provide the PIN number: ";
	cin >> pin;

	cout << "Please provide the amount you would like to deposit: ";
	cin >> depositAmount;

	i = searchAccount(accountNumber, mybank, size);

	if ((i != -1) && (mybank[i].pin == pin)) {
		mybank[i].balance += depositAmount;
		cout << "Deposit successful!" << endl;
	}
	else if ((i != -1) && (mybank[i].pin != pin)) {
		cout << "Sorry! Incorrect PIN" << endl;
	}
	else {
		cout << "Sorry! The account number you provided does not exist!" << endl;
	}

}
/*
Author: Melissa Paul
Input: The array mybank of type account and the its size
Output: The function returns nothing but displays whether the withdrawal was successful or an error message
Purpose: To ask users for their account number, PIN number, and amount to withdraw, verifying whether
the account exists and has sufficient funds. Then, either the withdrawal is performed or an error message 
is displayed
*/
void withdrawal(account mybank[], int size) {
	int accountNumber, pin, i;
	float withdrawAmount;

	cout << endl << "Please provide the account number: ";
	cin >> accountNumber;

	cout << "Please provide the PIN number: ";
	cin >> pin;

	cout << "Please provide the amount you would like to withdraw: ";
	cin >> withdrawAmount;

	i = searchAccount(accountNumber, mybank, size);

	if ((i != -1) && (mybank[i].pin == pin) && (mybank[i].balance >= withdrawAmount)) {
		mybank[i].balance -= withdrawAmount;
		cout << "Withdraw successful!" << endl;
	}
	else if ((i != -1) && (mybank[i].pin == pin) && (mybank[i].balance < withdrawAmount)) {
		cout << "Sorry! Insufficient fund" << endl;
	}
	else if ((i != -1) && (mybank[i].pin != pin)) {
		cout << "Sorry! Incorrect PIN" << endl;
	}
	else {
		cout << "Sorry! The account number you provided does not exist!" << endl;
	}
}
/*
Author: Melissa Paul
Input: The array mybank of type account and the its size
Output: The function returns nothing but displays the whether the transfer was successful or an error message
Purpose: To ask users for their account number, PIN number, target account number, and amount to transfer, 
verifying whether both accounts exist and the prior has sufficient funds. Then, either the transfer is performed 
or an error message is displayed
*/
void transfer(account mybank[], int size) { 
	int accountNumber, pin, i1, i2, targetAccountNumber;
	float transferAmount;

	cout << endl << "Please provide the account number: ";
	cin >> accountNumber;

	cout << "Please provide the PIN number: ";
	cin >> pin;

	cout << "Please provide the destination account number: ";
	cin >> targetAccountNumber;

	cout << "Please provide the amount you would like to transfer: ";
	cin >> transferAmount;

	i1 = searchAccount(accountNumber, mybank, size);
	i2 = searchAccount(targetAccountNumber, mybank, size);

	if ((i1 != -1) && (mybank[i1].pin == pin) && (i2 != -1) && (mybank[i1].balance >= transferAmount)) {
		mybank[i1].balance -= transferAmount;
		mybank[i2].balance += transferAmount;
		cout << "Transfer successful!" << endl;
	}
	else if ((i1 != -1) && (mybank[i1].pin == pin) && (i2 != -1) && (mybank[i1].balance < transferAmount)) {
		cout << "Sorry! Insufficient fund" << endl;
	}
	else if ((i1 != -1) && (mybank[i1].pin != pin)) {
		cout << "Sorry! Incorrect PIN" << endl;
	}
	else if ((i1 != -1) && (mybank[i1].pin == pin) && (i2 == -1)) {
		cout << "Sorry! The destination account number you provided does not exist!" << endl;
	}
	else {
		cout << "Sorry! The source account number you provided does not exist!" << endl;
	}
}

/*
Author: Melissa Paul
Input: The array mybank of type account and the its size
Output: The function returns nothing but displays the whether the account creation was successful, adding the 
information to the array, or an error message.
Purpose: To ask users for their new account information, adding it to the array after verifying that the account
does not already exist. If it does, an error message is displayed. 
*/
void newAccount(account mybank[], int& size) {
	int accountNumber, pin, i;
	float balance;
	string first, last;

	cout << endl << "Please provide the new account number: ";
	cin >> accountNumber;

	cout << "Please provide the new PIN number: ";
	cin >> pin;

	cout << "Please provide the first name: ";
	cin >> first;

	cout << "Please provide the last name: ";
	cin >> last;

	cout << "Please provide the balance: ";
	cin >> balance;

	i = searchAccount(accountNumber, mybank, size);

	if (i == -1) {
		mybank[size].accountNumber = accountNumber;
		mybank[size].pin = pin;
		mybank[size].first = first;
		mybank[size].last = last;
		mybank[size].balance = balance;
		size++;
		cout << "New account creation successful!" << endl;
	}
	else {
		cout << "Sorry! The account number you provided already exists!" << endl;
	}
}

/*
Author: Melissa Paul
Input: The array mybank of type account and the its size
Output: The function returns nothing but displays the whether the PIN change was successful, updating it in the
array, or an error message
Purpose: To ask users for their account number, PIN number, and new PIN number, verifying whether the account
exists and pin is correct. Then, either the PIN number is updated in the array or an error message is displayed.
*/
void changePinNumber (account mybank[], int size) {
	int accountNumber, pin, i, newPin;

	cout << endl << "Please provide the account number: ";
	cin >> accountNumber;

	cout << "Please provide the PIN number: ";
	cin >> pin;

	cout << "Please provide the new PIN number: ";
	cin >> newPin;

	i = searchAccount(accountNumber, mybank, size);

	if ((i != -1) && (mybank[i].pin == pin)) {
		mybank[i].pin = newPin;
		cout << "PIN number change successful!" << endl;
	}
	else if ((i != -1) && (mybank[i].pin != pin)) {
		cout << "Sorry! Incorrect PIN" << endl;
	}
	else {
		cout << "Sorry! The account number you provided does not exist!" << endl;
	}
}

/*
Author: Melissa Paul
Input: An output stream to override the "bank.txt" file, the array mybank of type account, and its size
Output: The function returns nothing but updates the "bank.txt" file and displays a "Bye" message
Purpose: To display a “Bye” message and overwrite the file “bank.txt” with the information contained in the array
*/
void quit(ofstream& outs, account mybank[], int size) {
	outs.open("bank.txt");

	for (int i = 0; i < size; i++) {
		outs << mybank[i].accountNumber << " " << mybank[i].pin << " " << mybank[i].first
			<< " " << mybank[i].last << " " << mybank[i].balance << endl;
	}

	outs.close();

	cout << endl << "Thank you for using the Banking System! You have successfully exited! Goodbye!" << endl;
}
