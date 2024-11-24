
// CAcqVoltageSamples_IntClkDlg : header file
//

#pragma once
#include "afxwin.h"
#include "textbox_okng.h"
#include "afxext.h"
#include "label_text.h"
//#include "afxcmn.h"

#include "DlgResult.h"
#include "DlgBarcode.h"
#include "DlgMessage.h"
#include "DlgSimpleInform.h"
#include "UserMsgDlg.h"

//#include <opencv2\opencv.hpp>
//#include <allheaders.h>
//#include <baseapi.h>
#include "afxcmn.h"

#include "UDpAsySk.h"
#include "dask.h"
#pragma comment(lib, "liblept168")
#pragma comment(lib, "libtesseract302")

using namespace std;
//using namespace cv;
//using namespace tesseract;

//#define TESTMODE_LEVEL_CHANGE

#define TESTMODE_NOISE_HIGHSAMPLERATE

#ifdef TESTMODE_NOISE_HIGHSAMPLERATE
#define NI_SAMPLE_RATE		200000.0
#define NI_SAMPLE_COUNT		6000
#define NI_CHECK_COUNT		4000
#else
#define NI_SAMPLE_RATE		100000.0
#define NI_SAMPLE_COUNT		3000
#define NI_CHECK_COUNT		2000

#endif

#define ADLINK_SAMPLE_RATE		100000.0
#define ADLINK_SAMPLE_COUNT		3072 // 1024*3
#define ADLINK_CHECK_COUNT		2000

#define AI_NIPCI_9010			0
#define AI_NIPCIe_9330			1
#define AI_ADLINK_PCI_9111		2


// CAcqVoltageSamples_IntClkDlg dialog
class CAcqVoltageSamples_IntClkDlg : public CDialog
{
// Construction
public:
    // Standard constructor
    CAcqVoltageSamples_IntClkDlg(CWnd* pParent = NULL);

    // Dialog data
    enum { IDD = IDD_ACQVOLTAGE_INTCLKDIGREF_DIALOG };

protected:
    // DDX/DDV support 
    virtual void DoDataExchange(CDataExchange* pDX);

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()
public:

	int		m_RunCounter;
	int		m_TaskRun;
	int		m_nCurrentNumber;
	int		m_nCurrentProcess;
	int		m_nCurrentStep;
	int		m_WaitCnt ;

	UINT m_OKcnt;


	long	m_AI_SAMPLE_COUNT;
	long	m_AI_CHECK_COUNT;
	double	m_AI_SAMPLE_RATE;
	int		m_nCardIdx;
	int		m_CardType;
	short	m_hCard;
	U16		m_wScanChans;
	U16		m_wRange;

	long	samplesPerChannel;
	void	SetDigitalPortSelect(int lDigSel, int lRefresh);
	void	CheckDigitalPort();
	void	SetChannelData(int lTestNumber);
	void	InitChannel();

	void	InitClearChannel();
	void	InitChannelOne(int lch);
	void	ReadChannel(int lch);
	void	UpdatePlot(int lch);
	void	CheckData(int CheckID);
	void	CheckOK();
	void	TestResultDisplay();
	void	CheckTotalOK();
	void	CallProcess();
	void	CallPreProcess(int lCurrentProcess);
	void	TestFinish();
	void	TestFinishGMES();
	void	SendOkSignalToJig();
	


	//CSerialPort m_ComPort;
	//CSerialPort m_ComPortPCB;
	//CSerialPort m_ComPortLED;
	void	ComSend();
	void ComPCBSend();
	void ComLedRead();
	void	OpenComport();
	void	OpenComportPCB();
	void	OpenComportLED();
	void OpenComportSCAN();

	int m_MainPAGE_COM_PROCESS;//m_TESTPAGE_COM_PROCESS;
	int  m_ComAck;
	//	 m_WaitCnt = 0;
	int  m_ResendCnt;

	int m_PCB_COM_PROCESS ;
	int m_PCBComAck ;
	int m_PCBWaitCnt ;
	int m_PCBResendCnt;

		int m_WaitPCB_Ack_Limit;

		
	int m_LED_COM_PROCESS;
	int m_LEDComAck;
	int m_LEDWaitCnt;
	int m_LEDResendCnt;


	
	BYTE m_RecvBuf[4096];
	int  m_RecvCnt;

	BYTE m_RecvBufPCB[4096];
	int  m_RecvCntPCB;

	BYTE m_RecvBufLED[4096];
	int  m_RecvCntLED;

	BYTE m_RecvBufSCAN[4096];
	int  m_RecvCntSCAN;


	BYTE m_SendBuf[4096];
	int  m_SendCnt;	
	
	BYTE m_SendBufPCB[4096];
	int  m_SendCntPCB;

	BYTE m_SendBufLED[4096];
	int  m_SendCntLED;

	void	SendData(BYTE *lbuf, int lcnt);
	int m_ComWaitCnt;

	int m_ComSMAV_1100APOk;

	
	BOOL InitDioChannel();
	BOOL SetD_OUT(ULONG lSetVal);
	BOOL ReadD_IN(unsigned long *lReadData);
	void CheckControlInput();
	
	
	Recomon_ModelT m_RemoconModel;
	void SendIR_Code(CString lCodeString, int lRepeat);
	void SendPreIR_Code(CString lCodeString, int lRepeat);
	int m_PrecodeWait;
	void GetRmtCodeList(CString lRmtFile);

	void UartCommandPcbSend();

	void LEDReadSend();
	void LEDClearSend();
	void UP_DIReadSend();
	
	void MessageDisplay(int lError, CString sMessage);


	void MesStart();
	int  MesTestReport();

	double m_avg_PPVoltage[8][3];
	double m_avg_Freg[8][3];

	double m_PPVoltage[8];
	double m_Frequency[8];

	double m_NoiseFlag[8];


	double m_RefVoltageMin[8];
	double m_RefVoltageMax[8];
	double m_FrequencyMin[8];
	double m_FrequencyMax[8];
	//double m_VoltageBalnce[8];//m_TmpVoltageBalnce
	

	double m_CheckVoltage[8];
	double m_CheckFrequency[8];

	int m_ChannelOK[8];
	int m_ChannelOKCNT[8];
	int m_VoltageOK[8];
	int m_FrequencyOK[8];
	int m_BalanceOK[8];
	int m_NG_OK_Num;

	bool m_LevelSkip;

	//int m_TEST_1_OK;
	//int m_TEST_2_OK;
	int m_TEST_Number;
	bool m_NewSystemCheck;

	int  m_TEST_Result;

	int m_TotalOK;
	bool m_bStartMES;


	CNiReal64Matrix Check_data[16];

	int  m_CheckID[8];
	int  m_CheckEnable[8];
	CString  m_CheckName[8];

	int m_DigitalPort;
	int m_DigitalPort_Save;

	int m_InitAiChannel;
	int m_DOportOpen;
	int m_DIportOpen;

	unsigned long m_DO_Writedata;
	
	CString m_BarcodeString;
	CString m_WipID;
	int m_GMES_Skipped;


	
	void SetTimeCheck(int  lIndex);
	unsigned long GetTimeCheck(int  lIndex);
	void  DisplayTimeLap();

	unsigned long mstartT[64];


	int		m_PreRunCounter;
	int		m_PreTaskRun;
	int		m_nPreCurrentNumber;
	int		m_nPreCurrentStep;
	int		m_nPreCurrentProcess;


	int CheckTimeOn;
	int CycleTimeOn;

	int m_LAN_CheckOK;
	int m_USB1_CheckOK;
	int m_USB2_CheckOK;
	int m_PCB_CheckOK;
	int m_LED_CheckOK;

	CFont* font;
	
	void LoadTestData(CString lstrModelname);//LoadTestData(CString lstrModelname)
	void DisplayTestData();
	void SetListControl();
	void SetSubListControl();


	int SetFunction(CString lString = "", int lStringIn = 0); //void SetFunction();
	//void CAcqVoltageSamples_IntClkDlg::CheckFunction();
	void RunFunction();
	void SetChannelDataSeq(int lTestChannel, int lSource);
	void SetChannelDataRangeSeq(int lTestChannel, int l_RefVoltageMin,int l_RefVoltageMax,int l_FrequencyMin,int l_FrequencyMax);
	void SetChannelDataRangeSeq(int lTestChannel, int l_RefVoltageMin,int l_RefVoltageMax,int l_FrequencyMin,int l_FrequencyMax, int l_TmpVoltageBalnce);

	void CAcqVoltageSamples_IntClkDlg::SetChannelDataManual(int lTestNumber);

	void PreSetFunction();
	void PreRunFunction();

	void SetFreqSend(UINT lPort, UINT lFreq );


	int mCheckAll;

	CString m_FunctionName;
	CString m_FunctionParameter;
	int			m_FunctionType;
	int			m_CheckDelayTime;
	CString		m_strMP_Key;
	int			m_RepeatCount;

	
	CString		m_PreFunctionName;
	CString		m_PreFunctionParameter;
	int			m_PreFunctionType;
	int			m_PreCheckDelayTime;
	CString		m_PrestrMP_Key;



	//TestPort_T m_PortData;
	int			m_nChannel;
	int			m_nSource;

	int m_TmpVoltageMin;
	int m_TmpVoltageMax;
	int m_TmpFrequencyMin;
	int m_TmpFrequencyMax;
	int m_TmpVoltageBalnce;

	int m_nBalanceEnable[8];
	int m_nBalanceChannel[8];
	int m_nBalanceValue[8];


	CString		m_strCameraCheckIMGfile;
	int			m_Match_Percent;
	CString		m_strCameraCheckChar;

	unsigned char m_UartMcuType;
	unsigned char m_UartCommand[50];
	int m_UartCommandCnt;
	unsigned char m_UartOkAckData[50];
	unsigned char m_UartREADData[50];
	int m_UartOkAckDataCnt;

	unsigned char m_LEDOkAckData[4];
	unsigned char m_LEDReadData[4];
	unsigned char m_LED_Up_DI_ReadData[4];
	int m_FanDiPort;
	int m_MIC_Status;




//////////////////////////////////////////////////////////////

	double tres1;
	double tres2;
	
	int nErode;
	int nDilate;
	int mTres,mTresMax;//	
	int mX,mY;	
	int mXW,mYH;	
	int mR,mG,mB;

	int m_ocrX,m_ocrY;	
	int m_ocrXW,m_ocrYH;	

//	TessBaseAPI api;


//	Mat src_Mat;
//	cv::Mat image;
//	Mat Template_Rslt;

	//void ProcessGetImage();
	//void ProcessTemplate();
	//void ProcessImage();
	//void ProcessOcr();
	////void EdgeGray(cv::Mat *gray, cv::Mat *edge, cv::Mat *outImage);
	//void SelectImage();

	CRect rect;
	CDC memDC;
	CBitmap Bitmap,*pOldBitmap;
	CDC *m_pDC;

	//void ResizeImage(IplImage* src_img, IplImage** dst_img, CRect* rect);
	//void DisplayImage(IplImage* img);
	//void DisplayBitmap(CDC* pDC, CRect rect, IplImage* img);


	int m_Camera_CheckOK;
	int m_Camera_Capture_Flag;
	CWinThread *pThreadCap;

	int m_EnableCount;
	int m_RoopCnt;
	CUdpAsySk *m_pUDPSocket;

	TCHAR m_szError[255];
	int m_EthernetMode;
	//int m_UploadGmes;
	int m_GmesOpen;
	UINT m_EthernetWaitCnt;
	UINT m_EthernetAck;
	UINT m_EthernetResendCnt;
	UINT m_GMES_Alive_WaitCnt;
	UINT m_GMES_CommError;
	UINT m_GMES_NGCNT;
	
	CString m_strEthernetReceive;
	CString m_strMesSend;
	CString m_GMES_ErrorName;//
	CString m_GMES_ErrorValue;

	CString m_Deisplay_ErrorName;//
	CString m_Deisplay_ErrorDetail;


	void CloseEthernetScocket() ;
	//void CreateEthernetSocket() ;
	long OnParseDataEthernet();
	BOOL OnCmdGmesSend();
	BOOL CreateEthernetSocket() ;
	BOOL ConnectSocket();
	
	int			m_AlarmNumber;
	int			m_AlarmCode[100];
	CString		m_AlarmName[100];
	CString		m_AlarmMessage[100];

	void GMESAreYouThereRequest();
	void GMESEquipmentStatusSend(int lStatus);
	void GMESLinkLoopbackTest();
	void GMESLinkLoopbackResponce(CString strAS_);
	void GMESLinkTestResponse() ;
	void GMESDateandTimeData();
	void GMESLoopbackdiagnosticsTestAcknowledge(CString lLoopBackString);
	void GMESDataandTimeAcknowledge(int lAck);
	void GMESAlarmSetReportSend(int lAlarm);
	void GMESAlarmSetReportSend() ;
	void GMES_Scan_InformSend(int lSendForce = 0);//F11
	void GMES_Result_ReportSend();
	void GMESProductDataAcknowledge();

	CString CAcqVoltageSamples_IntClkDlg::GetMyIPAddress();


	CDlgResult	*mpDlgResult;
	CDlgBarcode	*mpDlgBarcode;

	CDlgSimpleInform 	*mpDlgSimpleInform;
	CUserMsgDlg					*m_pUserMsgDlg;

	void NG_Display(CString lstr = "");
	void OK_Display();
	void CLOSE_Result_Display();

	void BarcodeErrorDisplay();
	int m_MainCOM_NG_Count;
	int m_NG_Retry_Count;
	int m_NG_WaitFlag;

	
	void SetGuiPos(int Mode);

	void AddGmesLog(CString LogStr, int Recv  = 0);
	void AddProcessLog(CString LogStr, int New = 0);
	void AddPCBLog(BYTE *LogData, int Cnt, int Rcv = 0);
	void OnBnClickedButtonFreqSet();

	void ChangeModel(CString lModel);
	int MessageWindow(CString str);
	CString GetModelList(CString NewName);

public:
     afx_msg void OnBnClickedStart();
	 afx_msg long OnReceiveData(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataPCB(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataLED(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataEthernet(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataSCAN(WPARAM wParam, LPARAM lParam);
	

 //  	ON_MESSAGE(WM_COMM_RXCHAR_PCB,OnReceiveDataPCB)
//	ON_MESSAGE(WM_COMM_RXCHAR_LED,OnReceiveDataLED) CButton m_startButton;
 //   CComboBox m_physicalChannel;
  //  CString m_minimum;
  //  CString m_maximum;
  //  CString m_samplesPerChannel;
  //  CString m_rate;

    std::auto_ptr<CNiDAQmxTask> m_task[16];
    std::auto_ptr<CNiDAQmxAnalogMultiChannelReader> m_reader[16];
    //std::auto_ptr<CNiDAQmxTask> m_task1;
    //std::auto_ptr<CNiDAQmxAnalogMultiChannelReader> m_reader1;

    CNiReal64Matrix m_data[16];
    CNiColor m_colors[8];

    // Callback for asynchronous DAQmx reads
    void RemoveEventHandler();
    void CleanUpIfNecessary();


   
	CNiGraph m_graph[8];
	//CString M_Vol[16];
	//CString M_Frq[16];


	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStopButton();
	CString m_ChnnelName[8];

	CLabel_text m_BarCode;
	CLabel_text m_BarCodeMark;
	

	CLabel_text m_FreqLabel[8];
	CLabel_text m_VoltLabel[8];
	CLabel_text m_NameLabel[8];



	CLabel_text m_MessageDisplay;

	CLabel_text m_CheckTimeLabel;
	CLabel_text m_CycleTimeLabel;
	CLabel_text m_CheckTimeLabelName;
	CLabel_text m_CycleTimeLabelName;

	CLabel_text m_OKCntLabel;
	CLabel_text m_NGCntLabel;
	CLabel_text m_OKCntLabelName;
	CLabel_text m_NGCntLabelName;//IDC_LABEL_OK_CNT_NAME
	
	afx_msg void OnBnClickedSetupButton();
	afx_msg void OnBnClickedTestButton();

	CBitmapButton m_cBtnStart;
	CBitmapButton m_cSetupButton;
	CBitmapButton m_cStopButton;
	CBitmapButton m_cTestButton;
	CBitmapButton m_cExitButton;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//DECLARE_EVENTSINK_MAP()
	//void MouseDownTextboxModel(short Button, short Shift, float X, float Y);
	//void MouseUpTextboxModel(short Button, short Shift, float X, float Y);

	CLabel_text m_cLbModel;
	CLabel_text m_cLbOkNg;
	CLabel_text m_cLb_Test1;
	CLabel_text m_cLb_Test2;
	CLabel_text m_cLb_Test3;
	//CLabel_text m_clbHz;

	CLabel_text m_cLb_Lan;
	CLabel_text m_cLb_Usb1;
	CLabel_text m_cLb_Usb2;

	CLabel_text m_LanLabelName;
	CLabel_text m_Usb1LabelName;
	CLabel_text m_Usb2LabelName;

	CListCtrl m_CtrlListMainProcess;
	CLabel_text m_CameraLabelName;
	CLabel_text m_cLb_Camera;
	afx_msg void OnHdnItemclickListMainProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListMainProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListMainProcess(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_pic;
	//afx_msg void OnStnDblclickStaticPic();
	//afx_msg void OnStnClickedStaticPic();
	DECLARE_EVENTSINK_MAP()
	void ClickLabelCamreaName();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	void DblClickLabel(LPDISPATCH Cancel);
	void DblClickLabelOK1(LPDISPATCH Cancel);
	void DblClickLabelOK2(LPDISPATCH Cancel);
	CComboBox m_cComboName[8];
	afx_msg void OnCbnSelchangeComboName1();
	CLabel_text m_cLb_ComMain;
	CLabel_text m_cLb_ComSet;
	CLabel_text m_cLb_ComLed;
	CLabel_text m_cLb_ComMainGmes;
	void DblClickLabelComGmes(LPDISPATCH Cancel);
	void DblClickLabelComMain(LPDISPATCH Cancel);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void ClickLabelOK1();
	void ClickLabelOK2();
	void DblClickLabelCheckTime(LPDISPATCH Cancel);
	void DblClickLabelNgCnt(LPDISPATCH Cancel);
	CLabel_text m_cLabelCableManager;
	CLabel_text m_cLabelCableMessage;
	void DblClickLabelManager(LPDISPATCH Cancel);
	void ClickLabelComGmes();
	void DblClickLabelBarcode(LPDISPATCH Cancel);
	afx_msg void OnBnClickedCheckRunAuto();
	CButton m_CheckRunMode;
};
