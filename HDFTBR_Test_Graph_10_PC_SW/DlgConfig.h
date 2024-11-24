#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <devguid.h>								// GUID_DEVCLASS_PORTS

#include <setupapi.h>					// ::SetupDi********* 
//#include "afxwin.h"
#pragma comment(lib, "setupapi.lib")
#include <vector>


#define PORTCHEK_MODE_IDLE__		0
#define PORTCHEK_MODE_MAIN__		1
#define PORTCHEK_MODE_PCBSET__		2
#define PORTCHEK_MODE_LEDCHECK__	3
#define PORTCHEK_MODE_SCANCHECK__	4


// CDlgConfig ��ȭ �����Դϴ�.

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgConfig();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CONFIG };

	int		m_nPort;
	int		m_nBaud;
	int		m_nParity;
	int		mbaud_List[10];

		
	int		m_nPortPcb;
	int		m_nBaudPcb;
	int		m_nParityPcb;

		
	int		m_nPortLED;
	int		m_nBaudLED;
	int		m_nParityLED;

	int		m_nPortScan;
	int		m_nBaudScan;
	int		m_nParityScan;
	int		m_nNI_CardSel;


	
	BYTE m_RecvBuf[4096];
	int  m_RecvCnt;
		
	BYTE m_RecvBufPCB[4096];
	int  m_RecvCntPCB;

	BYTE m_RecvBufLED[4096];
	int  m_RecvCntLED;

	BYTE m_RecvBufSCAN[4096];
	int  m_RecvCntSCAN;

	
	CString m_IPaddressGmes;//m_CtrlIpaddressGmes

	void	OpenComport();
	void	OpenComportPCB();
	void	OpenComportLED();

	void  ComSend();
	void  ComLedRead();
	void  ComPCBSend();
	
	void ComportSearch();

	void SearchPort(int* ArrPort);
	void GetDeviceInfo();
	CString		strPort[50];
	UINT		nNumberPort[50];
	int			m_PortCnt;
	int			m_PortCntCurrent;
	std::vector<SP_INTERFACE_DEVICE_DATA> interfaces;	
    std::vector<SP_INTERFACE_DEVICE_DETAIL_DATA*> devicePaths;



	int m_CheckMode;// = PORTCHEK_MODE_MAIN__;


	int m_ComAck;	
	int m_LEDComAck;	
	int m_PCBComAck;
	int m_SCANComAck;

		int m_WaitCnt;

//		UINT g_nPort_Set = 1;
//UINT g_nBaud_Set = 19200;
//UINT g_nParity_Set = 0;
//
//UINT g_nPort_Pcb = 2;
//UINT g_nBaud_Pcb = 19200;
//UINT g_nParity_Pcb = 0;
//
//UINT g_nPort_LED = 3;
//UINT g_nBaud_LED = 19200;
//UINT g_nParity_LED = 1;




protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	
	afx_msg long OnReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg long OnReceiveDataPCB(WPARAM wParam, LPARAM lParam);
	afx_msg long OnReceiveDataLED(WPARAM wParam, LPARAM lParam);
	afx_msg long OnReceiveDataSCAN(WPARAM wParam, LPARAM lParam);


	//CString m_EditPortString;
	CComboBox m_cComboBaud;

	//CString m_EditMesTnsTimeout;
	//CString m_EditMesAvnReplyTimeout;
	//CString m_EditMesUserID_CEID;
	//CString m_EditMesPswrdRPTID;
	//CString m_EditMesLine;
	//CString m_EditMesInspStep;

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	//CString m_EditSetPortString;
	//CString m_EditLEDPortString;
	CComboBox m_cComboSetBaud;
	CComboBox m_cComboLEDBaud;
	CComboBox m_cComboParity;
	CComboBox m_cComboSetParity;
	CComboBox m_cComboLedParity;
//	CIPAddressCtrl m_CtrlIpaddressGmes;
	CString m_PortNumber;
	CComboBox m_cComboPortSel;
	afx_msg void OnBnClickedButtonPortCheck();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSetPortCheck();
	afx_msg void OnBnClickedButtonLedPortCheck2();
	afx_msg void OnBnClickedButtonScannerPortCheck();
	CComboBox m_cComboScanBaud;
	CComboBox m_cComboScanParity;
	CComboBox m_cComboScanPort;
	CComboBox m_cComboLEDPort;
	CComboBox m_cComboPCBPort;
	CComboBox m_cComboMainPort;
	afx_msg void OnCbnSelchangeComboComportScan();
	CString m_Edit_RX_Data;
	CString m_ServerPortNumberCM45;
	CString m_ServerPortNumberCM89;
	BOOL m_CheckUseUSB_Scanner;
	CComboBox m_cComboNI_CardSel;
	afx_msg void OnBnClickedCheckUseUsbScanner();
};
