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


bool openMyself(FILE *fp) {

	TCHAR szPath[MAX_PATH];

	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		printf("Cannot determine the path of this executable\n");
		return false;
	}

	printf("\nszPath=%ls\n", szPath);
	
	TCHAR *mode = TEXT("r");			// open this file in read-only mode.  r+ produces "Permission denied" error
	char ch;
	_wfopen_s(&fp, szPath, mode);
	
	if (fp == NULL)
	{
		perror("Error While Opening The File Or File Does Not Exist\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(fp)) != EOF)
		printf("%c", ch);

	return true;
}

bool closeMyself(FILE *fp) {
	fclose(fp);
	return true;
}


int main(int argc, char *argv[]) {

	//int intArray[30];

	i = 3;					// second step required for creating .bss section

	FILE fp;				
	openMyself(&fp);		// open this binary in read-only mode
	


	closeMyself(&fp);

	return 0;
}