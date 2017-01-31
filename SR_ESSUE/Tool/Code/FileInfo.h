#ifndef FileInfo_h__
#define FileInfo_h__


class CFileInfo
{
public:
	wstring		ConvertRelativePath(wstring wstrFullPath);

public:
	CFileInfo(void);
	~CFileInfo(void);
};


#endif // FileInfo_h__
