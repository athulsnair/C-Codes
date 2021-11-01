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
#include "utils.h"

using namespace std;

/*
Problem: Write a program that will keep a list of contacts.
The contact will have a name (first name and last name), and a phone number (no dashes).
The program will read in all the saved contacts at the start of program.
The user will be able to either look at all their contacts or add a new contact or quit the app.
Once the contact is added it should be saved. The names should be no more than 256 characters.
 */

const int MAX_NAME_CHARACTERS = 256;
const char * INPUT_ERROR_STRING = "Invalid Input!, Please try again\n";
const char * CONTACTS_FILE_NAME = "Contacts.bin";

struct Contact{

	char firstName[MAX_NAME_CHARACTERS];
	char lastName[MAX_NAME_CHARACTERS];
	int number;
};

struct ContactsDB{

	Contact * optrContacts;
	int numberOfContacts;
	int capcity;
};

char GetOptionFromUser();
void ExecuteOption(ContactsDB & contactsDB, char option);
bool LoadContacts(ContactsDB & contactsDB);
void AddOption(ContactsDB & contactsDB);
void DisplayOption(const ContactsDB & contactsDB);
void ResizeContacts(ContactsDB & contactsDB, int newCapacity);
void SaveContactes(ContactsDB & contactsDB);
void CreateContactsFile();

int main() {

	ContactsDB contactsDB;
	contactsDB.optrContacts = nullptr;
	contactsDB.numberOfContacts = 0;
	contactsDB.capcity = 0;

	CreateContactsFile();

	if(!LoadContacts(contactsDB))
	{
		cout << "Error reading file! " << CONTACTS_FILE_NAME << endl;
		return 0;
	}

	char option;

	do
	{
		option = GetOptionFromUser();
		ExecuteOption(contactsDB, option);

	}while(option != 'q');

	SaveContactes(contactsDB);

	if(contactsDB.optrContacts != nullptr)
	{
		delete [] contactsDB.optrContacts;
		contactsDB.optrContacts = nullptr;
	}

	return 0;
}

void CreateContactsFile()
{
	ifstream inFile;

	inFile.open(CONTACTS_FILE_NAME, fstream::binary);

	if(!inFile.is_open())
	{
		ofstream outFile;
		outFile.open(CONTACTS_FILE_NAME, fstream::binary);
		outFile << flush;
		outFile.close();
	}
	else
	{
		inFile.close();
	}
}

bool LoadContacts(ContactsDB & contactsDB)
{

	ifstream inFile;

	inFile.open(CONTACTS_FILE_NAME, fstream::binary);

	if(inFile.is_open())
	{
		inFile.seekg(0, inFile.end);
		int lengthOfFileInBytes = inFile.tellg();
		inFile.seekg(0, inFile.beg);

		int numberOfContacts = lengthOfFileInBytes / sizeof(Contact);
		int capacity = numberOfContacts * 2 + 10;

		contactsDB.optrContacts = new Contact[capacity];
		contactsDB.numberOfContacts = numberOfContacts;
		contactsDB.capcity = capacity;

		inFile.read((char *)contactsDB.optrContacts, lengthOfFileInBytes);
		inFile.close();

		return true;
	}

	return false;
}

void SaveContactes(ContactsDB & contactsDB)
{
	ofstream outFile;
	outFile.open(CONTACTS_FILE_NAME, fstream::binary);

	if(outFile.is_open())
	{
		outFile.write((char*)contactsDB.optrContacts, contactsDB.numberOfContacts * sizeof(Contact));
		outFile.close();
	}
}

char GetOptionFromUser()
{
	const char options[] = {'a', 'd', 'q'};
	return GetCharacter("Please enter your Option\n\n(A)dd a new contact\n(D)isplay a contact\n(Q)uit\nWhat id your choice: ",\
											INPUT_ERROR_STRING, options, 3, CC_LOWER_CASE);
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
	}
}

void AddOption(ContactsDB & contactsDB)
{
	if(contactsDB.numberOfContacts == contactsDB.capcity)
	{
		ResizeContacts(contactsDB, contactsDB.capcity * 2 + 10);
	}

	GetString("Please enter the first name: ", INPUT_ERROR_STRING, contactsDB.optrContacts[contactsDB.numberOfContacts].firstName, MAX_NAME_CHARACTERS);
	GetString("Please enter the last name: ", INPUT_ERROR_STRING, contactsDB.optrContacts[contactsDB.numberOfContacts].lastName, MAX_NAME_CHARACTERS);

	cout << "Please enter the phone number: ";
	cin >> contactsDB.optrContacts[contactsDB.numberOfContacts].number;

	contactsDB.numberOfContacts++;
	SaveContactes(contactsDB);

	cout << "Saved!\n" << endl;
}

void DisplayOption(const ContactsDB & contactsDB)
{
	for(int i = 0; i < contactsDB.numberOfContacts ; i++)
	{
		cout << "Name : " << contactsDB.optrContacts[i].firstName << " " << contactsDB.optrContacts[i].lastName << endl;
		cout << "Number: " << contactsDB.optrContacts[i].number  << endl << endl;
	}
}


void ResizeContacts(ContactsDB & contactsDB, int newCapacity)
{
	// make new array of size newCapacity
	Contact * newContactsPtr = new Contact[newCapacity];
	// copy all existing contacts into the new array
	 for(int i = 0; i < contactsDB.numberOfContacts; i++)
	 {
		 strcpy(newContactsPtr[i].firstName, contactsDB.optrContacts[i].firstName);
		 strcpy(newContactsPtr[i].lastName, contactsDB.optrContacts[i].lastName);
		 newContactsPtr[i].number = contactsDB.optrContacts[i].number;
	 }

	// delete the old array
	 if(contactsDB.optrContacts != nullptr)
	 {
		 delete []contactsDB.optrContacts;
	 }
	// set the contactDB.optrContacts = new array
	 contactsDB.optrContacts = newContactsPtr;
	 contactsDB.capcity = newCapacity;
}

