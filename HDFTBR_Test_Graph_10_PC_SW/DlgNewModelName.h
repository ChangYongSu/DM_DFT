#pragma once


// CDlgNewModelName ��ȭ �����Դϴ�.

class CDlgNewModelName : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewModelName)

public:
	CDlgNewModelName(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgNewModelName();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODEL_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_NewName;
};
