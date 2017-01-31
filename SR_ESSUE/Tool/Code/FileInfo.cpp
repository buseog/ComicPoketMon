#include "StdAfx.h"
#include "FileInfo.h"
#include "Export_Function.h"
#include "Engine_Include.h"

CFileInfo::CFileInfo(void)
{
}

CFileInfo::~CFileInfo(void)
{
}

std::wstring CFileInfo::ConvertRelativePath(wstring wstrFullPath)
{
	TCHAR		szRelativePath[MAX_PATH] = L"";
	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// ��� ���(vcproj���� ��ġ) ���� �Լ�

	PathRelativePathTo((LPWSTR)szRelativePath, 
		szDirPath, 
		FILE_ATTRIBUTE_DIRECTORY, 
		wstrFullPath.c_str(), 
		FILE_ATTRIBUTE_NORMAL);

	return szRelativePath;
}