// DlgNewModelName.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgNewModelName.h"
#include "afxdialogex.h"


// CDlgNewModelName ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgNewModelName, CDialogEx)

CDlgNewModelName::CDlgNewModelName(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewModelName::IDD, pParent)
	, m_NewName(_T(""))
{

}

CDlgNewModelName::~CDlgNewModelName()
{
}

void CDlgNewModelName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_NewName);
}


BEGIN_MESSAGE_MAP(CDlgNewModelName, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewModelName �޽��� ó�����Դϴ�.
