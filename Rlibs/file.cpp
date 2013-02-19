#include "RLIBS.h"

#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#define FILE_FMT_BUFFER_LENGTH		16384

RLIBS_API BOOL Rlibs::FileExistsA(__rip LPCSTR szPath)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileA(szPath, &fd);
	BOOL bRet = (hFind != INVALID_HANDLE_VALUE) ? TRUE : FALSE;
	FindClose(hFind);
	return bRet;
}

RLIBS_API BOOL Rlibs::FileExistsW(__rip LPCWSTR wszPath)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFileW(wszPath, &fd);
	BOOL bRet = (hFind != INVALID_HANDLE_VALUE) ? TRUE : FALSE;
	FindClose(hFind);
	return bRet;
}

RLIBS_API BOOL Rlibs::FolderExistsA(__rip LPCSTR szPath)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileA(szPath, &fd);
	BOOL bFilter = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	BOOL bRetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
	FindClose(hFind);
	return bRetValue;
}

RLIBS_API BOOL Rlibs::FolderExistsW(__rip LPCWSTR wszPath)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFileW(wszPath, &fd);
	BOOL bFilter = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	BOOL bRetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
	FindClose(hFind);
	return bRetValue;
}

RLIBS_API HANDLE Rlibs::FileOpenA(__rip LPCSTR szFilename, __rip DWORD dwDesiredAccess)
{
	DWORD dwCreationDisposition = OPEN_ALWAYS;
	if ( dwDesiredAccess == GENERIC_READ ) dwCreationDisposition = OPEN_EXISTING;
	return ::CreateFileA(szFilename,
		dwDesiredAccess,
		0,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
}

RLIBS_API HANDLE Rlibs::FileOpenW(__rip LPCWSTR szFilename, __rip DWORD dwDesiredAccess)
{
	DWORD dwCreationDisposition = OPEN_ALWAYS;
	if ( dwDesiredAccess == GENERIC_READ ) dwCreationDisposition = OPEN_EXISTING;
	return ::CreateFileW(szFilename,
		dwDesiredAccess,
		0,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
}

RLIBS_API BOOL Rlibs::FileClose(__rip HANDLE hFile)
{
	return ::CloseHandle(hFile);
}

RLIBS_API UINT64 Rlibs::FileSize(__rip HANDLE hFile)
{
	DWORD dwFileSizeHigh = 0;
	DWORD dwFileSizeLow = ::GetFileSize(hFile, &dwFileSizeHigh);
	if ( dwFileSizeLow == 0xffffffff ) {
		return UINT64(-1);	// 0xffffffffffffffff
	}
	UINT64 qwFileSize = ( ((UINT64)dwFileSizeHigh) << 32 ) + (UINT64)dwFileSizeLow;
	return qwFileSize;
}

RLIBS_API UINT64 Rlibs::FileSizeA(__rip LPCSTR szFilename)
{
	HANDLE hFile = ::CreateFileA(szFilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return UINT64(-1);	// 0xffffffffffffffff
	}
	UINT64 qwRet = Rlibs::FileSize(hFile);
	::CloseHandle(hFile);
	return qwRet;
}

RLIBS_API UINT64 Rlibs::FileSizeW(__rip LPCWSTR wszFilename)
{
	HANDLE hFile = ::CreateFileW(wszFilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		return UINT64(-1);	// 0xffffffffffffffff
	}
	UINT64 qwRet = Rlibs::FileSize(hFile);
	::CloseHandle(hFile);
	return qwRet;
}

RLIBS_API UINT64 Rlibs::FileTell(__rip HANDLE hFile)
{
	ULONG high = 0;
	ULONG low = ::SetFilePointer(hFile, 0, (PLONG)&high, FILE_CURRENT);
	if ( low==INVALID_SET_FILE_POINTER && GetLastError()!=NO_ERROR ) {
		return (UINT64)-1;
	}
	return (((UINT64)high)<<32) + (UINT64)low;
}

RLIBS_API UINT64 Rlibs::FileSeek(HANDLE hFile, INT64 distance, DWORD MoveMethod)
{
	LARGE_INTEGER li;
	li.QuadPart = distance;
	li.LowPart  = ::SetFilePointer(hFile,
		li.LowPart,
		&li.HighPart,
		MoveMethod);
	if ( li.LowPart==INVALID_SET_FILE_POINTER && GetLastError()!=NO_ERROR ) {
		li.QuadPart = -1;
	}
	return li.QuadPart;
}

RLIBS_API DWORD Rlibs::FileRead(__rop PBYTE pBuffer, __rip DWORD dwBytesToRead, __rip HANDLE hFile)
{
	DWORD nTotalBytes = dwBytesToRead;
	while ( nTotalBytes > 0 ) 
	{
		DWORD  nBytesRead=0;
		DWORD  nBytesToRead = nTotalBytes;
		BOOL bRet = ::ReadFile(hFile,
			(LPVOID)(pBuffer+nBytesRead),
			nBytesToRead,
			&nBytesRead,
			NULL);
		if ( bRet==FALSE || nBytesRead==0 ) {
			UINT64 off = Rlibs::FileTell(hFile);
			return dwBytesToRead-nTotalBytes;
		}
		nTotalBytes -= nBytesRead;
	}
	return dwBytesToRead;
}

RLIBS_API DWORD Rlibs::FileReadStatic(__rop PBYTE pBuffer, __rip DWORD dwBytesToRead, __rip HANDLE hFile, __rip UINT64 distance, __rip DWORD MoveMethod)
{
	UINT64 qwFileCurrentOffset = Rlibs::FileTell(hFile);
	Rlibs::FileSeek(hFile, distance, MoveMethod);

	DWORD nTotalBytes = dwBytesToRead;
	while ( nTotalBytes > 0 ) 
	{
		DWORD  nBytesRead=0;
		DWORD  nBytesToRead = nTotalBytes;
		BOOL bRet = ::ReadFile(hFile,
			(LPVOID)(pBuffer+nBytesRead),
			nBytesToRead,
			&nBytesRead,
			NULL);
		if ( bRet==FALSE || nBytesRead==0 ) {
			Rlibs::FileSeek(hFile, qwFileCurrentOffset, FILE_BEGIN);	// 恢复原位置
			return dwBytesToRead-nTotalBytes;
		}
		nTotalBytes -= nBytesRead;
	}
	Rlibs::FileSeek(hFile, qwFileCurrentOffset, FILE_BEGIN);	// 恢复原位置
	return dwBytesToRead;
}

RLIBS_API DWORD Rlibs::FileWrite(__rip PBYTE pBuffer, __rip DWORD dwBytesToWrite, __rip HANDLE hFile)
{
	DWORD nTotalBytes = dwBytesToWrite;
	while ( nTotalBytes > 0 ) 
	{
		DWORD  nBytesWrite=0;
		DWORD  nBytesToWrite = nTotalBytes;
		BOOL bRet = ::WriteFile(hFile,
			(LPVOID)(pBuffer+nBytesWrite),
			nBytesToWrite,
			&nBytesWrite,
			NULL);
		if ( bRet==FALSE || nBytesWrite==0 ) {
			return dwBytesToWrite-nTotalBytes;
		}
		nTotalBytes -= nBytesWrite;
	}
	return dwBytesToWrite;
}

RLIBS_API DWORD Rlibs::FileWriteStatic(__rip PBYTE pBuffer, __rip DWORD dwBytesToWrite, __rip HANDLE hFile, __rip UINT64 distance, __rip DWORD MoveMethod)
{
	UINT64 qwFileCurrentOffset = Rlibs::FileTell(hFile);
	Rlibs::FileSeek(hFile, distance, MoveMethod);

	DWORD nTotalBytes = dwBytesToWrite;
	while ( nTotalBytes > 0 ) 
	{
		DWORD  nBytesWrite=0;
		DWORD  nBytesToWrite = nTotalBytes;
		BOOL bRet = ::WriteFile(hFile,
			(LPVOID)(pBuffer+nBytesWrite),
			nBytesToWrite,
			&nBytesWrite,
			NULL);
		if ( bRet==FALSE || nBytesWrite==0 ) {
			Rlibs::FileSeek(hFile, qwFileCurrentOffset, FILE_BEGIN);	// 恢复原位置
			return dwBytesToWrite-nTotalBytes;
		}
		nTotalBytes -= nBytesWrite;
	}
	Rlibs::FileSeek(hFile, qwFileCurrentOffset, FILE_BEGIN);	// 恢复原位置
	return dwBytesToWrite;
}

static inline DWORD _FilePrintfA(HANDLE hFile, LPCSTR szFormat, va_list argsList)
{
	char szBuffer[FILE_FMT_BUFFER_LENGTH] = {0};
	vsnprintf_s(szBuffer, sizeof(szBuffer), sizeof(szBuffer)-1, szFormat, argsList);
	return Rlibs::FileWrite((PBYTE)szBuffer, (DWORD)strlen(szBuffer), hFile);
}

static inline DWORD _FilePrintfW(HANDLE hFile, LPCWSTR szFormat, va_list argsList)
{
	wchar_t wszBuffer[FILE_FMT_BUFFER_LENGTH] = {0};
	_vsnwprintf_s(wszBuffer, sizeof(wszBuffer)/sizeof(wchar_t), sizeof(wszBuffer)/sizeof(wchar_t)-1, szFormat, argsList);
	return Rlibs::FileWrite((PBYTE)wszBuffer, (DWORD)(wcslen(wszBuffer)*sizeof(wchar_t)), hFile);
}

RLIBS_API DWORD Rlibs::FilePrintfA(__rip HANDLE hFile, __rip LPCSTR szFormat, ...)
{
	va_list argsList;
	va_start(argsList, szFormat);
	DWORD dwRet = _FilePrintfA(hFile, szFormat, argsList);
	va_end(argsList);
	return dwRet;
}

RLIBS_API DWORD Rlibs::FilePrintfW(HANDLE __rip hFile, __rip LPCWSTR wszFormat, ...)
{
	va_list argsList;
	va_start(argsList, wszFormat);
	DWORD dwRet = _FilePrintfW(hFile, wszFormat, argsList);
	va_end(argsList);
	return dwRet;
}

RLIBS_API DWORD Rlibs::FilePrintf(__rip HANDLE hFile, __rip LPCTSTR tszFormat, ...)
{
	va_list argsList;
	va_start(argsList, tszFormat);
#ifdef UNICODE
	DWORD dwRet = _FilePrintfW(hFile, tszFormat, argsList);
#else
	DWORD dwRet = _FilePrintfA(hFile, tszFormat, argsList);
#endif
	va_end(argsList);
	return dwRet;
}

RLIBS_API BOOL Rlibs::FileEnd(HANDLE hFile)
{
	UINT64 qwCurrent = Rlibs::FileTell(hFile);
	if ( qwCurrent == (UINT64)-1 ) return TRUE;	// 异常则认为文件结束
	UINT64 qwFileSize = Rlibs::FileSize(hFile);
	if ( qwFileSize == (UINT64)-1 ) return TRUE;	// 异常则认为文件结束
	return (qwCurrent>=qwFileSize);
}

RLIBS_API LPTSTR Rlibs::PathFindDirectoryA(__rop LPSTR szPathName, __rip LPCSTR szPath)
{
	if ( szPathName == NULL ) { _ASSERT(false); return NULL; }
	strcpy_s(szPathName, strlen(szPath)+1, szPath);
	::PathRemoveFileSpecA(szPathName);
	return szPathName;
}

RLIBS_API LPWSTR Rlibs::PathFindDirectoryW(__rop LPWSTR wszPathName, __rip LPCWSTR wszPath)
{
	if ( wszPathName == NULL ) { _ASSERT(false); return NULL; }
	wcscpy_s(wszPathName, wcslen(wszPath)+1, wszPath);
	::PathRemoveFileSpecW(wszPathName);
	return wszPathName;
}

RLIBS_API LPSTR Rlibs::PathFindFileNameA(__rip LPCSTR szPath)
{
	return ::PathFindFileNameA(szPath);
}

RLIBS_API LPWSTR Rlibs::PathFindFileNameW(__rip LPCWSTR wszPath)
{
	return ::PathFindFileNameW(wszPath);
}

RLIBS_API LPSTR Rlibs::PathFindFileMainA(__rop LPSTR szFileName, __rip LPCSTR szPath)
{
	if ( szFileName == NULL ) { _ASSERT(false); return NULL; }
	PBYTE pFileName = (PBYTE)::PathFindFileNameA(szPath);
	PBYTE pFileExt  = (PBYTE)::PathFindExtensionA(szPath);
	memcpy((PBYTE)szFileName, pFileName, pFileExt-pFileName);
	strncpy_s(szFileName, (pFileExt-pFileName)/sizeof(char)+1, (LPSTR)pFileName, (pFileExt-pFileName)/sizeof(char));
	return szFileName;
}

RLIBS_API LPWSTR Rlibs::PathFindFileMainW(__rop LPWSTR wszFileName, __rip LPCWSTR wszPath)
{
	if ( wszFileName == NULL ) { _ASSERT(false); return NULL; }
	PBYTE pFileName = (PBYTE)::PathFindFileNameW(wszPath);
	PBYTE pFileExt  = (PBYTE)::PathFindExtensionW(wszPath);
	memcpy((PBYTE)wszFileName, pFileName, pFileExt-pFileName);
	wcsncpy_s(wszFileName, (pFileExt-pFileName)/sizeof(wchar_t)+1, (LPWSTR)pFileName, (pFileExt-pFileName)/sizeof(wchar_t));
	return wszFileName;
}

RLIBS_API LPSTR Rlibs::PathFindFileExtensionA(__rip LPCSTR szPath)
{
	return ::PathFindExtensionA(szPath);
}

RLIBS_API LPWSTR Rlibs::PathFindFileExtensionW(__rip LPCWSTR wszPath)
{
	return ::PathFindExtensionW(wszPath);
}
