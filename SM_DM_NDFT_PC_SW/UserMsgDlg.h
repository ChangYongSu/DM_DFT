#pragma once


// CUserMsgDlg ��ȭ �����Դϴ�.

class CUserMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMsgDlg)

public:
	CUserMsgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUserMsgDlg();

public:
	CRect m_dlgRect;

	CString m_szMsg1;
	CString m_szMsg2;
	int m_DelayTime;
	//+add kwmoon 080508
	BOOL	m_bYes;
	BOOL m_bShowOkButton;
	BOOL m_Close_Result;

	void ShowMessage2(CString szMsg);
	void ShowMessage1(CString szMsg);

	void SetMessage(CString szMsg1, CString szMsg2);
	void SetMessageTime(CString szMessage1, CString szMessage2, int lDely);
	
	//+ add 090902
	BOOL		m_bActivate;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_USER_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnYes();
	afx_msg void OnBnClickedBtnNo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
