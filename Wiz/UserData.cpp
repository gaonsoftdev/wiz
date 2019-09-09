#include "stdafx.h"
#include "UserData.h"


CUserData::CUserData()
{
	m_bOpenSHP = FALSE;
	m_lfZoomFactor = 0.0;
	m_lfRatio = 0.0;
	m_MBR.xmax = m_MBR.ymax = m_MBR.xmin = m_MBR.ymin = 0.;
	CUserGridData m_step2GridData1();
	CUserGridData m_networkCompData();
	CUserGridData m_fragCurveParamData();
	TRACE("Construnt UserData\n");
}


CUserData::~CUserData()
{
	TRACE("Destroy UserData\n");
}