
// WizDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizDlg 대화 상자



CWizDlg::CWizDlg(CWnd* pParent /*=nullptr*/)
	: CNewWizDialog(CWizDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWizDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	/*DDX_Control(pDX, ID_WIZBACK, m_backButton);
	DDX_Control(pDX, ID_WIZNEXT, m_nextButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, ID_WIZFINISH, m_finishButton);
	DDX_Control(pDX, ID_WIZIMPORT, m_importButton);*/
}

BEGIN_MESSAGE_MAP(CWizDlg, CNewWizDialog)
	//ON_WM_PAINT()
	//ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_STEP_NAV_LIST, &CWizDlg::OnNMCustomdrawStepNavList)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CWizDlg 메시지 처리기
BOOL CWizDlg::OnInitDialog()
{
	m_pCancelButton = (CButton*)GetDlgItem(IDCANCEL);
	m_pFinishButton = (CButton*)GetDlgItem(ID_WIZFINISH);
	m_pNextButton = (CButton*)GetDlgItem(ID_WIZNEXT);
	m_pBackButton = (CButton*)GetDlgItem(ID_WIZBACK);
	m_pImportButton = (CButton*)GetDlgItem(ID_WIZIMPORT);
	m_pStepNavList = (CListCtrl*)GetDlgItem(IDC_STEP_NAV_LIST);
	m_pStepNavList->SetBkColor(RGB(243, 243, 243));
	CFont font;
	font.CreatePointFont(200, _T("굴림"));
	m_pStepNavList->SetFont(&font);

	ShowWindow(SW_SHOWMAXIMIZED);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetPlaceholderID(IDC_SHEETRECT);
			 
	CRect rect;
	m_pStepNavList->GetWindowRect(rect);
	m_pStepNavList->InsertColumn(0, _T("IS_SELECTED"), LVCFMT_LEFT, 0);
	m_pStepNavList->InsertColumn(1, _T("LABEL"), LVCFMT_LEFT, rect.Width());
	int cnt = m_StepLabelList.GetCount();
	for (; cnt >= 0; cnt--) {
		POSITION Pos = m_StepLabelList.FindIndex(cnt);
		if (Pos != NULL) {
			CString label;
			label = m_StepLabelList.GetAt(Pos);
			int nInsertedIndex = 0;
			if (cnt == 0) {
				nInsertedIndex = m_pStepNavList->InsertItem(0, _T("Y"));
			}
			else {
				nInsertedIndex = m_pStepNavList->InsertItem(0, _T("N"));
			}
			m_pStepNavList->SetItem(nInsertedIndex, 1, LVIF_TEXT, label, 0, 0, 0, NULL);
		}
	}
	CNewWizDialog::OnInitDialog();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWizDlg::AddStep(CNewWizPage* pPage, CString label) {
	int cnt = m_StepLabelList.GetCount();
	CString _label;
	_label.Format(label);
	m_StepLabelList.AddTail(_label);
}

void CWizDlg::OnSize(UINT nType, int cx, int cy)
{
	CNewWizDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// According to frame size resize components
	if (GetDlgItem(ID_WIZFINISH) != NULL) {
		CRect r, finishRect, cancelRect, nextRect, backRect, importRect;

		GetClientRect(r);

		int stepButtonHeight = r.bottom / 20;
		int stepButtonWidth = r.right / 10;
		int stepNavWidth = r.right / 8;

		// nav frame
		CRect navRect;
		m_pStepNavList->MoveWindow(
			r.left + DEFAULT_PADDING
			, r.top + DEFAULT_PADDING
			, stepNavWidth
			, r.bottom - (DEFAULT_PADDING * 3 + stepButtonHeight)
		);
		m_pStepNavList->GetWindowRect(&navRect);
		ScreenToClient(navRect);

		// content frame
		GetDlgItem(IDC_SHEETRECT)->MoveWindow(
			navRect.right
			, r.top + DEFAULT_PADDING
			, r.right - navRect.Width() - (DEFAULT_PADDING * 2)
			, r.bottom - (DEFAULT_PADDING * 3 + stepButtonHeight)
		);
		GetDlgItem(IDC_SHEETRECT)->GetWindowRect(&m_pageFrameRect);
		ScreenToClient(m_pageFrameRect);

		
		// Step buttons
		m_pCancelButton->MoveWindow(
			r.right - stepButtonWidth - DEFAULT_PADDING
			, r.bottom - stepButtonHeight - DEFAULT_PADDING
			, stepButtonWidth
			, stepButtonHeight
		);
		m_pCancelButton->GetWindowRect(&cancelRect);
		ScreenToClient(cancelRect);

		m_pFinishButton->MoveWindow(
			r.right - (r.right - cancelRect.left) - stepButtonWidth - DEFAULT_PADDING
			, r.bottom - stepButtonHeight - DEFAULT_PADDING
			, stepButtonWidth
			, stepButtonHeight
		);
		m_pFinishButton->GetWindowRect(&finishRect);
		ScreenToClient(finishRect);

		m_pNextButton->MoveWindow(
			r.right - (r.right - finishRect.left) - stepButtonWidth - DEFAULT_PADDING
			, r.bottom - stepButtonHeight - DEFAULT_PADDING
			, stepButtonWidth
			, stepButtonHeight
		);
		m_pNextButton->GetWindowRect(&nextRect);
		ScreenToClient(nextRect);
		
		m_pBackButton->MoveWindow(
			r.right - (r.right - nextRect.left) - stepButtonWidth - DEFAULT_PADDING
			, r.bottom - stepButtonHeight - DEFAULT_PADDING
			, stepButtonWidth
			, stepButtonHeight
		);
		m_pBackButton->GetWindowRect(&backRect);
		ScreenToClient(backRect);
		
		m_pImportButton->MoveWindow(
			m_pageFrameRect.left
			, r.bottom - stepButtonHeight - DEFAULT_PADDING
			, stepButtonWidth
			, stepButtonHeight
		);
		m_pImportButton->GetWindowRect(&importRect);
		ScreenToClient(importRect);
	}
}


void CWizDlg::OnNMCustomdrawStepNavList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	int iRow = (int)lplvcd->nmcd.dwItemSpec;

	switch (lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}

	// Modify item text and or background
	case CDDS_ITEMPREPAINT:
	{
		lplvcd->clrTextBk = RGB(243, 243, 243);
		// If you want the sub items the same as the item,
		// set *pResult to CDRF_NEWFONT
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}

	// Modify sub item text and/or background
	case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
	{
		if (iRow % 2) {
			lplvcd->clrText = RGB(0, 0, 255);
			// 홀수열의 배경색 재설정
			lplvcd->clrTextBk = RGB(255, 255, 255);
		}
		else {
			lplvcd->clrText = RGB(0, 255, 0);
			// 짝수열의 배경색 재설정
			lplvcd->clrTextBk = RGB(230, 230, 230);
		}

		*pResult = CDRF_DODEFAULT;
		return;
	}
	}
}


void CWizDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_STEP_NAV_LIST == nIDCtl) {
		LONG prevLeft = lpDrawItemStruct->rcItem.left;

		LV_COLUMN columnData, prevColumnData;
		memset(&columnData, 0, sizeof(LV_COLUMN));
		memset(&prevColumnData, 0, sizeof(LV_COLUMN));
		columnData.mask = LVCF_WIDTH | LVCF_FMT;
		prevColumnData.mask = LVCF_WIDTH | LVCF_FMT;

		LV_ITEM itemData;
		TCHAR buffer[256];
		
		// 컬럼의 개수만큼 for문을 돌면서 컬럼 정보를 얻는다.
		for (int columnIndex = 0; m_pStepNavList->GetColumn(columnIndex, &columnData); columnIndex++) {
			if (columnIndex > 0) {
				// 헤더 컬럼의 위치 변경에 따라 텍스트를 출력하기 위하여 출력 영역을 보정하여 준다.
				m_pStepNavList->GetColumn(columnIndex - 1, &prevColumnData);
				lpDrawItemStruct->rcItem.left += prevColumnData.cx;
				lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left;
			}

			// 컬럼 데이터를 가져온다.  
			itemData.mask = LVIF_TEXT | LVIF_PARAM;
			itemData.iItem = lpDrawItemStruct->itemID;
			itemData.iSubItem = columnIndex;
			itemData.pszText = buffer;
			itemData.cchTextMax = sizeof(buffer);
			m_pStepNavList->GetItem(&itemData);
			// DC를 확보한다. 모든지 할수 있다...이젠...  
			CString isSelected;
			CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
			{
				// 메모 : 컬럼별로 커스터마이징~  
				switch (columnIndex)
				{
				case 0:
					isSelected = (LPCTSTR)buffer;
					if (isSelected.CompareNoCase(_T("Y")) == 0) {
						pDC->SetTextColor(RGB(255, 0, 0));
					}
					else {
						pDC->SetTextColor(RGB(0, 0, 0));
					}
					break;
				case 1:
					// 이전 아이템의 위치정보에 따라 위치정보 조정
					//if (!m_prevNavItemRect.IsRectEmpty()) {
					//	lpDrawItemStruct->rcItem.top = m_prevNavItemRect.bottom;
					//	lpDrawItemStruct->rcItem.bottom = m_prevNavItemRect.Height();
					//}
					//if (lpDrawItemStruct->itemState & ODS_SELECTED) {
					//	pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT));
					//}
					//else {
					//	pDC->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(243, 243, 243));
					//}
					// 문자 길이에 따라 개행처리
					//int itemHeight = pDC->DrawText(buffer, wcslen(buffer), &lpDrawItemStruct->rcItem, DT_LEFT | DT_CALCRECT | DT_WORDBREAK);
					//if(itemHeight > lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) 
					//{
					//	lpDrawItemStruct->rcItem.bottom = lpDrawItemStruct->rcItem.top + itemHeight;
					//}
					// 다음를 그리기 위해 현재 아이템의 위치정보를 저장
					//m_prevNavItemRect = lpDrawItemStruct->rcItem;
					pDC->DrawText(buffer, wcslen(buffer), &lpDrawItemStruct->rcItem, DT_LEFT | DT_WORDBREAK);
					break;
				}
			}
		}
	}
	CNewWizDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CWizDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) {
	if (IDC_STEP_NAV_LIST == nIDCtl) {
		lpMeasureItemStruct->itemHeight = 40;
	}
	CNewWizDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CWizDlg::DoneWizardBack(bool IsBack) {
	if (IsBack) {
		int activeIndex = GetActiveIndex();
		m_pStepNavList->SetItem(activeIndex, 0, LVIF_TEXT, _T("Y"), 0, 0, 0, NULL);
		m_pStepNavList->SetItem(activeIndex + 1, 0, LVIF_TEXT, _T("N"), 0, 0, 0, NULL);
	}
}


void CWizDlg::DoneWizardNext(bool IsNext) {
	if (IsNext) {
		int activeIndex = GetActiveIndex();
		m_pStepNavList->SetItem(activeIndex, 0, LVIF_TEXT, _T("Y"), 0, 0, 0, NULL);
		m_pStepNavList->SetItem(activeIndex - 1, 0, LVIF_TEXT, _T("N"), 0, 0, 0, NULL);
	}
}


CRect CWizDlg::GetPageFrameRect()
{
	return m_pageFrameRect;
}


void CWizDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	int x, y;
	x = (int)GetSystemMetrics(SM_CXSCREEN);
	y = (int)GetSystemMetrics(SM_CYSCREEN);
	lpMMI->ptMinTrackSize = CPoint(x, y);
	lpMMI->ptMaxTrackSize = CPoint(x, y);

	CNewWizDialog::OnGetMinMaxInfo(lpMMI);
}
