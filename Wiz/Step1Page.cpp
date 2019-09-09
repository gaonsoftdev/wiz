// Step1Page.cpp : implementation file
//

#include "stdafx.h"
#include "Step1Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep1Page dialog


CStep1Page::CStep1Page(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CStep1Page::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStep1Page)
	//}}AFX_DATA_INIT
}


void CStep1Page::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep1Page)
	DDX_Control(pDX, ST_CAPTION, m_CaptionCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep1Page, CNewWizPage)
	//{{AFX_MSG_MAP(CStep1Page)
	//}}AFX_MSG_MAP
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep1Page message handlers

BOOL CStep1Page::OnInitDialog()
{
	CNewWizPage::OnInitDialog();

	m_Font.CreateFont(-16, 0, 0, 0,
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	m_CaptionCtrl.SetFont(&m_Font, TRUE);

	// Initialize.
	m_shapeChart.SetParent(this);
	m_shapeChart.SetWindow(GetDlgItem(IDC_MAP_PC));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CStep1Page::OnWizardNext()
{
	// check the import data.
	//if (!GetDataStore()->m_bOpenSHP) {
	//	AfxMessageBox(_T("There is not a shape file."));
	//	return -1;
	//}
	return 0;
}

void CStep1Page::OnSetActive()
{
	m_pParent->SetTitle(_T("노후 도로시설 내진성능관리 의사결정시스템"));

	// Get page window size.
	GetClientRect(&m_pageRect);

	// Resize other windows for page window size.
	GetDlgItem(IDC_MAP_PC)->MoveWindow(
		DEFAULT_PADDING
		, m_pageRect.bottom - (m_pageRect.bottom * 0.9)
		, m_pageRect.Width() - DEFAULT_PADDING * 2
		, (m_pageRect.bottom * 0.9) - DEFAULT_PADDING
	);
	CRect rect;
	GetDlgItem(IDC_MAP_PC)->GetWindowRect(rect);
	ScreenToClient(rect);
	
	// Draw chart, if there is a shape data.
	if (GetDataStore()->m_bOpenSHP) {
		m_shapeChart.SetShape(&GetDataStore()->m_SHP);
		m_shapeChart.Draw();
	}
}


BOOL CStep1Page::OnKillActive()
{
	return TRUE;
}


void CStep1Page::OnDraw(CDC* pDC)
{
}

void CStep1Page::OnWizardImport()
{
	CString filename;
	CFileDlgUtil::GetShapeFile(filename);
	if (filename.IsEmpty()) {
		return;
	}

	// 파일이 이미 열려있으면 닫는다.
	if (GetDataStore()->m_bOpenSHP)
		GetDataStore()->m_SHP.Close();

	if (!GetDataStore()->m_SHP.Open(filename))
		return;

	GetDataStore()->m_bOpenSHP = true;

	////////////////////////////////////////////
	//filename = _T("C:\\sample\\defcomp.xlsx");
	//CXLEzAutomation XL(FALSE); // FALSE: 처리 과정을 화면에 보이지 않는다
	//XL.OpenExcelFile(filename); // 액셀 파일 열기
	//int row = 1;
	//int col = 1;

	//CStringArray valueArray;
	//while (XL.GetCellValue(col, row) != _T("")) {
	//	while (XL.GetCellValue(col, row) != _T("")) {
	//		valueArray.Add(XL.GetCellValue(col, row));
	//		col++;
	//	}
	//	col = 1;
	//	row++;
	//}
	//XL.ReleaseExcel(); // 엑셀 파일 해제
	//GetDataStore()->m_networkCompClsData.SetData(row - 1, 8, &valueArray);
	//GetDataStore()->m_networkCompClsData.SetDataFilename(filename);
	//if (GetDataStore()->m_bOpenSHP) {
	//	int count = GetDataStore()->m_networkCompClsData.GetDataRow();
	//	NetworkComponent* networkComps = new NetworkComponent[count];
	//	for (int i = 0; i < count; i++)
	//	{
	//		networkComps[i].m_ID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][0]);
	//		networkComps[i].m_classID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][1]);
	//		networkComps[i].m_X = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][2]);
	//		networkComps[i].m_Y = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][3]);
	//		networkComps[i].m_linkID = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][4]);
	//		networkComps[i].m_reconstCost = _ttoi(GetDataStore()->m_networkCompClsData.GetData()[i][5]);
	//		networkComps[i].m_soilType = LPSTR(LPCTSTR(GetDataStore()->m_networkCompClsData.GetData()[i][6]));
	//		networkComps[i].m_fundPeriod = _ttof(GetDataStore()->m_networkCompClsData.GetData()[i][7]);
	//	}
	//	m_shapeChart.DrawWithNetworkComponents(&GetDataStore()->m_SHP, networkComps, count);
	//	delete[] networkComps;
	//}
	////////////////////////////////////////////
	
	m_shapeChart.SetShape(&GetDataStore()->m_SHP);
	m_shapeChart.Draw();
}

void CStep1Page::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	CPoint p;
	GetCursorPos(&p);
	CPoint p1;
	GetCursorPos(&p1);
	ScreenToClient(&p1);
	str.Format(_T("x=%d, y=%d\nx=%d, y=%d"), p.x, p.y, p1.x, p1.y);
	AfxMessageBox(str);

	CNewWizPage::OnRButtonUp(nFlags, point);
}


void CStep1Page::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CNewWizPage::OnPaint()을(를) 호출하지 마십시오.
	m_shapeChart.Draw();
}
