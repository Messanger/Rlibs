#include "RLIBS.h"

#include <windows.h>

RLIBS_API bool Rlibs::FileExistsA(__rip const char *szPath)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileA(szPath, &fd);
	bool bRet = (hFind != INVALID_HANDLE_VALUE) ? true : false;
	FindClose(hFind);
	return bRet;
}

RLIBS_API bool Rlibs::FileExistsW(__rip const wchar_t *wszPath)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFileW(wszPath, &fd);
	bool bRet = (hFind != INVALID_HANDLE_VALUE) ? true : false;
	FindClose(hFind);
	return bRet;
}

RLIBS_API bool Rlibs::FolderExistsA(__rip const char *szPath)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileA(szPath, &fd);
	BOOL bFilter = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	bool bRetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? true : false;
	FindClose(hFind);
	return bRetValue;
}

RLIBS_API bool Rlibs::FolderExistsW(__rip const wchar_t *wszPath)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFileW(wszPath, &fd);
	BOOL bFilter = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	bool bRetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? true : false;
	FindClose(hFind);
	return bRetValue;
}
