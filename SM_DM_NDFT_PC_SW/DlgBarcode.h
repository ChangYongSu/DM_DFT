#pragma once
#include "label_text.h"


// CDlgBarcode ��ȭ �����Դϴ�.

class CDlgBarcode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBarcode)

public:
	CDlgBarcode(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgBarcode();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_Barcode ;
	CString m_BarcodeString ;
	int m_ReturnFlag;
public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CLabel_text m_clabelBarCode;
};
