// Step5Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step5Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep5Page dialog


CStep5Page::CStep5Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep5Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep5Page)
	//}}AFX_DATA_INIT
}


CStep5Page::~CStep5Page()
{
}


void CStep5Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep5Page)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SEISMIC_SRC_LIST, m_seismicSrcList);
	DDX_Control(pDX, IDC_ADD_SRC_BTN, m_addSeismicSrcBtn);
	DDX_Control(pDX, IDC_DEL_SRC_BTN, m_delSeismicSrcBtn);
	DDX_Control(pDX, ST_SEISMIC_SRC_CAP, m_seismicSrcCap);
	DDX_Control(pDX, IDC_INTENSITY_COMBO, m_intensityCombo);
	DDX_Control(pDX, ST_INTENSITY_CAP, m_intensityCap);
	DDX_Control(pDX, IDC_RECURR_PERIOD_LIST, m_recurrencePeriodList);
	DDX_Control(pDX, IDC_RECURR_PERIOD_CAP, m_recurrencePeriodCap);
}


BEGIN_MESSAGE_MAP(CStep5Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep5Page)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADD_SRC_BTN, &CStep5Page::OnBnClickedAddSrcBtn)
	ON_BN_CLICKED(IDC_DEL_SRC_BTN, &CStep5Page::OnBnClickedDelSrcBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep5Page message handlers

BOOL CStep5Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	// Initialize.
	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_shapeChart.SetParent(this);
	m_shapeChart.SetWindow(GetDlgItem(IDC_MAP_PC));

	m_seismicSrcList.SetExtendedStyle(LVS_EX_FULLROWSELECT); // Set select one row
	m_seismicSrcList.InsertColumn(0, _T("Seq"), LVCFMT_LEFT);
	m_seismicSrcList.InsertColumn(1, _T("Seismic sources"), LVCFMT_LEFT);

	m_recurrencePeriodList.SetExtendedStyle(LVS_EX_FULLROWSELECT); // Set select one row
	m_recurrencePeriodList.InsertColumn(0, _T("Seq"), LVCFMT_LEFT);
	m_recurrencePeriodList.InsertColumn(1, _T("Recurrence period"), LVCFMT_LEFT);
	for (int i = 0; i < 4; i++)
	{
		CString str;
		str.Format(_T("%d"), i + 1);
		m_recurrencePeriodList.InsertItem(i, str);
		if (i == 0)
		{
			m_recurrencePeriodList.SetItemText(i, 1, _T("50"));
		}
		else if (i == 1)
		{
			m_recurrencePeriodList.SetItemText(i, 1, _T("100"));
		}
		else if (i == 2)
		{
			m_recurrencePeriodList.SetItemText(i, 1, _T("475"));
		}
		else if (i == 3)
		{
			m_recurrencePeriodList.SetItemText(i, 1, _T("1000"));
		}
	}

	m_intensityCombo.AddString(_T("Sa"));
	m_intensityCombo.AddString(_T("PGA"));
	m_intensityCombo.SetCurSel(0);

	//CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep5Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_fragCurveParamData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}

void CStep5Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);

	// Resize other windows for page window size.
	CString str = _T("");
	CRect rect;
	m_seismicSrcCap.SetFont(&m_Font, TRUE);
	m_seismicSrcCap.GetWindowText(str);
	CSize* size = &GetDC()->GetTextExtent(str);
	m_seismicSrcCap.MoveWindow(
		DEFAULT_PADDING
		, DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, size->cy + DEFAULT_PADDING
	); 
	m_seismicSrcCap.GetWindowRect(&rect);
	ScreenToClient(rect);

	m_seismicSrcList.MoveWindow(
		DEFAULT_PADDING
		, rect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, m_pageRect.Height() * 0.2
	);
	m_seismicSrcList.GetWindowRect(&rect);
	ScreenToClient(rect);
	m_seismicSrcList.SetColumnWidth(0, 50);
	m_seismicSrcList.SetColumnWidth(1, rect.Width() - m_seismicSrcList.GetColumnWidth(0));

	int height = m_pageRect.Height() * 0.25;
	GetDlgItem(IDC_MAP_PC)->MoveWindow(
		rect.right + DEFAULT_PADDING
		, rect.top
		, m_pageRect.right - rect.right - DEFAULT_PADDING * 2
		, m_pageRect.bottom - rect.top - DEFAULT_PADDING
	);

	GetDlgItem(IDC_MAP_PC)->ShowWindow(TRUE);

	int minButtonHeight = 30;
	height = rect.Height() * 0.1;
	if (minButtonHeight > height)
		height = minButtonHeight;
	m_addSeismicSrcBtn.MoveWindow(
		rect.left
		, rect.bottom
		, (rect.Width() - DEFAULT_PADDING) / 2
		, height
	);
	m_addSeismicSrcBtn.GetWindowRect(&rect);
	ScreenToClient(rect);

	m_delSeismicSrcBtn.MoveWindow(
		rect.right + DEFAULT_PADDING
		, rect.top
		, rect.Width()
		, rect.Height()
	); 

	m_recurrencePeriodCap.SetFont(&m_Font, TRUE);
	m_recurrencePeriodCap.GetWindowText(str);
	size = &GetDC()->GetTextExtent(str);
	m_recurrencePeriodCap.MoveWindow(
		DEFAULT_PADDING
		, rect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, size->cy + DEFAULT_PADDING
	);
	m_recurrencePeriodCap.GetWindowRect(&rect);
	ScreenToClient(rect);

	m_recurrencePeriodList.MoveWindow(
		DEFAULT_PADDING
		, rect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, m_pageRect.Height() * 0.2
	);
	m_recurrencePeriodList.GetWindowRect(&rect);
	ScreenToClient(rect);
	m_recurrencePeriodList.SetColumnWidth(0, 50);
	m_recurrencePeriodList.SetColumnWidth(1, rect.Width() - m_recurrencePeriodList.GetColumnWidth(0));

	m_intensityCap.SetFont(&m_Font, TRUE);
	m_intensityCap.GetWindowText(str);
	size = &GetDC()->GetTextExtent(str);
	m_intensityCap.MoveWindow(
		DEFAULT_PADDING
		, rect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, size->cy + DEFAULT_PADDING
	);
	m_intensityCap.GetWindowRect(&rect);
	ScreenToClient(rect);

	m_intensityCombo.MoveWindow(
		DEFAULT_PADDING
		, rect.bottom + DEFAULT_PADDING
		, m_pageRect.Width() * 0.2
		, m_pageRect.Height() * 0.2
	);

	// Set shape data, if there is a data.
	if (GetDataStore()->m_bOpenSHP) {
		m_shapeChart.SetShape(&GetDataStore()->m_SHP);
		m_shapeChart.Draw();
	}
}


BOOL CStep5Page::OnKillActive()
{
	return TRUE;
}


void CStep5Page::OnDraw(CDC* pDC)
{
}


void CStep5Page::OnWizardImport()
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

	//CStringArray columns;
	//columns.Add(_T("X"));
	//columns.Add(_T("Y"));
	//columns.Add(_T("data1"));
	//columns.Add(_T("data2"));
	//columns.Add(_T("data3"));
	//columns.Add(_T("data4"));

	//CUserGridData gridData;
	//gridData.SetData(row - 1, columns.GetCount(), &valueArray);
	//gridData.SetDataFilename(filename);
	//GetDataStore()->m_seismicSourcesArr.Add(gridData);
}


void CStep5Page::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CNewWizPage::OnPaint()을(를) 호출하지 마십시오.
	m_shapeChart.Draw();
}


void CStep5Page::OnBnClickedAddSrcBtn()
{
	CString filename;
	CFileDlgUtil::GetExcelFile(filename);
	if (filename.IsEmpty()) {
		return;
	}
	//filename = _T("C:\\sample\\kozani_fault.xlsx"); // test code
	CXLEzAutomation XL(FALSE); // FALSE: 처리 과정을 화면에 보이지 않는다
	XL.OpenExcelFile(filename); // 액셀 파일 열기
	int row = 1;
	int col = 1;
	int maxCol = 0;

	CStringArray valueArray;
	while (XL.GetCellValue(col, row) != _T("")) {
		while (XL.GetCellValue(col, row) != _T("")) {
			valueArray.Add(XL.GetCellValue(col, row));
			col++;
		}
		if (maxCol < col) maxCol = col - 1;
		col = 1;
		row++;
	}
	XL.ReleaseExcel(); // 엑셀 파일 해제

	CStringArray columns;
	columns.Add(_T("X"));
	columns.Add(_T("Y"));
	columns.Add(_T("data1"));
	columns.Add(_T("data2"));
	columns.Add(_T("data3"));
	columns.Add(_T("data4"));

	if (columns.GetCount() != maxCol) {
		AfxMessageBox(_T("파일 형식 또는 데이터가 잘못되었습니다."));
		return;
	}

	CUserGridData gridData;
	gridData.SetData(row - 1, maxCol, valueArray);
	gridData.SetColumnHeaders(columns);
	gridData.SetDataFilename(filename);

	// Add seismic source list
	int listCount = m_seismicSrcList.GetItemCount();
	CString str;
	str.Format(_T("%d"), listCount + 1);
	m_seismicSrcList.InsertItem(listCount, str);
	m_seismicSrcList.SetItemText(listCount, 1, filename);

	//GetDataStore()->m_seismicSourcesArr.Put(gridData);
	//TRACE("\n%s\n", GetDataStore()->m_seismicSourcesArr.Get(listCount).GetDataFilename());
	GetDataStore()->m_seismicSourcesArr.Add(gridData);
	TRACE("\n %s \n", GetDataStore()->m_seismicSourcesArr.GetAt(listCount).GetDataFilename());
}


void CStep5Page::OnBnClickedDelSrcBtn()
{
	int count = m_seismicSrcList.GetItemCount();

	for (int i = count; i >= 0; i--)
	{
		if (m_seismicSrcList.GetItemState(i, LVIS_SELECTED) != 0)
		{
			m_seismicSrcList.DeleteItem(i);
			// Redraw seq
			for (int j = i; j < count; j++)
			{
				CString str;
				str.Format(_T("%d"), j + 1);
				m_seismicSrcList.SetItemText(j, 0, str);
			}
		}
	}
}
