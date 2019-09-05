#pragma once
class CUserGridData
{
public:
	CUserGridData();
	CUserGridData(int row, int col, CStringArray* arr);
	~CUserGridData();

	CString**		GetData();
	void			SetData(int row, int col, CStringArray* arr);
	int				GetDataRow();
	int				GetDataCol();
	CString*		GetDataFilename();
	void			SetDataFilename(CString filename);
	CStringArray*	GetColumnHeaders();
	void			SetColumnHeaders(const CStringArray& headers);
	bool			IsRead();
private:
	CString			m_gridDataFile; // data source filename
	CStringArray	m_columnHeaders; // grid column headers
	int				m_gridDataRow; // grid data row size(only data)
	int				m_gridDataCol; // grid data column size(only data)
	bool			m_isRead;
	CString**		m_gridData; // grid data 2 array
};

