// Step3Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step3Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep3Page dialog


CStep3Page::CStep3Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep3Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep3Page)
	//}}AFX_DATA_INIT
}


CStep3Page::~CStep3Page()
{
	delete m_networkComps;
	m_networkComps = NULL;
}


void CStep3Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep3Page)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	DDX_Control(pDX, IDC_COMP_CLASS_GRID, m_compClassGrid);
	DDX_Control(pDX, IDC_NETWORK_COMP_GRID, m_networkCompGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep3Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep3Page)
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep3Page message handlers

BOOL CStep3Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);

	// Initialize.
	m_shapeChart.SetParent(this);
	m_shapeChart.SetWindow(GetDlgItem(IDC_MAP_PC));

	//CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep3Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_networkCompClsData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}


void CStep3Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);

	// Resize other windows for page window size.
	int gridHeight = m_pageRect.Height() * 0.25;
	GetDlgItem(IDC_NETWORK_COMP_GRID)->MoveWindow(
		DEFAULT_PADDING
		, m_pageRect.Height() * 0.1
		, m_pageRect.Width() * 0.6
		, gridHeight
	);
	GetDlgItem(IDC_NETWORK_COMP_GRID)->GetWindowRect(&m_networkCompGridRect);
	ScreenToClient(m_networkCompGridRect);

	GetDlgItem(IDC_COMP_CLASS_GRID)->MoveWindow(
		m_pageRect.Width() * 0.6 + DEFAULT_PADDING
		, m_pageRect.Height() * 0.1
		, m_pageRect.Width() * 0.25
		, gridHeight
	);
	GetDlgItem(IDC_COMP_CLASS_GRID)->GetWindowRect(&m_compClassGridRect);
	ScreenToClient(m_compClassGridRect);

	GetDlgItem(IDC_MAP_PC)->MoveWindow(
		DEFAULT_PADDING
		, m_networkCompGridRect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.6
		, m_pageRect.Height() * 0.6
	);
	GetDlgItem(IDC_MAP_PC)->ShowWindow(TRUE);
	
	// Initialize component class grid
	if (GetDataStore()->m_compClsData.GetColumnHeaders().IsEmpty()) {
		CGridUtil::Init(&m_compClassGrid, GetDataStore()->m_compClsData.GetColumnHeaders());
		CGridUtil::AutoFillColumns(&m_compClassGrid, &m_compClassGridRect);
	}
	// Fill data to grid, if there is a data.
	if (GetDataStore()->m_compClsData.IsRead()) {
		DrawCompClassGrid();
	}

	// Initialize network component grid.
	if (GetDataStore()->m_networkCompClsData.GetColumnHeaders().IsEmpty()) {
		CStringArray columns;
		columns.Add(_T("Network component ID"));
		columns.Add(_T("Class"));
		columns.Add(_T("X"));
		columns.Add(_T("Y"));
		columns.Add(_T("Link ID"));
		columns.Add(_T("Reconstruction cost"));
		columns.Add(_T("Soil type"));
		columns.Add(_T("Fundamental Period(sec)"));

		GetDataStore()->m_networkCompClsData.SetColumnHeaders(columns);
		CGridUtil::Init(&m_networkCompGrid, columns);
		CGridUtil::AutoFillColumns(&m_networkCompGrid, &m_networkCompGridRect);
	}
	// Fill data to grid, if there is a data.
	if (GetDataStore()->m_networkCompClsData.IsRead()) {
		DrawNetworkCompGrid();
	}
	// Set shape data, if there is a data.
	if (GetDataStore()->m_bOpenSHP) {
		m_shapeChart.SetShape(&GetDataStore()->m_SHP);
	}
	m_startToMove = false;
}


BOOL CStep3Page::OnKillActive()
{
	return TRUE;
}


void CStep3Page::OnDraw(CDC* pDC)
{
}


void CStep3Page::OnWizardImport()
{
	CString filename;
	CFileDlgUtil::GetExcelFile(filename);
	if (filename.IsEmpty()) {
		return;
	}
	//filename = _T("C:\\sample\\defcomp.xlsx"); // test code
	CXLEzAutomation XL(FALSE); // FALSE: 처리 과정을 화면에 보이지 않는다
	XL.OpenExcelFile(filename); // 액셀 파일 열기
	int row = 1;
	int col = 1;

	CStringArray valueArray;
	while (XL.GetCellValue(col, row) != _T("")) {
		while (XL.GetCellValue(col, row) != _T("")) {
			valueArray.Add(XL.GetCellValue(col, row));
			col++;
		}
		col = 1;
		row++;
	}
	XL.ReleaseExcel(); // 엑셀 파일 해제

	GetDataStore()->m_networkCompClsData.SetData(row - 1, 8, valueArray);
	GetDataStore()->m_networkCompClsData.SetDataFilename(filename);
	DrawNetworkCompGrid();
}


void CStep3Page::DrawCompClassGrid()
{
	CGridUtil::Draw(&m_compClassGrid, GetDataStore()->m_compClsData);
	for (int row = 1; row < m_compClassGrid.GetRowCount(); row++) {
		for (int col = 1; col < m_compClassGrid.GetColumnCount(); col++) {
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
			if (col == 1) {
				Item.strText.Format(_T("%d"), _ttoi(GetDataStore()->m_compClsData.GetData()[row - 1][col - 1]));
			}
			else {
				Item.strText.Format(_T("%s"), GetDataStore()->m_compClsData.GetData()[row - 1][col - 1]);
			}
			m_compClassGrid.SetItem(&Item);
		}
	}
	int arr[2] = { 1, 3 };
	CGridUtil::FillColumns(&m_compClassGrid, &m_compClassGridRect, arr, sizeof(arr) / sizeof(int));
	m_compClassGrid.UpdateData(TRUE);
}


void CStep3Page::DrawNetworkCompGrid()
{
	CGridUtil::Draw(&m_networkCompGrid, GetDataStore()->m_networkCompClsData);
	for (int row = 1; row < m_networkCompGrid.GetRowCount(); row++) {
		for (int col = 1; col < m_networkCompGrid.GetColumnCount(); col++) {
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
			switch (col) {
			case 1:
			case 2:
			case 5:
			case 6:
				Item.strText.Format(_T("%d"), _ttoi(GetDataStore()->m_networkCompClsData.GetData()[row - 1][col - 1]));
				break;
			case 3:
			case 4:
			case 8:
				Item.strText.Format(_T("%.3f"), _ttof(GetDataStore()->m_networkCompClsData.GetData()[row - 1][col - 1]));
				break;
			default:
				Item.strText.Format(_T("%s"), GetDataStore()->m_networkCompClsData.GetData()[row - 1][col - 1]);
				break;
			}
			m_networkCompGrid.SetItem(&Item);
		}
	}
	int arr[8] = { 2, 1, 1, 1, 1, 2, 1, 2 };
	CGridUtil::FillColumns(&m_networkCompGrid, &m_networkCompGridRect, arr, sizeof(arr) / sizeof(int));
	m_networkCompGrid.UpdateData(TRUE);

	// Draw network componets in shape chart, if there is shape data
	if (GetDataStore()->m_bOpenSHP) {
		int count = GetDataStore()->m_networkCompClsData.GetDataRow();
		m_networkComps = new NetworkComponent[count];
		for (int i = 0; i < count; i++)
		{
			m_networkComps[i].m_ID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][0]);
			m_networkComps[i].m_classID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][1]);
			m_networkComps[i].m_X = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][2]);
			m_networkComps[i].m_Y = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][3]);
			m_networkComps[i].m_linkID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][4]);
			m_networkComps[i].m_reconstCost = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][5]);
			m_networkComps[i].m_soilType = LPSTR(LPCTSTR(GetDataStore()->m_networkCompClsData.GetData()[i][6]));
			m_networkComps[i].m_fundPeriod = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][7]);
		}
		m_shapeChart.SetShape(&GetDataStore()->m_SHP);
		m_shapeChart.SetNetworkComponents(m_networkComps, count);
		m_shapeChart.m_chartType = CHART_NETWORKCOMP;
	}
}


void CStep3Page::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetDlgItem(IDC_MAP_PC)->GetWindowRect(&rect);
	TRACE("START: %d, %d", point.x, point.y);
	ScreenToClient(rect);
	rect.SetRect(rect.TopLeft() + m_shapeChart.m_legendRect.TopLeft(), rect.TopLeft() + m_shapeChart.m_legendRect.BottomRight());
	if (rect.PtInRect(point))
	{
		m_startPos = point;
		m_startToMove = true;
		CRect r;
		r.SetRect(m_shapeChart.m_rect.TopLeft(), m_shapeChart.m_rect.BottomRight());
		ClientToScreen(&r);
		ClipCursor(&r);
	}
	SetCapture();
	CNewWizPage::OnLButtonDown(nFlags, point);
}


void CStep3Page::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_startToMove)
	{
		TRACE("MOVE: %d, %d", point.x, point.y);
		m_endPos = point;
		CPoint pos = m_endPos - m_startPos;
		m_startPos = point;
		m_shapeChart.m_legendRect.SetRect(m_shapeChart.m_legendRect.TopLeft() + pos, m_shapeChart.m_legendRect.BottomRight() + pos);
		Invalidate();
	}

	CNewWizPage::OnMouseMove(nFlags, point);
}


void CStep3Page::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_startToMove)
	{
		TRACE("END: %d, %d", point.x, point.y);
		m_endPos = point;
		Invalidate();
		ClipCursor(NULL);
	}
	ReleaseCapture();
	m_startToMove = false;

	CNewWizPage::OnLButtonUp(nFlags, point);
}


void CStep3Page::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CNewWizPage::OnPaint()을(를) 호출하지 마십시오.

	m_shapeChart.Draw();
}
