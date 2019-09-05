#pragma once
#include "stdafx.h"
#include "GridCtrl.h"
#include "UserGridData.h"

class CGridUtil
{
public:
	CGridUtil();
	~CGridUtil();

	static void Init(CGridCtrl* grid, CStringArray* gridData);
	static void Draw(CGridCtrl* grid, CUserGridData* gridData);
	static void AutoFillColumns(CGridCtrl* grid, CRect* rect);
	static void FillColumns(CGridCtrl* grid, CRect* rect, int* ratio, int size);
};

