#include "stdafx.h"
#include "FileDlgUtil.h"


CFileDlgUtil::CFileDlgUtil()
{
}


CFileDlgUtil::~CFileDlgUtil()
{
}

void CFileDlgUtil::GetFile(CString filter, CString& filename)
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	// file loading
	if (dlg.DoModal() != IDOK)
		return;

	filename = dlg.GetPathName();
}

void CFileDlgUtil::GetShapeFile(CString& filename)
{
	TCHAR filter[] = _T("SHP Files (*.shp)|*.shp|");
	GetFile(filter, filename);
}

void CFileDlgUtil::GetExcelFile(CString& filename)
{
	TCHAR filter[] = _T("Excel Files (*.xls,*,xlsx)|*.xls;*.xlsx|");
	GetFile(filter, filename);
}