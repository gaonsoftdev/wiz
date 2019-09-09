﻿
// Wiz.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"

#include "Step1Page.h"
#include "Step2Page.h"
#include "Step3Page.h"
#include "Step4Page.h"
#include "Step5Page.h"
#include "Step6Page.h"
#include "Step7Page.h"
#include "Step8Page.h"

#include "PrinterPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizApp

BEGIN_MESSAGE_MAP(CWizApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWizApp 생성

CWizApp::CWizApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	/*if (g_UserData != NULL) {
		g_UserData = new UserData();
	}*/
}


// 유일한 CWizApp 개체입니다.

CWizApp theApp;


// CWizApp 초기화

BOOL CWizApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	
	CWizDlg dlg;
	m_pMainWnd = &dlg;

	CStep1Page Step1Page;
	CStep2Page Step2Page;
	CStep3Page Step3Page;
	CStep4Page Step4Page;
	CStep5Page Step5Page;
	CStep6Page Step6Page;
	CStep7Page Step7Page;
	CStep8Page Step8Page;

	CPrinterPage PrinterPage;
	
	dlg.AddPage(&Step1Page, CStep1Page::IDD);
	dlg.AddStep(&Step1Page, _T("1 Definition of Road Network"));
	dlg.AddPage(&Step2Page, CStep2Page::IDD);
	dlg.AddStep(&Step2Page, _T("2 Definition network component classes"));
	dlg.AddPage(&Step3Page, CStep3Page::IDD);
	dlg.AddStep(&Step3Page, _T("3 Definition of network component properties"));
	dlg.AddPage(&Step4Page, CStep4Page::IDD);
	dlg.AddStep(&Step4Page, _T("4 Seismic Faragility of Network Components"));
	dlg.AddPage(&Step5Page, CStep5Page::IDD);
	dlg.AddStep(&Step5Page, _T("5 Seismic hazard"));
	dlg.AddPage(&Step6Page, CStep6Page::IDD);
	dlg.AddStep(&Step6Page, _T("6 Couple hazard to fragility"));
	dlg.AddPage(&Step7Page, CStep7Page::IDD);
	dlg.AddStep(&Step7Page, _T("7 Traffic carrying capacity - time and Repair Cost Ratio array"));
	dlg.AddPage(&Step8Page, CStep8Page::IDD);
	dlg.AddStep(&Step8Page, _T("8 Traffic scenarios"));
	dlg.AddPage(&PrinterPage, CPrinterPage::IDD);
	dlg.AddStep(&PrinterPage, _T("6 asdgfasdgasdg"));
	
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == ID_WIZFINISH)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

