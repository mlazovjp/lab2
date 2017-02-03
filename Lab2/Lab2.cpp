// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Windows.h"

// First step towards creating the .bss section - Start
/*#pragma section("bss",read,write)  
__declspec(allocate("bss"))
char bss[4];
// First step towards creating the .bss section - End
*/

#pragma bss_seg("MyBSS")
char bss[4];

int main(int argc, char *argv[]) {

	bss[0] = 'a';	// second step required for creating .bss section
	bss[1] = 'b';	// second step required for creating .bss section
	bss[2] = 'c';	// second step required for creating .bss section
	bss[3] = 'd';	// second step required for creating .bss section

	int intArray[30];


	return 0;
}