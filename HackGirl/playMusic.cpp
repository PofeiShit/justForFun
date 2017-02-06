#include "playMusic.h"
using namespace wLog;
static const char* FILENAME = "mp3.txt";
static const int MAX_BUFFER = 1024;
void PlayMusic::play(const char* dirPath)
{
	
	if((_access(FILENAME, 0)) != -1){
		srand(time(NULL));
		char buffer[MAX_BUFFER];
		char temp[MAX_BUFFER];
		FILE *f = fopen(FILENAME, "r");
		if(f == NULL)
			return;
		while(!feof(f)){
			int v1 = rand() % 100;
			int v2 = rand() % 100;
			if(fgets(buffer, MAX_BUFFER, f) != NULL){
				if(v1 > v2)
					break;
			}
		}
		fclose(f);
		sprintf(temp, "play %s", buffer);
		printf("now is: %s", temp);
		int len = strlen(temp);
		temp[len - 1] = '\0';
		mciSendString(temp, NULL, 0, 0);
		Sleep(360000);
	} else
		DirectorySearch(dirPath);
}
bool PlayMusic::isMp3(const char* file)
{
	const char *pMp3 = strrchr(file, '.');
	char type[8];
	strncpy_s(type, pMp3, 4);
	if(strncmp(type, ".mp3", 4) == 0)
		return true;
	return false;
}

void PlayMusic::DirectorySearch(const char* dirPath)
{
	WIN32_FIND_DATAA lpFindFileData;
	char dirPathTemp[MAX_PATH];
	char dirCodeTemp[MAX_PATH];

	strcpy_s(dirPathTemp, strlen(dirPath) + 1, dirPath);
	strcpy_s(dirCodeTemp, strlen(dirPath) + 1, dirPath);
	//�����ַ���ָ���ַ����д����濪ʼ�����һ�γ��ֵ�λ��
	const char *pChar = strrchr(dirPath, '\\');
	//���\\��ĩβ����
	if(pChar != NULL && strlen(pChar) == 1)
		strcat_s(dirCodeTemp, "*");
	else {
		strcat_s(dirCodeTemp, "\\*");
		strcat_s(dirPathTemp, "\\");
	}
	HANDLE handle = FindFirstFileA(dirCodeTemp, &lpFindFileData);
	if(handle == INVALID_HANDLE_VALUE){
		std::cout << dirPathTemp << "����ʧ��!" << std::endl;
		return ;
	}
	//�����������ļ������ӡ���ֺʹ�С
	if((lpFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0){
		if(isMp3(dirPathTemp)){
			strcat_s(dirPathTemp, "\n");
			FileWrite::getInstance()->mywrite(dirPathTemp, FILENAME);
		}
			//std::cout << "�ļ���:" << dirPathTemp << " ��С:" << lpFindFileData.nFileSizeHigh *(MAXDWORD + 1) + lpFindFileData.nFileSizeLow << std::endl;
	}//else
		//std::cout << "�ļ�����:" << dirPathTemp << std::endl;
	//������·���µ��ļ��к��ļ�
	while(FindNextFileA(handle, &lpFindFileData)){
		//����ǵ�ǰ��·����������Ҫ���
		if(!strcmp(lpFindFileData.cFileName, ".") || !strcmp(lpFindFileData.cFileName, ".."))
			continue;
		//��ǰ�ļ��л��ļ���ȫ·������ǰ��·�� + �ļ��л��ļ������ƣ�
		char dirFileTemp[MAX_PATH];
		strcpy_s(dirFileTemp, strlen(dirPathTemp) + 1, dirPathTemp);
		strcat_s(dirFileTemp, lpFindFileData.cFileName);
		if((lpFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0){
			if(isMp3(dirFileTemp)){
				strcat_s(dirFileTemp, "\n");
				FileWrite::getInstance()->mywrite(dirFileTemp, FILENAME);
			}
				//std::cout << "�ļ���:" << dirFileTemp << " ��С:" << lpFindFileData.nFileSizeHigh * (MAXDWORD + 1) + lpFindFileData.nFileSizeLow << std::endl;
		} else {
		//	std::cout << "�ļ�����:" << dirFileTemp << std::endl;
			strcat_s(dirFileTemp, "\\");
			//�ݹ������ļ���
			DirectorySearch(dirFileTemp);
		}
	}
	FindClose(handle);
}