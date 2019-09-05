#pragma once
class ShapeChart
{
#define CHART_BASE				0
#define CHART_NETWORKCOMP		1
public:
	ShapeChart();
	ShapeChart(CWnd* pParent, CWnd* pCWnd);
	~ShapeChart();

	CWnd*					m_pParent;
	CWnd*					m_pCWnd;
	CRect					m_rect;
	CRect					m_mapRect; // 지도가 그려질 부분

	int						m_chartType;
	bool					m_isSetShapeData;
	CShape*					m_pShape;
	double					m_lfZoomFactor;
	double					m_lfRatio;
	GeoPoint				m_geoCenterPoint;	// 지도 중심 좌표
	CPoint					m_scrCenterPoint;	// 화면 중심 좌표

	int						m_labelCount;
	int						m_ratioWidth; // 비율을 적용한 실제 map 폭
	int						m_ratioHeight; // 비율을 적용한 실제 map 높이
	double					m_labelYOffset; // Y축 라벨 offset
	double					m_labelXOffset; // X축 라벨 offset
	double					m_geoPointRatio; // 1 geo point 비율

	CRect					m_legendRect;

	void SetParent(CWnd* pParend);
	void SetWindow(CWnd* pCWnd);

	void SetShape(CShape* shape);
	void SetNetworkComponents(NetworkComponent* networkComps, int count);
	
	void Draw();
	void DrawNetworkComponents();
	void DrawLegend();
	
	void ReMBR(CShape* shape, const MBR& _mbr);
	CPoint GeoPointToWindowPoint(double x, double y);
	void BubbleSort(NetworkComponent parm_data[], int parm_count);
private:
	NetworkComponent*		m_networkComps;
	int						m_networkCompsSize;

	COLORREF*				m_legendColorArr;
	CStringArray			m_legendLabelArr;
	int						m_legendCount;
	int						m_legendSize;
	bool					m_isShowLegend;
};

