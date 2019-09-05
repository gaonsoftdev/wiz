#include "stdafx.h"
#include "ShapeChart.h"

ShapeChart::ShapeChart()
{
	TRACE(_T("ShapeChart()\n"));
	m_pParent = NULL;
	m_pCWnd = NULL;
	m_labelCount = 10;
	m_lfZoomFactor = 0.9;
	m_lfRatio = 0.0;
	m_networkCompsSize = 0;
	m_networkComps = NULL;
	m_isShowLegend = false;
	m_legendColorArr = NULL;
	m_isSetShapeData = false;
	m_legendRect.SetRect(0, 0, 0, 0);
	m_chartType = CHART_BASE;
}


ShapeChart::ShapeChart(CWnd* pParent, CWnd* pCWnd)
{
	TRACE(_T("ShapeChart(CWnd* pParent, CWnd* pCWnd)\n"));
	m_pParent = pParent;
	m_pCWnd = pCWnd;
	m_labelCount = 10;
	m_lfZoomFactor = 0.9;
	m_lfRatio = 0.0;
	m_networkCompsSize = 0;
	m_networkComps = NULL;
	m_isShowLegend = false;
	m_legendColorArr = NULL;
	m_isSetShapeData = false;
	m_legendRect.SetRect(0, 0, 0, 0);
	m_chartType = CHART_BASE;
}


ShapeChart::~ShapeChart()
{
	TRACE(_T("~ShapeChart()\n"));
	delete [] m_legendColorArr;
	m_legendColorArr = NULL;
}


void ShapeChart::SetParent(CWnd* pParend)
{
	m_pParent = pParend;
}


void ShapeChart::SetWindow(CWnd* pCWnd)
{
	m_pCWnd = pCWnd;
}


void ShapeChart::SetShape(CShape* shape)
{
	m_pShape = shape;
	m_isSetShapeData = true;
}


void ShapeChart::Draw()
{
	if (!m_isSetShapeData)
		return;

	CDC* pDC = m_pCWnd->GetDC();
	m_pCWnd->GetWindowRect(m_rect);
	m_pParent->ScreenToClient(m_rect);
	m_pParent->GetDC()->FillSolidRect(m_rect, RGB(255, 255, 255));

	// 지도가 그려질 부분(차트 전체 화면의 좌/하 10%를 제외한 모든 부분)
	m_mapRect.left = m_rect.Width() * 0.1;
	m_mapRect.top = 0;
	m_mapRect.right = m_rect.Width();
	m_mapRect.bottom = m_rect.Height() - (m_rect.Height() * 0.1);

	// 화면에 뿌리기 위해서 ....
	m_geoCenterPoint.x = (m_pShape->m_MBR.xmax + m_pShape->m_MBR.xmin) / 2;
	m_geoCenterPoint.y = (m_pShape->m_MBR.ymax + m_pShape->m_MBR.ymin) / 2;

	ASSERT_VALID(pDC);
	if (!pDC)
		return;

	// 종횡비 계산..
	double lfRatio_X = fabs((m_mapRect.Width()) / (m_pShape->m_MBR.xmax - m_pShape->m_MBR.xmin));
	double lfRatio_Y = fabs((m_mapRect.Height()) / (m_pShape->m_MBR.ymax - m_pShape->m_MBR.ymin));

	// 비율 계산...
	if (lfRatio_X < lfRatio_Y)
		m_lfRatio = lfRatio_X;
	else
		m_lfRatio = lfRatio_Y;

	// 화면 중심좌료(X, Y)
	m_scrCenterPoint.x = (m_mapRect.right - m_mapRect.left) / 2;
	m_scrCenterPoint.y = (m_mapRect.bottom - m_mapRect.top) / 2;

#ifdef _DEBUG
	TRACE("\nm_geoCenterPoint.x = %f \nm_geoCenterPoint.y = %f \nm_lfZoomFactor = %f \nm_lfRatio = %f \n", m_geoCenterPoint.x, m_geoCenterPoint.y, m_lfZoomFactor, m_lfRatio);
	TRACE("\nm_scrCenterPoint.x = %d \nm_scrCenterPoint.y = %d \nlfRatio_X = %f \nlfRatio_Y = %f \n", m_scrCenterPoint.x, m_scrCenterPoint.y, lfRatio_X, lfRatio_Y);
	TRACE("\nchartRect.left = %d \nchartRect.top = %d \nchartRect.right = %d \nchartRect.bottom = %d \nchartRect.width = %d \nchartRect.height = %d \n", m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, m_rect.Width(), m_rect.Height());
	TRACE("\nm_mapRect.left = %d \nm_mapRect.top = %d \nm_mapRect.right = %d \nm_mapRect.bottom = %d \nm_mapRect.width = %d \nm_mapRect.height = %d \n", m_mapRect.left, m_mapRect.top, m_mapRect.right, m_mapRect.bottom, m_mapRect.Width(), m_mapRect.Height());
	TRACE("\nx-min = %f \nx-max = %f \ny-min = %f \ny-max = %f \n", m_pShape->m_MBR.xmin, m_pShape->m_MBR.xmax, m_pShape->m_MBR.ymin, m_pShape->m_MBR.ymax);
#endif

	//  double buffering
	CDC memDC;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap = nullptr;

	// 현재 윈도우(pDC)와 호환되는 DC(1 x 1)를 생성
	if (memDC.CreateCompatibleDC(pDC))
	{
		// 현재 윈도우(pDC)에 있는 DC에 내용과 같은 비트맵(width x height)을 생성
		if (bitmap.CreateCompatibleBitmap(pDC, m_mapRect.Width(), m_mapRect.Height()))
		{
			pDrawDC = &memDC;
			// 생성된 DC에 비트맵을 맵핑(bitmap이 변경되면 화면이 계속 바뀜)
			pOldBitmap = memDC.SelectObject(&bitmap);
		}
	}

	CRect rr(0, 0, m_mapRect.Width(), m_mapRect.Height());
	pDrawDC->FillSolidRect(&rr, RGB(255, 255, 230));

	// shape 파일내용 그리기
	m_pShape->Draw(pDrawDC, m_lfZoomFactor, m_geoCenterPoint, m_mapRect, m_lfRatio);

	//Swap buffers
	if (pDrawDC != pDC)
	{
		pDC->BitBlt(m_mapRect.left, m_mapRect.top, m_mapRect.Width(), m_mapRect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);
	}

	// Draw asixs
	CString str;
	CRect r;
	CPen scale_pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *p_oldPen = NULL;

	double diffValueX = m_pShape->m_MBR.xmax - m_pShape->m_MBR.xmin;
	double diffValueY = m_pShape->m_MBR.ymax - m_pShape->m_MBR.ymin;
	m_geoPointRatio = m_lfRatio * m_lfZoomFactor;
	m_ratioWidth = diffValueX * m_geoPointRatio;
	m_ratioHeight = diffValueY * m_geoPointRatio;

	// y축의 눈금당 좌표의 높이를 설정한다.
	double step = m_ratioHeight / double(m_labelCount - 1);
	double pos = 0.0;
	m_labelYOffset = ((m_mapRect.bottom - m_ratioHeight) / 2);

	// y축의 눈금당 수치값을 설정한다.
	double scale = (m_pShape->m_MBR.ymax - m_pShape->m_MBR.ymin) / double(m_labelCount - 1);
	int i = 0;
	for (i = 0; i < m_labelCount; i++) {
		// 눈금과 수치선을 그릴 y좌표를 설정한다.
		pos = m_labelYOffset + step * i;
		// 눈금을 그릴 펜을 설정한다.
		p_oldPen = pDC->SelectObject(&scale_pen);
		// y축의 눈금을 그린다.
		pDC->MoveTo(m_mapRect.left - 1, int(pos));
		pDC->LineTo(m_mapRect.left - 6, int(pos));
		// 기존의 펜으로 대체한다.
		pDC->SelectObject(p_oldPen);
		// 눈금의 수치(최대값을 눈금의 갯수로 나눈 값)를 문자로 출력한다.
		str.Format(_T("%4.3f"), m_pShape->m_MBR.ymax - scale * i);
		r.SetRect(0, int(pos - 8), m_mapRect.left - 8, int(pos + 10));
		pDC->DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	// x축의 눈금당 좌표의 높이를 설정한다.
	step = m_ratioWidth / double(m_labelCount - 1);
	pos = 0.0;
	m_labelXOffset = (m_rect.right - m_mapRect.Width() - m_rect.left) + ((m_mapRect.Width() - m_ratioWidth) / 2);
	// x축의 눈금당 수치값을 설정한다.
	scale = (m_pShape->m_MBR.xmax - m_pShape->m_MBR.xmin) / double(m_labelCount - 1);
	for (i = 0; i < m_labelCount; i++) {
		// 눈금과 수치선을 그릴 x좌표를 설정한다.
		pos = m_labelXOffset + (step * i);
		// 눈금을 그릴 펜을 설정한다.
		p_oldPen = pDC->SelectObject(&scale_pen);
		// x축의 눈금을 그린다.
		pDC->MoveTo(int(pos), m_mapRect.bottom + 1);
		pDC->LineTo(int(pos), m_mapRect.bottom + 6);
		// 기존의 펜으로 대체한다.
		pDC->SelectObject(p_oldPen);
		// 눈금의 수치(최대값을 눈금의 갯수로 나눈 값)를 문자로 출력한다.
		str.Format(_T("%4.3f"), m_pShape->m_MBR.xmin + scale * i);
		r.SetRect(int(pos - 10), m_mapRect.bottom + 10, int(pos + 100), m_rect.bottom);
		pDC->DrawText(str, r, DT_SINGLELINE | DT_LEFT | DT_TOP);
	}

	pDC->MoveTo(m_mapRect.left, m_mapRect.top);
	pDC->LineTo(m_mapRect.left, m_mapRect.bottom);
	pDC->LineTo(m_mapRect.right, m_mapRect.bottom);

	memDC.DeleteDC();
	pDrawDC->DeleteDC();
	bitmap.DeleteObject();
	pOldBitmap->DeleteObject();

	switch (m_chartType)
	{
	case CHART_NETWORKCOMP:
		DrawNetworkComponents();
		break;
	default:
		break;
	}

	if (m_isShowLegend)
	{
		DrawLegend();
	}
}

void ShapeChart::DrawNetworkComponents()
{
	CBrush brush;
	CBrush* pOldBrush;

	CDC* pDC = m_pCWnd->GetDC();
	int brushIndex = 0;
	int oldClassID = 0;

	for (int i = 0; i < m_networkCompsSize; i++)
	{
		if (oldClassID != m_networkComps[i].m_classID) {
			oldClassID = m_networkComps[i].m_classID;
			brushIndex++;
			brush.DeleteObject();
			brush.CreateSolidBrush(m_legendColorArr[brushIndex - 1]);
		}
		pOldBrush = pDC->SelectObject(&brush);
		CPoint point = GeoPointToWindowPoint(m_networkComps[i].m_X, m_networkComps[i].m_Y);
		pDC->Ellipse(point.x - m_legendSize, point.y - m_legendSize, point.x + m_legendSize, point.y + m_legendSize);
		pDC->SelectObject(pOldBrush);
	}
}


void ShapeChart::SetNetworkComponents(NetworkComponent* networkComps, int count)
{
	m_networkComps = networkComps;
	m_networkCompsSize = count;
	m_legendSize = ((m_mapRect.Width() > m_mapRect.Height()) ? m_mapRect.Height() : m_mapRect.Width()) * 0.010; // circle size

	BubbleSort(m_networkComps, m_networkCompsSize);
	int oldClassID = 0;
	m_legendCount = 0;
	CString label;
	for (int i = 0; i < m_networkCompsSize; i++)
	{
		if (oldClassID != m_networkComps[i].m_classID) {
			oldClassID = m_networkComps[i].m_classID;
			label.Format(_T("%d"), oldClassID);
			m_legendLabelArr.Add(label);
			m_legendCount++;
		}
	}
	m_legendColorArr = new COLORREF[m_legendCount];
	for (int i = 0; i < m_legendCount; i++)
	{
		COLORREF cRef;
		switch (i) {
		case 0:
			cRef = RGB(255, 0, 0);
			break;
		case 1:
			cRef = RGB(0, 255, 0);
			break;
		case 2:
			cRef = RGB(0, 0, 255);
			break;
		case 3:
			cRef = RGB(255, 255, 0);
			break;
		case 4:
			cRef = RGB(255, 0, 255);
			break;
		case 5:
			cRef = RGB(0, 255, 255);
			break;
		default:
			cRef = RGB(rand() % 255, rand() % 255, rand() % 255);
			break;
		}
		m_legendColorArr[i] = cRef;
	}

	m_isShowLegend = true;
}


void ShapeChart::DrawLegend()
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush brush;
	CPen* pOldPen;
	CBrush* pOldBrush;
	CDC* pDC = m_pCWnd->GetDC();

	CRect labelRect(0, 0, 0, 0);
	int rad = m_legendSize * 2;
	if (m_legendRect.IsRectEmpty())
	{
		m_legendRect.left = m_mapRect.right - 150;
		m_legendRect.top = m_mapRect.top;
	}
	int xPos= m_legendRect.left;
	int yPos = m_legendRect.top;
	int xOffset = xPos + rad + DEFAULT_PADDING;
	int width = 0;
	int height = 0;
	pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < m_legendCount; i++)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(m_legendColorArr[i]);
		pOldBrush = pDC->SelectObject(&brush);

		// 라벨 사이즈 계산
		CSize labelSize = pDC->GetTextExtent(m_legendLabelArr.GetAt(i));
		width = (width > labelSize.cx) ? width : labelSize.cx;
		height = ((rad > labelSize.cy) ? rad : labelSize.cy) + DEFAULT_PADDING; // 라벨과 도형중 큰쪽의 높이를 전체 높이로 사용
		// 라벨을 그릴 위치 셋팅(도형을 넣을만큼 빼고 왼쪽을 초기화)
		if (i == 0) {
			labelRect.SetRect(xOffset, m_legendRect.top, xOffset + width, m_legendRect.top + height);
		}
		else {
			labelRect.SetRect(xOffset, m_legendRect.bottom, xOffset + width, m_legendRect.bottom + height);
		}
		pDC->DrawText(m_legendLabelArr.GetAt(i), labelRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		int _w = xPos + m_legendSize;
		int _h = labelRect.top + labelRect.Height() / 2;
		pDC->Ellipse(_w - m_legendSize, _h - m_legendSize, _w + m_legendSize, _h + m_legendSize);
		pDC->SelectObject(pOldBrush);
		m_legendRect.bottom = labelRect.bottom;
		m_legendRect.right = (m_legendRect.right > labelRect.right) ? m_legendRect.right : labelRect.right;
	}
	pDC->SelectObject(pOldPen);

	//m_pCWnd->GetDC()->Rectangle(m_legendRect); // 흰색이라 안보임 나중에 투명으로 처리하면 살려라!!!
}


void ShapeChart::ReMBR(CShape* shape, const MBR& _mbr)
{
	m_pShape->m_geoCenterPoint.x = (_mbr.xmax + _mbr.xmin) / 2;
	m_pShape->m_geoCenterPoint.y = (_mbr.ymax + _mbr.ymin) / 2;
}


CPoint ShapeChart::GeoPointToWindowPoint(double x, double y)
{
	CPoint point;
	point.x = m_labelXOffset + (m_geoPointRatio * (abs(x - m_pShape->m_MBR.xmin)));
	point.y = m_ratioHeight + m_labelYOffset - (m_geoPointRatio * (abs(y - m_pShape->m_MBR.ymin)));
	return point;
}


void ShapeChart::BubbleSort(NetworkComponent arrData[], int count)
{
	int i, j, flag = 1;
	NetworkComponent temp;
	int comparison_count = 0;

	for (i = 0; i < count - 1; i++) {
		// 각 패스의 시작시점에서 flag값을 1로 설정한다. 
		flag = 1;
		for (j = 0; j < count - 1 - i; j++) {
			comparison_count++;
			if (arrData[j].m_classID > arrData[j + 1].m_classID) {
				// 자리 바꿈이 일어났다면 flag 값을 0으로 변경한다. 
				flag = 0;
				temp = arrData[j];
				arrData[j] = arrData[j + 1];
				arrData[j + 1] = temp;
			}
		}
		// flag값이 1이라는 소리는 한번도 자리바꿈이 일어나지 않았다는 뜻이다. 
		// 따라서 더 이상 정렬할 필요가 없다는 것으로 간주하여 종료한다. 
		if (flag == 1) break;
	}
}