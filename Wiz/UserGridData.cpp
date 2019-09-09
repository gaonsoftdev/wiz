#include "stdafx.h"
#include "UserGridData.h"


CUserGridData::CUserGridData()
{
	m_gridDataRow = 0;
	m_gridDataCol = 0;
	m_gridDataFile = _T("");
	m_columnHeaders.SetSize(0);
	m_isRead = false;
	m_gridData = NULL;
}

CUserGridData::CUserGridData(const CUserGridData& data)
{
	if (m_gridData != NULL) {
		m_gridDataRow = data.m_gridDataRow;
		m_gridDataCol = data.m_gridDataCol;
		m_gridData = new CString*[m_gridDataRow];
		int idx = 0;
		int i = 0;
		for (i = 0; i < m_gridDataRow; i++)
		{
			m_gridData[i] = new CString[m_gridDataCol];
			for (int j = 0; j < m_gridDataCol; j++)
			{
				m_gridData[i][j] = data.m_gridData[i][j];
			}
		}
		m_isRead = true;
		m_gridDataFile = data.m_gridDataFile;
	}
	else {
		m_gridDataRow = 0;
		m_gridDataCol = 0;
		m_gridData = NULL;
		m_isRead = false;
		m_gridDataFile = _T("");
	}
	m_columnHeaders.Copy(data.m_columnHeaders);
}


CUserGridData::~CUserGridData()
{
	if (m_gridData != NULL) {
		for (int i = 0; i < m_gridDataRow; ++i)
		{
			delete[] m_gridData[i];
		}
		delete[] m_gridData;
		m_gridData = NULL;
	}
}


CString** CUserGridData::GetData()
{
	return m_gridData;
}


void CUserGridData::SetData(int row, int col, const CStringArray& arr)
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
				m_gridData[i][j] = arr.GetAt(idx++);
			}
		}
		m_isRead = true;
	}
}


void CUserGridData::SetData(int row, int col, const CString** arr)
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
				m_gridData[i][j] = arr[i][j];
			}
		}
		m_isRead = true;
	}
}


void CUserGridData::SetDataFilename(CString filename)
{
	m_gridDataFile = filename;
}


CString CUserGridData::GetDataFilename()
{
	return m_gridDataFile;
}


int CUserGridData::GetDataRow()
{
	return m_gridDataRow;
}


int CUserGridData::GetDataCol()
{
	return m_gridDataCol;
}


CStringArray& CUserGridData::GetColumnHeaders()
{
	return m_columnHeaders;
}


void CUserGridData::SetColumnHeaders(const CStringArray& headers)
{
	m_columnHeaders.Copy(headers);
}


void CUserGridData::AddColumnHeader(const CString& header)
{
	m_columnHeaders.Add(header);
}


bool CUserGridData::IsRead()
{
	return m_isRead;
}


CUserGridData& CUserGridData::operator=(const CUserGridData& data)
{
	m_gridDataRow = data.m_gridDataRow;
	m_gridDataCol = data.m_gridDataCol;
	m_gridData = new CString*[m_gridDataRow];
	int idx = 0;
	int i = 0;
	for (i = 0; i < m_gridDataRow; i++)
	{
		m_gridData[i] = new CString[m_gridDataCol];
		for (int j = 0; j < m_gridDataCol; j++)
		{
			m_gridData[i][j] = data.m_gridData[i][j];
		}
	}
	m_isRead = true;
	m_gridDataFile = data.m_gridDataFile;
	m_columnHeaders.Copy(data.m_columnHeaders);
	return *this;
}
