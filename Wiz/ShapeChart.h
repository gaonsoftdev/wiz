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
	CRect					m_mapRect; // ������ �׷��� �κ�

	int						m_chartType;
	bool					m_isSetShapeData;
	CShape*					m_pShape;
	double					m_lfZoomFactor;
	double					m_lfRatio;
	GeoPoint				m_geoCenterPoint;	// ���� �߽� ��ǥ
	CPoint					m_scrCenterPoint;	// ȭ�� �߽� ��ǥ

	int						m_labelCount;
	int						m_ratioWidth; // ������ ������ ���� map ��
	int						m_ratioHeight; // ������ ������ ���� map ����
	double					m_labelYOffset; // Y�� �� offset
	double					m_labelXOffset; // X�� �� offset
	double					m_geoPointRatio; // 1 geo point ����

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

