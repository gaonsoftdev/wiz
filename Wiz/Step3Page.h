#if !defined(AFX_Step3Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_Step3Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1Page.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CStep3Page dialog

class CStep3Page : public CNewWizPage
{
	// Construction
public:
	CStep3Page(CWnd* pParent = NULL);   // standard constructor
	~CStep3Page();
	// Dialog Data
		//{{AFX_DATA(CStep3Page)
	enum { IDD = IDW_STEP3 };
	CStatic					m_CaptionCtrl;
	//}}AFX_DATA
	CRect					m_pageRect;
	CFont					m_Font;

	bool					m_startToMove;
	CPoint					m_startPos, m_endPos;

	ShapeChart				m_shapeChart;
	CRect					m_compClassGridRect;
	CGridCtrl				m_compClassGrid;
	CRect					m_networkCompGridRect;
	CGridCtrl				m_networkCompGrid;
	NetworkComponent*		m_networkComps;
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStep3Page)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void DrawCompClassGrid();
	void DrawNetworkCompGrid();
// Implementation
protected:
	LRESULT OnWizardNext();
	void OnSetActive();
	BOOL OnKillActive();
	
	// Generated message map functions
	//{{AFX_MSG(CStep3Page)
	virtual BOOL OnInitDialog();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImportBtn();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Step3Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
