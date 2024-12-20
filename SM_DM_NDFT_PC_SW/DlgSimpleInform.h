#pragma once
#include "label_text.h"


// CDlgSimpleInform 대화 상자입니다.

class CDlgSimpleInform : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSimpleInform)

public:
	CDlgSimpleInform(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSimpleInform();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SIMPLE_INFORM };

public:
	 int m_Count;
	 CString m_DisplayString;
	 CString m_DisplayString2;
	 
	 int m_Close_Result;
	 int m_WaitMassage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CLabel_text m_cLabelInformDisplay;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedNg();
};
