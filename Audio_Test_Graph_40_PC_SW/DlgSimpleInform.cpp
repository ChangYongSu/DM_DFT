// DlgSimpleInform.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgSimpleInform.h"
#include "afxdialogex.h"


// CDlgSimpleInform ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgSimpleInform, CDialogEx)

CDlgSimpleInform::CDlgSimpleInform(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSimpleInform::IDD, pParent)
{

}

CDlgSimpleInform::~CDlgSimpleInform()
{
}

void CDlgSimpleInform::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_DISPLAY, m_cLabelInformDisplay);
}


BEGIN_MESSAGE_MAP(CDlgSimpleInform, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDCANCEL, &CDlgSimpleInform::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgSimpleInform::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgSimpleInform::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if(pMsg->wParam == VK_RETURN)
		{
			
			return TRUE;
		}
	}		
	else if(pMsg->message == WM_CHAR)
	{
		char lCharInput =  (char)(pMsg->wParam);
		if(lCharInput == '1')
		{
			ShowWindow(SW_HIDE);
			KillTimer(1);
			m_Close_Result = _CLOSE_DISPLAY_OKCLICK;
			return TRUE;	
		}
		else if(lCharInput == '3')
		{
			ShowWindow(SW_HIDE);
			KillTimer(1);
			m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;	
			return TRUE;	
		}
		
	}	
	
	
	
	return CDialog::PreTranslateMessage(pMsg);
}

// CDlgSimpleInform �޽��� ó�����Դϴ�.


BOOL CDlgSimpleInform::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	  m_Count = 0;
//	m_EditLEDPortString.Format(_T("%d"),m_nPortLED );

	SetTimer(1, 100, NULL);
	




	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgSimpleInform::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//static int m_Count = 0;
	m_Count -= 100;
	if(m_Count < 0)
	{
		ShowWindow(SW_HIDE);
		KillTimer(1);
		m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDlgSimpleInform::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_Close_Result =  _OPEN_DISPLAY_;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(bShow)
		SetTimer(1, 100, NULL);
	m_cLabelInformDisplay.put_Caption(m_DisplayString);
	 //m_Count = 0;

	//if(m_Count > 60000)
	//{
	//	m_Count = 60000;
	//}

}


void CDlgSimpleInform::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_Close_Result =  _CLOSE_DISPLAY_CANCELCLICK;

	CDialogEx::OnCancel();
}


void CDlgSimpleInform::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Close_Result =  _CLOSE_DISPLAY_OKCLICK;
	CDialogEx::OnOK();
}
