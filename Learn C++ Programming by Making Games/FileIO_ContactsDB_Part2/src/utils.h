/*
 * utils.h
 *
 *  Created on: 22 May 2021
 *      Author: TESLA BLACK
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

const int IGNORE_CHARS = 256;

enum CharacterCaseType
{
	CC_UPPER_CASE= 0,
	CC_LOWER_CASE,
	CC_EITHER
};

int GetString(const char* prompt, const char* error, std::string & newString);
char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);
char GetCharacter(const char* prompt, const char* error);
int GetInteger(const char* prompt, const char* error, const int validInput[], int validInputLength);
void ClearScreen();
void WaitForKeyPress();


#endif /* UTILS_H_ */
