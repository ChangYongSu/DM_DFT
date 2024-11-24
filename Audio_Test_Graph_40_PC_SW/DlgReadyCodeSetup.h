#pragma once
#include "afxwin.h"


// CDlgReadyCodeSetup ��ȭ �����Դϴ�.

class CDlgReadyCodeSetup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReadyCodeSetup)

public:
	CDlgReadyCodeSetup(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgReadyCodeSetup();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_READY_CODE_SETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:

	Recomon_ModelT m_RemoconModel;
	TestProcess_T m_RdTestProcess;
	void GetRdRmtCodeList(CString lRmtFile);
	void DisplaySeqData();
	void EnableComboSeq();
	int  UpdateListData();
	

public:
	CComboBox m_cComboReRmtCode;
	CComboBox m_cComboRdSeq[10];
	//CComboBox m_cComboRdSeq;
	CString m_EditRdSq[10];
	//CString m_EditRdSq;
	afx_msg void OnCbnSelchangeComboRdseq1();
	afx_msg void OnCbnSelchangeComboRdseq2();
	afx_msg void OnCbnSelchangeComboRdseq3();
	afx_msg void OnCbnSelchangeComboRdseq4();
	afx_msg void OnCbnSelchangeComboRdseq5();
	afx_msg void OnCbnSelchangeComboRdseq6();
	afx_msg void OnCbnSelchangeComboRdseq7();
	afx_msg void OnCbnSelchangeComboRdseq8();
	afx_msg void OnCbnSelchangeComboRdseq9();
	afx_msg void OnCbnSelchangeComboRdseq10();
	afx_msg void OnBnClickedOk();
};
