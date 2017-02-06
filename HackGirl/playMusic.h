#pragma once

#include <windows.h>
#include <MMSystem.h>
#include <iostream>
#include "FileDll.h"
#include <io.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")

class PlayMusic
{
public:
	PlayMusic(){};
	~PlayMusic(){};
	/* ������� */
	static void play(const char* dirPath);
	/* ����MP3�ļ� */
private:	
	static void DirectorySearch(const char* dirPath);

	static bool isMp3(const char *file);
};