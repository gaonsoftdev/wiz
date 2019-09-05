
// WizDlg.h: 헤더 파일
//

#include "NewWizDialog.h"

#pragma once


// CWizDlg 대화 상자
class CWizDlg : public CNewWizDialog
{
	// 생성입니다.
public:
	CWizDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIZ_DIALOG };
	//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON			m_hIcon;

	CStringList		m_StepLabelList;
	CListCtrl*		m_pStepNavList; // step navigator
	CRect			m_prevNavItemRect;

	CButton*		m_pCancelButton;
	CButton*		m_pFinishButton;
	CButton*		m_pNextButton;
	CButton*		m_pBackButton;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual void DoneWizardBack(bool IsBack);
	virtual void DoneWizardNext(bool IsNext);
	DECLARE_MESSAGE_MAP()
public:
	void AddStep(CNewWizPage* pPage, CString label);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMCustomdrawStepNavList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
