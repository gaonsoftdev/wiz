#pragma once

#include "Shape.h"
#include "UserGridData.h"
#include "UserGridDataArray.h"

class CUserData
{
public:
	CUserData();
	~CUserData();

	CShape						m_SHP;
	MBR							m_MBR;
	bool						m_bOpenSHP;
	GeoPoint					m_geoCenterPoint;	// ���� �߽� ��ǥ
	CPoint						m_scrCenterPoint;	// ȭ�� �߽� ��ǥ
	double						m_lfZoomFactor;		// ZoomIn/out�� ���� ����
	double						m_lfRatio;			// ��ũ�� -> Geo ��ǥ..
	CPoint						m_ptZoomWindowLT, m_ptZoomWindowBR; //�»�� ���� ���ϴ� ��..
	CRect						m_rctScreen;

	CUserGridData				m_compClsData; // step2 import data
	CUserGridData				m_networkCompClsData; // step3 import data
	CUserGridData				m_fragCurveParamData; // step4 import data
	CArray<CUserGridData, CUserGridData&> m_seismicSourcesArr;
	//CUserGridDataArray			m_seismicSourcesArr; // step5 import data
};

