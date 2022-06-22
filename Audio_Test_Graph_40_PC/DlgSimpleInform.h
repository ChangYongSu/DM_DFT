#pragma once
#include "label_text.h"


// CDlgSimpleInform ��ȭ �����Դϴ�.

class CDlgSimpleInform : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSimpleInform)

public:
	CDlgSimpleInform(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSimpleInform();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SIMPLE_INFORM };

public:
	 int m_Count;
	 CString m_DisplayString;
	 
	 int m_Close_Result;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	DECLARE_MESSAGE_MAP()
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CLabel_text m_cLabelInformDisplay;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
