#if !defined(AFX_Step1Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_Step1Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1Page.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CStep1Page dialog

class CStep1Page : public CNewWizPage
{
	// Construction
public:
	CStep1Page(CWnd* pParent = NULL);   // standard constructor


	// Dialog Data
		//{{AFX_DATA(CStep1Page)
	enum { IDD = IDW_STEP1 };
	CStatic			m_CaptionCtrl;
	//}}AFX_DATA
	CRect			m_pageRect;
	CFont			m_Font;
	ShapeChart		m_shapeChart;
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStep1Page)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LRESULT OnWizardNext();
	void OnSetActive();
	BOOL OnKillActive();

	// Generated message map functions
	//{{AFX_MSG(CStep1Page)
	virtual BOOL OnInitDialog();
	virtual void OnWizardImport();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Step1Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
