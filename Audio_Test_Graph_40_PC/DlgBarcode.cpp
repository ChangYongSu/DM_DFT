// DlgBarcode.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgBarcode.h"
#include "afxdialogex.h"


// CDlgBarcode ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgBarcode, CDialogEx)

CDlgBarcode::CDlgBarcode(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBarcode::IDD, pParent)
{

}

CDlgBarcode::~CDlgBarcode()
{
}

void CDlgBarcode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL__BARCODE_1, m_clabelBarCode);
}


BEGIN_MESSAGE_MAP(CDlgBarcode, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgBarcode::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgBarcode::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlgBarcode::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if(pMsg->wParam == VK_RETURN)
		{
			//ClickCbtnStart();
			if(m_BarcodeString.GetLength() > 6)
			{
				m_Barcode = m_BarcodeString;
				OnBnClickedOk();
			}
			m_BarcodeString = _T("");
			return TRUE;
		}
	}
		
	else if(pMsg->message == WM_CHAR)
	{
		m_BarcodeString = m_BarcodeString  + (char)(pMsg->wParam);
		m_BarcodeString.MakeUpper();
		m_clabelBarCode.put_Caption(m_BarcodeString);
		return TRUE;		
	}	
	
	
	return CDialog::PreTranslateMessage(pMsg);
}

// CDlgBarcode �޽��� ó�����Դϴ�.


void CDlgBarcode::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ReturnFlag = 1;
	m_clabelBarCode.put_Caption("");
	CDialogEx::OnOK();
}


void CDlgBarcode::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ReturnFlag = 2;
	CDialogEx::OnCancel();
	m_clabelBarCode.put_Caption("");
}
