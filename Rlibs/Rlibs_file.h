#ifndef __RLIBS_FILE_DLLEXPORT_INCLUDED_H__
#define __RLIBS_FILE_DLLEXPORT_INCLUDED_H__

namespace Rlibs 
{

// ���һ��·���Ƿ���ڣ�����·�������·�����ļ����ļ��о��ɣ�
RLIBS_API BOOL FileExistsA(__rip LPCSTR szPath);
RLIBS_API BOOL FileExistsW(__rip LPCWSTR wszPath);
inline RLIBS_API BOOL FileExists(__rip LPCTSTR tszPath) 
{	
#ifdef UNICODE
	return FileExistsW(tszPath);
#else
	return FileExistsA(tszPath);
#endif
}

// ���һ���ļ����Ƿ���ڣ�����·�������·�����ɣ�
RLIBS_API BOOL FolderExistsA(__rip LPCSTR szPath);
RLIBS_API BOOL FolderExistsW(__rip LPCWSTR szPath);
inline RLIBS_API BOOL FolderExists(__rip LPCTSTR tszPath) 
{	
#ifdef UNICODE
	return FolderExistsW(tszPath);
#else
	return FolderExistsA(tszPath);
#endif
}

// ���ļ�
// dwDesiredAccess: GENERIC_READ, GENERIC_WRITE, GENERIC_EXECUTE, GENERIC_ALL
RLIBS_API HANDLE FileOpenA(__rip LPCSTR szFilename, __rip DWORD dwDesiredAccess);
RLIBS_API HANDLE FileOpenW(__rip LPCWSTR wszFilename, __rip DWORD dwDesiredAccess);
inline RLIBS_API HANDLE FileOpen(__rip LPCTSTR tszFilename, __rip DWORD dwDesiredAccess) 
{	
#ifdef UNICODE
	return FileOpenW(tszFilename, dwDesiredAccess);
#else
	return FileOpenA(tszFilename, dwDesiredAccess);
#endif
}

// �ر��ļ�
RLIBS_API BOOL FileClose(__rip HANDLE hFile);

// ��ȡ�ļ���С
RLIBS_API UINT64 FileSize(__rip HANDLE hFile);
RLIBS_API UINT64 FileSizeA(__rip LPCSTR szFilename);
RLIBS_API UINT64 FileSizeW(__rip LPCWSTR wszFilename);
inline RLIBS_API UINT64 FileSize(__rip LPCTSTR tszFilename)
{
#ifdef UNICODE
	return FileSizeW(tszFilename);
#else
	return FileSizeA(tszFilename);
#endif
}

// �ļ���λ
RLIBS_API UINT64 FileTell(__rip HANDLE hFile);
RLIBS_API UINT64 FileSeek(__rip HANDLE hFile, __rip INT64 distance, __rip DWORD MoveMethod);

// ͬ���ļ���д
RLIBS_API DWORD FileRead(__rop PBYTE pBuffer, __rip DWORD dwBytesToRead, __rip HANDLE hFile);
RLIBS_API DWORD FileReadStatic(__rop PBYTE pBuffer, __rip DWORD dwBytesToRead, __rip HANDLE hFile, __rip UINT64 distance, __rip DWORD MoveMethod);	// ��ȡ���ļ���ָ��λ�ò���ı�
RLIBS_API DWORD FileWrite(__rip PBYTE pBuffer, __rip DWORD dwBytesToWrite, __rip HANDLE hFile);
RLIBS_API DWORD FileWriteStatic(__rip PBYTE pBuffer, __rip DWORD dwBytesToWrite, __rip HANDLE hFile, __rip UINT64 distance, __rip DWORD MoveMethod);	// д����ļ���ָ��λ�ò���ı�

// ��ʽ��д�ļ�
RLIBS_API DWORD FilePrintfA(HANDLE hFile, LPCSTR szFormat, ...);
RLIBS_API DWORD FilePrintfW(HANDLE hFile, LPCWSTR wszFormat, ...);
RLIBS_API DWORD FilePrintf(HANDLE hFile, LPCTSTR tszFormat, ...);

// �Ƿ��ѵ����ļ�β
RLIBS_API BOOL FileEnd(HANDLE hFile);

// ��ȡ�ļ�����·������Ϣ
RLIBS_API LPSTR PathFindDirectoryA(__rop LPSTR szPathName, __rip LPCSTR szPath);
RLIBS_API LPWSTR PathFindDirectoryW(__rop LPWSTR wszPathName, __rip LPCWSTR szPath);
RLIBS_API LPTSTR PathFindDirectory(__rop LPTSTR tszPathName, __rip LPCTSTR szPath)
{
#ifdef UNICODE
	return PathFindDirectoryW(tszPathName, szPath);
#else
	return PathFindDirectoryA(tszPathName, szPath);
#endif
}

RLIBS_API LPSTR PathFindFileNameA(__rip LPCSTR szPath);
RLIBS_API LPWSTR PathFindFileNameW(__rip LPCWSTR szPath);
inline RLIBS_API LPTSTR PathFindFileName(__rip LPCTSTR tszPath)
{
#ifdef UNICODE
	return PathFindFileNameW(tszPath);
#else
	return PathFindFileNameA(tszPath);
#endif
}

RLIBS_API LPSTR PathFindFileMainA(__rop LPSTR szFileName, __rip LPCSTR szPath);
RLIBS_API LPWSTR PathFindFileMainW(__rop LPWSTR wszFileName, __rip LPCWSTR wszPath);
inline RLIBS_API LPTSTR PathFindFileMain(__rop LPTSTR tszFileName, __rip LPCTSTR tszPath)
{
#ifdef UNICODE
	return PathFindFileMainW(tszFileName, tszPath);
#else
	return PathFindFileMainA(tszFileName, tszPath);
#endif
}

RLIBS_API LPSTR PathFindFileExtensionA(__rip LPCSTR szPath);
RLIBS_API LPWSTR PathFindFileExtensionW(__rip LPCWSTR wszPath);
inline RLIBS_API LPTSTR PathFindFileExtension(__rip LPCTSTR tszPath)
{
#ifdef UNICODE
	return PathFindFileExtensionW(tszPath);
#else
	return PathFindFileExtensionA(tszPath);
#endif
}

}; // namespace Rlibs

#endif // __RLIBS_FILE_DLLEXPORT_INCLUDED_H__
