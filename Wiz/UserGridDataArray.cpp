#include "stdafx.h"
#include "UserGridDataArray.h"


CUserGridDataArray::CUserGridDataArray() : m_size(1), m_used(0)
{
	m_array = new CUserGridData[m_size];
}


CUserGridDataArray::~CUserGridDataArray()
{
	if (m_size > 0) {
		delete[] m_array;
	}
}


void CUserGridDataArray::Put(CUserGridData& data)
{
	if (m_size > m_used)
	{
		m_array[m_used] = data;
		m_used++;
		return;
	}

	CUserGridData* temp = new CUserGridData[m_size];

	for (int i = 0; i < m_used; i++)
	{
		temp[i] = m_array[i];
	}

	delete[] m_array;

	m_size++;

	m_array = new CUserGridData[m_size];

	for (int i = 0; i < m_used; i++)
	{
		m_array[i] = temp[i];
	}

	m_array[m_used] = data;
	m_used++;

	delete[] temp;

	return;
 }


CUserGridData& CUserGridDataArray::Get(int index)
{
	return this->m_array[index];
}


void CUserGridDataArray::Remove(int index)
{
	if (m_used == 0) return;

	m_used--;
	CUserGridData* temp = new CUserGridData[m_used];

	for (int i = 0; i < m_used; i++)
		temp[i] = m_array[i];

	delete[] m_array;
	m_array = new CUserGridData[m_size];

	for (int i = 0; i < m_used; i++)
		temp[i] = m_array[i];

	delete[] temp;
	return;
}


CUserGridData& CUserGridDataArray::operator[](int index)
{
	return this->m_array[index];
}