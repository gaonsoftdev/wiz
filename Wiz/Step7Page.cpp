// Step7Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step7Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep7Page dialog


CStep7Page::CStep7Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep7Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep7Page)
	//}}AFX_DATA_INIT
}

CStep7Page::~CStep7Page()
{
}

void CStep7Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep7Page)

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep7Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep7Page)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep7Page message handlers

BOOL CStep7Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));
	
	//CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep7Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_fragCurveParamData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}

void CStep7Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);
}

BOOL CStep7Page::OnKillActive()
{
	return TRUE;
}

void CStep7Page::OnDraw(CDC* pDC)
{
}

void CStep7Page::OnWizardImport()
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
}
