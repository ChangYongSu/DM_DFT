#pragma once

#include "label_text.h"
// CUserMsgDlg 대화 상자입니다.

class CUserMsgDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMsgDlg)

public:
	CUserMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
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

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_USER_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnYes();
	afx_msg void OnBnClickedBtnNo();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CLabel_text m_cLabelMessge1;
	CLabel_text m_cLabelMessge2;
	afx_msg void OnClose();
};
