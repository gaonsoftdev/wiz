#if !defined(AFX_Step5Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_Step5Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step1Page.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CStep5Page dialog

class CStep5Page : public CNewWizPage
{
	// Construction
public:
	CStep5Page(CWnd* pParent = NULL);   // standard constructor
	~CStep5Page();
	// Dialog Data
		//{{AFX_DATA(CStep5Page)
	enum { IDD = IDW_STEP5 };
	//}}AFX_DATA
	CRect					m_pageRect;
	CFont					m_Font;

	ShapeChart				m_shapeChart;
	// IDC_COMP_CURVE_COMBO
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStep5Page)
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
	//{{AFX_MSG(CStep5Page)
	virtual BOOL OnInitDialog();
	virtual void OnWizardImport();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	// Seismic source list component
	CStatic			m_seismicSrcCap;
	CStatic			m_intensityCap;
	CStatic			m_recurrencePeriodCap;
	CButton			m_addSeismicSrcBtn;
	CButton			m_delSeismicSrcBtn;
	CComboBox		m_intensityCombo;
	CListCtrl		m_seismicSrcList;
	CListCtrl		m_recurrencePeriodList;
public:
	afx_msg void OnBnClickedAddSrcBtn();
	afx_msg void OnBnClickedDelSrcBtn();
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Step5Page_H__C7A07F0E_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
