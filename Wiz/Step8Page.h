#if !defined(AFX_Step8Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_Step8Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1Page.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CStep8Page dialog

class CStep8Page : public CNewWizPage
{
	// Construction
public:
	CStep8Page(CWnd* pParent = NULL);   // standard constructor
	~CStep8Page();
	// Dialog Data
		//{{AFX_DATA(CStep8Page)
	enum { IDD = IDW_STEP6 };
	//}}AFX_DATA
	CRect					m_pageRect;
	CFont					m_Font;

	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStep8Page)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	// Implementation
protected:
	LRESULT OnWizardNext();
	void OnSetActive();
	BOOL OnKillActive();

	// Generated message map functions
	//{{AFX_MSG(CStep8Page)
	virtual BOOL OnInitDialog();
	virtual void OnWizardImport();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Step8Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
