#pragma once
#ifdef FILEDLL_EXPORTS
#define FILEDLL_API __declspec(dllexport)
#else
#define FILEDLL_API __declspec(dllimport)
#endif

namespace wLog
{
	class FileWrite
	{
	public:
		static FILEDLL_API void mywrite(const char* str, const char* filename);
		static FILEDLL_API FileWrite* getInstance();
	private:
		static FileWrite* fileWrite;
		FileWrite();
		FileWrite(const FileWrite &){};
		FileWrite& operator = (const FileWrite &){};

	};
}

