
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

#include "DeckLinkAPI_h.h"
#include "dask.h"

#include "ColorStaticST.h"	
#include "ListCtrlEx.h"

#include "ImageProc.h"
#include "BaseImage.h"

#pragma comment(lib, "liblept168")
#pragma comment(lib, "libtesseract302")

using namespace std;
//using namespace cv;
//using namespace tesseract;
#ifdef _DEBUG
//#define TESTMODE_LEVEL_CHANGE
#endif

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

#define DECK_HDMI_SAMPLE_RATE		48000.0
#define DECK_HDMI_SAMPLE_COUNT		1600 // 1024*3
#define DECK_HDMI_CHECK_COUNT		1200

#define AI_NIPCI_9010			0
#define AI_NIPCIe_9330			1
#define AI_ADLINK_PCI_9111		2
#define AI_DECK_HDMI_4K			3

#define VIDEO_MATROX_CORONUS		0
#define VIDEO__DECK_HDMI_4K			1


#define TIME_CHECK_RESERVED_0				0
#define TIME_CHECK_RESERVED_1				1
#define TIME_CHECK_RESERVED_2				2
#define TIME_CHECK_RESERVED_3				3
#define TIME_CHECK_RESERVED_4				4
#define TIME_CHECK_RESERVED_5				5
#define TIME_CHECK_RESERVED_6				6
#define TIME_CHECK_RESERVED_7				7
#define TIME_CHECK_RESERVED_8				8
#define PROCESS_TIME_DELAY_JIG1				9
#define PROCESS_TIME_DELAY_JIG2				10
#define PROCESS_TIME_DELAY_JIG3				11
#define PROCESS_TIME_DELAY_JIG4				12
#define PROCESS_TIME_DELAY_JIG5				13
#define PROCESS_TIME_DELAY_JIG6				14
#define PROCESS_TIME_DELAY_JIG7				15
#define PROCESS_TIME_DELAY_JIG8				16
#define PROCESS_TOTAL_TEST_TIME_1			17
#define PROCESS_TOTAL_TEST_TIME_2			18
#define PROCESS_TOTAL_TEST_TIME_3			19
#define PROCESS_TOTAL_TEST_TIME_4			20
#define PROCESS_TOTAL_TEST_TIME_5			21
#define PROCESS_TOTAL_TEST_TIME_6			22
#define PROCESS_TOTAL_TEST_TIME_7			23
#define PROCESS_TOTAL_TEST_TIME_8			24										 
#define PROCESS_AUTOPROCESS_TEST_TIME_1		25
#define PROCESS_AUTOPROCESS_TEST_TIME_2		26
#define PROCESS_AUTOPROCESS_TEST_TIME_3		27
#define PROCESS_AUTOPROCESS_TEST_TIME_4		28
#define PROCESS_AUTOPROCESS_TEST_TIME_5		29
#define PROCESS_AUTOPROCESS_TEST_TIME_6		30
#define PROCESS_AUTOPROCESS_TEST_TIME_7		31
#define PROCESS_AUTOPROCESS_TEST_TIME_8		32
#define TIME_CHECK_NOSIGNAL_TIME			33
#define TIME_CHECK_NG_OUTPUTL_DELAYTIME		34
											 
// Custom messages							
#define WM_REFRESH_INPUT_STREAM_DATA_MESSAGE	(WM_APP + 1)
#define WM_SELECT_VIDEO_MODE_MESSAGE			(WM_APP + 2)
#define WM_ADD_DEVICE_MESSAGE					(WM_APP + 3)
#define WM_REMOVE_DEVICE_MESSAGE				(WM_APP + 4)
#define WM_ERROR_RESTARTING_CAPTURE_MESSAGE		(WM_APP + 5)
#define WM_REFRESH_INPUT_AUDIO_DATA_MESSAGE		(WM_APP + 6)



#define  _AUDIO_SELECT_NON	0
#define  _AUDIO_SELECT_AUX	1
#define  _AUDIO_SELECT_SPK	2



typedef struct {
	// VITC timecodes and user bits for field 1 & 2
	CString	vitcF1Timecode;
	CString	vitcF1UserBits;
	CString	vitcF2Timecode;
	CString	vitcF2UserBits;

	// RP188 timecodes and user bits (VITC1, VITC2 and LTC)
	CString	rp188vitc1Timecode;
	CString	rp188vitc1UserBits;
	CString	rp188vitc2Timecode;
	CString	rp188vitc2UserBits;
	CString	rp188ltcTimecode;
	CString	rp188ltcUserBits;
} AncillaryDataStruct;





#ifndef __NOHDMI_CAPTURE__
class DeckLinkDevice;
class DeckLinkDeviceDiscovery;
class PreviewWindow;
#endif

class CEnvironmentData;


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

	CString			m_szExePath;

	void LoadRegistrySetting(CEnvironmentData* pCurrentSet);
	void ResetInitRegistrySetting(CEnvironmentData* pCurrentSet);
	void SaveRegistrySetting();
	int  ChangeModelCheckOpen(CString lNewModelName);
	LRESULT  OnChangeModelOpen(WPARAM wParam, LPARAM lParam);
	void SM_ModelOpen(void);
	//void SM_ModelNewOpen(void);
	void OnModelOpen();
	void UpdateInfo(int nIndex, CString s);
	void InitSubClassItem();
//	CEdit			ctrlSuffixEdit;

	CColorStaticST m_stcModelFolder;
	CColorStaticST m_stcRefFolder;
	CColorStaticST m_stcBarCode1;
	CColorStaticST m_stcBarCode2;
	CColorStaticST m_stcChassisName;
	CColorStaticST m_stcSeqName;
	CColorStaticST m_stcMode;
	CColorStaticST m_stcStatus;
	CColorStaticST m_stcTime;
	CColorStaticST m_stcCycleTime;

	int		m_RunCounter;
	int		m_TaskRun;
	int		m_nCurrentNumber;
	int		m_nCurrentProcess;
	int		m_nCurrentStep;
	int		m_WaitCnt ;
	int		m_nNoCurrentRepeatExecution;
	
	int		m_InterProcess;
	int		m_CheckErrorRetry;

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
	void	SendNGSignalToJig(int lON);
	int		m_NG_SignalON;
	


	//CSerialPort m_ComPort;
	//CSerialPort m_ComPortPCB;
	//CSerialPort m_ComPortLED;
	void	ComSend();
	void ComPCBSend();
	//void ComLedRead();
	void	OpenComport();
	void	OpenComportPCB();
	//void	OpenComportLED();
	void OpenComportSCAN();

	int m_MainPAGE_COM_PROCESS;//m_TESTPAGE_COM_PROCESS;
	int m_Main_COM_ID;//m_TESTPAGE_COM_PROCESS;
	int m_Main_RcvCOM_ID;//m_TESTPAGE_COM_PROCESS;
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
	BYTE m_RecvBufTemp[4096];
	int  m_RecvCntTemp;
	//int  m_ComWaitCount;
	void CAcqVoltageSamples_IntClkDlg::GetNextData(int lCnt);
	void CAcqVoltageSamples_IntClkDlg::FindNextStart(int lCnt);

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

	UINT16 m_HdmiAudioDataBuf[DECK_HDMI_SAMPLE_COUNT*8];
	UINT16 m_HdmiAudioData[8][DECK_HDMI_SAMPLE_COUNT];
	UINT m_HdmiAudioCount;
	UINT m_AudioCountBuf[DECK_HDMI_SAMPLE_COUNT];
	UINT m_AudioFameCount;
	UINT m_UpdateAudioData;

	
	void	SendData(BYTE *lbuf, int lcnt);
	void	SendData(BYTE *lbuf, int lcnt, int lComID_Port);
	int m_ComWaitCnt;
	
	BOOL InitDioChannel();
	BOOL SetD_OUT(ULONG lSetVal);
	BOOL ReadD_IN(unsigned long *lReadData);
	void CheckControlInput();
		
	Recomon_ModelT m_RemoconModel;
	BOOL SendIR_Code(CString lCodeString, int lRepeat);
	void SendPreIR_Code(CString lCodeString, int lRepeat);
	void SendAudioSel(int lAudio);
	void SendVideoSel(int lVideo);

	void ReadVolt(int lReadID1);
	int m_ReadMIOComAck;
	double m_VoltData[32];
	double m_ReadVoltData;
	int m_ReadVoltID;

	void ReadSMIO(int lReadID1 = 99);
	void WriteSM_Out(int lReadID1 = 99);

	int m_PrecodeWait;
	BOOL GetRmtCodeList(CString lRmtFile);

	void UartCommandPcbSend();

	//void LEDReadSend();
	//void LEDClearSend();
	//void UP_DIReadSend();
	
	void MessageDisplay(int lError, CString sMessage);



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
	int m_nMeasureWait;
	int m_bMakeReferenceMode;

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

	unsigned long mstartT_1;
	unsigned long mstartT_2;
	unsigned long mstartT_3;
	unsigned long mstartT_4;
	unsigned long mstartT_5;
	unsigned long mstartT_6;
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
	bool SeqFileModified(CString lstrModelname);
	void DisplayTestData();
	void SetListControl();
	void SetSubListControl();
	void InsertStepData2Grid(int nGridType);
	void InitMainGrid(int nGridType);
	void InsertResultData2Grid(int nGridType, int nStepNo);
	void InsertResult2DetailedGrid(int nStepNo);

	void CAcqVoltageSamples_IntClkDlg::InsertMsg2DetailedGrid(int nStepNo, CString sMsg);
	void CAcqVoltageSamples_IntClkDlg::InsertTotalData2Grid(int nGridType, BOOL bResult, CString sElapsedTime);
	void CAcqVoltageSamples_IntClkDlg::InsertPcbid2Grid(CString sWipID);	
	void CAcqVoltageSamples_IntClkDlg::DeleteResultDataFromGrid(int nGridType, int nStepNo);
	void CAcqVoltageSamples_IntClkDlg::DeleteResultDataFromDetailedGrid(int nStepNo);

	int m_LockStatus[500];
	CListCtrlEx  m_CtrlListMainProcessEx;

	int SetFunction(CString lString = "", int lStringIn = 0);
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
	int m_UartREADCnt;
	int m_UartOkAckDataCnt;

	unsigned char m_LEDOkAckData[4];
	unsigned char m_LEDReadData[4];
	unsigned char m_LED_Up_DI_ReadData[4];
	unsigned char m_LED_Up_DO_ReadData[4];
	int m_FanDiPort;
	int m_MIC_Status1;
	int m_MIC_Status2;

	int m_NoAckMainCom;
	int m_MIC_Init;

	int m_bAdjSpecMode;
///////////////////////////////////////////////////////////////////

	void GetApplicationVersion();
	CString m_szVersion;
	CString m_szCurrentStatus ;
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


//	void EdgeGray(cv::Mat *gray, cv::Mat *edge, cv::Mat *outImage);


	CRect rect;
	//CDC memDC;
	//CBitmap Bitmap,*pOldBitmap;
	//CDC *m_pDC;

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
	void GMES_Scan_InformSend();//F11
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
	int m_NG_Retry_Count;
	int m_NG_WaitFlag;

	
	//void SetGuiPos(int Mode);
	void ManualSelchangePort(int lport);

	void AddGmesLog(CString LogStr, int Recv  = 0);
	void AddProcessLog(CString LogStr, int New = 0);
	void AddPCBLog(BYTE *LogData, int Cnt, int Rcv = 0);
	void OnBnClickedButtonFreqSet();

	//void ChangeModel(CString lModel);
	int MessageWindow(CString str);
	CString GetModelList(CString NewName);

	int m_CheckPCB_Com_DelayTime;

public:
		void ComLogClear();
		void ComLog_AddString(CString szString);
		int AppendToLogAndScroll(CString str, COLORREF color = RGB(0, 0, 0));
		void LogDataSave(CString sLogFilePath);
		CStringArray m_strLogArray;
		int GetNumVisibleLines(CRichEditCtrl* pCtrl);
		void InitVersionGrid();
		void UpdateVersionInfo();
	
#ifndef __NOHDMI_CAPTURE__
	void ShowErrorMessage(TCHAR* msg, TCHAR* title);
	void					UpdateAncillaryData(AncillaryDataStruct& ancillaryData);
	
	CStatic					m_previewBox;
	//CStatic					m_previewBox2;
	//CStatic					m_previewBox3;
	PreviewWindow*			m_previewWindow;
	//PreviewWindow*			m_previewWindow2;
	//PreviewWindow*			m_previewWindow3;


	//
	AncillaryDataStruct			m_ancillaryData;
	CCriticalSection			m_critSec; // to synchronise access to the above structure
	DeckLinkDevice*				m_selectedDevice;
	//DeckLinkDevice*				m_selectedDevice2;
	//DeckLinkDevice*				m_selectedDevice3;
	DeckLinkDeviceDiscovery*	m_deckLinkDiscovery;

	int m_CaptureCardEnable;
	int m_CaptureCardReady;

	int video_Wait_Count;
	int ScreenCheck( );
	int ScreenCheck(CString lrefFilename  );
	int m_VideoSignalAlive;

	RgbColor m_BmpColorRef;
	int ScreenColorCheck(CString lrefFilename  ,RgbColor lBmpColorRef  );
	int ScreenRGBTest(CString lCheckFilename, CString lrefFilename, CString lMaskFilename, float &MaxDiffernece, BOOL bUseMaskImage = 0);
	int CAcqVoltageSamples_IntClkDlg::ScreenColorRedCheck(CString lrefFilename  ,RgbColor lBmpColorRef , float lOK_Percent = 20);
	int CAcqVoltageSamples_IntClkDlg::ScreenColorBlueCheck(CString lrefFilename  ,RgbColor lBmpColorRef  , float lOK_Percent = 20);
	int CAcqVoltageSamples_IntClkDlg::ScreenColorGreenCheck(CString lrefFilename  ,RgbColor lBmpColorRef  , float lOK_Percent = 20);
	//int CAcqVoltageSamples_IntClkDlg::ScreenColorRGBheck(CString lrefFilename  ,RgbColor lBmpColorRef  , float lOK_Percent = 20);
	int CAcqVoltageSamples_IntClkDlg::ScreenMovingPicCheck();


	void RefreshHDMI();

	void SetInputVideo( int DisplayNo);

	CString m_strRef_IMGfile;
	CString m_strFail_IMGfile;
	int m_DisplayRetryCount;

	RECT m_Rect_Image;
	int m_Image_SaveMode;
		
	unsigned int m_Start_x;
	unsigned int m_Start_y;
	unsigned int m_End_x;
	unsigned int m_End_y;
	unsigned int m_Width_x;
	unsigned int m_Height_y;
	int m_SettingMode;

	// Internal helper methods
	void					EnableInterface(bool enabled);
	void					RefreshVideoModeList();
	//void					RefreshVideoModeList2();
	//void					RefreshVideoModeList3();
	void					StartCapture();
	//void					StartCapture2();
	//void					StartCapture3();
	void					StopCapture();		
	//void					StopCapture2();
	//void					StopCapture3();
	void					AddDevice(IDeckLink* deckLink);
	void					RemoveDevice(IDeckLink* deckLink);
	
	
	void NewDeviceSelect();

	void CaptureControl(int lon);


	void SetRange( int lDisplayFlag,int lDisplayOK, CRect rect);
	void SetRangeColor( int lDisplayOK);
	void ClearRange();

	BYTE*			 m_pImageData;
	int		m_ImageWidth;
	int		m_ImageHeight;
	int		m_ImageSize;
	int Moving_Pic_Count;
	//m_pImageData = new BYTE[m_InfoHeader.biSizeImage];
	//if(m_pImageData != NULL){ delete m_pImageData; m_pImageData = NULL; }
	int ScreenCapture( CString lSaveFileName, CString lRefFileName, int lSave = 0);
	int ScreenCapture();
	int CompareImage(CString lrefFilename ,CRect rect);
	int CompareImage(CString lcheckFilename, CString lrefFilename, CRect rect  );
	void SaveAsImage();
//	int ScreenCapture();
//	int CompareImage(CString lrefFilename ,CRect rect);

	void CAcqVoltageSamples_IntClkDlg::SetGrabInfo(CBaseImage* pBaseImage);
		// UI-related handlers
#endif	

	
	afx_msg void			OnNewDeviceSelected();
	afx_msg void			OnStartStopBnClicked();
	//afx_msg void			OnClose();

	// Custom message handlers
	afx_msg LRESULT			OnRefreshInputStreamData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT			OnSelectVideoMode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT			OnAddDevice(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT			OnRemoveDevice(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT			OnErrorRestartingCapture(WPARAM wParam, LPARAM lParam);

public:
	void SetUSBSel(int Sel1, int Sel2);
	BOOL GetResultFromDetailedGrid(int nStepNo, CString& sMsg);
	void RunTestStart();
public:
     afx_msg void OnBnClickedStart();
	 afx_msg long OnReceiveData(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataPCB(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataLED(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataEthernet(WPARAM wParam, LPARAM lParam);
	 afx_msg long OnReceiveDataSCAN(WPARAM wParam, LPARAM lParam);

	 afx_msg long OnRefreshAudioData(WPARAM wParam, LPARAM lParam);
	

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
	//public:
	//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStopButton();
	CString m_ChnnelName[8];
	int m_SelectAudio; 

	CLabel_text m_BarCode;
	//CLabel_text m_BarCodeMark;
	

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
	CBitmapButton m_cNewModelButton;
	CBitmapButton m_cStopButton;
	CBitmapButton m_cTestButton;
	CBitmapButton m_cRefButton;
	CBitmapButton m_cExitButton;
	CBitmapButton m_cBtnSyntax;
	CBitmapButton m_cBtnOption;
	CBitmapButton m_cBtnView;



	CComboBox				m_deviceListCombo;	
	CComboBox m_modeListCombo;
	//CComboBox m_modeListCombo2;
	//CComboBox m_modeListCombo3;


	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
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
//	CStatic m_pic;
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
	afx_msg void OnCbnSelchangeComboName2();
	afx_msg void OnCbnSelchangeComboName3();
	afx_msg void OnCbnSelchangeComboName4();
	afx_msg void OnCbnSelchangeComboName5();
	afx_msg void OnCbnSelchangeComboName6();
	afx_msg void OnCbnSelchangeComboName7();
	afx_msg void OnCbnSelchangeComboName8();

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
	afx_msg void OnBnClickedStopCaptureButton();
	//CLabel_text m_cLbDisplayMark;

	
	void ClickLabelImageSet();
	void ClickLabelImageSaveAs();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	CLabel_text m_cLB_ImageSet;
	CLabel_text m_cLB_ImageSaveAs;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DblClickLabelBarcodeMark(LPDISPATCH Cancel);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CButton m_cCheckDisplayContinue;
	BOOL m_bCheckDisplayContinue;
	afx_msg void OnBnClickedCheckDisplayContinue();
	CRichEditCtrl m_ctrlEditComLog;
	CListCtrl m_CtrlListVersionProcess;
	afx_msg void OnNMCustomdrawListVersionProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListMainProcess(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedOptButton();
	void ClickLabelName1();
	void ClickLabelName2();
	void ClickLabelName3();
	void ClickLabelName4();
	afx_msg void OnBnClickedSyntaxButton();
	afx_msg void OnBnClickedViewButton();

	afx_msg void OnBnClickedNewButton();
	afx_msg void OnBnClickedRefButton();
};
