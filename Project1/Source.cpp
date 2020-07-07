#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

typedef struct
{
	char name[21];				//Recipient's name
	char phone_num[12];			//Recipient's phone number
	char e_mail[31];			//Recipient's email
}CUSTOMER;

typedef struct
{
	char name[21];				 //Package name
	char company[31];			 //Courier company
	char user[21];			     //Sender's name
	char arr_date[11];			 //Package arrival date
	char col_date[11];		     //Package collection date
}PACKAGE;

void list(CUSTOMER rec[], PACKAGE det[], int rows);
int search(CUSTOMER rec[], PACKAGE det[], int rows);
void show(CUSTOMER rec[], PACKAGE det[], int rows);
void update(CUSTOMER rec[], PACKAGE det[], int rows);

int main(void)
{
	CUSTOMER record[20];
	PACKAGE detail[20];
	int index = -1, choice;

	ifstream inFile("data.txt");
	if (!inFile)
	{
		cout << "Error opening input file\n";
	}
	else
	{
		inFile.getline(record[++index].name, 21);
		while (inFile)
		{
			inFile.getline(record[index].phone_num, 12);
			inFile.getline(record[index].e_mail, 31);
			inFile.getline(detail[index].name, 21);
			inFile.getline(detail[index].company, 31);
			inFile.getline(detail[index].user, 21);
			inFile.getline(detail[index].arr_date, 11);
			inFile.getline(detail[index].col_date, 11);

			if (inFile.peek() == '\n')
				inFile.ignore(256, '\n');

			inFile.getline(record[++index].name, 21);
		}
		inFile.close();

		do
		{
			cout << "Do you want to:\n";
			cout << "1. List all records\n";
			cout << "2. Search the records\n";
			cout << "3. Update the records\n";
			cout << "4. Exit\n";
			cout << "Enter choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1: list(record, detail, index); break;
			case 2: show(record, detail, index); break;
			case 3: update(record, detail, index); break;
			case 4: exit(100); break;
			default: cout << "Invalid choice.\n" << endl; break;
			}
		} while (choice != 4);

		ofstream outFile("data.txt");
		if (!outFile)
			cout << "Error opening output file, records are not updated.\n";
		else
		{
			for (int i = 0; i < index; i++)
			{
				outFile << record[i].name << endl;
				outFile << record[i].phone_num << endl;
				outFile << record[i].e_mail << endl;
				outFile << detail[i].name << endl;
				outFile << detail[i].company << endl;
				outFile << detail[i].user << endl;
				outFile << detail[i].arr_date << endl;
				outFile << detail[i].col_date << endl;
			}
			outFile.close();
		}

	}
	return 0;
}

void list(CUSTOMER rec[], PACKAGE det[], int rows)
{
	cout << "\n\tE-commerce Delivery Centre\n" << endl;

	for (int i = 0; i < rows; i++)
	{
		cout << "Full Name\t" << "Phone Number\t\t" << "Email" << endl;
		cout << "---------\t------------\t\t-----" << endl;
		cout << rec[i].name << "\t" << rec[i].phone_num << "\t\t" << rec[i].e_mail << endl;
		cout << endl;
		cout << "Package name\t" << "Courier Company\t\t" << "Sender" << endl;
		cout << "------------\t---------------\t\t------" << endl;
		cout << det[i].name << setw(5) << "\t" << det[i].company << "\t\t" << det[i].user << endl;
		cout << endl;
		cout << "Arrival date\t" << "Collection date" << endl;
		cout << "------------\t---------------" << endl;
		cout << det[i].arr_date << "\t" << det[i].col_date << endl;
		cout << "___________________________________________________________________________" << endl;
	}
	return;
}


int search(CUSTOMER rec[], PACKAGE det[], int rows)
{
	int option, i = -1;
	char sName[21], sPhone[12], sEmail[31];
	bool found = false;

	cout << endl;
	cout << "Do you want to search the customer by name, phone or email ? " << endl;

	do
	{
		cout << "Press 1 to search by name" << endl;
		cout << "Press 2 to search by phone number" << endl;
		cout << "Press 3 to search by email" << endl;
		cin >> option;

		if (option == 1)
		{
			cout << "Enter the customer name to search : ";
			rewind(stdin);
			cin.getline(sName, 21);

			while (i < rows && !found)
			{
				if (strcmp(sName, rec[i].name) == 0)
					found = true;
				else
					i++;
			}
		}
		else if (option == 2)
		{
			cout << "Enter the customer phone number to search : ";
			rewind(stdin);
			cin.getline(sPhone, 12);

			while (i < rows && !found)
			{
				if (strcmp(sPhone, rec[i].phone_num) == 0)
					found = true;
				else
					i++;
			}
		}
		else if (option == 3)
		{
			cout << "Enter the customer email to search : ";
			rewind(stdin);
			cin.getline(sEmail, 31);

			while (i < rows && !found)
			{
				if (strcmp(sEmail, rec[i].e_mail) == 0)
					found = true;
				else
					i++;
			}
		}
		else
			cout << "Invalid number.\n" << endl;

	} while (option > 3 || option <= 0);

	if (found == true)
		return i;
	else
		return -1;
}


void show(CUSTOMER rec[], PACKAGE det[], int rows)
{
	int i = search(rec, det, rows);
	if (i != -1)
	{
		cout << "Customer's name is " << rec[i].name << endl;
		cout << "Customer's phone number is " << rec[i].phone_num << endl;
		cout << "Customer's email is " << rec[i].e_mail << endl;
		cout << "Package name is " << det[i].name << endl;
		cout << "Courier company is " << det[i].company << endl;
		cout << "Sender is " << det[i].user << endl;
		cout << "Arrival date is " << det[i].arr_date << endl;
		cout << "Collection date is " << det[i].col_date << endl << endl;
	}
	else
		cout << "Record not found.\n" << endl;

	return;
}

void update(CUSTOMER rec[], PACKAGE det[], int rows)
{
	int i = search(rec, det, rows);
	if (i != -1)
	{
		int choice;
		do
		{
			cout << "Press 1 to update customer's contact information." << endl;
			cout << "Press 2 to update collection date." << endl;
			cout << "Press 3 return to main list." << endl;
			cin >> choice;

			if (choice == 1)
			{
				char uName[21], uPhone[12], uEmail[31];
				cout << "Current name is " << rec[i].name << endl << "Enter new name: ";
				rewind(stdin);
				cin.getline(uName, 21);
				strcpy_s(rec[i].name, uName);

				cout << "Current phone number is " << rec[i].phone_num << endl << "Enter new phone number: ";
				cin.getline(uPhone, 12);
				strcpy_s(rec[i].phone_num, uPhone);

				cout << "Current name is " << rec[i].e_mail << endl << "Enter new e_mail: ";
				cin.getline(uEmail, 31);
				strcpy_s(rec[i].e_mail, uEmail);
				cout << "Update successful.\n" << endl;
			}
			else if (choice == 2)
			{
				char uColdate[11];
				cout << "Enter collection date: ";
				rewind(stdin);
				cin.getline(uColdate, 11);
				strcpy_s(det[i].col_date, uColdate);
				cout << "Update successful.\n" << endl;
			}
			else if (choice == 3)
			{
				cout << endl;
				return;				 	    //Escape from loop
			}
			else
				cout << "Invalid number.\n" << endl;
		} while (choice);  		  			//Infinite loop
	}

	else
		cout << "Record not found.\n" << endl;

	return;
}


