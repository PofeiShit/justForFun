#pragma once


#include <curl/curl.h>
#include <string.h>
#include <time.h>
#define _CF_BUF_SIZE 256


//ʵ���ϴ����ܵ�class
class CCurlFtp
{
public:
	CCurlFtp(void){};
	~CCurlFtp(void){};
	/*
	** �ⲿ�ӿ�
	** ����FTP��������ַ
	** ��ڲ�����ip:URL��ַ
	** example: ip=L"ftp://192.168.0.100;  usrpwd = L"zack:sb123456";
	** �ϴ��ļ���Ϊfilename���ļ���ftp������
	** ��ڲ�����Դ�ļ����������Ǿ���·�������ϴ����ļ���
	** example: filename=L"���ϴ������ļ�.rar"; uploadFilename=NULL;�������ļ���
	*/

	bool uploadFile(const char *filename,const char *uploadFilename, const char *ip);

};
