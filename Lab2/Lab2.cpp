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


// reset to default value.  Useful after it has been modified
void setDefaultValueForvariableInBSS() {
	strcpy_s(variableInBSS, 16, "0123456789abcde");		//16 cells
}


// reset to default value.  Useful after it has been modified
void setDefaultValueForptrToHeap(char *ptrToHeap) {

	for (int i = 0; i < 15; i++) {
		ptrToHeap[i] = ('A' + i);
	}
	ptrToHeap[15] = '\0';
}


// reset to default value.  Useful after it has been modified
void setDefaultValueForvariableInDataSection() {
	strcpy_s(variableInDataSection, 16, "!@#$%^&*(_+<>?=");		//16 cells
}


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



//******************************************************************
// 2.) Copy 13 bytes from the heap to the DATA section - Start
//******************************************************************
void copy13BytesFromHeapToDataSection(char *ptrToHeap) {
	// heap: ptrToHeap
	// data: variableInDataSection
	printf("\n2.) Copy 13 bytes from the heap to the DATA section\n\n");
	printf("\tBefore 'memcpy(variableInDataSection, ptrToHeap, 13);'\n");
	printf("\t\t\tptrToHeap\t\t=\t %s\n", ptrToHeap);
	printf("\t\t\tvariableInDataSection\t=\t %s\n\n", variableInDataSection);

	memcpy(variableInDataSection, ptrToHeap, 13);

	printf("\tAfter 'memcpy(variableInDataSection, ptrToHeap, 13);'\n");
	printf("\t\t\tptrToHeap\t\t=\t %s\n", ptrToHeap);
	printf("\t\t\tvariableInDataSection\t=\t %s\n\n", variableInDataSection);
}
//******************************************************************
// 2.) Copy 13 bytes from the heap to the DATA section - End
//******************************************************************





//******************************************************************
// 3.) Copy 14 bytes from the stack to the heap - Start
//******************************************************************
void copy14BytesFromStackToHeap(char *ptrToHeap) {

	//***************************************
	// Create stuff on stack - Start
	//***************************************
	char variableOnStack[] = "Put me on stack";		// local function variable, is placed on stack
	//***************************************
	// Create stuff on stack - End
	//***************************************

	// BSS: variableInBSS
	// stack: variableOnStack
	printf("\n\n3.) Copy 14 bytes from the stack to the heap\n\n");
	printf("\tBefore 'memcpy(ptrToHeap, variableOnStack, 14);'\n");
	printf("\t\t\tvariableOnStack\t\t=\t %s\n", variableOnStack);
	printf("\t\t\tptrToHeap\t\t=\t %s\n\n", ptrToHeap);

	memcpy(ptrToHeap, variableOnStack, 14);

	printf("\tAfter 'memcpy(ptrToHeap, variableOnStack, 14);'\n");
	printf("\t\t\tvariableOnStack\t\t=\t %s\n", variableOnStack);
	printf("\t\t\tptrToHeap\t\t=\t %s\n\n", ptrToHeap);
}
//******************************************************************
// 3.) Copy 14 bytes from the stack to the heap - End
//******************************************************************


//******************************************************************
// 4.) Copy 15 bytes from the DATA section to the BSS - Start
//******************************************************************
void copy15BytesFromDataSectionToBSS() {

	printf("\n\n4.) Copy 15 bytes from the DATA section to the BSS\n\n");
	printf("\tBefore 'memcpy(variableInBSS, variableInDataSection, 15);'\n");
	printf("\t\t\tvariableInDataSection\t=\t %s\n", variableInDataSection);
	printf("\t\t\tvariableInBSS\t\t=\t %s\n\n", variableInBSS);

	memcpy(variableInBSS, variableInDataSection, 15);

	printf("\tAfter 'memcpy(variableInBSS, variableInDataSection, 15);'\n");
	printf("\t\t\tvariableInDataSection\t=\t %s\n", variableInDataSection);
	printf("\t\t\tvariableInBSS\t\t=\t %s\n\n", variableInBSS);
}
//******************************************************************
// 4.) Copy 15 bytes from the DATA section to the BSS - End
//******************************************************************


//******************************************************************
// 5.) Copy 4 bytes from the text section to the BSS - Start
//******************************************************************

// this function exists primarily as a means to point at executable code (text)
void dummyFunction() {
	return;
}

void copy4BytesFromTextSectionToBSS() {

	// we are going to try to capture the location in memory of a local function
	// and hope that will be in the .text section and the space there is executable code
	// we will try to copy 4 bytes from that address

	//const char *ptrToText = (const char *)0x0400;

	//void* ptrToText = dummyFunction;	// capture address at which this function exists
	const char * ptrToText = (const char *)dummyFunction;	// capture address at which this function exists

	printf("\n\n5.) Copy 4 bytes from the text section to the BSS\n\n");
	printf("\tBefore 'memcpy(variableInBSS, ptrToText, 4);'\n");
	printf("\t\t\tptrToText\t\t=\t %s\n", ptrToText);
	printf("\t\t\tvariableInBSS\t\t=\t %s\n\n", variableInBSS);

	memcpy(variableInBSS, ptrToText, 4);

	printf("\tAfter 'memcpy(variableInBSS, ptrToText, 4);'\n");
	printf("\t\t\tptrToText\t\t=\t %s\n", ptrToText);
	printf("\t\t\tvariableInBSS\t\t=\t %s\n\n", variableInBSS);
}
//******************************************************************
// 5.) Copy 4 bytes from the text section to the BSS - End
//******************************************************************



int main(int argc, char *argv[]) {

	//***************************************
	// Create stuff on Heap - Start
	//***************************************
	char *ptrToHeap;
	ptrToHeap = (char *) malloc(16);	// heap: allocated memory
	setDefaultValueForptrToHeap(ptrToHeap);
	//***************************************
	// Create stuff on Heap - End
	//***************************************


	//******************************************************************
	// 1.) Copy 12 bytes from the BSS section of the program to the stack - Start
	//******************************************************************
	setDefaultValueForvariableInBSS();
	copy12BytesFromBSSToStack();					//do it!
	//******************************************************************
	// 1.) Copy 12 bytes from the BSS section of the program to the stack - End
	//******************************************************************


	//******************************************************************
	// 2.) Copy 13 bytes from the heap to the DATA section - Start
	//******************************************************************
	setDefaultValueForptrToHeap(ptrToHeap);
	copy13BytesFromHeapToDataSection(ptrToHeap);
	//******************************************************************
	// 2.) Copy 13 bytes from the heap to the DATA section - End
	//******************************************************************


	//******************************************************************
	// 3.) Copy 14 bytes from the stack to the heap - Start
	//******************************************************************
	setDefaultValueForptrToHeap(ptrToHeap);
	copy14BytesFromStackToHeap(ptrToHeap);
	//******************************************************************
	// 3.) Copy 14 bytes from the stack to the heap - End
	//******************************************************************


	//******************************************************************
	// 4.) Copy 15 bytes from the DATA section to the BSS - Start
	//******************************************************************
	setDefaultValueForvariableInDataSection();
	setDefaultValueForvariableInBSS();
	copy15BytesFromDataSectionToBSS();
	//******************************************************************
	// 4.) Copy 15 bytes from the DATA section to the BSS - End
	//******************************************************************


	//******************************************************************
	// 5.) Copy 4 bytes from the text section to the BSS - Start
	//******************************************************************
	setDefaultValueForvariableInBSS();
	copy4BytesFromTextSectionToBSS();
	//******************************************************************
	// 5.) Copy 4 bytes from the text section to the BSS - End
	//******************************************************************


	free(ptrToHeap);		// free up memory from heap

	return 0;
}