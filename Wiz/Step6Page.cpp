// Step6Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step6Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep6Page dialog


CStep6Page::CStep6Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep6Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep6Page)
	//}}AFX_DATA_INIT
}

CStep6Page::~CStep6Page()
{
}

void CStep6Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep6Page)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep6Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep6Page)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep6Page message handlers

BOOL CStep6Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	//CheckRadioButton(RB_ACCEPT, RB_DECLINE, RB_DECLINE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep6Page::OnWizardNext()
{
	// check the import data.
	/*if (!GetDataStore()->m_fragCurveParamData.IsRead()) {
		AfxMessageBox(_T("입력된 데이터가 없습니다."));
		return -1;
	}*/
	return 0;
}

void CStep6Page::OnSetActive()
{
	// Get page window size.
	GetClientRect(&m_pageRect);

}

BOOL CStep6Page::OnKillActive()
{
	return TRUE;
}

void CStep6Page::OnDraw(CDC* pDC)
{
}

void CStep6Page::OnWizardImport()
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
