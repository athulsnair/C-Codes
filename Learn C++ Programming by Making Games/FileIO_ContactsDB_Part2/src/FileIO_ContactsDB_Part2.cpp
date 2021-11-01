//============================================================================
// Name        : FileIO_ContactsDB.cpp
// Author      : Athul
// Version     :
// Copyright   : Your copyright notice
// Description : FileIO_ContactsDB in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

/*
Problem: Write a program that will keep a list of contacts.
The contact will have a name (first name and last name), and a phone number (no dashes).
The program will read in all the saved contacts at the start of program.
The user will be able to either look at all their contacts or add a new contact or quit the app.
Once the contact is added it should be saved. The names should be no more than 256 characters.

 Replace C strings with C++ strings.
 Use a vector instead of dynamic memory
 Use a text file instead of a binary file

 Write a function that will remove a contact from the vector. Make this option in the menu.

 Change the display option to have a user choose the order in which to display:
 sorted by the first name
 sorted by the last name

 */

const int MAX_NAME_CHARACTERS = 256;
const char * INPUT_ERROR_STRING = "Invalid Input!, Please try again\n";
const char * CONTACTS_FILE_NAME = "Contacts.txt";

struct Contact{

	string firstName;
	string lastName;
	int number;
};

struct ContactsDB{

	vector<Contact> contacts;
};

char GetOptionFromUser();
void ExecuteOption(ContactsDB & contactsDB, char option);
bool LoadContacts(ContactsDB & contactsDB);
void AddOption(ContactsDB & contactsDB);
void DisplayOption(ContactsDB & contactsDB);
void SaveContactes(ContactsDB & contactsDB);
void RemoveOption(ContactsDB & contactsDB);
bool LastName(const Contact& c1, const Contact& c2);
bool FirstName(const Contact& c1, const Contact& c2);

int main() {

	ContactsDB contactsDB;

	LoadContacts(contactsDB);

	char option;

	do
	{
		option = GetOptionFromUser();
		ExecuteOption(contactsDB, option);

	}while(option != 'q');

	SaveContactes(contactsDB);

	return 0;
}


bool LoadContacts(ContactsDB & contactsDB)
{

	ifstream inFile;

	inFile.open(CONTACTS_FILE_NAME);

	Contact newContact;

	if(inFile.is_open())
	{
		while(!inFile.eof())
		{
			inFile >> ws;

			if(inFile.eof())
				break;

			inFile >> newContact.firstName >> newContact.lastName >> newContact.number;
			contactsDB.contacts.push_back(newContact);
		}

		inFile.close();

		return true;
	}


	return false;
}

void SaveContactes(ContactsDB & contactsDB)
{
	ofstream outFile;
	outFile.open(CONTACTS_FILE_NAME);

	if(outFile.is_open())
	{
		for(int i = 0; i < contactsDB.contacts.size(); i++)
		{
			outFile << contactsDB.contacts[i].firstName << " " << contactsDB.contacts[i].lastName << " " << contactsDB.contacts[i].number;

			// making sure there is not new line at the end of file
			if( i < contactsDB.contacts.size() - 1)
			{
				outFile << endl;
			}
		}

		outFile.close();
	}
}

char GetOptionFromUser()
{
	const char options[] = {'a', 'r', 'd', 'q'};
	return GetCharacter("Please enter your Option\n\n(A)dd a new contact\n(A)Remove a contact\n(D)isplay a contact\n(Q)uit\nWhat id your choice: ",\
											INPUT_ERROR_STRING, options, 4, CC_LOWER_CASE);
}

void ExecuteOption(ContactsDB & contactsDB, char option)
{
	switch(option)
	{
	case 'a':
		AddOption(contactsDB);
		break;
	case 'd':
		DisplayOption(contactsDB);
		break;
	case 'r':
		RemoveOption(contactsDB);
		break;
	}
}

void AddOption(ContactsDB & contactsDB)
{

	Contact newContact;

	GetString("Please enter the first name: ", INPUT_ERROR_STRING, newContact.firstName);
	GetString("Please enter the last name: ", INPUT_ERROR_STRING, newContact.lastName);


	cout << "Please enter the phone number: ";
	cin >> newContact.number;

	contactsDB.contacts.push_back(newContact);

	SaveContactes(contactsDB);

	cout << "Saved!\n" << endl;
}

void RemoveOption(ContactsDB & contactsDB)
{
	if(contactsDB.contacts.size() <= 0)
	{
		cout << "No contacts on the list" << endl;
		return;
	}

	string firstName;
	string lastName;

	GetString("Enter first name: ", INPUT_ERROR_STRING, firstName);
	GetString("Enter last name: ", INPUT_ERROR_STRING, lastName);

	bool found = false;
	int foundIndex = -1;

	for(int i = 0; i < contactsDB.contacts.size() && !found ; i++)
	{
		if(contactsDB.contacts[i].firstName == firstName && contactsDB.contacts[i].lastName == lastName)
		{
			found = true;
			foundIndex = i;
		}
	}

	if(found)
	{
		swap(contactsDB.contacts[foundIndex], contactsDB.contacts[contactsDB.contacts.size() - 1]);
		contactsDB.contacts.pop_back();
		cout << "Removed " << firstName << " " << lastName << " from contact" << endl;
	}
	else
	{
		cout << "Not found " << firstName << " " << lastName << " in contact" << endl;
	}

	SaveContactes(contactsDB);
}

void DisplayOption(ContactsDB & contactsDB)
{

	if(contactsDB.contacts.size() <= 0)
	{
		cout << "No contacts on the list" << endl;
		return;
	}

	const char sortOptions[] = {'f', 'l'};
	char option;

	option = GetCharacter("Please choose a sort option\n\n(F)irst Name\n(L)ast Name\n\n What is your choice:", INPUT_ERROR_STRING, sortOptions, 2, CC_LOWER_CASE);

	if(option == sortOptions[0])
	{
		sort(contactsDB.contacts.begin(), contactsDB.contacts.end(),FirstName);
	}
	else {
		sort(contactsDB.contacts.begin(), contactsDB.contacts.end(),LastName);
	}


	for(int i = 0; i < contactsDB.contacts.size() ; i++)
	{
		cout << "Name : " << contactsDB.contacts[i].firstName << " " << contactsDB.contacts[i].lastName << endl;
		cout << "Number: " << contactsDB.contacts[i].number  << endl << endl;
	}
}

bool FirstName(const Contact& c1, const Contact& c2)
{
	return c1.firstName < c2.firstName;
}

bool LastName(const Contact& c1, const Contact& c2)
{
	return c1.lastName < c2.lastName;
}
