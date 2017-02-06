// FileDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "FileDll.h"
#include <iostream>
namespace wLog
{
	FileWrite*	FileWrite::fileWrite = new FileWrite();

	void FileWrite::mywrite(const char* str, const char* filename)
	{
		FILE* file = fopen(filename, "a+");;
		if(NULL == file)
			return;
		int len = strlen(str);
		fwrite(str, 1, len, file);
		fclose(file);
	}
	FileWrite* FileWrite::getInstance()
	{
		return fileWrite;
	}
	FileWrite::FileWrite()
	{
		fileWrite = this;
	}
}

