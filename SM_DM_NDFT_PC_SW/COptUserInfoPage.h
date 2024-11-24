#pragma once


// COptUserInfoPage
class COptUserInfoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptUserInfoPage)

	// Construction
public:
	COptUserInfoPage();
	~COptUserInfoPage();

	// Dialog Data
		//{{AFX_DATA(COptUserInfoPage)
	enum { IDD = IDD_OPT_USERINFO_PAGE };
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
	//+add kwmoon 080416
	//CProgressMsgDlg* m_pProgressMsgDlg;
	void SetListControl();
	void SetSubListControl();
	// Overrides
		// ClassWizard generate virtual function overrides
		//{{AFX_VIRTUAL(COptGrabberPage)
public:
	virtual void OnOK();

	int m_ReadNo1;
	int m_ClearFlag;
	//int m_ReadNo2;
	//int m_ReadNo3;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptGrabberPage)
	//afx_msg void OnBtnGrabberOptApply();
	//virtual BOOL OnInitDialog();
	//afx_msg void OnBtnGrabberOptDelete();
	//afx_msg void OnBtnSave();
	//afx_msg void OnSelchangeComboPeriod();
	//afx_msg void OnHdmiResolution1();
	//afx_msg void OnHdmiResolution2();
	//afx_msg void OnHdmiResolution3();
	//afx_msg void OnHdmiResolution4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//////////////////////////////////////////////////////////////////////////
	//+ 2007.5.2 Add BY USY
public:
	//Variable
	//int m_nPeriod;
	////Function
	virtual BOOL OnInitDialog();

	//BOOL MakeOptionString(CString& szOptionData, UINT nNoDigit);

	////+add kwmoon 080415
	//BOOL DeleteFolder(CString szGrabFolderPath);

	////+add kwmoon 080415
	//void MakeModelFolderList(CString szModuleFolder, CStringArray& aModelFoler);



	//////////////////////////////////////////////////////////////////////////

	//afx_msg void OnBnClickedOk();
	CListCtrl m_CtrlListVoltProcess;
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_CtrlListDiProcess;
	//CListCtrl m_CtrlListDoProcess;
	afx_msg void OnBnClickedButtonDioCheck();
	afx_msg void OnNMClickListDiProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListDiProcess(NMHDR *pNMHDR, LRESULT *pResult);
};
//
//class COptUserInfoPage : public CMFCPropertyPage
//{
//	DECLARE_DYNAMIC(COptUserInfoPage)
//
//public:
//	COptUserInfoPage();
//	virtual ~COptUserInfoPage();
//
//protected:
//	DECLARE_MESSAGE_MAP()
//};


