#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <devguid.h>								// GUID_DEVCLASS_PORTS

#include <setupapi.h>					// ::SetupDi********* 
//#include "afxwin.h"
#pragma comment(lib, "setupapi.lib")
#include <vector>

// COptComportPage 대화 상자
class COptComportPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptComportPage)

	// Construction
public:
	COptComportPage();
	~COptComportPage();

	// Dialog Data
		//{{AFX_DATA(COptComportPage)
	enum { IDD = IDD_OPT_COMPORT_PAGE };
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
	int		m_nPort;
	int		m_nBaud;
	int		m_nParity;
	int		mbaud_List[10];


	int		m_nPortHdmi;
	int		m_nBaudHdmi;
	int		m_nParityHdmi;
//	int m_PortCnt;

	void COptComportPage::ComportSearch();
	void COptComportPage::GetDeviceInfo();
	CString		strPort[50];
	UINT		nNumberPort[50];
	int			m_PortCnt;
	int			m_PortCntCurrent;
	std::vector<SP_INTERFACE_DEVICE_DATA> interfaces;
	std::vector<SP_INTERFACE_DEVICE_DETAIL_DATA*> devicePaths;
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

	//afx_msg void OnBnClickedOk();
	CComboBox m_cComboMainPort;
	CComboBox m_cComboMainBaud;
	//CComboBox m_cComboMainParity;
	//CComboBox m_cComboHdmiParity;
	CComboBox m_cComboHdmiBaud;
	CComboBox m_cComboHdmiPort;
	CComboBox m_cComboScanPort;
	CComboBox m_cComboScanBaud;
	afx_msg void OnBnClickedSaveButton();
	CComboBox m_cComboUsbPort;
	CComboBox m_cComboUsbBaud;
	CComboBox m_cComboUsbParity;
	afx_msg void OnCbnSelchangeComboUsbPort();
	CComboBox m_cComboChipType;
};
//
//class COptComportPage : public CMFCPropertyPage
//{
//	DECLARE_DYNAMIC(COptComportPage)
//public:
//	COptComportPage();
//	virtual ~COptComportPage();
//
//protected:
//	DECLARE_MESSAGE_MAP()
//};

