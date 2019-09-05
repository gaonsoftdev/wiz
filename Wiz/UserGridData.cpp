#include "stdafx.h"
#include "UserGridData.h"


CUserGridData::CUserGridData()
{
	m_gridDataRow = 0;
	m_gridDataCol = 0;
	m_isRead = false;
}

CUserGridData::CUserGridData(int row, int col, CStringArray* arr)
{
	m_gridDataRow = 0;
	m_gridDataCol = 0;
	m_isRead = false;
	SetData(row, col, arr);
}

CUserGridData::~CUserGridData()
{
	TRACE("~CUserGridData");
	if (m_gridDataRow > 0) {
		for (int i = 0; i < m_gridDataRow; i++)
		{
			delete[] m_gridData[i];
		}
		delete[] m_gridData;
	}
}

CString** CUserGridData::GetData()
{
	return m_gridData;
}

void CUserGridData::SetData(int row, int col, CStringArray* arr)
{
	m_gridDataRow = row;
	m_gridDataCol = col;
	if (m_gridDataRow > 0) {
		m_gridData = new CString*[row];
		int idx = 0;
		int i = 0;
		for (i = 0; i < row; i++)
		{
			m_gridData[i] = new CString[col];
			for (int j = 0; j < col; j++)
			{
				m_gridData[i][j] = arr->GetAt(idx++);
			}
		}
		m_isRead = true;
	}
}

void CUserGridData::SetDataFilename(CString filename)
{
	m_gridDataFile = filename;
}

int CUserGridData::GetDataRow()
{
	return m_gridDataRow;
}

int CUserGridData::GetDataCol()
{
	return m_gridDataCol;
}

CString* CUserGridData::GetDataFilename()
{
	return &m_gridDataFile;
}

CStringArray* CUserGridData::GetColumnHeaders()
{
	return &m_columnHeaders;
}

void CUserGridData::SetColumnHeaders(const CStringArray& headers)
{
	m_columnHeaders.Copy(headers);
}

bool CUserGridData::IsRead()
{
	return m_isRead;
}
