#pragma once

#include "Shape.h"
class CUserData
{
public:
	CUserData();
	~CUserData();

	CShape			m_SHP;
	MBR				m_MBR;
	bool			m_bOpenSHP;
	GeoPoint		m_geoCenterPoint;	// ���� �߽� ��ǥ
	CPoint			m_scrCenterPoint;	// ȭ�� �߽� ��ǥ
	double			m_lfZoomFactor;		// ZoomIn/out�� ���� ����
	double			m_lfRatio;			// ��ũ�� -> Geo ��ǥ..
	CPoint			m_ptZoomWindowLT, m_ptZoomWindowBR; //�»�� ���� ���ϴ� ��..
	CRect			m_rctScreen;

	CUserGridData	m_compClsData; // 
	CUserGridData	m_networkCompClsData; // step3 import data
	CUserGridData	m_fragCurveParamData; // step4 import data
};

