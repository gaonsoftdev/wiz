#if !defined(AFX_Step4Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_Step4Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1Page.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CStep4Page dialog

class CStep4Page : public CNewWizPage
{
	// Construction
public:
	CStep4Page(CWnd* pParent = NULL);   // standard constructor
	~CStep4Page();
	// Dialog Data
		//{{AFX_DATA(CStep4Page)
	enum { IDD = IDW_STEP4 };
	CStatic					m_CaptionCtrl;
	//}}AFX_DATA
	CRect					m_pageRect;
	CFont					m_Font;

	CRect					m_fragCurveParamGridRect;
	CGridCtrl				m_fragCurveParamGrid;
	FragilityCurveParam*	m_fragCurveParams;

	CChartViewer			m_chartView;
	// IDC_COMP_CURVE_COMBO
	CComboBox				m_compCurveCombo;
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStep4Page)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void DrawFragCurveParamGrid();
	void drawChart(CChartViewer *viewer);
// Implementation
protected:
	LRESULT OnWizardNext();
	void OnSetActive();
	BOOL OnKillActive();
	
	// Generated message map functions
	//{{AFX_MSG(CStep4Page)
	virtual BOOL OnInitDialog();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImportBtn();
	afx_msg void OnPaint();
	afx_msg void OnCbnSelendokCompCurveCombo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Step4Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
