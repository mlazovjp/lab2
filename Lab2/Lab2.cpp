// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Windows.h"

// First step towards creating the .bss section - Start
#pragma section("bss",read,write)  
__declspec(allocate("bss"))
int i = 0;
// First step towards creating the .bss section - End


// "borrowed" from http://www.rohitab.com/discuss/topic/37906-how-to-get-address-of-a-pe-data-section/
IMAGE_SECTION_HEADER *find_section(IMAGE_NT_HEADERS *nthdrs, const char *sec_name)
{
	IMAGE_SECTION_HEADER *sec_hdr = IMAGE_FIRST_SECTION(nthdrs);
	WORD nsections = nthdrs->FileHeader.NumberOfSections;

	while (nsections--) {
		if (strcmp((char *)sec_hdr->Name, sec_name) == 0)
			return sec_hdr;
		sec_hdr++;
	}

	return NULL;
}


void outputDetailsOfIMAGE_SECTION_HEADER(IMAGE_SECTION_HEADER &ish) {

	printf("\n%s\n", ish.Name);
	printf("\tSizeOfRawData in bytes\t= %#010x (%d)\n", ish.SizeOfRawData, ish.SizeOfRawData);
	printf("\tPointerToRawData\t= %#010x\n", ish.PointerToRawData);

}

//http://stackoverflow.com/questions/15312340/printing-memory-as-1-byte-hex-in-c
/*
void printMemoryAtAddress(void)
{
	int dumpSize = 15;

	int input;
	printf("Enter the address (without the 0x):");
	scanf("%x", &input);
	printf("You entered: %x \n", input);
	printf("Address \tByte value \n");

	int i;
	for (i = 0; i<dumpSize; i++)
	{
		//int* address;
		unsigned char *address;
		address = (int*)(input + i);
		address = (int*)(input + i);
		printf("%p \t", address);
		printf("%.2x \n", *address);
	}
}
*/

int main(int argc, char *argv[]) {

	//int intArray[30];

	i = 3;					// second step required for creating .bss section

	// "borrowed" from http://stackoverflow.com/questions/6126980/get-pointer-to-image-dos-header-with-getmodulehandle
	PIMAGE_DOS_HEADER pidh = (PIMAGE_DOS_HEADER)GetModuleHandle(NULL);

	// "borrowed" from http://stackoverflow.com/questions/8782771/loading-pe-headers
	PIMAGE_NT_HEADERS pinh = (PIMAGE_NT_HEADERS)((BYTE*)pidh + pidh->e_lfanew);
	PIMAGE_FILE_HEADER pifh = (PIMAGE_FILE_HEADER)&pinh->FileHeader;
	PIMAGE_OPTIONAL_HEADER pioh = (PIMAGE_OPTIONAL_HEADER)&pinh->OptionalHeader;
	
	// create image section headers for the sections we care about
	IMAGE_SECTION_HEADER pish_text = *find_section(pinh, ".text");
	IMAGE_SECTION_HEADER pish_rdata = *find_section(pinh, ".rdata");
	IMAGE_SECTION_HEADER pish_data = *find_section(pinh, ".data");
	IMAGE_SECTION_HEADER pish_bss = *find_section(pinh, "bss");

	// display console output showing details of the sections
	outputDetailsOfIMAGE_SECTION_HEADER(pish_text);
	outputDetailsOfIMAGE_SECTION_HEADER(pish_rdata);
	outputDetailsOfIMAGE_SECTION_HEADER(pish_data);
	outputDetailsOfIMAGE_SECTION_HEADER(pish_bss);

	// borrowed from https://bytes.com/topic/c/answers/821797-jump-address-syntax
	//unsigned long address = 0x400000;
	//unsigned long address = pish_text.PointerToRawData;
	//typedef void VFunc(void);
	//((VFunc *)address)();

	/*
	unsigned char *p = (unsigned char *)&address;
	int i;

	printf("\nContents of %#010x \t=", address);
	
	for (i = 0; i < sizeof(address); ++i)
	{
		printf(" %02x", p[i]);
	}
	
	printf("\n");
	*/

	/*
	int n = 8, i = 0;
	unsigned char* byte_array = (unsigned char*)&pish_text.PointerToRawData;
	
	printf("\nContents of %#010x \t\t= ", address);
	while (i < n)
	{
		printf("%02X ", (unsigned)byte_array[i]);
		i++;
	}
	printf("\n");
	*/
	/*
	DWORD  dw = 0x00000400;
	unsigned char* pc = (unsigned char*)&dw;
	for (int i = 3; i >= 0; i--) {
		printf("%02X ", (unsigned)pc[i]);
	}
	*/


	// pointer to int (4bytes) that points to memory address 0x611268
	int* address = (int *)0x000400;

	printf("Memory address is: 0x%x\n", address);

	// Note that this address should exist on your process' memory or 
	// the line below will cause a Segmentation Fault
	*address = 0xdead; //assign a value to that address

	printf("Content of that address is: 0x%x\n", *address);

	return 0;
}