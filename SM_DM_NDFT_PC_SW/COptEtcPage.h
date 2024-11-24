#pragma once
class COptEtcPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptEtcPage)

	// Construction
public:
	COptEtcPage();
	~COptEtcPage();

	// Dialog Data
		//{{AFX_DATA(COptGrabberPage)
	enum { IDD = IDD_OPT_ETC_PAGE };
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
	//virtual void OnOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
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
	//BOOL MakeOptionString(CString& szOptionData, UINT nNoDigit);

	////+add kwmoon 080415
	//BOOL DeleteFolder(CString szGrabFolderPath);

	////+add kwmoon 080415
	//void MakeModelFolderList(CString szModuleFolder, CStringArray& aModelFoler);



	//////////////////////////////////////////////////////////////////////////

	//afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonFreqSet();
	afx_msg void OnBnClickedButtonFreqRead();
	//afx_msg void OnBnClickedButtonMic1On();
	//afx_msg void OnBnClickedButtonMic2On();

	afx_msg void OnBnClickedButtonFreq1();
	afx_msg void OnBnClickedButtonFreq2();
	afx_msg void OnBnClickedButtonFreq3();
	afx_msg void OnBnClickedButtonFreq4();
	afx_msg void OnBnClickedButtonFreq5();
	afx_msg void OnBnClickedButtonFreq6();
	afx_msg void OnBnClickedButtonFreq7();
	afx_msg void OnBnClickedButtonFreq8();
	afx_msg void OnBnClickedButtonFreq9();
	afx_msg void OnBnClickedButtonFreq10();
	afx_msg void OnBnClickedButtonFreq11();
	afx_msg void OnBnClickedButtonFreq12();

	UINT m_EditFreq[12];



	afx_msg void OnBnClickedButtonSave();
};
//
//// COptEtcPage
//
//class COptEtcPage : public CMFCPropertyPage
//{
//	DECLARE_DYNAMIC(COptEtcPage)
//
//public:
//	COptEtcPage();
//	virtual ~COptEtcPage();
//
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//

