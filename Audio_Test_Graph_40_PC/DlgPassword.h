#pragma once


// CDlgPassword ��ȭ �����Դϴ�.

class CDlgPassword : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPassword)

public:
	CDlgPassword(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgPassword();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PASSWORD };



	CString m_sPassword;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	CString m_EditPassword;
	CString m_NewPassword;
	CString m_EditConfirmPassword;
	afx_msg void OnEnChangeEditEnterPassword();
	afx_msg void OnBnClickedButtonPasswordChange();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditConfirmPassword();
};
