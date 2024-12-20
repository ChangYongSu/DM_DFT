// UserMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "UserMsgDlg.h"
#include "afxdialogex.h"
#include "AcqVoltageSamples_IntClkDlg.h"



// CUserMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUserMsgDlg, CDialog)

CUserMsgDlg::CUserMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMsgDlg::IDD, pParent)
{

}

CUserMsgDlg::~CUserMsgDlg()
{
}

void CUserMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserMsgDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_YES, &CUserMsgDlg::OnBnClickedBtnYes)
	ON_BN_CLICKED(IDC_BTN_NO, &CUserMsgDlg::OnBnClickedBtnNo)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUserMsgDlg 메시지 처리기입니다.

void CUserMsgDlg::ShowMessage1(CString szMessage)
{
	//m_ctrlMsg1.SetCaption(szMessage);
	//m_ctrlMsg1.SetWindowText(szMessage);
	//m_ctrlMsg1.Invalidate();
	//m_ctrlMsg1.UpdateWindow();
	SetDlgItemText(IDC_STATIC_MESSAGE1, szMessage);
}

void CUserMsgDlg::ShowMessage2(CString szMessage)
{
	SetDlgItemText(IDC_STATIC_MESSAGE2, szMessage);

	//m_ctrlMsg2.SetWindowText(szMessage);
	//m_ctrlMsg2.Invalidate();
	//m_ctrlMsg2.UpdateWindow();
}

void CUserMsgDlg::SetMessage(CString szMessage1, CString szMessage2)
{
	m_szMsg1 = szMessage1;
	m_szMsg2 = szMessage2;
	m_DelayTime = 100000;
	
}

void CUserMsgDlg::SetMessageTime(CString szMessage1, CString szMessage2, int lDely)
{
	m_szMsg1 = szMessage1;
	m_szMsg2 = szMessage2;
	m_DelayTime = lDely;
	
		
}

void CUserMsgDlg::OnBnClickedBtnYes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bYes	= TRUE;
	m_Close_Result = _CLOSE_DISPLAY_OKCLICK;


	//+ add 090902
	m_bActivate = FALSE;
	//-
	m_bShowOkButton = 1;
	OnOK();
}


void CUserMsgDlg::OnBnClickedBtnNo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_bYes	= FALSE;

	//+ add 090902
	m_bActivate = FALSE;
	//-
	m_bShowOkButton = 1;
	OnOK();
}


void CUserMsgDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(bShow)
	{
		// TODO: Add extra initialization here
		
		ShowMessage1(m_szMsg1);
		ShowMessage2(m_szMsg2);
		SetTimer(1, m_DelayTime, NULL);
	
		//+add kwmoon 080508
		m_bYes	= TRUE;
	
		GetDlgItem(IDC_BTN_YES)->ShowWindow(m_bShowOkButton);

	
		//+ add 090902
		m_bActivate = TRUE;
	}
	else
	{
		m_bActivate = FALSE;
	}
}


void CUserMsgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bShowOkButton = 1;
	m_bActivate = FALSE;
	OnOK();
	CDialog::OnTimer(nIDEvent);
}
