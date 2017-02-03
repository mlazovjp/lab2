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
	printf("\tSizeOfRawData (bytes)\t= %#010x (%d)\n", ish.SizeOfRawData, ish.SizeOfRawData);
	printf("\tPointerToRawData\t= %#010x\n", ish.PointerToRawData);

}


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



	return 0;
}