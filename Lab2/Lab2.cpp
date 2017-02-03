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

int main(int argc, char *argv[]) {

	//int intArray[30];

	i = 3;			// second step required for creating .bss section


	TCHAR szPath[MAX_PATH];

	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		printf("Cannot determine the path of this executable\n");
		return -1;
	}

	printf("\nszPath=%ls\n", szPath);

	//wcscpy_s(szPath, _countof(szPath), TEXT("C:\\Users\\mlazo\\Dropbox\\MCS\\CPS592 (Rev Eng)\\Assignments\\02\\source\\Lab2\\Release\\Lab2.exea"));
	//wcscpy_s(szPath, _countof(szPath), TEXT("C:\\Users\\mlazo\\Dropbox\\MCS\\CPS592 (Rev Eng)\\Assignments\\02\\source\\Lab2\\Release\\Lab2.exe"));
	//printf("szPath after=%ls\n", szPath);

	TCHAR *mode = TEXT("r");			// open this file in read-only mode.  r+ produces "Permission denied" error
	char ch;
	FILE *fp;
	_wfopen_s(&fp, szPath, mode);

	if (fp == NULL)
	{
		perror("Error While Opening The File Or File Does Not Exist\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(fp)) != EOF)
		printf("%c", ch);

	fclose(fp);

	return 0;
}