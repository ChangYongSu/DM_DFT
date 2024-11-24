#pragma once
#include "afxwin.h"
#include "textbox_okng.h"
#include "label_text.h"
//#include "cwboolean_do1.h"


// CDlgTestPage 대화 상자입니다.

class CDlgTestPage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestPage)

public:
	CDlgTestPage(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTestPage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TEST_PAGE };
public:
	BOOL InitPage();
	BOOL SetRemoconButton();
	BOOL InitDioChannel();
	BOOL SetD_OUT(ULONG lSetVal);
	BOOL ReadD_IN();
	void UpdateRead();

	unsigned long m_DI_Readdata;
	unsigned long m_DO_Writedata;
//	CNiDAQmxTask digitalReadTask;
//	CNiDAQmxTask digitalWriteTask;
	int m_DIportOpen;
	int m_DOportOpen;


	int m_TESTPAGE_COM_PROCESS;
	int m_ComAck;
	int m_WaitCnt;
	int m_ResendCnt;

	
	int m_LED_COM_PROCESS;
	int m_LEDComAck;
	int m_LEDWaitCnt;
	int m_LEDResendCnt;


	int m_PCB_COM_PROCESS;
	int m_PCBComAck;
	int m_PCBWaitCnt;
	int m_PCBResendCnt;

	int m_WaitPCB_Ack_Limit;



	BYTE m_RecvBuf[4096];
	int  m_RecvCnt;
		
	BYTE m_RecvBufPCB[4096];
	int  m_RecvCntPCB;

	BYTE m_RecvBufLED[4096];
	int  m_RecvCntLED;

	BYTE m_SendBuf[4096];
	int  m_SendCnt;	
	
	BYTE m_SendBufPCB[4096];
	int  m_SendCntPCB;

	BYTE m_SendBufLED[4096];
	int  m_SendCntLED;


	UINT m_nRecomonCount;
	CString m_strRemoconList[100];

	Recomon_ModelT m_RemoconModel;

	void OpenComport();
	void	OpenComportPCB();
	void	OpenComportLED();
	void    OpenComportSCAN();

	void ComResend();
	void ComLedRead();
	void ComPCBSend();


	void ComSend(BYTE *lbuf, int lcnt);
	void SetFreqSend(UINT lPort, UINT lFreq );
	//CSerialPort m_ComPort;
	//CSerialPort m_ComPortPCB;
	//CSerialPort m_ComPortLED;

	void GetRemoconList();
	void GetRmtCodeList(CString lRmtFile);
	void SendIRCode(int lRmtCodeIndex);


	void MessageDisplay(int lError, CString sMessage);
		

	int m_LAN_TestOK;
	int m_USB1_TestOK;
	int m_USB2_TestOK;

	int m_MAC_SendFlag;

	int		mbaud_List[10];
	UINT		nNumberPort[50];

	int		m_nPortPcb;
	int		m_nBaudPcb;
	int		m_nParityPcb;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboRmType;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg long OnReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg long OnReceiveDataPCB(WPARAM wParam, LPARAM lParam);
	afx_msg long OnReceiveDataLED(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedCheckDo1();
	afx_msg void OnBnClickedCheckDo2();
	afx_msg void OnBnClickedCheckDo3();
	afx_msg void OnBnClickedCheckDo4();
	BOOL m_CheckDO_1;
	BOOL m_CheckDO_2;
	BOOL m_CheckDO_3;
	BOOL m_CheckDO_4;
	BOOL m_Check_DI_1;
	BOOL m_Check_DI_2;
	BOOL m_Check_DI_3;
	BOOL m_Check_DI_4;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CLabel_text m_LedDi_1;
	CLabel_text m_LedDi_2;
	CLabel_text m_LedDi_3;
	CLabel_text m_LedDi_4;

	CLabel_text m_LedLAN;
	CLabel_text m_LedUSB1;
	CLabel_text m_LedUSB2;


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

	UINT m_EditFreq1;
	UINT m_EditFreq2;
	UINT m_EditFreq3;
	UINT m_EditFreq4;
	UINT m_EditFreq5;
	UINT m_EditFreq6;
	UINT m_EditFreq7;
	UINT m_EditFreq8;
	UINT m_EditFreq9;
	UINT m_EditFreq10;

	afx_msg void OnBnClickedButtonFreqSet();
	afx_msg void OnBnClickedButtonFreqRead();
	CComboBox m_cComboSignalCarrier;
	CComboBox m_cComboRmTest[12] ;
	/*CComboBox m_cComboRmTest2 ;
	CComboBox m_cComboRmTest3 ;
	CComboBox m_cComboRmTest4 ;
	CComboBox m_cComboRmTest5 ;
	CComboBox m_cComboRmTest6 ;
	CComboBox m_cComboRmTest7 ;
	CComboBox m_cComboRmTest8 ;
	CComboBox m_cComboRmTest9 ;
	CComboBox m_cComboRmTest10;
	CComboBox m_cComboRmTest11;
	CComboBox m_cComboRmTest12;*/
	afx_msg void OnBnClickedButtonRmtest1();
	afx_msg void OnBnClickedButtonRmtest2();
	afx_msg void OnBnClickedButtonRmtest3();
	afx_msg void OnBnClickedButtonRmtest4();
	afx_msg void OnBnClickedButtonRmtest5();
	afx_msg void OnBnClickedButtonRmtest6();
	afx_msg void OnBnClickedButtonRmtest7();
	afx_msg void OnBnClickedButtonRmtest8();
	afx_msg void OnBnClickedButtonRmtest9();
	afx_msg void OnBnClickedButtonRmtest10();
	afx_msg void OnBnClickedButtonRmtest11();
	afx_msg void OnBnClickedButtonRmtest12();
	afx_msg void OnCbnSelchangeComboSelectRmType();
//	CTextbox_okng m_cTestPageMessage;
	DECLARE_EVENTSINK_MAP()
	void ClickButtonTestConfig();
	CLabel_text m_cTpgMessage;
	CComboBox m_cComboRmtSelect;
	CString m_EditNewMac;
	CString m_EditMac1;
	CString m_EditMac2;
	CString m_EditMac3;
	CString m_EditMac4;
	afx_msg void OnBnClickedButtonMacSet();
	afx_msg void OnBnClickedButtonMacRead();
	afx_msg void OnBnClickedButtonLedRead();
	afx_msg void OnBnClickedButtonPcbSend();
	CComboBox m_ComboPcbType;
	CLabel_text m_Led_ON[16];
	CLabel_text m_Led_UP_DI_ON[4];
	afx_msg void OnBnClickedButtonLedClear();
	afx_msg void OnBnClickedCheckDoLed1();
	afx_msg void OnBnClickedCheckDoLed2();
	afx_msg void OnBnClickedCheckDoLed3();
	afx_msg void OnBnClickedCheckDoLed4();
	BOOL m_CheckDOLED_1;
	BOOL m_CheckDOLED_2;
	BOOL m_CheckDOLED_3;
	BOOL m_CheckDOLED_4;
	afx_msg void OnBnClickedButtonMic1On();
	afx_msg void OnBnClickedButtonMic2On();
	afx_msg void OnBnDoubleclickedButtonMic1On();
	afx_msg void OnBnDoubleclickedButtonMic2On();
	void ClickLabelLedUpDi1();
	CComboBox m_cComboPCBTempPort;
	CComboBox m_cComboTempSetBaud;
	CComboBox m_cComboTempSetParity;
	afx_msg void OnCbnSelchangeComboComportTempPcb();
	afx_msg void OnCbnSelchangeComboPcbTempBaud();
	afx_msg void OnCbnSelchangeComboTempPcbParity();
	afx_msg void OnBnClickedButtonUpdinRead();
};
