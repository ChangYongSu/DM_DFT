// DlgMessage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgMessage.h"
#include "afxdialogex.h"


// CDlgMessage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgMessage, CDialogEx)

CDlgMessage::CDlgMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMessage::IDD, pParent)
	, m_EditMessage(_T(""))
{

}

CDlgMessage::~CDlgMessage()
{
}

void CDlgMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_DISPLAY, m_EditMessage);
}


BEGIN_MESSAGE_MAP(CDlgMessage, CDialogEx)
END_MESSAGE_MAP()


// CDlgMessage �޽��� ó�����Դϴ�.
