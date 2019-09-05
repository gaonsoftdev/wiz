// Step4Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step4Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep4Page dialog


CStep4Page::CStep4Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep4Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep4Page)
	//}}AFX_DATA_INIT
}

CStep4Page::~CStep4Page()
{
	delete m_chartView.getChart();
	delete m_fragCurveParams;
	m_fragCurveParams = NULL;
}

void CStep4Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep4Page)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	DDX_Control(pDX, IDC_FRAG_CURVE_PARAM_GRID, m_fragCurveParamGrid);
	DDX_Control(pDX, IDC_CHART_PC, m_chartView);
	DDX_Control(pDX, IDC_COMP_CURVE_COMBO, m_compCurveCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep4Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep4Page)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_IMPORT_BTN, &CStep4Page::OnBnClickedImportBtn)
	ON_WM_PAINT()
	ON_CBN_SELENDOK(IDC_COMP_CURVE_COMBO, &CStep4Page::OnCbnSelendokCompCurveCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep4Page message handlers

BOOL CStep4Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);
	
	//CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep4Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_fragCurveParamData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}

void CStep4Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);

	// Resize other windows for page window size.
	GetDlgItem(IDC_IMPORT_BTN)->MoveWindow(
		m_pageRect.right * 0.8 + DEFAULT_PADDING
		, DEFAULT_PADDING
		, m_pageRect.right * 0.15
		, m_pageRect.bottom * 0.1
	);
	int gridHeight = m_pageRect.Height() * 0.25;
	GetDlgItem(IDC_FRAG_CURVE_PARAM_GRID)->MoveWindow(
		DEFAULT_PADDING
		, m_pageRect.Height() * 0.1
		, m_pageRect.Width() * 0.6
		, gridHeight
	);
	GetDlgItem(IDC_FRAG_CURVE_PARAM_GRID)->GetWindowRect(&m_fragCurveParamGridRect);
	ScreenToClient(m_fragCurveParamGridRect);

	// Initialize fragility curve parameters grid.
	if (GetDataStore()->m_fragCurveParamData.GetColumnHeaders()->IsEmpty()) {
		CStringArray columns;
		columns.Add(_T("Class"));
		columns.Add(_T("DS1 IMm"));
		columns.Add(_T("DS1 β"));
		columns.Add(_T("DS2 IMm"));
		columns.Add(_T("DS2 β"));
		columns.Add(_T("DS3 IMm"));
		columns.Add(_T("DS3 β"));
		columns.Add(_T("DS4 IMm"));
		columns.Add(_T("DS4 β"));

		GetDataStore()->m_fragCurveParamData.SetColumnHeaders(columns);
		CGridUtil::Init(&m_fragCurveParamGrid, &columns);
		CGridUtil::AutoFillColumns(&m_fragCurveParamGrid, &m_fragCurveParamGridRect);
	}
	if (GetDataStore()->m_fragCurveParamData.IsRead()) {
		DrawFragCurveParamGrid();
	}
}

BOOL CStep4Page::OnKillActive()
{
	return TRUE;
}

void CStep4Page::OnDraw(CDC* pDC)
{
}

void CStep4Page::OnBnClickedImportBtn()
{
	CString filename;
	CFileDlgUtil::GetExcelFile(filename);
	if (filename.IsEmpty()) {
		return;
	}
	//filename = _T("C:\\sample\\fragcurve.xlsx"); // test code
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

	GetDataStore()->m_fragCurveParamData.SetData(row - 1, GetDataStore()->m_fragCurveParamData.GetColumnHeaders()->GetSize(), &valueArray);
	GetDataStore()->m_fragCurveParamData.SetDataFilename(filename);
	DrawFragCurveParamGrid();

	// Initialize component curve combobox
	CString str;
	m_compCurveCombo.Clear();
	for (int i = 0; i < GetDataStore()->m_fragCurveParamData.GetDataRow(); i++)
	{
		str.Format(_T("%d"), m_fragCurveParams[i].m_classID);
		m_compCurveCombo.AddString(str);
	}
}

void CStep4Page::DrawFragCurveParamGrid()
{
	CGridUtil::Draw(&m_fragCurveParamGrid, &GetDataStore()->m_fragCurveParamData);
	for (int row = 1; row < m_fragCurveParamGrid.GetRowCount(); row++) {
		for (int col = 1; col < m_fragCurveParamGrid.GetColumnCount(); col++) {
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
			switch (col) {
			case 1:
				Item.strText.Format(_T("%d"), _ttoi(GetDataStore()->m_fragCurveParamData.GetData()[row - 1][col - 1]));
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				Item.strText.Format(_T("%.4f"), _ttof(GetDataStore()->m_fragCurveParamData.GetData()[row - 1][col - 1]));
				break;
			default:
				Item.strText.Format(_T("%s"), GetDataStore()->m_fragCurveParamData.GetData()[row - 1][col - 1]);
				break;
			}
			m_fragCurveParamGrid.SetItem(&Item);
		}
	}
	int arr[9] = { 1, 2, 2, 2, 2, 2, 2, 2, 2 };
	CGridUtil::FillColumns(&m_fragCurveParamGrid, &m_fragCurveParamGridRect, arr, sizeof(arr) / sizeof(int));
	m_fragCurveParamGrid.UpdateData(TRUE);

	int count = GetDataStore()->m_fragCurveParamData.GetDataRow();
	m_fragCurveParams = new FragilityCurveParam[count];
	int col = 0;
	for (int i = 0; i < count; i++)
	{
		col = 0;
		m_fragCurveParams[i].m_classID	 = _ttoi(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS1IMm	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS1Beta	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS2IMm	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS2Beta	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS3IMm	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS3Beta	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS4IMm	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
		m_fragCurveParams[i].m_DS4Beta	 = _ttof(GetDataStore()->m_fragCurveParamData.GetData()[i][col++]);
	}
}

void CStep4Page::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CNewWizPage::OnPaint()을(를) 호출하지 마십시오.

	drawChart(&m_chartView);
}

//
// Draw the chart and display it in the given viewer
//
void CStep4Page::drawChart(CChartViewer *viewer)
{
	// 차트에 필요한 데이터
	/*
	double data0[] = { 42, 49, 33, 38, 51, 46, 29, 41, 44, 57, 59, 52, 37, 34, 51, 56,
		56, 60, 70, 76, 63, 67, 75, 64, 51 };
	double data1[] = { 50, 55, 47, 34, 42, 49, 63, 62, 73, 59, 56, 50, 64, 60, 67, 67,
		58, 59, 73, 77, 84, 82, 80, 84, 89 };
	double data2[] = { 87, 89, 85, 66, 53, 39, 24, 21, 37, 56, 37, 22, 21, 33, 13, 17,
		4, 23, 16, 25, 9, 10, 5, 7, 6 };
	const char *labels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23",
		"24" };
		*/
		// Create a XYChart object of size 900 x 500 pixels
	XYChart *c = new XYChart(900, 500); //차트의 전체 크기를 정한다

	// Set the plotarea at (50, 30) and of size 250 x 150 pixels.
	c->setPlotArea(50, 30, 800, 430); //차트위 위치와 높이 넓이를 정한다.

	// Add a legend box at (55, 0) (top of the chart) using 8 pts Arial Font. Set
	// background and border to Transparent.
	c->addLegend(55, 0, false, "", 8)->setBackground(Chart::Transparent);

	// Add a title to the x axis
	c->xAxis()->setTitle("Network Load for Jun 12");

	// Add a title to the y axis
	c->yAxis()->setTitle("MBytes");

	// Set the labels on the x axis.
	//c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0]))));

	// Display 1 out of 2 labels on the x-axis. Show minor ticks for remaining
	// labels.
	c->xAxis()->setLabelStep(2, 1);

	// Add three area layers, each representing one data set. The areas are drawn in
	// semi-transparent colors.
	/*
	c->addAreaLayer(DoubleArray(data2, (int)(sizeof(data2) / sizeof(data2[0]))),
		0x808080ff, "Server #1", 3);
	c->addAreaLayer(DoubleArray(data0, (int)(sizeof(data0) / sizeof(data0[0]))),
		0x80ff0000, "Server #2", 3);
	c->addAreaLayer(DoubleArray(data1, (int)(sizeof(data1) / sizeof(data1[0]))),
		0x8000ff00, "Server #3", 3);
	*/

	// Add a line layer to the chart with 3-pixel line width
	LineLayer *layer = c->addLineLayer();
	layer->setLineWidth(1);

	// Add 3 data series to the line layer
	RanSeries *r = new RanSeries(1);
	//DoubleArray data0 = r->getSeries(100, 160, -15, 15);
	DoubleArray data0 = r->getSeries(100, 0, 1);
	DoubleArray data1 = r->getSeries(100, 0, 1);
	DoubleArray data2 = r->getSeries(100, 0, 1);
	int index;
	index = m_compCurveCombo.GetCurSel();
	if (index >= 0 && index != CB_ERR)
	{
		switch (index)
		{
		case 1:
			layer->addDataSet(data0, 0x5588cc, "Alpha");
			break;
		case 2:
			layer->addDataSet(data1, 0xee9944, "Beta");
			break;
		default:
			layer->addDataSet(data2, 0x99bb55, "Gamma");
			break;
		}
	}


	DoubleArray timeStamps = r->getDateSeries(100, Chart::chartTime(2014, 1, 1), 86400);
	// The x-coordinates for the line layer
	layer->setXData(timeStamps);

	// Set the chart image to the WinChartViewer
	delete viewer->getChart();
	viewer->setChart(c);
}

void CStep4Page::OnCbnSelendokCompCurveCombo()
{
	int index;
	index = m_compCurveCombo.GetCurSel();
	if (index >= 0 && index != CB_ERR)
	{
		CString selStr;
		m_compCurveCombo.GetLBText(index, selStr);
		drawChart(&m_chartView);
	}
}
