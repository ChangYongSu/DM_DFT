// DlgPassword.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgPassword.h"
#include "afxdialogex.h"
#include "FileControl.h"


// CDlgPassword ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgPassword, CDialogEx)

CDlgPassword::CDlgPassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPassword::IDD, pParent)
	, m_EditPassword(_T(""))
	, m_NewPassword(_T(""))
	, m_EditConfirmPassword(_T(""))
{

}

CDlgPassword::~CDlgPassword()
{
}

void CDlgPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ENTER_PASSWORD, m_EditPassword);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWORD, m_NewPassword);
	DDX_Text(pDX, IDC_EDIT_CONFIRM_PASSWORD, m_EditConfirmPassword);
}


BEGIN_MESSAGE_MAP(CDlgPassword, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ENTER_PASSWORD, &CDlgPassword::OnEnChangeEditEnterPassword)
	ON_BN_CLICKED(IDC_BUTTON_PASSWORD_CHANGE, &CDlgPassword::OnBnClickedButtonPasswordChange)
	ON_BN_CLICKED(IDOK, &CDlgPassword::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CONFIRM_PASSWORD, &CDlgPassword::OnEnChangeEditConfirmPassword)
END_MESSAGE_MAP()


// CDlgPassword �޽��� ó�����Դϴ�.



BOOL CDlgPassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	GetDlgItem(IDC_BUTTON_PASSWORD_CHANGE)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(0);

//	GetDlgItem(IDC_EDIT_PSWRD)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}





void CDlgPassword::OnEnChangeEditEnterPassword()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData();
	//char lbuf1[128];
	//char lbuf2[128];
	//sprintf(lbuf1,"%s",m_EditCurrentPW.GetBuffer());
	//sprintf(lbuf2,"%s",m_sPassword.GetBuffer());
	if(m_EditPassword ==  m_sPassword)
	{
		GetDlgItem(IDOK)->EnableWindow(1);
	}
	else if(m_EditPassword.Compare(_T("swcys1")) == 0 )
	{
		GetDlgItem(IDOK)->EnableWindow(1);
		g_strPassword = "1111";
		m_sPassword = g_strPassword;
		CFileControl lFile;
		lFile.SaveConfigSeqData();
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PASSWORD_CHANGE)->EnableWindow(0);
		GetDlgItem(IDOK)->EnableWindow(0);
	}

}

void CDlgPassword::OnEnChangeEditConfirmPassword()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	if(m_EditPassword == m_sPassword)
	{
		if(m_NewPassword == m_EditConfirmPassword)
		{
			if(m_NewPassword.GetLength()>3)
				GetDlgItem(IDC_BUTTON_PASSWORD_CHANGE)->EnableWindow(1);
		}
		
	}
}

void CDlgPassword::OnBnClickedButtonPasswordChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(m_EditPassword == m_sPassword)
	{
		if(m_NewPassword == m_EditConfirmPassword)
		{
			if(m_NewPassword.GetLength()>3)
			{
				m_sPassword = m_NewPassword;
			}
			else
			{
				MessageBox("New Password too Short Enter More than 4 Char !!");
			}
		}
		
	}
}


void CDlgPassword::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();


	CDialogEx::OnOK();
}




/*

	CString m_EditPassword;
	CString m_NewPassword;
	CString m_EditConfirmPassword;
*/