#include "takePhoto.h"
#include "curlFtp.h"
#include <iostream>

int main()
{
	ScreenShot *scrShot = new ScreenShot();
	CCurlFtp *curlFtp = new CCurlFtp();
	while(1){
		Sleep(5000);
		
		SYSTEMTIME time = {0};
		GetLocalTime(&time);
		char localTime[32];
		sprintf(localTime, "%d-%02d-%02d[%02d-%02d-%02d]",
			time.wYear,
			time.wMonth,
			time.wDay,
			time.wHour,
			time.wMinute,
			time.wSecond);
		//char filename[64];
		//sprintf(filename, "E:\\%sbmp.bmp", localTime);
		scrShot->CaptureScreenToFile(L"test.bmp",32);
		curlFtp->uploadFile("test.bmp", localTime, "ftp://192.168.0.105");

	}
	return 0;
}
