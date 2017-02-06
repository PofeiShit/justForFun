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
	/* 随机播放 */
	static void play(const char* dirPath);
	/* 搜索MP3文件 */
private:	
	static void DirectorySearch(const char* dirPath);

	static bool isMp3(const char *file);
};