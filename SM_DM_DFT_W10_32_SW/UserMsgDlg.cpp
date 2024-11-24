// UserMsgDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "UserMsgDlg.h"
#include "afxdialogex.h"
#include "AcqVoltageSamples_IntClkDlg.h"



// CUserMsgDlg ��ȭ �����Դϴ�.

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



// CUserMsgDlg �޽��� ó�����Դϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bShowOkButton = 1;
	m_bActivate = FALSE;
	OnOK();
	CDialog::OnTimer(nIDEvent);
}

BOOL CUserMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedBtnYes();
			return TRUE;
		}
	}
	/*else if (pMsg->message == WM_CHAR)
	{
		char lCharInput = (char)(pMsg->wParam);
		if (lCharInput == '1')
		{
			ShowWindow(SW_HIDE);
			KillTimer(1);
			m_Close_Result = _CLOSE_DISPLAY_OKCLICK;
			return TRUE;
		}
		else if (lCharInput == '3')
		{
			ShowWindow(SW_HIDE);
			KillTimer(1);
			m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;
			return TRUE;
		}

	}*/



	return CDialog::PreTranslateMessage(pMsg);
}
