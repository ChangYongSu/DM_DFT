#pragma once


// COptSpecPage
class COptSpecPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptSpecPage)

	// Construction
public:
	COptSpecPage();
	~COptSpecPage();

	// Dialog Data
		//{{AFX_DATA(COptSpecPage)
	enum { IDD = IDD_OPT_SPEC_PAGE };
	//CComboBox	m_ctrlHDMI_BitSpec;
	//CComboBox	m_ctrlPeriod;
	//int		m_nAnalogFormat;
	//int		m_nAudioMeasureMethod;
	//BOOL	m_bAutoDataDelete;
	//int		m_nHDMI_Resolution;
	//int		m_nRemoconCustomCode;
	//int		m_nRemoteType;
	//int		m_nAvSwitchBoxBuzzerMute;
	//int		m_nGrabCheckArea;
	//int		m_nAvSwitchBoxVideoMode;
	//}}AFX_DATA

public:
	BOOL COptSpecPage::Firmware_VersionRead(int nIndex);
	int m_WaitCount;
	//CProgressMsgDlg* m_pProgressMsgDlg;

	// Overrides
		// ClassWizard generate virtual function overrides
		//{{AFX_VIRTUAL(COptGrabberPage)
public:
	virtual void OnOK();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptSpecPage)
	//afx_msg void OnBtnGrabberOptApply();
	virtual BOOL OnInitDialog();
	//afx_msg void OnBtnGrabberOptDelete();
	//afx_msg void OnBtnSave();
	//afx_msg void OnSelchangeComboPeriod();
	//afx_msg void OnHdmiResolution1();
	//afx_msg void OnHdmiResolution2();
	//afx_msg void OnHdmiResolution3();
	//afx_msg void OnHdmiResolution4();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

	
	//////////////////////////////////////////////////////////////////////////

public:
	//Variable
	int  mCheckAll;
	int m_EditMode;
	int m_SelectItem;
	int m_SelectShell;
	void InitVerSpecGrid();
	void UpdateVerSpecGrid();
	void COptSpecPage::ReadNextUpdateVersion();
	//int m_nPeriod;
	////Function
	//BOOL MakeOptionString(CString& szOptionData, UINT nNoDigit);

	
	  	//////////////////////////////////////////////////////////////////////////
	//void OnOK();
	//afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_ctrlAudioVerSpecList;
	afx_msg void OnHdnItemclickListAudioSpecList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListAudioSpecList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListAudioSpecList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonUpdateVersion();
	afx_msg void OnBtnOptApply();
	afx_msg void OnBtnSave();
	afx_msg void OnEnChangeEditOptVersion();

	CEdit m_cEditOptVersion;
};
//
//class COptSpecPage : public CMFCPropertyPage
//{
//	DECLARE_DYNAMIC(COptSpecPage)
//
//public:
//	COptSpecPage();
//	virtual ~COptSpecPage();
//
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//

