#ifndef __RLIBS_FILE_DLLEXPORT_INCLUDED_H__
#define __RLIBS_FILE_DLLEXPORT_INCLUDED_H__

namespace Rlibs 
{

// 检查一个路径是否存在（绝对路径、相对路径，文件或文件夹均可）
RLIBS_API bool FileExistsA(__rip const char *szPath);
RLIBS_API bool FileExistsW(__rip const wchar_t *szPath);
#ifdef UNICODE
#define FileExists	FileExistsW
#else
#define FileExists	FileExistsA
#endif // !UNICODE

// 检查一个文件夹是否存在（绝对路径、相对路径均可）
RLIBS_API bool FolderExistsA(__rip const char *szPath);
RLIBS_API bool FolderExistsW(__rip const wchar_t *szPath);
#ifdef UNICODE
#define FolderExists	FolderExistsW
#else
#define FolderExists	FolderExistsA
#endif // !UNICODE

// 	RLIBS_API char *PathFindDirectory(const char *szPathName, const char *szPath);
// 	RLIBS_API char *PathFindFileName(const char *szPath);
// 	RLIBS_API char *PathFindFileMain(LPTSTR szFileName, LPCTSTR lpszPath);
// 	RLIBS_API char *PathFindFileExtension(LPCTSTR lpszPath);
 
// RLIBS_API HANDLE FileOpenA(LPCSTR szFilename, DWORD dwDesiredAccess);
// RLIBS_API HANDLE FileOpenW(LPCWSTR szFilename, DWORD dwDesiredAccess);
// RLIBS_API HANDLE FileOpen(LPCTSTR szFilename, DWORD dwDesiredAccess);
// RLIBS_API BOOL FileClose(HANDLE hFile);
// RLIBS_API UINT64 FileSizeA(LPCSTR szFilename);
// RLIBS_API UINT64 FileSizeW(LPCWSTR szFilename);
// RLIBS_API UINT64 FileSize(LPCTSTR szFilename);
// RLIBS_API UINT64 FileSize(HANDLE hFile);
// RLIBS_API UINT64 FileTell(HANDLE hFile);
// RLIBS_API UINT64 FileSeek(HANDLE hFile, INT64 distance, DWORD MoveMethod);
// RLIBS_API DWORD FileRead(PBYTE pBuffer, DWORD dwBytesToRead, HANDLE hFile);
// RLIBS_API DWORD FileReadEx(PBYTE pBuffer, DWORD dwBytesToRead, HANDLE hFile, UINT64 distance, DWORD MoveMethod);	// 读取后，文件流指针位置不会改变
// RLIBS_API DWORD FileWrite(PBYTE pBuffer, DWORD dwBytesToWrite, HANDLE hFile);
// RLIBS_API DWORD FileWriteEx(PBYTE pBuffer, DWORD dwBytesToWrite, HANDLE hFile, UINT64 distance, DWORD MoveMethod);	// 写入后，文件流指针位置不会改变
// RLIBS_API DWORD FilePrintfA(HANDLE hFile, LPCSTR szFormat, ...);
// RLIBS_API DWORD FilePrintfW(HANDLE hFile, LPCWSTR szFormat, ...);
// RLIBS_API DWORD FilePrintf(HANDLE hFile, LPCTSTR szFormat, ...);
// RLIBS_API BOOL FileEnd(HANDLE hFile);

}; // namespace Rlibs

#endif // __RLIBS_FILE_DLLEXPORT_INCLUDED_H__
