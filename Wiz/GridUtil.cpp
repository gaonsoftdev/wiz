#include "stdafx.h"
#include "GridUtil.h"

CGridUtil::CGridUtil()
{
}


CGridUtil::~CGridUtil()
{
}

void CGridUtil::Init(CGridCtrl* grid, const CStringArray& headers)
{
	grid->SetEditable(TRUE);
	grid->SetListMode(TRUE);
	grid->EnableDragAndDrop(TRUE);
	grid->SetTextBkColor(RGB(0xFF, 0xFF, 0xFF));
	grid->EnableScrollBar(ESB_ENABLE_BOTH, TRUE);
	grid->SetRowCount(1);
	grid->SetColumnCount(headers.GetSize() + 1);
	grid->SetFixedRowCount(1);
	grid->SetFixedColumnCount(0);

	// fill rows/cols with text
	for (int col = 0; col < grid->GetColumnCount(); col++) {
		GV_ITEM Item;
		Item.mask = GVIF_TEXT | GVIF_FORMAT;
		Item.row = 0;
		Item.col = col;
		Item.nFormat = DT_CENTER | DT_WORDBREAK;
		if (col == 0) {
			Item.strText = "";
		}
		else {
			Item.strText = headers.GetAt(col - 1);
		}
		grid->SetItem(&Item);
	}
	grid->AutoSize();
}

void CGridUtil::Draw(CGridCtrl* grid, CUserGridData gridData)
{
	int m_nFixRows = 1;
	int m_nFixCols = 1;
	bool IsShowColumnHeader = true;
	if (gridData.GetColumnHeaders().IsEmpty()) {
		IsShowColumnHeader = false;
	}
	grid->SetEditable(TRUE);
	grid->SetListMode(TRUE);
	grid->EnableDragAndDrop(TRUE);
	grid->SetTextBkColor(RGB(0xFF, 0xFF, 0xFF));
	grid->EnableScrollBar(ESB_ENABLE_BOTH, TRUE);
	grid->SetRowCount(gridData.GetDataRow() + 1);
	grid->SetColumnCount(gridData.GetDataCol() + 1);
	grid->SetFixedRowCount(m_nFixRows);
	grid->SetFixedColumnCount(m_nFixCols);

	// fill rows/cols with text
	for (int row = 0; row < grid->GetRowCount(); row++) {
		for (int col = 0; col < grid->GetColumnCount(); col++) {
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			if (row < m_nFixRows) { // 첫 row는 column 헤더
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				if (col == 0) {
					Item.strText = "";
				}
				else {
					Item.strText = gridData.GetColumnHeaders().GetAt(col - 1);
				}
			}
			else if (col < m_nFixCols) {
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
				Item.strText.Format(_T("%d"), row);
			}
			else {
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
				Item.strText.Format(_T("%s"), gridData.GetData()[row - 1][col - 1]);
			}
			grid->SetItem(&Item);
		}
	}
	// Make cell 1,1 read-only
	grid->SetItemState(m_nFixRows, m_nFixCols, grid->GetItemState(m_nFixRows, m_nFixCols) | GVIS_READONLY);
	grid->AutoSize();
	grid->SetRowHeight(0, 3 * grid->GetRowHeight(0) / 2);
}

void CGridUtil::AutoFillColumns(CGridCtrl* grid, CRect* rect)
{
	int col = grid->GetColumnCount();

	float* arr = new float[col];
	float totalWidth = 0.0;
	for (int i = 0; i < col; i++)
	{
		arr[i] = grid->GetColumnWidth(i);
		if (i != 0) {
			// 제일 앞은 고정 column 이므로 전체 width에서 제외
			totalWidth += arr[i];
		}
	}
	int changedWidth = 0;
	int changedTotalWidth = 0;
	for (int i = 1; i < col; i++)
	{
		changedWidth = rect->Width() / (totalWidth / arr[i]);
		changedTotalWidth += changedWidth;
		grid->SetColumnWidth(i, changedWidth);
	}
	// 최대 크기를 넘지 않도록 보정(스크롤 안생기게 하기위해 강제 조정)
	if (rect->Width() - arr[0] < changedTotalWidth)
	{
		grid->SetColumnWidth(col - 1, rect->Width() - arr[0] - (changedTotalWidth - changedWidth) - 10);
	}

	delete[] arr;
}

void CGridUtil::FillColumns(CGridCtrl* grid, CRect* rect, int* ratio, int size)
{
	int col = grid->GetColumnCount();
	for (int i = 1; i < col; i++)
	{
		if (i <= size) {
			grid->SetColumnWidth(i, ratio[i - 1]);
		}
		else {
			grid->SetColumnWidth(i, 1);
		}
	}
	AutoFillColumns(grid, rect);
}