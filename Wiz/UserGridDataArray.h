#include "UserGridData.h"
#pragma once
class CUserGridDataArray
{
private:
	CUserGridData*		m_array;
	int					m_size;
	int					m_used;
public:
	CUserGridDataArray();
	~CUserGridDataArray();

	void Put(CUserGridData& data);
	CUserGridData& Get(int index);
	void Remove(int index);
	CUserGridData& operator[](int index);
};

