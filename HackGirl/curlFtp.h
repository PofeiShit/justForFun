#pragma once


#include <curl/curl.h>
#include <string.h>
#include <time.h>
#define _CF_BUF_SIZE 256


//实现上传功能的class
class CCurlFtp
{
public:
	CCurlFtp(void){};
	~CCurlFtp(void){};
	/*
	** 外部接口
	** 设置FTP服务器地址
	** 入口参数：ip:URL地址
	** example: ip=L"ftp://192.168.0.100;  usrpwd = L"zack:sb123456";
	** 上传文件名为filename的文件到ftp服务器
	** 入口参数：源文件名（可以是绝对路径），上传后文件名
	** example: filename=L"待上传测试文件.rar"; uploadFilename=NULL;不更改文件名
	*/

	bool uploadFile(const char *filename,const char *uploadFilename, const char *ip);

};
