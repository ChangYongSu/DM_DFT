#pragma once


// COptFolderPage

class COptFolderPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptFolderPage)

	// Construction
public:
	COptFolderPage();
	~COptFolderPage();

	// Dialog Data
		//{{AFX_DATA(COptFolderPage)
	enum { IDD = IDD_OPT_FOLDER_PAGE };
	CString	m_szPatternFilePath;
	CString	m_szRemoteFilePath;
	CString	m_szTemplateSeqPath;
	CString	m_szTestParamPath;
	CString	m_szModelListPath;
	CString	m_strServerFolder;
	CString	m_strRefImageFolder;
	CString	m_strModelInfoFolder;
	//}}AFX_DATA

public:
	//+add kwmoon 080416
	//CProgressMsgDlg* m_pProgressMsgDlg;

	// Overrides
		// ClassWizard generate virtual function overrides
		//{{AFX_VIRTUAL(COptFolderPage)
public:
	//virtual void OnOK();
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
	//BOOL MakeOptionString(CString& szOptionData, UINT nNoDigit);

	////+add kwmoon 080415
	//BOOL DeleteFolder(CString szGrabFolderPath);

	////+add kwmoon 080415
	//void MakeModelFolderList(CString szModuleFolder, CStringArray& aModelFoler);



	//////////////////////////////////////////////////////////////////////////
		//{{AFX_MSG(COptFolderPage)
	afx_msg void OnBtnOpenPattern();
	afx_msg void OnBtnOpenRemote();
	afx_msg void OnBtnOpenTestParam();
	afx_msg void OnBtnOpenTemplateSeq();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOpenModelList();
	afx_msg void OnBtnOpenServerFolder();
	afx_msg void OnBtnOpenRefFolder();
	afx_msg void OnBtnOpenModelinfoFolder();
	//}}AFX_MSG
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSave();
};
//class COptFolderPage : public CMFCPropertyPage
//{
//	DECLARE_DYNAMIC(COptFolderPage)
//
//public:
//	COptFolderPage();
//	virtual ~COptFolderPage();
//
//protected:
//	DECLARE_MESSAGE_MAP()
//};


