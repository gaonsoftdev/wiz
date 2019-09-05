#pragma once
class CFileDlgUtil
{
public:
	CFileDlgUtil();
	~CFileDlgUtil();

	static void GetFile(CString filter, CString& filename);
	static void GetShapeFile(CString& filename);
	static void GetExcelFile(CString& filename);
};

