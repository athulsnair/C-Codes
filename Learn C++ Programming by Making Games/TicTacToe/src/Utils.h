/*
 * Utils.h
 *
 *  Created on: 10 Oct 2021
 *      Author: TESLA BLACK
 */

#ifndef UTILS_H_
#define UTILS_H_

const int IGNORE_CHARS = 256;

enum CharacterCaseType
{
	CC_UPPER_CASE = 0,
	CC_LOWER_CASE,
	CC_EITHER
};

char GetCharacter(const char* prompt, const char* error);

char GetCharacter(const char* prompt, const char* error, const char validIputs[], int validInputLength, CharacterCaseType charCase);
int GetInteger(const char* prompt, const char* error, const int validIputs[], int validInputLength);
void ClearScreen();
void WaitForKeyPress();

#endif /* UTILS_H_ */
