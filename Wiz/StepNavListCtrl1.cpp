// StepNavListCtrl.cpp: 구현 파일
//

#include "stdafx.h"
#include "Wiz.h"
#include "StepNavListCtrl.h"


// StepNavListCtrl

IMPLEMENT_DYNAMIC(StepNavListCtrl, CListCtrl)

StepNavListCtrl::StepNavListCtrl()
{

}

StepNavListCtrl::~StepNavListCtrl()
{
}


BEGIN_MESSAGE_MAP(StepNavListCtrl, CListCtrl)
END_MESSAGE_MAP()



// StepNavListCtrl 메시지 처리기




void StepNavListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	LV_ITEM item_data;
	TCHAR buffer[256];

	LV_COLUMN column_data, prev_column_data;
	memset(&column_data, 0, sizeof(LV_COLUMN));
	memset(&prev_column_data, 0, sizeof(LV_COLUMN));

	column_data.mask = LVCF_WIDTH | LVCF_FMT;
	prev_column_data.mask = LVCF_WIDTH | LVCF_FMT;

	// 컬럼의 개수만큼 for문을 돌면서 컬럼 정보를 얻는다.
	for (int column_index = 0; GetColumn(column_index, &column_data); column_index++) {
		if (column_index > 0) {
			// 헤더 컬럼의 위치 변경에 따라 텍스트를 출력하기 위하여 출력 영역을 보정하여 준다.
			GetColumn(column_index - 1, &prev_column_data);
			lpDrawItemStruct->rcItem.left += prev_column_data.cx;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left;
		}

		// 해당 컬럼의 셀 정보를 얻어 온다.
		item_data.mask = LVIF_TEXT | LVIF_PARAM;
		item_data.iItem = lpDrawItemStruct->itemID;
		item_data.iSubItem = column_index;
		item_data.pszText = buffer;
		item_data.cchTextMax = sizeof(buffer);
		VERIFY(GetItem(&item_data));

		CDC* pDC;
		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		//ID *p_data = (ID *)lpDrawItemStruct->itemData;

		//// 메일 확인 여부에 따라 폰트 굵기를 다르게 한다.
		//if (p_data->read_flag) pDC->SelectObject(&g_default_font);
		//else pDC->SelectObject(&g_bold_font);

		//// 선택된 인덱스에는 배경색을 칠한다.
		//if (lpDrawItemStruct->itemState & ODS_SELECTED)
		//	pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT));
		//else pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));

		//// 컬럼의 위치에 따라 데이터를 출력하여 준다.
		//pDC->SetTextColor(RGB(0, 0, 0));
		//if (column_index == 0) {
		//	pDC->SetTextColor(RGB(34, 118, 135));
		//	pDC->DrawText(buffer, strlen(buffer), &lpDrawItemStruct->rcItem, DT_LEFT);
		//}
		//else if (column_index == 1) pDC->DrawText(buffer, strlen(buffer),
		//	&lpDrawItemStruct->rcItem, DT_LEFT);
		//else if (column_index == 2) {
		//	if (p_data->read_flag) pDC->DrawText(item_data.pszText, strlen(item_data.pszText),
		//		&lpDrawItemStruct->rcItem, DT_LEFT);
		//}
	}
}
