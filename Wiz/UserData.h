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
	GeoPoint					m_geoCenterPoint;	// 지도 중심 좌표
	CPoint						m_scrCenterPoint;	// 화면 중심 좌표
	double						m_lfZoomFactor;		// ZoomIn/out을 위한 변수
	double						m_lfRatio;			// 스크린 -> Geo 좌표..
	CPoint						m_ptZoomWindowLT, m_ptZoomWindowBR; //좌상단 점과 우하단 점..
	CRect						m_rctScreen;

	CUserGridData				m_compClsData; // step2 import data
	CUserGridData				m_networkCompClsData; // step3 import data
	CUserGridData				m_fragCurveParamData; // step4 import data
	CArray<CUserGridData, CUserGridData&> m_seismicSourcesArr;
	//CUserGridDataArray			m_seismicSourcesArr; // step5 import data
};

