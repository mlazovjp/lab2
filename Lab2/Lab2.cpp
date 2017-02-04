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

//***************************************
// Create stuff in data section - Start
//***************************************
char variableInDataSection[] = "!@#$%^&*(_+<>?=";		// Global variable with a predefined value
//***************************************
// Create stuff in data section - End
//***************************************


#pragma bss_seg("MyBSS")
char variableInBSS[16];
//char bss[4];

//******************************************************************
// 1.) Copy 12 bytes from the BSS section of the program to the stack - Start
//******************************************************************
void copy12BytesFromBSSToStack() {

	//***************************************
	// Create stuff on stack - Start
	//***************************************
	char variableOnStack[] = "Put me on stack";		// local function variable, is placed on stack
	//***************************************
	// Create stuff on stack - End
	//***************************************

	// BSS: variableInBSS
	// stack: variableOnStack
	printf("\n\n1.) Copy 12 bytes from the BSS section of the program to the stack\n\n");
	printf("\tBefore 'memcpy(variableOnStack, variableInBSS, 12);'\n");
	printf("\t\t\tvariableInBSS\t\t=\t %s\n", variableInBSS);
	printf("\t\t\tvariableOnStack\t\t=\t %s\n\n", variableOnStack);

	memcpy(variableOnStack, variableInBSS, 12);

	printf("\tAfter 'memcpy(variableOnStack, variableInBSS, 12);'\n");
	printf("\t\t\tvariableInBSS\t\t=\t %s\n", variableInBSS);
	printf("\t\t\tvariableOnStack\t\t=\t %s\n\n", variableOnStack);

}
//******************************************************************
// 1.) Copy 12 bytes from the BSS section of the program to the stack - End
//******************************************************************


int main(int argc, char *argv[]) {

	//bss[0] = 'a';	// second step required for creating .bss section
	//bss[1] = 'b';	// second step required for creating .bss section
	//bss[2] = 'c';	// second step required for creating .bss section
	//bss[3] = 'd';	// second step required for creating .bss section

	//bss = 'z';
	/*
	char charDataArray1[] = { "abcdefghijklmno" };
	charBSS01 = charDataArray1[0];

	printf("\ncharBSS01=%c\n", charBSS01);

	char charDataArray2[] = { "Here I am!!" };



	const char src[50] = "http://www.tutorialspoint.com";
	char dest[50] = "";

	printf("Before memcpy dest = %s\n", dest);
	memcpy(dest, src, strlen(src) + 1);
	printf("After memcpy dest = %s\n", dest);
	*/

	




	//***************************************
	// Create stuff on Heap - Start
	//***************************************
	char *ptrToHeap;
	ptrToHeap = (char *) malloc(16);	// heap: allocated memory

	for (int i = 0; i < 15; i++) {
		ptrToHeap[i] = ('A' + i);
	}
	ptrToHeap[15] = '\0';
	//***************************************
	// Create stuff on Heap - End
	//***************************************

	//******************************************************************
	// 1a.) Prep variableInBSS by setting value - Start
	//******************************************************************
	strcpy_s(variableInBSS, 16, "0123456789abcde");		//16 cells
	copy12BytesFromBSSToStack();					//do it!
	//******************************************************************
	// 1a.) Prep variableInBSS by setting value - End
	//******************************************************************


	//******************************************************************
	// 2.) Copy 13 bytes from the heap to the DATA section - Start
	//******************************************************************

	// heap: ptrToHeap
	// data: variableInDataSection
	printf("2.) Copy 13 bytes from the heap to the DATA section\n\n");
	printf("\tBefore 'memcpy(variableInDataSection, ptrToHeap, 13);'\n");
	printf("\t\t\tptrToHeap\t\t=\t %s\n", ptrToHeap);
	printf("\t\t\tvariableInDataSection\t=\t %s\n\n", variableInDataSection);

	memcpy(variableInDataSection, ptrToHeap, 13);

	printf("\tAfter 'memcpy(variableInDataSection, ptrToHeap, 13);'\n");
	printf("\t\t\tptrToHeap\t\t=\t %s\n", ptrToHeap);
	printf("\t\t\tvariableInDataSection\t=\t %s\n\n", variableInDataSection);




	//******************************************************************
	// 2.) Copy 13 bytes from the heap to the DATA section - End
	//******************************************************************



	




	free(ptrToHeap);		// free up memory from heap

	return 0;
}