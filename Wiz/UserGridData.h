#pragma once
class CUserGridData
{
public:
	CUserGridData();
	CUserGridData(const CUserGridData& data);
	//CUserGridData(int row, int col, CStringArray* arr);
	~CUserGridData();

	CString** GetData();
	void SetData(int row, int col, const CStringArray& arr);
	void SetData(int row, int col, const CString** arr);
	int GetDataRow();
	int GetDataCol();
	CString GetDataFilename();
	void SetDataFilename(CString filename);
	CStringArray& GetColumnHeaders();
	void SetColumnHeaders(const CStringArray& headers);
	void AddColumnHeader(const CString& header);
	bool IsRead();

	CUserGridData& operator=(const CUserGridData& data);
protected                           :
	CString			m_gridDataFile; // data source filename
	CStringArray	m_columnHeaders; // grid column headers
	int				m_gridDataRow; // grid data row size(only data)
	int				m_gridDataCol; // grid data column size(only data)
	bool			m_isRead;
	CString**		m_gridData; // grid data 2 array
};

