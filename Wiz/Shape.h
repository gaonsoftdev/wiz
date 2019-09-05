// Shape.h: interface for the CShape class.
//
// Coded by Scene, Sanghee(shshin@gaia3d.com)
// 2001-11-14
// Ver 0.5
// Copyright(c) 2001 Gaia3D Inc & Scene, Sanghee
//
//////////////////////////////////////////////////////////////////////


class CShape
{
public:	// for variables
	CString		m_strSHPPath;				//Name of SHP file
	CString		m_strSHXPath;				//Name of SHX file

	int			m_nRecords;					// Number of Record
	int			m_nShapeType;				/* SHPT_* */
	MBR			m_MBR;						// Minimum Bounding Rectangle

	GeoPoint*	m_pSHPPoints;				// Real GeoPoint
	PolyObject*	m_pSHPPolyObjects;			// Real PolyObject

	bool		m_bOpen;					// To check whether SHP is Opened or not

	// Apparance 
	int			m_lineType;					// SHP LineType
	int			m_lineWidth;				// SHP LineWidth
	COLORREF	m_lineColor;				// SHP LineColor

	// Display 
	double		m_lfMainRatio;				// 전체 화면 대 지도 비율
	double		m_lfZoomFactor;				// 확대/축소 비율
	GeoPoint	m_geoCenterPoint;			// 지도 중심 점
	CPoint		m_scrCenterPoint;			// 화면 중심 점

public: // for functions
	CShape();
	virtual ~CShape();

	void		SwapWord(int _length, void* _pWord);	// Byte order changing
	bool		Open(CString	_filename);				// SHP file open
	bool		Close();
	void		Draw(CDC* _pDC, double _ZoomFactor, GeoPoint _ptMapCenter, CRect _rctScreen, double _lfRatio);

protected:
	void		DrawPoint(CDC* _pDC);
	void		DrawArc(CDC* _pDC);
	void		DrawPolygon(CDC* _pDC);
	void		DrawMultiPoint(CDC* _pDC);

	GeoPoint	DeviceToWorld(const CPoint&, double _lfRatio);
	CPoint		WorldToDevice(const GeoPoint& _geoPoint, double _lfRatio);
};