// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Windows.h"
//#include "WinNT.h"

// First step towards creating the .bss section - Start
#pragma section("bss",read,write)  
__declspec(allocate("bss"))
int i = 0;
// First step towards creating the .bss section - End

int main(int argc, char *argv[]) {

	int intArray[30];

	i = 3;			// second step required for creating .bss section

	/*const char *path;
	char *drive;
	char *dir;
	char *fname;
	char *ext;
	_splitpath(path, drive, dir, fname, ext);
	*/

	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	errno_t err;

	printf("argv[0]=%s", argv[0]);

	return 0;
}