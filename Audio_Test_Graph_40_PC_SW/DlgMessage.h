#pragma once


// CDlgMessage ��ȭ �����Դϴ�.

class CDlgMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMessage)

public:
	CDlgMessage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgMessage();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditMessage;
};
