// Shape.cpp: implementation of the CShape class.
//
// Coded by Scene, Sanghee(shshin@gaia3d.com)
// 2001-11-14
// Ver 0.5
// Copyright(c) 2001 Gaia3D Inc & Scene, Sanghee
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "time.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape::CShape()
{
	m_bOpen = FALSE;
	m_MBR.xmax = m_MBR.ymax = m_MBR.xmin = m_MBR.ymin = 0.;
	m_nShapeType = 0;
	m_pSHPPoints = NULL;
	m_pSHPPolyObjects = NULL;
	m_lineColor = RGB(0, 0, 0);
	m_lineWidth = 0;
	m_lineType = 0;
}

CShape::~CShape()
{
	Close();
}

void CShape::SwapWord(int _length, void* _pWord)
{
	int		i;
	unsigned char	temp;

	for (i = 0; i < _length / 2; i++)
	{
		temp = ((unsigned char *)_pWord)[i];
		((unsigned char *)_pWord)[i] = ((unsigned char *)_pWord)[_length - i - 1];
		((unsigned char *)_pWord)[_length - i - 1] = temp;
	}
}

bool CShape::Open(CString _filename)
{
	int tmp, i, j;

	m_strSHPPath = _filename;	//SHP file path
	//m_strSHPPath = _T("C:\\sample\\Road_Network.shp");	//Test code

	tmp = _filename.GetLength() - 4;
	CString ext = _T(".shx");
	m_strSHXPath = _filename.Mid(0, tmp) + ext; //SHX file path

	//open SHP/SHX file
	CFile fileSHP(m_strSHPPath, CFile::modeRead | CFile::typeBinary);
	CFile fileSHX(m_strSHXPath, CFile::modeRead | CFile::typeBinary);

	if (fileSHP == NULL || fileSHX == NULL)
	{
		AfxMessageBox(_T("SHP File Error!!"), IDOK | MB_ICONSTOP);
		return false;
	}

	/* release memory of exsiting one */
	if (m_bOpen)
		Close();

	/* Now read a Header of SHP/SHX */
	/*
		======================================
		SHP file structure
		======================================
		File Header(100Byte)
		Record Header(8Byte)
		Record Contents(가변Byte)
		Record Header(8Byte)
		Record Contents(가변Byte)
		.
		Record Header(8Byte)
		Record Contents(가변Byte)

		======================================
		File Header
		======================================
		------------------------------------------------------
		Position   Field        Value       Type    Byte Order
		------------------------------------------------------
		Byte 0     File Code    9994        Integer Big
		Byte 4     Unused       0           Integer Big
		Byte 8     Unused       0           Integer Big
		Byte 12    Unused       0           Integer Big
		Byte 16    Unused       0           Integer Big
		Byte 20    Unused       0           Integer Big
		Byte 24    File Length  File Length Integer Big
		Byte 28    Version      1000        Integer Little
		Byte 32    Shape Type   Shape Type  Integer Little
		Byte 36    Bounding Box Xmin        Double  Little
		Byte 44    Bounding Box Ymin        Double  Little
		Byte 52    Bounding Box Xmax        Double  Little
		Byte 60    Bounding Box Ymax        Double  Little
		Byte 68*   Bounding Box Zmin        Double  Little
		Byte 76*   Bounding Box Zmax        Double  Little
		Byte 84*   Bounding Box Mmin        Double  Little
		Byte 92*   Bounding Box Mmax        Double  Little
		-----------------------------------------------------
		* Unused, with value 0.0, if not Measured or Z type

		======================================
		SHX file structure
		======================================
		SHX header same 100-byte header as the .SHP file
	*/
	// Get File size & Number of records
	fileSHX.Seek(24L, SEEK_SET);
	fileSHX.Read(&tmp, sizeof(tmp));
	SwapWord(4, &tmp);	// Byte Order Changing

	int m_nFileSize = tmp * 2;	// get file size
	m_nRecords = (m_nFileSize - 100) / 8;	//get a number of records;

	// get shp type
	fileSHP.Seek(32L, SEEK_SET);
	fileSHP.Read(&m_nShapeType, sizeof(m_nShapeType));

	// Check a invalid shp type
	if (!(m_nShapeType == 1 || m_nShapeType == 3 || m_nShapeType == 5 || m_nShapeType == 8))
	{
		AfxMessageBox(_T("Invalid SHP Type.\nThis program only support Point, Arc, Polygon & MultiPoint SHP Type."), IDOK | MB_ICONSTOP);
		return false;
	}

	// get a MBR
	fileSHP.Read(&m_MBR, sizeof(MBR));

	// real routine of feature reading(point, arc, polygon, multipoint)
	switch (m_nShapeType)
	{
		// 포인트를 읽어들인다.
	case SHPT_POINT:
		m_pSHPPoints = new GeoPoint[m_nRecords];

		for (i = 0; i < m_nRecords; ++i)
		{
			fileSHX.Seek(100 + i * 8, SEEK_SET);
			fileSHX.Read(&tmp, sizeof(tmp));
			SwapWord(4, &tmp);
			tmp = tmp * 2;

			fileSHP.Seek(tmp + 12, SEEK_SET);
			fileSHP.Read((GeoPoint*)&m_pSHPPoints[i], 16);
		}
		break;

		// 폴리라인과 폴리곤을 읽어들인다.
	case SHPT_ARC:
	case SHPT_POLYGON:
		m_pSHPPolyObjects = new PolyObject[m_nRecords];

		for (i = 0; i < m_nRecords; ++i)
		{
			fileSHX.Seek(100 + i * 8, SEEK_SET);
			fileSHX.Read(&tmp, sizeof(tmp));
			SwapWord(4, &tmp);
			tmp = tmp * 2;

			fileSHP.Seek(tmp + 12, SEEK_SET);
			fileSHP.Read((MBR*)&m_pSHPPolyObjects[i].m_MBR, 32); // get MBR
			fileSHP.Read(&m_pSHPPolyObjects[i].m_nNumParts, 4); // get parts number
			fileSHP.Read(&m_pSHPPolyObjects[i].m_nNumPoints, 4); // get points number

			m_pSHPPolyObjects[i].m_pParts = new int[m_pSHPPolyObjects[i].m_nNumParts];
			m_pSHPPolyObjects[i].m_pPoints = new GeoPoint[m_pSHPPolyObjects[i].m_nNumPoints];

			for (j = 0; j < m_pSHPPolyObjects[i].m_nNumParts; ++j)
			{
				fileSHP.Read(&m_pSHPPolyObjects[i].m_pParts[j], 4);
			}

			for (j = 0; j < m_pSHPPolyObjects[i].m_nNumPoints; ++j)
			{
				fileSHP.Read(&m_pSHPPolyObjects[i].m_pPoints[j], 16);
			}
		}
		break;

		// 다중점을 읽어들인다.
	case SHPT_MULTIPOINT:
		m_pSHPPolyObjects = new PolyObject[m_nRecords];

		for (i = 0; i < m_nRecords; ++i)
		{
			fileSHX.Seek(100 + i * 8, SEEK_SET);
			fileSHX.Read(&tmp, sizeof(tmp));
			SwapWord(4, &tmp);
			tmp = tmp * 2;

			fileSHP.Seek(tmp + 12, SEEK_SET);
			fileSHP.Read((MBR*)&m_pSHPPolyObjects[i].m_MBR, 32); // get MBR
			fileSHP.Read(&m_pSHPPolyObjects[i].m_nNumPoints, 4); // get points number

			m_pSHPPolyObjects[i].m_pPoints = new GeoPoint[m_pSHPPolyObjects[i].m_nNumPoints];

			for (j = 0; j < m_pSHPPolyObjects[i].m_nNumPoints; ++j)
			{
				fileSHP.Read(&m_pSHPPolyObjects[i].m_pPoints[j], 16);
			}
		}
		break;
	}
	// SHP 색을 랜덤하게 할당한다.
	srand((unsigned)time(NULL));	// 랜덤함수 초기화..
	//m_lineColor = RGB(rand() % 255, rand() % 255, rand() % 255); //SHP 색..
	m_lineColor = RGB(0, 0, 255); //SHP 색..

	fileSHX.Close();
	fileSHP.Close();

	m_bOpen = true;
	return true;
}

void CShape::Draw(CDC* _pDC, double _ZoomFactor, GeoPoint _ptMapCenter, CRect _rctScreen, double _lfRatio)
{
	m_lfZoomFactor = _ZoomFactor;
	m_geoCenterPoint = _ptMapCenter;
	m_scrCenterPoint.x = int(_rctScreen.Width() / 2);
	m_scrCenterPoint.y = int(_rctScreen.Height() / 2);
	m_lfMainRatio = _lfRatio;

	switch (m_nShapeType)
	{
	case SHPT_POINT:		//point drawing
		DrawPoint(_pDC);
		break;

	case SHPT_ARC:			//arc drawing
		DrawArc(_pDC);
		break;

	case SHPT_POLYGON:		//polygon drawing
		DrawPolygon(_pDC);
		break;

	case SHPT_MULTIPOINT:	//multipoint drawing
		DrawMultiPoint(_pDC);
		break;
	}
}

CPoint CShape::WorldToDevice(const GeoPoint& _geoPoint, double _lfRatio)
{
	CPoint	tmpPoint;

	tmpPoint.x = long(_lfRatio * (_geoPoint.x - m_geoCenterPoint.x) * m_lfZoomFactor + m_scrCenterPoint.x);
	tmpPoint.y = long(_lfRatio * (m_geoCenterPoint.y - _geoPoint.y) * m_lfZoomFactor + m_scrCenterPoint.y);

	return tmpPoint;
}

GeoPoint CShape::DeviceToWorld(const CPoint& _point, double _lfRatio)
{
	GeoPoint	tmpGeoPoint;

	tmpGeoPoint.x = m_geoCenterPoint.x + (_point.x - m_scrCenterPoint.x) / (m_lfZoomFactor * _lfRatio);
	tmpGeoPoint.y = m_geoCenterPoint.y - (_point.y - m_scrCenterPoint.y) / (m_lfZoomFactor * _lfRatio);

	return tmpGeoPoint;
}

// 포인트를 그린다.
void CShape::DrawPoint(CDC* _pDC)
{
	CPen pen;
	CBrush	brush;

	CPoint	tmpPoint;

	int savedDC = _pDC->SaveDC();

	pen.CreatePen(m_lineType, m_lineWidth, m_lineColor);
	brush.CreateSolidBrush(m_lineColor);

	_pDC->SelectObject(&pen);
	_pDC->SelectObject(&brush);

	// 포인트의 개수만큼 돌면서 화면에 그린다.
	for (int i = 0; i < m_nRecords; ++i)
	{
		tmpPoint = WorldToDevice(m_pSHPPoints[i], m_lfMainRatio);
		_pDC->Ellipse(tmpPoint.x - 2, tmpPoint.y - 2, tmpPoint.x + 2, tmpPoint.y + 2);
	}
	_pDC->RestoreDC(savedDC);
}

// 폴리라인 혹은 ARC라는 놈을 그린다.
void CShape::DrawArc(CDC* _pDC)
{
	CPen	pen;

	int savedDC = _pDC->SaveDC();

	pen.CreatePen(m_lineType, m_lineWidth, m_lineColor);
	_pDC->SelectObject(&pen);

	// 폴리라인의 개수만큼 돌면서 그린다.
	for (int i = 0; i < m_nRecords; ++i)
	{
		// 화면에 그릴 포인트를 할당하고..
		CPoint*	pScrPoints = new CPoint[m_pSHPPolyObjects[i].m_nNumPoints];
		for (int j = 0; j < m_pSHPPolyObjects[i].m_nNumPoints; ++j)
		{
			pScrPoints[j] = WorldToDevice(m_pSHPPolyObjects[i].m_pPoints[j], m_lfMainRatio);
		}

		// 파트에 관한 메모리를 할당하고..
		int* pParts = new int[m_pSHPPolyObjects[i].m_nNumParts];
		for (int j = 0; j < m_pSHPPolyObjects[i].m_nNumParts; ++j)
		{
			if (j == m_pSHPPolyObjects[i].m_nNumParts - 1)
				pParts[j] = m_pSHPPolyObjects[i].m_nNumPoints - m_pSHPPolyObjects[i].m_pParts[j];
			else
				pParts[j] = m_pSHPPolyObjects[i].m_pParts[j + 1] - m_pSHPPolyObjects[i].m_pParts[j];
		}
		// 그린다..
		_pDC->PolyPolyline(pScrPoints, (DWORD*)pParts, m_pSHPPolyObjects[i].m_nNumParts);

		delete[] pScrPoints;
		delete[] pParts;
	}
	_pDC->RestoreDC(savedDC);
}

// 폴리곤을 그린다.
void CShape::DrawPolygon(CDC* _pDC)
{
	CPen	pen;
	CBrush	brush;

	int savedDC = _pDC->SaveDC();
	pen.CreatePen(m_lineType, m_lineWidth, RGB(0, 0, 0));
	brush.CreateSolidBrush(m_lineColor);

	_pDC->SelectObject(&brush);
	_pDC->SelectObject(&pen);

	for (int i = 0; i < m_nRecords; ++i)
	{
		// 스크린 포인트를 할당하고..
		CPoint*	pScrPoints = new CPoint[m_pSHPPolyObjects[i].m_nNumPoints];
		for (int j = 0; j < m_pSHPPolyObjects[i].m_nNumPoints; ++j)
		{
			pScrPoints[j] = WorldToDevice(m_pSHPPolyObjects[i].m_pPoints[j], m_lfMainRatio);
		}

		// 파트 정보를 정리하고..
		int* pParts = new int[m_pSHPPolyObjects[i].m_nNumParts];
		for (int j = 0; j < m_pSHPPolyObjects[i].m_nNumParts; ++j)
		{
			if (j == m_pSHPPolyObjects[i].m_nNumParts - 1)
				pParts[j] = m_pSHPPolyObjects[i].m_nNumPoints - m_pSHPPolyObjects[i].m_pParts[j];
			else
				pParts[j] = m_pSHPPolyObjects[i].m_pParts[j + 1] - m_pSHPPolyObjects[i].m_pParts[j];
		}
		// 그린다..
		_pDC->PolyPolygon(pScrPoints, pParts, m_pSHPPolyObjects[i].m_nNumParts);

		delete[] pScrPoints;
		delete[] pParts;
	}
	_pDC->RestoreDC(savedDC);
}

// 다중점을 그린다.
void CShape::DrawMultiPoint(CDC* _pDC)
{
	CPen	pen;

	int savedDC = _pDC->SaveDC();

	pen.CreatePen(m_lineType, m_lineWidth, m_lineColor);
	_pDC->SelectObject(&pen);

	for (int i = 0; i < m_nRecords; ++i)
	{
		// 스크린용 점을 할당한다.
		CPoint*	pScrPoints = new CPoint[m_pSHPPolyObjects[i].m_nNumPoints];
		for (int j = 0; j < m_pSHPPolyObjects[i].m_nNumPoints; ++j)
		{
			pScrPoints[j] = WorldToDevice(m_pSHPPolyObjects[i].m_pPoints[j], m_lfMainRatio);
			_pDC->Ellipse(pScrPoints[j].x - 2, pScrPoints[j].y - 2, pScrPoints[j].x + 2, pScrPoints[j].y + 2);
		}
		delete[] pScrPoints;
	}
	_pDC->RestoreDC(savedDC);
}

// 할당된 메모리를 제거한다.
bool CShape::Close()
{
	if (m_bOpen)
	{
		int i;
		switch (m_nShapeType)
		{
		case SHPT_POINT:
			delete[]m_pSHPPoints;
			break;

		case SHPT_MULTIPOINT:
			for (i = 0; i < m_nRecords; ++i)
				delete[] m_pSHPPolyObjects[i].m_pPoints;
			break;

		case SHPT_ARC:
		case SHPT_POLYGON:
			for (i = 0; i < m_nRecords; ++i)
			{
				delete[] m_pSHPPolyObjects[i].m_pParts;
				delete[] m_pSHPPolyObjects[i].m_pPoints;
			}
			delete[] m_pSHPPolyObjects;
			break;
		}
	}
	m_bOpen = false;
	return true;
}

