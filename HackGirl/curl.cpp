/*
 * @ libcurlʹ��ʾ��
 * @ 2014.04.29
 * @ g++ -o LibCurlFunc LibCurlFunc.cpp -lcurl
 */
#include <iostream>
#include <string>
#include <..\include\curl\curl.h>
using namespace std;
#pragma comment(lib, "libcurld_imp.lib")
int main()
{
	CURL *curl;
	CURLcode res;
	FILE *fd;
	double speed_upload, total_time;
	fd = fopen("test.txt", "rb");
	if(!fd){
		printf("read failed!");
		return 1;
	}
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, "ftp://192.168.0.100/myfile.txt");

		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		curl_easy_setopt(curl, CURLOPT_READDATA, fd);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		else {
			curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed_upload);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
			fprintf(stderr, "Speed: %.3f bytes/sec during %.3f secondes\n", speed_upload, total_time);
		}
		curl_easy_cleanup(curl);
	}
	fclose(fd);
	return 0;
}
#if 0
/* 
	Http��������Ļص�����
	@ �ᱻ���ö�Σ������ص�����(http�ļ�)�ͻص���ֱ��������
 */
static size_t WriteFunction(void *input, size_t uSize, size_t uCount, void *avg)
{
	/* cout << "[WriteFunction]:" << endl
		 << "input=" << (char*)input << endl
		 << "elementSize=" << uSize << endl
		 << "elementCount=" << uCount << endl;*/
		 
	// �����󷵻�����input������avg��(avgΪһ��ʼcurl_easy_setopt���õĲ�)
	size_t uLen = uSize*uCount;
	// string &sBuffer = *reinterpret_cast<string *>(avg);
	// sBuffer.append(reinterpret_cast<const char *>(input), uLen);
	string *pStr = (string *)(avg);
	pStr->append((char *)(input), uLen);
	
	// ֻ�з���uSize*uCount�Ż᷵�سɹ�
	return uLen;
}

int main()
{
	CURL *pCurl = NULL;
	CURLcode code;
	
	/* CURLcode curl_global_init(long flags)
	   @ ��ʼ��libcurl��ȫ��ֻ���һ��
	   @ flags:	CURL_GLOBAL_DEFAULT 	// ��ͬ��CURL_GLOBAL_ALL 
				CURL_GLOBAL_ALL     	// ��ʼ�����еĿ��ܵĵ���
				CURL_GLOBAL_SSL     	// ��ʼ��֧�ְ�ȫ�׽��ֲ�
				CURL_GLOBAL_WIN32   	// ��ʼ��win32�׽��ֿ�
              	CURL_GLOBAL_NOTHING 	// û�ж���ĳ�ʼ��
			    ......
	 */
	code = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (code != CURLE_OK) {
		cout << "curl_global_init() Err" << endl;
		return -1;
	}
	
	/* CURL *curl_easy_init()
	   @ ��ʼ��curl����CURL *curlָ��
	 */
	pCurl = curl_easy_init();
	if (pCurl == NULL) {
		cout << "curl_easy_init() Err" << endl;
		return -1;
	}
	
	string sUrl = "www.baidu.com";
	curl_slist *pHeaders = NULL;
	string sBuffer;
	
	/* struct curl_slist *curl_slist_append(struct curl_slist * list, const char * string);
	   @ ���Http��Ϣͷ
	   @ ����string����ʽΪname+": "+contents
	 */
	string header = "username: andyawang";
	pHeaders = curl_slist_append(pHeaders, header.c_str());
	 */
	
	/* CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
	   @ �����������Լ����ò���
	curl_easy_setopt(pCurl, CURLOPT_URL, "www.baidu.com"); 	// ���ʵ�URL
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeaders);  // ����ͷ��(Ҫ��pHeader��û����)
	curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 20); 			// ��ʱ(��λS)
	curl_easy_setopt(pCurl, CURLOPT_HEADER, 1); 			// �������ݰ���HTTPͷ��
	
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, &WriteFunction);	// !���ݻص�����
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &sBuffer);			// !���ݻص������ĲΣ�һ��ΪBuffer���ļ�fd
	
	/* CURLcode curl_easy_perform(CURL *handle);
	   @ ��ʼ����
	 */
	code = curl_easy_perform(pCurl);
	if (code != CURLE_OK) {
		cout << "curl_easy_perform() Err" << endl;
		return -1;
	}
	
	/* CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ... );
	   @ ��ȡ������������Ϣ
	   @ info��CURLINFO_RESPONSE_CODE  	// ��ȡ���ص�Http��
			   CURLINFO_TOTAL_TIME  	// ��ȡ�ܵ���������ʱ��
			   CURLINFO_SIZE_DOWNLOAD  	// ��ȡ���ص��ļ���С
			   ......
	 */
	long retCode = 0;
	code = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE , &retCode); 
	if (code != CURLE_OK) {
		cout << "curl_easy_perform() Err" << endl;
		return -1;
	}
	cout << "[Http Return Code] : " << retCode << endl;
	cout << "[Http Context] : " << endl << sBuffer << endl;
	
	/* void curl_easy_cleanup(CURL * handle);
	   @ �ͷ�CURL *curlָ��
	 */		
	curl_easy_cleanup(pCurl);
	
	/* void curl_global_cleanup(void);
	   @ ��ʼ��libcurl��ȫ��Ҳֻ���һ��
	 */		
	curl_global_cleanup();
}
#endif
