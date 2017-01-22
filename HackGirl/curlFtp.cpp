#include "curlFtp.h"
#include <iostream>
#pragma comment(lib, "libcurld_imp.lib")


bool CCurlFtp::uploadFile(const char *filename, const char *uploadFilename, const char* ip)
{
	CURL *curl;
	CURLcode res;
	FILE *fd;
	fd = fopen(filename, "rb");
	double speed_upload, total_time;
	if(!fd){
		//std::cout << "open failed" << std::endl;
		return false;
	}
	curl = curl_easy_init();
	char url[64];
	sprintf(url, "%s/%s.bmp", ip, uploadFilename);
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

		curl_easy_setopt(curl, CURLOPT_READDATA, fd);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK){
			//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		else {
			curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed_upload);
			curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
			//fprintf(stderr, "Speed: %.3f bytes/sec during %.3f secondes\n", speed_upload, total_time);
		}
		curl_easy_cleanup(curl);
	}
	fclose(fd);
	return 0;

}