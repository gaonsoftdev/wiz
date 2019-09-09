// Step2Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step2Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep2Page dialog


CStep2Page::CStep2Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep2Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep2Page)
	//}}AFX_DATA_INIT
}


void CStep2Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep2Page)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	DDX_Control(pDX, IDC_INPUT_GRID, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep2Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep2Page)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep2Page message handlers

BOOL CStep2Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep2Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_compClsData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}


void CStep2Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);

	// Resize other windows for page window size.
	int gridWidth = m_pageRect.Width() * 0.7;
	int gridHeight = m_pageRect.Height() * 0.25;
	GetDlgItem(IDC_INPUT_GRID)->MoveWindow(
		DEFAULT_PADDING
		, m_pageRect.Height() * 0.1
		, gridWidth
		, gridHeight
	);

	// Initialize grid.
	if (GetDataStore()->m_compClsData.GetColumnHeaders().IsEmpty()) {
		CStringArray columns;
		columns.Add(_T("Class"));
		columns.Add(_T("Description"));
		GetDataStore()->m_compClsData.SetColumnHeaders(columns);
		CGridUtil::Init(&m_Grid, columns);
		CRect gridRect;
		GetDlgItem(IDC_INPUT_GRID)->GetWindowRect(&gridRect);
		CGridUtil::AutoFillColumns(&m_Grid, &gridRect);
	}

	// Fill data to grid, if there is a data.
	if (GetDataStore()->m_compClsData.IsRead()) {
		DrawGrid();
	}
}


BOOL CStep2Page::OnKillActive()
{
	return TRUE;
}


void CStep2Page::OnDraw(CDC* pDC)
{

}


void CStep2Page::OnWizardImport()
{
	CString filename;
	CFileDlgUtil::GetExcelFile(filename);
	if (filename.IsEmpty()) {
		return;
	}
	//filename = _T("C:\\sample\\defclas.xls"); // test code
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

	GetDataStore()->m_compClsData.SetData(row - 1, 2, valueArray);
	GetDataStore()->m_compClsData.SetDataFilename(filename);
	DrawGrid();
}


void CStep2Page::DrawGrid() 
{
	CGridUtil::Draw(&m_Grid, GetDataStore()->m_compClsData);
	for (int row = 1; row < m_Grid.GetRowCount(); row++) {
		for (int col = 1; col < m_Grid.GetColumnCount(); col++) {
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
			m_Grid.SetItem(&Item);
		}
	}
	CRect gridRect;
	GetDlgItem(IDC_INPUT_GRID)->GetWindowRect(&gridRect);
	int arr[2] = { 1, 3 };
	CGridUtil::FillColumns(&m_Grid, &gridRect, arr, 2);
	m_Grid.UpdateData(TRUE);
}