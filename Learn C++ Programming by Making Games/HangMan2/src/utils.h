/*
 * utils.h
 *
 *  Created on: 22 May 2021
 *      Author: TESLA BLACK
 */

#ifndef UTILS_H_
#define UTILS_H_

const int IGNORE_CHARS = 256;

char GetCharacter(const char* prompt, const char* error, const char ValidInput[], int ValidInputLength);
char GetCharacter(const char* prompt, const char* error);


#endif /* UTILS_H_ */
