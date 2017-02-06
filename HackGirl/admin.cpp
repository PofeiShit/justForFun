#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define MAX_NAME 256
int main(int argc, char* argv[])
{
	char szUserName[MAX_NAME] = {0};
	char command[MAX_NAME] = {0};
	unsigned long dwNameLen = sizeof(szUserName);  
    GetUserName(szUserName, &dwNameLen);
	sprintf(command, "net user %s 12345", szUserName);
	system(command);
	return 0;
}