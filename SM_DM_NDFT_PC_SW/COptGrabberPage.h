#pragma once

#if 1

class COptGrabberPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptGrabberPage)

	// Construction
public:
	COptGrabberPage();
	~COptGrabberPage();

	// Dialog Data
		//{{AFX_DATA(COptGrabberPage)
	enum { IDD = IDD_OPT_GRABBER_PAGE };
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

	// Overrides
		// ClassWizard generate virtual function overrides
		//{{AFX_VIRTUAL(COptGrabberPage)
public:
	virtual void OnOK();
	//virtual void OnOK();

	void GetRemoconList();

	CString m_strRemoconList[1000];
	int m_nRecomonCount;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptGrabberPage)
	//afx_msg void OnBtnGrabberOptApply();
	virtual BOOL OnInitDialog();
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
	//BOOL MakeOptionString(CString& szOptionData, UINT nNoDigit);

	////+add kwmoon 080415
	//BOOL DeleteFolder(CString szGrabFolderPath);

	////+add kwmoon 080415
	//void MakeModelFolderList(CString szModuleFolder, CStringArray& aModelFoler);



	//////////////////////////////////////////////////////////////////////////

	afx_msg void OnBnClickedOk();
	CComboBox m_cComboGrabberType;
	CComboBox m_cComboAI_CardType;
	afx_msg void OnBnClickedButtonSave();
	int m_nGrabCheckArea;
	CComboBox m_cRemoconCombo;
	int m_nRemoteType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#else

// COptGrabberPage

class COptGrabberPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(COptGrabberPage)

public:
	COptGrabberPage();
	virtual ~COptGrabberPage();

protected:
	DECLARE_MESSAGE_MAP()
};

#endif