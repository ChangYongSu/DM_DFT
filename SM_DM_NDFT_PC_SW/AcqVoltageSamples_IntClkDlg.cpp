/******************************************************************************
*
* Example program:
*   AcqVoltageSamples_IntClk
*
* Category:
*   AI
*

******************************************************************************/

// AcqVoltageSamples_IntClkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgTestPage.h"

#include "AcqVoltageSamples_IntClkDlg.h"
//#include "DlgModelSetup.h"
#include "MesDb.h"
#include "FileControl.h"
#include "TlHelp32.h"
#include <direct.h>
//#include "DlgModelSetupSeq.h"

#include "IcmpEcho.h"
//#include "ping.h"

//#include "DlgImage.h"

#include "DeckLinkDevice.h"

#include "time.h" 


#include "CableChangeDlg.h"
#include "DlgPassword.h"
#include "OptionDlg.h"
#include "Global.h"
#include "TVCommCtrl.h"

#include "parser.h"
#include "step.h"
#include "CSelectChassisModelDlg.h"
#include "CSelectGenerateModel.h"
#include "CurrentSetting.h"
#include "AvSwitchBoxCtrl.h"

#include "BaseImage.h"
#include "ImageProc.h"
#include "realmeas.h"
#include "SMDIO_Jig_Ctrl.h"


CColorStaticST  ctrlStepMeasur_A;
CCurrentSetting	g_CurSetting;
clock_t			StepStart;

CImageProc		g_ImageProc;
CBaseImage		g_GrabImage;
CBaseImage		g_RefImage;
CBaseImage		g_MaskImage;


/////////////////////////////////////////////////////////////////////////////
// CEnvironmentData

CEnvironmentData::CEnvironmentData()
{
	nTotalLine = 0; 				// TOTAL LINES & TOTAL STEPS
	nTotalStep = 0;
	nTotalProduct = 0;		        // Total Products & OK Product
	nOKProduct = 0;
	nRunType = 0;              	// Current Run Mode 
	nDisplayType = 0;				// Current Display type	0 : Main Grid -> Normal Grid, 1 : Main Grid -> Detailed Grid
	nPrintType = 0;				// Current Print Out type
	nStepKey = 0;				// StepKey
	lTime = 0;       			// Last Compile Time

	bIsRunning = FALSE;			// Running state
	bRunAbort = FALSE;			// User abort key
	bSystemBreak = FALSE;            // System break
	bCompiled = FALSE;			// Parsing result
	bCommDisplay = FALSE;			// rs232 통신내용 Display
	bIsRunMsg = FALSE;			// thread 에서 실행 메세지를 보냈는지 여부
	bSaveGrabImg = FALSE;			// TRUE : Auto Save Grab Image
	bSaveProcImg = FALSE;			// TRUE : Auto Save Processed Image

	bSaveCaptionTestImg = FALSE;
	bSaveMovingPicTestImg = FALSE;
	bSaveIntermediateImage = FALSE;

	//+del kwmoon 080716
//	bSaveDistributionTable = FALSE;

	//+add kwmoon 080710
	bSaveProcessingTimeData = FALSE;

	//+add kwmoon 080716
	bSaveReviewData = FALSE;
	bSaveDetailResultData = FALSE;

	bSaveResult2Txt = FALSE;			// Save Result to Text File
	bSaveResult2Html = TRUE;// FALSE;	// Save Result to Html File
	bSaveResult2Csv = FALSE;			// Save Result to Csv File
	//-
	nNoRepeatExecution = 1;				// Save Number of repeat execution

	//+del kwmoon 080715
//	nNoAllowedErrorPixel = 0;

	//+change kwmoon 080925
//	nNoFrameForRefImageCreation = 2;
	nNoFrameForRefImageCreation = 1;

	nPixelInMiddleRange = 0;
	nNonBlackPixel = 0;

	//+add 090218(Modification No1)
	nNoUsedColors = 0;

	//+del kwmoon 080715
//	nNoAllowedErrorPixelForOsdTest = 0;

	nDelayPercentage = 100;

	//------------------
	// File/Folder Path
	//------------------
	sSeqPath = _T("");
	sFullSeqPath = _T("");
	sRemoconTitle = _T("");
	sPatternTitle = _T("");
	sViewerPath = _T("");
	sTestParamIni = _T("");
	sModelIni = _T("");
	sModelFolder = _T("");
	sGrabFolder = _T("");
	sRefFolder = _T("");
	sMaskFolder = _T("");
	sResultFolder = _T("");
	sResultPath = _T("");

	//+add kwmoon 080716
	sDetailResultDataPath = _T("");

	//+add kwmoon 081024
	sModelListPath = _T("");

	//	nLvdsWidth		= 0;				// Uranous Grabber Width
	//	nLvdsHeight		= 0;				// Uranous Grabber Height
	nAnalogWidth = 0;				// Matrox Analog Grabber(Cronos+) Width
	nAnalogHeight = 0;				// Matrox Analog Grabber(Cronos+) Height

	//------------------
	// COM Port
	//------------------
	sPatternComPort = _T("");
	sTVComPort = _T("");
	sAvSwitchBoxComPort = _T("");
	sScannerComPort = _T("");
	sIrChkComPort = _T("");
	sHDMIRoiShape = _T("");

	wPatternBaudRate = 0;
	//+change kwmoon 080804
//	wTVBaudRate				= 0;
	wTVBaudRate = 57600;
	nTVParity = EVENPARITY;
	wAvSwitchBoxBaudRate = 0;
	wScannerBaudRate = 0;
	wIrChkBaudRate = 0;

	bUsePatternGen = FALSE;
	bUseTVCommPort = TRUE;
	bUseAVSwitchBox = FALSE;
	bUseScanner = FALSE;

//	nAdcType = ADC_TYPE_RS232C;
	nAudioSource = 0;					// Audio Input Source 0: LineIn, 1: DigitalIn
//	nUranousMode			= 0;
//	nBitCount				= 0;
//	nTotalNoTest			= 0;
//	nTotalNoNg				= 0;

	//+ change kwmoon 080724
	//for (int i = 0; i < NO_SOURCE_TYPE; i++)
	//{
	//	nSrcMargin[i] = 0;
	//}

	nNoRetry = 0;
	bTVCommPortEcho = FALSE;

	//------------------
	// MES Data
	//------------------
	nLocation = 0;		//Location 0 : LG-PRI, 1 : LG-DD, 2 : JINSUNG, 3 : SG TECH
	nLineNo = 1;		//Line Number 1 ~ 10
	nSystemNo = 1;		//System Number 1 ~ 10
	nAuthority = 0;		//Authority 0 : Developer, 1 : Administrator, 2 : Operator
	strPassword = _T("");	// Developer : Password "5555" , Administrator : Password "DFT"
									// Operator : No Password
	strUserId = _T("");
	//	strMesDsn			= _T("");
	//	strMesUserId		= _T("");
	//	strMesPassWord		= _T("");
	bAutoUploadMes = FALSE;
	bUploadMes = FALSE;
	bGMES_Connection = FALSE;
	bAutoGMES_ChangeModel = FALSE;

	//	sToolOption1		= _T("");
	//	sToolOption2		= _T("");
	//	sToolOption3		= _T("");
	//	sToolOption4		= _T("");
	//	sToolOption5		= _T("");
	//	sAreaOption1		= _T("");

	sBE_Version = _T("");
	sFE_Version = _T("");
	sMicom_Version = _T("");
	sDSP_Version = _T("");
	sSubDSP_Version = _T("");
	sEQ_Version = _T("");
	sMEQ_Version = _T("");
	sTouch_Version = _T("");
	sDemo_Version = _T("");
	sDJSound_Version = _T("");
	sWirelessTx_Version = _T("");
	sWirelessRx_Version = _T("");
	sWoofer_Rx_Version = _T("");
	sRear_Kit_Rx_Version = _T("");
	sRear_SPK_L_Version = _T("");
	sRear_SPK_R_Version = _T("");
	sChecksum = _T("");
	nAudioGenFreq[0] = 1000;
	nAudioGenFreq[1] = 400;
	nAudioGenFreq[2] = 1000;
	nAudioGenFreq[3] = 400;
	nAudioGenFreq[4] = 1000;
	nAudioGenFreq[5] = 400;
	nAudioGenFreq[6] = 1000;
	nAudioGenFreq[7] = 400;
	nAudioGenFreq[8] = 1000;
	nAudioGenFreq[9] = 400;
	nAudioGenFreq[10] = 1000;
	nAudioGenFreq[11] = 400;

	nAudioCheckMethod = 1;
	//	nFullHd120Hz		= 0; // 0 :
	// add 091214
	//	nImageRotation		= 0;

		//+add kwmoon 080715
	fAllowedBandErrorPixelPercentage[0] = 0.0f;
	fAllowedBandErrorPixelPercentage[1] = 0.0f;
	fAllowedBandErrorPixelPercentage[2] = 0.0f;
	fAllowedBandErrorPixelPercentage[3] = 0.0f;
	fAllowedBandErrorPixelPercentage[4] = 0.0f;

	//+add kwmoon 080716
	nLevelMargin = 45;

	//+add kwmoon 080819
	nFreqMargin = 15;

	//+add kwmoon 080724
	//for (int i = 0; i < NO_SOURCE_TYPE; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		nAudioSpec[i][j] = 0;
	//	}
	//}

	bUseIrChk = 0;

	//+add PSH 100310
	nHDMIResolution = 0;
	nHDMIBitSpec = 0;

	bAvSwitchBoxBuzzerMute = 1;
	nAvSwitchBoxInitVideoCh = 0;
	nUseUserRetry = 0;
	bVersionCheckOnly = FALSE;
	sOrganizationID = _T("");
	sLineID = _T("");
	sEquipmentID = _T("");
	sOperationID = _T("");
	sModelID = _T("");
	sModelName_GMES = _T("");
	sModelSuffix = _T("");
	nDftSeq = 0;

	nChipType = 0x01;
	nProcessType = 0;
	sFixtureId = _T("");
	sMacAdd = _T("");
	nModelInfo_Check = 0;
	bFixtureIdCheck = TRUE;
	bMacAddCheck = FALSE;

	//sWifiMacAdd;
	bWifiMacAddCheck = FALSE;
	//sBTMacAdd;
	bBTMacAddCheck = FALSE;
	


	
}

//CEnvironmentData *CurrentSet;

CIniAccess		m_Ini;
int				g_nStepSize;
HWND			g_hCommWnd;

CStringArray g_Divisions;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg;


UINT threadCapture(LPVOID pParam)
{
//	CDlgImage* dlg = (CDlgImage*) pParam;

	//if(m_Camera_Capture_Flag ==1)
//	{

	//	while(!gbShutdown)
	//	{
	//		vcap >> gCuptureimage;
	//		gbCapture = FALSE;

	//		//cvShowImage("Video",dlg->image);
	//		//if ( bCapture )
	//		//{
	//		//	//dlg->src = &IplImage(dlg->image);
	//		//	gsrc_Mat = gCuptureimage;

	//		//	dlg->bCapture = false;
	//		//}

	//		Sleep(5);
	//		g_CameraCount++;
	//		if(g_CameraCount > 1000000)
	//			g_CameraCount = 0;
	//	}

	//}
	return 0;
}


void LoadStringVectorInComboBox(CComboBox& comboBox, const CNiStringVector& strings)
{
    for (unsigned long i = 0; i < strings.GetSize(); ++i)
        comboBox.AddString(strings[i]);
}

// CAcqVoltageSamples_IntClkDlg dialog
CAcqVoltageSamples_IntClkDlg::CAcqVoltageSamples_IntClkDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CAcqVoltageSamples_IntClkDlg::IDD, pParent)
 ///   m_minimum(_T("-5.0")),
  //  m_maximum(_T("5.0")),
  //  m_samplesPerChannel(_T("3000")),
 //   m_rate(_T("100000.0")
	
 , m_bCheckDisplayContinue(FALSE)
{

	

    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_colors[0] = CNiColor(0, 255, 0);
    m_colors[1] = CNiColor(255, 0, 0);
    m_colors[2] = CNiColor(0, 0, 255);
    m_colors[3] = CNiColor(255, 255, 0);
    m_colors[4] = CNiColor(0, 255, 255);
    m_colors[5] = CNiColor(255, 0, 255);
    m_colors[6] = CNiColor(128, 128, 128);
    m_colors[7] = CNiColor(255, 255, 255);
	/*m_ChnnelName[0] = _T("");
	m_ChnnelName[1] = _T("");
	m_ChnnelName[2] = _T("");
	m_ChnnelName[3] = _T("");
	m_ChnnelName[4] = _T("");
	m_ChnnelName[5] = _T("");*/
	

	m_TaskRun = 0;
	m_RunCounter = 0;

	m_PreRunCounter = 0;
	m_PreTaskRun = 0;
	m_nPreCurrentNumber = 0;
		
	m_pUDPSocket  = NULL;

	m_strCameraCheckIMGfile =  _T("btok.jpg");

	m_CheckDelayTime = 1000;
	m_HdmiAudioCount = 0;
	m_AudioFameCount = 0;
	memset(m_avg_PPVoltage, 0, sizeof(m_avg_PPVoltage));//[i][(m_RunCounter / 6) % 3] = m_PPVoltage[i];
	memset(m_avg_Freg, 0, sizeof(m_avg_Freg));//m_avg_Freg[i][(m_RunCounter / 6) % 3] = m_Frequency[i];

	memset(m_PPVoltage, 0, sizeof(m_PPVoltage));
	memset(m_Frequency, 0, sizeof(m_Frequency));
	m_RecvCntTemp = 0;
	m_RecvCnt = 0;
	m_bAdjSpecMode = FALSE;
	m_pImageData = NULL;

	m_bMakeReferenceMode = 0;

}



void CAcqVoltageSamples_IntClkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_PHYSICAL_CHANNEL_COMBO, m_physicalChannel);
	//DDX_Text(pDX, IDC_MINIMUM_EDIT, m_minimum);
	//DDX_Text(pDX, IDC_MAXIMUM_EDIT, m_maximum);
	//DDX_Text(pDX, IDC_SAMPLES_PER_CHANNEL_EDIT, m_samplesPerChannel);
	//DDX_Text(pDX, IDC_RATE_EDIT, m_rate);
	//	DDX_Control(pDX, IDC_START_BUTTON, m_startButton);
	DDX_Control(pDX, IDC_CWGRAPH0, m_graph[0]);
	DDX_Control(pDX, IDC_CWGRAPH1, m_graph[1]);
	DDX_Control(pDX, IDC_CWGRAPH2, m_graph[2]);
	DDX_Control(pDX, IDC_CWGRAPH3, m_graph[3]);
	DDX_Control(pDX, IDC_CWGRAPH4, m_graph[4]);
	DDX_Control(pDX, IDC_CWGRAPH5, m_graph[5]);
	DDX_Control(pDX, IDC_CWGRAPH6, m_graph[6]);
	DDX_Control(pDX, IDC_CWGRAPH7, m_graph[7]);


	DDX_Control(pDX, IDC_LABEL_HZ1, m_FreqLabel[0]);
	DDX_Control(pDX, IDC_LABEL_HZ2, m_FreqLabel[1]);
	DDX_Control(pDX, IDC_LABEL_HZ3, m_FreqLabel[2]);
	DDX_Control(pDX, IDC_LABEL_HZ4, m_FreqLabel[3]);
	DDX_Control(pDX, IDC_LABEL_HZ5, m_FreqLabel[4]);
	DDX_Control(pDX, IDC_LABEL_HZ6, m_FreqLabel[5]);
	DDX_Control(pDX, IDC_LABEL_HZ7, m_FreqLabel[6]);
	DDX_Control(pDX, IDC_LABEL_HZ8, m_FreqLabel[7]);


	DDX_Control(pDX, IDC_LABEL_VOLT1, m_VoltLabel[0]);
	DDX_Control(pDX, IDC_LABEL_VOLT2, m_VoltLabel[1]);
	DDX_Control(pDX, IDC_LABEL_VOLT3, m_VoltLabel[2]);
	DDX_Control(pDX, IDC_LABEL_VOLT4, m_VoltLabel[3]);
	DDX_Control(pDX, IDC_LABEL_VOLT5, m_VoltLabel[4]);
	DDX_Control(pDX, IDC_LABEL_VOLT6, m_VoltLabel[5]);
	DDX_Control(pDX, IDC_LABEL_VOLT7, m_VoltLabel[6]);
	DDX_Control(pDX, IDC_LABEL_VOLT8, m_VoltLabel[7]);

	DDX_Control(pDX, IDC_LABEL__NAME1, m_NameLabel[0]);
	DDX_Control(pDX, IDC_LABEL__NAME2, m_NameLabel[1]);
	DDX_Control(pDX, IDC_LABEL__NAME3, m_NameLabel[2]);
	DDX_Control(pDX, IDC_LABEL__NAME4, m_NameLabel[3]);
	DDX_Control(pDX, IDC_LABEL__NAME5, m_NameLabel[4]);
	DDX_Control(pDX, IDC_LABEL__NAME6, m_NameLabel[5]);
	DDX_Control(pDX, IDC_LABEL__NAME7, m_NameLabel[6]);
	DDX_Control(pDX, IDC_LABEL__NAME8, m_NameLabel[7]);


	DDX_Control(pDX, IDC_LABEL_MESSAGE, m_MessageDisplay);

	DDX_Control(pDX, IDC_START_BUTTON, m_cBtnStart);

	DDX_Control(pDX, IDC_SETUP_BUTTON, m_cSetupButton);
	DDX_Control(pDX, IDC_NEW_BUTTON, m_cNewModelButton);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_cStopButton);
	DDX_Control(pDX, IDC_TEST_BUTTON, m_cTestButton);
	DDX_Control(pDX, IDC_REF_BUTTON, m_cRefButton);
	DDX_Control(pDX, IDOK, m_cExitButton);




	DDX_Control(pDX, IDC_PREVIEW_BOX, m_previewBox);
	DDX_Control(pDX, IDC_INPUT_DEVICE_COMBO, m_deviceListCombo);
	DDX_Control(pDX, IDC_INPUT_MODE_COMBO, m_modeListCombo);
	//	DDX_Control(pDX, IDC_INPUT_MODE_COMBO2, m_modeListCombo2);
	//	DDX_Control(pDX, IDC_INPUT_MODE_COMBO3, m_modeListCombo3);
	//	DDX_Control(pDX, IDC_TEXTBOX_MODEL, m_TextModel);

	DDX_Control(pDX, IDC_LABEL_BARCODE, m_BarCode);
	//DDX_Control(pDX, IDC_LABEL_BARCODE_MARK, m_BarCodeMark);
	DDX_Control(pDX, IDC_LABEL_MODEL, m_cLbModel);
	DDX_Control(pDX, IDC_LABEL__OKNG, m_cLbOkNg);
	//	DDX_Control(pDX, IDC_LABEL__OKNG1, m_cLb_Test1);
	//	DDX_Control(pDX, IDC_LABEL__OKNG2, m_cLb_Test2);
	//	DDX_Control(pDX, IDC_LABEL__OKNG3, m_cLb_Test3);

	DDX_Control(pDX, IDC_LABEL_OK_LAN, m_cLb_Lan);
	DDX_Control(pDX, IDC_LABEL_USB1, m_cLb_Usb1);
	DDX_Control(pDX, IDC_LABEL_USB2, m_cLb_Usb2);

	DDX_Control(pDX, IDC_LABEL_LAN_NAME, m_LanLabelName);
	DDX_Control(pDX, IDC_LABEL_USB1_NAME, m_Usb1LabelName);
	DDX_Control(pDX, IDC_LABEL_USB2_NAME, m_Usb2LabelName);

	//GetDlgItem(IDC_LABEL_CHECK_TIME)->SetWindowPos(NULL,1236, 690, 80,15,SWP_ASYNCWINDOWPOS);
	//GetDlgItem(IDC_LABEL_CYCLE_TIME)->SetWindowPos(NULL,1236, 705, 80,15,SWP_ASYNCWINDOWPOS);

	DDX_Control(pDX, IDC_LABEL_CHECK_TIME, m_CheckTimeLabel);
	DDX_Control(pDX, IDC_LABEL_CYCLE_TIME, m_CycleTimeLabel);

	DDX_Control(pDX, IDC_LABEL_CHECK_TIME_NAME, m_CheckTimeLabelName);
	DDX_Control(pDX, IDC_LABEL_CYCLE_TIME_NAME, m_CycleTimeLabelName);
	//DDX_Control(pDX, IDC_LABEL_HZ1, m_clbHz);
	/*
	CLabel_text ;
	CLabel_text ;
	CLabel_text m_OKCntLabelName;
	CLabel_text m_NGLabelName;//
	*/
	DDX_Control(pDX, IDC_LABEL_OK_CNT, m_OKCntLabel);
	DDX_Control(pDX, IDC_LABEL_NG_CNT, m_NGCntLabel);

	DDX_Control(pDX, IDC_LABEL_OK_CNT_NAME, m_OKCntLabelName);
	DDX_Control(pDX, IDC_LABEL_NG_CNT_NAME, m_NGCntLabelName);
	DDX_Control(pDX, IDC_LIST_MAIN_PROCESS, m_CtrlListMainProcess);
	DDX_Control(pDX, IDC_LABEL_CAMREA_NAME, m_CameraLabelName);
	DDX_Control(pDX, IDC_LABEL_CAMERA, m_cLb_Camera);
	//	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
	DDX_Control(pDX, IDC_COMBO_NAME_1, m_cComboName[0]);
	DDX_Control(pDX, IDC_COMBO_NAME_2, m_cComboName[1]);
	DDX_Control(pDX, IDC_COMBO_NAME_3, m_cComboName[2]);
	DDX_Control(pDX, IDC_COMBO_NAME_4, m_cComboName[3]);
	DDX_Control(pDX, IDC_COMBO_NAME_5, m_cComboName[4]);
	DDX_Control(pDX, IDC_COMBO_NAME_6, m_cComboName[5]);
	DDX_Control(pDX, IDC_COMBO_NAME_7, m_cComboName[6]);
	DDX_Control(pDX, IDC_COMBO_NAME_8, m_cComboName[7]);

	DDX_Control(pDX, IDC_LABEL_COM_MAIN, m_cLb_ComMain);
	DDX_Control(pDX, IDC_LABEL_COM_SET, m_cLb_ComSet);
	DDX_Control(pDX, IDC_LABEL_COM_LED, m_cLb_ComLed);
	DDX_Control(pDX, IDC_LABEL_COM_GMES, m_cLb_ComMainGmes);
	DDX_Control(pDX, IDC_LABEL_MANAGER, m_cLabelCableManager);
	DDX_Control(pDX, IDC_LABEL_MASSAGE, m_cLabelCableMessage);
	//	DDX_Control(pDX, IDC_LABEL_DISPLAY_MARK, m_cLbDisplayMark);
	DDX_Control(pDX, IDC_LABEL_IMAGE_SET, m_cLB_ImageSet);
	DDX_Control(pDX, IDC_LABEL_IMAGE_SAVE_AS, m_cLB_ImageSaveAs);
	DDX_Control(pDX, IDC_CHECK_DISPLAY_CONTINUE, m_cCheckDisplayContinue);
	DDX_Check(pDX, IDC_CHECK_DISPLAY_CONTINUE, m_bCheckDisplayContinue);
	DDX_Control(pDX, IDC_COM_DEBUG_LOG, m_ctrlEditComLog);
	DDX_Control(pDX, IDC_LIST_VERSION_PROCESS, m_CtrlListVersionProcess);
	DDX_Control(pDX, IDC_SYNTAX_BUTTON, m_cBtnSyntax);
	DDX_Control(pDX, IDC_OPT_BUTTON, m_cBtnOption);
	DDX_Control(pDX, IDC_VIEW_BUTTON, m_cBtnView);
}


BEGIN_MESSAGE_MAP(CAcqVoltageSamples_IntClkDlg, CDialog)
    //{{ AFX_MSG_MAP
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}} AFX_MSG_MAP
    ON_BN_CLICKED(IDC_START_BUTTON, OnBnClickedStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedStopButton)
	ON_BN_CLICKED(IDC_SETUP_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedSetupButton)
	ON_BN_CLICKED(IDC_TEST_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedTestButton)
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveData)
	ON_MESSAGE(WM_COMM_RXCHAR_PCB,OnReceiveDataPCB)
	ON_MESSAGE(WM_COMM_RXCHAR_LED,OnReceiveDataLED)
	ON_MESSAGE(WM_COMM_RXCHAR_ETHERNET, OnReceiveDataEthernet)
	ON_MESSAGE(WM_COMM_RXCHAR_SCAN,OnReceiveDataSCAN)

	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CAcqVoltageSamples_IntClkDlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CAcqVoltageSamples_IntClkDlg::OnHdnItemclickListMainProcess)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MAIN_PROCESS, &CAcqVoltageSamples_IntClkDlg::OnNMClickListMainProcess)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MAIN_PROCESS, &CAcqVoltageSamples_IntClkDlg::OnNMCustomdrawListMainProcess)
//	ON_STN_DBLCLK(IDC_STATIC_PIC, &CAcqVoltageSamples_IntClkDlg::OnStnDblclickStaticPic)
//	ON_STN_CLICKED(IDC_STATIC_PIC, &CAcqVoltageSamples_IntClkDlg::OnStnClickedStaticPic)
	ON_WM_RBUTTONDBLCLK()
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_1, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName1)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_2, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName2)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_3, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName3)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_4, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName4)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_5, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName5)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_6, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName6)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_7, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName7)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_8, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName8)
	ON_WM_RBUTTONDOWN()				
	ON_WM_RBUTTONUP()

	

	ON_BN_CLICKED(IDC_START_STOP_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnStartStopBnClicked)
	
	ON_CBN_SELCHANGE(IDC_INPUT_DEVICE_COMBO, &CAcqVoltageSamples_IntClkDlg::OnNewDeviceSelected)

	// Custom messages
	ON_MESSAGE(WM_REFRESH_INPUT_STREAM_DATA_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnRefreshInputStreamData)
	ON_MESSAGE(WM_SELECT_VIDEO_MODE_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnSelectVideoMode)
	ON_MESSAGE(WM_ADD_DEVICE_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnAddDevice)
	ON_MESSAGE(WM_REMOVE_DEVICE_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnRemoveDevice)
	ON_MESSAGE(WM_ERROR_RESTARTING_CAPTURE_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnErrorRestartingCapture)

	ON_MESSAGE(WM_REFRESH_INPUT_AUDIO_DATA_MESSAGE, &CAcqVoltageSamples_IntClkDlg::OnRefreshAudioData)


	ON_BN_CLICKED(IDC_STOP_CAPTURE_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedStopCaptureButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_CONTINUE, &CAcqVoltageSamples_IntClkDlg::OnBnClickedCheckDisplayContinue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_VERSION_PROCESS, &CAcqVoltageSamples_IntClkDlg::OnNMCustomdrawListVersionProcess)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MAIN_PROCESS, &CAcqVoltageSamples_IntClkDlg::OnNMDblclkListMainProcess)
	ON_BN_CLICKED(IDC_OPT_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedOptButton)
	ON_BN_CLICKED(IDC_SYNTAX_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedSyntaxButton)
	ON_BN_CLICKED(IDC_VIEW_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedViewButton)
	ON_BN_CLICKED(IDC_NEW_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedNewButton)
	ON_BN_CLICKED(IDC_REF_BUTTON, &CAcqVoltageSamples_IntClkDlg::OnBnClickedRefButton)
END_MESSAGE_MAP()

int GetProcessList(CString lcurname, int MaxNum)
{
	CString lfname;
    int Index = 0;
    HANDLE         hProcessSnap = NULL;
    DWORD          Return       = FALSE;
    PROCESSENTRY32 pe32         = {0};

    //프로세스의 스냅샷을 생성한다.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return 0; 

    pe32.dwSize = sizeof(PROCESSENTRY32);

    //시스템의 모든 프로세스를 가져와 processName와 이름이 같은 것의 카운트를 리턴.
    if (Process32First(hProcessSnap, &pe32))
    {
        DWORD Code = 0;
        DWORD         dwPriorityClass;        

        do
        {
            HANDLE hProcess; 

            // Get the actual priority class.
            hProcess = OpenProcess (PROCESS_ALL_ACCESS,
                FALSE, pe32.th32ProcessID);
            dwPriorityClass = GetPriorityClass (hProcess);              

            if (Index < MaxNum)
            {
                //pProcessList[Index].ProcessName = pe32.szExeFile;
                lfname = pe32.szExeFile;
				if(lfname == lcurname)
				{
					Index++;
				}
            }

            CloseHandle (hProcess);      

        }
        while (Process32Next(hProcessSnap, &pe32));
    } 

    else
        return 0;
           // could not walk the list of processes 

    // Do not forget to clean up the snapshot object.
    CloseHandle (hProcessSnap);

    return Index;

}
//BOOL CAcqVoltageSamples_IntClkDlg::PreCreateWindow(CREATESTRUCT& cs)
//{
//
//	if (!CDialog::PreCreateWindow(cs))
//		return FALSE;
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if (g_nRunningProcessNo == 1)
//	{
//		cs.x = 0;
//		cs.y = 0;
//	}
//	else
//	{
//		cs.x = 960;
//		cs.y = 0;
//	}
//
//	cs.cx = 960;
//	cs.cy = 1080;
//
//	return CDialog::PreCreateWindow(cs);
//}
BOOL CAcqVoltageSamples_IntClkDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if(pMsg->wParam == VK_RETURN)
		{
			//ClickCbtnStart();
			if(m_BarcodeString.GetLength() > 6)
			{
				//m_WipID = m_BarcodeString;
			}
			m_BarcodeString = _T("");
			return TRUE;
		}
	}		
	else if(pMsg->message == WM_CHAR)
	{
		m_BarcodeString = m_BarcodeString  + (char)(pMsg->wParam);
		m_BarcodeString.MakeUpper();
		m_BarCode.put_Caption(m_BarcodeString);
		return TRUE;		
	}	
	else if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(m_TaskRun != TASK_RUN_IDLE)
		{
			RECT lRect;
			m_CtrlListMainProcess.GetWindowRect(&lRect);
		
			if((lRect.bottom > pMsg->pt.y)&&(lRect.top < pMsg->pt.y)
				&&(lRect.left < pMsg->pt.x)&&(lRect.right > pMsg->pt.x))
			{
				return TRUE;
			}
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}
//void CAcqVoltageSamples_IntClkDlg::GetApplicationVersion()
//{
//	CString sSwVer, sHwVer;
//
//	LPVOID lpBuffer;
//	UINT uiLen;
//	char caAppName[20];
//	strcpy(caAppName, AfxGetApp()->m_pszExeName);
//	strcat(caAppName, ".exe");
//
//	DWORD dwInfoSize = GetFileVersionInfoSize(caAppName, NULL);
//	LPVOID lpVersionInfo = new BYTE[dwInfoSize];
//
//	GetFileVersionInfo(caAppName, 0, dwInfoSize, lpVersionInfo);
//	VerQueryValue(lpVersionInfo, TEXT("\\StringFileInfo\\040904b0\\ProductVersion"), &lpBuffer, &uiLen);
//
//	char *pcVer = new char[uiLen + 1];
//	strncpy(pcVer, (char *)lpBuffer, uiLen);	// Product Version
//	m_szVersion.Format("%s", pcVer);
//
//	m_szCurrentStatus = m_szVersion;
//
//	CAcqVoltageSamples_IntClkDlg* pMainFrame = (CAcqVoltageSamples_IntClkDlg*)AfxGetMainWnd();
//	pMainFrame->SetWindowTextA(m_szCurrentStatus);
//
//	delete[] pcVer;
//
//	//+add 090226(Modification No2)
//	delete[] lpVersionInfo;
//}

void CAcqVoltageSamples_IntClkDlg::ResetInitRegistrySetting(CEnvironmentData* pCurrentSet)
{
//	CIniAccess pApp;////CWinApp* pApp = AfxGetApp();
//	CFile pFile;
//	CFileException FileExcept;
//
//	int nNoColors;
////	CString sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";
////
////
////	if (g_nRunningProcessNo == 1)
////	{
////		sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";
////	}
////	else
////	{
////		sIniPath = "D:\\DM_HDFT\\DM_HDFT_2.ini";
////	}
////	//+change kwmoon 080910
//////	if(!pFile.Open(sIniPath, CFile::modeRead | CFile::modeWrite, &FileExcept)) 
////	if (!pFile.Open(sIniPath, CFile::modeRead | CFile::shareDenyNone, &FileExcept))
////	{
////		char   szCause[255];
////		FileExcept.GetErrorMessage(szCause, 255);
////		AfxMessageBox(szCause);
////		SaveRegistrySetting();
////		return;
////	}
////	pFile.Close();
////	pApp.SetIniFile(sIniPath);
//
//
//
//
//	CString sTmp = _T("");
//	CString sBaudRate = _T("");
//
//	// Initialize variable
//	pCurrentSet->bIsRunning = FALSE;
//	pCurrentSet->bIsRunMsg = FALSE;
//
//	pCurrentSet->bMesUploadCheckTimer = FALSE;
//
//	pCurrentSet->sSeqPath = "D:\\DM_HDFT\\"//pApp.GetProfileString(_T("File"), _T("Current Seq"), _T(""));
//	pCurrentSet->sFullSeqPath = pApp.GetProfileString(_T("File"), _T("Current Full Seq"), _T(""));
//	pCurrentSet->sModelIni = pApp.GetProfileString(_T("File"), _T("Current ModelIni"), _T(""));
//	pCurrentSet->sRemoconTitle = pApp.GetProfileString(_T("File"), _T("Current Remocon"), _T(""));
//	pCurrentSet->sPatternTitle = pApp.GetProfileString(_T("File"), _T("Current Pattern"), _T(""));
//	pCurrentSet->sTestParamIni = pApp.GetProfileString(_T("File"), _T("Current TestParam"), _T(""));
//	//+add kwmoon 081024
//	pCurrentSet->sModelListPath = pApp.GetProfileString(_T("File"), _T("Current ModelList"), _T(""));
//
//	pCurrentSet->sChassisName = pApp.GetProfileString(_T("File"), _T("Current Chassis"), _T("BAR"));
//	pCurrentSet->sModelName = pApp.GetProfileString(_T("File"), _T("Current Model"), _T("SN6xInstall"));
//	pCurrentSet->sModelSuffixName = pApp.GetProfileString(_T("File"), _T("Current Model Suffix Name"), _T(""));
//
//	CurrentSet->sWorkOrderID = pApp.GetProfileString(_T("GMES"), _T("Current WorkOrder ID"), _T(""));
//	CurrentSet->sOrganizationID = pApp.GetProfileString(_T("GMES"), _T("Current Organization ID"), _T(""));
//	CurrentSet->sLineID = pApp.GetProfileString(_T("GMES"), _T("Current Line ID"), _T(""));
//	CurrentSet->sEquipmentID = pApp.GetProfileString(_T("GMES"), _T("Current Equipment ID"), _T(""));
//	CurrentSet->sOperationID = pApp.GetProfileString(_T("GMES"), _T("Current Operation ID"), _T(""));
//	CurrentSet->sModelID = pApp.GetProfileString(_T("GMES"), _T("Current Model ID"), _T(""));
//	CurrentSet->sModelName_GMES = pApp.GetProfileString(_T("GMES"), _T("Current Model Name"), _T(""));
//	CurrentSet->sModelSuffix = pApp.GetProfileString(_T("GMES"), _T("Current Model Suffix"), _T(""));
//
//	pCurrentSet->nRunType = pApp.GetProfileInt(_T("Run"), _T("Run Type"), STOP);
//	pCurrentSet->nRunStartType = pApp.GetProfileInt(_T("Run"), _T("Start Type"), MANUAL_START);
//
//	pCurrentSet->nDisplayType = pApp.GetProfileInt(_T("Display"), _T("Display Type"), DETAILEDGRID);
//	pCurrentSet->nPrintType = pApp.GetProfileInt(_T("Display"), _T("PrintOut Type"), ERRORVIEW);
//	pCurrentSet->bCommDisplay = pApp.GetProfileInt(_T("Display"), _T("Comm Display"), TRUE);
//	pCurrentSet->sViewerPath = pApp.GetProfileString(_T("File"), _T("Current Viewer"), "C:\\Windows\\Notepad.exe");
//	//	pCurrentSet->nLvdsWidth				= pApp.GetProfileInt(_T("Config"), _T("LVDS Grabber Width"), 1366);
//	//	pCurrentSet->nLvdsHeight			= pApp.GetProfileInt(_T("Config"), _T("LVDS Grabber Height"), 768);
//	pCurrentSet->nAnalogWidth = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Width"), 640);
//	pCurrentSet->nAnalogHeight = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Height"), 480);
//
//	//+add 090420(Modification No1)
//	pCurrentSet->nAnalogType = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Type"), 0);
//
//	CurrentSet->nUseUserRetry = pApp.GetProfileInt(_T("Config"), _T("Use User Retry"), 0);
//
//	//	if(pCurrentSet->nLvdsWidth	 == 0)	pCurrentSet->nLvdsWidth		= 1366;
//	//	if(pCurrentSet->nLvdsHeight	 == 0)	pCurrentSet->nLvdsHeight	= 768;
//	if (pCurrentSet->nAnalogWidth == 0)	pCurrentSet->nAnalogWidth = 640;
//	if (pCurrentSet->nAnalogHeight == 0)	pCurrentSet->nAnalogHeight = 480;
//
//	pCurrentSet->sModelFolder = pApp.GetProfileString(_T("Folder"), _T("Current Folder"), "D:\\DM_HDFT");
//	if (pCurrentSet->sModelFolder.IsEmpty())
//		pCurrentSet->sModelFolder = "D:\\DM_HDFT";
//	pCurrentSet->sGrabFolder = pApp.GetProfileString(_T("Folder"), _T("Current Grab Folder"), "D:\\DM_HDFT\\data");
//	if (pCurrentSet->sGrabFolder.IsEmpty())
//		pCurrentSet->sGrabFolder = "D:\\DM_HDFT\\data";
//	pCurrentSet->sRefFolder = pApp.GetProfileString(_T("Folder"), _T("Current Ref Folder"), "D:\\DM_HDFT\\ref");
//	if (pCurrentSet->sRefFolder.IsEmpty())
//		pCurrentSet->sRefFolder = "D:\\DM_HDFT\\ref";
//	pCurrentSet->sMaskFolder = pApp.GetProfileString(_T("Folder"), _T("Current Mask Folder"), "D:\\DM_HDFT\\ref\\Mask");
//	if (pCurrentSet->sMaskFolder.IsEmpty())
//		pCurrentSet->sMaskFolder = "D:\\DM_HDFT\\ref\\Mask";
//
//	//+add kwmoon 080904
//	pCurrentSet->sServerFolder = pApp.GetProfileString(_T("Folder"), _T("Current Server Folder"), "D:\\DM_HDFT");
//	if (pCurrentSet->sServerFolder.IsEmpty())
//		pCurrentSet->sServerFolder = "D:\\DM_HDFT";
//	//+add PSH 081029
//	pCurrentSet->sRefRootFolder = pApp.GetProfileString(_T("Folder"), _T("Current Reference Image Root Folder"), "D:\\DM_HDFT");
//	if (pCurrentSet->sRefRootFolder.IsEmpty())
//		pCurrentSet->sRefRootFolder = "D:\\DM_HDFT";
//	//+add PSH 081211
//	pCurrentSet->sModelInfoFolder = pApp.GetProfileString(_T("Folder"), _T("Current Model Info  Root Foler"), "D:\\DM_HDFT");
//	if (pCurrentSet->sModelInfoFolder.IsEmpty())
//		pCurrentSet->sModelInfoFolder = "D:\\DM_HDFT";
//
//	pCurrentSet->sParmAdjGrabFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Grab Folder"), "D:\\DM_HDFT\\data");
//	if (pCurrentSet->sParmAdjGrabFolder.IsEmpty())
//		pCurrentSet->sParmAdjGrabFolder = "D:\\DM_HDFT";
//	pCurrentSet->sParmAdjRefFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Ref Folder"), "D:\\DM_HDFT\\ref");
//	if (pCurrentSet->sParmAdjRefFolder.IsEmpty())
//		pCurrentSet->sParmAdjRefFolder = "D:\\DM_HDFT";
//	pCurrentSet->sParmAdjMaskFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Mask Folder"), "D:\\DM_HDFT\\ref\\Mask");
//	if (pCurrentSet->sParmAdjMaskFolder.IsEmpty())
//		pCurrentSet->sParmAdjMaskFolder = "D:\\DM_HDFT";
//
//	if (g_nRunningProcessNo == 1)
//	{
//		pCurrentSet->sPatternComPort = pApp.GetProfileString(_T("Config"), _T("Pattern Generator ComPort"), "COM1");
//		if (pCurrentSet->sPatternComPort == _T("")) pCurrentSet->sPatternComPort = "COM1";
//
//		pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM3");
//		if (pCurrentSet->sAvSwitchBoxComPort == _T("")) pCurrentSet->sAvSwitchBoxComPort = "COM3";
//
//		//pCurrentSet->sTVComPort				= pApp.GetProfileString(_T("Config"), _T("TV ComPort"), "COM5");
//		//if(pCurrentSet->sTVComPort			== _T("")) pCurrentSet->sTVComPort = "COM5";
//
//		pCurrentSet->sScannerComPort = pApp.GetProfileString(_T("Config"), _T("Scanner ComPort"), "COM7");
//		if (pCurrentSet->sScannerComPort == _T("")) pCurrentSet->sScannerComPort = "COM7";
//
//		pCurrentSet->sIrChkComPort = pApp.GetProfileString(_T("Config"), _T("IR Checker ComPort"), "COM9");
//		if (pCurrentSet->sIrChkComPort == _T("")) pCurrentSet->sIrChkComPort = "COM9";
//
//		pCurrentSet->sHDMIComPort = pApp.GetProfileString(_T("Config"), _T("HDMI Generator ComPort"), "\\\\.\\COM11");
//		if (pCurrentSet->sHDMIComPort == _T("")) pCurrentSet->sHDMIComPort = "\\\\.\\COM11";
//
//		pCurrentSet->sThComPort = pApp.GetProfileString(_T("Config"), _T("Thermometer ComPort"), "\\\\.\\COM13");
//		if (pCurrentSet->sThComPort == _T("")) pCurrentSet->sThComPort = "\\\\.\\COM13";
//
//		pCurrentSet->sSM_DIOComPort = pApp.GetProfileString(_T("Config"), _T("DIO Jig ComPort"), "COM5");
//		if (pCurrentSet->sSM_DIOComPort == _T("")) pCurrentSet->sSM_DIOComPort = "COM5";
//	}
//	else
//	{
//		pCurrentSet->sPatternComPort = pApp.GetProfileString(_T("Config"), _T("Pattern Generator ComPort"), "COM2");
//		if (pCurrentSet->sPatternComPort == _T("")) pCurrentSet->sPatternComPort = "COM2";
//
//		pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM4");
//		if (pCurrentSet->sAvSwitchBoxComPort == _T("")) pCurrentSet->sAvSwitchBoxComPort = "COM4";
//
//		//pCurrentSet->sTVComPort				= pApp.GetProfileString(_T("Config"), _T("TV ComPort"), "COM6");
//		//if(pCurrentSet->sTVComPort			== _T("")) pCurrentSet->sTVComPort = "COM6";
//
//		pCurrentSet->sScannerComPort = pApp.GetProfileString(_T("Config"), _T("Scanner ComPort"), "COM8");
//		if (pCurrentSet->sScannerComPort == _T("")) pCurrentSet->sScannerComPort = "COM8";
//
//		pCurrentSet->sIrChkComPort = pApp.GetProfileString(_T("Config"), _T("IR Checker ComPort"), "\\\\.\\COM10");
//		if (pCurrentSet->sIrChkComPort == _T("")) pCurrentSet->sIrChkComPort = "\\\\.\\COM10";
//
//		pCurrentSet->sHDMIComPort = pApp.GetProfileString(_T("Config"), _T("HDMI Generator ComPort"), "\\\\.\\COM12");
//		if (pCurrentSet->sHDMIComPort == _T("")) pCurrentSet->sHDMIComPort = "\\\\.\\COM12";
//
//		pCurrentSet->sThComPort = pApp.GetProfileString(_T("Config"), _T("Thermometer ComPort"), "\\\\.\\COM14");
//		if (pCurrentSet->sThComPort == _T("")) pCurrentSet->sThComPort = "\\\\.\\COM14";
//
//		pCurrentSet->sSM_DIOComPort = pApp.GetProfileString(_T("Config"), _T("DIO Jig ComPort"), "COM6");
//		if (pCurrentSet->sSM_DIOComPort == _T("")) pCurrentSet->sSM_DIOComPort = "COM6";
//
//
//	}
//
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Pattern Generator Baud Rate"), "9600");
//	pCurrentSet->wPatternBaudRate = (DWORD)(atoi(sBaudRate));
//
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox Baud Rate"), "9600");
//	pCurrentSet->wAvSwitchBoxBaudRate = (DWORD)(atoi(sBaudRate));
//
//	//+del psh 080701
////	sBaudRate							= pApp.GetProfileString(_T("Config"), _T("TV Baud Rate"), "115200");
////	pCurrentSet->wTVBaudRate			= (DWORD)(atoi(sBaudRate));
////-
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Scanner Baud Rate"), "9600");
//	pCurrentSet->wScannerBaudRate = (DWORD)(atoi(sBaudRate));
//
//	//+Add kwmoon 080625
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("IR Checker Baud Rate"), "19200");
//	pCurrentSet->wIrChkBaudRate = (DWORD)(atoi(sBaudRate));
//
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("HDMI Generator Baud Rate"), "19200");
//	pCurrentSet->wHDMIBaudRate = (DWORD)(atoi(sBaudRate));
//
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Thermometer Baud Rate"), "9600");
//	pCurrentSet->wThBaudRate = (DWORD)(atoi(sBaudRate));
//
//	sBaudRate = pApp.GetProfileString(_T("Config"), _T("DIO Jig Baud Rate"), "19200");
//	pCurrentSet->wSM_DIOBaudRate = (DWORD)(atoi(sBaudRate));
//
//	pCurrentSet->bUsePatternGen = pApp.GetProfileInt(_T("Config"), _T("Use Pattern Generator"), 1);
//	//	pCurrentSet->bUseTVCommPort			= pApp.GetProfileInt(_T("Config"), _T("Use TVComm Port"), 1);
//	pCurrentSet->bUseAVSwitchBox = pApp.GetProfileInt(_T("Config"), _T("Use AVSwitchingBox"), 1);
//	pCurrentSet->bUseScanner = pApp.GetProfileInt(_T("Config"), _T("Use Scanner"), 1);
//	pCurrentSet->bUseHDMIGen = pApp.GetProfileInt(_T("Config"), _T("Use HDMI Generator"), 1);
//	pCurrentSet->bUseIrChk = pApp.GetProfileInt(_T("Config"), _T("Use IR Checker"), 1);
//	pCurrentSet->bUseTh = pApp.GetProfileInt(_T("Config"), _T("Use Thermometer"), 1);
//	pCurrentSet->bUseSM_DIO = pApp.GetProfileInt(_T("Config"), _T("Use DIO Jig"), 1);
//
//
//	//+change kwmoon 080804
//	pCurrentSet->nAdcType = pApp.GetProfileInt(_T("Config"), _T("ADC Type"), 0); // 0 : RS232C, 1 : I2C
//
//	pCurrentSet->bSaveGrabImg = pApp.GetProfileInt(_T("Config"), _T("Auto Save Grab Image"), 0);// 0 : NG, 1 : ALL
//	pCurrentSet->bSaveProcImg = TRUE; // pApp.GetProfileInt(_T("Config"), _T("Auto Save Processed Image"), 1);
//	pCurrentSet->bSaveCaptionTestImg = pApp.GetProfileInt(_T("Config"), _T("Save Caption Test Image"), 0);
//	pCurrentSet->bSaveMovingPicTestImg = pApp.GetProfileInt(_T("Config"), _T("Save Moving Pic Test Image"), 0);
//	pCurrentSet->bSaveIntermediateImage = pApp.GetProfileInt(_T("Config"), _T("Save Intermediate Image"), 0);
//	pCurrentSet->bSaveProcessingTimeData = pApp.GetProfileInt(_T("Config"), _T("Save Processing Time Data"), 0);
//
//	//+add kwmoon 080716
//	pCurrentSet->bSaveReviewData = pApp.GetProfileInt(_T("Config"), _T("Save Review Data"), 0);
//	pCurrentSet->bSaveDetailResultData = pApp.GetProfileInt(_T("Config"), _T("Save Detail Result Data"), 0);
//
//	pCurrentSet->nAudioSource = pApp.GetProfileInt(_T("Config"), _T("Audio Input Source"), 0);
//
//	//+change kwmoon 080715
//	pCurrentSet->bSaveResult2Txt = pApp.GetProfileInt(_T("Config"), _T("Save Result to Text File"), 0);
//	pCurrentSet->bSaveResult2Html = pApp.GetProfileInt(_T("Config"), _T("Save Result to Html File"), 1);
//	pCurrentSet->bSaveResult2Csv = pApp.GetProfileInt(_T("Config"), _T("Save Result to Csv File"), 1);
//	//-
//
//	pCurrentSet->nNoRepeatExecution = pApp.GetProfileInt(_T("Config"), _T("No of repeat execution"), 1);
//
//	//+change kwmoon 080925
////	pCurrentSet->nNoFrameForRefImageCreation	= pApp.GetProfileInt(_T("Config"), _T("No of frames for refimage creation"), 2);
//	pCurrentSet->nNoFrameForRefImageCreation = pApp.GetProfileInt(_T("Config"), _T("No of frames for refimage creation"), 1);
//
//
//	pCurrentSet->nPixelInMiddleRange = pApp.GetProfileInt(_T("Config"), _T("Percentage of pixels in middle range"), 85);
//	pCurrentSet->nNonBlackPixel = pApp.GetProfileInt(_T("Config"), _T("Percentage of non-black pixels"), 30);
//
//	//+add 090218(Modification No1)
//	pCurrentSet->nNoUsedColors = pApp.GetProfileInt(_T("Config"), _T("No Used Colors"), 5000);
//
//	//+del kwmoon 080715
////	pCurrentSet->nNoAllowedErrorPixelForOsdTest =  pApp.GetProfileInt(_T("Config"), _T("No of allowed error pixel for osd test"), 0);
//
//	//+add kwmoon 080123
//	pCurrentSet->nDelayPercentage = pApp.GetProfileInt(_T("Config"), _T("Delay Percentage"), 100);
//
//	//	pCurrentSet->nUranousMode			= pApp.GetProfileInt(_T("Config"), _T("Uranous Grabber Mode"), NS_SINGLE8);
//
//		//+add psh 090630
//	//	pCurrentSet->bOddDE_Only			= (BOOL)pApp.GetProfileInt(_T("Config"), _T("LVDS OddDE Only"), 0);
//
//	//	if(pCurrentSet->nUranousMode == 0)	pCurrentSet->nUranousMode = NS_SINGLE;
//
//	//	pCurrentSet->nBitCount				= pApp.GetProfileInt(_T("Config"), _T("Color Bit Count"), 24);
//		//+del PSH 081218
//	//	pCurrentSet->nTotalNoTest			= pApp.GetProfileInt(_T("Config"), _T("Total No of test"), 0);
//	//	pCurrentSet->nTotalNoNg				= pApp.GetProfileInt(_T("Config"), _T("Total No of Ng"), 0);
//
//		//+add kwmoon 081004
//	//	pCurrentSet->nTotalNoUserStop		= pApp.GetProfileInt(_T("Config"), _T("Total No of User Stop"), 0);
//
//	pCurrentSet->nNoRetry = pApp.GetProfileInt(_T("Config"), _T("No of Internal Retry"), 1);
//
//	//+add psh 081030
//	pCurrentSet->nGrabCheckArea = pApp.GetProfileInt(_T("Config"), _T("Grab Image Check Area"), 7);
//	if (pCurrentSet->nGrabCheckArea < 0 || pCurrentSet->nGrabCheckArea >8)
//		pCurrentSet->nGrabCheckArea = 7;
//	//+del kwmoon 080125
//	//+add kwmoon 071227
////	pCurrentSet->nSpecMargin			= pApp.GetProfileInt(_T("Config"), _T("Spec Margin"), 0);
//
//	//+del kwmoon 080819
//	//+add kwmoon 080123
////	pCurrentSet->nFreqMargin		= pApp.GetProfileInt(_T("Config"), _T("Audio Spec Margin"), 30);
//
//	pCurrentSet->bTVCommPortEcho = (BOOL)pApp.GetProfileInt(_T("Config"), _T("TVComm Port Echo"), 0);
//
//	pCurrentSet->sHDMIRoiShape = pApp.GetProfileString(_T("Config"), _T("HDMI Roi Shape"), "VERTICAL");
//	pCurrentSet->nLocation = pApp.GetProfileInt(_T("DataBase"), _T("Location"), 0);
//	pCurrentSet->nLineNo = pApp.GetProfileInt(_T("DataBase"), _T("Line Number"), 0);
//	pCurrentSet->nSystemNo = pApp.GetProfileInt(_T("DataBase"), _T("System Number"), 0);
//	pCurrentSet->nAuthority = pApp.GetProfileInt(_T("DataBase"), _T("Authority"), 0);
//	pCurrentSet->strPassword = pApp.GetProfileString(_T("DataBase"), _T("PassWord"), _T("DFT"));
//
//	//	pCurrentSet->strMesDsn				= pApp.GetProfileString(_T("DataBase"), _T("MES DSN"), _T("DISMES"));
//	//	pCurrentSet->strMesUserId			= pApp.GetProfileString(_T("DataBase"), _T("MES USERID"), _T("MESLOOK"));
//	//	pCurrentSet->strMesPassWord			= pApp.GetProfileString(_T("DataBase"), _T("MES PASSWORD"), _T("LOOKMES"));
//	pCurrentSet->strGmesIP = pApp.GetProfileString(_T("DataBase"), _T("GMES Host IP"), _T("156.147.82.152"));
//	pCurrentSet->nGmesPort = pApp.GetProfileInt(_T("DataBase"), _T("GMES Host Port"), 40201);
//
//	pCurrentSet->bUploadMes = (BOOL)pApp.GetProfileInt(_T("DataBase Upload"), _T("UPLOAD MES DATA"), 0);
//	pCurrentSet->bAutoUploadMes = (BOOL)pApp.GetProfileInt(_T("DataBase"), _T("AUTO UPLOAD MES DATA"), 0);
//	pCurrentSet->bAutoGMES_ChangeModel = (BOOL)pApp.GetProfileInt(_T("AUTO CHANGE MODEL"), _T("AUTO CHANGE MODEL"), 0);
//
//	pCurrentSet->bAutoDataDelete = (BOOL)pApp.GetProfileInt(_T("DataBase"), _T("AUTO UPLOAD MES DATA"), 0);
//
//	//+change kwmoon 080925
////	pCurrentSet->nAudioCheckMethod		= pApp.GetProfileInt(_T("Config"), _T("AudioCheckMethod"), 0);
//	pCurrentSet->nAudioCheckMethod = pApp.GetProfileInt(_T("Config"), _T("AudioCheckMethod"), 1);
//
//	//+add psh 090401
//	pCurrentSet->nDataSavePeriod = pApp.GetProfileInt(_T("Config"), _T("Data Save Period"), 60);
//
//	if ((pCurrentSet->nDataSavePeriod < 0) || (pCurrentSet->nDataSavePeriod > 1000))
//	{
//		pCurrentSet->nDataSavePeriod = 60;
//	}
//	pCurrentSet->bAutoDataDelete = pApp.GetProfileInt(_T("Config"), _T("Auto Data Delete"), 1);
//	if ((pCurrentSet->bAutoDataDelete < 0) || (pCurrentSet->bAutoDataDelete > 1))
//	{
//		pCurrentSet->bAutoDataDelete = 1;
//	}
//
//	//	CurrentSet->sCPUVersion   = pApp.GetProfileString(_T("Config"), _T("CPU Version"), _T(""));
//	//	CurrentSet->sMicomVersion = pApp.GetProfileString(_T("Config"), _T("Micom Version"), _T(""));
//	//	CurrentSet->sUSBVersion   = pApp.GetProfileString(_T("Config"), _T("USB Version"), _T(""));
//
//		// 090120 External DFT
//	//	pCurrentSet->nLvdsGrabberType		= pApp.GetProfileInt(_T("Config"), _T("Lvds Grabber Type"), INTERNAL_GRABBER);
//
//		//+add psh 110225
//	pCurrentSet->nRemoteCustomCode = pApp.GetProfileInt(_T("Config"), _T("Remocon Custom Code"), 0);
//	if ((pCurrentSet->nRemoteCustomCode < 0) || (pCurrentSet->nRemoteCustomCode > 12))
//	{
//		pCurrentSet->nRemoteCustomCode = 0;
//	}
//	pCurrentSet->nRemoteType = pApp.GetProfileInt(_T("Config"), _T("Remocon Type"), 0);
//	if ((pCurrentSet->nRemoteType < 0) || (pCurrentSet->nRemoteType > 1))
//	{
//		pCurrentSet->nRemoteType = 0;
//	}
//	pCurrentSet->b2PCBA_WID = m_Ini.GetProfileInt(GENERAL_S, "Scan TWO LABEL");
//
//	pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM4");
//	pCurrentSet->bAvSwitchBoxBuzzerMute = pApp.GetProfileInt(_T("Config"), _T("AV SwitchBox Buzzet Mute"), 1);
//
//	pCurrentSet->nAvSwitchBoxInitVideoCh = pApp.GetProfileInt(_T("Config"), _T("AV SwitchBox Initialize Video Mode"), 1);
//
//	pCurrentSet->bVersionCheckOnly = pApp.GetProfileInt(_T("Config"), _T("Version Check Only"), 0);
//
//	pCurrentSet->nProcessType = pApp.GetProfileInt(_T("Config"), _T("Inspection Process Type"), 0);
//
//	pCurrentSet->nModelInfo_Check = pApp.GetProfileInt(_T("Config"), _T("Model Info. Check Type"), 0);
//
//	pCurrentSet->bFixtureIdCheck = pApp.GetProfileInt(_T("Config"), _T("Fixture ID Check"), 1);
//
//	pCurrentSet->nJigUpType = pApp.GetProfileInt(_T("Config"), _T("JigUpType"), 0);
//
//	pCurrentSet->nSoundInDeviceID = pApp.GetProfileInt(_T("Config"), _T("Sound Device ID"), 0);
//	pCurrentSet->sSoundInDeviceName = pApp.GetProfileString(_T("Config"), _T("Sound Device Name"), "NC");
//
//	pCurrentSet->bNoVideoCapture = pApp.GetProfileInt(_T("Config"), _T("No Video Capture"), 0);
//

}

void CAcqVoltageSamples_IntClkDlg::LoadRegistrySetting(CEnvironmentData* pCurrentSet)
{
	CIniAccess pApp;////CWinApp* pApp = AfxGetApp();
	CFile pFile;
	CFileException FileExcept;

	int nNoColors;
	CString sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";


	if (g_nRunningProcessNo == 1)
	{
		sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";
	}
	else
	{
		sIniPath = "D:\\DM_HDFT\\DM_HDFT_2.ini";
	}
	//+change kwmoon 080910
//	if(!pFile.Open(sIniPath, CFile::modeRead | CFile::modeWrite, &FileExcept)) 
	if (!pFile.Open(sIniPath, CFile::modeRead | CFile::shareDenyNone, &FileExcept))
	{
		char   szCause[255];
		FileExcept.GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause);
		SaveRegistrySetting();
		return ;
	}
	pFile.Close();
	pApp.SetIniFile(sIniPath);




	CString sTmp = _T("");
	CString sBaudRate = _T("");

	// Initialize variable
	pCurrentSet->bIsRunning = FALSE;
	pCurrentSet->bIsRunMsg = FALSE;

	pCurrentSet->bMesUploadCheckTimer = FALSE;

	pCurrentSet->sSeqPath = pApp.GetProfileString(_T("File"), _T("Current Seq"), _T(""));
	pCurrentSet->sFullSeqPath = pApp.GetProfileString(_T("File"), _T("Current Full Seq"), _T(""));
	pCurrentSet->sModelIni = pApp.GetProfileString(_T("File"), _T("Current ModelIni"), _T(""));
	pCurrentSet->sRemoconTitle = pApp.GetProfileString(_T("File"), _T("Current Remocon"), _T(""));
	pCurrentSet->sPatternTitle = pApp.GetProfileString(_T("File"), _T("Current Pattern"), _T(""));
	pCurrentSet->sTestParamIni = pApp.GetProfileString(_T("File"), _T("Current TestParam"), _T(""));
	//+add kwmoon 081024
	pCurrentSet->sModelListPath = pApp.GetProfileString(_T("File"), _T("Current ModelList"), _T(""));

	pCurrentSet->sChassisName = pApp.GetProfileString(_T("File"), _T("Current Chassis"), _T("BAR"));
	pCurrentSet->sModelName = pApp.GetProfileString(_T("File"), _T("Current Model"), _T("SN6xInstall"));
	pCurrentSet->sModelSuffixName = pApp.GetProfileString(_T("File"), _T("Current Model Suffix Name"), _T(""));

	CurrentSet->sWorkOrderID = pApp.GetProfileString(_T("GMES"), _T("Current WorkOrder ID"), _T(""));
	CurrentSet->sOrganizationID = pApp.GetProfileString(_T("GMES"), _T("Current Organization ID"), _T(""));
	CurrentSet->sLineID = pApp.GetProfileString(_T("GMES"), _T("Current Line ID"), _T(""));
	CurrentSet->sEquipmentID = pApp.GetProfileString(_T("GMES"), _T("Current Equipment ID"), _T(""));
	CurrentSet->sOperationID = pApp.GetProfileString(_T("GMES"), _T("Current Operation ID"), _T(""));
	CurrentSet->sModelID = pApp.GetProfileString(_T("GMES"), _T("Current Model ID"), _T(""));
	CurrentSet->sModelName_GMES = pApp.GetProfileString(_T("GMES"), _T("Current Model Name"), _T(""));
	CurrentSet->sModelSuffix = pApp.GetProfileString(_T("GMES"), _T("Current Model Suffix"), _T(""));

	pCurrentSet->nRunType = pApp.GetProfileInt(_T("Run"), _T("Run Type"), STOP);
	pCurrentSet->nRunStartType = pApp.GetProfileInt(_T("Run"), _T("Start Type"), MANUAL_START);

	pCurrentSet->nDisplayType = pApp.GetProfileInt(_T("Display"), _T("Display Type"), DETAILEDGRID);
	pCurrentSet->nPrintType = pApp.GetProfileInt(_T("Display"), _T("PrintOut Type"), ERRORVIEW);
	pCurrentSet->bCommDisplay = pApp.GetProfileInt(_T("Display"), _T("Comm Display"), TRUE);
	pCurrentSet->sViewerPath = pApp.GetProfileString(_T("File"), _T("Current Viewer"), "C:\\Windows\\Notepad.exe");
	//	pCurrentSet->nLvdsWidth				= pApp.GetProfileInt(_T("Config"), _T("LVDS Grabber Width"), 1366);
	//	pCurrentSet->nLvdsHeight			= pApp.GetProfileInt(_T("Config"), _T("LVDS Grabber Height"), 768);
	pCurrentSet->nAnalogWidth = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Width"), 640);
	pCurrentSet->nAnalogHeight = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Height"), 480);

	//+add 090420(Modification No1)
	pCurrentSet->nAnalogType = pApp.GetProfileInt(_T("Config"), _T("Analog Grabber Type"), 0);

	CurrentSet->nUseUserRetry = pApp.GetProfileInt(_T("Config"), _T("Use User Retry"), 0);

	//	if(pCurrentSet->nLvdsWidth	 == 0)	pCurrentSet->nLvdsWidth		= 1366;
	//	if(pCurrentSet->nLvdsHeight	 == 0)	pCurrentSet->nLvdsHeight	= 768;
	if (pCurrentSet->nAnalogWidth == 0)	pCurrentSet->nAnalogWidth = 640;
	if (pCurrentSet->nAnalogHeight == 0)	pCurrentSet->nAnalogHeight = 480;

	pCurrentSet->sModelFolder = pApp.GetProfileString(_T("Folder"), _T("Current Folder"), "D:\\DM_HDFT");
	if (pCurrentSet->sModelFolder.IsEmpty())
		pCurrentSet->sModelFolder = "D:\\DM_HDFT";
	pCurrentSet->sGrabFolder = pApp.GetProfileString(_T("Folder"), _T("Current Grab Folder"), "D:\\DM_HDFT\\data");
	if (pCurrentSet->sGrabFolder.IsEmpty())
		pCurrentSet->sGrabFolder = "D:\\DM_HDFT\\data";
	pCurrentSet->sRefFolder = pApp.GetProfileString(_T("Folder"), _T("Current Ref Folder"), "D:\\DM_HDFT\\ref");
	if (pCurrentSet->sRefFolder.IsEmpty())
		pCurrentSet->sRefFolder = "D:\\DM_HDFT\\ref";
	pCurrentSet->sMaskFolder = pApp.GetProfileString(_T("Folder"), _T("Current Mask Folder"), "D:\\DM_HDFT\\ref\\Mask");
	if (pCurrentSet->sMaskFolder.IsEmpty())
		pCurrentSet->sMaskFolder = "D:\\DM_HDFT\\ref\\Mask";

	//+add kwmoon 080904
	pCurrentSet->sServerFolder = pApp.GetProfileString(_T("Folder"), _T("Current Server Folder"), "D:\\DM_HDFT");
	if (pCurrentSet->sServerFolder.IsEmpty())
		pCurrentSet->sServerFolder = "D:\\DM_HDFT";
	//+add PSH 081029
	pCurrentSet->sRefRootFolder = pApp.GetProfileString(_T("Folder"), _T("Current Reference Image Root Folder"), "D:\\DM_HDFT");
	if (pCurrentSet->sRefRootFolder.IsEmpty())
		pCurrentSet->sRefRootFolder = "D:\\DM_HDFT";
	//+add PSH 081211
	pCurrentSet->sModelInfoFolder = pApp.GetProfileString(_T("Folder"), _T("Current Model Info  Root Foler"), "D:\\DM_HDFT");
	if (pCurrentSet->sModelInfoFolder.IsEmpty())
		pCurrentSet->sModelInfoFolder = "D:\\DM_HDFT";

	pCurrentSet->sParmAdjGrabFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Grab Folder"), "D:\\DM_HDFT\\data");
	if (pCurrentSet->sParmAdjGrabFolder.IsEmpty())
		pCurrentSet->sParmAdjGrabFolder = "D:\\DM_HDFT";
	pCurrentSet->sParmAdjRefFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Ref Folder"), "D:\\DM_HDFT\\ref");
	if (pCurrentSet->sParmAdjRefFolder.IsEmpty())
		pCurrentSet->sParmAdjRefFolder = "D:\\DM_HDFT";
	pCurrentSet->sParmAdjMaskFolder = pApp.GetProfileString(_T("Folder"), _T("ParmAdj Current Mask Folder"), "D:\\DM_HDFT\\ref\\Mask");
	if (pCurrentSet->sParmAdjMaskFolder.IsEmpty())
		pCurrentSet->sParmAdjMaskFolder = "D:\\DM_HDFT";

	if (g_nRunningProcessNo == 1)
	{
		pCurrentSet->sPatternComPort = pApp.GetProfileString(_T("Config"), _T("Pattern Generator ComPort"), "COM1");
		if (pCurrentSet->sPatternComPort == _T("")) pCurrentSet->sPatternComPort = "COM1";

		pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM3");
		if (pCurrentSet->sAvSwitchBoxComPort == _T("")) pCurrentSet->sAvSwitchBoxComPort = "COM3";

		//pCurrentSet->sTVComPort				= pApp.GetProfileString(_T("Config"), _T("TV ComPort"), "COM5");
		//if(pCurrentSet->sTVComPort			== _T("")) pCurrentSet->sTVComPort = "COM5";

		pCurrentSet->sScannerComPort = pApp.GetProfileString(_T("Config"), _T("Scanner ComPort"), "COM7");
		if (pCurrentSet->sScannerComPort == _T("")) pCurrentSet->sScannerComPort = "COM7";

		pCurrentSet->sIrChkComPort = pApp.GetProfileString(_T("Config"), _T("IR Checker ComPort"), "COM9");
		if (pCurrentSet->sIrChkComPort == _T("")) pCurrentSet->sIrChkComPort = "COM9";

		pCurrentSet->sHDMIComPort = pApp.GetProfileString(_T("Config"), _T("HDMI Generator ComPort"), "\\\\.\\COM11");
		if (pCurrentSet->sHDMIComPort == _T("")) pCurrentSet->sHDMIComPort = "\\\\.\\COM11";

		pCurrentSet->sThComPort = pApp.GetProfileString(_T("Config"), _T("Thermometer ComPort"), "\\\\.\\COM13");
		if (pCurrentSet->sThComPort == _T("")) pCurrentSet->sThComPort = "\\\\.\\COM13";

		pCurrentSet->sSM_DIOComPort = pApp.GetProfileString(_T("Config"), _T("DIO Jig ComPort"), "COM5");
		if (pCurrentSet->sSM_DIOComPort == _T("")) pCurrentSet->sSM_DIOComPort = "COM5";
	}
	else
	{
		pCurrentSet->sPatternComPort = pApp.GetProfileString(_T("Config"), _T("Pattern Generator ComPort"), "COM2");
		if (pCurrentSet->sPatternComPort == _T("")) pCurrentSet->sPatternComPort = "COM2";

		pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM4");
		if (pCurrentSet->sAvSwitchBoxComPort == _T("")) pCurrentSet->sAvSwitchBoxComPort = "COM4";

		//pCurrentSet->sTVComPort				= pApp.GetProfileString(_T("Config"), _T("TV ComPort"), "COM6");
		//if(pCurrentSet->sTVComPort			== _T("")) pCurrentSet->sTVComPort = "COM6";

		pCurrentSet->sScannerComPort = pApp.GetProfileString(_T("Config"), _T("Scanner ComPort"), "COM8");
		if (pCurrentSet->sScannerComPort == _T("")) pCurrentSet->sScannerComPort = "COM8";

		pCurrentSet->sIrChkComPort = pApp.GetProfileString(_T("Config"), _T("IR Checker ComPort"), "\\\\.\\COM10");
		if (pCurrentSet->sIrChkComPort == _T("")) pCurrentSet->sIrChkComPort = "\\\\.\\COM10";

		pCurrentSet->sHDMIComPort = pApp.GetProfileString(_T("Config"), _T("HDMI Generator ComPort"), "\\\\.\\COM12");
		if (pCurrentSet->sHDMIComPort == _T("")) pCurrentSet->sHDMIComPort = "\\\\.\\COM12";

		pCurrentSet->sThComPort = pApp.GetProfileString(_T("Config"), _T("Thermometer ComPort"), "\\\\.\\COM14");
		if (pCurrentSet->sThComPort == _T("")) pCurrentSet->sThComPort = "\\\\.\\COM14";

		pCurrentSet->sSM_DIOComPort = pApp.GetProfileString(_T("Config"), _T("DIO Jig ComPort"), "COM6");
		if (pCurrentSet->sSM_DIOComPort == _T("")) pCurrentSet->sSM_DIOComPort = "COM6";
		
	}

	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Pattern Generator Baud Rate"), "9600");
	pCurrentSet->wPatternBaudRate = (DWORD)(atoi(sBaudRate));

	sBaudRate = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox Baud Rate"), "9600");
	pCurrentSet->wAvSwitchBoxBaudRate = (DWORD)(atoi(sBaudRate));

	//+del psh 080701
//	sBaudRate							= pApp.GetProfileString(_T("Config"), _T("TV Baud Rate"), "115200");
//	pCurrentSet->wTVBaudRate			= (DWORD)(atoi(sBaudRate));
//-
	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Scanner Baud Rate"), "9600");
	pCurrentSet->wScannerBaudRate = (DWORD)(atoi(sBaudRate));

	//+Add kwmoon 080625
	sBaudRate = pApp.GetProfileString(_T("Config"), _T("IR Checker Baud Rate"), "19200");
	pCurrentSet->wIrChkBaudRate = (DWORD)(atoi(sBaudRate));

	sBaudRate = pApp.GetProfileString(_T("Config"), _T("HDMI Generator Baud Rate"), "19200");
	pCurrentSet->wHDMIBaudRate = (DWORD)(atoi(sBaudRate));

	sBaudRate = pApp.GetProfileString(_T("Config"), _T("Thermometer Baud Rate"), "9600");
	pCurrentSet->wThBaudRate = (DWORD)(atoi(sBaudRate));

	sBaudRate = pApp.GetProfileString(_T("Config"), _T("DIO Jig Baud Rate"), "19200");
	pCurrentSet->wSM_DIOBaudRate = (DWORD)(atoi(sBaudRate));

	pCurrentSet->bUsePatternGen = pApp.GetProfileInt(_T("Config"), _T("Use Pattern Generator"), 1);
	//	pCurrentSet->bUseTVCommPort			= pApp.GetProfileInt(_T("Config"), _T("Use TVComm Port"), 1);
	pCurrentSet->bUseAVSwitchBox = pApp.GetProfileInt(_T("Config"), _T("Use AVSwitchingBox"), 1);
	pCurrentSet->bUseScanner = pApp.GetProfileInt(_T("Config"), _T("Use Scanner"), 1);
	pCurrentSet->bUseHDMIGen = pApp.GetProfileInt(_T("Config"), _T("Use HDMI Generator"), 1);
	pCurrentSet->bUseIrChk = pApp.GetProfileInt(_T("Config"), _T("Use IR Checker"), 1);
	pCurrentSet->bUseTh = pApp.GetProfileInt(_T("Config"), _T("Use Thermometer"), 1);
	pCurrentSet->bUseSM_DIO = pApp.GetProfileInt(_T("Config"), _T("Use DIO Jig"), 1);


	//+change kwmoon 080804
	pCurrentSet->nAdcType = pApp.GetProfileInt(_T("Config"), _T("ADC Type"), 0); // 0 : RS232C, 1 : I2C

	pCurrentSet->bSaveGrabImg = pApp.GetProfileInt(_T("Config"), _T("Auto Save Grab Image"), 0);// 0 : NG, 1 : ALL
	pCurrentSet->bSaveProcImg = TRUE; // pApp.GetProfileInt(_T("Config"), _T("Auto Save Processed Image"), 1);
	pCurrentSet->bSaveCaptionTestImg = pApp.GetProfileInt(_T("Config"), _T("Save Caption Test Image"), 0);
	pCurrentSet->bSaveMovingPicTestImg = pApp.GetProfileInt(_T("Config"), _T("Save Moving Pic Test Image"), 0);
	pCurrentSet->bSaveIntermediateImage = pApp.GetProfileInt(_T("Config"), _T("Save Intermediate Image"), 0);
	pCurrentSet->bSaveProcessingTimeData = pApp.GetProfileInt(_T("Config"), _T("Save Processing Time Data"), 0);

	//+add kwmoon 080716
	pCurrentSet->bSaveReviewData = pApp.GetProfileInt(_T("Config"), _T("Save Review Data"), 0);
	pCurrentSet->bSaveDetailResultData = pApp.GetProfileInt(_T("Config"), _T("Save Detail Result Data"), 0);

	pCurrentSet->nAudioSource = pApp.GetProfileInt(_T("Config"), _T("Audio Input Source"), 0);

	//+change kwmoon 080715
	pCurrentSet->bSaveResult2Txt = pApp.GetProfileInt(_T("Config"), _T("Save Result to Text File"), 0);
	pCurrentSet->bSaveResult2Html = pApp.GetProfileInt(_T("Config"), _T("Save Result to Html File"), 1);
	pCurrentSet->bSaveResult2Csv = pApp.GetProfileInt(_T("Config"), _T("Save Result to Csv File"), 1);
	//-

	pCurrentSet->nNoRepeatExecution = pApp.GetProfileInt(_T("Config"), _T("No of repeat execution"), 1);

	//+change kwmoon 080925
//	pCurrentSet->nNoFrameForRefImageCreation	= pApp.GetProfileInt(_T("Config"), _T("No of frames for refimage creation"), 2);
	pCurrentSet->nNoFrameForRefImageCreation = pApp.GetProfileInt(_T("Config"), _T("No of frames for refimage creation"), 1);


	pCurrentSet->nPixelInMiddleRange = pApp.GetProfileInt(_T("Config"), _T("Percentage of pixels in middle range"), 85);
	pCurrentSet->nNonBlackPixel = pApp.GetProfileInt(_T("Config"), _T("Percentage of non-black pixels"), 30);

	//+add 090218(Modification No1)
	pCurrentSet->nNoUsedColors = pApp.GetProfileInt(_T("Config"), _T("No Used Colors"), 5000);

	//+del kwmoon 080715
//	pCurrentSet->nNoAllowedErrorPixelForOsdTest =  pApp.GetProfileInt(_T("Config"), _T("No of allowed error pixel for osd test"), 0);

	//+add kwmoon 080123
	pCurrentSet->nDelayPercentage = pApp.GetProfileInt(_T("Config"), _T("Delay Percentage"), 100);

	pCurrentSet->nNoRetry = pApp.GetProfileInt(_T("Config"), _T("No of Internal Retry"), 1);

	//+add psh 081030
	pCurrentSet->nGrabCheckArea = pApp.GetProfileInt(_T("Config"), _T("Grab Image Check Area"), 7);
	if(pCurrentSet->nGrabCheckArea <0 || pCurrentSet->nGrabCheckArea >8)
		pCurrentSet->nGrabCheckArea = 7;

	pCurrentSet->bTVCommPortEcho = (BOOL)pApp.GetProfileInt(_T("Config"), _T("TVComm Port Echo"), 0);

	pCurrentSet->sHDMIRoiShape = pApp.GetProfileString(_T("Config"), _T("HDMI Roi Shape"), "VERTICAL");
	pCurrentSet->nLocation = pApp.GetProfileInt(_T("DataBase"), _T("Location"), 0);
	pCurrentSet->nLineNo = pApp.GetProfileInt(_T("DataBase"), _T("Line Number"), 0);
	pCurrentSet->nSystemNo = pApp.GetProfileInt(_T("DataBase"), _T("System Number"), 0);
	pCurrentSet->nAuthority = pApp.GetProfileInt(_T("DataBase"), _T("Authority"), 0);
	pCurrentSet->strPassword = pApp.GetProfileString(_T("DataBase"), _T("PassWord"), _T("DFT"));

	pCurrentSet->strGmesIP = pApp.GetProfileString(_T("DataBase"), _T("GMES Host IP"), _T("156.147.82.152"));
	pCurrentSet->nGmesPort = pApp.GetProfileInt(_T("DataBase"), _T("GMES Host Port"), 40201);

	pCurrentSet->bUploadMes = (BOOL)pApp.GetProfileInt(_T("DataBase Upload"), _T("UPLOAD MES DATA"), 0);
	pCurrentSet->bAutoUploadMes = (BOOL)pApp.GetProfileInt(_T("DataBase"), _T("AUTO UPLOAD MES DATA"), 0);
	pCurrentSet->bAutoGMES_ChangeModel = (BOOL)pApp.GetProfileInt(_T("AUTO CHANGE MODEL"), _T("AUTO CHANGE MODEL"), 0);

	pCurrentSet->bAutoDataDelete = (BOOL)pApp.GetProfileInt(_T("DataBase"), _T("AUTO UPLOAD MES DATA"), 0);

	pCurrentSet->nAudioCheckMethod = pApp.GetProfileInt(_T("Config"), _T("AudioCheckMethod"), 1);

	//+add psh 090401
	pCurrentSet->nDataSavePeriod = pApp.GetProfileInt(_T("Config"), _T("Data Save Period"), 60);

	if ((pCurrentSet->nDataSavePeriod < 0) || (pCurrentSet->nDataSavePeriod > 1000))
	{
		pCurrentSet->nDataSavePeriod = 60;
	}
	pCurrentSet->bAutoDataDelete = pApp.GetProfileInt(_T("Config"), _T("Auto Data Delete"), 1);
	if ((pCurrentSet->bAutoDataDelete < 0) || (pCurrentSet->bAutoDataDelete > 1))
	{
		pCurrentSet->bAutoDataDelete = 1;
	}

		//+add psh 110225
	pCurrentSet->nRemoteCustomCode = pApp.GetProfileInt(_T("Config"), _T("Remocon Custom Code"), 0);
	if ((pCurrentSet->nRemoteCustomCode < 0) || (pCurrentSet->nRemoteCustomCode > 12))
	{
		pCurrentSet->nRemoteCustomCode = 0;
	}
	pCurrentSet->nRemoteType = pApp.GetProfileInt(_T("Config"), _T("Remocon Type"), 0);
	if ((pCurrentSet->nRemoteType < 0) || (pCurrentSet->nRemoteType > 1))
	{
		pCurrentSet->nRemoteType = 0;
	}
	pCurrentSet->b2PCBA_WID = m_Ini.GetProfileInt(GENERAL_S, "Scan TWO LABEL");

	pCurrentSet->sAvSwitchBoxComPort = pApp.GetProfileString(_T("Config"), _T("AV SwitchBox ComPort"), "COM4");
	pCurrentSet->bAvSwitchBoxBuzzerMute = pApp.GetProfileInt(_T("Config"), _T("AV SwitchBox Buzzet Mute"), 1);

	pCurrentSet->nAvSwitchBoxInitVideoCh = pApp.GetProfileInt(_T("Config"), _T("AV SwitchBox Initialize Video Mode"), 1);

	pCurrentSet->bVersionCheckOnly = pApp.GetProfileInt(_T("Config"), _T("Version Check Only"), 0);

	pCurrentSet->nProcessType = pApp.GetProfileInt(_T("Config"), _T("Inspection Process Type"), 0);

	pCurrentSet->nModelInfo_Check = pApp.GetProfileInt(_T("Config"), _T("Model Info. Check Type"), 0);

	pCurrentSet->bFixtureIdCheck = pApp.GetProfileInt(_T("Config"), _T("Fixture ID Check"), 1);

	pCurrentSet->nJigUpType = pApp.GetProfileInt(_T("Config"), _T("JigUpType"), 0);

	pCurrentSet->nSoundInDeviceID = pApp.GetProfileInt(_T("Config"), _T("Sound Device ID"), 0);
	pCurrentSet->sSoundInDeviceName = pApp.GetProfileString(_T("Config"), _T("Sound Device Name"), "NC");

	pCurrentSet->bNoVideoCapture = pApp.GetProfileInt(_T("Config"), _T("No Video Capture"), 0);	
}

//+add kwmoon 071210
void CAcqVoltageSamples_IntClkDlg::SaveRegistrySetting()
{
	CIniAccess pApp;////CWinApp* pApp = AfxGetApp();
	CFile pFile;
	CFileException FileExcept;
	CString sTmp;
	CString sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";


	if (g_nRunningProcessNo == 1)
	{
		sIniPath = "D:\\DM_HDFT\\DM_HDFT_1.ini";
	}
	else
	{
		sIniPath = "D:\\DM_HDFT\\DM_HDFT_2.ini";
	}

	if (!pFile.Open(sIniPath, CFile::modeRead | CFile::modeWrite | CFile::modeCreate | CFile::shareDenyNone, &FileExcept))
	{
		char   szCause[255];
		FileExcept.GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause);
		return ;
	}
	pFile.Close();

	pApp.SetIniFile(sIniPath);


//	CString sTmp = _T("");
	CString sBaudRate = _T("");
	//	CurrentSet->nTotalNoTest		= g_nNoTested;
	//	CurrentSet->nTotalNoNg			= g_nFailed;
		//+add kwmoon 081004
	//	CurrentSet->nTotalNoUserStop	= g_nUserStop;

	pApp.WriteProfileString(_T("File"), _T("Current Seq"), CurrentSet->sSeqPath);
	pApp.WriteProfileString(_T("File"), _T("Current Full Seq"), CurrentSet->sFullSeqPath);
	pApp.WriteProfileString(_T("File"), _T("Current ModelIni"), CurrentSet->sModelIni);
	pApp.WriteProfileString(_T("File"), _T("Current Remocon"), CurrentSet->sRemoconTitle);
	pApp.WriteProfileString(_T("File"), _T("Current Pattern"), CurrentSet->sPatternTitle);

	pApp.WriteProfileString(_T("File"), _T("Current Chassis"), CurrentSet->sChassisName);
	pApp.WriteProfileString(_T("File"), _T("Current Model"), CurrentSet->sModelName);
	pApp.WriteProfileString(_T("File"), _T("Current Model Suffix Name"), CurrentSet->sModelSuffixName);

	pApp.WriteProfileString(_T("GMES"), _T("Current WorkOrder ID"), CurrentSet->sWorkOrderID);
	pApp.WriteProfileString(_T("GMES"), _T("Current Line ID"), CurrentSet->sLineID);
	pApp.WriteProfileString(_T("GMES"), _T("Current Equipment ID"), CurrentSet->sEquipmentID);
	pApp.WriteProfileString(_T("GMES"), _T("Current Operation ID"), CurrentSet->sOperationID);
	pApp.WriteProfileString(_T("GMES"), _T("Current Model ID"), CurrentSet->sModelID);
	pApp.WriteProfileString(_T("GMES"), _T("Current Model Name"), CurrentSet->sModelName_GMES);
	pApp.WriteProfileString(_T("GMES"), _T("Current Model Suffix"), CurrentSet->sModelSuffix);


	//+add kwmoon 080724
	pApp.WriteProfileString(_T("File"), _T("Current TestParam"), CurrentSet->sTestParamIni);

	//+add kwmoon 081024
	pApp.WriteProfileString(_T("File"), _T("Current ModelList"), CurrentSet->sModelListPath);

	pApp.WriteProfileInt(_T("Run"), _T("Run Type"), CurrentSet->nRunType);
	pApp.WriteProfileInt(_T("Run"), _T("Start Type"), CurrentSet->nRunStartType);
	pApp.WriteProfileInt(_T("Display"), _T("Display Type"), CurrentSet->nDisplayType);
	pApp.WriteProfileInt(_T("Display"), _T("PrintOut Type"), CurrentSet->nPrintType);
	pApp.WriteProfileInt(_T("Display"), _T("Comm Display"), CurrentSet->bCommDisplay);
	pApp.WriteProfileString(_T("File"), _T("Current Viewer"), CurrentSet->sViewerPath);

	pApp.WriteProfileString(_T("Folder"), _T("Current Folder"), CurrentSet->sModelFolder);
	pApp.WriteProfileString(_T("Folder"), _T("Current Grab Folder"), CurrentSet->sGrabFolder);
	pApp.WriteProfileString(_T("Folder"), _T("Current Ref Folder"), CurrentSet->sRefFolder);
	pApp.WriteProfileString(_T("Folder"), _T("Current Mask Folder"), CurrentSet->sMaskFolder);

	//+add kwmoon 080904
	pApp.WriteProfileString(_T("Folder"), _T("Current Server Folder"), CurrentSet->sServerFolder);
	//+add PSH 081029
	pApp.WriteProfileString(_T("Folder"), _T("Current Reference Image Root Folder"), CurrentSet->sRefRootFolder);
	//+add PSH 081211
	pApp.WriteProfileString(_T("Folder"), _T("Current Model Info  Root Foler"), CurrentSet->sModelInfoFolder);

	pApp.WriteProfileString(_T("Folder"), _T("ParmAdj Current Grab Folder"), CurrentSet->sParmAdjGrabFolder);
	pApp.WriteProfileString(_T("Folder"), _T("ParmAdj Current Ref Folder"), CurrentSet->sParmAdjRefFolder);
	pApp.WriteProfileString(_T("Folder"), _T("ParmAdj Current Mask Folder"), CurrentSet->sParmAdjMaskFolder);

	//	pApp.WriteProfileInt(_T("Config"), _T("LVDS Grabber Width"),			CurrentSet->nLvdsWidth);
	//	pApp.WriteProfileInt(_T("Config"), _T("LVDS Grabber Height"),			CurrentSet->nLvdsHeight);
	pApp.WriteProfileInt(_T("Config"), _T("Analog Grabber Width"), CurrentSet->nAnalogWidth);
	pApp.WriteProfileInt(_T("Config"), _T("Analog Grabber Height"), CurrentSet->nAnalogHeight);

	pApp.WriteProfileInt(_T("Config"), _T("Use User Retry"), CurrentSet->nUseUserRetry);

	//+add 090420(Modification No1)
	pApp.WriteProfileInt(_T("Config"), _T("Analog Grabber Type"), CurrentSet->nAnalogType);

	pApp.WriteProfileString(_T("Config"), _T("Pattern Generator ComPort"), CurrentSet->sPatternComPort);
	sBaudRate.Format("%d", CurrentSet->wPatternBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("Pattern Generator Baud Rate"), sBaudRate);

	pApp.WriteProfileString(_T("Config"), _T("HDMI Generator ComPort"), CurrentSet->sHDMIComPort);
	sBaudRate.Format("%d", CurrentSet->wHDMIBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("HDMI Generator Baud Rate"), sBaudRate);

	pApp.WriteProfileString(_T("Config"), _T("Thermometer ComPort"), CurrentSet->sThComPort);
	sBaudRate.Format("%d", CurrentSet->wThBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("Thermometer Baud Rate"), sBaudRate);
	pApp.WriteProfileInt(_T("Config"), _T("Use Thermometer"), CurrentSet->bUseTh);


	pApp.WriteProfileString(_T("Config"), _T("DIO Jig ComPort"), CurrentSet->sSM_DIOComPort);
	sBaudRate.Format("%d", CurrentSet->wSM_DIOBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("DIO Jig Baud Rate"), sBaudRate);

	pApp.WriteProfileInt(_T("Config"), _T("Use DIO Jig"), CurrentSet->bUseSM_DIO);

	pApp.WriteProfileString(_T("Config"), _T("TV ComPort"), CurrentSet->sTVComPort);
	//+del psh 080701
//	sBaudRate.Format("%d", CurrentSet->wTVBaudRate);
//	pApp.WriteProfileString(_T("Config"), _T("TV Baud Rate"), sBaudRate);
//-

	pApp.WriteProfileString(_T("Config"), _T("AV SwitchBox ComPort"), CurrentSet->sAvSwitchBoxComPort);
	sBaudRate.Format("%d", CurrentSet->wAvSwitchBoxBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("AV SwitchBox Baud Rate"), sBaudRate);

	pApp.WriteProfileString(_T("Config"), _T("Scanner ComPort"), CurrentSet->sScannerComPort);
	sBaudRate.Format("%d", CurrentSet->wScannerBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("Scanner Baud Rate"), sBaudRate);

	//+add kwmoon 080625
	pApp.WriteProfileString(_T("Config"), _T("IR Checker ComPort"), CurrentSet->sIrChkComPort);
	sBaudRate.Format("%d", CurrentSet->wIrChkBaudRate);
	pApp.WriteProfileString(_T("Config"), _T("IR Checker Baud Rate"), sBaudRate);

	pApp.WriteProfileInt(_T("Config"), _T("Use Pattern Generator"), CurrentSet->bUsePatternGen);
	//pApp.WriteProfileInt(_T("Config"), _T("Use TVComm Port"),				CurrentSet->bUseTVCommPort);
	pApp.WriteProfileInt(_T("Config"), _T("Use AVSwitchingBox"), CurrentSet->bUseAVSwitchBox);
	pApp.WriteProfileInt(_T("Config"), _T("Use Scanner"), CurrentSet->bUseScanner);
	pApp.WriteProfileInt(_T("Config"), _T("Use HDMI Generator"), CurrentSet->bUseHDMIGen);
	pApp.WriteProfileInt(_T("Config"), _T("Use IR Checker"), CurrentSet->bUseIrChk);

	pApp.WriteProfileInt(_T("Config"), _T("ADC Type"), (BOOL)(CurrentSet->nAdcType));
	pApp.WriteProfileInt(_T("Config"), _T("Auto Save Grab Image"), (BOOL)(CurrentSet->bSaveGrabImg));
	pApp.WriteProfileInt(_T("Config"), _T("Auto Save Processed Image"), (BOOL)(CurrentSet->bSaveProcImg));
	pApp.WriteProfileInt(_T("Config"), _T("Save Caption Test Image"), (BOOL)(CurrentSet->bSaveCaptionTestImg));
	pApp.WriteProfileInt(_T("Config"), _T("Save Moving Pic Test Image"), (BOOL)(CurrentSet->bSaveMovingPicTestImg));
	pApp.WriteProfileInt(_T("Config"), _T("Save Intermediate Image"), (BOOL)(CurrentSet->bSaveIntermediateImage));

	//+del kwmoon 080716
//	pApp.WriteProfileInt(_T("Config"), _T("Save Distribution Table"),		(BOOL)(CurrentSet->bSaveDistributionTable));

	//+add kwmoon 080710
	pApp.WriteProfileInt(_T("Config"), _T("Save Processing Time Data"), (BOOL)(CurrentSet->bSaveProcessingTimeData));

	//+add kwmoon 080716
	pApp.WriteProfileInt(_T("Config"), _T("Save Review Data"), (BOOL)(CurrentSet->bSaveReviewData));
	pApp.WriteProfileInt(_T("Config"), _T("Save Detail Result Data"), (BOOL)(CurrentSet->bSaveDetailResultData));


	pApp.WriteProfileInt(_T("Config"), _T("Audio Input Source"), CurrentSet->nAudioSource);

	pApp.WriteProfileInt(_T("Config"), _T("Save Result to Text File"), (BOOL)(CurrentSet->bSaveResult2Txt));
	pApp.WriteProfileInt(_T("Config"), _T("Save Result to Html File"), (BOOL)(CurrentSet->bSaveResult2Html));
	pApp.WriteProfileInt(_T("Config"), _T("Save Result to Csv File"), (BOOL)(CurrentSet->bSaveResult2Csv));

	pApp.WriteProfileInt(_T("Config"), _T("No of repeat execution"), (UINT)(CurrentSet->nNoRepeatExecution));
	//+del kwmoon 080715
//	pApp.WriteProfileInt(_T("Config"), _T("No of allowed error pixel"),	(UINT)(CurrentSet->nNoAllowedErrorPixel));
	pApp.WriteProfileInt(_T("Config"), _T("No of frames for refimage creation"), (UINT)(CurrentSet->nNoFrameForRefImageCreation));
	pApp.WriteProfileInt(_T("Config"), _T("Percentage of pixels in middle range"), (UINT)(CurrentSet->nPixelInMiddleRange));
	pApp.WriteProfileInt(_T("Config"), _T("Percentage of non-black pixels"), (UINT)(CurrentSet->nNonBlackPixel));

	//+add 090218(Modification No1)
	pApp.WriteProfileInt(_T("Config"), _T("No Used Colors"), (UINT)(CurrentSet->nNoUsedColors));

	//+del kwmoon 080715
//	pApp.WriteProfileInt(_T("Config"), _T("No of allowed error pixel for osd test"),	(UINT)(CurrentSet->nNoAllowedErrorPixelForOsdTest));

	pApp.WriteProfileInt(_T("Config"), _T("Delay Percentage"), (UINT)(CurrentSet->nDelayPercentage));
	//	pApp.WriteProfileInt(_T("Config"), _T("Uranous Grabber Mode"),			CurrentSet->nUranousMode);
		//+add psh 090630
	//	pApp.WriteProfileInt(_T("Config"), _T("LVDS OddDE Only"),			(UINT)CurrentSet->bOddDE_Only);

	//	pApp.WriteProfileInt(_T("Config"), _T("Color Bit Count"),				CurrentSet->nBitCount);
	//	pApp.WriteProfileInt(_T("Config"), _T("Total No of test"),				(UINT)(CurrentSet->nTotalNoTest));
	//	pApp.WriteProfileInt(_T("Config"), _T("Total No of Ng"),				(UINT)(CurrentSet->nTotalNoNg));

		//+add kwmoon 081004
	//	pApp.WriteProfileInt(_T("Config"), _T("Total No of User Stop"),			(UINT)(CurrentSet->nTotalNoUserStop));

	pApp.WriteProfileInt(_T("Config"), _T("No of Internal Retry"), CurrentSet->nNoRetry);

	//+add PSH 081030
	pApp.WriteProfileInt(_T("Config"), _T("Grab Image Check Area"), CurrentSet->nGrabCheckArea);

	pApp.WriteProfileInt(_T("Config"), _T("Inspection Process Type"), CurrentSet->nProcessType);

	pApp.WriteProfileInt(_T("Config"), _T("TVComm Port Echo"), (UINT)CurrentSet->bTVCommPortEcho);
	pApp.WriteProfileString(_T("Config"), _T("HDMI Roi Shape"), CurrentSet->sHDMIRoiShape);
	pApp.WriteProfileInt(_T("DataBase"), _T("Location"), (UINT)CurrentSet->nLocation);
	pApp.WriteProfileInt(_T("DataBase"), _T("Line Number"), (UINT)CurrentSet->nLineNo);
	pApp.WriteProfileInt(_T("DataBase"), _T("System Number"), (UINT)CurrentSet->nSystemNo);
	pApp.WriteProfileInt(_T("DataBase"), _T("Authority"), (UINT)CurrentSet->nAuthority);
	pApp.WriteProfileString(_T("DataBase"), _T("PassWord"), CurrentSet->strPassword);

	pApp.WriteProfileString(_T("DataBase"), _T("GMES Host IP"), CurrentSet->strGmesIP);
	pApp.WriteProfileInt(_T("DataBase"), _T("GMES Host Port"), CurrentSet->nGmesPort);
	//	pApp.WriteProfileString(_T("DataBase"), _T("MES DSN"),					CurrentSet->strMesDsn);
	//	pApp.WriteProfileString(_T("DataBase"), _T("MES USERID"),				CurrentSet->strMesUserId);
	//	pApp.WriteProfileString(_T("DataBase"), _T("MES PASSWORD"),			CurrentSet->strMesPassWord);

	pApp.WriteProfileInt(_T("DataBase"), _T("AUTO UPLOAD MES DATA"), (UINT)CurrentSet->bAutoUploadMes);

	//+add kwmoon 080502
	pApp.WriteProfileInt(_T("DataBase Upload"), _T("UPLOAD MES DATA"), (UINT)CurrentSet->bUploadMes);
	pApp.WriteProfileInt(_T("AUTO CHANGE MODEL"), _T("AUTO CHANGE MODEL"), (UINT)CurrentSet->bAutoGMES_ChangeModel);

	//+del kwmoon 080724
//	for(int nTmp = 0;InputDefined[nTmp].pszName != NULL; nTmp++)
//	{
//		pApp.WriteProfileInt(SRCMARGIN_S, InputDefined[nTmp].pszName, CurrentSet->nSrcMargin[nTmp]);
//	}

	//+add kwmoon 080523
	pApp.WriteProfileInt(_T("Config"), _T("AudioCheckMethod"), (UINT)CurrentSet->nAudioCheckMethod);

	//+add psh 090401
	pApp.WriteProfileInt(_T("Config"), _T("Data Save Period"), (UINT)CurrentSet->nDataSavePeriod);
	pApp.WriteProfileInt(_T("Config"), _T("Auto Data Delete"), (UINT)CurrentSet->bAutoDataDelete);

	//+add PSH 0811118
/*	pApp.WriteProfileString(_T("Config"), _T("Tool Option1"),			CurrentSet->sToolOption1);
	pApp.WriteProfileString(_T("Config"), _T("Tool Option2"),			CurrentSet->sToolOption2);
	pApp.WriteProfileString(_T("Config"), _T("Tool Option3"),			CurrentSet->sToolOption3);
	pApp.WriteProfileString(_T("Config"), _T("Tool Option4"),			CurrentSet->sToolOption4);
	pApp.WriteProfileString(_T("Config"), _T("Area Option1"),			CurrentSet->sAreaOption1);
*/
//	pApp.WriteProfileString(_T("Config"), _T("CPU Version"),			CurrentSet->sCPUVersion);
//	pApp.WriteProfileString(_T("Config"), _T("Micom Version"),			CurrentSet->sMicomVersion);
//	pApp.WriteProfileString(_T("Config"), _T("USB Version"),			CurrentSet->sUSBVersion);

	// 090120 External DFT
//	pApp.WriteProfileInt(_T("Config"), _T("Lvds Grabber Type"),		(UINT)CurrentSet->nLvdsGrabberType);

	//+add psh 110226
	pApp.WriteProfileInt(_T("Config"), _T("Remocon Custom Code"), (UINT)CurrentSet->nRemoteCustomCode);
	pApp.WriteProfileInt(_T("Config"), _T("Remocon Type"), (UINT)CurrentSet->nRemoteType);
	pApp.WriteProfileInt(_T("Config"), _T("Scan TWO LABEL"), (UINT)CurrentSet->b2PCBA_WID);


	pApp.WriteProfileInt(_T("Config"), _T("AV SwitchBox Buzzet Mute"), (UINT)CurrentSet->bAvSwitchBoxBuzzerMute);

	pApp.WriteProfileInt(_T("Config"), _T("AV SwitchBox Initialize Video Mode"), (UINT)CurrentSet->nAvSwitchBoxInitVideoCh);

	pApp.WriteProfileInt(_T("Config"), _T("Version Check Only"), CurrentSet->bVersionCheckOnly);

	pApp.WriteProfileInt(_T("Config"), _T("Model Info. Check Type"), CurrentSet->nModelInfo_Check);
	pApp.WriteProfileInt(_T("Config"), _T("Fixture ID Check"), CurrentSet->bFixtureIdCheck);
	pApp.WriteProfileInt(_T("Config"), _T("JigUpType"), CurrentSet->nJigUpType);

	pApp.WriteProfileInt(_T("Config"), _T("Sound Device ID"), CurrentSet->nSoundInDeviceID);
	pApp.WriteProfileString(_T("Config"), _T("Sound Device Name"), CurrentSet->sSoundInDeviceName);
	pApp.WriteProfileInt(_T("Config"), _T("No Video Capture"), CurrentSet->bNoVideoCapture);

}

//+change kwmoon 081024
void CAcqVoltageSamples_IntClkDlg::SM_ModelOpen(void)
{
//	CWinApp* pApp = AfxGetApp();

	int		nNoModel = 0;
	CString sTmp = _T("");
	CString sMsg = _T("");
	BOOL bFlag;
	BOOL bGrabFlag;
	//	UINT nVal1;//

	if (OpenModelListFile(CurrentSet->sModelListPath, nNoModel, g_Divisions) == FALSE) return;

	//+add PSH 090507
	//bFlag = m_SignalEnable;//g_pView->wIn_Flag;
	//090615
	//AudioMeasureStop();
	//-
	//StopGrabThread();

	//Sleep(100);

	CSelectChassisModelDlg dlg;
	dlg.m_nNoModel = nNoModel;

	if (dlg.DoModal() == IDOK)
	{
#if 1		//+move kwmoon 080818
		CurrentSet->sSeqPath = CurrentSet->sServerFolder + dlg.m_szSeqFilePath;
		CurrentSet->sModelIni = CurrentSet->sModelInfoFolder + dlg.m_szModelInfoFilePath;
		CurrentSet->sModelFolder = CurrentSet->sServerFolder + dlg.m_szModelInfoFilePath.Left(dlg.m_szModelInfoFilePath.ReverseFind('\\'));
		CurrentSet->sRefFolder = CurrentSet->sRefRootFolder + dlg.m_szRefImgFolder;
		CurrentSet->sMaskFolder = CurrentSet->sRefFolder + "\\Mask";

		CurrentSet->sChassisName = dlg.m_sSelChassis;
		CurrentSet->sModelName = dlg.m_sSelModel;

		//add PSH 20091019
		if (!FileExists(CurrentSet->sRefFolder)) {
			CreateFullPath(CurrentSet->sRefFolder);
			CreateFullPath(CurrentSet->sMaskFolder);
		}


		CString  lsOldnPort = CurrentSet->sTVComPort;
		int lOldnBaud = CurrentSet->wTVBaudRate;
		int lOldnParity = CurrentSet->nTVParity;
		//=====================
		// Open Model.ini File 
		//=====================
		if (FileExists(CurrentSet->sModelIni))
		{
			OpenModelIniFile(CurrentSet->sModelIni);

			//AvSwitchBoxCtrl.SetVideoOutType(CurrentSet->nAnalogType);

			//bGrabFlag = g_pView->m_bGrabThreadRunning;
			//StopGrabThread();
			//Sleep(500);
			//AnalogControl.SetVideoSourceType(CurrentSet->nAnalogType);
			//Sleep(500);
			//if (bGrabFlag) StartGrabThread();
			SetGrabInfo(&g_GrabImage);
		}
		else
		{
			SaveModelIniFile(CurrentSet->sModelIni);
				sMsg.Format("Failed to load file.\n[%s]",CurrentSet->sModelIni);
				AfxMessageBox(sMsg);
			//CModelInfoCreate dlg;

			//dlg.m_sModelInfo_FileName = CurrentSet->sModelIni;
			//dlg.DoModal();
		}

		if (CurrentSet->sModelSuffixName.Find(CurrentSet->sModelName) == -1)
		{
			CurrentSet->sModelSuffixName = CurrentSet->sModelName;
			if (!CurrentSet->sModelSuffix.IsEmpty() )
			{
				CurrentSet->sModelSuffixName += ".";
				CurrentSet->sModelSuffixName += CurrentSet->sModelSuffix;
			}
		}
		m_cLbModel.put_Caption((LPCSTR)CurrentSet->sModelName);
		// position change PSH 080911
		SaveRegistrySetting();
		LoadRegistrySetting(CurrentSet);

		//====================
		// Open Sequence File 
		//====================
		if (FileExists(CurrentSet->sSeqPath))
		{
			if (Prescan(CurrentSet->sSeqPath) == TRUE)
			{
				CurrentSet->bCompiled = TRUE;
				CurrentSet->lTime = GetModifyTime(CurrentSet->sSeqPath);
			}
			else
			{
				DeleteStepList();
				CurrentSet->bCompiled = FALSE;

				//+del kwmoon 081024
				// change PSH 080603
			//	CurrentSet->sSeqPath = dlg.m_strSeqFilePath;
				CurrentSet->lTime = 0;
			}
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sSeqPath);
			AfxMessageBox(sMsg);

			DeleteStepList();
			CurrentSet->bCompiled = FALSE;
			CurrentSet->sSeqPath = _T("");
			CurrentSet->lTime = 0;
		}


		//==========================
		// Open Test Parameter File 
		//==========================
		if (CurrentSet->sTestParamIni.IsEmpty())
		{
			CurrentSet->sTestParamIni = m_szExePath + "\\TestParam.Ini";
		}

		if (FileExists(CurrentSet->sTestParamIni))
		{
			OpenTestParamIniFile(CurrentSet->sTestParamIni);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sTestParamIni);
			MessageBox(sMsg);
		}

		//===================
		// Open Pattern File 
		//===================
		if (CurrentSet->sPatternTitle.IsEmpty())
		{
			CurrentSet->sPatternTitle = m_szExePath + "\\Pattern.pat";
		}

		if (FileExists(CurrentSet->sPatternTitle))
		{
			OpenPatternFile(CurrentSet->sPatternTitle);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sPatternTitle);
			AfxMessageBox(sMsg);
		}

		//===================
		// Open Remocon File 
		//===================
		if (CurrentSet->sRemoconTitle.IsEmpty())
		{
			CurrentSet->sRemoconTitle = m_szExePath + "\\Remote\\DM_DFT_HT_REMOTE.rmt";
		}
		//switch (CurrentSet->nRemoteCustomCode)
		//{
		//case REMOCON_HT:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_HT_REMOTE.rmt";
		//	//	nVal1 = 0x2C;
		//	break;

		//case REMOCON_MINI:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_MINI_REMOTE.rmt";
		//	//	nVal1 = 0x10;
		//	break;

		//case REMOCON_BD:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_BD_REMOTE.rmt";
		//	break;

		//case REMOCON_PN:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_PN_REMOTE.rmt";
		//	break;

		//case REMOCON_LO:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LO_REMOTE.rmt";
		//	break;

		//case REMOCON_NA:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_NA_REMOTE.rmt";
		//	break;

		//case REMOCON_SO:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_SO_REMOTE.rmt";
		//	break;

		//case REMOCON_CM:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_CM_REMOTE.rmt";
		//	break;

		//case REMOCON_GS:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_GS_REMOTE.rmt";
		//	break;

		//case REMOCON_TB:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_TB_REMOTE.rmt";
		//	break;

		//case REMOCON_SH:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSH_REMOTE.rmt";
		//	break;

		//case REMOCON_SI:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSI_REMOTE.rmt";
		//	break;

		//case REMOCON_JV:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_JVC_REMOTE.rmt";
		//	break;

		//default:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_HT_REMOTE.rmt";
		//	//	nVal1 = 0x2C;
		//	break;
		//}


		if (FileExists(CurrentSet->sRemoconTitle))
		{
			OpenRemoteFile(CurrentSet->sRemoconTitle);
			//	AvSwitchBoxCtrl.SetAvSwitch(SET_CUSTOM_CODE, MAX_AVSWITCH_WAIT_DELAY,  nVal1, 0);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sRemoconTitle);
			MessageBox(sMsg);
		}

		//AvSwitchBoxCtrl.SetAvSwitch(REMOTE_TYPE_SEL, MAX_AVSWITCH_WAIT_DELAY,  CurrentSet->nRemoteType, 0);

		//====================
		// Open Template File 
		//====================
		if (!CurrentSet->sFullSeqPath.IsEmpty())
		{
			if (FileExists(CurrentSet->sFullSeqPath))
			{
				OpenFullSeq(CurrentSet->sFullSeqPath);
			}
		}

		//		UpdateInfo(MODEL, CurrentSet->sModelFolder);
		UpdateInfo(MODEL, CurrentSet->sModelName);
		UpdateInfo(CHASSIS, CurrentSet->sChassisName);
		UpdateInfo(REF, CurrentSet->sRefFolder);
		UpdateInfo(SEQ, CurrentSet->sSeqPath);

		//ctrlSuffixEdit.SetWindowText(CurrentSet->sModelSuffixName);

		/*
				UpdateInfo(TOOL_OPTION1,CurrentSet->sToolOption1);
				UpdateInfo(TOOL_OPTION2,CurrentSet->sToolOption2);
				UpdateInfo(TOOL_OPTION3,CurrentSet->sToolOption3);
				UpdateInfo(TOOL_OPTION4,CurrentSet->sToolOption4);
				UpdateInfo(TOOL_OPTION5,CurrentSet->sToolOption5);
				UpdateInfo(AREA_OPTION1,CurrentSet->sAreaOption1);
				UpdateInfo(CPU_VERSION,CurrentSet->sCPUVersion);
				UpdateInfo(MICOM_VERSION,CurrentSet->sMicomVersion);
				UpdateInfo(USB_VERSION,CurrentSet->sUSBVersion);
		*/

		UpdateVersionInfo();

		InsertStepData2Grid(CurrentSet->nDisplayType);

		//+add psh 080701

		if ((TVCommCtrl.m_bPortOpen != 1)
			|| (lsOldnPort != CurrentSet->sTVComPort)
			|| (lOldnBaud != CurrentSet->wTVBaudRate)
			|| (lOldnParity != CurrentSet->nTVParity))
		{
			if (TVCommCtrl.m_bPortOpen)
			{
				TVCommCtrl.PortClose();
//				_Wait(150);
			}

			if (TVCommCtrl.Create(CurrentSet->sTVComPort, CurrentSet->wTVBaudRate) == FALSE)
			{
				TVCommCtrl.PortClose();
				TVCommCtrl.Create(CurrentSet->sTVComPort, CurrentSet->wTVBaudRate);
				if (TVCommCtrl.m_bPortOpen == FALSE)
				{
					CString szErrMsg;
					szErrMsg.Format("Failed to open COM port (%s)", CurrentSet->sTVComPort);
					MessageBox(szErrMsg);
				}
			}
			//-
		}
#endif
	}

	//+add PSH 090615
//	StartGrabThread();
	//	if(bFlag) SetTimer(2, 2000, NULL);
}


void CAcqVoltageSamples_IntClkDlg::UpdateInfo(int nIndex, CString s)
{
	CString sTmp, sModelName, sModelFolder;
	//SaveModelIniFile(CurrentSet->sModelIni);

	switch (nIndex)
	{
	case SEQ:
		m_stcModelFolder.SetWindowText(_T(s));
		break;
	case MODEL:
		m_stcSeqName.SetWindowText(_T(s));
		break;
	case CHASSIS:
		m_stcChassisName.SetWindowText(_T(s));
		break;
	case REF:
		m_stcRefFolder.SetWindowText(_T(s));
		break;
	//case TESTED:
	//	m_ctrLEDTested.SetWindowText(_T(s));
	//	break;
	//case FAILED:
	//	m_ctrLEDFailed.SetWindowText(_T(s));
	//	break;
	//case RATE:
	//	m_ctrLEDRate.SetWindowText(_T(s));
	//	break;
	case STATUS:
		m_stcStatus.SetWindowText(_T(s));
		break;
	case MODE:
		m_stcMode.SetWindowText(_T(s));
		break;
	case TIME:
		m_stcTime.SetWindowText(_T(s));
		break;
	case PROG_NO:
		//			m_stcProgramNo.SetWindowText(_T(s)); 
		break;
	case AUDIO_L_FREQ:
		//			m_stcLFreq.SetWindowText(_T(s));
		break;
	case AUDIO_R_FREQ:
		//			m_stcRFreq.SetWindowText(_T(s));
		break;
	case AUDIO_L_LEVEL:
		//			m_stcLLevel.SetWindowText(_T(s));
		break;
	case AUDIO_R_LEVEL:
		//			m_stcRLevel.SetWindowText(_T(s));
		break;

	//case LED_STATE:
	//	//m_LedsMesOn.EnableWindow(CurrentSet->bGMES_Connection);
	//	m_LedsMesOn.SetLedState(CurrentSet->bUploadMes);
	//	//	m_LedsMesOn.SetLedState(1);
	//	break;
	default:
		break;
	}

}



LRESULT  CAcqVoltageSamples_IntClkDlg::OnChangeModelOpen(WPARAM wParam, LPARAM lParam)
{

	CString lFindName;
	lFindName = CurrentSet->sModelSuffixName;
	CString str;
	//CString lFindName;
	CString lFoundedName;
	lFindName = CurrentSet->sModelSuffixName;
	//lFindName.Replace(".", "_");
	str = "Check S/N is";
	str += lFindName;
	str += " MODEL. \r\n \r\n";
	str += "  Do You Change MODEL ?";

	//	if(IDOK == MessageWindow(str))
	if (IDYES == MessageBox(str, "New Model Detected", MB_YESNO))
	{
		if (0 == ChangeModelCheckOpen(lFindName))
		{
			MessageBox("New Model Not Found!!");
		}
	}
	return 0;
	////////////////////////////////////////////////////////////////

}




int  CAcqVoltageSamples_IntClkDlg::ChangeModelCheckOpen(CString lNewModelName)
{
	CWinApp* pApp = AfxGetApp();

	int		nNoModel = 0;
	CString sTmp = _T("");
	CString sMsg = _T("");
	BOOL bFlag;
	BOOL bFindFlag;
	BOOL bGrabFlag;
	POSITION	Pos = NULL;
	CModelData* pModelData = NULL;
	//	UINT nVal1;//

	if (OpenModelListFile(CurrentSet->sModelListPath, nNoModel, g_Divisions) == FALSE) return 0;

	//+add PSH 090507
//	bFlag = m_SignalEnable;//g_pView->wIn_Flag;
	//090615
//	AudioMeasureStop();
	//-
//	StopGrabThread();

	Sleep(100);
	//BP250 - N.DJPNLLM
	CString str;
	CString lFindName;
	CString lFoundedName;
	lFindName = lNewModelName;
	//lFindName.Replace(".", "_");
	//str = "Check S/N is";
	//str += lFindName;
	//str += " MODEL. \r\n \r\n";
	//str += "  Do You Change MODEL ?";

	//	if(IDOK == MessageWindow(str))
	if (1) // (IDYES == MessageBox(str, "New Model Detected", MB_YESNO))
	{

		//if (dlg.DoModal() == IDOK)
		Pos = CurrentSet->ModelList.GetHeadPosition();
		bFindFlag = 0;
		while (Pos)
		{
			pModelData = CurrentSet->ModelList.GetNext(Pos);

			if (pModelData->m_szChassisName != _T(""))
			{
				if (pModelData->m_szModelName.Find(lFindName) >= 0)
				{
					//lFindName = pModelData->m_szModelName;
					lFoundedName = pModelData->m_szModelName;
					bFindFlag = 1;
					break;
				}
			}
		}
	}
	else
	{
		return 0;
	}

	//CurrentSet->sModelSuffixName;
	if (bFindFlag == 1)
	{
		//+move kwmoon 080818
		CurrentSet->sSeqPath = CurrentSet->sServerFolder + pModelData->m_szSeqFilePath;
		CurrentSet->sModelIni = CurrentSet->sModelInfoFolder + pModelData->m_szModelInfoFilePath;
		CurrentSet->sModelFolder
			= CurrentSet->sServerFolder
			+ pModelData->m_szModelInfoFilePath.Left(pModelData->m_szModelInfoFilePath.ReverseFind('\\'));


		CurrentSet->sRefFolder = CurrentSet->sRefRootFolder + pModelData->m_szRefImgFolder;// .m_szRefImgFolder;
		CurrentSet->sMaskFolder = CurrentSet->sRefFolder + "\\Mask";

		CurrentSet->sChassisName = pModelData->m_szChassisName;// .m_sSelChassis;
		CurrentSet->sModelName = pModelData->m_szModelName;;

		//add PSH 20091019
		if (!FileExists(CurrentSet->sRefFolder)) {
			CreateFullPath(CurrentSet->sRefFolder);
			CreateFullPath(CurrentSet->sMaskFolder);
		}

		//=====================
		// Open Model.ini File 

		CString  lsOldnPort = CurrentSet->sTVComPort;
		int lOldnBaud = CurrentSet->wTVBaudRate;
		int lOldnParity = CurrentSet->nTVParity;

		//=====================
		if (FileExists(CurrentSet->sModelIni))
		{

			OpenModelIniFile(CurrentSet->sModelIni);

			//AvSwitchBoxCtrl.SetVideoOutType(CurrentSet->nAnalogType);

			//bGrabFlag = g_pView->m_bGrabThreadRunning;
			//StopGrabThread();
			Sleep(500);
//			AnalogControl.SetVideoSourceType(CurrentSet->nAnalogType);
			//Sleep(500);
			//if (bGrabFlag) StartGrabThread();
			SetGrabInfo(&g_GrabImage);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]",CurrentSet->sModelIni);
			AfxMessageBox(sMsg);
			SaveModelIniFile(CurrentSet->sModelIni);
			//CModelInfoCreate dlg;

			//dlg.m_sModelInfo_FileName = CurrentSet->sModelIni;
			//dlg.DoModal();
		}

		// position change PSH 080911
		SaveRegistrySetting();

		//====================
		// Open Sequence File 
		//====================
		if (FileExists(CurrentSet->sSeqPath))
		{
			if (Prescan(CurrentSet->sSeqPath) == TRUE)
			{
				CurrentSet->bCompiled = TRUE;
				CurrentSet->lTime = GetModifyTime(CurrentSet->sSeqPath);
			}
			else
			{
				DeleteStepList();
				CurrentSet->bCompiled = FALSE;

				//+del kwmoon 081024
				// change PSH 080603
			//	CurrentSet->sSeqPath = dlg.m_strSeqFilePath;
				CurrentSet->lTime = 0;
			}
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sSeqPath);
			AfxMessageBox(sMsg);

			DeleteStepList();
			CurrentSet->bCompiled = FALSE;
			CurrentSet->sSeqPath = _T("");
			CurrentSet->lTime = 0;
		}


		//==========================
		// Open Test Parameter File 
		//==========================
		if (CurrentSet->sTestParamIni.IsEmpty())
		{
			CurrentSet->sTestParamIni = m_szExePath + "\\TestParam.Ini";
		}

		if (FileExists(CurrentSet->sTestParamIni))
		{
			OpenTestParamIniFile(CurrentSet->sTestParamIni);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sTestParamIni);
			AfxMessageBox(sMsg);
		}

		//===================
		// Open Pattern File 
		//===================
		if (CurrentSet->sPatternTitle.IsEmpty())
		{
			CurrentSet->sPatternTitle = m_szExePath + "\\Pattern.pat";
		}

		if (FileExists(CurrentSet->sPatternTitle))
		{
			OpenPatternFile(CurrentSet->sPatternTitle);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sPatternTitle);
			AfxMessageBox(sMsg);
		}

		//===================
		// Open Remocon File 
		//===================
		if(CurrentSet->sRemoconTitle.IsEmpty())
		{
			CurrentSet->sRemoconTitle = m_szExePath + "\\Remote\\DM_DFT_HT_REMOTE.rmt";
		}

		//switch (CurrentSet->nRemoteCustomCode)
		//{
		//case REMOCON_HT:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_HT_REMOTE.rmt";
		//	//	nVal1 = 0x2C;
		//	break;

		//case REMOCON_MINI:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_MINI_REMOTE.rmt";
		//	//	nVal1 = 0x10;
		//	break;

		//case REMOCON_BD:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_BD_REMOTE.rmt";
		//	break;

		//case REMOCON_PN:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_PN_REMOTE.rmt";
		//	break;

		//case REMOCON_LO:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LO_REMOTE.rmt";
		//	break;

		//case REMOCON_NA:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_NA_REMOTE.rmt";
		//	break;

		//case REMOCON_SO:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_SO_REMOTE.rmt";
		//	break;

		//case REMOCON_CM:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_CM_REMOTE.rmt";
		//	break;

		//case REMOCON_GS:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_GS_REMOTE.rmt";
		//	break;

		//case REMOCON_TB:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSC_TB_REMOTE.rmt";
		//	break;

		//case REMOCON_SH:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSH_REMOTE.rmt";
		//	break;

		//case REMOCON_SI:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_LSI_REMOTE.rmt";
		//	break;

		//case REMOCON_JV:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_JVC_REMOTE.rmt";
		//	break;

		//default:
		//	CurrentSet->sRemoconTitle = m_szExePath + "\\DM_DFT_HT_REMOTE.rmt";
		//	//	nVal1 = 0x2C;
		//	break;
		//}


		if (FileExists(CurrentSet->sRemoconTitle))
		{
			OpenRemoteFile(CurrentSet->sRemoconTitle);

		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sRemoconTitle);
			AfxMessageBox(sMsg);
		}

		//AvSwitchBoxCtrl.SetAvSwitch(REMOTE_TYPE_SEL, MAX_AVSWITCH_WAIT_DELAY,  CurrentSet->nRemoteType, 0);

		//====================
		// Open Template File 
		//====================
		if (!CurrentSet->sFullSeqPath.IsEmpty())
		{
			if (FileExists(CurrentSet->sFullSeqPath))
			{
				OpenFullSeq(CurrentSet->sFullSeqPath);
			}
		}

		//		UpdateInfo(MODEL, CurrentSet->sModelFolder);
		UpdateInfo(MODEL, CurrentSet->sModelName);
		UpdateInfo(CHASSIS, CurrentSet->sChassisName);
		UpdateInfo(REF, CurrentSet->sRefFolder);
		UpdateInfo(SEQ, CurrentSet->sSeqPath);

		//ctrlSuffixEdit.SetWindowText(CurrentSet->sModelSuffixName);

		/*
				UpdateInfo(TOOL_OPTION1,CurrentSet->sToolOption1);
				UpdateInfo(TOOL_OPTION2,CurrentSet->sToolOption2);
				UpdateInfo(TOOL_OPTION3,CurrentSet->sToolOption3);
				UpdateInfo(TOOL_OPTION4,CurrentSet->sToolOption4);
				UpdateInfo(TOOL_OPTION5,CurrentSet->sToolOption5);
				UpdateInfo(AREA_OPTION1,CurrentSet->sAreaOption1);
				UpdateInfo(CPU_VERSION,CurrentSet->sCPUVersion);
				UpdateInfo(MICOM_VERSION,CurrentSet->sMicomVersion);
				UpdateInfo(USB_VERSION,CurrentSet->sUSBVersion);
		*/

		UpdateVersionInfo();

		InsertStepData2Grid(CurrentSet->nDisplayType);


		if ((TVCommCtrl.m_bPortOpen != 1)
			|| (lsOldnPort != CurrentSet->sTVComPort)
			|| (lOldnBaud != CurrentSet->wTVBaudRate)
			|| (lOldnParity != CurrentSet->nTVParity))
		{
			//+add psh 080701
			if (TVCommCtrl.m_bPortOpen)
			{
				TVCommCtrl.PortClose();
//				_Wait(150);
			}

			if (TVCommCtrl.Create(CurrentSet->sTVComPort, CurrentSet->wTVBaudRate) == FALSE)
			{
				TVCommCtrl.PortClose();
				TVCommCtrl.Create(CurrentSet->sTVComPort, CurrentSet->wTVBaudRate);
				if (TVCommCtrl.m_bPortOpen == FALSE)
				{
					CString szErrMsg;
					szErrMsg.Format("Failed to open COM port (%s)", CurrentSet->sTVComPort);
					AfxMessageBox(szErrMsg);
				}
			}
		}


		//-
	}

	//+add PSH 090615
	//StartGrabThread();
	//	if(bFlag) SetTimer(2, 2000, NULL);

	if (bFindFlag == 1)
		return 1;
	else
		return 0;

}
void CAcqVoltageSamples_IntClkDlg::InitSubClassItem()
{
	COLORREF crBackColor = RGB(225, 225, 198);
	COLORREF crPushColor = RGB(238, 239, 231);

	m_stcModelFolder.SubclassDlgItem(IDC_MODEL_FOLDER_STATIC, this);
	m_stcModelFolder.SetBkColor(crBackColor);
	m_stcModelFolder.SetTextColor(RGB(0, 0, 0));
	//	m_stcModelFolder.SetPath (TRUE);

	m_stcRefFolder.SubclassDlgItem(IDC_REF_FOLDER_STATIC, this);
	m_stcRefFolder.SetBkColor(crBackColor);
	m_stcRefFolder.SetTextColor(RGB(0, 0, 0));
	//	m_stcRefFolder.SetPath (TRUE);

	m_stcBarCode1.SubclassDlgItem(IDC_BARCODE_STATIC1, this);
	m_stcBarCode1.SetBkColor(crBackColor);
	m_stcBarCode1.SetTextColor(RGB(0, 0, 0));


	m_stcBarCode2.SubclassDlgItem(IDC_BARCODE_STATIC2, this);
	m_stcBarCode2.SetBkColor(crBackColor);
	m_stcBarCode2.SetTextColor(RGB(0, 0, 0));


	m_stcChassisName.SubclassDlgItem(IDC_CHASSISNAME, this);
	m_stcChassisName.SetBkColor(crBackColor);
	m_stcChassisName.SetTextColor(RGB(0, 0, 0));

	m_stcSeqName.SubclassDlgItem(IDC_SEQFILENAME, this);
	m_stcSeqName.SetBkColor(crBackColor);
	m_stcSeqName.SetTextColor(RGB(0, 0, 0));

	m_stcMode.SubclassDlgItem(IDC_TESTMODE, this);
	m_stcMode.SetBkColor(RGB(255, 255, 255));

	m_stcStatus.SubclassDlgItem(IDC_CURRENTSTATUS, this);
	m_stcStatus.SetBkColor(RGB(0, 0, 255));
	m_stcStatus.SetTextColor(RGB(255, 255, 255));

	m_stcTime.SubclassDlgItem(IDC_TESTTIME, this);
	m_stcTime.SetBkColor(crBackColor);
	m_stcTime.SetTextColor(RGB(0, 0, 0));

	m_stcCycleTime.SubclassDlgItem(IDC_CYCLE_TIME, this);
	m_stcCycleTime.SetBkColor(crBackColor);
	m_stcCycleTime.SetTextColor(RGB(0, 0, 0));
//
//	m_ctrLEDTested.SubclassDlgItem(IDC_TESTNUMBER, this);
//	m_ctrLEDFailed.SubclassDlgItem(IDC_FAILNUMBER, this);
//	m_ctrLEDRate.SubclassDlgItem(IDC_FAILRATE, this);
//
//	//+add kwmoon 071015 : [2in1]
//	m_ctrLEDTested.SetBkColor(RGB(189, 231, 97));
//	m_ctrLEDTested.SetTextColor(RGB(0, 0, 0));
//	m_ctrLEDFailed.SetBkColor(RGB(189, 231, 97));
//	m_ctrLEDFailed.SetTextColor(RGB(0, 0, 0));
//	m_ctrLEDRate.SetBkColor(RGB(189, 231, 97));
//	m_ctrLEDRate.SetTextColor(RGB(0, 0, 0));
//	//-
//
////	ctrlSummaryGrid.SubclassDlgItem(IDC_MAINVIEW_GRID, this);
//
//	ctrlTestProgress.SubclassDlgItem(IDC_TEST_PROGRESS, this);
//	ctrlTestProgress.SetTextColor(RGB(255, 128, 64), RGB(255, 255, 255));
//
//	ctrlTestProgress.SetGradientColors(RGB(0, 0, 255), RGB(0, 0, 255));
//	ctrlTestProgress.SetPos(0);
//	ctrlTestProgress.SetShowPercent();
//	ctrlTestProgress.SetTiedText(TRUE);
//
//	ctrlImgProg.SubclassDlgItem(IDC_IMG_PROC_PROG, this);
//	ctrlImgProg.SetBkColor(DARK_BLACK_COLOR);
//	ctrlImgProg.SetGradientColors(LIGHT_BLUE_COLOR, DARK_BLUE_COLOR);
//	ctrlImgProg.SetPos(0);
//
//	ctrlTestStep.SubclassDlgItem(IDC_TESTSTEP, this);
//	ctrlTestSubStep.SubclassDlgItem(IDC_TEST_SUBSTEP, this);
//
//	ctrlTestStep.SetBkColor(RGB(189, 231, 97));
//	ctrlTestStep.SetTextColor(RGB(0, 0, 0));
//
//	ctrlTestSubStep.SetBkColor(RGB(189, 231, 97));
//	ctrlTestSubStep.SetTextColor(RGB(0, 0, 0));
//
//	ctrlTestSubStep.SetWindowText(_T(""));
//
//	ctrlFixtureID.SubclassDlgItem(IDC_FIXTURE_ID, this);
//	ctrlFixtureID.SetBkColor(RGB(195, 231, 197));
//	ctrlFixtureID.SetTextColor(RGB(0, 0, 0));
//
//	ctrlStepTarget_V.SubclassDlgItem(IDC_STEP_VIDEO_T, this);
//	ctrlStepMeasur_V.SubclassDlgItem(IDC_STEP_VIDEO_M, this);
//	ctrlStepTarget_A.SubclassDlgItem(IDC_STEP_AUDIO_T, this);
//	ctrlStepMeasur_A.SubclassDlgItem(IDC_STEP_AUDIO_M, this);
//
//	ctrlStepTarget_V.SetBkColor(RGB(189, 231, 97));
//	ctrlStepTarget_V.SetTextColor(RGB(0, 0, 0));
//	ctrlStepMeasur_V.SetBkColor(RGB(189, 231, 97));
//	ctrlStepMeasur_V.SetTextColor(RGB(0, 0, 0));
//	ctrlStepTarget_A.SetBkColor(RGB(189, 231, 97));
//	ctrlStepTarget_A.SetTextColor(RGB(0, 0, 0));
//	ctrlStepMeasur_A.SetBkColor(RGB(189, 231, 97));
//	ctrlStepMeasur_A.SetTextColor(RGB(0, 0, 0));
//
//	ctrlWipIDLabel.SubclassDlgItem(IDC_STATIC_WIP_ID_LABEL, this);
//	ctrlWipIDLabel.SetBkColor(RGB(195, 231, 197));
//	ctrlWipIDLabel.SetTextColor(RGB(0, 0, 0));
//
//	ctrlWipIDLabel2.SubclassDlgItem(IDC_STATIC_WIP_ID_LABEL2, this);
//	ctrlWipIDLabel2.SetBkColor(RGB(195, 231, 197));
//	ctrlWipIDLabel2.SetTextColor(RGB(0, 0, 0));
//
//
//
//	ctrlStepTarget_V.SetWindowText(_T(""));
//	ctrlStepMeasur_V.SetWindowText(_T(""));
//	ctrlStepTarget_A.SetWindowText(_T(""));
//	ctrlStepMeasur_A.SetWindowText(_T(""));
//


	//if (CurrentSet->bUseScanner) {
	//	ctrlWipIdEdit.SetReadOnly(TRUE);
	//	ctrlWipIdEdit2.SetReadOnly(TRUE);

	//	//InitScanner(CurrentSet->sScannerComPort, CurrentSet->wScannerBaudRate);
	//	//CurrentSet->bUseScanner = TRUE;
	//	ctrlWipIDLabel.SetBkColor(0x00FF00);
	//	if (CurrentSet->b2PCBA_WID == 1)
	//		ctrlWipIDLabel2.SetBkColor(0x00FF00);
	//	else
	//		ctrlWipIDLabel2.SetBkColor(0x808080);

	//}
	//else {
	//	ctrlWipIdEdit.SetReadOnly(FALSE);
	//	if (CurrentSet->b2PCBA_WID == 1)
	//		ctrlWipIdEdit2.SetReadOnly(FALSE);
	//	else
	//		ctrlWipIdEdit2.SetReadOnly(TRUE);

	//	CurrentSet->bUseScanner = FALSE;
	//	ctrlWipIDLabel.SetBkColor(0x808080);
	//	ctrlWipIDLabel2.SetBkColor(0x808080);
	//}
	//ctrlWipIdEdit.SubclassDlgItem(IDC_EDIT_WIPID, this);
	//ctrlWipIdEdit.SetWindowText(_T(""));
	//m_strWipId = _T("");
	//m_nInsertSel = 0;

	//ctrlWipIdEdit2.SubclassDlgItem(IDC_EDIT_WIPID2, this);
	//ctrlWipIdEdit2.SetWindowText(_T(""));
	//m_strWipId2 = _T("");




	//ctrlSuffixEdit.SubclassDlgItem(IDC_EDIT_SUFFIX, this);
	//ctrlSuffixEdit.SetWindowText(_T(""));

	//+add kwmoon 080502
//	ctrlToolOptionTitle.SubclassDlgItem(IDC_EDIT_TOOL_OPTION_TITLE, this);
//	ctrlToolOptionTitle.SetWindowText(_T("TOOL OPTION"));
//	ctrlAreaOptionTitle.SubclassDlgItem(IDC_EDIT_AREA_OPTION_TITLE, this);
//	ctrlAreaOptionTitle.SetWindowText(_T("AREA OPTION"));
	//ctrlAudioLTitle.SubclassDlgItem(IDC_EDIT_AUDIO_L_TITLE, this);
	//ctrlAudioLTitle.SetWindowText(_T("AUDIO-L"));
	//ctrlAudioRTitle.SubclassDlgItem(IDC_EDIT_AUDIO_R_TITLE, this);
	//ctrlAudioRTitle.SetWindowText(_T("AUDIO-R"));

//	ctrlCPUVersionTitle.SubclassDlgItem(IDC_EDIT_CPU_VERSION_TITLE, this);
//	ctrlCPUVersionTitle.SetWindowText(_T("CPU Ver"));
//	ctrlMicomVersionTitle.SubclassDlgItem(IDC_EDIT_MICOM_VERSION_TITLE, this);
//	ctrlMicomVersionTitle.SetWindowText(_T("MICOM Ver"));
//	ctrlUSBVersionTitle.SubclassDlgItem(IDC_EDIT_USB_VERSION_TITLE, this);
//	ctrlUSBVersionTitle.SetWindowText(_T("USB Ver"));



//	ctrlToolOption1.SubclassDlgItem(IDC_TOOL_OPTION1, this);
//	ctrlToolOption2.SubclassDlgItem(IDC_TOOL_OPTION2, this);
//	ctrlToolOption3.SubclassDlgItem(IDC_TOOL_OPTION3, this);
//	ctrlToolOption4.SubclassDlgItem(IDC_TOOL_OPTION4, this);
	//091016
//	ctrlToolOption5.SubclassDlgItem(IDC_TOOL_OPTION5, this);

//	ctrlAreaOption1.SubclassDlgItem(IDC_AREA_OPTION1, this);

//	ctrlCPUVersion.SubclassDlgItem(IDC_CPU_VERSION, this);
//	ctrlMicomVersion.SubclassDlgItem(IDC_MICOM_VERSION, this);
//	ctrlUSBVersion.SubclassDlgItem(IDC_USB_VERSION, this);

	//m_LedsMesOn.SetIcons(IDI_LEDOFF, IDI_LEDON);
	//m_LedsMesOn.SetTextColors(0, COLOR_DARKBLUE, COLOR_LIGHTGRAY); //RGB(238, 239, 231));
	//m_LedsMesOn.SetTextColors(1, COLOR_BLUE, COLOR_LIGHTGRAY); //RGB(238, 239, 231));


	//m_cLabelSoundLeftFREQ.SubclassDlgItem(IDC_TEXT_FREQ_LEFT, this);//IDC_TEXT_FREQ_LEFT // ctrlPLC_COM_Status.SubclassDlgItem(IDC_PLC_COM_STATUS,this);
	//m_cLabelSoundLeftVolt.SubclassDlgItem(IDC_TEXT_VOLT_LEFT, this);//IDC_TEXT_VOLT_LEFT
	//m_cLabelSoundRightFREQ.SubclassDlgItem(IDC_TEXT_FREQ_RIGHT, this);//IDC_TEXT_FREQ_RIGHT
	//m_cLabelSoundRightVolt.SubclassDlgItem(IDC_TEXT_VOLT_RIGHT, this);//IDC_TEXT_VOLT_RIGHT

	//m_cLabelSoundLeftFREQ.SetWindowText(_T("0 Hz"));
	//m_cLabelSoundLeftFREQ.SetBkColor(RGB(0, 0, 0));
	//m_cLabelSoundLeftFREQ.SetTextColor(RGB(0, 255, 0));

	//m_cLabelSoundLeftVolt.SetWindowText(_T("0 mV"));
	//m_cLabelSoundLeftVolt.SetBkColor(RGB(0, 0, 0));
	//m_cLabelSoundLeftVolt.SetTextColor(RGB(0, 255, 0));

	//m_cLabelSoundRightFREQ.SetWindowText(_T("0 Hz"));
	//m_cLabelSoundRightFREQ.SetBkColor(RGB(0, 0, 0));
	//m_cLabelSoundRightFREQ.SetTextColor(RGB(0, 255, 0));

	//m_cLabelSoundRightVolt.SetWindowText(_T("0 mV"));
	//m_cLabelSoundRightVolt.SetBkColor(RGB(0, 0, 0));
	//m_cLabelSoundRightVolt.SetTextColor(RGB(0, 255, 0));


}


#define _MANUAL_SCOPE_ADDMODE
// CAcqVoltageSamples_IntClkDlg message handlers

BOOL CAcqVoltageSamples_IntClkDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    


	CString  BaseStr;
    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog.
    SetIcon(m_hIcon, TRUE);     // Set big icon
    SetIcon(m_hIcon, FALSE);    // Set small icon
	
#ifdef _DFT_SYSTEM1

	g_nRunningProcessNo = 1;
#else
	g_nRunningProcessNo = 2;
#endif
	m_szCurrentStatus.Format("DM NDFT %d", g_nRunningProcessNo);
	m_szCurrentStatus += " [V240606.001]";

	CAcqVoltageSamples_IntClkDlg* pMainFrame = (CAcqVoltageSamples_IntClkDlg*)AfxGetMainWnd();
	pMainFrame->SetWindowTextA(m_szCurrentStatus);

	CString sTmp = _T("");
	CString sMsg = _T("");

	CurrentSet = new CEnvironmentData;

	TCHAR szExeName[_MAX_PATH] = _T("");
	GetModuleFileName(NULL, szExeName, _MAX_PATH);
	m_szExePath = szExeName;
	m_szExePath = "D:\\DM_HDFT";// m_szExePath.Left(m_szExePath.ReverseFind('\\'));
	
	CString szLogFile = _T("");

	InitSubClassItem();

	sTmp.Format(_T("%s\\TestResult"), m_szExePath);
	if (!FileExists(sTmp))   CreateFullPath(sTmp);

#if _DEBUG
	LoadRegistrySetting(CurrentSet);
#else
	LoadRegistrySetting(CurrentSet);
#endif

	//=====================
	// Open Model.ini File 
	//=====================
	if (CurrentSet->sModelIni.IsEmpty())
	{
		//+change kwmoon 080904
	//	CreateModelIniFile(m_szExePath);
		//CurrentSet->sModelIni = m_szExePath + "\\ModelInfo.Ini";
		CurrentSet->sModelIni = m_szExePath + "\\Ref_20\\BAR\\TEST\\TEST.ini";//'\Ref_20\BAR\SN6xTEST\SN6xTEST.ini
	}

	//+add kwmoon 080821 : Add FileExists Check
	if (FileExists(CurrentSet->sModelIni))
	{
		OpenModelIniFile(CurrentSet->sModelIni);
		//+add PSH 081016
		SetGrabInfo(&g_GrabImage);
	}
	else
	{
		SaveModelIniFile(CurrentSet->sModelIni);
		sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sModelIni);
		AfxMessageBox(sMsg);
	}

	//CurrentSet->sModelSuffixName;
	if (CurrentSet->sModelSuffixName.Find(CurrentSet->sModelName)== -1)
	{
		CurrentSet->sModelSuffixName = CurrentSet->sModelName;
		CurrentSet->sModelSuffixName += ".";
		CurrentSet->sModelSuffixName += CurrentSet->sModelSuffix;
	}
	m_cLbModel.put_Caption((LPCSTR)CurrentSet->sModelName);
	//	CurrentSet->sModelSuffixName.Format(_T("%s\\Data\\%s\\%s\\%s"), pView->m_szExePath, sDate, CurrentSet->sChassisName, CurrentSet->sModelName);
	//}
	
	//==========================
	// Open Test Parameter File 
	//==========================
	if (CurrentSet->sTestParamIni.IsEmpty())
	{
		CurrentSet->sTestParamIni = m_szExePath + "\\TestParam.Ini";
	}

	//+add kwmoon 080821 : Add FileExists Check
	if (FileExists(CurrentSet->sTestParamIni))
	{
		OpenTestParamIniFile(CurrentSet->sTestParamIni);
	}
	else
	{
		sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sTestParamIni);
		AfxMessageBox(sMsg);
	}

	//===================
	// Open Pattern File 
	//===================
	if (CurrentSet->sPatternTitle.IsEmpty())
	{
		CurrentSet->sPatternTitle = m_szExePath + "\\Pattern.pat";
	}

	//+add kwmoon 080821 : Add FileExists Check
	if (FileExists(CurrentSet->sPatternTitle))
	{
		OpenPatternFile(CurrentSet->sPatternTitle);
	}
	else
	{
		sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sPatternTitle);
		AfxMessageBox(sMsg);
	}

	//===================
	// Open Remocon File 
	//===================
	if ((CurrentSet->sRemoconTitle.IsEmpty())||(CurrentSet->sRemoconTitle.GetLength() < 10))
	{
		CurrentSet->sRemoconTitle = m_szExePath + "\\Remote\\DM_DFT_HT_REMOTE.rmt";
	}
	

	//}
	//+add kwmoon 080821 : Add FileExists Check
	if (FileExists(CurrentSet->sRemoconTitle))
	{
		OpenRemoteFile(CurrentSet->sRemoconTitle);
	}
	else
	{
		sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sRemoconTitle);
		AfxMessageBox(sMsg);
	}

	//====================
	// Open Template File 
	//====================
	if (!CurrentSet->sFullSeqPath.IsEmpty())
	{
		if (FileExists(CurrentSet->sFullSeqPath))
		{
			OpenFullSeq(CurrentSet->sFullSeqPath);
		}
	}

	if (CurrentSet->nRunType < CONT || CurrentSet->nRunType > AUTO)
	{
		CurrentSet->nRunType = CONT;
	}

	if (CurrentSet->nPrintType < ALL || CurrentSet->nPrintType >NONE)
	{
		CurrentSet->nPrintType = ERRORVIEW;
	}

	//+add kwmoon 081024
	//======================
	// Open Model List File 
	//======================
	if (CurrentSet->sModelListPath.IsEmpty())
	{
		//		CurrentSet->sModelListPath = m_szExePath + "\\ModelList.ini";
		CurrentSet->sModelListPath = m_szExePath + "\\ModelList.xls";
	}
	else {
		sTmp = CurrentSet->sModelListPath.Right(3);
		sTmp.MakeLower();
		if (sTmp == "ini")
		{
			CurrentSet->sModelListPath = m_szExePath + "\\ModelList.xls";
		}
	}
#if 1
	if (FileExists(CurrentSet->sModelListPath))
	{
		int nNoModel = 0;
		OpenModelListFile(CurrentSet->sModelListPath, nNoModel, g_Divisions);
	}
	else
	{
		sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sModelListPath);
		AfxMessageBox(sMsg);
	}
#endif

	// 090909
//====================
// Open Sequence File 
//====================
	if (CurrentSet->sSeqPath.IsEmpty())
	{
		CurrentSet->sSeqPath = "D:\\DM_HDFT\\SEQ_18\\SN6x_Test_Install.seq";//'\SEQ_18\SN6x_Test_Install.seq
	}
	//else
	{
		//+add kwmoon 080821 : Add FileExists Check
		if (FileExists(CurrentSet->sSeqPath))
		{
			CurrentSet->bCompiled = Prescan(CurrentSet->sSeqPath);
		}
		else
		{
			sMsg.Format("Failed to load file.\n[%s]", CurrentSet->sSeqPath);
			AfxMessageBox(sMsg);
		}
	}
	CurrentSet->nDisplayType = DETAILEDGRID;
	InitMainGrid(CurrentSet->nDisplayType);
	InitVersionGrid();

	InsertStepData2Grid(CurrentSet->nDisplayType);
	


//	UpdateInfo(MODEL, CurrentSet->sModelName);
	UpdateInfo(MODEL, CurrentSet->sModelName);
	UpdateInfo(CHASSIS, CurrentSet->sChassisName);
	UpdateInfo(REF, CurrentSet->sRefFolder);
	UpdateInfo(SEQ, CurrentSet->sSeqPath);



	OpenComport();
	OpenComportPCB();
	//OpenComportLED();
	OpenComportSCAN();


	CString str;
	if (m_ComPort.mPort_Opened == FALSE)
	{
		str.Format(_T("MAIN COM Port %d Open FAIL !!"), CurrentSet->sAvSwitchBoxComPort);

		ComLog_AddString(str);// MessageBox(str);
	}
	//if (m_ComPortPCB.mPort_Opened == FALSE)
	//{
	//	str.Format(_T("SET USB COM Port %d Open FAIL !!"), CurrentSet->sTVComPort);
	//	ComLog_AddString(str);//MessageBox(str);
	//}

	//=================
	// Init TVCommPort 
	//=================
	if (CurrentSet->bUseTVCommPort)
	{
		sMsg = _T("[TVCommPort] Port Open Check = ");

		if (TVCommCtrl.m_bPortOpen == FALSE)
		{
			if (TVCommCtrl.Create(CurrentSet->sTVComPort, CurrentSet->wTVBaudRate)) sMsg += "PASS";
			else sMsg += "FAIL";
		}
		else sMsg += "PASS";

		//m_pInitDlg->AddString2List(sMsg);
	}

//	GetApplicationVersion();

	//CString lfname = _T("MultiAudioTester.exe");
	//if( GetProcessList(lfname, 1024) > 1)
	//{
	//	MessageBox("MultiAudioTester.exe Program Running Detected!!");
	//	OnCancel();
	//	
	//} 
//		CTime lCurTime;
//		lCurTime = CTime::GetcurrentTime()
////	int lYear = lCurTime.getcu
#ifdef __START_DEBUG_MODE_
	MessageBox("1");
#endif

	m_WaitPCB_Ack_Limit = 30;
	video_Wait_Count = 1000;


	int lMakeflag = 0;

	//BaseStr = _T(PATH_BASE_DIR);
	//
	//str = _T("D:\\SM Digital");
	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;
	//}	
	//
	//if(_mkdir(BaseStr.GetBuffer())==0)
	//{
	//	lMakeflag = 1;
	//}

	////str = _T(PATH_BASE_Back_DIR);
	//str = BaseStr + _T("\\Log");
	//
	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\log]");
	//}		
	//
	//str = BaseStr + _T("\\Remote");

	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	//}		
	//
	//str = BaseStr + _T("\\Model");

	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	//}	
	//str = BaseStr + _T("\\Image");

	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	//}	

	//str = BaseStr + _T("\\Sound");

	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	//}	




	//str = PASSWORD_PATH_BASE_DIR;
	//if(_mkdir(str.GetBuffer())==0)
	//{
	//	lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	//}	


	if (g_nRunningProcessNo == 1)
	{

		this->SetWindowPos(NULL, 0, 0, 970, 1040, SWP_ASYNCWINDOWPOS);
	}
	else
	{
		this->SetWindowPos(NULL, 960, 0, 970, 1040, SWP_ASYNCWINDOWPOS);
	}


	m_cSetupButton.LoadBitmaps(IDB_BITMAP_MODEL_ON, IDB_BITMAP_MODEL_OFF);
	//GetDlgItem(IDC_SETUP_BUTTON)->SetWindowPos(NULL, 70, 5, 60, 60, SWP_ASYNCWINDOWPOS);
	//GetDlgItem(IDC_SETUP_BUTTON)->SetWindowPos(NULL, 70, 5, 60, 60, SWP_ASYNCWINDOWPOS);

	m_cNewModelButton.LoadBitmaps(IDB_BITMAP_NEW_ON, IDB_BITMAP_NEW_OFF);

	m_cBtnView.LoadBitmaps(IDB_BITMAP_EDIT_ON, IDB_BITMAP_EDIT_PRESS);


	m_cBtnSyntax.LoadBitmaps(IDB_BITMAP_SYNTAX_ON, IDB_BITMAP_SYNTAX_PRESS);
//	GetDlgItem(IDC_SYNTAX_BUTTON)->SetWindowPos(NULL,145, 05,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
//	GetDlgItem(IDC_START_BUTTON)->SetWindowPos(NULL,245, 05,60,60,SWP_ASYNCWINDOWPOS);

	//m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
	m_cStopButton.LoadBitmaps(IDB_BITMAP_STOP_ON, IDB_BITMAP_STOP_OFF);
//	GetDlgItem(IDC_STOP_BUTTON)->SetWindowPos(NULL,320, 05,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnOption.LoadBitmaps(IDB_BITMAP_OPTION_ON, IDB_BITMAP_OPTION_PRESS);
//	GetDlgItem(IDC_OPT_BUTTON)->SetWindowPos(NULL,420, 05,60,60,SWP_ASYNCWINDOWPOS);

	m_cTestButton.LoadBitmaps(IDB_BITMAP_TEST_ON, IDB_BITMAP_TEST_OFF);

	m_cRefButton.LoadBitmaps(IDB_BITMAP_REF_ON, IDB_BITMAP_REF_OFF);

	m_cExitButton.LoadBitmaps(IDB_BITMAP_EXIT_ON, IDB_BITMAP_EXIT_OFF);
//	GetDlgItem(IDOK)->SetWindowPos(NULL,595, 05,60,60,SWP_ASYNCWINDOWPOS);

//	CString str;

	float lfval = 0.0;
	str.Format(_T("%4.1f (s)    "), lfval);	
	m_stcTime.SetWindowText(str);//
	m_CheckTimeLabel.put_Caption(str);

	lfval = 0.0;
	str.Format(_T("%4.1f (s)    "), lfval);	
	m_stcCycleTime.SetWindowText(str);//
	m_CycleTimeLabel.put_Caption(str);

	CFileControl lFile;
	lFile.ReadCountData();

	str.Format(_T("%d"), g_nOKCnt);	
	m_OKCntLabel.put_Caption(str);

	str.Format(_T("%d"), g_nNGCnt);	
	m_NGCntLabel.put_Caption(str);


	if(lFile.ReadCableCountData() != 0)
	{
		lFile.SaveCableCountData();
	}
	
	int lcountError = 0;
	str = "";
	if(gCableManager.nUSB_CableCount >= gCableManager.nUSB_CableCountMax)
	{
		str = _T("Change USB Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}

	if(gCableManager.nPort_CableCount >= gCableManager.nPort_CableCountMax)
	{
		str += _T("Change Portable Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}


	if(gCableManager.nCM4CheckerCount >= gCableManager.nCM4CheckerCountMax)
	{
		str += _T("Change CM4 Checker Pin \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}	
	if(gCableManager.nCM5CheckerCount >= gCableManager.nCM5CheckerCountMax)
	{
		str += _T("Change CM5 Checker Pin \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}
	if(gCableManager.nMIC_CableCount >= gCableManager.nMIC_CableCountMax)
	{
		str += _T("Change MIC Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}		
		
	if(lcountError > 0)
	{
	}
	else
	{
		m_cLabelCableMessage.put_BackColor(0x0008FF00);
		str += _T("\r\n\r\nCheck Cable OK\r\n");
	}
	m_cLabelCableMessage.put_Caption(str);


#ifdef __START_DEBUG_MODE_
	MessageBox("2");
#endif
/////////////////////////////////////////////////////
//
//#ifdef __G_MES_SET_MODE__
//	if(lFile.Read_ConfigSeqData())
//	{
//		lFile.SaveConfigSeqData();
//	}
//#else
//
//	if(lFile.Read_ConfigData())
//	{
//		lFile.SaveConfigData();
//	}
//
//#endif

	//if(lFile.Read_ConfigPassword())
	//{
	//	lFile.Save_ConfigPassword();
	//}
	//CString m_NgWaveFile  = _T(PATH_BASE_DIR);
	//m_NgWaveFile  += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav

	//sndPlaySound( m_NgWaveFile , SND_ASYNC);
	//Beep(1200, 300);

	//Beep(400, 500);
	//Beep(800, 1000);
	//Beep(1200, 1000);


	

#ifdef __START_DEBUG_MODE_
	MessageBox("3");
#endif


	//lFile.Read_IniModel();//gTestSeqData.strModelName
	//lFile.OpenModel(gTestSeqData.strModelName);
	//LoadTestData(gTestSeqData.strSeqFileName);


	//if(m_ComPortLED.mPort_Opened == FALSE)
	//{
	//	str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);		
	//	ComLog_AddString(str);//MessageBox(str);
	//}
	
	//if(m_ComPortScanner.mPort_Opened == FALSE)
	//{	
	//	if(g_CheckUseUSB_Scanner == 0)
	//	{
	//	
	//	
	//		str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);		
	//		ComLog_AddString(str);//MessageBox(str);
	//	}
	//}



	//SetListControl();
	DisplayTestData();
		
	//CheckDigitalPort();

	GetRmtCodeList(CurrentSet->sRemoconTitle);

	str = gTestSeqData.strModelName;
	//m_cLbModel.put_Caption((LPCSTR)str);

	m_DO_Writedata = 0;

	m_DIportOpen = 1;
	m_DOportOpen = 1;

	m_NewSystemCheck = 0;
	m_RecvCnt = 0;
	m_MainPAGE_COM_PROCESS = 0;
	m_ComAck = 0;
	m_ResendCnt = 0;
	m_ComWaitCnt = 0;
//	m_DigitalPort = DIG_OPTICAL_SELECT;
	m_SelectAudio = _AUDIO_SELECT_NON;
	m_PrecodeWait = 0;

	#ifdef __START_DEBUG_MODE_
	MessageBox("4");
#endif


#ifdef __G_MES_SET_MODE__

	//Send Are You There
	

	//CreateEthernetSocket();

	if(CurrentSet->bGMES_Connection)
	{

		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		m_EthernetWaitCnt = 0;
	}


#else
#endif
//	MessageBox("5");

	for(int i = 0; i < 8; i++)
	{
		m_graph[i].PlotTemplate.LineWidth = 1;
		m_graph[i].Axes.Item("YAxis-1").Maximum = 1.2;
		m_graph[i].Axes.Item("YAxis-1").Minimum = -1.2;
	}

	#ifdef __START_DEBUG_MODE_
	MessageBox("5");
#endif

	SetChannelData(0);
	InitChannel();
	if(m_InitAiChannel == 0)
	{
		//MessageBox("Audio Capture Card INIT FAIL!!");
		str.Format("Audio Capture Card INIT FAIL!!");
		ComLog_AddString(str);//
		g_NIAuioBoardFail = 1;//AUDIO Board Fail
	}
#ifdef __START_DEBUG_MODE_
	MessageBox("6");
#endif
	CheckTimeOn = 0;
	CycleTimeOn = 0;
	
	CString lStrName[18] = {
		_T("  HDMI_R"),		_T("  HDMI_L"),
		_T("  OPTICAL_R"),	_T("  OPTICAL_L"),
		_T("  FRONT R"),	_T("  FRONT L"),
		_T("  REAR R"),		_T("  REAR L"),
		_T("  CENTER"),		_T("  WOOFER"),
		_T("  SPEAKER_4R"),	_T("  SPEAKER_4L"),
		_T("  AUX_R"),		_T("  AUX_L"),
		_T("  PORTABLE_R"), _T("  PORTABLE_L"), 
		_T("  COAX_R"),		_T("  COAX_L")};

	
	font = new CFont;
////	font->CreateFontA( 16,                          // nHeight
//	font->CreateFontA( 25,                          // nHeight
//					0,                          // nWidth
//					0,                          // nEscapement
//					0,                          // nOrientation
//					400,                           // nWeight
//					0,                          // bItalic
//					0,                          // bUnderline 
//					0,                          // cStrikeOut 
//					0,                          // nCharSet
//					0,           // nOutPrecision 
//					0,                          // nClipPrecision 
//					PROOF_QUALITY,              // nQuality
//					0,  // nPitchAndFamily 
//					_T("Arial"));                     // lpszFacename


	font->CreateFontA( 20,                          // nHeight
					   0,                          // nWidth
					   0,                          // nEscapement
					   0,                          // nOrientation
					   600,                           // nWeight
					   0,                          // bItalic
					   0,                          // bUnderline 
					   0,                          // cStrikeOut 
					   0,                          // nCharSet
					   0,           // nOutPrecision 
					   0,                          // nClipPrecision 
					 PROOF_QUALITY,              // nQuality
					 0,  // nPitchAndFamily 
					 _T("Arial"));                     // lpszFacename
	//font->CreatePointFont(40,_T("Arial"));   
	

#ifdef __START_DEBUG_MODE_
	MessageBox("7");
#endif

	for(int i = 0 ;i < 8 ;i++)
	{
		for(int j =0; j < 18; j++)
		{
			m_cComboName[i].AddString(lStrName[j]); 
		}
		m_cComboName[i].SetCurSel(g_ManualId[i]);
		m_cComboName[i].SetFont(font);
	}
	delete font;
/*
#ifdef __OK_CHECK_FAST_MODE__
	m_NameLabel[0].put_Caption(_T(" CHECK 1 "));
	m_NameLabel[1].put_Caption(_T(" CHECK 1 "));
#else
	m_NameLabel[0].put_Caption(_T(" CHECK 2 "));
	m_NameLabel[1].put_Caption(_T(" CHECK 2 "));


#endif
*/

	//if (api.Init("D:\\SM Digital\\AudioTester_1100AP\\tessdata", "smfont")) 
	//{
	//	AfxMessageBox("tessract Init 실패");
 //      // exit(1);
 //   }
#ifdef __START_DEBUG_MODE_
	MessageBox("8");
#endif

//	CPing	m_ping;
	//MessageBox("6");
	
	IcmpEcho ping;
	unsigned long ulIP;
	DWORD delay;
	CString strtmp;
	CString strtmpIPAddress;
	delay = 1000;	

	if(CurrentSet->bGMES_Connection)
	{
		ulIP = ping.ResolveIP( g_nRemoteIPAddress.GetBuffer() );
		delay = ping.PingHostOK( ulIP, PING_TIMEOUT);


		if(delay > 100)
		{
			m_cLb_ComMainGmes.put_BackColor(0x000000FF);
			//MessageBox("GMES NOT Connected!");
			str = "GMES NOT Connected!";
			ComLog_AddString(str);//
			CurrentSet->bGMES_Connection = 0;
			m_EthernetMode =  ETHERNET_MODE_IDLE;
		}


	}



#ifdef __START_DEBUG_MODE_
	MessageBox("11");
#endif
//	bCapture = false;

	//if(m_Camera_Capture_Flag ==1)
	//{
	//	gbShutdown = false;
	//	pThreadCap = AfxBeginThread(threadCapture, this);


	//			
	//	m_pDC = m_pic.GetDC();
	//	m_pic.GetClientRect(&rect);
	//
	//	memDC.CreateCompatibleDC(m_pDC);
	//	Bitmap.CreateCompatibleBitmap(m_pDC,rect.Width(),rect.Height());
	//
	//	pOldBitmap = memDC.SelectObject(&Bitmap);
	//}



	SetTimer(1,10,NULL);
	SetTimer(2,1000,NULL);

	OnBnClickedButtonFreqSet();

	mpDlgResult = new CDlgResult;	
	mpDlgResult->Create(CDlgResult::IDD, this);
	mpDlgResult->ShowWindow(SW_HIDE);//SetWindowPos(this,rectP.left+ 15,rectP.top+160,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
	mpDlgResult->pDlg = this;

	mpDlgBarcode = new CDlgBarcode;	
	mpDlgBarcode->Create(CDlgBarcode::IDD, this);
	mpDlgBarcode->ShowWindow(SW_HIDE);//SetWindowPos(this,rectP.left+ 15,rectP.top+160,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
	//mpDlgResult->pMainWnd = this;

	mpDlgSimpleInform = new CDlgSimpleInform;	
	mpDlgSimpleInform->Create(CDlgSimpleInform::IDD, this);
	mpDlgSimpleInform->ShowWindow(SW_HIDE);//SetWindowPos(this,rectP.left+ 15,rectP.top+160,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);

	m_pUserMsgDlg = new CUserMsgDlg;	
	m_pUserMsgDlg->Create(CUserMsgDlg::IDD, this);
	m_pUserMsgDlg->ShowWindow(SW_HIDE);//SetWindowPos(this,rectP.left+ 15,rectP.top+160,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
	//#include "DlgSimpleInform.h"
#ifdef __START_DEBUG_MODE_
	MessageBox("12");
#endif


	
#ifndef NO_CAPTURE_MODE__
	// Create and initialise preview and DeckLink device discovery objects 
	m_previewWindow = new PreviewWindow();
	if (m_previewWindow->init(&m_previewBox) == false)
	{
		//MessageBox(_T("This application was unable to initialise the preview window1"), _T("Error"));
		str = "DeckLink device error";// _T("This application was unable to initialise the preview window1");
		ComLog_AddString(str);//
		goto bail;
	}



	m_deckLinkDiscovery = new DeckLinkDeviceDiscovery(this);
	if (!m_deckLinkDiscovery->Enable())
	{
		//MessageBox(_T("Please install the Blackmagic Desktop Video drivers to use the features of this application."), _T("This application requires the Desktop Video drivers installed."));
		str = "DeckLink driver error";
		ComLog_AddString(str);//
	}
	m_cLb_Camera.put_BackColor(0x00FFFF);
	//m_cLb_Camera.put_Caption("WAIT");
bail:
#endif
	
	ChangeModelCheckOpen(CurrentSet->sModelName);
	UpdateVersionInfo();// InitVersionGrid();InitVersionGrid();
	//NG_Display("rorouerqrpotq\r\nuuhrthert\r\njhhguoyt");
	// Return TRUE unless you set the focus to a control.
	SetUSBSel(USB_SEL_UART_MODE_, USB_SEL_UART_MODE_);
	WriteSM_Out(99);
    return TRUE;
}

void CAcqVoltageSamples_IntClkDlg::ComLogClear()
{
	m_strLogArray.RemoveAll();
	HWND hEdit = m_ctrlEditComLog.m_hWnd;

	BOOL bReadOnly = ::GetWindowLong(hEdit, GWL_STYLE) & ES_READONLY;
	if (bReadOnly)
		::SendMessage(hEdit, EM_SETREADONLY, FALSE, 0);
	::SendMessage(hEdit, EM_SETSEL, 0, -1);
	::SendMessage(hEdit, WM_CLEAR, 0, 0);
	if (bReadOnly)
		::SendMessage(hEdit, EM_SETREADONLY, TRUE, 0);

}


void CAcqVoltageSamples_IntClkDlg::ComLog_AddString(CString szString)
{
	CString strTmp =  "\r\n";
	strTmp += szString;
	AppendToLogAndScroll(strTmp);
	AddProcessLog(strTmp);
}

int CAcqVoltageSamples_IntClkDlg::GetNumVisibleLines(CRichEditCtrl* pCtrl)
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	pCtrl->GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = pCtrl->CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = pCtrl->CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
	{
		nLastChar = pCtrl->GetTextLength();
	}

	// Convert to lines
	nFirstLine = pCtrl->LineFromChar(nFirstChar);
	nLastLine = pCtrl->LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}


int CAcqVoltageSamples_IntClkDlg::AppendToLogAndScroll(CString str, COLORREF color)
{
	long nVisible = 0;
	long nInsertionPoint = 0;
	CHARFORMAT cf;

//	if (str.GetLength() > 45)
//		str.Insert(36,"\r\n  ");//  //.SetAt(16, "\n');

	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0; // To disable CFE_AUTOCOLOR

	cf.crTextColor = color;

	// Set insertion point to end of text
	nInsertionPoint = m_ctrlEditComLog.GetWindowTextLength();
	m_ctrlEditComLog.SetSel(nInsertionPoint, -1);

	// Set the character format
	m_ctrlEditComLog.SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing 
	// selected, this will simply insert
	// the string at the current caret position.
	m_strLogArray.Add(str);
	m_ctrlEditComLog.ReplaceSel(str);


	// Get number of currently visible lines or maximum number of visible lines
	// (We must call GetNumVisibleLines() before the first call to LineScroll()!)
	nVisible = GetNumVisibleLines(&m_ctrlEditComLog);

	// Now this is the fix of CRichEditCtrl's abnormal behaviour when used
	// in an application not based on dialogs. Checking the focus prevents
	// us from scrolling when the CRichEditCtrl does so automatically,
	// even though ES_AUTOxSCROLL style is NOT set.
	if (&m_ctrlEditComLog != m_ctrlEditComLog.GetFocus())
	{
		m_ctrlEditComLog.LineScroll(10);
		//m_ctrlEditComLog.LineScroll(1 - nVisible);
	}

	return 0;
}

void CAcqVoltageSamples_IntClkDlg::LogDataSave(CString sLogFilePath)
{
	CString szLogFile = _T("");

	szLogFile = sLogFilePath;
	szLogFile.Replace(".dat", ".log");

	HANDLE hText = NULL;
	HANDLE hClipData;                            /* handles to clip data  */
	LPSTR  lpClipData;                           /* pointers to clip data */
	HWND hEdit = m_ctrlEditComLog.m_hWnd;

	CStdioFile File;
	CFileException ex;

	CString str;
	if (!File.Open(szLogFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText, &ex)) {
		EmptyClipboard();
		CloseClipboard();
		ComLog_AddString(_T("Unable to save Log list : File Open Error"));
		return;
	}

	TRY{
		for (int i = 0; i < m_strLogArray.GetCount(); i++)
		{
			str = m_strLogArray.GetAt(i);
					File.WriteString(str);



		}
		File.Close();
	}
		CATCH(CFileException, e) {
		ComLog_AddString(_T("Unable to save Log list : File Write Error"));
		e->Delete();

	}
	END_CATCH



		//m_ctrlEditComLog.
		//m_ctrlEditComLog.SetSel(0,-1);// SetSel(0, -1, TRUE);
		//m_ctrlEditComLog.Copy();
#if 0
	// Copy all of the text to the clipboard.
		m_ctrlEditComLog.SetSel(0, -1);
	m_ctrlEditComLog.Copy();


	if (OpenClipboard()) {
		if (!(hClipData = GetClipboardData(CF_TEXT))) {
			CloseClipboard();
			return;
		}

		lpClipData = (char*)GlobalLock(hClipData);

		if (!File.Open(szLogFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText, &ex)) {
			EmptyClipboard();
			CloseClipboard();
			AddStringToStatus(_T("Unable to save Log list : File Open Error"));
			return;
		}

		TRY{
			File.WriteString(lpClipData);


			File.Close();
		}

			CATCH(CFileException, e) {
			AddStringToStatus(_T("Unable to save Log list : File Write Error"));
			e->Delete();
		}
		END_CATCH

			EmptyClipboard();
		CloseClipboard();
	}
#endif
}




BOOL CAcqVoltageSamples_IntClkDlg::CreateEthernetSocket() 
{
	BOOL lresult = 0;
	if (m_pUDPSocket) 
	{
		AfxMessageBox("Socket already created, \r\n Close and Reopen!");
		//lresult = m_pUDPSocket->Connect(g_nRemoteIPAddress, g_nRemotePortNumber);
		//if(lresult == 0)
		//{
		//	if (GetLastError() != WSAEWOULDBLOCK) 
		//	{
				m_pUDPSocket->Close();
				delete m_pUDPSocket;
				m_pUDPSocket = NULL;
				AfxMessageBox (m_szError);
		//		return FALSE;
		//	}
		//}
	}
//	else
	{
		if (g_nLocalPortNumber == 0)
		{
			AfxMessageBox ("Please enter a local port number");
			return FALSE;
		}
		if ((m_pUDPSocket = new CUdpAsySk(this)) == NULL) 
		{
			AfxMessageBox ("Failed to allocate UDP socket! Close and restart app.");
			return FALSE;
		}
		m_pUDPSocket->m_sendBuffer = "";   //for async send
		m_pUDPSocket->m_nBytesSent = 0;
		m_pUDPSocket->m_nBytesBufferSize = 0;


		g_nLocalPortNumber++;
		if(g_nLocalPortNumber > 7500)
		{
			g_nLocalPortNumber = 7000;
		}
	//	if (!m_pUDPSocket->Create(g_nLocalPortNumber, SOCK_DGRAM))
		if (!m_pUDPSocket->Create(g_nLocalPortNumber, SOCK_STREAM))
		{
			wsprintf(m_szError, "Failed to create TCP socket: %d! Close and restart app.", m_pUDPSocket->GetLastError());
			delete m_pUDPSocket;
			m_pUDPSocket = NULL;
			AfxMessageBox (m_szError);
		
			return FALSE;
		}
		lresult = m_pUDPSocket->Connect(g_nRemoteIPAddress, g_nRemotePortNumber);
		if(lresult == 0)
		{
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				m_pUDPSocket->Close();
				delete m_pUDPSocket;
				m_pUDPSocket = NULL;
				AfxMessageBox (m_szError);
				return FALSE;
			}
		}
	}

		
	

	return TRUE;
}


BOOL CAcqVoltageSamples_IntClkDlg::ConnectSocket() 
{
	BOOL lresult = 0;
	if (m_pUDPSocket) 
	{
	
		lresult = m_pUDPSocket->Connect(g_nRemoteIPAddress, g_nRemotePortNumber);
		if(lresult == 0)
		{
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				m_pUDPSocket->Close();
				delete m_pUDPSocket;
				m_pUDPSocket = NULL;
				AfxMessageBox (m_szError);
				return FALSE;
			}
		}
	}
	else
	{
		if (g_nLocalPortNumber == 0)
		{
			AfxMessageBox ("Please enter a local port number");
			return FALSE;
		}
		if ((m_pUDPSocket = new CUdpAsySk(this)) == NULL) 
		{
			AfxMessageBox ("Failed to allocate UDP socket! Close and restart app.");
			return FALSE;
		}
		m_pUDPSocket->m_sendBuffer = "";   //for async send
		m_pUDPSocket->m_nBytesSent = 0;
		m_pUDPSocket->m_nBytesBufferSize = 0;

		g_nLocalPortNumber++;
		if(g_nLocalPortNumber > 7500)
		{
			g_nLocalPortNumber = 7000;
		}
	//	if (!m_pUDPSocket->Create(g_nLocalPortNumber, SOCK_DGRAM))
		if (!m_pUDPSocket->Create(g_nLocalPortNumber, SOCK_STREAM))
		{
			wsprintf(m_szError, "Failed to create TCP socket: %d! Close and restart app.", m_pUDPSocket->GetLastError());
			delete m_pUDPSocket;
			m_pUDPSocket = NULL;
			AfxMessageBox (m_szError);
		
			return FALSE;
		}
		lresult = m_pUDPSocket->Connect(g_nRemoteIPAddress, g_nRemotePortNumber);
		if(lresult == 0)
		{
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				m_pUDPSocket->Close();
				delete m_pUDPSocket;
				m_pUDPSocket = NULL;
				AfxMessageBox (m_szError);
				return FALSE;
			}
		}
	}

		
	

	return TRUE;
}

//UINT g_nRemotePortNumber = 8000;
//UINT g_nLocalPortNumber = 7000;
//CString g_nRemoteIPAddress = _T("192.168.1.20");

void CAcqVoltageSamples_IntClkDlg::CloseEthernetScocket() 
{

	if (m_pUDPSocket)
	{
		m_pUDPSocket->Close();
		delete m_pUDPSocket;

		m_pUDPSocket  = NULL;

	}	
	m_EthernetMode =  ETHERNET_MODE_IDLE;	
	CurrentSet->bGMES_Connection = 0;
	m_cLb_ComMainGmes.put_BackColor(0x000001FF);
}

BOOL CAcqVoltageSamples_IntClkDlg::OnCmdGmesSend() 
{
	
	if (!m_pUDPSocket)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		AfxMessageBox("GMES Please create socket first.");
		m_EthernetMode =  ETHERNET_MODE_IDLE;
		//MessageBox("GMES Socket Create Fail!");
		CurrentSet->bGMES_Connection = 0;
		
		return FALSE;
	}
	if (m_strMesSend.GetLength() == 0) 
	{
		MessageDisplay(1, "GMES Data Strings ERROR to Send");
		//CurrentSet->bGMES_Connection = 0;
		//m_EthernetMode =  ETHERNET_MODE_IDLE;
		return FALSE;
	}

	//if (g_nRemoteIPAddress.GetLength() == 0)
	//{
	//	MessageDisplay(1, "Please Type the remote IPaddress to Send to");
	//	m_EthernetMode =  ETHERNET_MODE_IDLE;
	//	CurrentSet->bGMES_Connection = 0;
	//	return FALSE;
	//}


	if(m_pUDPSocket->m_Connected == 0)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		MessageDisplay(1, "GMES Socket Not Connected!!");
		m_EthernetMode =  ETHERNET_MODE_IDLE;
		CurrentSet->bGMES_Connection = 0;
		AfxMessageBox("GMES Socket Not Connected.");
		CloseEthernetScocket() ;
		return FALSE;	
	}

	m_pUDPSocket->m_nBytesSent = 0;
/////////////////
/*	
	TCHAR szSend[65467];
	for (int i=0; i<65467; i++)
		szSend[i] = 'c';
	szSend[65466] = 0;
	m_pUDPSocket->m_sendBuffer = CString(szSend);
	m_pUDPSocket->m_nBytesBufferSize = m_pUDPSocket->m_sendBuffer.GetLength() + 1;
*/
////////////////
	m_pUDPSocket->m_sendBuffer = m_strMesSend;
	m_pUDPSocket->m_nBytesBufferSize = m_strMesSend.GetLength() + 1;

	
	if(m_pUDPSocket->DoAsyncSendBuff() == 1)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		MessageBox("GMES Server Connect FAIL! \r\nGMES DATA Send ERROR","ERROR");
		//if(IDYES == MessageBox("GMES Server Connect FAIL! \r\nGMES DATA Send ERROR","ERROR"))
		//{
		//	CloseEthernetScocket() ;
		//	m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;			
		//}
		//else
		//{
		//	m_EthernetMode =  ETHERNET_MODE_IDLE;
		//}
		CurrentSet->bGMES_Connection = 0;
		CloseEthernetScocket() ;
		return FALSE;
	}
	//m_strMesSend = "";
	//m_EthernetMode = ETHERNET_MODE_WAIT;
	AddGmesLog(m_strMesSend);
	return TRUE;
}

void CAcqVoltageSamples_IntClkDlg::GMESAreYouThereRequest() //S1F1
{
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S1F1\" NAME=\"Are You There Request\">\r\n");
	m_strMesSend += _T("</EIF>");
	if(OnCmdGmesSend() == 0)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		MessageDisplay(1, "GMES INIT Fail!");
		CurrentSet->bGMES_Connection = 0;
	}
}



void CAcqVoltageSamples_IntClkDlg::GMESEquipmentStatusSend(int lStatus) //S1F3
{
	//EquipmentStatusSend
	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S1F3\" NAME=\"Equipment Status Send\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");

	m_strMesSend += _T("  <ITEM>\r\n");
	m_strMesSend += _T("    <EQPSTATUS>");
	if(lStatus == 1)
	{
		m_strMesSend +=  _T("R");
	}
	else
	{
		m_strMesSend +=  _T("D");
	}
	m_strMesSend += _T("</EQPSTATUS>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}

void CAcqVoltageSamples_IntClkDlg::GMESLinkLoopbackTest() //S2F4
{
//<EIFVERSION="1.8"ID="S2F25"NAME="LoopbackdiagnosticsTestRequest">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM>
//</EIF>
	//EquipmentStatusSend
	//CString str1;
	m_strMesSend = _T("<EIFVERSION=\"1.4\"ID=\"S2F25\"NAME=\"LoopbackdiagnosticsTestRequest\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("<ITEM>\r\n");
	m_strMesSend += _T("<AS>HZ_AUDIO</AS>\r\n");
	m_strMesSend += _T("</ITEM>\r\n");
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}

void CAcqVoltageSamples_IntClkDlg::GMESLinkLoopbackResponce(CString strAS_) //S2F4	void GMESLinkLoopbackResponce();
{
//<EIFVERSION="1.8"ID="S2F26"NAME="LoopbackdiagnosticsTestAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM></EIF >
	//EquipmentStatusSend
	//CString str1;
	m_strMesSend = _T("<EIFVERSION=\"1.4\"ID=\"S2F26\"NAME=\"LoopbackdiagnosticsTestAcknowledge\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("<ITEM>\r\n");
	m_strMesSend += _T("<AS>");
	m_strMesSend += strAS_;
	m_strMesSend += _T("</AS>\r\n");
	m_strMesSend += _T("</ITEM>\r\n");
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}

void CAcqVoltageSamples_IntClkDlg::GMESLinkTestResponse() //S2F4
{
//	<EIFVERSION="1.8"ID="S2F4"NAME="LinkTestResponse">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//</EIF>
	//EquipmentStatusSend
	//CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S2F4\" NAME=\"Link Test Response\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}

void CAcqVoltageSamples_IntClkDlg::GMESDateandTimeData() //S1F3
{
//<EIFVERSION="1.8"ID="S2F18"NAME="DateandTimeData">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<TIME></TIME>
//</ITEM>
//</EIF>
	//EquipmentStatusSend
	time_t ti;
	time(&ti);
	struct tm *t = localtime(&ti);		

	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S2F18\" NAME=\"Date and Time Data\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("  <ITEM>\r\n");
	m_strMesSend += _T("    <TIME>");
	str1.Format(_T("%04d%02d%02d%02d%02d%02d"), t->tm_year,  t->tm_mon,   t->tm_mday, t->tm_hour,t->tm_min, t->tm_sec);
	//“YYYYMMDDhhmmss”
	m_strMesSend += str1;
	m_strMesSend += _T("</TIME>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}

void CAcqVoltageSamples_IntClkDlg::GMESLoopbackdiagnosticsTestAcknowledge(CString lLoopBackString) //S2F26
{
//<EIF VERSION="1.8"ID="S2F26"NAME="LoopbackdiagnosticsTestAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM></EIF >

	//CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S2F26\" NAME=\"Loopback diagnostics Test Acknowledge\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("  <ITEM>\r\n");
	m_strMesSend += _T("    <AS>");
	m_strMesSend += lLoopBackString;
	m_strMesSend += _T("</AS>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>\r\n");	
	
	OnCmdGmesSend();
}


void CAcqVoltageSamples_IntClkDlg::GMESDataandTimeAcknowledge(int lAck) //S2F32
{
//<EIFVERSION="1.8"ID="S2F32"NAME="DataandTimeAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<ACK></ACK>
//</ITEM>
//</EIF>
//Notice
//<EQPID>EquipmentID
//<ACK>AcknowledgeCode
//0=Accepted
//1=NotAccepted

	//CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S2F32\" NAME=\"Data and Time Acknowledge\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	
	m_strMesSend += _T("  <ITEM>\r\n");
	m_strMesSend += _T("     <ACK>");
	if(lAck == 0)
		m_strMesSend += _T("1");
	else
		m_strMesSend += _T("0");

	m_strMesSend += _T("</ACK>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>");	
	
	OnCmdGmesSend();
}

//int			m_AlarmNumber;
//int			m_AlarmCode[100];
//CString		m_AlarmName[100];
//CString		m_AlarmMessage[100];


void CAcqVoltageSamples_IntClkDlg::GMESAlarmSetReportSend() //S5F1
{
	
//<EIFVERSION="1.8"ID="S5F1"NAME="AlarmSetReportSend">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<SUBITEMLISTCOUNT="n">
//<ALCD></ALCD>
//<ALNAME></ALNAME>
//<ALTX></ALTX>
//</SUBITEMLIST>
//</ITEM>
//</EIF>
//Notice
//<EQPID>EquipmentID
//<SUBITEMLISTCOUNT=“n”>Countof<ALCD>,<ALNAME>,<ALTX>Pair
//<ALCD>AlarmCode
//<ALNAME>AlarmName
//<ALTX>AlarmMessage
//GMES에해당Equipment의ALCD/ALNAME/ALTX가정의되어있는경우
//ALCD만전송함.

	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S5F1\" NAME=\"Alarm Set Report Send\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	


	m_strMesSend += _T("  <ITEM>\r\n");
//	m_strMesSend += _T("<SUBITEMLISTCOUNT=\"n\">");
	str1.Format(    _T("    <SUBITEMLIST COUNT=\"%d\">\r\n"), m_AlarmNumber);
	m_strMesSend += str1;

	for(int i = 0; i < m_AlarmNumber; i++)
	{
		m_strMesSend += _T("      <ALCD>");//<ALCD>AlarmCode
		str1.Format(_T("%d"), m_AlarmCode[i]);
		m_strMesSend += _T("</ALCD>\r\n");
		m_strMesSend += _T("      <ALNAME>");//<ALNAME>AlarmName
		m_strMesSend += m_AlarmName[i];
		m_strMesSend += _T("</ALNAME>\r\n");
		m_strMesSend += _T("      <ALTX>");//<ALTX>AlarmMessage
		m_strMesSend += m_AlarmMessage[i];
		m_strMesSend += _T("</ALTX>\r\n");
	}
	m_strMesSend += _T("    </SUBITEMLIST>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>");	
	
	OnCmdGmesSend();
}


void CAcqVoltageSamples_IntClkDlg::GMES_Scan_InformSend() //S6F11
{
	if(m_GMES_Skipped == 1)
	{
		return;
	}

	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S6F11\" NAME=\"Event Report Send\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");
	m_strMesSend += _T("    <CEID>");
	m_strMesSend += g_strCEID;
	m_strMesSend += _T("</CEID>\r\n");
	m_strMesSend += _T("    <RPTID>");
	m_strMesSend += g_strRPTID;
	m_strMesSend += _T("</RPTID>\r\n");
	m_strMesSend += _T("  </ELEMENT>\r\n");	


	m_strMesSend += _T("  <ITEM>\r\n");
	m_strMesSend += _T("    <SUBITEMLIST COUNT=\"1\">\r\n");
	m_strMesSend += _T("      <NAME>SETID</NAME>\r\n");
	m_strMesSend += _T("      <VALUE>");
	m_strMesSend += g_strSetID;
	m_strMesSend += _T("</VALUE>\r\n");


	m_strMesSend += _T("    </SUBITEMLIST>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>");	
	
	OnCmdGmesSend();//g_strSetID
	m_EthernetResendCnt = 0;
	m_EthernetAck = 0;
	m_EthernetMode = ETHERNET_MODE_WAIT;
}

void CAcqVoltageSamples_IntClkDlg::GMESProductDataAcknowledge() //S6F6
{
	if(m_GMES_Skipped == 1)
	{
		return;
	}
//	<EIFVERSION="1.8"ID="S6F6"NAME="ProductDataAcknowledge">
//<ELEMENT>




	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S6F6\" NAME=\"Product Data Acknowledge\">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	//<WOID></WOID>
//<ORGID></ORGID>
//<LINEID></LINEID>
	m_strMesSend += _T("    <EQPID>");//<EQPID></EQPID>
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");

	m_strMesSend += _T("    <PROCID>");
	m_strMesSend += g_strProcID;
	m_strMesSend += _T("</PROCID>\r\n");
	m_strMesSend += _T("    <SETID>");
	m_strMesSend += g_strSetID;
	m_strMesSend += _T("</SETID>\r\n");

	m_strMesSend += _T("    <MODEL>\r\n");//<MODEL>

	m_strMesSend += _T("    <ID>");
	m_strMesSend += g_strModelID;
	m_strMesSend += _T("</ID>\r\n");

	m_strMesSend += _T("    <NAME>");
	m_strMesSend += g_strMesModelName;
	m_strMesSend += _T("</NAME>\r\n");

	m_strMesSend += _T("    <SUFFIX>");
	m_strMesSend += g_strModelSuffix;
	m_strMesSend += _T("</SUFFIX>\r\n");

	m_strMesSend += _T("    </MODEL>\r\n");//</MODEL>
	m_strMesSend += _T("  </ELEMENT>\r\n");	//</ELEMENT>

	m_strMesSend += _T("  <ITEM>\r\n");//<ITEM>

	m_strMesSend += _T("    <ACK>0</ACK>\r\n");
	m_strMesSend += _T("    <REASON>");
	//m_strMesSend += g_strSetID;
	m_strMesSend += _T("</REASON>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");//</ITEM>
	m_strMesSend += _T("</EIF>");//</EIF>	
	
	OnCmdGmesSend();//g_strSetID
}

void CAcqVoltageSamples_IntClkDlg::GMES_Result_ReportSend() //S6F1
{
	if(m_GMES_Skipped == 1)
	{
		return;
	}
	if (gbManualRefMode == 1)
	{
		//m_TaskRun = TASK_FINISH_PROCESS;
		//gbManualRefMode = 0;
		return;
	}
	CString str1;
	m_strMesSend = _T("<EIF VERSION=\"1.4\" ID=\"S6F1\" NAME=\"Inspection(Processing) Data Send \">\r\n");
	m_strMesSend += _T("  <ELEMENT>\r\n");
	m_strMesSend += _T("    <TID>Null</TID>\r\n");	
	m_strMesSend += _T("    <WOID>");
	m_strMesSend += g_strWOID;
	m_strMesSend += _T("</WOID>\r\n");

	m_strMesSend += _T("    <ORGID>");
	m_strMesSend += g_strORGID;
	m_strMesSend += _T("</ORGID>\r\n");


	m_strMesSend += _T("    <LINEID>");
	m_strMesSend += g_strLineID;
	m_strMesSend += _T("</LINEID>\r\n");


	m_strMesSend += _T("    <EQPID>");
	m_strMesSend += g_strEQPID;
	m_strMesSend += _T("</EQPID>\r\n");

	m_strMesSend += _T("    <PROCID>");
	m_strMesSend += g_strProcID;
	m_strMesSend += _T("</PROCID>\r\n");


	m_strMesSend += _T("    <SETID>");
	m_strMesSend += g_strSetID;
	m_strMesSend += _T("</SETID>\r\n");

	
	m_strMesSend += _T("    <MODEL>\r\n");//<MODEL>

	m_strMesSend += _T("    <ID>");
	m_strMesSend += g_strModelID;
	m_strMesSend += _T("</ID>\r\n");

	m_strMesSend += _T("    <NAME>");
	m_strMesSend += g_strMesModelName;
	m_strMesSend += _T("</NAME>\r\n");

	m_strMesSend += _T("    <SUFFIX>");
	m_strMesSend += g_strModelSuffix;
	m_strMesSend += _T("</SUFFIX>\r\n");

	m_strMesSend += _T("    </MODEL>\r\n");//</MODEL>

	m_strMesSend += _T("  </ELEMENT>\r\n");	


	m_strMesSend += _T("  <ITEM>\r\n");
//	m_strMesSend += _T("<SUBITEMLISTCOUNT=\"n\">");
//	str1.Format(    _T("    <SUBITEMLIST COUNT=\"%d\">\r\n"), m_AlarmNumber);
	str1 =  _T("    <SUBITEMLIST COUNT=\"1\">\r\n");
	m_strMesSend += str1;

	m_strMesSend += _T("      <NAME>RESULT</NAME>\r\n");
	if(m_TEST_Result == 1)
	{
		m_strMesSend += _T("      <VALUE>OK</VALUE>\r\n");
	}
	else
	{
		m_strMesSend += _T("      <VALUE>NG</VALUE>\r\n");
	}

	m_strMesSend += _T("      <NAME>TIME</NAME>\r\n");
	m_strMesSend += _T("      <VALUE>");
	str1 = m_CheckTimeLabel.get_Caption();
	str1 = str1.Left(str1.Find(" (s)"));	
	m_strMesSend += str1;
	m_strMesSend += _T("</VALUE>\r\n");

	
	m_strMesSend += _T("      <NAME>TOTAL_TIME</NAME>\r\n");
	m_strMesSend += _T("      <VALUE>");
	str1 = m_CycleTimeLabel.get_Caption();
	str1 = str1.Left(str1.Find(" (s)"));	
	m_strMesSend += str1;
	m_strMesSend += _T("</VALUE>\r\n");


	if(m_TEST_Result == 0)
	{
		m_strMesSend += _T("      <NAME>NG_ITEM</NAME>\r\n");
		m_strMesSend += _T("      <VALUE>");
		str1 = m_GMES_ErrorName;//m_GMES_ErrorValue;
		m_strMesSend += str1;
		m_strMesSend += _T("</VALUE>\r\n");

		m_strMesSend += _T("      <NAME>NG_VALUE</NAME>\r\n");
		m_strMesSend += _T("      <VALUE>");
		str1 = m_GMES_ErrorValue;
		m_strMesSend += str1;
		m_strMesSend += _T("</VALUE>\r\n");



	}


	m_strMesSend += _T("    </SUBITEMLIST>\r\n");
	m_strMesSend += _T("  </ITEM>\r\n");
	m_strMesSend += _T("</EIF>");	
//	<SUBITEMLIST COUNT=“2">
//<NAME>RESULT</NAME>
//<VALUE>NG</VALUE>
//<NAME>TOTAL_TIME</NAME>
//<VALUE> 37.3</VALUE>
//<NAME>NG_ITEM</NAME>
//<VALUE> AUX_FREQUENCY</VALUE>
//<NAME>NG_VALUE</NAME>
//<VALUE> 0</VALUE>
//</SUBITEMLIST>

	OnCmdGmesSend();
	m_EthernetAck = 0;

	m_EthernetMode = ETHERNET_MODE_WAIT;
	m_EthernetResendCnt = 0;
}

void CAcqVoltageSamples_IntClkDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);      // Device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
// the minimized window.
HCURSOR CAcqVoltageSamples_IntClkDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
//#define ORA_USING_TNS_NAME _T("DAVMDEV")
//#define ORA_USING_USER_ID _T("oraspc")
//#define ORA_USING_PASSWRD _T("spcora00")
/*
//dev
BYOMINN
BYOMOUT
BYOMT1
BYOMT2
BYOMT3
BYOMT4
BYOMT5
BYOMT6
BYOMT7
BYOMT8
BYOMT9
BYOMT10

//
AGING_LOW
BYOMOUT
BYOMT1
BYOMT10
BYOMT2
BYOMT3
BYOMT4
BYOMT5
BYOMT6
BYOMT7
BYOMT8
BYOMT9
SET_ON_CUR

*/
//
//void CAcqVoltageSamples_IntClkDlg::MesStart()
//{
//	CString sMsg;
//
//	CurrentSet.strMesDsn = g_strMesTns;
//	CurrentSet.strMesUserId = g_strMesUserID;
//	CurrentSet.strMesPassWord = g_strMesPassword;//g_strMesAvn
//	CurrentSet.strMesAvn = g_strMesAvn;
//	CurrentSet.strProductionLine = g_strMesLine;
//	CurrentSet.strStepName = g_strMesInspStep;
//
//	g_MesDb.m_strWipId = m_WipID;
//	m_WipID = _T("");
//
//	if(g_MesDb.m_strWipId.GetLength() < 6)
//	{
//		MessageDisplay(1, _T("BAR CODE EMPTY!! "));
//		m_bStartMES = FALSE;
//		g_MesDb.m_strWipId  = _T("");
//	}
//	else
//	{
//		/*int lresult = g_MesDb.StepCheck();
//		if(lresult == 1)
//		{
//			MessageDisplay(0, g_MesDb.m_strMessage);
//		}
//		else
//		{
//			MessageDisplay(1, g_MesDb.m_strMessage);
//			int lok = MessageBox(_T("MES CHECK FAIL!! TEST CONTINUE??"),  _T("MES FAIL"), MB_YESNO | MB_DEFBUTTON2);
//			if(IDYES != lok)
//			{
//				m_TaskRun = TASK_RUN_IDLE;
//				MessageDisplay(1, _T(" TEST STOP!!"));
//			}
//			
//		}*/
//
//		int lresult =  g_MesDb.Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		if(lresult == 1)
//		{
//			MessageDisplay(0, sMsg);
//			m_bStartMES = TRUE;
//		}
//		else
//		{
//			MessageDisplay(1, sMsg);
//			m_bStartMES = TRUE;
//		}
//		
//	}	
//	
//}
//
//
//int CAcqVoltageSamples_IntClkDlg::MesTestReport()
//{
//	//CurrentSet.strMesDsn = ORA_USING_TNS_NAME;
//	//CurrentSet.strMesUserId = ORA_USING_USER_ID;
//	//CurrentSet.strMesPassWord = ORA_USING_PASSWRD;
//	//CurrentSet.bCommDisplay = 1;
//	//CurrentSet.strStepName =_T("BYOMT1");
//	int lresult = 0;
//
//#ifdef __G_MES_SET_MODE__
//
//#else //#endif
//	if(CurrentSet->bGMES_Connection)
//	{
//		if(m_bStartMES)
//		{
//			if(m_TEST_Result == 1)
//			{
//				lresult = g_MesDb.StepComplete(TRUE);
//			}
//			else
//			{
//				lresult = g_MesDb.StepComplete(FALSE);
//			}
//		}
//	}
//
//#endif
//	//gSaveInfo.bMesSts = lresult;
//	if(lresult == 1)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//	
//
//	//m_bStartMES = TRUE;
//	//OnBnClickedStart();
//}
//


void CAcqVoltageSamples_IntClkDlg::OnBnClickedStart() 
{
	gbManualRefMode = 0;
	RunTestStart();
}


void CAcqVoltageSamples_IntClkDlg::RunTestStart()
{
	//gbManualRefMode = 0;
	CLOSE_Result_Display();

	m_GMES_CommError = 0;
	m_WipID = m_BarCode.get_Caption();
	if (gbManualScopeMode)
	{
		MessageBox("MANUAL SCOPE MODE!!");
		return;

	}

	if ((m_TaskRun != TASK_RUN_IDLE) && (m_TaskRun != TASK_WAIT_SELECT_PROCESS) && (m_TaskRun != TASK_WAIT_BARCODE_PROCESS))
	{
		return;
	}


	CFileControl lFile;

	//if (SeqFileModified(gTestSeqData.strSeqFileName))
	//{
	//	int nChoice = MessageBox("Sequence File(Model File) is changed. Do you want to recompile?", "SEQ FILE CHANGED!", MB_YESNO);
	//	if (nChoice == IDYES)
	//	{
	//		LoadTestData(gTestSeqData.strSeqFileName);
	//		SetSubListControl();
	//	}
	//}
	if ((CurrentSet->bCompiled != TRUE)
		|| (GetModifyTime(CurrentSet->sSeqPath) != CurrentSet->lTime))
	{
		int nChoice = AfxMessageBox(IDS_QUERY_COMPILE, MB_YESNO);

		switch (nChoice)
		{
		case IDYES:
		{
			CurrentSet->bCompiled = Prescan(CurrentSet->sSeqPath);

			if (CurrentSet->bCompiled == FALSE)
			{
				return; // pView->m_nNoCurrentRepeatExecution = 1; goto END_EXIT;
			}
			SetSubListControl();
		}
		break;
		}
	}
	m_NoAckMainCom = 0;
	ComLogClear();
	ComLog_AddString(_T("[START]"));
	//MessageDisplay(0, _T("START"));
	if (gbManualRefMode == 1)
	{
		m_GMES_Skipped = 1;
	}
	else
	{
		if (CurrentSet->bGMES_Connection)
		{
			if (m_WipID.GetLength() > 5)
			{
				m_GMES_Skipped = 0;
				g_strSetID = m_WipID;
				GMES_Scan_InformSend();//m_WipID

			}
			else
			{
				MessageDisplay(1, _T("BAR CODE EMPTY!! "));
				//MessageBox("Barcode Not Read !\r\n GMES not Availbele!");
				BarcodeErrorDisplay();
				m_TaskRun = TASK_WAIT_BARCODE_PROCESS;
				return;
				/*if(IDYES != MessageBox("Barcode Not Read !\r\n Contonue test?", "Barcode Error", MB_YESNO))
				{
					MessageDisplay(1, _T("TEST STOP !! "));

				}
				else
				{
					m_GMES_Skipped = 1;
				}*/
			}
		}
		else
		{
			m_GMES_Skipped = 1;
			MessageDisplay(1, _T("GMES NOT ENABLE !! "));
			//In BH 181228
			if (m_WipID.GetLength() > 1)
			{
				//	m_GMES_Skipped = 0;
				g_strSetID = m_WipID;
				//	GMES_Scan_InformSend();//m_WipID

			}
			else
			{
				//if(g_strSetID.GetLength() < 2)
				//{
				//	MessageDisplay(1, _T("BAR CODE EMPTY!! "));
				//	//MessageBox("Barcode Not Read !\r\n GMES not Availbele!");
				//	BarcodeErrorDisplay();
				//	m_TaskRun = TASK_WAIT_BARCODE_PROCESS;
				//	return;
				//}
				g_strSetID = "NO_SCAN";

			}
		}
	}
	//Emd In BH 181228

	//CFileControl lFile;
	//CString LogStr;
	//lFile.SaveProcessLOG(LogStr, 1);

//	CLOSE_Result_Display();
	CString szTemp1 = _T("");
	CString szTemp2 = _T("");
	CString szTemp3 = _T("");
	CString szSeqPath = _T("");
	CString szSeqFile = _T("");
	CString sDate = _T("");
	CString sTime = _T("");

	CTime Time;
	Time = CTime::GetCurrentTime();
	sDate = Time.Format("[%y_%m_%d]");
	sTime = Time.Format("%HH_%MM_%SS");
	if (CurrentSet->sModelSuffixName.IsEmpty()) {
		szTemp1.Format(_T("%s\\Data\\%s\\%s\\%s"), m_szExePath, sDate, CurrentSet->sChassisName, CurrentSet->sModelName);
	}
	else {
		szTemp1.Format(_T("%s\\Data\\%s\\%s\\%s"), m_szExePath, sDate, CurrentSet->sChassisName, CurrentSet->sModelSuffixName);
	}
	szTemp2.Format(_T("%s\\%s_%s_%d"), szTemp1, g_strSetID, sTime, g_nRunningProcessNo);

	//	CurrentSet->sGrabFolder			  = szTemp1 + "\\" + sTime + "_" + m_strWipId + "\\";  
	//	CurrentSet->sResultFolder		  = CurrentSet->sGrabFolder;
	//	CurrentSet->sResultPath			  = CurrentSet->sResultFolder + sTime + ".dat";
	//	CurrentSet->sDetailResultDataPath = CurrentSet->sResultFolder + sTime + ".inf";

	CurrentSet->sGrabFolder = szTemp2;
	CurrentSet->sResultFolder = szTemp2;
	CurrentSet->sResultPath = szTemp2 + ".dat";
	CurrentSet->sDetailResultDataPath = szTemp2 + ".inf";

	CurrentSet->sResultSummaryPath = szTemp1 + "\\" + "TestSummary.dat";

	//	if(!FileExists(CurrentSet->sGrabFolder))   CreateFullPath(CurrentSet->sGrabFolder);
	//	if(!FileExists(CurrentSet->sResultFolder)) CreateFullPath(CurrentSet->sResultFolder);
	if (!FileExists(szTemp1)) CreateFullPath(szTemp1);



	m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
	m_LED_COM_PROCESS = COM_MODE_IDLE;
	m_PCB_COM_PROCESS = COM_MODE_IDLE;

	ClearRange();

	SetTimeCheck(4);
	SetTimeCheck(6);

	CString str;
	unsigned long lCheck_Time = GetTimeCheck(4);

	str.Format(_T("%.1f (s)    "), lCheck_Time / 1000.0);
	m_CheckTimeLabel.put_Caption(str);
	m_stcTime.SetWindowText(str);//

	lCheck_Time = GetTimeCheck(5);
	if (lCheck_Time > 1000000)
		lCheck_Time = 1000000;

	//	g_CycleTime = 
	str.Format(_T("%.1f (s)    "), lCheck_Time / 1000.0);
	m_CycleTimeLabel.put_Caption(str);
	m_stcCycleTime.SetWindowText(str);//
	SetTimeCheck(5);

	CheckTimeOn = 1;
	CycleTimeOn = 1;


	//	SetChannelData(0);
	//	InitChannel();	
#ifdef __G_MES_SET_MODE__

#else //#endif
	if (CurrentSet->bGMES_Connection)
	{
		MesStart();
	}
	else
	{
		m_bStartMES = FALSE;
	}
#endif
	m_TaskRun = TASK_RUN_START;
	AddProcessLog("<<START>>", 1);
	m_RunCounter = 0;
	//SetTimer(1,10,NULL);	
	//m_cLb_Test1.put_Caption(_T("WAIT"));
	//m_cLb_Test1.put_BackColor(0x0000FFFF);
	//
	//m_cLb_Test2.put_Caption(_T("WAIT"));
	//m_cLb_Test2.put_BackColor(0x0000FFFF);
	//
	//m_cLb_Test3.put_Caption(_T("WAIT"));
	//m_cLb_Test3.put_BackColor(0x0000FFFF);




	//m_OkNgLabel.put_Text(_T("WAIT"));
	//m_OkNgLabel.put_BackColor(0x0000FFFF);

	m_cLbOkNg.put_Caption(_T("WAIT"));//m_BarCode
	m_cLbOkNg.put_BackColor(0x0000FFFF);



	m_cLb_Lan.put_Caption(_T("WAIT"));
	m_cLb_Lan.put_BackColor(0x0000FFFF);
	m_cLb_Usb1.put_Caption(_T("WAIT"));
	m_cLb_Usb1.put_BackColor(0x0000FFFF);
	m_cLb_Usb2.put_Caption(_T("WAIT"));
	m_cLb_Usb2.put_BackColor(0x0000FFFF);

	m_LAN_CheckOK = 0;
	m_USB1_CheckOK = 0;
	m_USB2_CheckOK = 0;

	for (int i = 0; i < 6; i++)
	{
		m_CheckEnable[i] = 0;
	}


	//if (m_nCurrentNumber == 0)
	//	PosStep = StepList.GetHeadPosition();


	//if (PosStep == NULL)
	//	return FALSE;

	//pCurStep = StepList.GetNext(PosStep);
	//m_nCurrentNumber++;
	//if (m_nCurrentNumber != pCurStep->m_nStep)
	//	return FALSE;
	PosStep = StepList.GetHeadPosition();


	for (int i = 0; i < m_CtrlListMainProcess.GetItemCount(); i++)
	{
		if (PosStep == NULL)
			break;
		pCurStep = StepList.GetNext(PosStep);

		m_CtrlListMainProcess.SetItemText(i, 2, "");
		m_CtrlListMainProcess.SetItemText(i, 3, "");

		//	m_CtrlListMainProcess.SetItem(i, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);   
		//	m_CtrlListMainProcess.SetItem(i, 3, LVIF_TEXT, _T(" "), NULL, NULL, NULL, NULL);   	
		//	m_CtrlListTestProcess.SetItem(i, 9, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);   
		if (m_CtrlListMainProcess.GetCheck(i))
		{
			pCurStep->m_bTest = 1;// gTestSeqData.TestStepList[i].bEnable = 1;
		}
		else
		{
			if (CurrentSet->bGMES_Connection)
			{
				pCurStep->m_bTest = 1; //gTestSeqData.TestStepList[i].bEnable = 1;
				m_CtrlListMainProcess.SetCheck(i);
			}
			else
			{
				pCurStep->m_bTest = 0; //gTestSeqData.TestStepList[i].bEnable = 0;
			}
		}
		//m_CtrlListMainProcess.Update(i);

		gTestSeqData.TestStepList[i].m_Result = 1;
	}
	//m_CtrlListMainProcess.Invalidate();
	for (int i = 0; i < 8; i++)
	{
		m_graph[i].Axes.Item("YAxis-1").Maximum = 1.2;
		m_graph[i].Axes.Item("YAxis-1").Minimum = -1.2;
	}

	gTestSeqData.m_TotalResult = 3;

	m_nCurrentNumber = 0;
	m_nCurrentProcess = 0;
	//for(int i = m_nCurrentNumber;i < gTestSeqData.TestCnt; i++)
	//{	
	//
	//	m_nCurrentNumber = i;
	//	if(gTestSeqData.TestStepList[i].bEnable == 0)
	//	{
	//	}
	//	else
	//	{
	//		
	//		break;
	//	}
	//}
	m_CtrlListMainProcess.Invalidate();

	m_NG_Retry_Count = 1;
	m_NG_WaitFlag = 0;

	SetTimeCheck(1);
}


void CAcqVoltageSamples_IntClkDlg::CallProcess()
{
	//if(m_TEST_Result == 0)//NG
	//{
	//	TestFinish();
	//	return;
	//}
	
	switch(m_nCurrentStep)
	{
	case 0:
		m_nCurrentStep = 1;
		//m_InterProcess
		m_InterProcess = STEP_FUNC_START;
		SetFunction();
		break;
	case 1:
		RunFunction();
		break;
	case 2:
		//GetFunction();m_nCurrentNumber

		m_nCurrentStep = 0;
		m_nCurrentProcess = 0;
		if (pCurStep->m_bResult == TEST_FAIL)
		{

			m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);


			//	if(IDYES == MessageBox("NG RETRY?" , "NG" , MB_YESNO))
			//	{
			//		m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
			//		//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
			//		m_nCurrentProcess = 0;
			////		if(GetTimeCheck(1) > m_CheckDelayTime)

			//	}
			//	else
			//	{
			//		TestFinish();
			//	}
			NG_Display(m_GMES_ErrorName);
			m_TaskRun = TASK_WAIT_SELECT_PROCESS;

			//m_NG_Retry_Count++;//m_NG_WaitFlag = 0;

			break;
		}
		else
		{
			if (pCurStep->m_bResult == TEST_SKIP)
			{
				m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "SKIP", NULL, NULL, NULL, NULL);
			
			}
			else if (pCurStep->m_bResult == TEST_PASS)//if(gTestSeqData.TestStepList[m_nCurrentNumber].m_Result == 1)
			{
				m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
			}
	
		
	//		if (pCurStep->m_bResult == TEST_FAIL)		
//mpDlgSimpleInform->ShowWindow(SW_SHOW);

			if(mpDlgSimpleInform->IsWindowVisible())
			{
				mpDlgSimpleInform->ShowWindow(0);
			}
			m_NoAckMainCom = 0;

			for(int i = 0; i < 6; i++)
			{
				m_nBalanceEnable[i] = 0;
			}
			
			

			unsigned long lCheck_Time = GetTimeCheck(6);
			CString str;
			str.Format(_T("%.1f"), lCheck_Time/1000.0);
			m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			SetTimeCheck(6);

			m_nCurrentNumber++;
	/*
			int i;
			for( i = m_nCurrentNumber;i < gTestSeqData.TestCnt; i++)
			{
				if(gTestSeqData.TestStepList[i].bEnable == 0)
				{
				}
				else
				{
					break;
				}
			}
			m_nCurrentNumber = i;*/

			
			if(m_nCurrentNumber >= StepList.GetSize())
			{
				m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				TestFinishGMES();//TestFinish();
			}
			else
			{
				m_nCurrentProcess = 0;		
				for(int  i = 0; i < 6; i++)
				{
					m_CheckEnable[i] = 0;
				}
			}
			//m_CtrlListMainProcess.Invalidate();
			//RECT lRectPrev;
			//RECT lRect;
			//RECT lRectEn;
			//RECT lMainRect;
			int lPrevNumber = (m_nCurrentNumber > 0)?m_nCurrentNumber - 1:0;
			for (int i = 0; i < 3; i++)
			{
				str = m_CtrlListMainProcess.GetItemText(lPrevNumber, i);
				m_CtrlListMainProcess.SetItemText(lPrevNumber, i, str);
				str = m_CtrlListMainProcess.GetItemText(m_nCurrentNumber, i);
				m_CtrlListMainProcess.SetItemText(m_nCurrentNumber, i, str);
			}
			//m_CtrlListMainProcess.GetWindowRect(&lMainRect);
			//m_CtrlListMainProcess.GetItemRect(lPrevNumber, &lRectPrev, LVIR_LABEL);
			//m_CtrlListMainProcess.GetItemRect(m_nCurrentNumber, &lRect, LVIR_LABEL);
			//	lRectEn.

			//lRect.left = lRectPrev.left + lMainRect.left-5;
			//lRect.top = lRectPrev.top + lMainRect.top-5;
			//lRect.right = lMainRect.right+10;
			//lRect.bottom = lRect.bottom +lMainRect.top+10;
			//InvalidateRect(&lRect);

			m_NG_Retry_Count = 1;
			m_NG_WaitFlag = 0;
		}
		


		break;
	default:
		break;
	}

	//m_OKcnt = 0;
	//SetTimeCheck(1);
}

	//void CAcqVoltageSamples_IntClkDlg::SetFunction()
	//void CAcqVoltageSamples_IntClkDlg::RunFunction()
int CAcqVoltageSamples_IntClkDlg::SetFunction(CString lString, int lStringIn)
{
	//m_nCurrentNumber
	CString Str;


	if (m_nCurrentNumber == 0)
		PosStep = StepList.GetHeadPosition();


	if (PosStep == NULL)
		return FALSE;

	pCurStep = StepList.GetNext(PosStep);
	int lCheck = m_CtrlListMainProcess.GetCheck(m_nCurrentNumber);
	if (lCheck == 0)
	{
		
		m_nCurrentStep = 2;
		pCurStep->m_bResult = TEST_SKIP;
		Str.Format("Skip Step %d:", m_nCurrentNumber + 1);
		Str += pCurStep->GetStepName();
		ComLog_AddString(Str);
		return TRUE;
	}
	if ((pCurStep->m_bRunVideoTest == 0)&&(gbManualRefMode==1))
	{
		m_nCurrentStep = 2;
		pCurStep->m_bResult = TEST_SKIP;
		Str.Format("Skip No Ref Step %d:", m_nCurrentNumber + 1);
		Str += pCurStep->GetStepName();
		ComLog_AddString(Str);
		return TRUE;
	}
	
	if (m_nCurrentNumber+1 != pCurStep->m_nStep)
		return FALSE;
	Str.Format("Set Step %d:", m_nCurrentNumber + 1);
	Str += pCurStep->GetStepName();
	ComLog_AddString(Str);
	return TRUE;

}



void CAcqVoltageSamples_IntClkDlg::RunFunction()
{

	int nPosition = 0;
	BOOL nResult = TEST_WAIT;
	static int sWaitCnt = 0;
	static DWORD s_Start_Time = 0;// 
	static clock_t sFuncStepStart;
	CString Str;
	clock_t lCurClock;
	if (sWaitCnt > 0)
		sWaitCnt--;
	//if(m_TEST_Result == 0)//NG
	//{
	//	TestFinish();
	//	return;
	//}


//#define STEP_FUNC_START		0
//#define STEP_FUNC_SET			1
//#define STEP_FUNC_RUN			2

	switch(m_InterProcess )
	{
	case STEP_FUNC_START:

		PosFunc = pCurStep->m_InstructionList.GetHeadPosition();		
		if (pCurStep->m_nStepType == PROCESS_FUNCTION)
		{
			pCurStep->SetResult(TRUE);
		}

		m_nCurrentProcess = 0;

		if (PosFunc != NULL)
		{
			m_InterProcess = STEP_FUNC_SET;
			StepStart = clock();

		}
		else
		{
			pCurStep->SetResult(FALSE);
			m_InterProcess = STEP_FUNC_END;
		}
		break;

	case STEP_FUNC_SET:
		m_nCurrentProcess++;

		if (PosFunc != NULL)
		{
			
			pCurFunc = pCurStep->m_InstructionList.GetNext(PosFunc);
			pCurFunc->m_nFuncTimeLimit = 1000;
			pCurFunc->m_nFuncTestType = _FUNC_NO_TEST_PASS__TYPE;

			Str.Format("Set Function %d:", m_nCurrentProcess + 1);
			Str += pCurFunc->m_strFuncName;
			ComLog_AddString(Str);

			//ComLog_AddString
			nResult = (*pCurFunc->m_pFunc)();
			// CString str = pCurFunc->m_strCommant;
			if (nResult != TEST_PASS)
			{
				pCurStep->SetResult(FALSE);
				m_InterProcess = STEP_FUNC_END;
			}
			else
			{
				m_InterProcess = STEP_FUNC_RUN;
				sFuncStepStart = clock();

			}
		}
		else
		{
			m_InterProcess = STEP_FUNC_END;
		}
		break;
	case STEP_FUNC_RUN:
		//m_nCurrentProcess++;
		switch (pCurFunc->m_nFuncTestType)
		{
			
		case _FUNC_WORK_TEST_TYPE:
			nResult = Work_Normal_Check();
			if (nResult != TEST_PASS)
			{
				lCurClock = (clock() - sFuncStepStart);
				//g_pView->m_nMeasureWait pCurFunc->m_nFuncTimeLimit
				if (lCurClock > pCurFunc->m_nFuncTimeLimit)
				{					
					nResult = TEST_FAIL;
				}
				else
				{
					nResult = TEST_WAIT;
				}
			}
			else
			{
				if ((pCurFunc->m_nFuncTestType == _FUNC_MIO_TEST_TYPE)
					||(pCurFunc->m_nFuncTestType == _FUNC_MAC_ADD_TEST_TYPE)
					||(pCurFunc->m_nFuncTestType == _FUNC_VERSION_CHECK_TEST_TYPE)
					||(pCurFunc->m_nFuncTestType == _FUNC_MOVING_PC_TEST_TYPE))
				{
					nResult = TEST_WAIT;
					pCurFunc->m_nFuncTimeLimit = 1000;
				}
			}
			break;
		case _FUNC_MOVING_PC_TEST_TYPE:
			nResult = ScreenMovingPicCheck();//
			if (nResult == TEST_WAIT)
			{
				lCurClock = clock();
				if (((double)(lCurClock - sFuncStepStart)) > pCurFunc->m_nFuncTimeLimit)
				{
					nResult = TEST_FAIL;
				}
			}
			
			break;
		case _FUNC_MAC_ADD_TEST_TYPE:
			nResult = TVCommCtrl.MAC_AddressCheck();//
			if (nResult == TEST_WAIT)
			{
				lCurClock = clock();
				if (((double)(lCurClock - sFuncStepStart)) > pCurFunc->m_nFuncTimeLimit)
				{
					nResult = TEST_FAIL;
				}
			}
			

			break;		case _FUNC_MIO_TEST_TYPE:
			nResult = gSMDIO_Ctrl.CheckResultMIO();
			if (nResult == TEST_WAIT)
			{
				lCurClock = clock();
				if (((double)(lCurClock - sFuncStepStart)) > pCurFunc->m_nFuncTimeLimit)
				{
					nResult = TEST_FAIL;
				}
			}
			else if (nResult == TEST_NEXT)
			{
				sFuncStepStart = clock();
				//if (((double)(lCurClock - sFuncStepStart)) > pCurFunc->m_nFuncTimeLimit)
				//{
				//	nResult = TEST_FAIL;
				//}
			}
			
			break;
		case _FUNC_UART_COMMAND_TEST_TYPE:
			nResult = TVCommCtrl.UartCheck();
			if (nResult == TEST_WAIT)
			{			
				lCurClock = clock();
				if (((double)(lCurClock - sFuncStepStart) ) > TVCommCtrl.m_nWaitLimit)
				{
					nResult = TEST_FAIL;
				}
			}
			break;
		case _FUNC_VERSION_CHECK_TEST_TYPE:
			nResult = TVCommCtrl.Firmware_VersionCheck();
			break;

		case _FUNC_NO_TEST_PASS__TYPE:
			nResult = TEST_PASS;
			break;

		case _FUNC_AUDIO_TEST_TYPE:
			nResult = TEST_PASS;
			break;

		case _FUNC_VIDEO_TEST_TYPE:
			nResult = TEST_PASS;
			break;

		case _FUNC_WAIT_DELAY_TYPE:
			if (nResult != TEST_PASS)
			{
				nResult = TEST_WAIT;
				lCurClock = clock();
				if (((double)(lCurClock - sFuncStepStart) ) > pCurFunc->m_nFuncTimeLimit)
				{
					nResult = TEST_PASS;
				}
			}
			break;

		case _FUNC_AV_SWITCH_CTRL_TYPE:

			nResult = AvSwitchBoxCtrl.WaitReceiveMsg();
			if (nResult == TEST_WAIT)
			{
				if (((double)(clock() - sFuncStepStart) ) > pCurFunc->m_nFuncTimeLimit)
				{
					nResult = TEST_FAIL;
				}
			}			
			break;

		case _FUNC_WAIT_MANUAL_WAIT_TYPE:
			if (m_pUserMsgDlg->m_bActivate == 1)
			{
				//m_pUserMsgDlg->ShowWindow(SW_HIDE);	
				if (nResult == TEST_WAIT)
				{
					if (((double)(clock() - sFuncStepStart)) > pCurFunc->m_nFuncTimeLimit)
					{
						nResult = TEST_FAIL;
					}
				}
			}
			else
			{
				if (m_pUserMsgDlg->m_bYes == 1)
				{
					nResult = TEST_PASS;
				}
				else
				{
					nResult = TEST_FAIL;
				}

			}
			break;

		default:
			//MessageBox("Not Defined Function!!");
			break;
		}
		//m_InterProcess = STEP_FUNC_SET;

		if (nResult == TEST_PASS)
		{
			m_InterProcess = STEP_FUNC_SET;
			pCurStep->SetResult(TRUE);
			//if (nResult == TEST_PASS)
			//pCurStep->m_bResult = TEST_PASS;
		}
		else if (nResult == TEST_FAIL)
		{
			pCurStep->SetResult(FALSE);
			m_InterProcess = STEP_FUNC_END;

			//	if (CurrentSet->bRunAbort)nResult = TEST_ABORT;
				//g_nNoFailedStep++;
			//pCurStep->SetElapsedTime((double)(clock() - StepStart) / CLOCKS_PER_SEC);
			//InsertResultData2Grid(CurrentSet->nDisplayType, pCurStep->m_nStep);
			//return;
		}

		//if (pCurFunc != NULL)
		//{
		//	//pCurFunc = pCurStep->m_InstructionList.GetNext(PosFunc);
		//	nResult = (*pCurFunc->m_pFunc)();


		//	if (nResult == TEST_PASS)
		//	{
		//		m_InterProcess = STEP_FUNC_SET;
		//	}
		//	else if (nResult == TEST_FAIL)
		//	{
		//		pCurStep->SetResult(FALSE);
		//		m_InterProcess = STEP_FUNC_END;

		//		//	if (CurrentSet->bRunAbort)nResult = TEST_ABORT;
		//			//g_nNoFailedStep++;
		//		//pCurStep->SetElapsedTime((double)(clock() - StepStart) / CLOCKS_PER_SEC);
		//		//InsertResultData2Grid(CurrentSet->nDisplayType, pCurStep->m_nStep);

		//		//return;
		//	}
		//	//else
		//	//{
		//	//	if(((double)(clock() - StepStart) / CLOCKS_PER_SEC)
		//	//}
		//}
		break;
	case STEP_FUNC_END:
		//m_nCurrentProcess++;
		m_nCurrentStep = 2;
		if (pCurStep->GetResult() == TEST_PASS)
			pCurStep->m_bResult = TEST_PASS;
	
		break;
	default:

		break;
	}
	
	return;	   
}

void CAcqVoltageSamples_IntClkDlg::InsertResultData2Grid(int nGridType, int nStepNo)
{
	if (nGridType == DETAILEDGRID) InsertResult2DetailedGrid(nStepNo);
}

void CAcqVoltageSamples_IntClkDlg::InsertResult2DetailedGrid(int nStepNo)
{
	if ((nStepNo > (m_CtrlListMainProcess.GetItemCount() - 1)) || (nStepNo <= 0)) return;
	nStepNo -= 1;
	CString sTmp;
	//	m_ctrlSummaryGrid.SetRedraw(flexRDNone);
	//	m_ctrlSummaryGrid.SetRow(nStepNo);

		//if (nStepNo % 7 == 0) m_CtrlListMainProcess.Scroll(nStepNo*20);//.settop.SetTopRow(nStepNo);

		// (Column 11) Elapsed Time
	if (pCurStep->m_nStepType == PROCESS_FUNCTION)
	{
		sTmp.Format(_T("%5.1f"), pCurStep->m_fElapsedTime);

		//	m_ctrlSummaryGrid.SetCol(11);
		//	m_ctrlSummaryGrid.SetColDataType(11, flexDTString);
		//	m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 11, sTmp);

		//	m_ctrlSummaryGrid.SetRedraw(-1);
		//	m_ctrlSummaryGrid.Refresh();
		m_CtrlListMainProcessEx.SetCellBackColor(nStepNo, 2, RGB(255, 255, 128));
		m_CtrlListMainProcess.SetItem(nStepNo, 2, LVIF_TEXT, "PASS", NULL, NULL, NULL, NULL);
		m_CtrlListMainProcess.SetItem(nStepNo, 11, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL);
		return;
	}

	//===============
	// Test Function
	//===============
	if (pCurStep->m_bTest) // == TRUE)
	{
		//===================
		// (Column 3) Result
		//===================
		if (pCurStep->m_bResult) // PASS
		{
			sTmp = _T("OK");
			//m_ctrlSummaryGrid.SetCol(3);
			//m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
			m_CtrlListMainProcessEx.SetCellBackColor(nStepNo, 2, RGB(0, 0, 255));
			m_CtrlListMainProcessEx.SetCellForeColor(nStepNo, 2, RGB(255, 255, 255));
			//m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 3, sTmp);

			m_CtrlListMainProcess.SetItem(nStepNo, 2, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL);
		}
		// NG
		else
		{
			//090324
			sTmp = _T("NG");
			if (pCurStep->m_bRunAudioTest && pCurStep->m_bRunVideoTest)
			{

				if (pCurStep->m_bVideoTestResult == FALSE)
				{
					sTmp = _T("NG/V");
				}

				if (pCurStep->m_bAudioTestResult == FALSE)
				{
					sTmp = _T("NG/A");
				}

				if ((pCurStep->m_bVideoTestResult == FALSE) && (pCurStep->m_bAudioTestResult == FALSE))
				{
					sTmp = _T("NG/AV");
				}
			}
			else if (!pCurStep->m_bRunAudioTest && pCurStep->m_bRunVideoTest)
			{
				if (pCurStep->m_bVideoTestResult == FALSE)
				{
					sTmp = _T("NG/V");
				}
			}
			else if (pCurStep->m_bRunAudioTest && !pCurStep->m_bRunVideoTest)
			{
				if (pCurStep->m_bAudioTestResult == FALSE)
				{
					sTmp = _T("NG/A");
				}
			}
			else
			{
				sTmp = _T("NG");
			}

			//m_ctrlSummaryGrid.SetCol(3);
			//m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
			//m_ctrlSummaryGrid.SetCellBackColor(RGB(255,0,0));
			//m_ctrlSummaryGrid.SetCellForeColor(RGB(255,255,255));
			//m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 3, sTmp);

			m_CtrlListMainProcessEx.SetCellBackColor(nStepNo, 2, RGB(255, 0, 0));
			m_CtrlListMainProcessEx.SetCellForeColor(nStepNo, 2, RGB(255, 255, 255));
			m_CtrlListMainProcess.SetItem(nStepNo, 2, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL);
		}
		if (pCurStep->m_bRunAudioTest)
		{
			sTmp.Format(_T("%d, %d, %d, %d"), pCurStep->m_nLeftFreq[1], pCurStep->m_nRightFreq[1], pCurStep->m_nLeftLevel[1], pCurStep->m_nRightLevel[1]);

			//m_ctrlSummaryGrid.SetCol(10);
			//m_ctrlSummaryGrid.SetColDataType(10, flexDTString);
			m_CtrlListMainProcess.SetItem(nStepNo, 10, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo , 10, sTmp);
		}

		//+add kwmoon 081013
		if (pCurStep->m_bAdcValueCheckStep)
		{
			//========================================================
			// (Column 10) Display ADC value instead of Audio Measure
			//========================================================
			sTmp = pCurStep->m_szAdcValue;
			//m_ctrlSummaryGrid.SetCol(10);
			//m_ctrlSummaryGrid.SetColDataType(10, flexDTString);
			m_CtrlListMainProcess.SetItem(nStepNo, 10, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo , 10, sTmp);
		}
	}
	//======
	// SKIP
	//======
	else // if(pCurStep->m_bTest == FALSE)
	{
		sTmp = _T("SKIP");
		//m_ctrlSummaryGrid.SetCol(3);
		//m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
		//m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 3, sTmp);
		//m_ctrlSummaryGrid.SetRedraw(-1);
		//m_ctrlSummaryGrid.Refresh();

		m_CtrlListMainProcess.SetItem(nStepNo, 2, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // 
		return;
	}

	// (Column 4) Measure
	if (pCurStep->m_nFuncType == MEAS_BOOL)
	{
		if (pCurStep->m_bMeasured == FALSE) sTmp.Format(_T("%s"), "FALSE");
		else sTmp.Format(_T("%s"), "TRUE");
	}
	else sTmp.Format(_T("%4.1f"), pCurStep->m_fMeasured);

	if (pCurStep->m_nTestType == MULTICHECL_TEST) {
		sTmp.Format(_T("%.02f, %.02f"), pCurStep->m_fMeasured_L, pCurStep->m_fMeasured_R);
	}

	//m_ctrlSummaryGrid.SetCol(4);
	//m_ctrlSummaryGrid.SetColDataType(4, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 4, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 4, sTmp);

	// (Column 5) Target
	if (pCurStep->m_nFuncType == MEAS_BOOL)
	{
		if (pCurStep->m_bNominal == FALSE) sTmp.Format(_T("%s"), "FALSE");
		else sTmp.Format(_T("%s"), "TRUE");
	}
	else sTmp.Format(_T("%4.1f"), pCurStep->m_fNominal);

	//m_ctrlSummaryGrid.SetCol(5);
	//m_ctrlSummaryGrid.SetColDataType(5, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 5, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 5, sTmp);



	// (Column 11) Elapsed Time
	sTmp.Format(_T("%5.1f"), pCurStep->m_fElapsedTime);
	//m_ctrlSummaryGrid.SetCol(11);
	//m_ctrlSummaryGrid.SetColDataType(11, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 11, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 11, sTmp);

	//m_ctrlSummaryGrid.SetRedraw(-1);
	//m_ctrlSummaryGrid.Refresh();
	m_CtrlListMainProcess.Invalidate();

	return;
}

//int CAcqVoltageSamples_IntClkDlg::SetFunction(CString lString, int lStringIn)
//{
//	//m_nCurrentNumber
//
//	
//
//	if(m_nCurrentNumber == 0)
//		PosStep = StepList.GetHeadPosition();
//
//
//	if (PosStep == NULL)
//		return FALSE;
//
//	pCurStep = StepList.GetNext(PosStep);
//	m_nCurrentNumber++;
//	if(m_nCurrentNumber != pCurStep->m_nStep)
//		return FALSE;
//
//	return TRUE;
//
//	int lFileError = 0;
//	CString lFunctionString;
//	
//	m_FunctionType = TEST_SEQ_TYPE_END;
//
//	//lFunctionString = gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//	if (lStringIn == 1)
//	{
//		lFunctionString = lString;
//	}
//	else
//	{
//		lFunctionString = gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//	}
//	int lpos, lendpos;
//	lpos = lFunctionString.Find("(");
//	lendpos = lFunctionString.Find(")");
//	lFunctionString = lFunctionString.Left(lendpos);
//	m_FunctionName = lFunctionString.Left(lpos);
//	m_FunctionName = m_FunctionName.MakeLower();
//	m_FunctionParameter = lFunctionString.Mid(lpos+1);
//
//	if(m_FunctionName.Compare("delay") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_DELAY;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		if(m_CheckDelayTime < 0)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}//TEST_SEQ_TYPE_BEEP
//	else  if(m_FunctionName.Compare("power_on_check") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_POWER_ON_CHECK;
//		//SendPower(lIndex, 0);
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		if(m_CheckDelayTime < 0)
//		{
//			lFileError = 1;
//			m_CheckDelayTime = 1000;
//		}
//	}
//	//else if(m_FunctionName.Compare("beep") == 0)
//	//{
//	//	m_FunctionType = TEST_SEQ_TYPE_BEEP;
//	//	
//	//	m_LED_Up_DI_ReadData[1] = 0;
//	//	m_LED_Up_DI_ReadData[2] = 0;
//
//	//	int lpos, lendpos;
//	//	DWORD lFreq,lDelay;
//
//
//	//	lpos = m_FunctionParameter.Find(",");	
//
//	//	CString str1 = m_FunctionParameter.Left(lpos);
//	//	CString str2 = m_FunctionParameter.Mid(lpos+1);
//	//	//
//	//	//lFreq = _ttoi(str1);
//	//	lDelay = _ttoi(str2);
//	//	//if(lFreq > 2000)
//	//	//{
//	//	//	lFreq = 800;
//	//	//}
//	//	//if(lDelay > 5000)
//	//	//{
//	//	//	lDelay = 300;
//	//	//}
//	//	//Beep(1200, 1000);
//	//	mpDlgSimpleInform->m_DisplayString = str1;
//	//	mpDlgSimpleInform->m_Count = lDelay;
//	//	CRect rectP;
//	//	CRect rect;		
//	//	
//	//	mpDlgSimpleInform->m_WaitMassage = 0;
//	//	mpDlgSimpleInform->m_Close_Result =  _OPEN_DISPLAY_;
//
//	//	this->GetWindowRect(&rectP);
//	//	mpDlgSimpleInform->GetWindowRect(&rect);
//
//	//	mpDlgSimpleInform->ShowWindow(SW_SHOW);
//	//	mpDlgSimpleInform->SetWindowPos(this,rectP.left+ 300,rectP.top+350,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
//	//	//mpDlgSimpleInform->ShowWindow(SW_SHOW);
//	//	
//	//	CString m_NgWaveFile  = _T(PATH_BASE_DIR);
//	//	m_NgWaveFile  += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//	//	sndPlaySound( m_NgWaveFile , SND_ASYNC);
//	//	
//	//	//m_nCurrentStep = 2;
//	//}
//	else if(m_FunctionName.Compare("usermessage") == 0)
//	{
//		CString str1;
//		CString str2;
//		CString str3;
//		CString str4;
//
//
//		m_FunctionType = TEST_SEQ_TYPE_USER_MASSAGE;
//		
//		m_LED_Up_DI_ReadData[1] = 0;
//		m_LED_Up_DI_ReadData[2] = 0;
//
//		int lpos, lendpos;
//		DWORD lFreq,lDelay;
//
//		lpos = m_FunctionParameter.Find(",");
//		
//		str1 = m_FunctionParameter.Left(lpos);		
//		str2 = m_FunctionParameter.Mid(lpos+1);
//				
//		str1.Trim();
//		str1.TrimLeft("\"");
//		str1.TrimRight("\"");
//		
//		lpos = str2.Find(",");	
//		if(lpos > 0)
//		{
//			str3 = str2.Left(lpos);		
//			str4 = str2.Mid(lpos+1);
//			str3.Trim();
//			str3.TrimLeft("\"");
//			str3.TrimRight("\"");	
//
//			lDelay = _ttoi(str4);
//			m_pUserMsgDlg->SetMessageTime(str1, str3, lDelay);
//		}
//		else
//		{
//			str2.Trim();
//			str2.TrimLeft("\"");
//			str2.TrimRight("\"");	
//
//			lDelay = _ttoi(str2);
//			m_pUserMsgDlg->SetMessageTime(str1, "", lDelay);
//		}
//		m_pUserMsgDlg->m_bShowOkButton = 0;		
//		m_pUserMsgDlg->m_Close_Result =  _OPEN_DISPLAY_;
//
//		CRect rectP;
//		CRect rect;	
//		this->GetWindowRect(&rectP);
//		m_pUserMsgDlg->GetWindowRect(&rect);
//
//		m_pUserMsgDlg->ShowWindow(SW_SHOW);
//		m_pUserMsgDlg->SetWindowPos(this,rectP.left+ 300,rectP.top+350,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
//		
//		if (lStringIn == 0)
//		{
//			CString m_NgWaveFile = _T(PATH_BASE_DIR);
//			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//			sndPlaySound(m_NgWaveFile, SND_ASYNC);
//		}
//		
//	
//	
//
////BOOL _NotifyMessage()
////{
////
////	CString sMsg1;
////	CString sMsg2;
////	BOOL    bRetrun = TRUE;
////
////	pos = pCurFunc->m_ArgumentList.GetHeadPosition();
////	if (pos!= NULL)
////	{
////        sMsg1 = GetString();
////        sMsg2 = GetString();
////
////		g_pView->m_UserMsgDlg.SetMessage(sMsg1,sMsg2);
////		g_pView->m_UserMsgDlg.DoModal();
////
////		bRetrun = g_pView->m_UserMsgDlg.m_bYes;
////	
////	}
////
////	if(!bRetrun) CurrentSet->bRunAbort = TRUE;
//////090408
//////	return bRetrun;
////	return TRUE;
////}
//
//	}
//	else if(m_FunctionName.Compare("manual_check") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MANUAL_CHECK;
//
//		m_LED_Up_DI_ReadData[1] = 0;
//		m_LED_Up_DI_ReadData[2] = 0;
//
//		int lpos, lendpos;
//		DWORD lFreq,lDelay;
//
//
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//		//
//		//lFreq = _ttoi(str1);
//		lDelay = _ttoi(str2);
//		//if(lFreq > 2000)
//		//{
//		//	lFreq = 800;
//		//}
//		//if(lDelay > 5000)
//		//{
//		//	lDelay = 300;
//		//}
//		//Beep(1200, 1000);
//		mpDlgSimpleInform->m_DisplayString = str1;
//		mpDlgSimpleInform->m_Count = lDelay;
//		CRect rectP;
//		CRect rect;		
//		
//		this->GetWindowRect(&rectP);
//		mpDlgSimpleInform->GetWindowRect(&rect);
//
//		mpDlgSimpleInform->m_WaitMassage = 0;
//		mpDlgSimpleInform->m_Close_Result =  _OPEN_DISPLAY_;
//		mpDlgSimpleInform->ShowWindow(SW_SHOW);
//		mpDlgSimpleInform->SetWindowPos(this,rectP.left+ 300,rectP.top+350,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
//		//mpDlgSimpleInform->ShowWindow(SW_SHOW);
//		if (lStringIn == 0)
//		{
//			CString m_NgWaveFile = _T(PATH_BASE_DIR);
//			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//			sndPlaySound(m_NgWaveFile, SND_ASYNC);
//		}
//		//m_nCurrentStep = 2;
//	}	
//	else if(m_FunctionName.Compare("waitmessage") == 0)// waitmessage("ARC SPK Out Test" ,"" )
//	{
//		m_FunctionType = TEST_SEQ_TYPE_WAIT_MASSAGE;
//
//		m_LED_Up_DI_ReadData[1] = 0;
//		m_LED_Up_DI_ReadData[2] = 0;
//
//		int lpos, lendpos;
//		DWORD lFreq,lDelay;
//
//
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//		//
//		
//		str1.Trim();
//		str1.TrimLeft("\"");
//		str1.TrimRight("\"");
//		
//		str2.Trim();
//		str2.TrimLeft("\"");
//		str2.TrimRight("\"");
//		
//
//		CRect rectP;
//		CRect rect;		
//		
//		
//		m_pUserMsgDlg->SetMessage(str1, str2);
//		m_pUserMsgDlg->m_bShowOkButton = 1;		
//		m_pUserMsgDlg->m_Close_Result =  _OPEN_DISPLAY_;
//
//		this->GetWindowRect(&rectP);
//		m_pUserMsgDlg->GetWindowRect(&rect);
//
//		m_pUserMsgDlg->ShowWindow(SW_SHOW);
//		m_pUserMsgDlg->SetWindowPos(this,rectP.left+ 300,rectP.top+350,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
//		
//		if (lStringIn == 0)
//		{
//			CString m_NgWaveFile = _T(PATH_BASE_DIR);
//			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//			sndPlaySound(m_NgWaveFile, SND_ASYNC);
//		}
//		
//		
//	}
//	else if((m_FunctionName.Compare("remocon_out") == 0)||(m_FunctionName.Compare("remocon_out1") == 0))
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_KEY;
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//
//
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("remocon_out2") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_PRE_KEY;
//		int lpos, lendpos;
//	/*	lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);
//		m_strMP_Key = strtemp;*/
//		
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("remocon_repeat") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		//////////////////////////////////////////////////
//		m_FunctionParameter = m_FunctionParameter.Mid(lendpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		strtemp = m_FunctionParameter.Left(lpos);
//		m_RepeatCount = _ttoi(strtemp);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		m_FunctionParameter.Mid(lpos+1);
//	//	lpos = m_FunctionParameter.Find(",");
//	
//		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
//		m_CheckDelayTime = _ttoi(strtemp);
//
//		////////////////////////////////////////////////
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}	
//
//	else if(m_FunctionName.Compare("remocon_repeat10") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT10_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("remocon_repeat2") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_PRE_REPEAT_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		//////////////////////////////////////////////////
//		m_FunctionParameter = m_FunctionParameter.Mid(lendpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		strtemp = m_FunctionParameter.Left(lpos);
//		m_RepeatCount = _ttoi(strtemp);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		m_FunctionParameter.Mid(lpos+1);
//	//	lpos = m_FunctionParameter.Find(",");
//	
//		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
//		m_CheckDelayTime = _ttoi(strtemp);
//
//		////////////////////////////////////////////////
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("set_audio_display") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_SET_DISPLAY;
//
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//		
//		int l_nChannel = _ttoi(str1);
//		int l_nRange = _ttoi(str2);
//
//		if(l_nChannel > 8)
//		{
//			for(int i = 0; i < 8; i++)
//			{
//				
//				m_graph[i].Axes.Item("YAxis-1").Maximum = l_nRange/1000.0/2.0;
//				m_graph[i].Axes.Item("YAxis-1").Minimum = -l_nRange/1000.0/2.0;
//			}
//		}
//		else if((l_nChannel > 0)&&(l_nChannel <= 8))
//		{
//			m_graph[l_nChannel-1].Axes.Item("YAxis-1").Maximum = l_nRange/1000.0/2.0;
//			m_graph[l_nChannel-1].Axes.Item("YAxis-1").Minimum = -l_nRange/1000.0/2.0;
//		}
//
//		//if(m_CheckDelayTime < 50)
//		//{
//		//	m_CheckDelayTime = 1000;
//		//}
//
//		m_nCurrentStep = 2;
//	}
//	else if(m_FunctionName.Compare("set_audio_channel") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_SET_AUDIO;
//
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//		
//		m_nChannel = _ttoi(str1);
//		m_nSource = _ttoi(str2);
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if((m_FunctionName.Compare("check_audio_range") == 0)||(m_FunctionName.Compare("check_audio") == 0))
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO;
//		int lpos, lendpos;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_nChannel = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMin = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMax = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageMin = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageMax = _ttoi(str1);
//
//		
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageBalnce = _ttoi(str1);
//
//		if((m_TmpVoltageBalnce > 95)||(m_TmpVoltageBalnce < 5))
//		{
//
//			m_TmpVoltageBalnce = 0;
//
//		}
//
//
//		if(m_CheckDelayTime < 50)
//		{
//
//			m_CheckDelayTime = 1000;
//		}
//
//	}
//	else if(m_FunctionName.Compare("check_balance") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_RL_BALANCE;
//		int lpos, lendpos;
//
//	//		int m_nBalanceEnable[8];
//	//int m_nBalanceChannel[8];
//	//int m_nBalanceValue[8];
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		int l_nBalance = _ttoi(str1);
//		if((l_nBalance > 0)&&(l_nBalance <= 8))
//		{
//			int lIndex = l_nBalance - 1;//Zero base
//			m_nBalanceEnable[lIndex] = 1;
//
//			m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//			lpos = m_FunctionParameter.Find(",");
//			str1 = m_FunctionParameter.Left(lpos);
//			
//			m_nBalanceChannel[lIndex] = _ttoi(str1);
//			if((m_nBalanceChannel[lIndex] > 0)&&(m_nBalanceChannel[lIndex] <= 8))
//			{
//				m_nBalanceChannel[lIndex] = m_nBalanceChannel[lIndex] - 1;
//			}
//			else
//			{
//				m_nBalanceEnable[l_nBalance] = 0;
//			}
//				
//
//			m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//			//m_FunctionParameter.Mid(lpos+1);
//		//	lpos = m_FunctionParameter.Find(",");
//			str1 = m_FunctionParameter;//.Left(lpos);
//			m_nBalanceValue[lIndex] = _ttoi(str1);
//
//			
//
//			if(m_nBalanceValue[lIndex] < 0)
//			{
//				m_nBalanceValue[lIndex] = 0;
//				m_nBalanceEnable[lIndex] = 0;
//			}
//
//			if(m_CheckDelayTime < 50)
//			{
//				m_CheckDelayTime = 1000;
//			}
//		}
//			m_nCurrentStep = 2;
//
//	}
//	else if(m_FunctionName.Compare("check_audio_work") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO_WORK;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//
//		InitChannel();	
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("check_lan") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_LAN;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("check_usb1") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_USB1;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("check_usb2") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_USB2;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("check_camera_ocr") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_OCR;	
//
//		int lpos, lendpos;
//	/*	lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//		m_strCameraCheckChar = lFunctionString.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strCameraCheckIMGfile = strtemp;
//		if(m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//
//	}
//	else if(m_FunctionName.Compare("check_camera_image") == 0)
//	{
//		m_Camera_CheckOK = 3;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE;
//
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos+1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strCameraCheckIMGfile = strtemp;
//		//check_camera_image("check_sum.jpg",85,3000 )
//
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_Match_Percent = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter;//.Left(lpos);
//		m_CheckDelayTime = _ttoi(str1);
//	//	m_Match_Percent
//		//lpos = m_FunctionParameter.Find("\"");
//		//lendpos = m_FunctionParameter.Find("\"");
//		//m_strCameraCheckIMGfile = lFunctionString.Mid(lpos+1,lendpos);	
//		if((m_Match_Percent < 50) || (m_Match_Percent > 95))
//			m_Match_Percent = 85;
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("uartcheck") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_UART_COMMAND;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		str1.MakeUpper();
//		CString str2;
//		str2 = str1;
//
//		for(int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if(lpos  >= 0)
//			{
//			//	str1.Find("0/X");
//				
//				m_UartCommand[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos+4);
//
//				m_UartCommandCnt = i+1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//	//		unsigned char m_UartCommand[50];
//	//int m_UartCommandCnt;
//	//unsigned char m_UartOkAckData[50];
//	//int m_UartOkAckDataCnt;
//		//m_UartCommand = _ttoi(str1);
//
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		str2 = str1;
//
//		str2.MakeUpper();
//		for(int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if(lpos  >= 0)
//			{			
//				
//				m_UartOkAckData[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos+4);
//				m_UartOkAckDataCnt = i+1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//	//	m_UartOkAckData = lFile.ReadHex(str1);
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		///str1 = m_FunctionParameter.Mid(lpos+1);		
//
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 
//
//		
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		if (lStringIn == 0)
//		UartCommandPcbSend();
//		m_PCB_CheckOK = 0;
//
//		//m_UartCommand();
//	}	
//	else if(m_FunctionName.Compare("set_main_noack") == 0)//uartcheck_noack(0x81 ,0x01 ,3000 ) 
//	{
//		if(m_FunctionParameter.Find("0") >= 0)
//		{
//			m_NoAckMainCom = 0;
//		}
//		else
//		{
//			m_NoAckMainCom = 1;
//		
//		}
//
//		m_FunctionType = TEST_SEQ_TYPE_MAIN_COM_NO_ACK_COMMAND;
//	}
//	else if(m_FunctionName.Compare("uartcheck_noack") == 0)//uartcheck_noack(0x81 ,0x01 ,3000 ) 
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_UART_NO_ACK_COMMAND;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		str1.MakeUpper();
//		CString str2;
//		str2 = str1;
//
//		for(int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if(lpos  >= 0)
//			{
//			//	str1.Find("0/X");
//				
//				m_UartCommand[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos+4);
//
//				m_UartCommandCnt = i+1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//	//		unsigned char m_UartCommand[50];
//	//int m_UartCommandCnt;
//	//unsigned char m_UartOkAckData[50];
//	//int m_UartOkAckDataCnt;
//		//m_UartCommand = _ttoi(str1);
//
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		str2 = str1;
//
//		str2.MakeUpper();
//		for(int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if(lpos  >= 0)
//			{			
//				
//				m_UartOkAckData[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos+4);
//				m_UartOkAckDataCnt = i+1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//	//	m_UartOkAckData = lFile.ReadHex(str1);
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		///str1 = m_FunctionParameter.Mid(lpos+1);		
//
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 
//
//		
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		if (lStringIn == 0)
//		UartCommandPcbSend();
//		m_PCB_CheckOK = 0;
//		
//		m_PCB_COM_PROCESS = COM_MODE_IDLE;
//		m_PCBComAck = COM_ACK_OK;
//
//		
//	}	
//	else if(m_FunctionName.Compare("checksum") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_SUM_COMMAND;
//
//		//lpos = m_FunctionParameter.Find(",");
//		//CString str1 = m_FunctionParameter.Left(lpos);
//		//str1.MakeUpper();
//		//CString str2;
//		//str2 = str1;
//
//		//for(int i = 0; i < 50; i++)
//		//{
//		//	lpos = str2.Find("0X");
//		//	if(lpos  >= 0)
//		//	{
//		//	//	str1.Find("0/X");
//		//		
//		//		m_UartCommand[i] = lFile.ReadHex(str2);
//		//		str2 = str2.Mid(lpos+4);
//
//		//		m_UartCommandCnt = i+1;
//		//	}
//		//	else
//		//	{
//		//		break;
//		//	}
//		//}
//
//	//		unsigned char m_UartCommand[50];
//	//int m_UartCommandCnt;
//	//unsigned char m_UartOkAckData[50];
//	//int m_UartOkAckDataCnt;
//		//m_UartCommand = _ttoi(str1);
//
//	//	lpos = m_FunctionParameter.Find(",");
//	//	m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//	//	lpos = m_FunctionParameter.Find(",");
//	//	str1 = m_FunctionParameter.Left(lpos);
//	//	str2 = str1;
//
//	//	str2.MakeUpper();
//	//	for(int i = 0; i < 50; i++)
//	//	{
//	//		lpos = str2.Find("0X");
//	//		if(lpos  >= 0)
//	//		{			
//	//			
//	//			m_UartOkAckData[i] = lFile.ReadHex(str2);
//	//			str2 = str2.Mid(lpos+4);
//	//			m_UartOkAckDataCnt = i+1;
//	//		}
//	//		else
//	//		{
//	//			break;
//	//		}
//	//	}
//
//	////	m_UartOkAckData = lFile.ReadHex(str1);
//	//	lpos = m_FunctionParameter.Find(",");
//	//	m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//	//	//m_FunctionParameter.Mid(lpos+1);
//	//	lpos = m_FunctionParameter.Find(",");
//	//	///str1 = m_FunctionParameter.Mid(lpos+1);		
//		m_UartCommand[0] = 0x2D;
//		m_UartCommandCnt = 1;
//		if(gTestSeqData.CheckSum[2] == 0)
//		{
//			m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
//			m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
//			m_UartOkAckDataCnt = 2;
//		}
//		else
//		{
//			m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
//			m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
//			m_UartOkAckData[2] = gTestSeqData.CheckSum[2];
//			m_UartOkAckData[3] = gTestSeqData.CheckSum[3];
//			m_UartOkAckDataCnt = 4;
//		}
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 
//
//		
//		
//		if(m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		if (lStringIn == 0)
//		UartCommandPcbSend();
//		m_PCB_CheckOK = 0;
//
//		//m_UartCommand();
//	}	
//	else if(m_FunctionName.Compare("check_led") == 0)// check_led(4,4,4,4,1000 )
//	{
//		//CFileControl lFile;
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		//m_FunctionType = TEST_SEQ_TYPE_CHECK_LED;
//
//		//lpos = m_FunctionParameter.Find(",");
//		//CString str1 = m_FunctionParameter.Left(lpos);
//		//int lledcnt =   _ttoi(str1);
//		//if(lledcnt == 1)
//		//	m_LEDOkAckData[0] = 0xF1;
//		//else if(lledcnt == 2)
//		//	m_LEDOkAckData[0] = 0xF3;
//		//else if(lledcnt == 3)
//		//	m_LEDOkAckData[0] = 0xF7;
//		//else if(lledcnt == 4)
//		//	m_LEDOkAckData[0] = 0xFF;
//		//else
//		//	m_LEDOkAckData[0] = 0xF0;
//		////m_UartCommand = _ttoi(str1);
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		//lledcnt =   _ttoi(str1);
//		//if(lledcnt == 1)
//		//	m_LEDOkAckData[1] = 0xF1;
//		//else if(lledcnt == 2)
//		//	m_LEDOkAckData[1] = 0xF3;
//		//else if(lledcnt == 3)
//		//	m_LEDOkAckData[1] = 0xF7;
//		//else if(lledcnt == 4)
//		//	m_LEDOkAckData[1] = 0xFF;
//		//else
//		//	m_LEDOkAckData[1] = 0xF0;
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		//lledcnt =   _ttoi(str1);
//		//if(lledcnt == 1)
//		//	m_LEDOkAckData[2] = 0xF1;
//		//else if(lledcnt == 2)
//		//	m_LEDOkAckData[2] = 0xF3;
//		//else if(lledcnt == 3)
//		//	m_LEDOkAckData[2] = 0xF7;
//		//else if(lledcnt == 4)
//		//	m_LEDOkAckData[2] = 0xFF;
//		//else
//		//	m_LEDOkAckData[2] = 0xF0;
//
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		//lledcnt =   _ttoi(str1);
//		//if(lledcnt == 1)
//		//	m_LEDOkAckData[3] = 0xF1;
//		//else if(lledcnt == 2)
//		//	m_LEDOkAckData[3] = 0xF3;
//		//else if(lledcnt == 3)
//		//	m_LEDOkAckData[3] = 0xF7;
//		//else if(lledcnt == 4)
//		//	m_LEDOkAckData[3] = 0xFF;
//		//else
//		//	m_LEDOkAckData[3] = 0xF0;
//
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//	
//		//m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
//		//
//		//if(m_CheckDelayTime <= 30)
//		//{
//		//	m_CheckDelayTime = 1000;
//		//}
//		//LEDReadSend();
//		//m_LED_CheckOK = 0;
//		////m_UartCommand();
//	}
//	else if(m_FunctionName.Compare("clear_led") == 0)// check_led(4,4,4,4,1000 )
//	{
//	//	CFileControl lFile;
//	//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//	//	m_FunctionType = TEST_SEQ_TYPE_CLEAR_LED;
//
//	//	
//	//
//	//	m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
//	//	
//	//	if(m_CheckDelayTime <= 30)
//	//	{
//	//		m_CheckDelayTime = 1000;
//	//	}
//	//	LEDClearSend();
//	////	m_LED_CheckOK = 0;
//	//	//m_UartCommand();
//	}	
//	else if(m_FunctionName.Compare("check_fan") == 0)// check_fan(1,1000 )
//	{
//		//CFileControl lFile;
//
//		//
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		//m_FunctionType = TEST_SEQ_TYPE_CHECK_FAN;
//
//		//lpos = m_FunctionParameter.Find(",");
//		//CString str1 = m_FunctionParameter.Left(lpos);
//		//int l_FanDiPort =   _ttoi(str1);
//
//		////if((l_FanDiPort > 0)&&(l_FanDiPort <= 4))
//		////{
//		////	m_FanDiPort = l_FanDiPort - 1;
//		////}
//		////else
//		//{
//		//	m_FanDiPort = 0;
//		//}
//		//m_LED_Up_DI_ReadData[m_FanDiPort] = 0;
//
//
//		//CString str2 = m_FunctionParameter.Mid(lpos+1);
//		//m_CheckDelayTime = _ttoi(str2);//check_led(4,4,4,4,1000 )		
//		//
//		//if(m_CheckDelayTime <= 30)
//		//{
//		//	m_CheckDelayTime = 1000;
//		//}
//		//LEDClearSend();
//	//	m_LED_CheckOK = 0;
//		//m_UartCommand();
//	}
//	else if((m_FunctionName.Compare("set_mic") == 0) || (m_FunctionName.Compare("set_mic1") == 0))
//	{
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_SET_MIC1;
//		m_MIC_Status = _ttoi(m_FunctionParameter);
//		
//		//if(m_CheckDelayTime <= 0)
//		{
//			m_CheckDelayTime = 2000;
//		}
//	}	//set_mic
//	else if(m_FunctionName.Compare("set_mic2") == 0)
//	{
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_SET_MIC2;
//		m_MIC_Status = _ttoi(m_FunctionParameter);
//		
//		//if(m_CheckDelayTime <= 0)
//		{
//			m_CheckDelayTime = 2000;
//		}
//	}	//set_mic
//	else if(m_FunctionName.Compare("set_freq") == 0)
//	{
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_SET_FREQ_OUT;
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_nSource = _ttoi(str1);
//		if((m_nSource >= 1)&&(m_nSource <= 10))
//		{
//			CString str2 = m_FunctionParameter.Mid(lpos+1);		
//			m_MIC_Status = _ttoi(str2);
//		}
//		else
//		{
//			str1 = "Syntex Error : ";
//			str1 += gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//			MessageDisplay(1, str1);
//
//			MessageBox(gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess], "Syntex Error");
//		
//		
//			m_TaskRun = TASK_RUN_IDLE;	
//			CycleTimeOn = 0;
//		}
//		
//	}	//s
//	else if(m_FunctionName.Compare("set_freq_on") == 0)
//	{
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_SET_FREQ_OUT_ON;
//			
//
//		CString str1 = m_FunctionParameter;
//		m_nSource = _ttoi(str1);
//		if((m_nSource >= 1)&&(m_nSource <= 10))
//		{
//		;
//		}
//		else
//		{
//			str1 = "Syntex Error : ";
//			str1 += gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//			MessageDisplay(1, str1);
//
//			MessageBox(gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess], "Syntex Error");
//		
//		
//			m_TaskRun = TASK_RUN_IDLE;	
//			CycleTimeOn = 0;
//		}
//		
//	}	//s
//	else if(m_FunctionName.Compare("set_freq_off") == 0)
//	{
//		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_SET_FREQ_OUT_OFF;
//			
//
//		CString str1 = m_FunctionParameter;
//		m_nSource = _ttoi(str1);
//		if((m_nSource >= 1)&&(m_nSource <= 10))
//		{
//		;
//		}
//		else
//		{
//			str1 = "Syntex Error : ";
//			str1 += gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//			MessageDisplay(1, str1);
//
//			MessageBox(gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess], "Syntex Error");
//		
//		
//			m_TaskRun = TASK_RUN_IDLE;	
//			CycleTimeOn = 0;
//		}
//		
//	}	//s
//	else  if(m_FunctionName.Compare("display_check_pass") == 0) //TEST_SEQ_TYPE_DISPLAY_CHECK_PASS			49 //display_check_pass(ref_cd_pass,ref_cd_fail, 50000)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_DISPLAY_CHECK_PASS;	
//	//	m_DisplayRetryCount = 0;
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_strRef_IMGfile = str1;
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//		lpos = str2.Find(",");	//str2.
//		str1 = str2.Left(lpos);
//		m_strFail_IMGfile = str1;
//
//		str1 =  str2.Mid(lpos+1);
//		
//	//	m_nChannel = _ttoi(str1);
//	//	m_nSource = _ttoi(str2);
//
//		m_CheckDelayTime = _ttoi(str1);
//		if(m_CheckDelayTime < 0)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else  if(m_FunctionName.Compare("display_check") == 0) //display_check(ref_uhd_4k, 5000)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_DISPLAY_CHECK;	
//	//	m_DisplayRetryCount = 0;
//		
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos+1);
//
//		m_strRef_IMGfile = str1;
//
//		m_CheckDelayTime = _ttoi(str2);
//		if(m_CheckDelayTime < 0)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if(m_FunctionName.Compare("set_video_channel") == 0)//set_video_channel(1)
//	{
//
////(1)	_T("HDMI"),
////(2)	_T("COMPONENT"),
////(3)	_T("CVBS"),
//
//
//		m_FunctionType = TEST_SEQ_TYPE_SET_VIDEO;
//
//		//int lpos, lendpos;
//		//lpos = m_FunctionParameter.Find(",");	
//
//		CString str1 = m_FunctionParameter;	
//		m_nSource = _ttoi(str1);
//		//if(m_CheckDelayTime[lSetIndex] < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}		
//	else if(m_FunctionName.Compare("audio_level") == 0)//#define 			42 //audio_level(1,100,1000)
//	{
//		
//		m_FunctionType = TEST_SEQ_TYPE_AUDIO_LEVEL_CHECK;
//
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");	
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_nChannel = _ttoi(str1);
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMin = 0;//_ttoi(str1);
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMax = 10000;//_ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		if(lpos > 0)
//		{
//		str1 = m_FunctionParameter.Left(lpos);
//		}
//		else
//		{
//			str1 = m_FunctionParameter;//.Left(lpos);
//		}
//		m_TmpVoltageMin = _ttoi(str1);
//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		//m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageMax = 20000;//_ttoi(str1);
//
//		//
//		//m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
//		////m_FunctionParameter.Mid(lpos+1);
//		//lpos = m_FunctionParameter.Find(",");
//		//str1 = m_FunctionParameter;//.Left(lpos);
//		//m_CheckDelayTime = _ttoi(str1);
//		//if(m_CheckDelayTime < 1000)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else
//	{
//		//Error
//		CString str1;
//		str1 = "Syntex Error : ";
//		str1 += gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//		MessageDisplay(1, str1);
//		if (m_TaskRun != TASK_RUN_IDLE)
//		{
//			MessageBox(lString, "Syntex Error");
//		}
//	//	MessageBox(gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess], "Syntex Error");
//		
//		
//		m_TaskRun = TASK_RUN_IDLE;	
//		CycleTimeOn = 0;
//	
//	}
//	m_OKcnt = 0;
//	SetTimeCheck(1);
//
//	if (m_FunctionType == TEST_SEQ_TYPE_END)
//	{
//		m_nCurrentStep = 2;
//	}
//	return  lFileError;
//}
//
//
//
//void CAcqVoltageSamples_IntClkDlg::RunFunction()
//{
//	static int sWaitCnt = 0;
//	static DWORD s_Start_Time  = 0;// 
//	if(sWaitCnt > 0)
//		sWaitCnt--;
//	//if(m_TEST_Result == 0)//NG
//	//{
//	//	TestFinish();
//	//	return;
//	//}
//
//	if (m_InterProcess == 0)
//	{
//
//	}
//	else
//	{
//	}
//
//
//	return;
//
//
//
//	switch(m_FunctionType)//m_nCurrentNumber
//	{
//	case TEST_SEQ_TYPE_DELAY:
//		if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			SetTimeCheck(1);
//			m_nCurrentStep = 2;
//			
//		}
//
//		break;
//
//	case  	TEST_SEQ_TYPE_POWER_ON_CHECK:
//		if(m_InterProcess == 0)
//		{
//			MessageDisplay(0, "TEST_SEQ_TYPE_POWER_ON_CHECK!!");		
//			
//			sWaitCnt = 30;
//			m_InterProcess = 1;
//			s_Start_Time = GetTickCount();
//			//sRepeatCount = 0;
//
//		}		
//		else if(m_InterProcess == 1)
//		{
//			if((m_USB1_CheckOK & 0x01)||(m_USB2_CheckOK & 0x01))
//			{
//				m_nCurrentStep = 2;
//				gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//			}
//			
//			else if(GetTimeCheck(1) > m_CheckDelayTime)
//			{
//			
//				gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//				m_nCurrentStep = 2;
//				
//				m_GMES_ErrorName = _T(" POWER ON ERROR: ");
//				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//					
//				m_Deisplay_ErrorName =  _T("POWER ON ERROR \r\n");// 频率  // 音量 // 版本// 频率 左右音量差异  // 音量 // 版本 // 命令 //检查 版本 回答
//				m_Deisplay_ErrorName += _T("POWER ON NG ");
//						
//				//str2.Format(_T("CH[%d] FREQ:%d[%d - %d] Hz"), i+1, (int)(m_Frequency[i]),m_FrequencyMin[i], m_FrequencyMax[i] );
//						
//				m_GMES_ErrorValue = "Power ON Fail ";//.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;
//				
//			}
//			else if((GetTickCount() - s_Start_Time) > 1000)
//			{
//				SendIR_Code("POWER", 0);
//				s_Start_Time = GetTickCount();
//			}
//			else
//			{
//				sWaitCnt = 30;
//			}
//		}
//		
//		
//		
//		break;
//
//
//	case  TEST_SEQ_TYPE_MP_KEY:
//		
//		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
//		SendIR_Code(m_strMP_Key, 0);
//		m_nCurrentStep = 2;
//	
//		break;
//		
//	case  TEST_SEQ_TYPE_MP_REPEAT_KEY:
//		
//		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
//		if(m_RepeatCount <= 5)
//		{
//			SendIR_Code(m_strMP_Key, 1);
//		}
//		else
//		{
//			SendIR_Code(m_strMP_Key, m_RepeatCount);
//		}
//
//		m_nCurrentStep = 2;
//	
//		break;
//	case  TEST_SEQ_TYPE_MP_REPEAT10_KEY:
//		
//		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
//		SendIR_Code(m_strMP_Key, 2);
//		m_nCurrentStep = 2;
//	
//		break;
//
//	case  TEST_SEQ_TYPE_PRE_REPEAT20_KEY:
//		
//		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
//		SendIR_Code(m_strMP_Key, 3);
//		m_nCurrentStep = 2;
//	
//		break;
//		
//	case   TEST_SEQ_TYPE_SET_AUDIO:
//
//		SetChannelDataSeq(m_nChannel, m_nSource);
//		m_nCurrentStep = 2;
//
//		break;
//
//	case   TEST_SEQ_TYPE_CHECK_AUDIO:
//		SetChannelDataRangeSeq(m_nChannel,m_TmpVoltageMin,m_TmpVoltageMax,m_TmpFrequencyMin,m_TmpFrequencyMax);
//		m_nCurrentStep = 2;
//
//		break;
//
//	case   TEST_SEQ_TYPE_AUDIO_LEVEL_CHECK:
//		SetChannelDataRangeSeq(m_nChannel,m_TmpVoltageMin,m_TmpVoltageMax,m_TmpFrequencyMin,m_TmpFrequencyMax);
//		m_nCurrentStep = 2;
//
//		break;
//
//	case   TEST_SEQ_TYPE_CHECK_AUDIO_WORK:
//	//	SetChannelDataRangeSeq(m_nChannel,m_TmpVoltageMin,m_TmpVoltageMax,m_TmpFrequencyMin,m_TmpFrequencyMax);
//		CheckOK();
//		
//		if((m_ChannelOK[0] == 1)
//		&& (m_ChannelOK[1] == 1)
//		&& (m_ChannelOK[2] == 1)
//		&& (m_ChannelOK[3] == 1)
//		&& (m_ChannelOK[4] == 1)
//		&& (m_ChannelOK[5] == 1))
//		{
//			m_TotalOK = 1;
//			m_OKcnt++;
//#ifdef __OK_CHECK_FAST_MODE__
//			if(m_OKcnt > 2)
//#else
//			if(m_OKcnt > 5)
//#endif
//			{
//				TestResultDisplay();
//				gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//				m_nCurrentStep = 2;
//
//				/*for(int i = 0; i< 6; i++)
//				m_graph[i].Plots.RemoveAll();*/
//
//				if(m_bCheckDisplayContinue == 0)
//				{
////					InitClearChannel();
//				}
//			}
//		}
//		else
//		{
//			m_TotalOK = 0;
//			m_OKcnt = 0;
//		}
//	
//
//		if(GetTimeCheck(1) > m_CheckDelayTime)
//		{	
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//			TestResultDisplay();
//			m_nCurrentStep = 2;
//			
//		//if( ((m_PPVoltage[i] >= m_RefVoltageMin[i])&&(m_PPVoltage[i] <= m_RefVoltageMax[i])) )
//		//if((m_Frequency[i] >= m_FrequencyMin[i]) &&	(m_Frequency[i] <= m_FrequencyMax[i]))
//
//			CString str1, str2;
//			CString strV1, strV2;
//			m_GMES_ErrorName = "";
//			for(int i = 0; i < 6; i++)
//			{
//	//			m_Deisplay_ErrorName;//
//	//CString m_Deisplay_ErrorDetail
//				if(m_ChannelOK[i] == 0)
//				{
//					if(m_FrequencyOK[i] == 0)
//					{
//						
//						
//						m_GMES_ErrorName = _T(" FREQUENCY ERROR: ");
//						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//					
//						m_Deisplay_ErrorName =  _T("FREQUENCY ERROR \r\n");// 频率  // 音量 // 版本// 频率 左右音量差异  // 音量 // 版本 // 命令 //检查 版本 回答
//						m_Deisplay_ErrorName += _T("FREQUENCY NG ");
//						
//						//str1 += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//						str2.Format(_T("CH[%d] FREQ:%d[%d - %d] Hz"), i+1, (int)(m_Frequency[i]),m_FrequencyMin[i], m_FrequencyMax[i] );
//						
//						m_GMES_ErrorValue = str2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;
//					}
//					else if(m_VoltageOK[i] == 0)
//					{						
//						strV1 = _T("VOLUME_ERROR : ");
//						m_GMES_ErrorName = _T(" VOLUME_ERROR :");
//						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//						m_Deisplay_ErrorName = _T("VOLUME_ERROR \r\n");
//						m_Deisplay_ErrorName += _T("VOLUME NG ");
//						
//						strV2.Format(_T("CH[%d] VOL:%d[%d - %d] mV"), i+1, (int)(m_PPVoltage[i]),(int)(m_RefVoltageMin[i]), (int)(m_RefVoltageMax[i]) );
//						
//						m_GMES_ErrorValue = strV2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//
//						//m_Deisplay_ErrorName = m_GMES_ErrorName;
//						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//m_Deisplay_ErrorName
//
//						
//					}
//					else if(m_BalanceOK[i] == 0)
//						{						
//						//strV1 = _T("BALANCE ERROR : ");
//						m_GMES_ErrorName = _T(" BALANCE ERROR: ");
//						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 频率 左右音量差异  // 音量 // 版本 // 命令 //检查 版本 回答
//						m_Deisplay_ErrorName = _T("BALANCE ERROR \r\n");
//
//					//	m_Deisplay_ErrorName += _T("左右音量差异 NG ");
//						m_Deisplay_ErrorName += _T("R/L BALANCE NG ");
//						
//						strV2.Format(_T("CH[%d] VOL:%d[%d - %d] mV"), i+1, (int)(m_PPVoltage[i]),(int)(m_PPVoltage[m_nBalanceChannel[i]]), (int)(m_RefVoltageMax[i]) );
//						
//						m_GMES_ErrorValue = strV2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//
//						//m_Deisplay_ErrorName = m_GMES_ErrorName;
//						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//m_Deisplay_ErrorName
//
//						
//					}
//					//break;
//				}
//				
//
//
//			}
//
//		}
//		break;
//
//	case   TEST_SEQ_TYPE_TEST_LAN:
//		if(m_LAN_CheckOK == 1)
//		{
//			m_nCurrentStep = 2;	
//			
//			//m_TEST_Result = 1;
//			m_cLb_Lan.put_Caption(_T("O K"));
//			m_cLb_Lan.put_BackColor(0x0000FF00);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//		//	m_cLbOkNg.put_Caption(_T("O K"));
//		//	m_cLbOkNg.put_BackColor(0x0000FF00);
//				
//		}
//		else if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			//m_TEST_Result = 0;
//			m_cLb_Lan.put_Caption(_T("N G"));
//			m_cLb_Lan.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						
//		//	m_cLbOkNg.put_Caption(_T("N G"));
//		//	m_cLbOkNg.put_BackColor(0x000000FF);
//					
//			m_nCurrentStep = 2;	
//			m_GMES_ErrorName = _T("LAN_ERROR : ");
//			m_Deisplay_ErrorName = _T("LAN_ERROR ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//			m_GMES_ErrorValue = _T("ERROR");
//			//m_Deisplay_ErrorName = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		}
//		break;	
//
//	case   TEST_SEQ_TYPE_TEST_USB1:
//		if(m_USB1_CheckOK	 == 7)
//		{
//			m_nCurrentStep = 2;	
//			//m_TEST_Result = 1;
//			m_cLb_Usb1.put_Caption(_T("O K"));
//			m_cLb_Usb1.put_BackColor(0x0000FF00);
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 0;
//			m_cLb_Usb1.put_Caption(_T("N G"));
//			m_cLb_Usb1.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						
//			//m_cLbOkNg.put_Caption(_T("N G"));
//			//m_cLbOkNg.put_BackColor(0x000000FF);	
//			
//			m_nCurrentStep = 2;	
//			//m_GMES_ErrorName = gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//			m_GMES_ErrorName = _T("USB1_ERROR ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//						
//			m_Deisplay_ErrorName = _T("USB1 ERROR \r\n");
//			m_Deisplay_ErrorName += _T("USB1 CHECK NG ");
//		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//			m_GMES_ErrorValue = _T("ERROR");
//				
//			//m_Deisplay_ErrorName = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		}
//		break;	
//
//	case   TEST_SEQ_TYPE_TEST_USB2:
//		if(m_USB2_CheckOK	 == 7)
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 1;
//			m_cLb_Usb2.put_Caption(_T("O K"));
//			m_cLb_Usb2.put_BackColor(0x0000FF00);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 0;
//			m_cLb_Usb2.put_Caption(_T("N G"));
//			m_cLb_Usb2.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						
//			//m_cLbOkNg.put_Caption(_T("N G"));
//			//m_cLbOkNg.put_BackColor(0x000000FF);	
//			
//			
//			m_GMES_ErrorName = _T("USB2_ERROR: ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//
//			m_Deisplay_ErrorName = _T("USB2 ERROR \r\n");
//			m_Deisplay_ErrorName += _T("USB2 CHECK NG ");
//			m_GMES_ErrorValue = _T("ERROR");
//
//			// = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		}
//		break;	
//
//	case   TEST_SEQ_TYPE_CHECK_CAMERA_OCR:
//		m_nCurrentStep = 2;
//		break;
//
//	case   TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE:
//		
//	
//		
//		if(m_Camera_CheckOK	 == 1)
//		{
//			m_nCurrentStep = 2;
//#ifndef __IMAGE_DEBUG__		
//			//m_cLb_Camera.put_Caption(_T("O K"));
//#endif
//			m_cLb_Camera.put_BackColor(0x0000FF00);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;						
//						
//		}
//		else if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			m_nCurrentStep = 2;
//#ifndef __IMAGE_DEBUG__		
//			//m_cLb_Camera.put_Caption(_T("N G"));
//#endif			
//			m_cLb_Camera.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;	
//					
//			//m_GMES_ErrorName = _T("IMAGE CHECK ERROR : ");
//			//m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//			m_GMES_ErrorName = _T("IMAGE CHECK ERROR  ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//			m_GMES_ErrorValue = _T("ERROR");
//		
//			m_Deisplay_ErrorName = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;
//		}
//		break;	
//	case   TEST_SEQ_TYPE_CHECK_UART_NO_ACK_COMMAND:
//			m_nCurrentStep = 2;
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result =1;
//			break;	
//	case   TEST_SEQ_TYPE_MAIN_COM_NO_ACK_COMMAND:
//			m_nCurrentStep = 2;
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result =1;
//			break;	
//	case   TEST_SEQ_TYPE_CHECK_UART_COMMAND:
//
//		if(m_PCB_CheckOK	 == 1)
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 1;
//		//	m_cLb_Usb2.put_Caption(_T("O K"));
//		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if((GetTimeCheck(1) > m_CheckDelayTime)||(m_PCB_CheckOK == 2))
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 0;
//		//	m_cLb_Usb2.put_Caption(_T("N G"));
//		//	m_cLb_Usb2.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						
//			//m_cLbOkNg.put_Caption(_T("N G"));
//			//m_cLbOkNg.put_BackColor(0x000000FF);	
//			
//			if(m_PCB_CheckOK == 2)
//			{
//				m_GMES_ErrorName = _T("USB ACK ERROR :");
//				m_Deisplay_ErrorName= _T("USB ACK ERROR \r\n");// 频率  // 音量 // 版本 // 命令 //检查 版本 回答
//				m_Deisplay_ErrorName += _T("USB ACK NG ");
//				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//				CString str;
//				m_GMES_ErrorValue = "";
//				for(int i = 0; i < m_UartOkAckDataCnt; i++)
//				{
//					m_GMES_ErrorValue += " ";
//					str.Format(_T("%02X"), m_UartREADData[i]);
//					m_GMES_ErrorName += str;
//				}
//				m_GMES_ErrorValue += "[";
//				for(int i = 0; i < m_UartOkAckDataCnt; i++)
//				{
//					str.Format(_T("%02X "), m_UartOkAckData[i]);
//				}
//				m_GMES_ErrorValue += "]";
//				//m_Deisplay_ErrorName = m_GMES_ErrorName;
//				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//
//			}
//			else
//			{
//				m_GMES_ErrorName = _T(" SET USB COMMAND NG ");
//				m_Deisplay_ErrorName = _T("SET USB COMMAND NG \r\n");
//				m_Deisplay_ErrorName += _T("SET USB COMMAND NG ");
//				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
//				m_GMES_ErrorValue = _T("ERROR");
//
//				//m_Deisplay_ErrorName = m_GMES_ErrorName;
//				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//			}
//			
//		}
//		break;	
//	case   TEST_SEQ_TYPE_CHECK_SUM_COMMAND:
//
//		
//		if(m_PCB_CheckOK	 == 1)
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 1;
//		//	m_cLb_Usb2.put_Caption(_T("O K"));
//		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if((GetTimeCheck(1) > m_CheckDelayTime)||(m_PCB_CheckOK == 2))
//		{
//			m_nCurrentStep = 2;
//			//m_TEST_Result = 0;
//		//	m_cLb_Usb2.put_Caption(_T("N G"));
//		//	m_cLb_Usb2.put_BackColor(0x000000FF);
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						
//			//m_cLbOkNg.put_Caption(_T("N G"));
//			//m_cLbOkNg.put_BackColor(0x000000FF);	
//			
//			//m_GMES_ErrorName = gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//			if(m_PCB_CheckOK == 2)
//			{
//				m_GMES_ErrorName = _T("CHECK SUM ERROR :");
//				m_Deisplay_ErrorName = _T("CHECK SUM ERROR\r\n");
//				m_Deisplay_ErrorName += _T("CHECK SUM NG");
//				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
//				CString str;
//				for(int i = 0; i < m_UartOkAckDataCnt; i++)
//				{
//					m_GMES_ErrorName += " ";
//					str.Format(_T("%02X"), m_UartREADData[i]);
//					m_GMES_ErrorName += str;
//				}
//				m_GMES_ErrorName += "[";
//				for(int i = 0; i < m_UartOkAckDataCnt; i++)
//				{
//					str.Format(_T("%02X "), m_UartOkAckData[i]);
//				}
//				m_GMES_ErrorName += "]";
//			
//			//	m_Deisplay_ErrorName = m_GMES_ErrorName;
//				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//				
//
//			}
//			else
//			{
//				m_GMES_ErrorName = _T("SET USB COMMAND ERROR ");
//				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
//				m_Deisplay_ErrorName = _T("SET USB COMMAND NG \r\n");
//				m_Deisplay_ErrorName += _T("SET USB COMMAND NG ");
//				m_GMES_ErrorValue = _T("ERROR");
//			//	m_Deisplay_ErrorName = m_GMES_ErrorName;
//				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//			}
//		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
//			
//		}
//		break;	
//			//m_nCurrentStep = 2;
//	case   TEST_SEQ_TYPE_CHECK_LED:
//		
//		//
//		//if(m_LED_CheckOK	 == 1)
//		//{
//		//	m_nCurrentStep = 2;
//
//		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//		//	//m_cLbOkNg.put_Caption(_T("O K"));
//		//	//m_cLbOkNg.put_BackColor(0x0000FF00);				
//		//				
//		//}
//		//else if(GetTimeCheck(1) > m_CheckDelayTime)
//		//{
//		//	m_nCurrentStep = 2;
//
//		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//		//			
//		//	m_GMES_ErrorName = _T("LED OUT ERROR :");
//		//	m_Deisplay_ErrorName = _T("LED OUT ERROR \r\n");
//		//	m_Deisplay_ErrorName += _T("LED TEST NG ");
//		//	m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
//		//	//CString str;
//		//	//str.Format(_T(),)
//
//		//	for(int j = 0; j < 4; j++)
//		//	{
//		//		for(int i = 0; i < 4; i++)
//		//		{
//		//			if((m_LEDReadData[j]>>i) & 0x01)
//		//			{
//		//				m_GMES_ErrorValue += "O";
//		//			}
//		//			else
//		//			{					
//		//				m_GMES_ErrorValue += "X";				
//		//			}
//		//		}
//		//		m_GMES_ErrorValue += "[";
//		//		for(int i = 0; i < 4; i++)
//		//		{
//		//			if((m_LEDOkAckData[j]>>i) & 0x01)
//		//			{
//		//				m_GMES_ErrorValue += "O";
//		//			}
//		//			else
//		//			{					
//		//				m_GMES_ErrorValue += "X";				
//		//			}
//
//		//		}
//		//		m_GMES_ErrorValue += "]  ";
//		//	}
//
//
//		//	//m_GMES_ErrorValue = _T("ERROR");
//		//	//m_Deisplay_ErrorName = m_GMES_ErrorName;
//		//	m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		//				
//
//		//}
//		//else
//		//{
//		//	if(sWaitCnt <= 0)
//		//	{
//		//		sWaitCnt = 10;
//		//		LEDReadSend();
//		//	}			
//		//}
//		break;	
//	case   TEST_SEQ_TYPE_CHECK_FAN:
//		
//		
//		if(m_LED_Up_DI_ReadData[m_FanDiPort] != 0)
//		{
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if(GetTimeCheck(1) > m_CheckDelayTime)
//		{
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//					
//			m_GMES_ErrorName = _T("FAN CHECK ERROR :");
//			m_Deisplay_ErrorName = _T("COOLING FAN ERROR \r\n");
//			m_Deisplay_ErrorName += _T("FAN TEST NG ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
//			//CString str;
//			//str.Format(_T(),)
//
//	
//			m_GMES_ErrorValue += "  ";
//			
//
//
//			//m_GMES_ErrorValue = _T("ERROR");
//			//m_Deisplay_ErrorName = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//						
//
//		}
//		else
//		{
//			if(sWaitCnt <= 0)
//			{
//				sWaitCnt = 10;
////				UP_DIReadSend();
//			}			
//		}
//		break;	
//
//			
//	case   TEST_SEQ_TYPE_MANUAL_CHECK:		
//		
//		if((m_LED_Up_DI_ReadData[1] != 0) || ( mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_OKCLICK))
//		{
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//			//m_cLbOkNg.put_Caption(_T("O K"));
//			//m_cLbOkNg.put_BackColor(0x0000FF00);				
//						
//		}
//		else if((m_LED_Up_DI_ReadData[2] != 0)
//			||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_TIMEOUT)
//			||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_CANCELCLICK))
//		{
//
//			mpDlgSimpleInform->m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;
//
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//					
//			m_GMES_ErrorName = _T("MANUAL CHECK ERROR :");
//			m_Deisplay_ErrorName = _T("USER CHECK ERROR \r\n");
//			m_Deisplay_ErrorName += _T("USER MANUAL TEST NG ");
//			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
//			//CString str;
//			//str.Format(_T(),)
//
//	
//			m_GMES_ErrorValue += "  ";
//			
//
//
//			//m_GMES_ErrorValue = _T("ERROR");
//			//m_Deisplay_ErrorName = m_GMES_ErrorName;
//			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//						
//
//		}
//		else
//		{
//			if(sWaitCnt <= 0)
//			{
//				sWaitCnt = 10;
//			//	UP_DIReadSend();
//			}			
//		}
//		break;	
//		
//	case   TEST_SEQ_TYPE_USER_MASSAGE:		
//		
//		if((m_LED_Up_DI_ReadData[1] != 0) || ( m_pUserMsgDlg->m_Close_Result == _CLOSE_DISPLAY_OKCLICK)||(m_pUserMsgDlg->m_bActivate == 0))
//		{
//		
//			if(m_pUserMsgDlg->m_bActivate == 1)
//			{
//				m_pUserMsgDlg->ShowWindow(SW_HIDE);
//			}
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;		
//						
//		}
//		//else if((m_LED_Up_DI_ReadData[2] != 0)
//		//	)
//		//	//||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_CANCELCLICK))
//		//{
//
//		//
//
//		//	m_nCurrentStep = 2;
//
//		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//		//			
//		//	m_GMES_ErrorName = _T("USER CHECK ERROR :");
//		//	m_Deisplay_ErrorName = _T("USER CHECK ERROR \r\n");
//		//	m_Deisplay_ErrorName += _T("USER MANUAL TEST NG ");
//		//	m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
//		//	//CString str;
//		//	//str.Format(_T(),)
//
//	
//		//	m_GMES_ErrorValue += "  ";
//		//	
//
//
//		//	//m_GMES_ErrorValue = _T("ERROR");
//		//	//m_Deisplay_ErrorName = m_GMES_ErrorName;
//		//	m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		//				
//
//		//}
//		else
//		{
//			if(sWaitCnt <= 0)
//			{
//				sWaitCnt = 10;
//			//	UP_DIReadSend();
//			}			
//		}
//		break;	
//		
//	case   TEST_SEQ_TYPE_WAIT_MASSAGE:		
//		if((m_LED_Up_DI_ReadData[1] != 0) || ( m_pUserMsgDlg->m_Close_Result == _CLOSE_DISPLAY_OKCLICK)||(m_pUserMsgDlg->m_bActivate == 0))
//		{
//		
//			if(m_pUserMsgDlg->m_bActivate == 1)
//			{
//				m_pUserMsgDlg->ShowWindow(SW_HIDE);
//			}
//			m_nCurrentStep = 2;
//
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;		
//						
//		}
//		//if((m_LED_Up_DI_ReadData[1] != 0) || (m_pUserMsgDlg->m_bYes == 1))
//		//{
//		//	m_nCurrentStep = 2;
//
//		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//
//		//	//m_cLbOkNg.put_Caption(_T("O K"));
//		//	//m_cLbOkNg.put_BackColor(0x0000FF00);				
//		//				
//		//}
//		//else if((m_LED_Up_DI_ReadData[2] != 0)
//		//	||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_TIMEOUT)
//		//	||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_CANCELCLICK)
//		//	||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_NGCLICK))
//		//{
//
//		//	mpDlgSimpleInform->m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;
//
//		//	m_nCurrentStep = 2;
//
//		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//		//			
//		//	m_GMES_ErrorName = _T("WAIT CHECK ERROR :");
//		//	m_Deisplay_ErrorName = _T("USER WAIT CHECK ERROR \r\n");
//		//	m_Deisplay_ErrorName += _T("USER WAIT TEST NG ");
//		//	m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
//		//	//CString str;
//		//	//str.Format(_T(),)
//
//	
//		//	m_GMES_ErrorValue += "  ";
//		//	
//
//
//		//	//m_GMES_ErrorValue = _T("ERROR");
//		//	//m_Deisplay_ErrorName = m_GMES_ErrorName;
//		//	m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
//		//				
//
//		//}
//		else
//		{
//			if(sWaitCnt <= 0)
//			{
//				sWaitCnt = 10;
//				//UP_DIReadSend();
//			}			
//		}
//		break;	
//	case   TEST_SEQ_TYPE_CLEAR_LED:			
//
//			m_nCurrentStep = 2;
//			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//		
//		break;	
//	case   TEST_SEQ_TYPE_SET_MIC1:
//	
//		m_MIC_Status = _ttoi(m_FunctionParameter);
//		if(m_MIC_Status != 1)
//			m_MIC_Status = 0;
//
//		SetFreqSend(4, m_MIC_Status);//MIC : 4(m_MIC_Status);
//		m_nCurrentStep = 2;
//		break;	
//
//
//	case   TEST_SEQ_TYPE_SET_MIC2:
//	
//		m_MIC_Status = _ttoi(m_FunctionParameter);
//		if(m_MIC_Status != 1)
//			m_MIC_Status = 0;
//
//		SetFreqSend(5, m_MIC_Status);//MIC : 4(m_MIC_Status);
//		m_nCurrentStep = 2;
//
//		
//		break;			
//
//
//	case   TEST_SEQ_TYPE_SET_FREQ_OUT:
//	
//		//m_MIC_Status = _ttoi(m_FunctionParameter);
//	//	if(m_MIC_Status != 1)
//	//		m_MIC_Status = 0;
//
//		SetFreqSend(m_nSource-1, m_MIC_Status);//MIC : 4(m_MIC_Status);
//		m_nCurrentStep = 2;
//
//		
//		break;			
//	
//	case   TEST_SEQ_TYPE_SET_FREQ_OUT_ON:
//	
//		//m_MIC_Status = _ttoi(m_FunctionParameter);
//	//	if(m_MIC_Status != 1)
//	//		m_MIC_Status = 0;
//
//		SetFreqSend(m_nSource-1, 1);//MIC : 4(m_MIC_Status);
//		m_nCurrentStep = 2;
//
//		
//		break;		
//
//	case   TEST_SEQ_TYPE_SET_FREQ_OUT_OFF:
//	
//		//m_MIC_Status = _ttoi(m_FunctionParameter);
//	//	if(m_MIC_Status != 1)
//	//		m_MIC_Status = 0;
//
//		SetFreqSend(m_nSource-1, 0);//MIC : 4(m_MIC_Status);
//		m_nCurrentStep = 2;
//
//		
//		break;			
//
//	
//	case  TEST_SEQ_TYPE_DISPLAY_CHECK:////display_check(m_strref_imgfile, 5000)
//
//		if(m_InterProcess == 0)
//		{			
//			MessageDisplay(0, "TEST_SEQ_TYPE_DISPLAY_CHECK!!");
//			CaptureControl(1);
//				
//		//	SetPortSelect(lSetIndex, 1);
//		//	SetHDMI_SW_Send(0, m_HdmiSel_Port[lIndex]);
//			sWaitCnt = 10;
//
//			m_InterProcess = 1;
//			//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK , CRect rect );
//			CRect rect(0,0,0,0) ;
//			SetRange(  0 , 0,  rect);
//			
//					
//		}
//		else if(m_InterProcess == 1)
//		{
//			m_InterProcess = 3;
////
//			//if(sWaitCnt[lSetIndex] == 0)
//			//{	
//			//	if((g_DisplayAudioPortNo == lSetIndex)||(g_DisplayAudioPortNo == _DISPLY_PORT_IDLE))
//			//	{
//			//		SelectPort(lSetIndex);
//			//	//	SetPortSelect(lSetIndex, 1);
//			//	//	SetHDMI_SW_Send(0, m_HdmiSel_Port[lIndex]);
//			//		sWaitCnt[lSetIndex] = 20;
//
//			//	//	m_InterProcess[lSetIndex] = 1;
//			////		SetRange(int lIndex, int lDisplayFlag,int lDisplayOK , CRect rect );
//			////		CRect rect(0,0,0,0) ;
//			////		SetRange(  0 , 0,  rect);
//			//		CaptureControl(1);
//			//							
//			//		m_InterProcess[lSetIndex] = 3;
//			//		sWaitCnt[lSetIndex] = 60;
//			//	}
//			//	else
//			//	{
//			//		sWaitCnt[lSetIndex] = 30;
//			//	}
//			//
//
//
//		
//			//	
//			//}		
//		}	
//		else if(m_InterProcess == 2)
//		{
//			if(sWaitCnt == 0)
//			{
//				m_InterProcess = 3;	
//			}
//		}	
//		else if(m_InterProcess == 3)
//		{
//			//if(sWaitCnt[lIndex] == 0)
//			//{
//			//	SetHDMI_SW_Send(2, m_HdmiSel_Port[lIndex]);
//				m_InterProcess = 4;
//			//	sWaitCnt[lIndex] = 60;
//			//}
//			//}
//				m_CheckErrorRetry = 0;
//				m_OKcnt = 0;
//		}
//		else if(m_InterProcess == 4)
//		{
//			if(sWaitCnt == 0)
//			{
//#if 0// def _CHECK_PASS_DEBUG__
//				m_nCurrentStep[lIndex] = 2;	
//#else 
//				CRect rectCD_Type;
//				rectCD_Type.left =250;
//				rectCD_Type.top = 70;
//				rectCD_Type.right =360;
//				rectCD_Type.bottom = 95;
//	
//				CRect rectPASS_Type;
//				rectPASS_Type.left =250;
//				rectPASS_Type.top = 70;
//				rectPASS_Type.right =360;
//				rectPASS_Type.bottom = 95;
//
////CRect rect;
////rect.left = 110;
////rect.top = 70;
////rect.right = 200;
////rect.bottom = 95;
//				//ScreenCapture();
//				if((ScreenCheck( m_strRef_IMGfile) == 0))//&&(CompareImage(lIndex, m_strRef_IMGfile[lIndex], rectPASS_Type) == 0))
//				{
//
//					m_OKcnt++;
//					if(m_OKcnt > 2)
//					{
//						m_nCurrentStep = 2;	
//						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//						CRect rect(0,0,0,0) ;
//						SetRange(  0 , 0,  rect);
//
//	/*					if(g_DisplayAudioPortNo == lSetIndex)
//						{
//							g_DisplayAudioPortNo = _DISPLY_PORT_IDLE;
//						}
//	*/
//					}
//					else
//					{
//						sWaitCnt = 10;
//					}		
//					
//				}
//				else
//				{
//					m_OKcnt = 0;
//					//m_nCurrentStep[lIndex] = 2;
//					//SetHDMI_SW_Send(0, m_HdmiSel_Port[lIndex]);	
//					m_CheckErrorRetry++;
//					sWaitCnt = 30;
//					if(m_CheckErrorRetry > 20)
//					{
//						m_InterProcess = 2;
//						m_CheckErrorRetry = 0;
//					}
//					else if(GetTimeCheck(1) > m_CheckDelayTime)
//					{
//						
///*						if(m_CheckErrorRetry[lSetIndex] > 10)
//						{*/								
//
//						//CaptureControl(0);
//							m_nCurrentStep = 2;	
//							gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//							
//							m_Deisplay_ErrorName = "DISPLAY_CHECK Time Out!!";								
//
//						//}
//						//else
//						//{
//						////	m_InterProcess[lIndex] = 0;
//						//	m_CheckErrorRetry[lSetIndex]++;
//						//}
//					}
//					else
//					{
//						sWaitCnt = 30;
//					}
//
//				}
//#endif
//				//m_nCurrentStep[lIndex] = 5;				
//			}
//		}
//			
//
//		break;
//	case  TEST_SEQ_TYPE_DISPLAY_CHECK_PASS://TEST_SEQ_TYPE_DISPLAY_CHECK_PASS			//display_check_pass(ref_cd_pass,ref_cd_fail, 50000)
//		
////#if 1
//		if(m_InterProcess == 0)
//		{			
//			MessageDisplay(0, "TEST_SEQ_TYPE_DISPLAY_CHECK_PASS!!");				
//				
//			//	SetHDMI_SW_Send(0, m_HdmiSel_Port[lIndex]);
//			sWaitCnt = 10;
//
//			m_InterProcess = 3;
//			//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK , CRect rect );
//			CRect rect(0,0,0,0) ;
//			SetRange( 0 , 0,  rect);
//
//			CaptureControl(1);
//				
//		}		
//		else if(m_InterProcess == 3)
//		{		
//				
//			if(sWaitCnt == 0)
//			{
//
//				CRect rectCD_Type;
//				rectCD_Type.left =250;
//				rectCD_Type.top = 70;
//				rectCD_Type.right =360;
//				rectCD_Type.bottom = 95;
//	
//				CRect rectPASS_Type;
//				rectPASS_Type.left =250;
//				rectPASS_Type.top = 70;
//				rectPASS_Type.right =360;
//				rectPASS_Type.bottom = 95;
//
//
//				ScreenCapture();
//				if((CompareImage( m_strRef_IMGfile, rectCD_Type) == 0))//&&(CompareImage(lIndex, m_strRef_IMGfile[lIndex], rectPASS_Type) == 0))
//				{
//					m_nCurrentStep = 2;
//				
//					gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
//					sWaitCnt = 5;
//					//CaptureControl(0);
//					ClearRange();
//				}
//				else if((CompareImage( m_strFail_IMGfile, rectCD_Type) == 0))//&&(CompareImage(lIndex, m_strRef_IMGfile[lIndex], rectPASS_Type) == 0))
//				{
//					m_nCurrentStep = 2;	
//					gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//					m_Deisplay_ErrorName = "DISPLAY_CHECK FAIL!!";
//				//	g_CurrentHDMI_SEL_LOCK = CONTROL_FREE;
//				//	StopCapture();
//					//CaptureControl(0);
//					ClearRange();
//				}
//				else
//				{
//					sWaitCnt = 20;
//						
//					if(GetTimeCheck(1) > m_CheckDelayTime)
//					{
//							
//						m_nCurrentStep = 2;	
//						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
//						m_Deisplay_ErrorName = "DISPLAY_CHECK Time Out!!";	
//						//CaptureControl(0);
//						ClearRange();
//					}
//				}
//				//m_nCurrentStep[lIndex] = 5;				
//			}
//		}
//	
//		break;
//
//		
//	case   TEST_SEQ_TYPE_SET_VIDEO://TEST_SEQ_TYPE_SET_VIDEO
//		if(m_nSource == 1)
//		{
//			SetInputVideo( m_nSource);
//		}
//		else if(m_nSource == 2)
//		{
//			SetInputVideo( m_nSource);
//		}
//		else if(m_nSource == 3)
//		{
//			SetInputVideo( m_nSource);
//		}
//		else
//		{
//			SetInputVideo( 1);
//		}
//		//SetPortHDMISelect(lSetIndex, 0);
//		m_nCurrentStep = 2;
//
//		break;
//
//	default:
//		m_nCurrentStep = 2;
//		
//		break;
//
//	}
//
//}


void CAcqVoltageSamples_IntClkDlg::CallPreProcess(int lCurrentProcess)
{
	//int		m_PreRunCounter;
	//int		m_PreTaskRun;
	//int		m_nPreCurrentNumber = 0;
	//m_nPreCurrentProcess
	if(gTestSeqData.PreTestCnt == 0)
	{
		m_PreTaskRun = TASK_RUN_IDLE;
	}

	
	switch(m_nPreCurrentStep)
	{
	case 0:
		PreSetFunction();
		m_nPreCurrentStep = 1;
		break;
	case 1:
		PreRunFunction();
		break;
	case 2:
		//GetFunction();m_nCurrentNumber

		m_nPreCurrentStep = 0;
		m_nPreCurrentProcess++;
		if( m_nPreCurrentProcess >= gTestSeqData.PreStepList[m_nPreCurrentNumber].nCount )
		{
			m_nPreCurrentNumber++;
			if(m_nPreCurrentNumber >= gTestSeqData.PreTestCnt)
			{
				m_PreTaskRun = TASK_RUN_IDLE;
			}
			else
			{
				m_nPreCurrentProcess = 0;
			}
		}
		break;
	default:
		break;
	}

	//m_OKcnt = 0;

	//SetTimeCheck(1);
	//if(gTestSeqData.PreTestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_DELAY)
	//{
	//		//m_WaitCnt = 0;		
	//	//	MessageDisplay(0, "WAIT DELAY TIME!!");
	//}
	//else if(gTestSeqData.PreTestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_MP_KEY)
	//{			
	//		//m_WaitCnt = 0;		
	//	//	MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
	//		SendPreIR_Code(gTestSeqData.PreTestProcess.aSeqData[lCurrentProcess].strMP_Key, 0);
	//}	
	//else if(gTestSeqData.PreTestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_MP_REPEAT_KEY)
	//{			
	//		//m_WaitCnt = 0;		
	//	//	MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
	//		SendPreIR_Code(gTestSeqData.PreTestProcess.aSeqData[lCurrentProcess].strMP_Key, 1);
	//}
	//else
	//{
	//	m_PreTaskRun = TASK_RUN_IDLE;
	//}
	//SetTimeCheck(2);
}
//
//CString		m_PreFunctionName;
//	CString		m_PreFunctionParameter;
//	int			m_PreFunctionType;
//	int			m_PreCheckDelayTime;
//	CString		m_PrestrMP_Key;

void CAcqVoltageSamples_IntClkDlg::PreSetFunction()//PreRunFunction
{
	CString lFunctionString;

	/*lFunctionString = gTestSeqData.PreStepList[m_nPreCurrentNumber].FunctionCommand[m_nPreCurrentProcess];
	int lpos, lendpos;
	lpos = lFunctionString.Find("(");
	lendpos = lFunctionString.Find(")");
	m_PreFunctionName = lFunctionString.Left(lpos);
	m_PreFunctionParameter = lFunctionString.Mid(lpos+1,lendpos);*/
	

	m_PreFunctionType = TEST_SEQ_TYPE_END;

	lFunctionString = gTestSeqData.PreStepList[m_nPreCurrentNumber].FunctionCommand[m_nPreCurrentProcess];
	int lpos, lendpos;
	lpos = lFunctionString.Find("(");
	lendpos = lFunctionString.Find(")");
	lFunctionString = lFunctionString.Left(lendpos);
	m_PreFunctionName = lFunctionString.Left(lpos);
	m_PreFunctionParameter = lFunctionString.Mid(lpos+1);

	if(m_PreFunctionName.Compare("delay") == 0)
	{
		m_PreFunctionType = TEST_SEQ_TYPE_DELAY;
		m_PreCheckDelayTime = _ttoi(m_PreFunctionParameter);
		if(m_PreCheckDelayTime < 0)
		{
			m_PreCheckDelayTime = 1000;
		}
		SetTimeCheck(2);


		
	}
	else if((m_PreFunctionName.Compare("remocon_out") == 0)||(m_PreFunctionName.Compare("remocon_out1") == 0))
	{
		m_PreFunctionType = TEST_SEQ_TYPE_MP_KEY;
		int lpos, lendpos;
		lpos = m_PreFunctionParameter.Find("\"");
		CString strtemp = m_PreFunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_PrestrMP_Key = strtemp;


		if(m_PreCheckDelayTime < 50)
		{
			m_PreCheckDelayTime = 1000;
		}
	}
	else if(m_PreFunctionName.Compare("remocon_out2") == 0)
	{
		m_PreFunctionType = TEST_SEQ_TYPE_PRE_KEY;
		int lpos, lendpos;
	/*	lpos = m_PreFunctionParameter.Find("\"");
		lendpos = m_PreFunctionParameter.Find("\"");

		CString strtemp = m_PreFunctionParameter.Mid(lpos+1,lendpos);
		m_strMP_Key = strtemp;*/
		
		lpos = m_PreFunctionParameter.Find("\"");
		CString strtemp = m_PreFunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_PrestrMP_Key = strtemp;
		if(m_PreCheckDelayTime < 50)
		{
			m_PreCheckDelayTime = 1000;
		}
	}
	else if(m_PreFunctionName.Compare("remocon_repeat") == 0)
	{
		m_PreFunctionType = TEST_SEQ_TYPE_MP_REPEAT_KEY;
		int lpos, lendpos;
		/*lpos = m_PreFunctionParameter.Find("\"");
		lendpos = m_PreFunctionParameter.Find("\"");

		CString strtemp = m_PreFunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_PreFunctionParameter.Find("\"");
		CString strtemp = m_PreFunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_PrestrMP_Key = strtemp;
		if(m_PreCheckDelayTime < 50)
		{
			m_PreCheckDelayTime = 1000;
		}
	}		
	else if(m_PreFunctionName.Compare("remocon_repeat10") == 0)
	{
		m_PreFunctionType = TEST_SEQ_TYPE_MP_REPEAT10_KEY;
		int lpos, lendpos;
		/*lpos = m_PreFunctionParameter.Find("\"");
		lendpos = m_PreFunctionParameter.Find("\"");

		CString strtemp = m_PreFunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_PreFunctionParameter.Find("\"");
		CString strtemp = m_PreFunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_PrestrMP_Key = strtemp;
		if(m_PreCheckDelayTime < 50)
		{
			m_PreCheckDelayTime = 1000;
		}
	}
	else if(m_PreFunctionName.Compare("remocon_repeat20") == 0)
	{
		m_PreFunctionType = TEST_SEQ_TYPE_PRE_REPEAT20_KEY;
		int lpos, lendpos;
		/*lpos = m_PreFunctionParameter.Find("\"");
		lendpos = m_PreFunctionParameter.Find("\"");

		CString strtemp = m_PreFunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_PreFunctionParameter.Find("\"");
		CString strtemp = m_PreFunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_PrestrMP_Key = strtemp;
		if(m_PreCheckDelayTime < 50)
		{
			m_PreCheckDelayTime = 1000;
		}
	}
	
	
	
	m_OKcnt = 0;
	SetTimeCheck(2);
}


//CString		m_PreFunctionName;
//	CString		m_PreFunctionParameter;
//	int			m_PreFunctionType;
//	int			m_PreCheckDelayTime;
//	CString		m_PrestrMP_Key;
void CAcqVoltageSamples_IntClkDlg::PreRunFunction()
{
	//if(m_TEST_Result == 0)//NG
	//{
	//	TestFinish();
	//	return;
	//}
	switch(m_PreFunctionType)
	{
	case TEST_SEQ_TYPE_DELAY:
		if(GetTimeCheck(2) > m_PreCheckDelayTime)
		{
			SetTimeCheck(2);
			m_nPreCurrentStep = 2;
		}
		
		break;

	case  TEST_SEQ_TYPE_PRE_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_PRE_KEY!!");
		SendPreIR_Code(m_PrestrMP_Key, 0);
		m_nPreCurrentStep = 2;
	
		break;
		
	case  TEST_SEQ_TYPE_PRE_REPEAT_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_PRE_REPEAT_KEY!!");
		SendPreIR_Code(m_PrestrMP_Key, 1);
		m_nPreCurrentStep = 2;
	
		break;


		
	case  TEST_SEQ_TYPE_PRE_REPEAT20_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_PRE_REPEAT_KEY!!");
		SendPreIR_Code(m_PrestrMP_Key, 3);
		m_nPreCurrentStep = 2;
	
		break;
	/*	
	case  TEST_SEQ_TYPE_MP_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_PRE_REPEAT_KEY!!");
		SendIR_Code(m_PrestrMP_Key, 0);
		m_nPreCurrentStep = 2;
	
		break;
	case  TEST_SEQ_TYPE_MP_REPEAT_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_PRE_REPEAT_KEY!!");
		SendIR_Code(m_PrestrMP_Key, 1);
		m_nPreCurrentStep = 2;
	
		break;
		#define 				2
#define TEST_SEQ_TYPE_PRE_KEY				3
#define TEST_SEQ_TYPE_TEST_2				4
#define TEST_SEQ_TYPE_TEST_3				5
#define TEST_SEQ_TYPE_MP_REPEAT_KEY			6
#define TEST_SEQ_TYPE_PRE_REPEAT_KEY		7
#define TEST_SEQ_TYPE_TEST_LAN				8
#define TEST_SEQ_TYPE_TEST_USB1				9
#define TEST_SEQ_TYPE_TEST_USB2				10
#define TEST_SEQ_TYPE_SET_AUDIO				11
#define TEST_SEQ_TYPE_CHECK_AUDIO			12
#define TEST_SEQ_TYPE_CHECK_CAMERA_OCR		13
#define TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE	14
#define TEST_SEQ_TYPE_CHECK_AUDIO_WORK		15
#define TEST_SEQ_TYPE_CHECK_UART_COMMAND	16
#define TEST_SEQ_TYPE_CLEAR_LED				17
#define TEST_SEQ_TYPE_CHECK_LED				18
#define TEST_SEQ_TYPE_SET_MIC1				19
#define TEST_SEQ_TYPE_SET_MIC2				20
#define TEST_SEQ_TYPE_MP_REPEAT10_KEY		21
#define TEST_SEQ_TYPE_PRE_REPEAT20_KEY		22*/
	default:
		m_nPreCurrentStep = 2;
		break;

	}
	//else if(gTestSeqData.TestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_MP_REPEAT_KEY)
	//{			
	//		m_WaitCnt = 0;		
	//		MessageDisplay(0, "TEST_SEQ_TYPE_MP_REPEAT_KEY!!");
	//		SendIR_Code(gTestSeqData.TestProcess.aSeqData[lCurrentProcess].strMP_Key, 1);
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_TEST_LAN)
	//{			
	//		m_WaitCnt = 0;		
	//		MessageDisplay(0, "TEST_SEQ_TYPE_LAN_TEST!!");
	//		m_cLbOkNg.put_Caption(_T("WAIT"));
	//		m_cLbOkNg.put_BackColor(0x0000FFFF);

	//		
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_TEST_USB1)
	//{			
	//		m_WaitCnt = 0;		
	//		MessageDisplay(0, "TEST_SEQ_TYPE_USB1_TEST!!");	
	//		m_cLbOkNg.put_Caption(_T("WAIT"));
	//		m_cLbOkNg.put_BackColor(0x0000FFFF);
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[lCurrentProcess].nSeqType == TEST_SEQ_TYPE_TEST_USB2)
	//{			
	//		m_WaitCnt = 0;		
	//		MessageDisplay(0, "TEST_SEQ_TYPE_USB2_TEST!!");	
	//		m_cLbOkNg.put_Caption(_T("WAIT"));
	//		m_cLbOkNg.put_BackColor(0x0000FFFF);
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
	//{
	//	SetChannelData(0);
	//	//InitChannel();	
	//	MessageDisplay(0, "First TEST !!");
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
	//{
	//	SetChannelData(1);
	//	InitChannel();	
	//	MessageDisplay(0, "Second TEST !!");
	//		
	//}	
	//else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
	//{
	//	SetChannelData(2);
	//	InitChannel();	
	//	MessageDisplay(0, "3'rd TEST !!");
	//		
	//}	
	//else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
	//{
	//	SetChannelData(3);
	//	InitChannel();	
	//	MessageDisplay(0, "4'th TEST !!");
	//		
	//}
	//else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_END)
	//{
	//	TestFinish();
	//}
	//else
	//{
	//	m_TaskRun = TASK_RUN_IDLE;
	//}
	//m_OKcnt = 0;

	//SetTimeCheck(1);
}

void CAcqVoltageSamples_IntClkDlg::ReadVolt(int lReadID1)
{
	//0x02CVR000000 s 0x03	
	
	int i ;


	BYTE lbuf[128]; 
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

	sprintf((char *)&lbuf[1], "CREADV_%02d", lReadID1);
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;

	
	SendData(lbuf, 13);
	m_ReadMIOComAck = COM_ACK_WAIT;

}


void CAcqVoltageSamples_IntClkDlg::ReadSMIO(int lReadID1)
{
	//0x02CDR000000 s 0x03	
	
	int i ;


	BYTE lbuf[128]; 
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

//	sprintf((char *)&lbuf[1], "CREADI_%02d000000 s 0x03	", lReadID1);
	sprintf((char *)&lbuf[1], "CREADI_99000000 s 0x03	", lReadID1);
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	
	SendData(lbuf, 13);
	m_ReadMIOComAck = COM_ACK_WAIT;

}

void CAcqVoltageSamples_IntClkDlg::WriteSM_Out(int lReadID1)
{
	//0x02CDR000000 s 0x03	

	int i;


	BYTE lbuf[128];
	BYTE lOutbuf[16];
	memset(lOutbuf, 0, sizeof(lOutbuf));
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;
	if (lReadID1 == 99)
	{
		for (int i = 0; i < 8; i++)
		{
			if (gDoData[i] == 1)
			{
				lOutbuf[0] |= (0x01 << i);
			}
			if (gDoData[i + 8] == 1)
			{
				lOutbuf[1] |= (0x01 << i);
			}
			if (gDoData[i + 16] == 1)
			{
				lOutbuf[2] |= (0x01 << i);
			}
		}

		sprintf((char *)&lbuf[1], "CWO%02d%02X%02X%02XO000000 s 0x03	", lReadID1, lOutbuf[0], lOutbuf[1], lOutbuf[2]);
	}
	else if ((lReadID1 >= 0) && (lReadID1 < 24))
	{
		if (gDoData[lReadID1])
		{
			sprintf((char *)&lbuf[1], "CWO%02d111111 s 0x03	", lReadID1);
		}
		else
		{
			sprintf((char *)&lbuf[1], "CWO%02d000000 s 0x03	", lReadID1);
		}
	}
	else
	{
		return;
	}

	lbuf[12] = 0x03;
	lbuf[13] = 0x0d;
	lbuf[14] = 0x0a;

	SendData(lbuf, 15);
	m_ReadMIOComAck = COM_ACK_WAIT;

}

BOOL CAcqVoltageSamples_IntClkDlg::SendIR_Code(CString lCodeString,  int lRepeat)
{
	int lRmtCodeIndex = 0;

	int i ;

	for( i = 0; i < m_RemoconModel.m_Cnt; i++)
	{
		if(m_RemoconModel.Data[i].m_Name.Compare(lCodeString.GetBuffer()) == 0)
		{
			
			break;
		}
	}
	lRmtCodeIndex = i;

	BYTE lbuf[128]; 
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

	//if(lRepeat == 1)
	//{
	//	sprintf((char *)&lbuf[1], "CRSNE");
	//}
	//else if(lRepeat == 2)
	//{
	//	sprintf((char *)&lbuf[1], "CRSN2");
	//}
	//else if(lRepeat > 5)
	//{
	//	sprintf((char *)&lbuf[1], "CRS%02d", lRepeat);
	//}
	//else 
	{
		sprintf((char *)&lbuf[1], "CRSND");
	}

	if(lRmtCodeIndex < m_RemoconModel.m_Cnt)
	{
		if(CurrentSet->nRemoteType == 1)//gTestSeqData.nRemoconSigType == 0)
		{
			str = _T("IR");
		}
		else
		{
			str = _T("CA");
		}
		str += m_RemoconModel.Data[lRmtCodeIndex].m_Company;

		str += m_RemoconModel.Data[lRmtCodeIndex].m_Code;

		sprintf((char *)&lbuf[6], str.GetBuffer());
		int len = str.GetLength() + 6;
		if(len < 18)
		{
			for(int i = len; i < 18; i++)
			{
				lbuf[i] = 0x20;
			}
		}
		
		lbuf[18] = 0x03;
		lbuf[19] = 0x0d;
		lbuf[20] = 0x0a;
		SendData(lbuf, 21);

		

		 MessageDisplay(2, "IR CODE Send!!");

		
		 CString Logstr;
		 Logstr = "Remote : ";
		 Logstr += m_RemoconModel.Data[i].m_Name;
		 Logstr += "[" ;
		 Logstr += m_RemoconModel.Data[i].m_Company;
		 Logstr += m_RemoconModel.Data[i].m_Code;
		 Logstr += "]" ;

		 AddProcessLog(Logstr);
		 return 1;
	}
	else
	{
		//MessageBox("Send IR CODE FAIL!!");
		MessageDisplay(1, "Send IR CODE FAIL!!");
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
		m_Deisplay_ErrorName = "Send IR CODE FAIL!! ";//m_GMES_ErrorName;lCodeString
		m_Deisplay_ErrorName += lCodeString;
		m_Deisplay_ErrorDetail= lCodeString;
//	mpDlgResult->m_DetailMessage = m_Deisplay_ErrorDetail;//m_GMES_ErrorValue;
		return 0;
	}

}
void CAcqVoltageSamples_IntClkDlg::SendPreIR_Code(CString lCodeString, int lRepeat)
{
	int lRmtCodeIndex = 0;

	int i ;

	for( i = 0; i < m_RemoconModel.m_Cnt; i++)
	{
		if(m_RemoconModel.Data[i].m_Name.Compare(lCodeString.GetBuffer()) == 0)
		{
			
			break;
		}
	}
	if(m_RemoconModel.m_Cnt == i)
	{
		return;
	}
	else
	{
		lRmtCodeIndex = i;
	}

	BYTE lbuf[128]; 
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

	if(lRepeat == 1)
	{
		sprintf((char *)&lbuf[1], "CRSNR");
		MessageDisplay(2, "PRE IR CODE Repeat Send!!");
	}
	else if((lRepeat == 2)||(lRepeat == 3))
	{
		sprintf((char *)&lbuf[1], "CRSN3");
		MessageDisplay(2, "PRE IR CODE REPEAT Send!!");
	}
	else if(lRepeat > 5)
	{
		sprintf((char *)&lbuf[1], "CRF%02d", lRepeat);
	}	
	else
	{
		sprintf((char *)&lbuf[1], "CRSNF");
		MessageDisplay(2, "PRE IR CODE Send!!");
	}

	if(lRmtCodeIndex < m_RemoconModel.m_Cnt)
	{
		if (CurrentSet->nRemoteType == 1)//(gTestSeqData.nRemoconSigType == 0)
		{
			str = _T("IR");
		}
		else
		{
			str = _T("CA");
		}
		str += m_RemoconModel.Data[lRmtCodeIndex].m_Company;

		str += m_RemoconModel.Data[lRmtCodeIndex].m_Code;

		sprintf((char *)&lbuf[6], str.GetBuffer());
		int len = str.GetLength() + 6;
		if(len < 18)
		{
			for(int i = len; i < 18; i++)
			{
				lbuf[i] = 0x20;
			}
		}
		
		lbuf[18] = 0x03;
		lbuf[19] = 0x0d;
		lbuf[20] = 0x0a;
		SendData(lbuf, 21);
		

		 CString Logstr;
		 Logstr = "Remote : ";
		 Logstr += m_RemoconModel.Data[i].m_Name;
		 Logstr += "[" ;
		 Logstr += m_RemoconModel.Data[i].m_Company;
		 Logstr += m_RemoconModel.Data[i].m_Code;
		 Logstr += "]" ;

		 AddProcessLog(Logstr);
		 

	}
	else
	{
		//MessageBox("Send IR CODE FAIL!!");
		MessageDisplay(1, "Send PRE IR CODE FAIL!!");
	}
}

void CAcqVoltageSamples_IntClkDlg::SendAudioSel(int lAudio)
{
	int lRmtCodeIndex = 0;
	int i;
	
	BYTE lbuf[128];
	int lcnt;
	CString str;
	if(lAudio >= 9) // (lAudio >= 3) &&(lAudio <= 6))
	{
		lAudio = 9;
		m_SelectAudio = _AUDIO_SELECT_SPK;//_AUDIO_SELECT_NON
	}
	else if(lAudio < 9)
	{
		lAudio = 1;
		m_SelectAudio = _AUDIO_SELECT_AUX;
	}
	else
	{
		lAudio = 99;
		m_SelectAudio = _AUDIO_SELECT_NON;
	}

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

	
	sprintf((char *)&lbuf[1], "CA_SEL_%02d", lAudio);
	//MessageDisplay(2, "PRE IR CODE Repeat Send!!");
	

	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	
#if 0
	SendData(lbuf, 13);
#else
	SendData(lbuf, 13, COM_ID_HDMI_SC_PORT);
#endif

	
}

void CAcqVoltageSamples_IntClkDlg::SendVideoSel(int lVideo)
{
	int lRmtCodeIndex = 0;
	int i;

	BYTE lbuf[128];
	int lcnt;
	CString str;
	if(lVideo != 1)
		lVideo = 2;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;


	sprintf((char *)&lbuf[1], "CV_SEL_%02d", lVideo);
	//MessageDisplay(2, "PRE IR CODE Repeat Send!!");


	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;

#if 0
	SendData(lbuf, 13);
#else
	SendData(lbuf, 13, COM_ID_HDMI_SC_PORT);
#endif
	
}


void CAcqVoltageSamples_IntClkDlg::UartCommandPcbSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;

	//int lType = 0x01;//m_ComboPcbType.GetCurSel();
	CString StrTmp;
	CString StrMsg;
	//GetDlgItemText(IDC_EDIT_PCB_COMMAND,Str);

	

	lbuf[0] = 0xAA;
	lbuf[1] = m_UartCommandCnt + 2;//0x03;
//	sprintf(lbuf,"PCB TYPE= %d\n", gTestSeqData.nComPcbType);// m_cComboModelPcbType
	if((CurrentSet->nChipType >= 1)&&(CurrentSet->nChipType <= 3))//if((gTestSeqData.nComPcbType >= 0)&&(gTestSeqData.nComPcbType < 3))
	{
		lbuf[2] =   CurrentSet->nChipType;
	}
	else
	{
		CurrentSet->nChipType = 1;
		lbuf[2] =  CurrentSet->nChipType;
	}
	for(int i = 0; i < m_UartCommandCnt; i++)
	{
		lbuf[3+i] = m_UartCommand[i] ;
	}



	unsigned char lCheckSum = 0;
	for(int i = 0; i < m_UartCommandCnt +3; i++)
	{
		lCheckSum ^= lbuf[i];
	}
	lbuf[m_UartCommandCnt +3] = lCheckSum;

	m_SendCntPCB = m_UartCommandCnt +4;
	memcpy(m_SendBufPCB, lbuf, m_SendCntPCB); 	
	m_SendCntPCB = m_UartCommandCnt +4;
	
	ComPCBSend();
	if (m_ComPortPCB.mPort_Opened)
	{		
		StrMsg = ">>";
		for (int i = 0; i < m_SendCntPCB; i++)
		{
			StrTmp.Format(_T("%02X "), m_SendBufPCB[i]);
			StrMsg += StrTmp;
		}
		ComLog_AddString(StrMsg);
	}

	m_PCB_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_PCBComAck =COM_ACK_WAIT;
	m_PCBWaitCnt = 0;
	m_PCBResendCnt = 0;
	if(m_SendBufPCB[3] == 0xc1)
		m_WaitPCB_Ack_Limit = 600;
	else
		m_WaitPCB_Ack_Limit = 200;
	SetTimeCheck(_CHECK_TIME_PCB_COM_ID);
	m_CheckPCB_Com_DelayTime = 2000;

	MessageDisplay(2, "Command Send!");
}

//
//void CAcqVoltageSamples_IntClkDlg::ComLedRead()
//{
//	if(g_SetComOnlyMode == 1)
//	{
//		return;
//	}
//	//SendData(m_SendBuf, m_SendCnt);
//	//	void ComSend(BYTE lbuf, int lcnt);
//	if(m_ComPortLED.mPort_Opened)
//	{
//		
//		m_ComPortLED.WriteToPort(m_SendBufLED, m_SendCntLED);
//	}
//	else
//	{
//		OpenComportLED();
//		//MessageBox(_T("Com Port Not Opened !!"));
//		if(m_ComPortLED.mPort_Opened)
//		{
//			
//			m_ComPortLED.WriteToPort(m_SendBufLED, m_SendCntLED);
//		}
//	}
//
//	m_RecvCntLED = 0;
//}
//void CAcqVoltageSamples_IntClkDlg::LEDReadSend()
//{
//	if(g_SetComOnlyMode == 1)
//	{
//		return;
//	}
//	BYTE lbuf[128]; 
//	//int lcnt;
//	//UINT m_EditFreq1;
//
//	lbuf[0] = 0x02;	
//	
//	sprintf((char *)&lbuf[1], "CCHECKLED");
//  //sprintf((char *)&lbuf[1], "CMAC_READ");
//	
//	
//	lbuf[10] = 0x03;
//	lbuf[11] = 0x0d;
//	lbuf[12] = 0x0a;
//	
//
//	memcpy(m_SendBufLED, lbuf, 13); 	
//	m_SendCntLED = 13;
//
//	ComLedRead();
//
//	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
//	m_LEDComAck =COM_ACK_WAIT;
//	m_LEDWaitCnt = 0;
//	m_LEDResendCnt = 0;
//
//	//	int m_LED_COM_PROCESS;
//	//int m_LEDComAck;
//	//int m_LEDWaitCnt;
//	//int m_LEDResendCnt;
//	MessageDisplay(2, "LED Read!");
//}
//void CAcqVoltageSamples_IntClkDlg::UP_DIReadSend()
//{
//	if(g_SetComOnlyMode == 1)
//	{
//		return;
//	}
//	BYTE lbuf[128]; 
//	//int lcnt;
//	//UINT m_EditFreq1;
//
//	lbuf[0] = 0x02;	
//	
//	sprintf((char *)&lbuf[1], "CCHECKDIN");
//  //sprintf((char *)&lbuf[1], "CMAC_READ");
//	
//	
//	lbuf[10] = 0x03;
//	lbuf[11] = 0x0d;
//	lbuf[12] = 0x0a;
//	
//
//	memcpy(m_SendBufLED, lbuf, 13); 	
//	m_SendCntLED = 13;
//
////	ComLedRead();
//
//	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
//	m_LEDComAck =COM_ACK_WAIT;
//	m_LEDWaitCnt = 0;
//	m_LEDResendCnt = 0;
//
//	//	int m_LED_COM_PROCESS;
//	//int m_LEDComAck;
//	//int m_LEDWaitCnt;
//	//int m_LEDResendCnt;
//	MessageDisplay(2, "UP DI Read!");
//}
//void CAcqVoltageSamples_IntClkDlg::LEDClearSend()
//{
//	if(g_SetComOnlyMode == 1)
//	{
//		return;
//	}
//	BYTE lbuf[128]; 
//	//int lcnt;
//	//UINT m_EditFreq1;
//
//	lbuf[0] = 0x02;	
//	
//	sprintf((char *)&lbuf[1], "CCLEARLED");
//  //sprintf((char *)&lbuf[1], "CMAC_READ");
//	
//	
//	lbuf[10] = 0x03;
//	lbuf[11] = 0x0d;
//	lbuf[12] = 0x0a;
//	
//
//	memcpy(m_SendBufLED, lbuf, 13); 	
//	m_SendCntLED = 13;
//
//	ComLedRead();
//
//	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
//	m_LEDComAck =COM_ACK_WAIT;
//	m_LEDWaitCnt = 0;
//	m_LEDResendCnt = 0;
//
//	//	int m_LED_COM_PROCESS;
//	//int m_LEDComAck;
//	//int m_LEDWaitCnt;
//	//int m_LEDResendCnt;
//	MessageDisplay(2, "LED Clear!");
//}

//SetMic
void CAcqVoltageSamples_IntClkDlg::SetFreqSend(UINT lPort, UINT lFreq )//MIC : 4
{
	if(g_SetComOnlyMode == 1)
	{
		return;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	CString str;
	//UINT m_EditFreq1;
	

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	if(lFreq == 0)
	{
		sprintf((char *)&lbuf[1], "CFREQ%02d000       ", lPort);
	}
	else if(lFreq == 1)
	{
		sprintf((char *)&lbuf[1], "CFREQ%02d001       ", lPort);
	//	CurrentSet->nAudioGenFreq[lPort]
	}
	else
	{
		sprintf((char *)&lbuf[1], "CFREQ%02d%03d       ", lPort, lFreq/10);
	}
	
	lbuf[18] = 0x03;
	lbuf[19] = 0x0d;
	lbuf[20] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	SendData(lbuf, 21, COM_ID_AUDIO_PORT);	

}

BOOL CAcqVoltageSamples_IntClkDlg::GetRmtCodeList(CString lRmtFile)//gTestSeqData.strRemoconFileName;
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	FILE *m_fp;
	CString str;
	CString Filename;
	char lbuf[1024];
	char lTemp_Company[64];
	char lTemp_Code[64];
	char lTemp_Repeat[64];
	char lTemp_Name[64];
	char lTemp_Discription[129];

	

	//str = PATH_BASE_DIR;
	//str += _T("\\Remote\\");
	str = lRmtFile;//gTestSeqData.strRemoconFileName;
	
	// 파일경로 가져오기    
	 
	Filename = str;
		
	fopen_s(&m_fp, (LPCSTR)Filename, "r");
	if(m_fp)
	{
		m_RemoconModel.m_Cnt = 0;
		//memset(&m_RemoconModel, 0, sizeof(Recomon_ModelT));
		while(fgets(lbuf, 1024, m_fp) != NULL) 
		{
			if(lbuf[0] == '[')
			{
				continue;
			}
			if(strlen(lbuf) < 16)
			{
				break;
			}
			sscanf_s(lbuf, "%s %s %s %s", lTemp_Company,32, lTemp_Code,32,lTemp_Repeat,32, lTemp_Name,32);
			if(lTemp_Company[strlen(lTemp_Company)-1] == ',')
			{
				lTemp_Company[strlen(lTemp_Company)-1] = 0 ;
			}
				
			if(lTemp_Code[strlen(lTemp_Code)-1] == ',')
			{
				lTemp_Code[strlen(lTemp_Code)-1] = 0 ;
			}
				
			if(lTemp_Repeat[strlen(lTemp_Repeat)-1] == ',')
			{
				lTemp_Repeat[strlen(lTemp_Repeat)-1] = 0; 
			}

			if(lTemp_Name[strlen(lTemp_Name)-1] == ',')
			{
				lTemp_Name[strlen(lTemp_Name)-1] = 0;
			}

			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Company.Format(_T("%s"),lTemp_Company);
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Code.Format(_T("%s"),lTemp_Code); 
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Repeat = atoi(lTemp_Repeat);
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Name.Format(_T("%s"),lTemp_Name); 
			m_RemoconModel.m_Cnt++;		
			if(m_RemoconModel.m_Cnt >= 200)
			{
				break;
			}
		}
					

		fclose(m_fp);	
		//SetDlgItemText(IDC_STATIC_RMT_FILE, Filename);
		//for(int id = 0; id < 12; id++)
		//{
		//	m_cComboRmTest[id].ResetContent();
		//	for(int i = 0; i < m_RemoconModel.m_Cnt; i++)
		//	{
		//		str = m_RemoconModel.Data[i].m_Company;
		//		str += _T(" : "); 
		//		str += m_RemoconModel.Data[i].m_Name;
		//		m_cComboRmTest[id].AddString(str);
		//	}
		//	if(m_RemoconModel.m_Cnt > id)
		//	{
		//		m_cComboRmTest[id].SetCurSel(id);
		//	}
		//	else
		//	{
		//		m_cComboRmTest[id].SetCurSel(0);
		//	}
		//}

		return 1;
	} 
	else
	{
		return 0;
	}
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedStopButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_TaskRun = false;
	m_TaskRun = TASK_RUN_IDLE;
	//m_startButton.EnableWindow(true);
	CycleTimeOn = 0;
	//TestFinish();///test
	
	if(m_pUserMsgDlg->m_bActivate == 1)
	{
		m_pUserMsgDlg->ShowWindow(SW_HIDE);
	}
	gbManualRefMode = 0;

}

void CAcqVoltageSamples_IntClkDlg::CleanUpIfNecessary()
{
	for(int i = 0; i < 16; i++)
	{
		delete m_reader[i].release();
		delete m_task[i].release();
	}
}

void CAcqVoltageSamples_IntClkDlg::RemoveEventHandler()
{
	for(int i = 0; i < 16; i++)
	{
		if (m_reader[i].get())
		{
			// Remove our event handler
			while(!m_reader[i]->RemoveAllEventHandlers())
			{
				::Sleep(100);

				MSG msg;
				while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}

void CAcqVoltageSamples_IntClkDlg::OnCancel()
{
//	gbShutdown = true;
	Sleep(200);
    ShowWindow(SW_HIDE);
    RemoveEventHandler();
	for(int i = 0; i < 16; i++)
	{
		if (m_task[i].get() != NULL)
		{
			m_task[i]->Control(DAQmxTaskAbort);
		}
	}
    CleanUpIfNecessary();

//	g_MesDb.Close();

	if (mpDlgResult != NULL)
	{
		delete mpDlgResult;
		mpDlgResult = NULL;
	}

	if (mpDlgBarcode != NULL)
	{
		delete mpDlgBarcode;
		mpDlgBarcode = NULL;
	}

	if (mpDlgSimpleInform != NULL)
	{
		delete mpDlgSimpleInform;
		mpDlgSimpleInform = NULL;
	}

    CDialog::OnCancel();
}

/*

0 : HDMI_ANA_AUD_OUT_R
1 : HDMI_ANA_AUD_OUT_L
2 : DIG_2_ANA_AUD_R
3 : DIG_2_ANA_AUD_L
4 : 7.1_AUDIO_OUT_R1
5 : 7.1_AUDIO_OUT_L1
6 : 7.1_AUDIO_OUT_R2
7 : 7.1_AUDIO_OUT_L2
8 : 7.1_AUDIO_OUT_R3
9 : 7.1_AUDIO_OUT_L3
10 : 7.1_AUDIO_OUT_R4
11 : 7.1_AUDIO_OUT_L4
12 : ANA_AUDIO_OUT_R
13 : ANA_AUDIO_OUT_L
14 : P_ANA_AUDIO_OUT_R
15 : P_ANA_AUDIO_OUT_L
16 : P_ANA_AUDIO_OUT_R
17 : P_ANA_AUDIO_OUT_L

*/

void CAcqVoltageSamples_IntClkDlg::CheckDigitalPort()
{
	int lDigtalFound = 0;
	TestPort_T lPortData;
	for(int i = 0; i < 20; i ++)
	{
		if(lDigtalFound)
			break;
		
	}

	//SetDigitalPortSelect(m_DigitalPort, 1);
}

void CAcqVoltageSamples_IntClkDlg::SetDigitalPortSelect(int lDigSel, int lRefresh)
{
	//if(lRefresh)
	//{
	//	m_DigitalPort_Save = lDigSel;
	//}
	//else if(m_DigitalPort_Save == lDigSel)
	//{
	//	return;
	//}

	//BYTE lbuf[128]; 
	//int lcnt;
	//CString str;
	////UINT m_EditFreq1;
	//UpdateData();

	//lbuf[0] = 0x02;
	//
	////sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	//sprintf((char *)&lbuf[1], "CA_SEL_%02d", lDigSel);
	//
	//lbuf[10] = 0x03;
	//lbuf[11] = 0x0d;
	//lbuf[12] = 0x0a;
	////ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	//SendData(lbuf, 13);
	
}


void CAcqVoltageSamples_IntClkDlg::SetChannelData(int lTestNumber)
{
	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;
			
			m_NameLabel[i].put_Caption("COM MODE");
			

		}
		return;
	}
	CString lStrName[16] = {
		_T("HDMI_R"),_T("HDMI_L"),
_T("MIC 1"),_T("MIC 2"),
_T("SPDIF R"),_T("SPDIF L"),
_T("AUX_R"),_T("AUX_L"),
_T("SPEAK1R"),_T("SPEAK1L"),
_T("SPEAK2R"),_T("SPEAK2L"),
_T("SPEAK3R"),_T("SPEAK3L"),
_T("SPEAK4R"),_T("SPEAK4L")
	};
		//CString lStrName[18] = {
		//_T("HDMI_R"),_T("HDMI_L"),
		//_T("OPTICAL_R"),_T("OPTICAL_L"),
		//_T("Front R"),_T("Front L"),
		//_T("Rear R"),_T("Rear L"),
		//_T("Center"),_T("Woofer"),
		//_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		//_T("AUX_R"),_T("AUX_L"),
		//_T("PORTABLE_R"),_T("PORTABLE_L"), 
		//_T("COAX_R"),_T("COAX_L")};

	double l_RefVoltageMin[6] = {300,300,300,300,300,300};
	double l_RefVoltageMax[6] = {1500,1500,1500,1500,1500,1500};
	double l_FrequencyMin[6] = {10,10,10,10,10,10};
	double l_FrequencyMax[6] = {1200,1200,1200,1200,1200,1200};

		
	m_cLbOkNg.put_Caption(_T("WAIT"));
	m_cLbOkNg.put_BackColor(0x0000FFFF);


	m_TotalOK = 3;

	//m_LevelSkip = 1;
	


	for(int i = 0; i < 8; i++)
	{
		m_CheckEnable[i] = 1;
		if(m_CheckEnable[i] )
		{							
//			m_DigitalPort = DIG_OPTICAL_SELECT;					
			m_CheckID[i] = i;			

			m_ChnnelName[i] = lStrName[i];
			m_NameLabel[i].put_Caption(m_ChnnelName[i]);

			m_RefVoltageMin[i] = l_RefVoltageMin[i];
			m_RefVoltageMax[i] = l_RefVoltageMax[i];
			m_FrequencyMin[i] = l_FrequencyMin[i];
			m_FrequencyMax[i] = l_FrequencyMax[i];
		}
		else
		{
			m_NameLabel[i].put_Caption(_T(" N/A "));
		}

		m_ChannelOK[i] = 3;
		m_VoltageOK[i] = 3;
		m_FrequencyOK[i] = 3;

		m_ChannelOKCNT[i] = 0;
	}	

	//SetDigitalPortSelect(m_DigitalPort, 0);
}

void CAcqVoltageSamples_IntClkDlg::SetChannelDataManual(int lTestNumber)
{
	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;
			if(m_CheckEnable[i] )
			{	
				m_NameLabel[i].put_Caption("COM MODE");
			}
		}
		return;
	}

		CString lStrName[18] = {
		_T("HDMI_R"),_T("HDMI_L"),
		_T("AUX_R"),_T("AUX_L"),
		_T("OPTICAL_R"),_T("OPTICAL_L"),
		_T("PORTABLE_R"),_T("PORTABLE_L"), 
		_T("Front R"),_T("Front L"),
		_T("Rear R"),_T("Rear L"),
		_T("Center"),_T("Woofer"),
		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		_T("COAX_R"),_T("COAX_L")};

	double l_RefVoltageMin[6] = {300,300,300,300,300,300};
	double l_RefVoltageMax[6] = {1500,1500,1500,1500,1500,1500};
	double l_FrequencyMin[6] = {10,10,10,10,10,10};
	double l_FrequencyMax[6] = {1200,1200,1200,1200,1200,1200};
	
	m_cLbOkNg.put_Caption(_T("WAIT"));
	m_cLbOkNg.put_BackColor(0x0000FFFF);


	m_TotalOK = 3;

	//m_LevelSkip = 1;
	


	for(int i = 0; i < 8; i++)
	{
		m_CheckEnable[i] = 1;
		if(m_CheckEnable[i] )
		{							
//			m_DigitalPort = DIG_OPTICAL_SELECT;					
			m_CheckID[i] = g_ManualId[i];

			m_ChnnelName[i] = lStrName[g_ManualId[i]];
			m_NameLabel[i].put_Caption(m_ChnnelName[i]);

		}
		else
		{
			m_NameLabel[i].put_Caption(_T(" N/A "));
		}

		m_ChannelOK[i] = 3;
		m_VoltageOK[i] = 3;
		m_FrequencyOK[i] = 3;

		m_ChannelOKCNT[i] = 0;
	}	

	//SetDigitalPortSelect(m_DigitalPort, 0);
}


void CAcqVoltageSamples_IntClkDlg::SetChannelDataSeq(int lTestChannel, int lSource)
{	
	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;
			if(m_CheckEnable[i] )
			{	
				m_NameLabel[i].put_Caption("COM MODE");
			}
		}
		return;
	}

	//(1)	_T("HDMI_R"),
	//(2)	_T("HDMI_L"),
	//(3)	_T("OPTICAL_R"),
	//(4)	_T("OPTICAL_L"),
	//(5)	_T("Front R"),
	//(6)	_T("Front L"),
	//(7)	_T("Rear R"),
	//(8)	_T("Rear L"),
	//(9)	_T("Center"),
	//(10)	_T("Woofer"),
	//(11)	_T("SPEAKER_4R"),
	//(12)	_T("SPEAKER_4L"),
	//(13)	_T("AUX_R"),
	//(14)	_T("AUX_L"),
	//(15)	_T("PORTABLE_R"),
	//(16)	_T("PORTABLE_L"), 
	//(17)	_T("COAX_R"),
	//(18)	_T("COAX_L")};
//(1)	_T("HDMI_R"),
//(2)		_T("HDMI_L"),
//(3)		_T("MIC 1"),
//(4)		_T("MIC 2"),
//(5)		_T("SPDIF R"),
//(6)		_T("SPDIF L"),
//(7)		_T("AUX_R"),
//(8)		_T("AUX_L"),
//(9)		_T("SPEAK1R"),
//(10)		_T("SPEAK1L"),
//(11)		_T("SPEAK2R"),
//(12)		_T("SPEAK2L"),
//(13)		_T("SPEAK3R"),
//(14)		_T("SPEAK3L"),
//(15)		_T("SPEAK4R"),
//(16)		_T("SPEAK4L")


	CString lStrName[16] = {
		_T("HDMI_R"),	_T("HDMI_L"),
		_T("MIC 1"),	_T("MIC 2"),
		_T("OPT R"),	_T("OPT L"),
		_T("AUX_R"),	_T("AUX_L"),
		_T("SPEAK1R"),	_T("SPEAK1L"),
		_T("SPEAK2R"),	_T("SPEAK2L"),
		_T("SPEAK3R"),	_T("SPEAK3L"),
		_T("SPEAK4R"),	_T("SPEAK4L")
	};

	CString lStrSPKName[16] = {
		_T("SPEAK4R"),	_T("SPEAK4L"),
		_T("SPEAK3R"),	_T("SPEAK3L"),
		_T("SPEAK2R"),	_T("SPEAK2L"),
		_T("SPEAK1R"),	_T("SPEAK1L"),
		_T("HDMI_R"),	_T("HDMI_L"),
		_T("MIC 1"),	_T("MIC 2"),
		_T("OPT R"),	_T("OPT L"),
		_T("AUX_R"),	_T("AUX_L")
	};

	CString lStrAUXName[16] = {
		_T("HDMI_R"),	_T("HDMI_L"),
		_T("MIC 1"),	_T("MIC 2"),
		_T("OPT R"),	_T("OPT L"),
		_T("AUX_R"),	_T("AUX_L"),
		_T("SPEAK1R"),	_T("SPEAK1L"),
		_T("SPEAK2R"),	_T("SPEAK2L"),
		_T("SPEAK3R"),	_T("SPEAK3L"),
		_T("SPEAK4R"),	_T("SPEAK4L")
	};

	//CString lStrName[18] = {
	//_T("HDMI_R"),_T("HDMI_L"),
	//_T("OPTICAL_R"),_T("OPTICAL_L"),
	//_T("Front R"),_T("Front L"),
	//_T("Rear R"),_T("Rear L"),
	//_T("Center"),_T("Woofer"),
	//_T("SPEAKER_4R"),_T("SPEAKER_4L"),
	//_T("AUX_R"),_T("AUX_L"),
	//_T("PORTABLE_R"),_T("PORTABLE_L"), 
	//_T("COAX_R"),_T("COAX_L")};
	
	if((lTestChannel > 0)&&(lTestChannel < 7))//Zero Base Index
	{
		lTestChannel -= 1;
	}

	if((lSource > 0)&&(lSource <= 8))//Zero Base Index
	{
		if (m_SelectAudio != _AUDIO_SELECT_AUX)
		{
			SendAudioSel(lSource);
			m_SelectAudio = _AUDIO_SELECT_AUX;
		}
		lSource -= 1;
	}
	else if((lSource > 8)&&(lSource <= 16))//Zero Base Index
	{
		if (m_SelectAudio != _AUDIO_SELECT_SPK)
		{
			SendAudioSel(lSource);
			m_SelectAudio = _AUDIO_SELECT_SPK;
		}
		switch (lSource)
		{
		case 9:
			lSource = 6;
			break;
		case 10:
			lSource = 7;
			break;
		case 11:
			lSource = 4;
			break;
		case 12:
			lSource = 5;
			break;
		case 13:
			lSource = 2;
			break;
		case 14:
			lSource = 3;
			break;
		case 15:
			lSource = 0;
			break;
		case 16:
			lSource = 1;
			break;
		default:
			lSource = 0;
			break;

		} //= 16 - lSource;
	}
		
	//if((lSource == 2) || (lSource == 3))
	//{				
	//	m_DigitalPort = DIG_OPTICAL_SELECT;
	//}
	//else if((lSource == 16) || (lSource == 17))
	//{				
	//	m_DigitalPort = DIG_COAX_SELECT;
	//}

	//if(lSource == 16)
	//{
	//	m_CheckID[lTestChannel] = 2;
	//	//m_DigitalPort = DIG_COAX_SELECT;//DIG_OPTICAL_SELECT;
	//}
	//else if(lSource == 17)
	//{
	//	m_CheckID[lTestChannel] = 3;
	//	//m_DigitalPort = DIG_COAX_SELECT;//DIG_OPTICAL_SELECT;
	//}
	//else 
	if((lSource >= 0)&&(lSource <= 15))
	{
		m_CheckID[lTestChannel] = lSource;
		m_CheckEnable[lTestChannel] = 1;
	}
	else
	{
		m_CheckEnable[lTestChannel] = 0;
	}


	for (int i = 0; i < 8; i++)
	{
		if (m_SelectAudio == _AUDIO_SELECT_AUX)
		{
			lStrName[i] = lStrAUXName[i];
		}
		else
		{
			lStrName[i] = lStrSPKName[i];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		m_ChnnelName[i] = lStrName[m_CheckID[i]];
		m_NameLabel[i].put_Caption(m_ChnnelName[i]);
	}

	//if((lSource == 2) || (lSource == 3)||(lSource == 16) || (lSource == 17))
	//{				
	////	m_DigitalPort = DIG_COAX_SELECT;	
	//	SetDigitalPortSelect(m_DigitalPort, 0);
	//}
}


void CAcqVoltageSamples_IntClkDlg::SetChannelDataRangeSeq(int lTestChannel,int l_RefVoltageMin,int l_RefVoltageMax,int l_FrequencyMin,int l_FrequencyMax)
{	

	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;
			m_NameLabel[i].put_Caption("COM MODE");
			
		}
		return;
	}
	if((lTestChannel > 0)&&(lTestChannel < 7))//Zero Base Index
	{
		lTestChannel -= 1;
	}
			
	m_CheckEnable[lTestChannel] = 1;
	InitChannelOne(lTestChannel+1);
	m_RefVoltageMin[lTestChannel] = l_RefVoltageMin;
	m_RefVoltageMax[lTestChannel] = l_RefVoltageMax;
	m_FrequencyMin[lTestChannel] = l_FrequencyMin;
	m_FrequencyMax[lTestChannel] = l_FrequencyMax;	

	//m_VoltageBalnce[lTestChannel] = 0;
}


void CAcqVoltageSamples_IntClkDlg::SetChannelDataRangeSeq(int lTestChannel,int l_RefVoltageMin,int l_RefVoltageMax,int l_FrequencyMin,int l_FrequencyMax, int l_TmpVoltageBalnce)
{	
	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;			
			m_NameLabel[i].put_Caption("COM MODE");	
		}
		return;
	}
	if((lTestChannel > 0)&&(lTestChannel < 7))//Zero Base Index
	{
		lTestChannel -= 1;
	}
			
	m_CheckEnable[lTestChannel] = 1;
	InitChannelOne(lTestChannel+1);
	m_RefVoltageMin[lTestChannel] = l_RefVoltageMin;
	m_RefVoltageMax[lTestChannel] = l_RefVoltageMax;
	m_FrequencyMin[lTestChannel] = l_FrequencyMin;
	m_FrequencyMax[lTestChannel] = l_FrequencyMax;	

	//m_VoltageBalnce[lTestChannel] = l_TmpVoltageBalnce;
}

#if  1


void CAcqVoltageSamples_IntClkDlg::InitChannelOne(int lch)
{

	if (g_SetComOnlyMode == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;

			m_NameLabel[i].put_Caption("COM MODE");


		}
		return;
	}
	if ((lch > 0) && (lch < 7))//Zero Base Index
	{
		lch -= 1;
	}

	CWaitCursor wait;
	//	CString physicalChannel1;
	CString physicalChannel, referenceTriggerSource;
	CString strTemp;
	double minimum, maximum, sampleRate;


	UpdateData(true);
	//m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;


	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
		I16 err;
		
		m_AI_SAMPLE_RATE = DECK_HDMI_SAMPLE_RATE;
		m_AI_SAMPLE_COUNT = DECK_HDMI_SAMPLE_COUNT;
		m_AI_CHECK_COUNT = DECK_HDMI_CHECK_COUNT;

		m_wRange = AD_B_5_V;
		if (m_InitAiChannel == 0)
		{			
			m_InitAiChannel = 1;			
		}

		if (m_InitAiChannel == 1)
		{

			CString str;
			int i = lch;
						
			{
				m_data[i].SetSize(1, m_AI_SAMPLE_COUNT);
				if (m_CheckEnable[i] == 0)
				{
					return;
				}

				m_avg_PPVoltage[i][0] = 0;
				m_avg_PPVoltage[i][1] = 0;
				m_avg_PPVoltage[i][2] = 0;
				m_avg_Freg[i][0] = 0;
				m_avg_Freg[i][1] = 0;
				m_avg_Freg[i][2] = 0;

				double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
				double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

				str.Format(_T("%4.0f Hz"), lavghz);
				m_FreqLabel[i].put_Caption(str);
				m_FreqLabel[i].put_ForeColor(0x0000ff00);

				str.Format(_T("%4.0f mV"), lavgpp);
				m_VoltLabel[i].put_Caption(str);
				m_VoltLabel[i].put_ForeColor(0x0000ff00);

				m_graph[i].Plots.RemoveAll();

			}


			//	for(int i = 0; i < 6; i++)
			{
				m_ChannelOK[i] = 3;
				m_VoltageOK[i] = 3;
				m_FrequencyOK[i] = 3;

				m_ChannelOKCNT[i] = 0;
			}
		}
	}
	else if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{

		I16 err;

		//		#define ADLINK_SAMPLE_RATE		100000.0
		//#define ADLINK_SAMPLE_COUNT		3072 // 1024*3
		//#define ADLINK_CHECK_COUNT		2000


		m_nCardIdx = 0;
		m_CardType = PCI_9111DG;

		m_AI_SAMPLE_RATE = ADLINK_SAMPLE_RATE;
		m_AI_SAMPLE_COUNT = ADLINK_SAMPLE_COUNT;
		m_AI_CHECK_COUNT = ADLINK_CHECK_COUNT;

		m_wRange = AD_B_5_V;
		if (m_InitAiChannel == 0)
		{
			if ((m_hCard = Register_Card(m_CardType, m_nCardIdx)) < 0)
			{
				m_InitAiChannel = 0;
				strTemp.Format(TEXT("Register_Card Error = %d"), m_hCard);
				AfxMessageBox(strTemp);
			}
			else
			{
				m_InitAiChannel = 1;
			}
		}

		if (m_InitAiChannel == 1)
		{

			CString str;
			int i = lch;


			err = AI_9111_Config(m_hCard, TRIG_INT_PACER, 0, 1024);
			if (err != 0) {

				strTemp.Format(TEXT("AI_9111_Config error=%d"), err);

				AfxMessageBox(strTemp);
			}
			err = AI_AsyncDblBufferMode(m_hCard, 0);
			if (err != 0) {
				strTemp.Format(TEXT("AI_DblBufferMode error=%d"), err);
				AfxMessageBox(strTemp);
			}

			//for(int i = 0; i < 6; i++)
			{
				m_data[i].SetSize(1, m_AI_SAMPLE_COUNT);
				if (m_CheckEnable[i] == 0)
				{
					return;
				}

				m_avg_PPVoltage[i][0] = 0;
				m_avg_PPVoltage[i][1] = 0;
				m_avg_PPVoltage[i][2] = 0;
				m_avg_Freg[i][0] = 0;
				m_avg_Freg[i][1] = 0;
				m_avg_Freg[i][2] = 0;

				double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
				double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

				str.Format(_T("%4.0f Hz"), lavghz);
				m_FreqLabel[i].put_Caption(str);
				m_FreqLabel[i].put_ForeColor(0x0000ff00);

				str.Format(_T("%4.0f mV"), lavgpp);
				m_VoltLabel[i].put_Caption(str);
				m_VoltLabel[i].put_ForeColor(0x0000ff00);

				m_graph[i].Plots.RemoveAll();

			}


			//	for(int i = 0; i < 6; i++)
			{
				m_ChannelOK[i] = 3;
				m_VoltageOK[i] = 3;
				m_FrequencyOK[i] = 3;

				m_ChannelOKCNT[i] = 0;
			}

		}



	}
	else if ((g_nNI_CardSel == 0) || (g_nNI_CardSel == 1))
	{
		//CNiString(m_rate) >> sampleRate;
		sampleRate = NI_SAMPLE_RATE;//200000;
		samplesPerChannel = NI_SAMPLE_COUNT;//6000;
	   // CNiString(m_samplesPerChannel) >> samplesPerChannel;

		//m_startButton.EnableWindow(false);
		RemoveEventHandler();
		//   CleanUpIfNecessary();

		int i = lch;
		//for(int i = 0 ; i < 6; i++)
		{
			m_data[i].SetSize(1, NI_SAMPLE_COUNT);
		}
		//for(int i = 0 ; i < 6; i++)
		{

			//	m_data[i].SetSize(1,3000);
			if (m_CheckEnable[i] == 0)
			{
				return;
			}


			m_InitAiChannel = 1;



			try
			{
				// Create a new task
				m_task[i] = std::auto_ptr<CNiDAQmxTask>(new CNiDAQmxTask());

				physicalChannel.Format(_T("Dev1/ai%d"), m_CheckID[i]);
				// Create a channel
			//	m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
			//		static_cast<DAQmxAITerminalConfiguration>(-1), minimum, maximum, 
			//		DAQmxAIVoltageUnitsVolts);
				m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "",
					DAQmxAITerminalConfigurationRse, minimum, maximum,
					DAQmxAIVoltageUnitsVolts);

				// Configure timing specs    
				m_task[i]->Timing.ConfigureSampleClock("", sampleRate, DAQmxSampleClockActiveEdgeRising,
					DAQmxSampleQuantityModeFiniteSamples, samplesPerChannel);

				// Verify the task
				m_task[i]->Control(DAQmxTaskVerify);


			}
			catch (CException* e)
			{
				//e->ReportError();
				e->Delete();

				m_InitAiChannel = 0;
				//break;
			}
		}

		CString str;


		//for(int i = 0; i < 6; i++)
		{

			m_avg_PPVoltage[i][0] = 0;
			m_avg_PPVoltage[i][1] = 0;
			m_avg_PPVoltage[i][2] = 0;
			m_avg_Freg[i][0] = 0;
			m_avg_Freg[i][1] = 0;
			m_avg_Freg[i][2] = 0;

			double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
			double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

			str.Format(_T("%4.0f Hz"), lavghz);
			m_FreqLabel[i].put_Caption(str);
			m_FreqLabel[i].put_ForeColor(0x0000ff00);

			str.Format(_T("%4.0f mV"), lavgpp);
			m_VoltLabel[i].put_Caption(str);
			m_VoltLabel[i].put_ForeColor(0x0000ff00);

			m_graph[i].Plots.RemoveAll();

		}


		//	for(int i = 0; i < 6; i++)
		{
			m_ChannelOK[i] = 3;
			m_VoltageOK[i] = 3;
			m_FrequencyOK[i] = 3;

			m_ChannelOKCNT[i] = 0;
		}
	}
	UpdateData(false);
}

void CAcqVoltageSamples_IntClkDlg::InitChannel()
{
	if (g_SetComOnlyMode == 1)
	{
		return;
	}



	CWaitCursor wait;
	//	CString physicalChannel1;
	CString physicalChannel, referenceTriggerSource;
	CString strTemp;
	double minimum, maximum, sampleRate;


	UpdateData(true);
	//m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;

	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{

		I16 err;

		m_AI_SAMPLE_RATE = DECK_HDMI_SAMPLE_RATE;
		m_AI_SAMPLE_COUNT = DECK_HDMI_SAMPLE_COUNT;
		m_AI_CHECK_COUNT = DECK_HDMI_CHECK_COUNT;

		m_wRange = AD_B_5_V;
		//if (m_InitAiChannel == 0)
		{
			m_InitAiChannel = 1;
		}

		if (m_InitAiChannel == 1)
		{
			CString str;			
			for (int i = 0; i < 8; i++)
			{
				m_data[i].SetSize(1, m_AI_SAMPLE_COUNT);
				if (m_CheckEnable[i] == 0)
				{
					return;
				}

				m_avg_PPVoltage[i][0] = 0;
				m_avg_PPVoltage[i][1] = 0;
				m_avg_PPVoltage[i][2] = 0;
				m_avg_Freg[i][0] = 0;
				m_avg_Freg[i][1] = 0;
				m_avg_Freg[i][2] = 0;

				double lavgpp = 0;// (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
				double lavghz = 0;// (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

				str.Format(_T("%4.0f Hz"), lavghz);
				m_FreqLabel[i].put_Caption(str);
				m_FreqLabel[i].put_ForeColor(0x0000ff00);

				str.Format(_T("%4.0f mV"), lavgpp);
				m_VoltLabel[i].put_Caption(str);
				m_VoltLabel[i].put_ForeColor(0x0000ff00);

				m_graph[i].Plots.RemoveAll();

			}

			for (int i = 0; i < 8; i++)
			{
				m_ChannelOK[i] = 3;
				m_VoltageOK[i] = 3;
				m_FrequencyOK[i] = 3;

				m_ChannelOKCNT[i] = 0;
			}
		}
	}
	else if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{

		I16 err;


		m_nCardIdx = 0;
		m_CardType = PCI_9111DG;

		m_AI_SAMPLE_RATE = ADLINK_SAMPLE_RATE;
		m_AI_SAMPLE_COUNT = ADLINK_SAMPLE_COUNT;
		m_AI_CHECK_COUNT = ADLINK_CHECK_COUNT;

		m_wRange = AD_B_5_V;

		if (m_InitAiChannel != 1)
		{
			if ((m_hCard = Register_Card(m_CardType, m_nCardIdx)) < 0)
			{
				m_InitAiChannel = 0;
				strTemp.Format(TEXT("Register_Card Error = %d"), m_hCard);
				ComLog_AddString(strTemp);//
				AfxMessageBox(strTemp);
			}
			else
			{
				m_InitAiChannel = 1;

			}
		}

		if (m_InitAiChannel == 1)
		{
			CString str;

			err = AI_9111_Config(m_hCard, TRIG_INT_PACER, 0, 1024);
			if (err != 0) {

				strTemp.Format(TEXT("AI_9111_Config error=%d"), err);
				ComLog_AddString(strTemp);//
				AfxMessageBox(strTemp);
				m_InitAiChannel = 0;
			}
			err = AI_AsyncDblBufferMode(m_hCard, 0);
			if (err != 0) {
				strTemp.Format(TEXT("AI_DblBufferMode error=%d"), err);
				ComLog_AddString(strTemp);//
				AfxMessageBox(strTemp);
				m_InitAiChannel = 0;
			}

			for (int i = 0; i < 8; i++)
			{

				m_data[i].SetSize(1, m_AI_SAMPLE_COUNT);
				if (m_CheckEnable[i] == 0)
				{
					continue;
				}
				m_avg_PPVoltage[i][0] = 0;
				m_avg_PPVoltage[i][1] = 0;
				m_avg_PPVoltage[i][2] = 0;
				m_avg_Freg[i][0] = 0;
				m_avg_Freg[i][1] = 0;
				m_avg_Freg[i][2] = 0;

				double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
				double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

				str.Format(_T("%4.0f Hz"), lavghz);
				m_FreqLabel[i].put_Caption(str);
				m_FreqLabel[i].put_ForeColor(0x0000ff00);

				str.Format(_T("%4.0f mV"), lavgpp);
				m_VoltLabel[i].put_Caption(str);
				m_VoltLabel[i].put_ForeColor(0x0000ff00);

				m_graph[i].Plots.RemoveAll();

			}


			for (int i = 0; i < 8; i++)
			{
				m_ChannelOK[i] = 3;
				m_VoltageOK[i] = 3;
				m_FrequencyOK[i] = 3;

				m_ChannelOKCNT[i] = 0;
			}

			//	err=AI_ContScanChannels (m_hCard, m_wScanChans, m_wRange, (U16*)m_pAIBuf, AI_SAMPLE_COUNT, (F64)m_fSampleRate, SYNCH_OP);
			////	err=AI_ContScanChannels (m_hCard, i, m_wRange, (U16*)m_pAIBuf, AI_SAMPLE_COUNT, (F64)m_fSampleRate, SYNCH_OP);
			//	if (err!=0)
			//	{
			//		strTemp.Format( TEXT("AI_ContReadChannel error=%d"), err);
			//		AfxMessageBox( strTemp );
			//	} 
			//	//	C9111intDlg dlg(hCard, wCardType);
			//	//	m_pMainWnd = &dlg;
			//	//	nResponse = dlg.DoModal();
			//	//	if (nResponse == IDOK)
			//	//	{
			//	//		// TODO: Place code here to handle when the dialog is
			//	//		//  dismissed with OK
			//	//	}
			//	//	else if (nResponse == IDCANCEL)
			//	//	{
			//	//		// TODO: Place code here to handle when the dialog is
			//	//		//  dismissed with Cancel

		}
	}
	else if ((g_nNI_CardSel == 0) || (g_nNI_CardSel == 1))
	{
		//CNiString(m_rate) >> sampleRate;
		//sampleRate = 100000;
		//samplesPerChannel = 3000;
		sampleRate = NI_SAMPLE_RATE;//200000;
		samplesPerChannel = NI_SAMPLE_COUNT;//6000;

		m_AI_SAMPLE_RATE = NI_SAMPLE_RATE;
		m_AI_SAMPLE_COUNT = NI_SAMPLE_COUNT;
		m_AI_CHECK_COUNT = NI_CHECK_COUNT;
		// CNiString(m_samplesPerChannel) >> samplesPerChannel;

		 //m_startButton.EnableWindow(false);
		RemoveEventHandler();
		CleanUpIfNecessary();
		m_InitAiChannel = 1;
		for (int i = 0; i < 8; i++)
		{
			m_data[i].SetSize(1, m_AI_SAMPLE_COUNT);
		}
		m_InitAiChannel = 1;
		for (int i = 0; i < 8; i++)
		{

			//	m_data[i].SetSize(1,3000);
			if (m_CheckEnable[i] == 0)
			{
				continue;
			}

			/*
			m_CheckID[i] = lCheckID[i];
			m_ChnnelName[i] = lCheckName[i];
			m_NameLabel[i].put_Text(m_ChnnelName[i]);


			m_RefVoltageMin[i] = l_RefVoltageMin[i];
			m_RefVoltageMax[i] = l_RefVoltageMax[i];
			m_FrequencyMin[i] = l_FrequencyMin[i];
			m_FrequencyMax[i] = l_FrequencyMax[i];

			m_ChannelOK[i] = 3;
			*/


			/*
				double m_RefVoltageMin[6];
				double m_RefVoltageMax[6];
				double m_FrequencyMin[6];
				double m_FrequencyMax[6];

			//	double m_ChannelOK[6];
			//	double m_TotalOK[6];
			*/

			/*
				CTextbox_okng m_FreqLabel[6];
				CTextbox_okng m_VoltLabel[6];
				CTextbox_okng m_NameLabel[6];
			*/
			//SetDlgItemText();



			try
			{
				// Create a new task
				m_task[i] = std::auto_ptr<CNiDAQmxTask>(new CNiDAQmxTask());

				physicalChannel.Format(_T("Dev1/ai%d"), m_CheckID[i]);
				// Create a channel
			//	m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
			//		static_cast<DAQmxAITerminalConfiguration>(-1), minimum, maximum, 
			//		DAQmxAIVoltageUnitsVolts);
				m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "",
					DAQmxAITerminalConfigurationRse, minimum, maximum,
					DAQmxAIVoltageUnitsVolts);

				// Configure timing specs    
				m_task[i]->Timing.ConfigureSampleClock("", sampleRate, DAQmxSampleClockActiveEdgeRising,
					DAQmxSampleQuantityModeFiniteSamples, samplesPerChannel);

				// Verify the task
				m_task[i]->Control(DAQmxTaskVerify);


			}
			catch (CException* e)
			{
				//e->ReportError();
				e->Delete();

				m_InitAiChannel = 0;
				//break;
			}
		}

		CString str;


		for (int i = 0; i < 8; i++)
		{

			m_avg_PPVoltage[i][0] = 0;
			m_avg_PPVoltage[i][1] = 0;
			m_avg_PPVoltage[i][2] = 0;
			m_avg_Freg[i][0] = 0;
			m_avg_Freg[i][1] = 0;
			m_avg_Freg[i][2] = 0;

			double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
			double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

			str.Format(_T("%4.0f Hz"), lavghz);
			m_FreqLabel[i].put_Caption(str);
			m_FreqLabel[i].put_ForeColor(0x0000ff00);

			str.Format(_T("%4.0f mV"), lavgpp);
			m_VoltLabel[i].put_Caption(str);
			m_VoltLabel[i].put_ForeColor(0x0000ff00);

			m_graph[i].Plots.RemoveAll();

		}


		for (int i = 0; i < 8; i++)
		{
			m_ChannelOK[i] = 3;
			m_VoltageOK[i] = 3;
			m_FrequencyOK[i] = 3;

			m_ChannelOKCNT[i] = 0;
		}
	}
	UpdateData(false);
}

void CAcqVoltageSamples_IntClkDlg::InitClearChannel()
{

	return;

	if (g_SetComOnlyMode == 1)
	{
		return;
	}


	CWaitCursor wait;
	//	CString physicalChannel1;
	CString physicalChannel, referenceTriggerSource;
	double minimum, maximum, sampleRate;


	UpdateData(true);
	//m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;
	//CNiString(m_rate) >> sampleRate;
	//sampleRate = 100000;
	//samplesPerChannel = NI_SAMPLE_COUNT;
   // CNiString(m_samplesPerChannel) >> samplesPerChannel;

	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
		//m_InitAiChannel = 1;
		for (int i = 0; i < 8; i++)
		{
			m_data[i].SetSize(1, DECK_HDMI_SAMPLE_COUNT);
		}

		for (int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;

			//	m_data[i].SetSize(1,3000);
			if (m_CheckEnable[i] == 0)
			{
				continue;
			}
		}

		CString str;

		for (int i = 0; i < 8; i++)
		{
			m_avg_PPVoltage[i][0] = 0;
			m_avg_PPVoltage[i][1] = 0;
			m_avg_PPVoltage[i][2] = 0;
			m_avg_Freg[i][0] = 0;
			m_avg_Freg[i][1] = 0;
			m_avg_Freg[i][2] = 0;

			double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
			double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

			str.Format(_T("%4.0f Hz"), lavghz);
			m_FreqLabel[i].put_Caption(str);
			m_FreqLabel[i].put_ForeColor(0x0000ff00);

			str.Format(_T("%4.0f mV"), lavgpp);
			m_VoltLabel[i].put_Caption(str);
			m_VoltLabel[i].put_ForeColor(0x0000ff00);

			m_graph[i].Plots.RemoveAll();

		}


		for (int i = 0; i < 8; i++)
		{
			m_ChannelOK[i] = 3;
			m_VoltageOK[i] = 3;
			m_FrequencyOK[i] = 3;

			m_ChannelOKCNT[i] = 0;
		}
	}
	else if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		//m_InitAiChannel = 1;
		for (int i = 0; i < 8; i++)
		{
			m_data[i].SetSize(1, ADLINK_SAMPLE_COUNT);
		}
		for (int i = 0; i < 8; i++)
		{

			m_CheckEnable[i] = 0;

			//	m_data[i].SetSize(1,3000);
			if (m_CheckEnable[i] == 0)
			{
				continue;
			}


		}

		CString str;


		for (int i = 0; i < 8; i++)
		{

			m_avg_PPVoltage[i][0] = 0;
			m_avg_PPVoltage[i][1] = 0;
			m_avg_PPVoltage[i][2] = 0;
			m_avg_Freg[i][0] = 0;
			m_avg_Freg[i][1] = 0;
			m_avg_Freg[i][2] = 0;

			double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
			double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

			str.Format(_T("%4.0f Hz"), lavghz);
			m_FreqLabel[i].put_Caption(str);
			m_FreqLabel[i].put_ForeColor(0x0000ff00);

			str.Format(_T("%4.0f mV"), lavgpp);
			m_VoltLabel[i].put_Caption(str);
			m_VoltLabel[i].put_ForeColor(0x0000ff00);

			m_graph[i].Plots.RemoveAll();

		}


		for (int i = 0; i < 8; i++)
		{
			m_ChannelOK[i] = 3;
			m_VoltageOK[i] = 3;
			m_FrequencyOK[i] = 3;

			m_ChannelOKCNT[i] = 0;
		}
	}
	else if ((g_nNI_CardSel == 0) || (g_nNI_CardSel == 1))
	{

		//m_startButton.EnableWindow(false);
		RemoveEventHandler();
		CleanUpIfNecessary();
		m_InitAiChannel = 1;
		for (int i = 0; i < 8; i++)
		{
			m_data[i].SetSize(1, NI_SAMPLE_COUNT);
		}
		for (int i = 0; i < 8; i++)
		{

			m_CheckEnable[i] = 0;

			//	m_data[i].SetSize(1,3000);
			if (m_CheckEnable[i] == 0)
			{
				continue;
			}


		}

		CString str;


		for (int i = 0; i < 8; i++)
		{

			m_avg_PPVoltage[i][0] = 0;
			m_avg_PPVoltage[i][1] = 0;
			m_avg_PPVoltage[i][2] = 0;
			m_avg_Freg[i][0] = 0;
			m_avg_Freg[i][1] = 0;
			m_avg_Freg[i][2] = 0;

			double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
			double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

			str.Format(_T("%4.0f Hz"), lavghz);
			m_FreqLabel[i].put_Caption(str);
			m_FreqLabel[i].put_ForeColor(0x0000ff00);

			str.Format(_T("%4.0f mV"), lavgpp);
			m_VoltLabel[i].put_Caption(str);
			m_VoltLabel[i].put_ForeColor(0x0000ff00);

			m_graph[i].Plots.RemoveAll();

		}


		for (int i = 0; i < 8; i++)
		{
			m_ChannelOK[i] = 3;
			m_VoltageOK[i] = 3;
			m_FrequencyOK[i] = 3;

			m_ChannelOKCNT[i] = 0;
		}
	}
	UpdateData(false);
}


void CAcqVoltageSamples_IntClkDlg::ReadChannel(int lch)
{
	static int sRefeshWaitCount = 0;
	I16 err;
	CString 	strTemp;
	if (m_InitAiChannel == 0)
	{
		return;
	}

//	if (m_CheckEnable[lch] == 0)
//		return;
	if (g_SetComOnlyMode == 1)
	{
		return;
	}



	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{

//#define DECK_HDMI_SAMPLE_RATE		48000.0
//#define DECK_HDMI_SAMPLE_COUNT	3072 // 1024*3
//#define DECK_HDMI_CHECK_COUNT		2000
		m_HdmiAudioCount = DECK_HDMI_SAMPLE_COUNT;
		U16 m_pAIBuf[DECK_HDMI_SAMPLE_COUNT];
		m_AI_SAMPLE_COUNT = DECK_HDMI_SAMPLE_COUNT;
		const int cs_ShiftNum = 300;//417;
		int lstrat = 600;//833;
		double lSumTemp = 0;
		double lAverage = 0;
		double lStartAverage = 0;

		double lMaxTemp = -5000;
		int lMaxNo = 0;

		double lMinTemp = 5000;
		int lMinNo = 0;

		int lOrgineNo = 0;
		
		double ldBuf[DECK_HDMI_SAMPLE_COUNT];
		double ldbl_Buf[DECK_HDMI_SAMPLE_COUNT];
		double ldbl_OrgBuf[DECK_HDMI_SAMPLE_COUNT];

		//if ((m_AudioFameCount < 4) || (m_HdmiAudioCount == 0))
		//{

		//	sRefeshWaitCount++;
		//	if (sRefeshWaitCount > 80)
		//	{
		//		memset(m_pAIBuf, 0, sizeof(m_pAIBuf));
		//	}
		//	else
		//	{
		//		return;
		//	}
		//}
		//else
		//{
		//	sRefeshWaitCount = 0;
		//}


		for (int lch = 0; lch < AUDIO_CHANNEL_NO; lch++)
		{
			double lCheckData = 0;
			if (m_CheckID[lch] > 8)
				m_CheckID[lch] %= 8;

			if (m_AudioFameCount < 4) 
			{
				sRefeshWaitCount++;
				if (sRefeshWaitCount > 80)
				{
					memset(m_pAIBuf, 0, sizeof(m_pAIBuf));
					sRefeshWaitCount = 0;
				}
				else
				{
					return;
				}
			}
			else
			{
				
				sRefeshWaitCount = 0;
				
				memcpy(m_pAIBuf, m_HdmiAudioData[m_CheckID[lch]], sizeof(m_pAIBuf));
				//memset(m_HdmiAudioData[m_CheckID[lch]], 0, sizeof(m_HdmiAudioData[m_CheckID[lch]]));
			}
			//if (m_HdmiAudioCount == 0)
			//	return;


			//memcpy(m_pAIBuf, m_HdmiAudioData[m_CheckID[lch]], sizeof(m_pAIBuf));
			//memset(m_HdmiAudioData[m_CheckID[lch]], 0, sizeof(m_HdmiAudioData[m_CheckID[lch]]));
			for (int i = 0; i < m_AI_SAMPLE_COUNT; i++)
			{
				//	m_data[lch](0,i) = (m_pAIBuf[i]>>4) ;
				if ((m_pAIBuf[i] == 0) && (i > 0))
				{
					m_pAIBuf[i] = m_pAIBuf[i - 1];
				}

				if (m_pAIBuf[i] & 0x8000)
				{
					m_data[lch](0, i) = (int)((m_pAIBuf[i] / 16) | 0xFFFFF000);
				}
				else
				{
					m_data[lch](0, i) = (m_pAIBuf[i] >> 4);
				}
				//			m_data[ch_ID](0, i) = m_data[ch_ID](0, i) / 2048. * 5.;
				m_data[lch](0, i) = m_data[lch](0, i) / 2048. * 3.3;// 2.1;

				lCheckData = m_data[lch](0, i);

				lSumTemp += lCheckData;
			}

			lAverage = lSumTemp / m_AI_SAMPLE_COUNT;
		}
		m_UpdateAudioData = 1;
		/////////////////////////////////////
//		for (int ch_ID = 0; ch_ID < AUDIO_CHANNEL_NO; ch_ID++)
//		{
//			m_data[ch_ID].SetSize(1, m_AI_SAMPLE_COUNT);
//			double lCheckData = 0;
//
//		//	memcpy(m_pAIBuf, m_HdmiAudioData[m_CheckID[ch_ID]], sizeof(m_pAIBuf));
//			memcpy(m_pAIBuf, m_HdmiAudioData[ch_ID], sizeof(m_pAIBuf));
//			for (int i = 0; i < m_AI_SAMPLE_COUNT; i++)
//			{
//				//	m_data[lch](0,i) = (m_pAIBuf[i]>>4) ;
//				if ((m_pAIBuf[i] == 0) && (i > 0))
//				{
//					m_pAIBuf[i] = m_pAIBuf[i-1];
//				}
//
//				if (m_pAIBuf[i] & 0x8000)
//				{
//					m_data[ch_ID](0, i) = (int)((m_pAIBuf[i] / 16) | 0xFFFFF000);
//				}
//				else
//				{
//					m_data[ch_ID](0, i) = (m_pAIBuf[i] >> 4);
//				}
//	//			m_data[ch_ID](0, i) = m_data[ch_ID](0, i) / 2048. * 5.;
//				m_data[ch_ID](0, i) = m_data[ch_ID](0, i) / 2048. * 2.1;
//
//				lCheckData = m_data[ch_ID](0, i);
//
//				lSumTemp += lCheckData;
//			}
//
//			lAverage = lSumTemp / m_AI_SAMPLE_COUNT;
//
//#if 0
//			//////////////////////////////////////////////////////////////
//			//if ((m_CheckID[lch] == 10) || (m_CheckID[lch] == 11))
//			//{
//			//	lSumTemp = 0;
//
//
//			//	for (int i = 0; i < cs_ShiftNum; i++)
//			//	{
//			//		lSumTemp += m_data[ch_ID](0, i);
//			//	}
//
//			//	lStartAverage = lSumTemp / cs_ShiftNum;
//			//	//	for(int i = lstrat; i < m_AI_SAMPLE_COUNT; i++)
//			//	for (int i = 0; i < cs_ShiftNum / 2; i++)
//			//	{
//			//		ldBuf[i] = lStartAverage;
//			//	}
//
//			//	for (int i = cs_ShiftNum; i < m_AI_SAMPLE_COUNT; i++)
//			//	{
//
//			//		/*			if(i < cs_ShiftNum/2)
//			//					{
//			//						lAverage = lSumTemp / cs_ShiftNum;
//			//						ldBuf[i-cs_ShiftNum/2] = lAverage;
//			//					}
//			//					else*/
//			//		{
//			//			lAverage = lSumTemp / cs_ShiftNum;
//			//			ldBuf[i - cs_ShiftNum / 2] = lAverage;
//			//		}
//
//
//			//		//else
//			//		{
//			//			lSumTemp += m_data[ch_ID](0, i);
//			//			lSumTemp -= m_data[ch_ID](0, i - cs_ShiftNum);
//			//		}
//
//			//		if (lMaxTemp < lAverage)
//			//		{
//			//			lMaxTemp = lAverage;
//
//			//			lMaxNo = i;
//			//		}
//
//			//		if (lMinTemp > lAverage)
//			//		{
//			//			lMinTemp = lAverage;
//			//			lMinNo = i;
//			//		}
//			//		//	if(m_AI_SAMPLE_COUNT
//			//	}
//			//	for (int i = m_AI_SAMPLE_COUNT - cs_ShiftNum / 2; i < m_AI_SAMPLE_COUNT; i++)
//			//	{
//			//		ldBuf[i] = lAverage;
//			//	}
//
//			//	lOrgineNo = lMaxNo - cs_ShiftNum;
//
//
//			//	for (int i = 0; i < m_AI_SAMPLE_COUNT; i++)
//			//	{
//
//			//		ldbl_OrgBuf[i] = m_data[ch_ID](0, i);
//			//		//ldBuf[i] = sin((i - lOrgineNo) * __MYPI / cs_FilterNum) * lMaxTemp;
//			//		ldbl_Buf[i] = m_data[ch_ID](0, i) - ldBuf[i];
//			//		//if(lch == 0)
//			//		m_data[ch_ID](0, i) = m_data[ch_ID](0, i) - ldBuf[i];
//
//			//	}
//
//			//}
//#endif
//		}
				
		m_AudioFameCount = 0;
		//m_HdmiAudioCount = 0;
		memset(m_HdmiAudioData, 0, sizeof(m_HdmiAudioData));
	}
	else if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		U16 m_pAIBuf[ADLINK_SAMPLE_COUNT];
		m_AI_SAMPLE_COUNT = ADLINK_SAMPLE_COUNT;
		m_wScanChans = m_CheckID[lch];
		m_wRange = AD_B_5_V;

		//		I16 AI_ContReadChannel (U16 CardNumber, U16
		//Channel, U16 AdRange, U16 *Buffer, U32
		//ReadCount, F32 SampleRate, U16 SyncMode)
		err = AI_ContReadChannel(m_hCard, m_wScanChans, m_wRange, (U16*)m_pAIBuf, m_AI_SAMPLE_COUNT, (F64)m_AI_SAMPLE_RATE, SYNCH_OP);
		if (err != 0)
		{
			strTemp.Format(TEXT("AI_ContReadChannel error=%d"), err);
			AfxMessageBox(strTemp);
			m_InitAiChannel = 0;
		}
		else
		{
			///////////////////////////////////
					//100000/60/2 = 833
					//	const double cs_FilterNum = 600;//833.0;
			const int cs_ShiftNum = 300;//417;
			int lstrat = 600;//833;
			double lSumTemp = 0;
			double lAverage = 0;
			double lStartAverage = 0;

			double lMaxTemp = -5000;
			int lMaxNo = 0;

			double lMinTemp = 5000;
			int lMinNo = 0;

			int lOrgineNo = 0;


			double ldBuf[ADLINK_SAMPLE_COUNT];
			double ldbl_Buf[ADLINK_SAMPLE_COUNT];
			double ldbl_OrgBuf[ADLINK_SAMPLE_COUNT];

			/////////////////////////////////////
			m_data[lch].SetSize(1, m_AI_SAMPLE_COUNT);
			double lCheckData = 0;
			for (int i = 0; i < m_AI_SAMPLE_COUNT; i++)
			{
				//	m_data[lch](0,i) = (m_pAIBuf[i]>>4) ;
				if (m_pAIBuf[i] & 0x8000)
				{
					m_data[lch](0, i) = (int)((m_pAIBuf[i] / 16) | 0xFFFFF000);
				}
				else
				{
					m_data[lch](0, i) = (m_pAIBuf[i] >> 4);
				}
				m_data[lch](0, i) = m_data[lch](0, i) / 2048. * 5.;

				lCheckData = m_data[lch](0, i);

				lSumTemp += lCheckData;
			}

			lAverage = lSumTemp / m_AI_SAMPLE_COUNT;
			//////////////////////////////////////////////////////////////
			if ((m_CheckID[lch] == 10) || (m_CheckID[lch] == 11))
			{
				lSumTemp = 0;


				for (int i = 0; i < cs_ShiftNum; i++)
				{
					lSumTemp += m_data[lch](0, i);
				}

				lStartAverage = lSumTemp / cs_ShiftNum;
				//	for(int i = lstrat; i < m_AI_SAMPLE_COUNT; i++)
				for (int i = 0; i < cs_ShiftNum / 2; i++)
				{
					ldBuf[i] = lStartAverage;
				}

				for (int i = cs_ShiftNum; i < m_AI_SAMPLE_COUNT; i++)
				{

					/*			if(i < cs_ShiftNum/2)
								{
									lAverage = lSumTemp / cs_ShiftNum;
									ldBuf[i-cs_ShiftNum/2] = lAverage;
								}
								else*/
					{
						lAverage = lSumTemp / cs_ShiftNum;
						ldBuf[i - cs_ShiftNum / 2] = lAverage;
					}


					//else
					{
						lSumTemp += m_data[lch](0, i);
						lSumTemp -= m_data[lch](0, i - cs_ShiftNum);
					}

					if (lMaxTemp < lAverage)
					{
						lMaxTemp = lAverage;

						lMaxNo = i;
					}

					if (lMinTemp > lAverage)
					{
						lMinTemp = lAverage;
						lMinNo = i;
					}
					//	if(m_AI_SAMPLE_COUNT
				}
				for (int i = m_AI_SAMPLE_COUNT - cs_ShiftNum / 2; i < m_AI_SAMPLE_COUNT; i++)
				{
					ldBuf[i] = lAverage;
				}

				lOrgineNo = lMaxNo - cs_ShiftNum;


				for (int i = 0; i < m_AI_SAMPLE_COUNT; i++)
				{

					ldbl_OrgBuf[i] = m_data[lch](0, i);
					//ldBuf[i] = sin((i - lOrgineNo) * __MYPI / cs_FilterNum) * lMaxTemp;
					ldbl_Buf[i] = m_data[lch](0, i) - ldBuf[i];
					//if(lch == 0)
					m_data[lch](0, i) = m_data[lch](0, i) - ldBuf[i];

				}

			}


		}

	}
	else
	{
		try
		{
			// Create multi-channel reader
			m_reader[lch] = std::auto_ptr<CNiDAQmxAnalogMultiChannelReader>(new CNiDAQmxAnalogMultiChannelReader(m_task[lch]->Stream));

			// Start asynchronous read
			m_reader[lch]->ReadMultiSample(samplesPerChannel, m_data[lch]);

		}
		catch (CException* e)
		{
			e->ReportError();
			e->Delete();
			m_InitAiChannel = 0;
			//   m_startButton.EnableWindow(true);
		}
	}
}


#else
void CAcqVoltageSamples_IntClkDlg::InitChannelOne(int lch)
{

	if(g_SetComOnlyMode == 1)
	{
		for(int i = 0; i < 8; i++)
		{
			m_CheckEnable[i] = 0;
			
			m_NameLabel[i].put_Caption("COM MODE");
			

		}
		return;
	}
	if((lch > 0)&&(lch < 7))//Zero Base Index
	{
		lch -= 1;
	}

    CWaitCursor wait;
//	CString physicalChannel1;
    CString physicalChannel, referenceTriggerSource;
    double minimum, maximum, sampleRate;
    

    UpdateData(true);
    //m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;
    //CNiString(m_rate) >> sampleRate;
	sampleRate = NI_SAMPLE_RATE;//200000;
	samplesPerChannel = NI_SAMPLE_COUNT;//6000;
   // CNiString(m_samplesPerChannel) >> samplesPerChannel;

    //m_startButton.EnableWindow(false);
    RemoveEventHandler();
 //   CleanUpIfNecessary();

	int i = lch;
	//for(int i = 0 ; i < 6; i++)
	{
		m_data[i].SetSize(1,NI_SAMPLE_COUNT);
	}
	//for(int i = 0 ; i < 6; i++)
	{

	//	m_data[i].SetSize(1,3000);
		if(m_CheckEnable[i] == 0)
		{
			return;
		}


	m_InitAiChannel = 1;


		
		try
		{
			// Create a new task
			m_task[i] = std::auto_ptr<CNiDAQmxTask>(new CNiDAQmxTask());

			physicalChannel.Format(_T("Dev1/ai%d"),m_CheckID[i]);
			// Create a channel
		//	m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
		//		static_cast<DAQmxAITerminalConfiguration>(-1), minimum, maximum, 
		//		DAQmxAIVoltageUnitsVolts);
			m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
				DAQmxAITerminalConfigurationRse, minimum, maximum, 
				DAQmxAIVoltageUnitsVolts);

			// Configure timing specs    
			m_task[i]->Timing.ConfigureSampleClock("", sampleRate, DAQmxSampleClockActiveEdgeRising, 
				DAQmxSampleQuantityModeFiniteSamples, samplesPerChannel);

			// Verify the task
			m_task[i]->Control(DAQmxTaskVerify);

		
		}
		catch (CException* e)
		{
			//e->ReportError();
			e->Delete();

			m_InitAiChannel = 0;
			//break;
		 }
	}

	CString str;
		
		
	//for(int i = 0; i < 6; i++)
	{
		
		m_avg_PPVoltage[i][0] = 0 ;	
		m_avg_PPVoltage[i][1] = 0 ;	
		m_avg_PPVoltage[i][2] = 0 ;	
		m_avg_Freg[i][0] = 0;
		m_avg_Freg[i][1] = 0;
		m_avg_Freg[i][2] = 0;
		
		double lavgpp = (m_avg_PPVoltage[i][0]+m_avg_PPVoltage[i][1]+m_avg_PPVoltage[i][2]) / 3;
		double lavghz = (m_avg_Freg[i][0]+m_avg_Freg[i][1]+m_avg_Freg[i][2]) / 3;
	
		str.Format(_T("%4.0f Hz"), lavghz);
		m_FreqLabel[i].put_Caption(str);
		m_FreqLabel[i].put_ForeColor(0x0000ff00);
	
		str.Format(_T("%4.0f mV"), lavgpp);
		m_VoltLabel[i].put_Caption(str);
		m_VoltLabel[i].put_ForeColor(0x0000ff00);

		m_graph[i].Plots.RemoveAll();
		
	}

	
//	for(int i = 0; i < 6; i++)
	{
		m_ChannelOK[i] = 3;
		m_VoltageOK[i] = 3;
		m_FrequencyOK[i] = 3;

		m_ChannelOKCNT[i] = 0;
	}	
	UpdateData(false);
}

void CAcqVoltageSamples_IntClkDlg::InitChannel()
{
	if(g_SetComOnlyMode == 1)
	{
		return;
	}



    CWaitCursor wait;
//	CString physicalChannel1;
    CString physicalChannel, referenceTriggerSource;
    double minimum, maximum, sampleRate;
    

    UpdateData(true);
    //m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;
    //CNiString(m_rate) >> sampleRate;
	//sampleRate = 100000;
	//samplesPerChannel = 3000;
	sampleRate = NI_SAMPLE_RATE;//200000;
	samplesPerChannel = NI_SAMPLE_COUNT;//6000;
   // CNiString(m_samplesPerChannel) >> samplesPerChannel;

    //m_startButton.EnableWindow(false);
    RemoveEventHandler();
    CleanUpIfNecessary();
	m_InitAiChannel = 1;
	for(int i = 0 ; i < 8; i++)
	{
		m_data[i].SetSize(1,NI_SAMPLE_COUNT);
	}
	m_InitAiChannel = 1;
	for(int i = 0 ; i < 8; i++)
	{

	//	m_data[i].SetSize(1,3000);
		if(m_CheckEnable[i] == 0)
		{
			continue;
		}

		/*
		m_CheckID[i] = lCheckID[i];
		m_ChnnelName[i] = lCheckName[i];
		m_NameLabel[i].put_Text(m_ChnnelName[i]);


		m_RefVoltageMin[i] = l_RefVoltageMin[i];
		m_RefVoltageMax[i] = l_RefVoltageMax[i];
		m_FrequencyMin[i] = l_FrequencyMin[i];
		m_FrequencyMax[i] = l_FrequencyMax[i];

		m_ChannelOK[i] = 3;
		*/


/*
	double m_RefVoltageMin[6];
	double m_RefVoltageMax[6];
	double m_FrequencyMin[6];
	double m_FrequencyMax[6];

//	double m_ChannelOK[6];
//	double m_TotalOK[6];
*/

/*		
	CTextbox_okng m_FreqLabel[6];
	CTextbox_okng m_VoltLabel[6];
	CTextbox_okng m_NameLabel[6];
*/
	//SetDlgItemText();


		
		try
		{
			// Create a new task
			m_task[i] = std::auto_ptr<CNiDAQmxTask>(new CNiDAQmxTask());

			physicalChannel.Format(_T("Dev1/ai%d"),m_CheckID[i]);
			// Create a channel
		//	m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
		//		static_cast<DAQmxAITerminalConfiguration>(-1), minimum, maximum, 
		//		DAQmxAIVoltageUnitsVolts);
			m_task[i]->AIChannels.CreateVoltageChannel(physicalChannel, "", 
				DAQmxAITerminalConfigurationRse, minimum, maximum, 
				DAQmxAIVoltageUnitsVolts);

			// Configure timing specs    
			m_task[i]->Timing.ConfigureSampleClock("", sampleRate, DAQmxSampleClockActiveEdgeRising, 
				DAQmxSampleQuantityModeFiniteSamples, samplesPerChannel);

			// Verify the task
			m_task[i]->Control(DAQmxTaskVerify);

		
		}
		catch (CException* e)
		{
			//e->ReportError();
			e->Delete();

			m_InitAiChannel = 0;
			//break;
		 }
	}

	CString str;
		
		
	for(int i = 0; i < 8; i++)
	{
		
		m_avg_PPVoltage[i][0] = 0 ;	
		m_avg_PPVoltage[i][1] = 0 ;	
		m_avg_PPVoltage[i][2] = 0 ;	
		m_avg_Freg[i][0] = 0;
		m_avg_Freg[i][1] = 0;
		m_avg_Freg[i][2] = 0;
		
		double lavgpp = (m_avg_PPVoltage[i][0]+m_avg_PPVoltage[i][1]+m_avg_PPVoltage[i][2]) / 3;
		double lavghz = (m_avg_Freg[i][0]+m_avg_Freg[i][1]+m_avg_Freg[i][2]) / 3;
	
		str.Format(_T("%4.0f Hz"), lavghz);
		m_FreqLabel[i].put_Caption(str);
		m_FreqLabel[i].put_ForeColor(0x0000ff00);
	
		str.Format(_T("%4.0f mV"), lavgpp);
		m_VoltLabel[i].put_Caption(str);
		m_VoltLabel[i].put_ForeColor(0x0000ff00);

		m_graph[i].Plots.RemoveAll();
		
	}

	
	for(int i = 0; i < 8; i++)
	{
		m_ChannelOK[i] = 3;
		m_VoltageOK[i] = 3;
		m_FrequencyOK[i] = 3;

		m_ChannelOKCNT[i] = 0;
	}	
	UpdateData(false);
}

void CAcqVoltageSamples_IntClkDlg::InitClearChannel()
{

	if(g_SetComOnlyMode == 1)
	{
		return;
	}


    CWaitCursor wait;
//	CString physicalChannel1;
    CString physicalChannel, referenceTriggerSource;
    double minimum, maximum, sampleRate;
    

    UpdateData(true);
    //m_physicalChannel.GetWindowText(physicalChannel);
   // CNiString(m_minimum) >> minimum;
  //  CNiString(m_maximum) >> maximum;
	minimum = -5;
	maximum = 5;
    //CNiString(m_rate) >> sampleRate;
	//sampleRate = 100000;
	//samplesPerChannel = NI_SAMPLE_COUNT;
   // CNiString(m_samplesPerChannel) >> samplesPerChannel;

    //m_startButton.EnableWindow(false);
    RemoveEventHandler();
    CleanUpIfNecessary();
	m_InitAiChannel = 1;
	for(int i = 0 ; i < 8; i++)
	{
		m_data[i].SetSize(1,NI_SAMPLE_COUNT);
	}
	for(int i = 0 ; i < 8; i++)
	{

		m_CheckEnable[i] = 0;

	//	m_data[i].SetSize(1,3000);
		if(m_CheckEnable[i] == 0)
		{
			continue;
		}

	
	}

	CString str;
		
		
	for(int i = 0; i < 8; i++)
	{
		
		m_avg_PPVoltage[i][0] = 0 ;	
		m_avg_PPVoltage[i][1] = 0 ;	
		m_avg_PPVoltage[i][2] = 0 ;	
		m_avg_Freg[i][0] = 0;
		m_avg_Freg[i][1] = 0;
		m_avg_Freg[i][2] = 0;
		
		double lavgpp = (m_avg_PPVoltage[i][0]+m_avg_PPVoltage[i][1]+m_avg_PPVoltage[i][2]) / 3;
		double lavghz = (m_avg_Freg[i][0]+m_avg_Freg[i][1]+m_avg_Freg[i][2]) / 3;
	
		str.Format(_T("%4.0f Hz"), lavghz);
		m_FreqLabel[i].put_Caption(str);
		m_FreqLabel[i].put_ForeColor(0x0000ff00);
	
		str.Format(_T("%4.0f mV"), lavgpp);
		m_VoltLabel[i].put_Caption(str);
		m_VoltLabel[i].put_ForeColor(0x0000ff00);

		m_graph[i].Plots.RemoveAll();
		
	}

	
	for(int i = 0; i < 8; i++)
	{
		m_ChannelOK[i] = 3;
		m_VoltageOK[i] = 3;
		m_FrequencyOK[i] = 3;

		m_ChannelOKCNT[i] = 0;
	}	
	UpdateData(false);
}


void CAcqVoltageSamples_IntClkDlg::ReadChannel(int lch)
{
   if(m_InitAiChannel == 0)
   {
	   return;
   }

	if(m_CheckEnable[lch] == 0)
		return;
	if(g_SetComOnlyMode == 1)
	{
		return;
	}

    try
    {
		// Create multi-channel reader
		m_reader[lch] = std::auto_ptr<CNiDAQmxAnalogMultiChannelReader>(new CNiDAQmxAnalogMultiChannelReader(m_task[lch]->Stream));

		// Start asynchronous read
		m_reader[lch]->ReadMultiSample(samplesPerChannel, m_data[lch]);

    }
    catch (CException* e)
    {
        e->ReportError();
        e->Delete();
		m_InitAiChannel = 0;
     //   m_startButton.EnableWindow(true);
     }
}
#endif
//
//void CAcqVoltageSamples_IntClkDlg::ReadChannel()
//{
//   if(m_InitAiChannel == 0)
//   {
//	   return;
//   }
//
//	if(m_CheckEnable[lch] == 0)
//		return;
//
//
//    try
//    {
//		// Create multi-channel reader
//		m_reader[lch] = std::auto_ptr<CNiDAQmxAnalogMultiChannelReader>(new CNiDAQmxAnalogMultiChannelReader(m_task[lch]->Stream));
//
//		// Start asynchronous read
//		m_reader[lch]->ReadMultiSample(samplesPerChannel, m_data[lch]);
//
//    }
//    catch (CException* e)
//    {
//        e->ReportError();
//        e->Delete();
//		m_InitAiChannel = 0;
//     //   m_startButton.EnableWindow(true);
//     }
//}




void CAcqVoltageSamples_IntClkDlg::UpdatePlot(int lch)
{
	if (m_InitAiChannel == 0)
	{
		return;
	}
	if (g_SetComOnlyMode == 1)
	{
		return;
	}
	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
		//if (m_HdmiAudioCount < DECK_HDMI_SAMPLE_COUNT)
		//	return;
		if (m_UpdateAudioData != 1)
			return;
		/////////////////////////////////////
		//if((0 <= lch)&&(8 > lch))
		for (lch = 0; lch < 8; lch++)
		{
			//m_PPVoltage[CheckID] = PPVoltage;	
			//m_Frequency[CheckID] = Frequency;
			if ((m_PPVoltage[lch] < 100)
				|| ((m_PPVoltage[lch] < 100)
					&& ((m_CheckID[lch] < 4) || (m_CheckID[lch] > 11))))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = 1.2;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -1.2;
			}
			else if (m_PPVoltage[lch] < 100)
			{
				if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 * 3) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 3))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 5;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 5;
				}
			}
			else if (m_PPVoltage[lch] < 500)
			{
				if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 2.5) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 2.5))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 3;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 3;
				}
			}
			else if (m_PPVoltage[lch] < 1000)
			{
				if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 * 2) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 2))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 2.5;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 2.5;
				}
			}
			else if (m_PPVoltage[lch] < 2000)
			{
				if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 *1.5) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 1.5))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 1.5;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 1.5;
				}
			}
			else if (m_PPVoltage[lch] < 4000)
			{
				if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 1.3))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.3 / 2000;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.3 / 2000;
				}
			}
			else
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = 2.4;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -2.4;
			}

			// Plot data
			
			m_graph[lch].Plots.RemoveAll();

			//	for (unsigned int i = 0; i < m_task[lch]->AIChannels.Count; i++)
			for (unsigned int i = 0; i < 8; i++)
			{
				m_graph[lch].Plots.Add();
				//m_graph[lch].Plots.Item(i+1).LineColor = m_colors[i % 8];
				m_graph[lch].Plots.Item(i + 1).LineColor = m_colors[0];
			}
			/*
						for (unsigned int i = 0; i < 500; i++)
						{
							m_graph[lch].PlotY( Check_data[lch][i]);
						}
			*/

			if (gbManualScopeMode == 1)
			{
				m_graph[lch].PlotY(Check_data[g_ManualId[lch]]);
			}
			else
			{
				m_graph[lch].PlotY(Check_data[lch]);
			}


		}
	
		m_UpdateAudioData = 0;
	
	}
	else
	{
		//m_PPVoltage[CheckID] = PPVoltage;	
		//m_Frequency[CheckID] = Frequency;
		if ((m_PPVoltage[lch] < 100)
			|| ((m_PPVoltage[lch] < 100)
				&& ((m_CheckID[lch] < 4) || (m_CheckID[lch] > 11))))
		{
			m_graph[lch].Axes.Item("YAxis-1").Maximum = 1.2;
			m_graph[lch].Axes.Item("YAxis-1").Minimum = -1.2;
		}
		else if (m_PPVoltage[lch] < 100)
		{
			if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 * 3) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 3))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 5;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 5;
			}
		}
		else if (m_PPVoltage[lch] < 500)
		{
			if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 2.5) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 2.5))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 3;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 3;
			}
		}
		else if (m_PPVoltage[lch] < 1000)
		{
			if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 * 2) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 2))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 2.5;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 2.5;
			}
		}
		else if (m_PPVoltage[lch] < 2000)
		{
			if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4 *1.5) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000 * 1.5))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 * 1.5;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 * 1.5;
			}
		}
		else if (m_PPVoltage[lch] < 4000)
		{
			if ((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch] / 2000 * 1.4) || (m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch] / 2000))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.3 / 2000;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.3 / 2000;
			}
		}
		else
		{
			m_graph[lch].Axes.Item("YAxis-1").Maximum = 2.4;
			m_graph[lch].Axes.Item("YAxis-1").Minimum = -2.4;
		}

		// Plot data
		m_graph[lch].Plots.RemoveAll();

		//	for (unsigned int i = 0; i < m_task[lch]->AIChannels.Count; i++)
		for (unsigned int i = 0; i < 8; i++)
		{
			m_graph[lch].Plots.Add();
			//m_graph[lch].Plots.Item(i+1).LineColor = m_colors[i % 8];
			m_graph[lch].Plots.Item(i + 1).LineColor = m_colors[0];
		}
		/*
					for (unsigned int i = 0; i < 500; i++)
					{
						m_graph[lch].PlotY( Check_data[lch][i]);
					}
		*/
		m_graph[lch].PlotY(Check_data[lch]);
		


	}
}
#if 1


BOOL CAcqVoltageSamples_IntClkDlg::SetD_OUT(ULONG lSetVal)
{
	if (g_SetComOnlyMode == 1)
	{
		return 0;
	}
	if (m_InitAiChannel == 0)
	{
		return 0;
	}

	if (m_DOportOpen == 0)
		return 0;


	m_DO_Writedata = lSetVal;


	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
	}
	else	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		EDO_9111_Config(0, P9111_EDO_OUT_EDO);
		DO_WritePort(0, P9111_CHANNEL_EDO, lSetVal);
	}
	else if (g_nNI_CardSel == 0)
	{
		try
		{
			// Create the task
			CNiDAQmxTask digitalWriteTask;

			//  Create an Digital Output channel and name it.
			digitalWriteTask.DOChannels.CreateChannel(
				"Dev1/port1",
				"",
				DAQmxOneChannelForAllLines);

			//  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
			//  of digital data on demand, so no timeout is necessary.
			CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);

			//CNiString(m_dataToWrite) >> dataToWrite;
			writer.WriteSingleSamplePort(true, lSetVal);
		}
		catch (CNiDAQmxException *e)
		{
			e->ReportError();
			e->Delete();
			m_DOportOpen = 0;

			return 0;
		}
	}
	else
	{
		try
		{
			// Create the task
			CNiDAQmxTask digitalWriteTask;

			//  Create an Digital Output channel and name it.
			digitalWriteTask.DOChannels.CreateChannel(
				"Dev1/port0",
				"",
				DAQmxOneChannelForAllLines);

			//  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
			//  of digital data on demand, so no timeout is necessary.
			CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);

			//CNiString(m_dataToWrite) >> dataToWrite;
			writer.WriteSingleSamplePort(true, lSetVal);
		}
		catch (CNiDAQmxException *e)
		{
			e->ReportError();
			e->Delete();
			m_DOportOpen = 0;

			return 0;
		}
	}
	return 1;

}


BOOL CAcqVoltageSamples_IntClkDlg::ReadD_IN(unsigned long *lReadData)
{
	UINT inputData = 0;
	if (g_SetComOnlyMode == 1)
	{
		return 0;
	}
	if (m_InitAiChannel == 0)
	{
		return 0;
	}

	if (m_DIportOpen == 0)
		return 0;

	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
	}
	else if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		inputData = 0;
		DI_ReadPort(m_hCard, P9111_CHANNEL_EDI, lReadData);
		if ((*lReadData & 0x0000F) != 0x0000F)
		{
			inputData = (UINT)*lReadData;
			inputData = (UINT)*lReadData;
		}
	}
	else if (g_nNI_CardSel == 0)
	{
		try
		{
			CNiDAQmxTask digitalReadTask;
			//Create the reader

			digitalReadTask.DIChannels.CreateChannel(
				"Dev1/port0",
				"",
				DAQmxOneChannelForAllLines);
			CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

			// Read the data
			//unsigned long data = reader.ReadSingleSamplePortUInt32();
			*lReadData = reader.ReadSingleSamplePortUInt32();

			// Display the data
			//m_hexData.Format(_T("0x%X"),data);//0x3F		
			//UpdateData(FALSE);		
		}
		catch (CNiDAQmxException *exception)
		{
			exception->ReportError();
			exception->Delete();
			m_DIportOpen = 0;
			return 0;
		}
	}
	else
	{
		try
		{
			CNiDAQmxTask digitalReadTask;
			//Create the reader

			digitalReadTask.DIChannels.CreateChannel(
				"Dev1/port1",
				"",
				DAQmxOneChannelForAllLines);
			CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

			// Read the data
			//unsigned long data = reader.ReadSingleSamplePortUInt32();
			*lReadData = reader.ReadSingleSamplePortUInt32();

			// Display the data
			//m_hexData.Format(_T("0x%X"),data);//0x3F		
			//UpdateData(FALSE);		
		}
		catch (CNiDAQmxException *exception)
		{
			exception->ReportError();
			exception->Delete();
			m_DIportOpen = 0;
			return 0;
		}
	}
	return 1;
}

#else

BOOL CAcqVoltageSamples_IntClkDlg::SetD_OUT(ULONG lSetVal)
{
	if(g_SetComOnlyMode == 1)
	{
		return 0;
	}
	if(m_InitAiChannel == 0)
	{
		return 0;
	}

	if(m_DOportOpen == 0)
		return 0;


	m_DO_Writedata = lSetVal;

	
	if(g_nNI_CardSel == 0)
	{
		try
		{
			// Create the task
			CNiDAQmxTask digitalWriteTask;

			//  Create an Digital Output channel and name it.
			digitalWriteTask.DOChannels.CreateChannel(
				"Dev1/port1",
				"",
				DAQmxOneChannelForAllLines);

			//  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
			//  of digital data on demand, so no timeout is necessary.
			CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);
        
			//CNiString(m_dataToWrite) >> dataToWrite;
			writer.WriteSingleSamplePort(true, lSetVal);
		}
		catch (CNiDAQmxException *e)
		{
			e->ReportError();
			e->Delete();
			m_DOportOpen = 0;

			return 0;
		}
	}
	else
	{
		try
		{
			// Create the task
			CNiDAQmxTask digitalWriteTask;

			//  Create an Digital Output channel and name it.
			digitalWriteTask.DOChannels.CreateChannel(
				"Dev1/port0",
				"",
				DAQmxOneChannelForAllLines);

			//  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
			//  of digital data on demand, so no timeout is necessary.
			CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);
        
			//CNiString(m_dataToWrite) >> dataToWrite;
			writer.WriteSingleSamplePort(true, lSetVal);
		}
		catch (CNiDAQmxException *e)
		{
			e->ReportError();
			e->Delete();
			m_DOportOpen = 0;

			return 0;
		}
	}
	return 1;

}


BOOL CAcqVoltageSamples_IntClkDlg::ReadD_IN(unsigned long *lReadData)
{
	if(g_SetComOnlyMode == 1)
	{
		return 0;
	}
	if(m_InitAiChannel == 0)
	{
		return 0;
	}

	if(	m_DIportOpen == 0)
		return 0;

	if(g_nNI_CardSel == 0)
	{
		try
		{       
			CNiDAQmxTask digitalReadTask;
			//Create the reader
				
			digitalReadTask.DIChannels.CreateChannel(
				"Dev1/port0",
				"",
				DAQmxOneChannelForAllLines);
			CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

			// Read the data
			//unsigned long data = reader.ReadSingleSamplePortUInt32();
			*lReadData = reader.ReadSingleSamplePortUInt32();

			// Display the data
			//m_hexData.Format(_T("0x%X"),data);//0x3F		
			//UpdateData(FALSE);		
		}
		catch(CNiDAQmxException *exception)
		{
			exception->ReportError();
			exception->Delete();
			m_DIportOpen = 0;
			return 0;
		}	
	}
	else
	{
		try
		{       
			CNiDAQmxTask digitalReadTask;
			//Create the reader
				
			digitalReadTask.DIChannels.CreateChannel(
				"Dev1/port1",
				"",
				DAQmxOneChannelForAllLines);
			CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

			// Read the data
			//unsigned long data = reader.ReadSingleSamplePortUInt32();
			*lReadData = reader.ReadSingleSamplePortUInt32();

			// Display the data
			//m_hexData.Format(_T("0x%X"),data);//0x3F		
			//UpdateData(FALSE);		
		}
		catch(CNiDAQmxException *exception)
		{
			exception->ReportError();
			exception->Delete();
			m_DIportOpen = 0;
			return 0;
		}	
	}
		return 1;
}
#endif
//#define TEMP_CHANGE_PORT__

void CAcqVoltageSamples_IntClkDlg::CheckControlInput()
{
	if(g_SetComOnlyMode == 1)
	{
		return;
	}
	unsigned long lReadData;
	int lStart = 0;
	int lSensor = 0;
	int lTouch = 0;
	int lReserved = 0;
	static int sOnCnt[4] = {0,0,0,0};
	static int sOffCnt[4] = {0,0,0,0};
	static int sOffFlag[4] = {0,0,0,0};
	static int sPressCnt[4] = {0,0,0,0};

	static int sPressWarning = 0;

	CAcqVoltageSamples_IntClkDlg::ReadD_IN(&lReadData);

	if((lReadData & 0x01) == 1)
	{		
		if(sOnCnt[0] > 1)
		{
			if(sOffFlag[0])
			{
				//SendPreIR_Code(gTestSeqData.TestProcess.strPre_Key);
				sOffFlag[0] = 0; 
				//m_PrecodeWait = 5;
				
				m_nPreCurrentStep = 0;	
				m_nPreCurrentProcess = 0;
				m_nPreCurrentNumber = 0;
				if(gTestSeqData.PreTestCnt > 0)
				{
					m_PreTaskRun = TASK_RUN_START;
					MessageDisplay(2, "Preprocess Start");
				}
			}
		}
		else
		{
			sOnCnt[0]++;
		}
		
		sOffCnt[0] = 0;
		
	}
	else
	{
		if(sOffCnt[0] > 5)
		{
			sOffFlag[0] = 1; 
		}
		else
		{
			sOffFlag[0] = 0; 
			sOffCnt[0]++;
		}

		sOnCnt[0] = 0;
	}

#ifdef TEMP_CHANGE_PORT__
	if((lReadData & 0x08) == 0)
#else
	if((lReadData & 0x02) == 0)
#endif	
	{		
		if(sOnCnt[1] > 1)
		{
			if(sOffFlag[1])
			{
				if(m_TaskRun == TASK_WAIT_SELECT_PROCESS)
				{
					m_NG_Retry_Count++;
					//if(m_NG_WaitFlag
					gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
					m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
					//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
					m_nCurrentProcess = 0;
					m_nCurrentStep = 0;
					m_NG_WaitFlag = 1;

					//return;

					m_TaskRun = TASK_RUN_PROCESS;
					CLOSE_Result_Display();
						
					m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
					m_LED_COM_PROCESS = COM_MODE_IDLE;
					m_PCB_COM_PROCESS = COM_MODE_IDLE;

				}
				else
				{
					CLOSE_Result_Display();
					OnBnClickedStart();
				}
				sOffFlag[1] = 0; 
			}
		}
		else
		{

			
			sOnCnt[1]++;
		}
		sOffCnt[1] = 0;		
		if(m_TaskRun == TASK_RUN_IDLE)
		{
			if((sPressCnt[1] > 400)&&((sPressCnt[1] % 500) == 99))
			{
				MessageDisplay(1, "Start Button Pressed Long Time!");
				sPressWarning = 1;
			}
			if(gbManualScopeMode != 1)
			{
				sPressCnt[1]++;
			}
		}
		
	}
	else
	{
		if(sOffCnt[1] > 5)
		{
			sOffFlag[1] = 1; 
		}
		else
		{
			sOffFlag[1] = 0; 
			sOffCnt[1]++;
		}

		sOnCnt[1] = 0;

		if(sPressWarning)
		{
			MessageDisplay(2, "Start Button Released!");
			sPressWarning = 0;
		}
	}
	

	if((lReadData & 0x04) == 0)
	{			
		if(sOnCnt[2] > 1)
		{
			if(sOffFlag[2])
			{				
				
				if(m_TaskRun == TASK_WAIT_SELECT_PROCESS)
				{
					if(m_GMES_CommError == 1)
					{
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						m_NG_WaitFlag = 0;
						TestFinishGMES();//TestFinish();
					}
					else
					{
						m_NG_Retry_Count++;

						//if(m_NG_WaitFlag
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
						m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
						//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
						m_nCurrentProcess = 0;
						m_nCurrentStep = 0;
						//m_NG_WaitFlag = 1;

						//return;

						m_TaskRun = TASK_RUN_PROCESS;
						CLOSE_Result_Display();
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_LED_COM_PROCESS = COM_MODE_IDLE;
						m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
					}
				}
			}
		}

		else
		{
			sOnCnt[2]++;
		}

		sOffCnt[2] = 0;
		
	}
	else
	{
		if(sOffCnt[2] > 5)
		{
			sOffFlag[2] = 1; 
		}
		else
		{
			sOffFlag[2] = 0; 
			sOffCnt[2]++;
		}
		sOnCnt[2] = 0;
	}


	if((lReadData & 0x08) == 0)
	{			
		if(sOnCnt[3] > 1)
		{
			if(sOffFlag[3])
			{				
				
				if(m_TaskRun != TASK_RUN_IDLE)
				{
					if(m_TaskRun == TASK_WAIT_SELECT_PROCESS)
					{
				
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T("NG"), NULL, NULL, NULL, NULL);
				
						////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
						//m_nCurrentProcess = 0;
						//m_nCurrentStep = 0;
						////m_NG_WaitFlag = 1;

						////return;

						//m_TaskRun = TASK_RUN_PROCESS;
						//CLOSE_Result_Display();
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_LED_COM_PROCESS = COM_MODE_IDLE;
						m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
			
						m_NG_WaitFlag = 0;
						TestFinishGMES();//TestFinish();
					}
					else if(m_TaskRun == TASK_WAIT_BARCODE_PROCESS)
					{
					//	m_TaskRun = TASK_RUN_IDLE;
						CLOSE_Result_Display();
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_LED_COM_PROCESS = COM_MODE_IDLE;
						m_PCB_COM_PROCESS = COM_MODE_IDLE;

						m_TaskRun = TASK_RUN_IDLE;
						m_cLbOkNg.put_Caption(_T("STOP"));//m_BarCode
						m_cLbOkNg.put_BackColor(0x0000FFFF);
					}
					else
					{
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T("NG"), NULL, NULL, NULL, NULL);
				
						////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
						//m_nCurrentProcess = 0;
						//m_nCurrentStep = 0;
						////m_NG_WaitFlag = 1;

						////return;

						//m_TaskRun = TASK_RUN_PROCESS;
						//CLOSE_Result_Display();
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_LED_COM_PROCESS = COM_MODE_IDLE;
						m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
						//m_EthernetMode = 

						m_NG_WaitFlag = 0;
						//TestFinishGMES();//
						TestFinish();
					}
						

					mpDlgBarcode->ShowWindow(SW_HIDE);


				}
			}
		}

		else
		{
			sOnCnt[3]++;
		}

		sOffCnt[3] = 0;
		
	}
	else
	{
		if(sOffCnt[3] > 5)
		{
			sOffFlag[3] = 1; 
		}
		else
		{
			sOffFlag[3] = 0; 
			sOffCnt[3]++;
		}
		sOnCnt[3] = 0;
	}
	/*

	unsigned long lCycle_Time = GetTimeCheck(5);
	str.Format(_T("Cycle Time: %.2f"), lCycle_Time/1000.0);
	
	SetDlgItemText(IDC_STATIC_TOTALTIME,str);

	*/


}





void CAcqVoltageSamples_IntClkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//double m_avg_PPVoltage[6][3];
	//double m_avg_Freg[6][3];

	CString str;
	CString str2;
	unsigned long lCheck_Time;

	//static int sEthernetWaitCnt = 0;



	if(gbManualScopeMode == 1)
	{
		if(nIDEvent == 2)
		{
			KillTimer(2);

			if(g_nPortReopen)
			{
				MessageDisplay(2, "GMES Port Change!");
				CloseEthernetScocket() ;
				m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
				m_EthernetWaitCnt = 0;
		
				CurrentSet->bGMES_Connection = 1;
				g_nPortReopen = 0;
			}

			if(CurrentSet->bGMES_Connection == 0)
			{
				m_EthernetMode = ETHERNET_MODE_IDLE;
			}

			switch(m_EthernetMode)
			{	
			case ETHERNET_MODE_CREATE_SOCKET:

				if(m_EthernetWaitCnt > 1)
				{
					if(CreateEthernetSocket())
					{
						m_EthernetMode = ETHERNET_MODE_HOST_CHECK;
						MessageDisplay(2, "GMES Socket Create!");

						m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
					}
					else
					{
						m_EthernetMode = ETHERNET_MODE_IDLE;
						MessageDisplay(1, "GMES Socket Create Fail!");
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);

						MessageBox("GMES Socket Create Fail!");
						CurrentSet->bGMES_Connection = 0;

					}

					m_EthernetWaitCnt = 0;
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				break;
			case ETHERNET_MODE_HOST_CHECK:
				//Send Are You There
				//=> Are You There Data		
			
				if(m_EthernetWaitCnt > 5)
				{
					m_EthernetWaitCnt = 0;
					GMESAreYouThereRequest();
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				break;		
		
			case ETHERNET_MODE_TIME_SEND:
				//Equipment Status Send
				//=>Equipment Status Acknowledge
			
				if(m_EthernetWaitCnt > 10)
				{
					m_EthernetWaitCnt = 0;
					GMESDateandTimeData();
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				break;

			case ETHERNET_MODE_EQIP_CONNECT:
				//Equipment Status Send
				//=>Equipment Status Acknowledge
			
				if(m_EthernetWaitCnt > 10)
				{
					GMESEquipmentStatusSend(1);
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				break;

			case ETHERNET_MODE_WAIT:
				//Equipment Status Send
				//=>Equipment Status Acknowledge
				if(m_EthernetAck == 1)
				{
					m_EthernetMode = ETHERNET_MODE_RUN;//ETHERNET_MODE_WAIT
				}
				else if(m_EthernetWaitCnt > 100)
				{
					m_EthernetResendCnt++;
					if(m_EthernetResendCnt > 0)
					{
						m_EthernetWaitCnt = 0;
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);
						MessageDisplay(1, "GMES Ack Time Out");
						m_GMES_CommError = 1;
						m_TaskRun = TASK_WAIT_SELECT_PROCESS;
						m_EthernetMode = ETHERNET_MODE_RUN;
						//m_NG_Retry_Count++;
						m_GMES_ErrorName = "GMES Ack Time Out";
						m_GMES_ErrorValue = "GMES Ack Time Out";
						
						m_Deisplay_ErrorName = m_GMES_ErrorName;
						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
						NG_Display(m_GMES_ErrorName);
					}
					else
					{
						m_EthernetWaitCnt = 0;
						OnCmdGmesSend();
					}
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				break;
			case ETHERNET_MODE_RUN://OnCmdGmesSend();

				m_GMES_Alive_WaitCnt++;
				if(m_GMES_Alive_WaitCnt > 20000)
				{
					CurrentSet->bGMES_Connection = 0;
					m_GMES_Alive_WaitCnt = 2;
					MessageBox( "GMES Link Time Out");
					CloseEthernetScocket();
					m_GMES_NGCNT ++;
					MessageDisplay(1, "GMES Link Time Out");
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		
					m_EthernetWaitCnt = 0;
				}
				else
				{
					if(m_GMES_Alive_WaitCnt == 50)
						m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
					//m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
				}
		
				//SetTimer(2,20,NULL);

				break;
			default:

				if(m_EthernetWaitCnt > 100)
				{
					m_EthernetWaitCnt = 0;
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
				

				}
				else
				{
					m_EthernetWaitCnt++;
				}
				//if(CurrentSet->bGMES_Connection)
				//{
				////	m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
				////	m_EthernetWaitCnt = 0;

				//}
				break;
			}

			SetTimer(2,10,NULL);
		}
		else if(nIDEvent == 1)
		{
			KillTimer(1);
	

			if(gbManualScopeMode)
			{
				int i = m_RunCounter%8;

				if(m_CheckEnable[i] == 1)
				{
					//for(int i = 0; i < 6; i++)
					{
						ReadChannel(i);			
						CheckData(i);
						UpdatePlot(i);

					}
	#if 0
					//for(int i = 0; i < 6; i++)
					{
						m_avg_PPVoltage[i][(m_RunCounter/6) %3] = m_PPVoltage[i] ;	
						m_avg_Freg[i][(m_RunCounter/6) %3] = m_Frequency[i];
						if((m_RunCounter/6)%3 == 2)
						{
							double lavgpp = (m_avg_PPVoltage[i][0]+m_avg_PPVoltage[i][1]+m_avg_PPVoltage[i][2]) / 3;
							double lavghz = (m_avg_Freg[i][0]+m_avg_Freg[i][1]+m_avg_Freg[i][2]) / 3;
	
							str.Format(_T("%4.0f Hz"), lavghz);
							m_FreqLabel[i].put_Caption(str);
	
							str.Format(_T("%4.0f mV"), lavgpp);
							m_VoltLabel[i].put_Caption(str);

						}
					}
	#else

					str.Format(_T("%4.0f Hz"), m_Frequency[i]);
					m_FreqLabel[i].put_Caption(str);
	
					str.Format(_T("%4.0f mV"), m_PPVoltage[i]);
					m_VoltLabel[i].put_Caption(str);
	#endif
				}	
				if(m_EnableCount == 1)
				{
					if(i == 0)
					{
				/*		m_RoopCnt++;
						str.Format(_T("%3d "),m_RoopCnt);
						m_CheckTimeLabel.put_Caption(str);*/
					}
				}
			}
			else
			{
				int k = m_RunCounter%8;
				for(int i = 0; i < 6; i++)
				{
			
					if(m_CheckEnable[i] == 1)
					{					
						ReadChannel(i);			
						CheckData(i);
						UpdatePlot(i);

					}

					//for(int i = 0; i < 6; i++)
			/*		{
						ReadChannel(i);
				
			
						CheckData(i);
						UpdatePlot(i);

					}*/
	#if 0
					//for(int i = 0; i < 6; i++)
					{
						m_avg_PPVoltage[i][(m_RunCounter/6) %3] = m_PPVoltage[i] ;	
						m_avg_Freg[i][(m_RunCounter/6) %3] = m_Frequency[i];
						if((m_RunCounter/6)%3 == 2)
						{
							double lavgpp = (m_avg_PPVoltage[i][0]+m_avg_PPVoltage[i][1]+m_avg_PPVoltage[i][2]) / 3;
							double lavghz = (m_avg_Freg[i][0]+m_avg_Freg[i][1]+m_avg_Freg[i][2]) / 3;
	
							str.Format(_T("%4.0f Hz"), lavghz);
							m_FreqLabel[i].put_Caption(str);
	
							str.Format(_T("%4.0f mV"), lavgpp);
							m_VoltLabel[i].put_Caption(str);

						}
					}
	#else

					str.Format(_T("%4.0f Hz"), m_Frequency[i]);
					str2 = m_FreqLabel[i].get_Caption();
					if(str2.Compare(str) != 0)
					{
						m_FreqLabel[i].put_Caption(str);
					}
	
					str.Format(_T("%4.0f mV"), m_PPVoltage[i]);
					str2 = m_VoltLabel[i].get_Caption();
					if(str2.Compare(str) != 0)
					{
						m_VoltLabel[i].put_Caption(str);
					}
	#endif
				}	
				if(m_EnableCount == 1)
				{
					if(k == 0)
					{
						//m_RoopCnt++;
						//str.Format(_T("%3d "),m_RoopCnt);
						//m_CheckTimeLabel.put_Caption(str);
						//m_stcCycleTime.SetWindowText(str);//
					}
				}

			}
			
			
			m_RunCounter++;
			if(m_RunCounter > 120000)
			{
				m_RunCounter = 0;
			}



	

			switch(m_MainPAGE_COM_PROCESS)
			{
				case COM_MODE_WAIT_ACK:
					if(m_ComAck == COM_ACK_OK)
					{
						m_cLb_ComMain.put_BackColor(0x00FF00);
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_ComWaitCnt = 0;
					}
					else if(m_ComAck == COM_ACK_BUSY)
					{
						m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
						m_ComWaitCnt = 0;
					}
					else 
					{
						if(m_TaskRun == TASK_RUN_IDLE)
						{
						
							m_ComWaitCnt++;

							if(m_ComWaitCnt > 60)
							{
								m_ComWaitCnt = 0;
								m_ResendCnt++;
								if(m_ResendCnt > 3)
								{
									MessageDisplay(2, "COM WAIT TIME OUT !!!");
			//#ifndef __COM_DEBUG_MODE__
			//						MessageBox("COM WAIT TIME OUT !");

			//						m_TaskRun = TASK_RUN_IDLE;
			//#endif
									m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
									CycleTimeOn = 0;
								}
								else
								{
									ComSend();
								}
							}
						}
						else
						{
							m_ComWaitCnt++;

							if(m_ComWaitCnt > 100)
							{
								m_ComWaitCnt = 0;
								m_ResendCnt++;
								if(m_ResendCnt > 3)
								{
									int ltime = GetTimeCheck(1);
									if(ltime > m_CheckDelayTime)
									{
										//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
										//m_TaskRun = TASK_WAIT_SELECT_PROCESS;
										m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
										//NG_Display();
										//m_NG_Retry_Count++;
										MessageDisplay(2, "COM WAIT TIME OUT !!!");
									}
									//else
									//{
									//	ComSend();
									//}
								}
								else
								{
									ComSend();
								}
							}
					
						}
					}
				break;

				case COM_MODE_IDLE:
			
				default:

				break;
			}
		

	
			//switch(m_LED_COM_PROCESS)
			//{
			//case COM_MODE_IDLE:
			//	break;
			//case COM_MODE_WAIT_ACK:

			//	if(m_LEDComAck == COM_ACK_OK)
			//	{
			//		m_LEDComAck = COM_ACK_WAIT;
			//		m_LED_COM_PROCESS = COM_MODE_IDLE;
			//		//MessageBox("COM OK !! ");
			//		//MessageDisplay(0, "COM LED OK !! ");
			//	}
			//	else if(m_LEDComAck == COM_ACK_BUSY)
			//	{
			//		//MessageBox("COM Fail !! ");
			//		MessageDisplay(1, "COM LED FAIL !! ");
			//		m_LED_COM_PROCESS = COM_MODE_IDLE;
			//	}
			//	else
			//	{
			//		/*
			//		int m_WaitCnt;
			//		int m_ResendCnt;
			//		*/
			//	
			//		
			//		if(m_TaskRun == TASK_RUN_IDLE)
			//		{
			//			
			//			m_LEDWaitCnt++;

			//			if(m_LEDWaitCnt > 100)
			//			{			
			//				m_LEDResendCnt++;
			//				if(m_LEDResendCnt < 2)
			//				{
			//					ComLedRead();
			//				}
			//				else
			//				{
			//					//MessageBox("COM Time Out !! ");
			//					MessageDisplay(2, "COM LED Time Out !!");
			//					m_LED_COM_PROCESS = COM_MODE_IDLE;
			//				}
			//			}

			//		}
			//		else
			//		{
			//			if(GetTimeCheck(1) > m_CheckDelayTime)
			//			{
			//			//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
			//			//	if(IDYES == MessageBox("Main COM NG RETRY?" , "NG" , MB_YESNO))
			//			//	{
			//			//		m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
			//			//		//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
			//			////		m_nCurrentProcess = 0;
			//			////		if(GetTimeCheck(1) > m_CheckDelayTime)
			//			//		ComLedRead();
			//			//		SetTimeCheck(1);
		
			//			//	}
			//			//	else
			//			//	{
			//			//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
			//			//		TestFinish();
			//			//		m_LED_COM_PROCESS = COM_MODE_IDLE;
			//			//	}
			//			/*	m_TaskRun = TASK_WAIT_SELECT_PROCESS;
			//			
			//				NG_Display();
			//				m_NG_Retry_Count++;*/
			//				MessageDisplay(2, "COM LED Time Out !!");
			//				m_LED_COM_PROCESS = COM_MODE_IDLE;
			//			
			//			}
			//		}
			//	}
			//	break;
			//default:
			//	m_LED_COM_PROCESS = COM_MODE_IDLE;
			//	break;

			//}

			////int m_PCB_COM_PROCESS;
			//int m_PCBComAck;
			//int m_PCBWaitCnt;
			//int m_PCBResendCnt;

			switch(m_PCB_COM_PROCESS)
			{
			case COM_MODE_IDLE:
				break;
			case COM_MODE_WAIT_ACK:

				if(m_PCBComAck == COM_ACK_OK)
				{
					m_PCBComAck = COM_ACK_WAIT;
					m_PCB_COM_PROCESS = COM_MODE_IDLE;
					//MessageBox("COM OK !! ");
					//MessageDisplay(0, "COM Audio OK !! ");
				}
				else if(m_PCBComAck == COM_ACK_BUSY)
				{
					//MessageBox("COM Fail !! ");
					MessageDisplay(2, "COM Audio FAIL !! ");
					m_PCB_COM_PROCESS = COM_MODE_IDLE;
				}
				else
				{
					/*
					int m_WaitCnt;
					int m_ResendCnt;
					*/
				

					if(m_TaskRun == TASK_RUN_IDLE)
					{
						
						m_PCBWaitCnt++;

			//			if(m_PCBWaitCnt > 180)
						if(m_PCBWaitCnt > m_WaitPCB_Ack_Limit)
						{
			
							m_PCBResendCnt++;
							if(m_PCBResendCnt < 2)
							{
								ComPCBSend();
							}
							else
							{
								//MessageBox("COM Time Out !! ");
								MessageDisplay(2, "COM USB Time Out !!");
								m_PCB_COM_PROCESS = COM_MODE_IDLE;
							}
						}

					}
					else
					{
						if(GetTimeCheck(1) > m_CheckDelayTime)
						{
							m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
							//if(IDYES == MessageBox("Main COM NG RETRY?" , "NG" , MB_YESNO))
							//{
							//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);							
							//	ComPCBSend();
							//	SetTimeCheck(1);
		
							//}
							//else
							//{
							//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
							//	TestFinish();
							//	m_PCB_COM_PROCESS = COM_MODE_IDLE;
							//}
							
						//	m_GMES_ErrorName = _T("SetUart Communication Error");
						//	m_GMES_ErrorValue = _T("Ack Time Out");

							m_TaskRun = TASK_WAIT_SELECT_PROCESS;
							m_PCB_COM_PROCESS = COM_MODE_IDLE;
							//m_NG_Retry_Count++;
							//NG_Display(m_GMES_ErrorName);

						}
						else
						{
							m_PCBWaitCnt++;

				//			if(m_PCBWaitCnt > 180)
							if(m_PCBWaitCnt > m_WaitPCB_Ack_Limit)
							{
			
								m_PCBResendCnt++;
								if(m_PCBResendCnt < 10)
								{
									ComPCBSend();
								}
								//else
								//{
								//	//MessageBox("COM Time Out !! ");
								//	MessageDisplay(1, "COM USB Time Out !!");
								//	m_PCB_COM_PROCESS = COM_MODE_IDLE;
								//}
							}
						}
					}
				}
				break;
			default:
				m_PCB_COM_PROCESS = COM_MODE_IDLE;
				break;

			}	

			SetTimer(1,5,NULL);
		}		
		
		CDialog::OnTimer(nIDEvent);
		return;
	}





	
	if(nIDEvent == 2)
	{
		KillTimer(2);
		if(g_SetComOnlyMode == 1)
		{
			m_EthernetMode = ETHERNET_MODE_IDLE;
			g_nPortReopen = 0;
		}

		if(g_nPortReopen)
		{
			MessageDisplay(2, "GMES Port Change!");
			CloseEthernetScocket() ;
			m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
			m_EthernetWaitCnt = 0;
		
			CurrentSet->bGMES_Connection = 1;
			g_nPortReopen = 0;
		}

		if(CurrentSet->bGMES_Connection == 0)
		{
			m_EthernetMode = ETHERNET_MODE_IDLE;
		}

		switch(m_EthernetMode)
		{	
		case ETHERNET_MODE_CREATE_SOCKET:

			if(m_EthernetWaitCnt > 1)
			{
				if(CreateEthernetSocket())
				{
					m_EthernetMode = ETHERNET_MODE_HOST_CHECK;
					MessageDisplay(2, "GMES Socket Create!");

					m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
				}
				else
				{
					m_EthernetMode = ETHERNET_MODE_IDLE;
					MessageDisplay(1, "GMES Socket Create Fail!");
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);

					MessageBox("GMES Socket Create Fail!");
					CurrentSet->bGMES_Connection = 0;

				}

				m_EthernetWaitCnt = 0;
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			break;
		case ETHERNET_MODE_HOST_CHECK:
			//Send Are You There
			//=> Are You There Data		
			
			if(m_EthernetWaitCnt > 5)
			{
				m_EthernetWaitCnt = 0;
				GMESAreYouThereRequest();
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			break;		
		
		case ETHERNET_MODE_TIME_SEND:
			//Equipment Status Send
			//=>Equipment Status Acknowledge
			
			if(m_EthernetWaitCnt > 10)
			{
				m_EthernetWaitCnt = 0;
				GMESDateandTimeData();
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			break;

		case ETHERNET_MODE_EQIP_CONNECT:
			//Equipment Status Send
			//=>Equipment Status Acknowledge
			
			if(m_EthernetWaitCnt > 10)
			{
				GMESEquipmentStatusSend(1);
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			break;

		case ETHERNET_MODE_WAIT:
			//Equipment Status Send
			//=>Equipment Status Acknowledge
			if(m_EthernetAck == 1)
			{
				m_EthernetWaitCnt = 0;
				m_EthernetMode = ETHERNET_MODE_RUN;//ETHERNET_MODE_WAIT
			}
			else if(m_EthernetWaitCnt > 100)
			{
				m_EthernetResendCnt++;
				if(m_EthernetResendCnt > 1)
				{
					m_EthernetWaitCnt = 0;
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
					MessageDisplay(1, "GMES Ack Time Out");
					m_GMES_CommError = 1;
					m_TaskRun = TASK_WAIT_SELECT_PROCESS;
					m_EthernetMode = ETHERNET_MODE_RUN;
					//m_NG_Retry_Count++;
				//	
					
					m_Deisplay_ErrorName = "GMES Ack Time Out";
					m_Deisplay_ErrorName += "\r\nGMES 通信 NG";
					m_Deisplay_ErrorDetail = "GMES Ack Time Out";
					NG_Display("GMES Ack Time Out");
				}
				else
				{
					m_EthernetWaitCnt = 0;
					OnCmdGmesSend();
				}
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			break;
		case ETHERNET_MODE_RUN://OnCmdGmesSend();

			m_GMES_Alive_WaitCnt++;
			if(m_GMES_Alive_WaitCnt > 2500)
			{
				CurrentSet->bGMES_Connection = 0;
				m_GMES_Alive_WaitCnt = 2;
				MessageBox( "GMES Link Time Out");
				CloseEthernetScocket();
				m_GMES_NGCNT ++;
				MessageDisplay(1, "GMES Link Time Out");
				m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		
				m_EthernetWaitCnt = 0;
			}
			else
			{
				if(m_GMES_Alive_WaitCnt == 20)
				{
					CurrentSet->bGMES_Connection = 1;
					m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
				//m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
				}
				else if(m_GMES_Alive_WaitCnt == 200)
				{
					m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
			//		GMESLinkLoopbackTest();
				}

			}
		
			//SetTimer(2,20,NULL);

			break;
		default:

			if(m_EthernetWaitCnt > 100)
			{
				m_EthernetWaitCnt = 0;
				m_cLb_ComMainGmes.put_BackColor(0x000000FF);
				

			}
			else
			{
				m_EthernetWaitCnt++;
			}
			//if(CurrentSet->bGMES_Connection)
			//{
			////	m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
			////	m_EthernetWaitCnt = 0;

			//}
			break;
		}

		SetTimer(2,20,NULL);
	}
	else if(nIDEvent == 1)
	{
		KillTimer(1);
	

		CheckControlInput();

		int i = m_RunCounter%6;
		//if(m_CheckEnable[i] == 1)
		{
			//for(int i = 0; i < 6; i++)
			{
				ReadChannel(i);
			//	ReadChannelex(i);
			
				CheckData(i);
				UpdatePlot(i);

			}
			if (m_InitAiChannel == 1)
			{

				//for(int i = 0; i < 6; i++)
				{
					m_avg_PPVoltage[i][(m_RunCounter / 6) % 3] = m_PPVoltage[i];
					m_avg_Freg[i][(m_RunCounter / 6) % 3] = m_Frequency[i];
					if ((m_RunCounter / 6) % 3 == 2)
					{
						double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
						double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

						str.Format(_T("%4.0f Hz"), lavghz);
						m_FreqLabel[i].put_Caption(str);

						str.Format(_T("%4.0f mV"), lavgpp);
						m_VoltLabel[i].put_Caption(str);

					}
				}
			}
			else
			{
				m_avg_PPVoltage[i][(m_RunCounter / 6) % 3] = 0;
				m_avg_Freg[i][(m_RunCounter / 6) % 3] = 0;
				if ((m_RunCounter / 6) % 3 == 2)
				{
					double lavgpp = (m_avg_PPVoltage[i][0] + m_avg_PPVoltage[i][1] + m_avg_PPVoltage[i][2]) / 3;
					double lavghz = (m_avg_Freg[i][0] + m_avg_Freg[i][1] + m_avg_Freg[i][2]) / 3;

					str.Format(_T("%4.0f Hz"), lavghz);
					m_FreqLabel[i].put_Caption(str);

					str.Format(_T("%4.0f mV"), lavgpp);
					m_VoltLabel[i].put_Caption(str);

				}
			}
		}




		m_RunCounter++;

		if(m_RunCounter > 120000)
		{
			m_RunCounter = 0;
		}

		switch(m_MainPAGE_COM_PROCESS)
		{
			case COM_MODE_IDLE:
				break;

			case COM_MODE_WAIT_ACK:
				if(m_ComAck == COM_ACK_OK)
				{
					m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
					m_ComWaitCnt = 0;
				//	MessageDisplay(0, "COM_ACK_OK !!!");
					
				}
				else if(m_ComAck == COM_ACK_BUSY)
				{
					m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
					m_ComWaitCnt = 0;
					MessageDisplay(1, "COM_ACK_BUSY !!!");
				}
				else 
				{
					if(m_TaskRun == TASK_RUN_IDLE)
					{
						
						m_ComWaitCnt++;

						if(m_ComWaitCnt > 60)
						{
							m_ComWaitCnt = 0;
							m_ResendCnt++;
							if(m_ResendCnt > 3)
							{
								MessageDisplay(1, "COM WAIT TIME OUT !!!");
	
								m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
								CycleTimeOn = 0;
							}
							else
							{
								ComSend();
								//MessageDisplay(1, "COM Resend !!!");
							}
						}
					}
					else
					{
						m_ComWaitCnt++;

						if(m_ComWaitCnt > 60)
						{
							m_ComWaitCnt = 0;
							m_ResendCnt++;
							if(m_ResendCnt > 3)
							{
								int ltime = GetTimeCheck(1);
								if(ltime > m_CheckDelayTime)
								{
									//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
									//m_TaskRun = TASK_WAIT_SELECT_PROCESS;
									m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
									//NG_Display();
									//m_NG_Retry_Count++;
									MessageDisplay(1, "COM WAIT TIME OUT !!!");
								}
							}
							else
							{
								ComSend();
							}
						}
					
					}
				}
			break;

			default:
				break;
			
		}
	
	

		switch(m_PCB_COM_PROCESS)
		{
		case COM_MODE_IDLE:
			break;
		case COM_MODE_WAIT_ACK:

			if(m_PCBComAck == COM_ACK_OK)
			{
				m_PCBComAck = COM_ACK_WAIT;
				m_PCB_COM_PROCESS = COM_MODE_IDLE;
				//MessageBox("COM OK !! ");
				//MessageDisplay(0, "COM Audio OK !! ");
			}
			else if(m_PCBComAck == COM_ACK_BUSY)
			{
				//MessageBox("COM Fail !! ");
				MessageDisplay(2, "COM Audio FAIL !! ");
				m_PCB_COM_PROCESS = COM_MODE_IDLE;
			}
			else
			{
				/*
				int m_WaitCnt;
				int m_ResendCnt;
				*/
				

				if(m_TaskRun == TASK_RUN_IDLE)
				{
						
					m_PCBWaitCnt++;

		//			if(m_PCBWaitCnt > 180)
					if(m_PCBWaitCnt > m_WaitPCB_Ack_Limit)
					{
			
						m_PCBResendCnt++;
						if(m_PCBResendCnt < 2)
						{
							ComPCBSend();
						}
						else
						{
							//MessageBox("COM Time Out !! ");
							MessageDisplay(2, "COM USB Time Out !!");
							m_PCB_COM_PROCESS = COM_MODE_IDLE;
						}
					}

				}
				else
				{
					if( (GetTimeCheck(_CHECK_TIME_PCB_COM_ID) > m_CheckPCB_Com_DelayTime)&&(GetTimeCheck(_CHECK_TIME_PCB_COM_ID) > 1000))//if (GetTimeCheck(1) > m_CheckDelayTime)
					{
						m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
						//if(IDYES == MessageBox("Main COM NG RETRY?" , "NG" , MB_YESNO))
						//{
						//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);							
						//	ComPCBSend();
						//	SetTimeCheck(1);
		
						//}
						//else
						//{
						//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						//	TestFinish();
						//	m_PCB_COM_PROCESS = COM_MODE_IDLE;
						//}
							
						m_GMES_ErrorName = _T("USB Communication Error");
						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
						m_Deisplay_ErrorName = _T("USB Communication Error");

						m_Deisplay_ErrorName += _T("\r\n");
						m_Deisplay_ErrorName +=_T("USB COM NG");// 频率  // 音量 // 版本
					

						m_GMES_ErrorValue = _T("Ack Time Out");
							
						//m_Deisplay_ErrorName = m_GMES_ErrorName;
						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//

						m_TaskRun = TASK_WAIT_SELECT_PROCESS;
						m_PCB_COM_PROCESS = COM_MODE_IDLE;
						//m_NG_Retry_Count++;
						NG_Display(m_GMES_ErrorName);

					}
					else if(m_PCBWaitCnt > m_WaitPCB_Ack_Limit)
					{
			
						m_PCBResendCnt++;
						if(m_PCBResendCnt < 3)
						{
							ComPCBSend();
						}
						else
						{
							//MessageBox("COM Time Out !! ");
							MessageDisplay(2, "COM USB Time Out !!");
							m_PCB_COM_PROCESS = COM_MODE_IDLE;
						}
					}
				}
			}
			break;
		default:
			m_PCB_COM_PROCESS = COM_MODE_IDLE;
			break;

		}

	

		//if(m_MainPAGE_COM_PROCESS == COM_MODE_IDLE)
		if((m_MainPAGE_COM_PROCESS == COM_MODE_IDLE)
//			&&(m_LED_COM_PROCESS == COM_MODE_IDLE)
			&&(m_PCB_COM_PROCESS == COM_MODE_IDLE)
			&&(m_EthernetMode  != ETHERNET_MODE_WAIT))
		{


			switch(m_TaskRun)
			{

			case TASK_RUN_IDLE:		


				if(GetTimeCheck(3) > 500)
				{
					if(m_DO_Writedata &  0x01)
					//if(m_DO_Writedata &  0x03) //NG 50ms
					{
						SetD_OUT(0x00);
					}
				}

				CheckTimeOn = 0;

				if(video_Wait_Count < 2000)
				{
					video_Wait_Count++;
					if((video_Wait_Count > 150)&&((video_Wait_Count % 50) == 0))
					{					
						
						if(m_VideoSignalAlive == 0)//
						{
							if((video_Wait_Count % 100) == 0)
							{
								RefreshHDMI();
							
								m_cLb_Camera.put_BackColor(0x0000FFFF);
								
								//str.Format(_T("RESET%d"),video_Wait_Count/100);								 
								//m_cLb_Camera.put_Caption(str);
							}
						}
					/*	else if(ScreenCheck() == 0)
						{
							if((video_Wait_Count % 100) == 0)
							{
								RefreshHDMI();
							
								m_cLb_Camera.put_BackColor(0x0000FFFF);
								
								str.Format(_T("RESET%d"),video_Wait_Count/100);
								 
								m_cLb_Camera.put_Caption(str);
							}
						}*/
						else
						{
							video_Wait_Count = 0;
							
							m_cLb_Camera.put_BackColor(0x0000FF00);
							//m_cLb_Camera.put_Caption("ACTIVE");
						}
					}
				}
				break;
		
			case TASK_WAIT_SELECT_PROCESS:
				if(m_NG_Retry_Count < 10)
				{
					//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
					////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
					//m_nCurrentProcess = 0;
					//m_nCurrentStep = 0;
					//m_NG_WaitFlag = 1;
					//if(CurrentSet->nUseUserRetry > m_NG_Retry_Count)
					//{
					//	m_NG_Retry_Count++;
					//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
					//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
					//	////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
					//	m_nCurrentProcess = 0;
					//	m_nCurrentStep = 0;
					//	CLOSE_Result_Display();
					//	m_TaskRun = TASK_RUN_PROCESS;
					//	
					//}
					
					if((mpDlgResult->m_ReturnFlag == 1)||(CurrentSet->nUseUserRetry > m_NG_Retry_Count))
					{
						m_NG_Retry_Count++;
						if(m_GMES_CommError == 1)
						{
							gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
							m_NG_WaitFlag = 0;
							TestFinishGMES();//TestFinish();
						}
						else
						{
							gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
							m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
							////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
							m_nCurrentProcess = 0;
							m_nCurrentStep = 1;
							m_InterProcess = STEP_FUNC_START;
							CLOSE_Result_Display();
							m_TaskRun = TASK_RUN_PROCESS;
						}

					}
					else if(mpDlgResult->m_ReturnFlag == 2)//||((m_NG_WaitFlag == 1)&&(m_NG_Retry_Count >= 2)))
					{
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						m_NG_WaitFlag = 0;
						TestFinishGMES();//TestFinish();

					}
					else if(CurrentSet->nUseUserRetry > 0)
					{
						gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						m_NG_WaitFlag = 0;
						TestFinishGMES();
					}
		
		
				}
				else 
				{
					gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
					m_NG_WaitFlag = 0;
					TestFinishGMES();//TestFinish();
				}

			//m_NG_WaitFlag = 0;
		
				break;		
			
			case TASK_WAIT_BARCODE_PROCESS:
		
				if(mpDlgBarcode->m_ReturnFlag == 1)
				{
					m_TaskRun = TASK_RUN_IDLE;
					m_BarCode.put_Caption(mpDlgBarcode->m_Barcode);
					OnBnClickedStart();

				}
				else if(mpDlgBarcode->m_ReturnFlag == 2)
				{
					m_TaskRun = TASK_RUN_IDLE;
					m_cLbOkNg.put_Caption(_T("STOP"));//m_BarCode
					m_cLbOkNg.put_BackColor(0x0000FFFF);

				}
		
		
				

			//m_NG_WaitFlag = 0;
		
				break;

			case TASK_RUN_START:

				SetD_OUT(0x00);//OK DO OUT CONTROL 

	//			m_nCurrentNumber = 0;//gTestSeqData.TestProcess.aSeqData[0].nSeqType;
	//			m_nCurrentProcess = 0;
				m_nCurrentStep = 0;
				SetTimeCheck(1);//m_WaitCnt = 0;
				m_TEST_Result = 3;
				m_TaskRun = TASK_RUN_PROCESS;
				MessageDisplay(0, "START");


				break;

			case TASK_RUN_PROCESS://m_TaskRun

			
				//lCheck_Time = GetTimeCheck(6);			
			
				//str.Format(_T("%.1f"),  lCheck_Time/1000.0);
				//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		

				CallProcess();

		


				break;
			case TASK_FINISH_PROCESS:
			
					TestFinish();
					m_TaskRun = TASK_RUN_IDLE;
						
				break;

			default:

				m_TaskRun = TASK_RUN_IDLE;
				break;		
			}
		}

		DisplayTimeLap();
		if(m_TaskRun == TASK_RUN_PROCESS)
		{
			lCheck_Time = GetTimeCheck(6);					
			str.Format(_T("%.1f"),  lCheck_Time/1000.0);
			if (str != m_CtrlListMainProcess.GetItemText(m_nCurrentNumber, 3))
			{
				m_CtrlListMainProcess.SetItemText(m_nCurrentNumber, 3,  str);
			}
		}

		//str.Format(_T("CNT : %d"), m_RunCounter);
		//SetDlgItemText(IDC_STATIC_CNT, str);
		SetTimer(1,5,NULL);
	}


	CDialog::OnTimer(nIDEvent);
}


#if 0
void CAcqVoltageSamples_IntClkDlg::CheckData(int CheckID)
{

	if(g_SetComOnlyMode == 1)
	{
		return;
	}
	double     lbuf[4000];
	double     lTime[4000];
	double lMinCmp = 0, lmaxCmp = 0;

	double lMinSum = 0, lmaxSum = 0,  lAverage = 0; 
	double lMin[300], lmax[300];
	int lMinCnt = 0, lmaxCnt = 0;
	double PPVoltage = 0;
	double Frequency = 0;

	int lStartNum = 0,	lEndNum = 0,	lCheckCrossCnt = 0;
	int lSignalError = 0;
	int i;
	int lmaxEnable = 0;
	int lminEnable = 0;

	

	double CmpCoefFwd = 0, CmpCoefBak = 0;
//////////////////////////////////////////////////
	//
#ifdef TESTMODE_LEVEL_CHANGE	
	m_data[CheckID].SetSize(1,6000);
	for(i = 0; i < 6000; i++)
	{
		
		if((i < 1000)&&(CheckID%2))
		{
			m_data[CheckID](0,i) = 1.0*sin(3.141592 / 50 * i)*(CheckID/120.0+0.01) ;
		}
		else
		{
			m_data[CheckID](0,i) = 1.0*sin(3.141592 / 500 * i)*(CheckID/120.0+0.01) ;
		}

	}
#endif
//////////////////////////////////////
	lmaxSum = 0;
	for(i = 0; i < NI_SAMPLE_COUNT; i++)
	{
		lmaxSum += abs(m_data[CheckID](0,i));
	}
	lAverage = lmaxSum/NI_SAMPLE_COUNT;
	
	//CmpCoef1 = data[CheckID][0];
	memset(lMin, 0, sizeof(lMin));
	memset(lmax, 0, sizeof(lmax));
	//lMinCmp = -0.2;
	//lmaxCmp = 0.2;
	//m_data
	lMinSum = 0;
	lmaxSum = 0;
	lminEnable  = 1;
	lmaxEnable =1;

	double lchecklimit = lAverage;//*0.5;
	if(lchecklimit < 0.01)
		lchecklimit = 0.011;

	lchecklimit = lchecklimit*2;

	for(i = 0; i < NI_SAMPLE_COUNT-3; i++)
	{
		CmpCoefBak = CmpCoefFwd;
		CmpCoefFwd = m_data[CheckID](0,i)+m_data[CheckID](0,i+1)+m_data[CheckID](0,i+2)+m_data[CheckID](0,i+3);
	//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.1)&&(lminEnable && lmaxEnable))
	//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.5)&&(lminEnable && lmaxEnable))
		if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lchecklimit)&&(lminEnable && lmaxEnable))
		{
			if(lStartNum == 0)
			{
				lMinCnt = 0;
				lmaxCnt = 0;
				lStartNum = i;
			}
			else //if(lminEnable && lmaxEnable)
			{
				lMin[lMinCnt] = lMinCmp;
				lmax[lmaxCnt] = lmaxCmp;
				lMinCnt++;
				lmaxCnt++;
			}

			//if(lminEnable && lmaxEnable)
			{
				lTime[lCheckCrossCnt] = i;
				lCheckCrossCnt++;
				if(lCheckCrossCnt >= 200)
				{
					lSignalError = 1;
					break;
				}
				lEndNum = i;
				
			}
			lMinCmp = 0;
			lmaxCmp = 0;
				
			lmaxEnable = 0;	
			lminEnable = 0;
		}
		else
		{
		//	if((lMinCmp > CmpCoefFwd)&&(CmpCoefFwd <= -lAverage*2))
			if((lMinCmp > CmpCoefFwd)&&(CmpCoefFwd < 0))
			{
				lMinCmp = CmpCoefFwd;
				lminEnable = 1;
			}
	//		if((lmaxCmp < CmpCoefFwd)&&(CmpCoefFwd >= lAverage*2))
			if((lmaxCmp < CmpCoefFwd)&&(CmpCoefFwd > 0))
			{
				lmaxCmp = CmpCoefFwd;
				lmaxEnable = 1;
			}
			
		}
	}
	if(lCheckCrossCnt < 2)
	{
		lSignalError = 1;
		PPVoltage =  lmaxCmp - lMinCmp;
	}
	else
	{
		for(i = 0; i < lMinCnt ; i++)
		{			
			//lmaxSum += lmax[i];
			lMinSum += lMin[i];
		}

		for(i = 0; i < lmaxCnt ; i++)
		{			
			lmaxSum += lmax[i];
			//lMinSum += lMin[i];
		}

		PPVoltage = (lmaxSum/lmaxCnt - lMinSum/lMinCnt)*1000 /4;
	}

	int lNoiseErrorCount = 0;

	if(lSignalError)
	{
		Frequency = 0;
	}
	else
	{
	//	Frequency = 100000.0 / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
		Frequency = NI_SAMPLE_RATE / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
	
	
		if(PPVoltage < 100)
		{
			double lAvgCount = (lEndNum - lStartNum)/lCheckCrossCnt;
			double lCurCount = 0;
			for(int i = 1; i< lCheckCrossCnt-1; i++)
			{
				lCurCount = lTime[i] - lTime[i-1];
				if((lCurCount > lAvgCount*2)||(lCurCount < lAvgCount/2))
				{
					lNoiseErrorCount++;
				}
			}
			if(lNoiseErrorCount > 2)
			{
				Frequency = 0;

				if(PPVoltage < 100)
					PPVoltage  = 0;
			}
		}
	}
	if(PPVoltage < 20)
	{
		PPVoltage  = 0;
		Frequency = 0;
	}


/*	NI_SAMPLE_RATE		
 NI_SAMPLE_COUNT	*/	
	m_PPVoltage[CheckID] = PPVoltage;	
	m_Frequency[CheckID] = Frequency;

//	M_Vol[CheckID].Format(_T("P%02d : %4.0fmV"), CheckID, PPVoltage);
//	M_Frq[CheckID].Format(_T("F%02d : %4.0fHz"), CheckID, Frequency);
	UpdateData(FALSE);

	if((lStartNum < 0)||(lStartNum >= NI_SAMPLE_COUNT-NI_CHECK_COUNT-50))
	{
		lStartNum = 0;
	}

	int j;
	
	j = 0;
	lmaxSum = 0;


	Check_data[CheckID].SetSize(1,NI_CHECK_COUNT);

#if 0
	//for(i = lStartNum; i < lStartNum+NI_CHECK_COUNT; i++)
	//{
	//	Check_data[CheckID](0,j) = m_data[CheckID](0,i);
	//	
	//	j++;			
	//}

	for(i = lStartNum; i < lStartNum+NI_CHECK_COUNT; i++)
	{
		lmaxSum = 0;
		for(int k = 0; k < 40; k++)
		{
			lmaxSum += m_data[CheckID](0,i+k);
		}

		{
			Check_data[CheckID](0,j) = lmaxSum / 40;
		}
		j++;			
	}
#else
	for(i = lStartNum; i < lStartNum+NI_CHECK_COUNT; i++)
	{
		lmaxSum = 0;
		for(int k = 0; k < 20; k++)
		{
			lmaxSum += m_data[CheckID](0,i+k);
		}

		{
			Check_data[CheckID](0,j) = lmaxSum / 20;
		}
		j++;			
	}


	lmaxSum = 0;
	for(i = 0; i < NI_CHECK_COUNT; i++)
	{
		if(lmaxSum < Check_data[CheckID](0,i))//m_Frequency[CheckID] > 25000)
		{
			lmaxSum = Check_data[CheckID](0,i);
		}

		if(lMinSum > Check_data[CheckID](0,i))//m_Frequency[CheckID] > 25000)
		{
			lMinSum = Check_data[CheckID](0,i);
		}
	}
	if(((lmaxSum - m_PPVoltage[CheckID] / 2) >  m_PPVoltage[CheckID] / 2/5)&&((lMinSum - m_PPVoltage[CheckID] / 2) >  m_PPVoltage[CheckID] / 2/5))
	{
		m_NoiseFlag[CheckID] = 1;
	}
	else
	{
		m_NoiseFlag[CheckID] = 0;
	}

	if((lmaxSum < m_PPVoltage[CheckID]/2000)&&(m_PPVoltage[CheckID] > 20)&&(m_Frequency[CheckID] > 1500))
	{
		double lScaleCoef = 0;
		lScaleCoef = m_PPVoltage[CheckID]/lmaxSum/2000;

		for(i = 0; i < NI_CHECK_COUNT; i++)
		{
			Check_data[CheckID](0,i) = Check_data[CheckID](0,i) * lScaleCoef;
		}
	}	
#endif
}
#else
//
void CAcqVoltageSamples_IntClkDlg::CheckData(int CheckID)
{
	if (m_InitAiChannel == 0)
	{
		return;
	}
	if (g_SetComOnlyMode == 1)
	{
		return;
	}

	if (g_nNI_CardSel == AI_DECK_HDMI_4K)
	{
		//if (m_HdmiAudioCount < DECK_HDMI_SAMPLE_COUNT)
		//	return;
		if (m_UpdateAudioData != 1)
			return;
		/////////////////////////////////////
		for (CheckID = 0; CheckID < 8; CheckID++)
		{
			double     lbuf[4000];
			double     lTime[4000];
			double lMinCmp = 0, lmaxCmp = 0;

			double lMinSum = 0, lmaxSum = 0, lAverage = 0;
			double lMin[300], lmax[300];
			int lMinCnt = 0, lmaxCnt = 0;
			double PPVoltage = 0;
			double Frequency = 0;

			int lStartNum = 0, lEndNum = 0, lCheckCrossCnt = 0;
			int lSignalError = 0;
			int i;
			int lmaxEnable = 0;
			int lminEnable = 0;



			double CmpCoefFwd = 0, CmpCoefBak = 0;
			//////////////////////////////////////////////////
				//
		#ifdef TESTMODE_LEVEL_CHANGE	
			m_data[CheckID].SetSize(1, 6000);
			for (i = 0; i < 6000; i++)
			{

				if ((i < 1000) && (CheckID % 2))
				{
					m_data[CheckID](0, i) = 1.0*sin(3.141592 / 50 * i)*(CheckID / 120.0 + 0.01);
				}
				else
				{
					m_data[CheckID](0, i) = 1.0*sin(3.141592 / 500 * i)*(CheckID / 120.0 + 0.01);
				}

			}
		#endif
			//////////////////////////////////////
			lmaxSum = 0;
			for (i = 0; i < m_AI_SAMPLE_COUNT; i++)
			{
				lmaxSum += abs(m_data[CheckID](0, i));
			}
			lAverage = lmaxSum / m_AI_SAMPLE_COUNT;

			//CmpCoef1 = data[CheckID][0];
			memset(lMin, 0, sizeof(lMin));
			memset(lmax, 0, sizeof(lmax));
			//lMinCmp = -0.2;
			//lmaxCmp = 0.2;
			//m_data
			lMinSum = 0;
			lmaxSum = 0;
			lminEnable = 1;
			lmaxEnable = 1;

			double lchecklimit = lAverage;//*0.5;
			if (lchecklimit < 0.01)
				lchecklimit = 0.011;

			lchecklimit = lchecklimit * 2;

			for (i = 0; i < m_AI_SAMPLE_COUNT - 3; i++)
			{
				CmpCoefBak = CmpCoefFwd;
				CmpCoefFwd = m_data[CheckID](0, i) + m_data[CheckID](0, i + 1) + m_data[CheckID](0, i + 2) + m_data[CheckID](0, i + 3);
				//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.1)&&(lminEnable && lmaxEnable))
				//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.5)&&(lminEnable && lmaxEnable))
				if ((-0.00 > CmpCoefFwd) && (lmaxCmp >= lchecklimit) && (lminEnable && lmaxEnable))
				{
					if (lStartNum == 0)
					{
						lMinCnt = 0;
						lmaxCnt = 0;
						lStartNum = i;
					}
					else //if(lminEnable && lmaxEnable)
					{
						lMin[lMinCnt] = lMinCmp;
						lmax[lmaxCnt] = lmaxCmp;
						lMinCnt++;
						lmaxCnt++;
					}

					//if(lminEnable && lmaxEnable)
					{
						lTime[lCheckCrossCnt] = i;
						lCheckCrossCnt++;
						if (lCheckCrossCnt >= 200)
						{
							lSignalError = 1;
							break;
						}
						lEndNum = i;

					}
					lMinCmp = 0;
					lmaxCmp = 0;

					lmaxEnable = 0;
					lminEnable = 0;
				}
				else
				{
					//	if((lMinCmp > CmpCoefFwd)&&(CmpCoefFwd <= -lAverage*2))
					if ((lMinCmp > CmpCoefFwd) && (CmpCoefFwd < 0))
					{
						lMinCmp = CmpCoefFwd;
						lminEnable = 1;
					}
					//		if((lmaxCmp < CmpCoefFwd)&&(CmpCoefFwd >= lAverage*2))
					if ((lmaxCmp < CmpCoefFwd) && (CmpCoefFwd > 0))
					{
						lmaxCmp = CmpCoefFwd;
						lmaxEnable = 1;
					}

				}
			}
			if (lCheckCrossCnt < 2)
			{
				lSignalError = 1;
				PPVoltage = lmaxCmp - lMinCmp;
			}
			else
			{
				for (i = 0; i < lMinCnt; i++)
				{
					//lmaxSum += lmax[i];
					lMinSum += lMin[i];
				}

				for (i = 0; i < lmaxCnt; i++)
				{
					lmaxSum += lmax[i];
					//lMinSum += lMin[i];
				}

				PPVoltage = (lmaxSum / lmaxCnt - lMinSum / lMinCnt) * 1000 / 4;
			}

			int lNoiseErrorCount = 0;

			if (lSignalError)
			{
				Frequency = 0;
			}
			else
			{
				//	Frequency = 100000.0 / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
				Frequency = m_AI_SAMPLE_RATE / (lEndNum - lStartNum) * (lCheckCrossCnt - 1);


				if (PPVoltage < 100)
				{
					double lAvgCount = (lEndNum - lStartNum) / lCheckCrossCnt;
					double lCurCount = 0;
					for (int i = 1; i < lCheckCrossCnt - 1; i++)
					{
						lCurCount = lTime[i] - lTime[i - 1];
						if ((lCurCount > lAvgCount * 2) || (lCurCount < lAvgCount / 2))
						{
							lNoiseErrorCount++;
						}
					}
					if (lNoiseErrorCount > 2)
					{
						Frequency = 0;

						if (PPVoltage < 100)
							PPVoltage = 0;
					}
				}
			}
			if (PPVoltage < 20)
			{
				PPVoltage = 0;
				Frequency = 0;
			}


			/*	NI_SAMPLE_RATE
			 NI_SAMPLE_COUNT	*/
			m_PPVoltage[CheckID] = PPVoltage;
			m_Frequency[CheckID] = Frequency;

			//	M_Vol[CheckID].Format(_T("P%02d : %4.0fmV"), CheckID, PPVoltage);
			//	M_Frq[CheckID].Format(_T("F%02d : %4.0fHz"), CheckID, Frequency);
			UpdateData(FALSE);

			if ((lStartNum < 0) || (lStartNum >= m_AI_SAMPLE_COUNT - m_AI_CHECK_COUNT - 50))
			{
				lStartNum = 0;
			}

			int j;

			j = 0;
			lmaxSum = 0;


			Check_data[CheckID].SetSize(1, m_AI_CHECK_COUNT);

		#if 0
			//for(i = lStartNum; i < lStartNum+NI_CHECK_COUNT; i++)
			//{
			//	Check_data[CheckID](0,j) = m_data[CheckID](0,i);
			//	
			//	j++;			
			//}

			for (i = lStartNum; i < lStartNum + NI_CHECK_COUNT; i++)
			{
				lmaxSum = 0;
				for (int k = 0; k < 40; k++)
				{
					lmaxSum += m_data[CheckID](0, i + k);
				}

				{
					Check_data[CheckID](0, j) = lmaxSum / 40;
				}
				j++;
			}
		#else
			for (i = lStartNum; i < lStartNum + m_AI_CHECK_COUNT; i++)
			{
				lmaxSum = 0;
				for (int k = 0; k < 20; k++)
				{
					lmaxSum += m_data[CheckID](0, i + k);
				}

				{
					Check_data[CheckID](0, j) = lmaxSum / 20;
				}
				j++;
			}


			lmaxSum = 0;
			for (i = 0; i < m_AI_CHECK_COUNT; i++)
			{
				if (lmaxSum < Check_data[CheckID](0, i))//m_Frequency[CheckID] > 25000)
				{
					lmaxSum = Check_data[CheckID](0, i);
				}

				if (lMinSum > Check_data[CheckID](0, i))//m_Frequency[CheckID] > 25000)
				{
					lMinSum = Check_data[CheckID](0, i);
				}
			}
			if (((lmaxSum - m_PPVoltage[CheckID] / 2) > m_PPVoltage[CheckID] / 2 / 5) && ((lMinSum - m_PPVoltage[CheckID] / 2) > m_PPVoltage[CheckID] / 2 / 5))
			{
				m_NoiseFlag[CheckID] = 1;
			}
			else
			{
				m_NoiseFlag[CheckID] = 0;
			}

			if ((lmaxSum < m_PPVoltage[CheckID] / 2000) && (m_PPVoltage[CheckID] > 20) && (m_Frequency[CheckID] > 1500))
			{
				double lScaleCoef = 0;
				lScaleCoef = m_PPVoltage[CheckID] / lmaxSum / 2000;

				for (i = 0; i < m_AI_CHECK_COUNT; i++)
				{
					Check_data[CheckID](0, i) = Check_data[CheckID](0, i) * lScaleCoef;
				}
			}
		#endif
		}
	}
	else
	{
	
		double     lbuf[4000];
		double     lTime[4000];
		double lMinCmp = 0, lmaxCmp = 0;

		double lMinSum = 0, lmaxSum = 0, lAverage = 0;
		double lMin[300], lmax[300];
		int lMinCnt = 0, lmaxCnt = 0;
		double PPVoltage = 0;
		double Frequency = 0;

		int lStartNum = 0, lEndNum = 0, lCheckCrossCnt = 0;
		int lSignalError = 0;
		int i;
		int lmaxEnable = 0;
		int lminEnable = 0;



		double CmpCoefFwd = 0, CmpCoefBak = 0;
		//////////////////////////////////////////////////
			//
#ifdef TESTMODE_LEVEL_CHANGE	
		m_data[CheckID].SetSize(1, 6000);
		for (i = 0; i < 6000; i++)
		{

			if ((i < 1000) && (CheckID % 2))
			{
				m_data[CheckID](0, i) = 1.0*sin(3.141592 / 50 * i)*(CheckID / 120.0 + 0.01);
			}
			else
			{
				m_data[CheckID](0, i) = 1.0*sin(3.141592 / 500 * i)*(CheckID / 120.0 + 0.01);
			}

		}
#endif
		//////////////////////////////////////
		lmaxSum = 0;
		for (i = 0; i < m_AI_SAMPLE_COUNT; i++)
		{
			lmaxSum += abs(m_data[CheckID](0, i));
		}
		lAverage = lmaxSum / m_AI_SAMPLE_COUNT;

		//CmpCoef1 = data[CheckID][0];
		memset(lMin, 0, sizeof(lMin));
		memset(lmax, 0, sizeof(lmax));
		//lMinCmp = -0.2;
		//lmaxCmp = 0.2;
		//m_data
		lMinSum = 0;
		lmaxSum = 0;
		lminEnable = 1;
		lmaxEnable = 1;

		double lchecklimit = lAverage;//*0.5;
		if (lchecklimit < 0.01)
			lchecklimit = 0.011;

		lchecklimit = lchecklimit * 2;

		for (i = 0; i < m_AI_SAMPLE_COUNT - 3; i++)
		{
			CmpCoefBak = CmpCoefFwd;
			CmpCoefFwd = m_data[CheckID](0, i) + m_data[CheckID](0, i + 1) + m_data[CheckID](0, i + 2) + m_data[CheckID](0, i + 3);
			//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.1)&&(lminEnable && lmaxEnable))
			//	if((-0.00 > CmpCoefFwd)&&(lmaxCmp >= lAverage*0.5)&&(lminEnable && lmaxEnable))
			if ((-0.00 > CmpCoefFwd) && (lmaxCmp >= lchecklimit) && (lminEnable && lmaxEnable))
			{
				if (lStartNum == 0)
				{
					lMinCnt = 0;
					lmaxCnt = 0;
					lStartNum = i;
				}
				else //if(lminEnable && lmaxEnable)
				{
					lMin[lMinCnt] = lMinCmp;
					lmax[lmaxCnt] = lmaxCmp;
					lMinCnt++;
					lmaxCnt++;
				}

				//if(lminEnable && lmaxEnable)
				{
					lTime[lCheckCrossCnt] = i;
					lCheckCrossCnt++;
					if (lCheckCrossCnt >= 200)
					{
						lSignalError = 1;
						break;
					}
					lEndNum = i;

				}
				lMinCmp = 0;
				lmaxCmp = 0;

				lmaxEnable = 0;
				lminEnable = 0;
			}
			else
			{
				//	if((lMinCmp > CmpCoefFwd)&&(CmpCoefFwd <= -lAverage*2))
				if ((lMinCmp > CmpCoefFwd) && (CmpCoefFwd < 0))
				{
					lMinCmp = CmpCoefFwd;
					lminEnable = 1;
				}
				//		if((lmaxCmp < CmpCoefFwd)&&(CmpCoefFwd >= lAverage*2))
				if ((lmaxCmp < CmpCoefFwd) && (CmpCoefFwd > 0))
				{
					lmaxCmp = CmpCoefFwd;
					lmaxEnable = 1;
				}

			}
		}
		if (lCheckCrossCnt < 2)
		{
			lSignalError = 1;
			PPVoltage = lmaxCmp - lMinCmp;
		}
		else
		{
			for (i = 0; i < lMinCnt; i++)
			{
				//lmaxSum += lmax[i];
				lMinSum += lMin[i];
			}

			for (i = 0; i < lmaxCnt; i++)
			{
				lmaxSum += lmax[i];
				//lMinSum += lMin[i];
			}

			PPVoltage = (lmaxSum / lmaxCnt - lMinSum / lMinCnt) * 1000 / 4;
		}

		int lNoiseErrorCount = 0;

		if (lSignalError)
		{
			Frequency = 0;
		}
		else
		{
			//	Frequency = 100000.0 / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
			Frequency = m_AI_SAMPLE_RATE / (lEndNum - lStartNum) * (lCheckCrossCnt - 1);


			if (PPVoltage < 100)
			{
				double lAvgCount = (lEndNum - lStartNum) / lCheckCrossCnt;
				double lCurCount = 0;
				for (int i = 1; i < lCheckCrossCnt - 1; i++)
				{
					lCurCount = lTime[i] - lTime[i - 1];
					if ((lCurCount > lAvgCount * 2) || (lCurCount < lAvgCount / 2))
					{
						lNoiseErrorCount++;
					}
				}
				if (lNoiseErrorCount > 2)
				{
					Frequency = 0;

					if (PPVoltage < 100)
						PPVoltage = 0;
				}
			}
		}
		if (PPVoltage < 20)
		{
			PPVoltage = 0;
			Frequency = 0;
		}


		/*	NI_SAMPLE_RATE
		 NI_SAMPLE_COUNT	*/
		m_PPVoltage[CheckID] = PPVoltage;
		m_Frequency[CheckID] = Frequency;

		//	M_Vol[CheckID].Format(_T("P%02d : %4.0fmV"), CheckID, PPVoltage);
		//	M_Frq[CheckID].Format(_T("F%02d : %4.0fHz"), CheckID, Frequency);
		UpdateData(FALSE);

		if ((lStartNum < 0) || (lStartNum >= m_AI_SAMPLE_COUNT - m_AI_CHECK_COUNT - 50))
		{
			lStartNum = 0;
		}

		int j;

		j = 0;
		lmaxSum = 0;


		Check_data[CheckID].SetSize(1, m_AI_CHECK_COUNT);

#if 0
		//for(i = lStartNum; i < lStartNum+NI_CHECK_COUNT; i++)
		//{
		//	Check_data[CheckID](0,j) = m_data[CheckID](0,i);
		//	
		//	j++;			
		//}

		for (i = lStartNum; i < lStartNum + NI_CHECK_COUNT; i++)
		{
			lmaxSum = 0;
			for (int k = 0; k < 40; k++)
			{
				lmaxSum += m_data[CheckID](0, i + k);
			}

			{
				Check_data[CheckID](0, j) = lmaxSum / 40;
			}
			j++;
		}
#else
		for (i = lStartNum; i < lStartNum + m_AI_CHECK_COUNT; i++)
		{
			lmaxSum = 0;
			for (int k = 0; k < 20; k++)
			{
				lmaxSum += m_data[CheckID](0, i + k);
			}

			{
				Check_data[CheckID](0, j) = lmaxSum / 20;
			}
			j++;
		}


		lmaxSum = 0;
		for (i = 0; i < m_AI_CHECK_COUNT; i++)
		{
			if (lmaxSum < Check_data[CheckID](0, i))//m_Frequency[CheckID] > 25000)
			{
				lmaxSum = Check_data[CheckID](0, i);
			}

			if (lMinSum > Check_data[CheckID](0, i))//m_Frequency[CheckID] > 25000)
			{
				lMinSum = Check_data[CheckID](0, i);
			}
		}
		if (((lmaxSum - m_PPVoltage[CheckID] / 2) > m_PPVoltage[CheckID] / 2 / 5) && ((lMinSum - m_PPVoltage[CheckID] / 2) > m_PPVoltage[CheckID] / 2 / 5))
		{
			m_NoiseFlag[CheckID] = 1;
		}
		else
		{
			m_NoiseFlag[CheckID] = 0;
		}

		if ((lmaxSum < m_PPVoltage[CheckID] / 2000) && (m_PPVoltage[CheckID] > 20) && (m_Frequency[CheckID] > 1500))
		{
			double lScaleCoef = 0;
			lScaleCoef = m_PPVoltage[CheckID] / lmaxSum / 2000;

			for (i = 0; i < m_AI_CHECK_COUNT; i++)
			{
				Check_data[CheckID](0, i) = Check_data[CheckID](0, i) * lScaleCoef;
			}
		}
#endif
	}
}
#endif

void CAcqVoltageSamples_IntClkDlg::CheckOK()
{
	 int lOldchOk[6];

	for(int i = 0 ; i < 6; i++)
	{
		if(m_CheckEnable[i] == 0)
		{
			m_ChannelOK[i] = 1;

			//if(m_nBalanceEnable[i] == 1)
			//{
			//	MessageDisplay(1, "Cannot Check Volume Balance");
			//	MessageBox( "Sequence File NG\r\nCannot Check Volume Balance!", "Sequence File NG");
			//	CLOSE_Result_Display();
			//	m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
			//	m_LED_COM_PROCESS = COM_MODE_IDLE;
			//	m_PCB_COM_PROCESS = COM_MODE_IDLE;

			//	m_TaskRun = TASK_RUN_IDLE;
			//	m_cLbOkNg.put_Caption(_T("STOP"));//m_BarCode
			//	m_cLbOkNg.put_BackColor(0x0000FFFF);
			//}
			continue;
		}

		//if(m_nBalanceEnable[i] == 0)
		{
			m_BalanceOK[i] = 1;
			m_nBalanceEnable[i] = 0;
		}

			//		int m_nBalanceEnable[8];
	//int m_nBalanceChannel[8];
	//int m_nBalanceValue[8];

		lOldchOk[i] = m_ChannelOK[i];
			/*int m_VoltageOK[6];
	int m_FrequencyOK[6];*/
		if( ((m_PPVoltage[i] >= m_RefVoltageMin[i])&&(m_PPVoltage[i] <= m_RefVoltageMax[i])) )
		{
			m_VoltageOK[i] = 1;
		}
		else
		{
			m_VoltageOK[i] = 0;
		}

		//if(m_nBalanceEnable[i] == 1)
		//{
		//	double lLarge,lSmall;

		//	if(m_PPVoltage[i] > m_PPVoltage[m_nBalanceChannel[i]])
		//	{
		//		lLarge = m_PPVoltage[i];
		//		lSmall = m_PPVoltage[m_nBalanceChannel[i]];
		//	}
		//	else
		//	{
		//		lLarge = m_PPVoltage[m_nBalanceChannel[i]];
		//		lSmall = m_PPVoltage[i];
		//	}

		//	//if(lLarge*(1+m_nBalanceValue[i]/100.) > lSmall)
		//	if((lLarge - lSmall) > lSmall*(m_nBalanceValue[i]/100.))
		//	{
		//		m_BalanceOK[i] = 0;
		//	}
		//	else
		//	{
		//		m_BalanceOK[i] = 1;
		//	}
		//}
		//else
		{
			m_BalanceOK[i] = 1;
		}


	/*
		if((m_VoltageBalnce[i] > 0)&&(m_VoltageBalnce[i] < 100))
		{
			if( ((m_PPVoltage[i] >= m_RefVoltageMin[i])&&(m_PPVoltage[i] <= m_RefVoltageMax[i])) )
			{
				m_BalanceOK[i] = 1;
			}
			else
			{
				m_VoltageOK[i] = 0;
			}
		}
		*/

		if((m_Frequency[i] >= m_FrequencyMin[i]) &&	(m_Frequency[i] <= m_FrequencyMax[i])&&(m_NoiseFlag[i]==0))
		{
			m_FrequencyOK[i] = 1;
		}
		else
		{
			m_FrequencyOK[i] = 0;
		}
		//if(( ((m_PPVoltage[i] >= m_RefVoltageMin[i])&&(m_PPVoltage[i] <= m_RefVoltageMax[i])) || m_LevelSkip)&&		
		//(m_Frequency[i] >= m_FrequencyMin[i])&&		
		//(m_Frequency[i] <= m_FrequencyMax[i]))
	
		if((m_VoltageOK[i] == 1) && (m_FrequencyOK[i] == 1)&&(m_BalanceOK[i] == 1))
		{
			
			m_ChannelOKCNT[i]++;
//#ifdef __OK_CHECK_FAST_MODE__
//			if(m_ChannelOKCNT[i] > 2)
//#else
//			if(m_ChannelOKCNT[i] > 12)
//#endif
			{
				m_ChannelOK[i] = 1;
			}
		}
		else
		{
			m_ChannelOK[i] = 0;
			m_ChannelOKCNT[i] = 0;
		}

		m_CheckVoltage[i] = m_PPVoltage[i];
		m_CheckFrequency[i] = m_Frequency[i];

	}

	
	

	
}
void CAcqVoltageSamples_IntClkDlg::TestResultDisplay()
{
	int lOldchOk[6];

	for(int i = 0; i < 6; i++)
	{
		if(m_CheckEnable[i])
		{
			if(m_ChannelOK[i] != 1)
			{
				m_ChannelOK[i] = 0;
				if((m_VoltageOK[i] ==  0)||(m_BalanceOK[i] == 0))
				{
					m_VoltLabel[i].put_ForeColor(0x000000ff);
				}
				if(m_FrequencyOK[i] == 0)
				{
					m_FreqLabel[i].put_ForeColor(0x000000ff);
				}

			}
		}
	}

	if((m_CheckEnable[0] )||(m_CheckEnable[1] ))
	{
		if(m_ChannelOK[0] && m_ChannelOK[1])
		{
		//	m_cLb_Test1.put_Caption(_T("O K"));
		/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test1.put_Caption(_T("O K 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test1.put_Caption(_T("O K 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test1.put_Caption(_T("O K 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test1.put_Caption(_T("O K 4"));
			}*/
		//	m_cLb_Test1.put_BackColor(0x0000FF00);
		}
		else
		{
		//	m_cLb_Test1.put_Caption(_T("N G"));
		/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test1.put_Caption(_T("N G 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test1.put_Caption(_T("N G 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test1.put_Caption(_T("N G 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test1.put_Caption(_T("N G 4"));
			}*/
		//	m_cLb_Test1.put_BackColor(0x000000FF);
		}
		
	}
	if((m_CheckEnable[2] )||(m_CheckEnable[3] ))
	{
		
		if(m_ChannelOK[2] && m_ChannelOK[3])
		{
		//	m_cLb_Test2.put_Caption(_T("O K"));
	/*		if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test2.put_Caption(_T("O K 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test2.put_Caption(_T("O K 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test2.put_Caption(_T("O K 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test2.put_Caption(_T("O K 4"));
			}*/
		//	m_cLb_Test2.put_BackColor(0x0000FF00);
		}
		else
		{
		//	m_cLb_Test2.put_Caption(_T("N G"));
		/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test2.put_Caption(_T("N G 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test2.put_Caption(_T("N G 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test2.put_Caption(_T("N G 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test2.put_Caption(_T("N G 4"));
			}*/
		//	m_cLb_Test2.put_BackColor(0x000000FF);
		}
		
	}

	if((m_CheckEnable[4] )||(m_CheckEnable[5] ))
	{
		
		if(m_ChannelOK[4] && m_ChannelOK[5])
		{
		//	m_cLb_Test3.put_Caption(_T("O K"));
	/*		if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test3.put_Caption(_T("O K 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test3.put_Caption(_T("O K 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test3.put_Caption(_T("O K 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test3.put_Caption(_T("O K 4"));
			}*/
		//	m_cLb_Test3.put_BackColor(0x0000FF00);
		}
		else
		{
		//	m_cLb_Test3.put_Caption(_T("N G"));
	/*		if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
			{
				m_cLb_Test3.put_Caption(_T("N G 1"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
			{
				m_cLb_Test3.put_Caption(_T("N G 2"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
			{
				m_cLb_Test3.put_Caption(_T("N G 3"));
			}
			else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
			{
				m_cLb_Test3.put_Caption(_T("N G 4"));
			}*/
		//	m_cLb_Test3.put_BackColor(0x000000FF);
		}
		
	}
}

void CAcqVoltageSamples_IntClkDlg::TestFinishGMES()
{
	//ULONG lSetVal = 0x00;
	//CFileControl lFile;//SAVE LOG
	//lFile.ReadCountData();
	

	CString LogStr;
	CString StrTmp;
	CString sTmp;
	CString StrTestTime;
	LogStr = "TEST Result://";
	for(int i = 0; i < StepList.GetSize(); i++)
	{
		StrTestTime = m_CtrlListMainProcess.GetItemText(m_nCurrentNumber, 3);
		if(m_CtrlListMainProcess.GetCheck(i) == 1)
		{
			StrTmp = m_CtrlListMainProcess.GetItemText(i, 1); ;// gTestSeqData.TestStepList[i].strStepName;
			StrTmp += ": ";
			StrTmp += StrTestTime;
			StrTmp += ": s";
			if(m_CtrlListMainProcess.GetItemText(i, 2) == "NG")//gTestSeqData.TestStepList[i].m_Result == 0)
			{
				StrTmp +=  ":NG //";
				LogStr += StrTmp;
				m_TEST_Result = 0;
				break;
			}
			else
			{
				StrTmp +=  ":OK //";
				LogStr += StrTmp;
				m_TEST_Result = 1;
			}
		}
	}

			
	StrTmp = "// Total Time: ";
	StrTestTime =  m_CheckTimeLabel.get_Caption();
	StrTmp += StrTestTime;
	StrTmp += "s //";
	StrTmp += "Total Result: ";
	if(m_TEST_Result == 1)
	{
		StrTmp += " O K ";
	}
	else
	{
		StrTmp += " N G ";
	}
	LogStr += StrTmp;
	AddProcessLog( LogStr);

	gSaveInfo.bMesSts = 0;
	if(m_GMES_CommError == 0)
	{
		GMES_Result_ReportSend();
	}
	else
	{
	}
	

	m_TaskRun = TASK_FINISH_PROCESS;
		
}

void CAcqVoltageSamples_IntClkDlg::TestFinish()
{
	if (gbManualRefMode == 1)
	{
		gbManualRefMode = 0;
		return;
	}
	ULONG lSetVal = 0x00;
	CFileControl lFile;//SAVE LOG
	lFile.ReadCountData();
//	CLOSE_Result_Display();
	
	for(int i = 0; i < gTestSeqData.TestCnt; i++)
	{
		if(gTestSeqData.TestStepList[i].m_Result == 0)
		{
			m_TEST_Result = 0;
			break;
		}
		else
		{
			m_TEST_Result = 1;
		}
	}

	if(m_GMES_CommError == 1)
	{
		m_TEST_Result = 0;
	}

	if(m_TEST_Result == 1)
	{
		lSetVal = 0x01;
		MessageDisplay(0, "SEND OK SIGNAL!!");
		gSaveInfo.strTestResult = _T("OK");
		g_nOKCnt++;
		m_cLbOkNg.put_Caption(_T("O K"));
		m_cLbOkNg.put_BackColor(0x0000FF00);	

		SendOkSignalToJig();//Back Jig
		CycleTimeOn = 0;
		OK_Display();
		//Beep(800, 300);
		
		CString m_NgWaveFile  = _T(PATH_BASE_DIR);
		m_NgWaveFile  += _T("\\Sound\\OK_CHECK.wav");//OK_CHECK.wav
		sndPlaySound( m_NgWaveFile , SND_ASYNC);

		
	
	}
	else
	{
		lSetVal = 0x02;
		MessageDisplay(1, "SEND NG SIGNAL!!");
		gSaveInfo.strTestResult = _T("NG");
		g_nNGCnt++;
				
						
		m_cLbOkNg.put_Caption(_T("N G"));
		m_cLbOkNg.put_BackColor(0x000000FF);	

		CycleTimeOn = 0;
		SendOkSignalToJig();//Back Jig

		//NG_Display();
		//CLOSE_Result_Display();
		
	}

	CString str;
	unsigned long lCheck_Time = GetTimeCheck(4);
	str.Format(_T("%4.1f (s)   "), lCheck_Time/1000.0);
	m_CheckTimeLabel.put_Caption(str);
	m_stcTime.SetWindowText(str);//

	CString str1;
	str1 = m_CheckTimeLabel.get_Caption();
	str1 = str1.Left(str1.Find(" (s)"));	
	gSaveInfo.CheckTime = _ttof(str1);

	str1 = m_CycleTimeLabel.get_Caption();
	str1 = str1.Left(str1.Find(" (s)"));		
	gSaveInfo.CycleTime  = _ttof(str1);
	//if(m_GMES_CommError == 0)
	//{
	//	GMES_Result_ReportSend();
	//	gSaveInfo.bMesSts = 1;
	//}
	//else
	//{
	//	gSaveInfo.bMesSts = 0;
	//}
	SetD_OUT(lSetVal);

	SetTimeCheck(3);

	gSaveInfo.strModelName = gTestSeqData.strModelName;
//	gSaveInfo.bMesSts = MesTestReport();
	//gSaveInfo.strTestResult = _T("OK");
	gSaveInfo.strWipID_SetSN = g_strSetID;
	
	//gCableManager.nUSB_CableCount
	
	lFile.SaveLog();

	if((gTestSeqData.strModelName.Find("CM4") >= 0)||(gTestSeqData.strModelName.Find("CM5") >= 0))
	{
		CString str;
		int lcountError = 0;
		
		gCableManager.nUSB_CableCount++;
		gCableManager.nPort_CableCount++;
		if(gCableManager.nUSB_CableCount >= gCableManager.nUSB_CableCountMax)
		{
			str = _T("Change USB Cable \r\n");
			m_cLabelCableMessage.put_BackColor(0x000080FF);
			lcountError++;
		}

		if(gCableManager.nPort_CableCount >= gCableManager.nPort_CableCountMax)
		{
			str += _T("Change Portable Cable \r\n");
			m_cLabelCableMessage.put_BackColor(0x000080FF);
			lcountError++;
		}



		if(gTestSeqData.strModelName.Find("CM4") >= 0)
		{
			gCableManager.nCM4CheckerCount++;
			if(gCableManager.nCM4CheckerCount >= gCableManager.nCM4CheckerCountMax)
			{
				str += _T("Change CM4 Checker Pin \r\n");
				m_cLabelCableMessage.put_BackColor(0x000080FF);
				lcountError++;
			}
		}
		else if(gTestSeqData.strModelName.Find("CM5") >= 0)
		{
			gCableManager.nCM5CheckerCount++;
			gCableManager.nMIC_CableCount++;
			if(gCableManager.nCM5CheckerCount >= gCableManager.nCM5CheckerCountMax)
			{
				str += _T("Change CM5 Checker Pin \r\n");
				m_cLabelCableMessage.put_BackColor(0x000080FF);
				lcountError++;
			}
			if(gCableManager.nMIC_CableCount >= gCableManager.nMIC_CableCountMax)
			{
				str += _T("Change MIC Cable \r\n");
				m_cLabelCableMessage.put_BackColor(0x000080FF);
				lcountError++;
			}		
		
		}

		if(lcountError > 0)
		{
		}
		else
		{
			m_cLabelCableMessage.put_BackColor(0x0000FF00);
			str += _T("\r\n\r\Check Cable OK\r\n");
		}
		m_cLabelCableMessage.put_Caption(str);

		lFile.SaveCableCountData();
	}
	


	
	//m_Check_Time = lCheck_Time/1000.0;

	CheckTimeOn = 0;
	//CycleTimeOn = 1;

	str.Format(_T("%d"), g_nOKCnt);	
	m_OKCntLabel.put_Caption(str);

	str.Format(_T("%d"), g_nNGCnt);	
	m_NGCntLabel.put_Caption(str);
	lFile.SaveCountData();
	if(CurrentSet->bGMES_Connection)
	{
		m_BarCode.put_Caption("");
	}
	
	m_TaskRun = TASK_RUN_IDLE;
}

//m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
//						m_LED_COM_PROCESS = COM_MODE_IDLE;
//						m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//						//m_EthernetMode = 
//
//						m_NG_WaitFlag = 0;
//						//TestFinishGMES();//
//						TestFinish();

void CAcqVoltageSamples_IntClkDlg::CheckTotalOK()
{
	
	if(m_TotalOK == 1)
	{
	/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
		{
			m_cLbOkNg.put_Caption(_T("O K 1"));
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
		{
			m_cLbOkNg.put_Caption(_T("O K 2"));
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
		{
			m_cLbOkNg.put_Caption(_T("O K 3"));
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
		{
			m_cLbOkNg.put_Caption(_T("O K 4"));
		}*/
	
		//m_cLbOkNg.put_Caption(_T("O K"));
		m_cLbOkNg.put_BackColor(0x0000FF00);

		//m_TEST_Result = 1;
	}
	else
	{
		/*if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
		{
			m_cLbOkNg.put_Caption(_T("N G 1"));
			m_NG_OK_Num = 1;
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
		{
			m_cLbOkNg.put_Caption(_T("N G 2"));
			m_NG_OK_Num = 2;
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
		{
			m_cLbOkNg.put_Caption(_T("N G 3"));
			m_NG_OK_Num = 3;
		}
		else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
		{
			m_cLbOkNg.put_Caption(_T("N G 4"));
			m_NG_OK_Num = 4;
		}*/
		//m_cLbOkNg.put_Caption(_T("N G"));
		m_cLbOkNg.put_BackColor(0x000000FF);	
	//	m_TEST_Result = 0;
		//TestFinish();

		
	}

	TestResultDisplay();
	

}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedSetupButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	if(m_TaskRun != TASK_RUN_IDLE) 
	{
		MessageBox("TEST PROCESSING");
		return;
	}

	SM_ModelOpen();
	return;

//
//	CFileControl lFile;
//
//
//	CDlgPassword dlgpw;
//
//	dlgpw.m_sPassword = g_strPassword;
//#ifdef _SM_DEBUG
//	if (1)
//	{
//		if (1)
//		{
//#else
//	if(dlgpw.DoModal()==IDOK)
//	{		
//		if(g_strPassword == dlgpw.m_sPassword)
//		{
//#endif	
//			CString str = _T("");
//			DlgModelSetupSeq dlg;
//		//	CDlgModelSetup dlg;
//			m_Camera_Capture_Flag = 0;//
//
//			if(m_ComPort.mPort_Opened == TRUE)
//				m_ComPort.ClosePort();
//		
//			if(m_ComPortPCB.mPort_Opened == TRUE)
//				m_ComPortPCB.ClosePort();
//		
//			//if(m_ComPortLED.mPort_Opened == TRUE)
//			//	m_ComPortLED.ClosePort();
//		
//
//			int lrtn = dlg.DoModal();
//			if((lrtn == IDOK)||(lrtn == IDCANCEL))
//			{
//
//				LoadTestData(gTestSeqData.strSeqFileName);
//
//				//SetListControl();
//				DisplayTestData();
//		
//				//m_TextModel.put_Text(gTestSeqData.strModelName);	
//
//				CFileControl lFile;
//				lFile.SaveINIModel();
//				lFile.OpenModel(gTestSeqData.strModelName);
//
//				CheckDigitalPort();
//				GetRmtCodeList(CurrentSet->sRemoconTitle);
//
//				////str = _T("MODEL : ");
//				str = gTestSeqData.strModelName;
//				//m_TextModel.put_Text(str);
//				m_cLbModel.put_Caption((LPCSTR)str);
//				m_DO_Writedata = 0;
//				if(gbManualScopeMode == 0)
//				{
//					SetChannelData(0);
//					InitChannel();
//				}
//
//				if(CurrentSet->bGMES_Connection)
//				{			
//					CloseEthernetScocket() ;
//					m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
//					m_EthernetWaitCnt = 0;
//					g_nPortReopen = 0;
//					CurrentSet->bGMES_Connection = 1;			
//				}
//			}
//
//	
//		//	if(g_CameraFound == 1)
//		//		m_Camera_Capture_Flag = 1;//m_Camera_Capture_Flag = 1;
//
//		
//			OpenComport();
//			OpenComportPCB();
////			OpenComportLED();
//			OpenComportSCAN();
//		//	CString str;
//			if(m_ComPort.mPort_Opened== FALSE)
//			{
//				str = _T("MAIN COM Port");
//				str += CurrentSet->sAvSwitchBoxComPort;
//				str += _T(" Open FAIL !!");
//
//	
//				MessageDisplay(1, str); //MessageBox(str);
//			}
//			if(m_ComPortPCB.mPort_Opened == FALSE)
//			{	
//				str = _T("SET UART COM Port");
//				str += CurrentSet->sTVComPort;
//				str += _T(" Open FAIL !!");
//				
//				MessageDisplay(1, str); //MessageBox(str);
//			}
//	
//			//if(m_ComPortLED.mPort_Opened == FALSE)
//			//{
//			//	str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);		
//			//	MessageBox(str);
//			//}
//	
//			if(m_ComPortScanner.mPort_Opened == FALSE)
//			{	
//				if(g_CheckUseUSB_Scanner == 0)
//				{
//		
//		
//					str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);		
//					MessageDisplay(1, str); //MessageBox(str);
//				}
//			}
//
//			OnBnClickedButtonFreqSet();
//		}
//		else
//		{
//			g_strPassword = dlgpw.m_sPassword;
//			lFile.Save_ConfigPassword();
//		}
//	}
//
//#endif
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedTestButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_TaskRun != TASK_RUN_IDLE) 
	{
		MessageBox("TEST PROCESSING");
		return;
	}
//	m_Camera_Capture_Flag = 0;
	CDlgTestPage dlg;
	if(m_ComPort.mPort_Opened == TRUE)
		m_ComPort.ClosePort();
		
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
		
	//if(m_ComPortLED.mPort_Opened == TRUE)
	//	m_ComPortLED.ClosePort();
		
	

	if(dlg.DoModal() == IDOK)
	{
	}
	OpenComport();
	OpenComportPCB();
//	OpenComportLED();
	OpenComportSCAN();
	CString str;
	if(m_ComPort.mPort_Opened== FALSE)
	{
		str = _T("MAIN COM Port");
		str += CurrentSet->sAvSwitchBoxComPort;
		str += _T(" Open FAIL !!");
	//	str.Format(_T("MAIN COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
	
		MessageDisplay(1, str);
	}
	if(m_ComPortPCB.mPort_Opened == FALSE)
	{	
		//str.Format(_T("Audio COM Port %d Open FAIL !!"),  gTestSeqData.nPort_Pcb);
		str = _T("SET UART COM Port");
		str += CurrentSet->sTVComPort;
		str += _T(" Open FAIL !!");
		MessageDisplay(1, str); //MessageBox(str);
	}
	
	//if(m_ComPortLED.mPort_Opened == FALSE)
	//{
	//	str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);		
	//	MessageBox(str);
	//}
	
	//if(m_ComPortScanner.mPort_Opened == FALSE)
	//{	
	//	if(g_CheckUseUSB_Scanner == 0)
	//	{		
	//		str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);		
	//		MessageDisplay(1, str); //MessageBox(str);
	//	}
	//}

	//if(g_CameraFound == 1)
	//	m_Camera_Capture_Flag = 1;
	//for(int i = 0; i< 6; i++)
	//			m_graph[i].Plots.RemoveAll();
	if(gbManualScopeMode == 0)
	{
//		InitClearChannel();
	}
	OnBnClickedButtonFreqSet();

}

void CAcqVoltageSamples_IntClkDlg::MessageDisplay(int lError, CString sMessage)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MessageDisplay.put_Caption(sMessage);

	if(lError == 0)
	{
		m_MessageDisplay.put_ForeColor(0x00FF0000);
	}
	else if(lError == 1)
	{
		m_MessageDisplay.put_ForeColor(0x000000FF);
	}
	else if(lError == 2)
	{
		m_MessageDisplay.put_ForeColor(0x0000FFFF);
	}
	AddProcessLog(sMessage);
}

void	CAcqVoltageSamples_IntClkDlg::SendData(BYTE *lbuf, int lcnt, int lComID_Port)
{

	//02 M nn [dd:"TransData dd Byte"] 03 0d 0a
	m_MainPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_ComAck =COM_ACK_WAIT;
	m_ComWaitCnt = 0;
	m_ResendCnt = 0;


	m_SendBuf[0] = 0x02;
	m_SendBuf[1] = 'M';
	m_SendBuf[2] = lcnt / 10 + 0x30;
	m_SendBuf[3] = lcnt % 10 + 0x30;
	m_SendBuf[4] = '[';
	m_SendBuf[5] = lComID_Port / 10 + 0x30;
	m_SendBuf[6] = lComID_Port % 10 + 0x30;
	m_SendBuf[7] = ':';

	memcpy(&m_SendBuf[8], lbuf, lcnt); 
	m_SendBuf[lcnt + 8] = ']';
	m_SendBuf[lcnt + 9] = 0x03;


	m_SendCnt = lcnt+10;
	ComSend();
	m_Main_COM_ID = lComID_Port;
	m_Main_RcvCOM_ID = 0;
	if(m_NoAckMainCom == 1)
	{
		m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
	}
}


void	CAcqVoltageSamples_IntClkDlg::SendData(BYTE *lbuf, int lcnt)
{
	if (g_SetComOnlyMode == 1)
	{
		return;
	}

	m_MainPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_ComAck = COM_ACK_WAIT;
	m_ComWaitCnt = 0;
	m_ResendCnt = 0;

	memcpy(m_SendBuf, lbuf, lcnt);
	m_SendCnt = lcnt;
	ComSend();
	m_Main_COM_ID = 0;
	if (m_NoAckMainCom == 1)
	{
		m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
	}
}


void CAcqVoltageSamples_IntClkDlg::ComSend()//void CAcqVoltageSamples_IntClkDlg::OpenComport()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	CString strMsg;
	CString strTmp ;
	if(m_ComPort.mPort_Opened)
	{
		
		m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);

	
	}
	else
	{
		OpenComport();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPort.mPort_Opened)
		{
			
			m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
			
		}
		else
		{
			//MessageBox(_T("Com Port Not Opened !!"));
			return;
		}
		
	}
	
	strMsg = ">> ";

	for (int i = 0; i < m_SendCnt; i++)
	{
		if ((m_SendBuf[i] < 0x20)||(m_SendBuf[i] > 0x7F))
		{
			strTmp.Format("x%02X", m_SendBuf[i]);
			strMsg += strTmp;
		}
		else
		{
			//strTmp.SetAt(0,)
			strMsg += m_SendBuf[i];
		}
		if (strMsg.GetLength() > 30)
		{
			ComLog_AddString(strMsg);
			strMsg = "";
		}


	}
	ComLog_AddString(strMsg);

}

void CAcqVoltageSamples_IntClkDlg::ComPCBSend()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	TVCommCtrl.m_ReadComplete = 0;
	if(m_ComPortPCB.mPort_Opened)
	{
		
		m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
		CFileControl lfile;
			CString str; 
			m_SendBufPCB[m_SendCntPCB] = 0;
			AddPCBLog(m_SendBufPCB, m_SendCntPCB, 0);
	}
	else
	{
		OpenComportPCB();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPortPCB.mPort_Opened)
		{
			
			m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
			CFileControl lfile;
			CString str; 
			m_SendBufPCB[m_SendCntPCB] = 0;
			AddPCBLog(m_SendBufPCB, m_SendCntPCB, 0);
			
		}
	}

	SetTimeCheck(_CHECK_TIME_PCB_COM_ID);
}


void CAcqVoltageSamples_IntClkDlg::OpenComport()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	if(g_SetComOnlyMode == 1)
	{
		return;
	}
	CString str;
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
	if(m_ComPort.InitPort(this, _ttoi(CurrentSet->sAvSwitchBoxComPort.Mid(CurrentSet->sAvSwitchBoxComPort.Find("COM")+3)),
		CurrentSet ->wAvSwitchBoxBaudRate, 'N', 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPort.StartMonitoring();
		m_cLb_ComMain.put_BackColor(0x00FFFF);
	}
	else
	{
		m_cLb_ComMain.put_BackColor(0x0001FF);
		str.Format(_T("MAIN COM Port %d Open FAIL !!"), CurrentSet->sAvSwitchBoxComPort);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}
	AvSwitchBoxCtrl.m_bPortOpen = m_ComPort.mPort_Opened;
}

void CAcqVoltageSamples_IntClkDlg::OpenComportPCB()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	if(CurrentSet->nTVParity > 4)
	{
		CurrentSet->nTVParity = 1;
	}

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
	if(m_ComPortPCB.InitPort(this, _ttoi(CurrentSet->sTVComPort.Mid(CurrentSet->sTVComPort.Find("COM") + 3)), 
		CurrentSet->wTVBaudRate, lParityChar[CurrentSet->nTVParity], 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPortPCB.StartMonitoring();
	}
	else
	{
		str = _T("UART Port ");
		str += CurrentSet->sTVComPort;
		str += _T(" Open FAIL !!");

		//str.Format(_T("Audio COM Port %d Open FAIL !!"),  gTestSeqData.nPort_Pcb);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}

	m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
}
//
//void CAcqVoltageSamples_IntClkDlg::OpenComportLED()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
//{
//	if(g_SetComOnlyMode == 1)
//	{
//		return;
//	}
//	CString str;
//	char lParityChar[3] = {'N', 'E', 'O'};
//
//	if(g_nParity_LED > 2)
//	{
//		g_nParity_LED = 0;
//	}
//	if(m_ComPortLED.mPort_Opened)
//	{
//		m_ComPortLED.ClosePort();
//	}
////	if(m_ComPortLED.InitPort(this, g_nPort_LED, g_nBaud_LED, 'N', 8, 1, EV_RXCHAR, 4096 ))
//	if(m_ComPortLED.InitPort(this, g_nPort_LED, g_nBaud_LED, lParityChar[g_nParity_LED], 8, 1, EV_RXCHAR, 4096 ))
//	{		
//		m_ComPortLED.StartMonitoring();
//	}
//	else
//	{
//		str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);
//		//MessageBox(str);
//		MessageDisplay(1, str);
//		/*StatusDisplayMsg(str, 1 );*/
//		//MessageBox(str);
//	}
//
//	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_LED;
//}


void CAcqVoltageSamples_IntClkDlg::OpenComportSCAN()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	if(g_SetComOnlyMode == 1)
	{
		return;
	}

	
	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	//if(g_nParity_Scanner > 2)
	//{
	//	g_nParity_LED = 0;
	//}
	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}
	if (m_ComPortScanner.InitPort(this, _ttoi(CurrentSet->sScannerComPort.Mid(CurrentSet->sScannerComPort.Find("COM") + 3)),
		CurrentSet->wScannerBaudRate, lParityChar[0], 8, 1, EV_RXCHAR, 4096))
	{
		m_ComPortScanner.StartMonitoring();
	}	
	else
	{
		str.Format(_T("SCANNER  COM Port %d Open FAIL !!"), CurrentSet->sScannerComPort, CurrentSet->wScannerBaudRate);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}
	m_ComPortScanner.m_RxMessageID = WM_COMM_RXCHAR_SCAN;
}

long CAcqVoltageSamples_IntClkDlg::OnRefreshAudioData(WPARAM wParam, LPARAM lParam)
{
	//UINT16 lbuf[51200];
	int lcnt;
	UINT lFramesumcnt;
	//static UINT m_AudioCountBuf[3072];

	

	//memcpy(lCountBuf, (void *)wParam, sizeof(lCountBuf));
	
	lFramesumcnt = 		(UINT)wParam;
	lcnt = (int)lFramesumcnt;// &0xFFFF;
	//lFramesumcnt = lFramesumcnt >> 16;

	//if (lcnt < 0) || (lcnt > AUDIO_CHANNEL_NO * 1600 * 2))
	if (lcnt < 25600) 
		return 0;

	//if (m_AudioFameCount >= DECK_HDMI_SAMPLE_COUNT)
	//	m_AudioFameCount = 0;

	//m_AudioCountBuf[m_AudioFameCount] = lFramesumcnt;
	//m_AudioFameCount++;

	////if (m_HdmiAudioCount >= DECK_HDMI_SAMPLE_COUNT)
	//if (m_HdmiAudioCount >= m_AudioFameCount)
	//	return 0;

	//if ((m_HdmiAudioCount < 0) || (m_HdmiAudioCount > DECK_HDMI_SAMPLE_COUNT))
	//	m_HdmiAudioCount = 0;
	//if (m_AudioFameCount >= 4)
	//{
	//	if (m_HdmiAudioCount == 0)
	//		m_AudioFameCount = 0;
	//	return 0;
	//}
	lcnt = (lcnt > 25600) ? 25600: lcnt;
	memcpy(m_HdmiAudioDataBuf, (void *)lParam, lcnt);
	//memcpy(m_HdmiAudioDataBuf, lbuf, 12800*4);
	//m_AudioFameCount++;
	if (lcnt == 25600)
	{
		m_HdmiAudioCount = 0;
		for (int i = 1; (i < 1600); i++)
		{
			if (i % 800 == 0)
				continue;
			for (int k = 0; k < 8; k++)
			{
				m_HdmiAudioData[k][m_HdmiAudioCount] = m_HdmiAudioDataBuf[i * 8 + k];
			//	m_HdmiAudioData[k][m_HdmiAudioCount] = m_HdmiAudioDataBuf[i * AUDIO_CHANNEL_NO + k];
			}
			m_HdmiAudioCount++;

			//if (m_HdmiAudioCount >= DECK_HDMI_SAMPLE_COUNT)
			//{
			//	//m_HdmiAudioCount = 0;
			//	break;
			//}
		}
		
		m_AudioFameCount = 4;
	}

	
	//for (int i = 0;  (i < 800); i++)
	////for (int i = 0; (i < 800); i++)
	//{
	//	for (int k = 0; k < 1; k++)
	//	{
	//		m_HdmiAudioData[k][m_HdmiAudioCount] = lbuf[i * AUDIO_CHANNEL_NO + k];
	//	}
	//	m_HdmiAudioCount++;

	//	if (m_HdmiAudioCount >= DECK_HDMI_SAMPLE_COUNT)
	//	{
	//		//m_HdmiAudioCount = 0;
	//		break;
	//	}
	//}
	//if (m_HdmiAudioCount >= DECK_HDMI_SAMPLE_COUNT)
	//	m_HdmiAudioCount = 0;
	//UINT m_HdmiAudioData[8][DECK_HDMI_SAMPLE_COUNT];

	return 0;
}
void CAcqVoltageSamples_IntClkDlg::GetNextData(int lCnt)
{
	CString str;
	CString StrTmp;

	StrTmp = "DFT->PC:";
	for (int i = 0; i < lCnt; i++)
	{
		if (m_RecvBuf[i] > 0x20)
		{
			str.Format("%c", m_RecvBuf[i]);
		}
		else
		{
			str.Format("\\%02Xx", m_RecvBuf[i]);
		}

		StrTmp += str;
	}
	StrTmp += "\n";
	//TRACE(StrTmp);


	BYTE lbuf[4096];
	if (m_RecvCnt > lCnt)
	{
		int lRevCnt = m_RecvCnt - lCnt;
		memcpy(lbuf, &(m_RecvBuf[lCnt]), lRevCnt);
		for (int i = 0; i < lRevCnt; i++)
		{
			if (lbuf[i] == 0x02)
			{
				m_RecvCnt = lRevCnt - i;
				memcpy(m_RecvBuf, lbuf, m_RecvCnt);
				return;
			}
		}
	}
	m_RecvCnt = 0;
}
void CAcqVoltageSamples_IntClkDlg::FindNextStart(int lCnt)
{
	CString str;
	CString StrTmp;


	BYTE lbuf[4096];
	if (m_RecvCnt >= lCnt)
	{
		//	int lRevCnt = m_RecvCnt - lCnt;
		//	memcpy(lbuf, &(m_RecvBuf[lCnt]), lRevCnt);
		for (int i = 1; i < lCnt; i++)
		{
			if (m_RecvBuf[i] == 0x02)
			{
				m_RecvCnt = m_RecvCnt - i;
				memcpy(m_RecvBuf, &m_RecvBuf[i], m_RecvCnt);
				return;
			}
		}
	}
	m_RecvCnt = 0;
}

long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	BYTE lbuf[4096];
	BYTE lDatabuf[4096];
	int lcnt;
	static int sUsingBuf = 0;

	CString strMsg;
	CString strTmp;


	lcnt = (int)wParam;
	memcpy(lbuf,(void *)lParam,lcnt);

	
	if ((m_RecvCntTemp < 0) || (m_RecvCntTemp > 4095))
		m_RecvCntTemp = 0;


	for (int i = 0; i < lcnt; i++)
	{
		m_RecvBufTemp[m_RecvCntTemp++] = lbuf[i];
		if (m_RecvCntTemp > 4095)
			m_RecvCntTemp = 0;
	}
		
	if (sUsingBuf == 1)
	{
		return 0;
	}
	sUsingBuf = 1;

	if((m_RecvCnt < 0)||(m_RecvCnt > 4095))
		m_RecvCnt = 0;


	for(int i = 0; i < m_RecvCntTemp; i++)
	{
		m_RecvBuf[m_RecvCnt++] = m_RecvBufTemp[i];
		if(m_RecvCnt > 4095)
			m_RecvCnt = 0;
	}
	m_RecvCntTemp = 0;

	while(m_RecvCnt > 2)
	{
		
		if(m_RecvBuf[0] == 0x02)
		{
			if(m_RecvCnt >= 10)
			{

				if ((m_RecvBuf[1] == 'M') && (m_RecvBuf[4] == '[') && (m_RecvBuf[7] == ':'))//if (strncmp((char *)&m_RecvBuf[1], "M", 1) == 0)
				{
					//02 M nn [dd:"TransData dd Byte"] 03 0d 0a
					int lDataCount = (m_RecvBuf[2] - 0x30) * 10 + m_RecvBuf[3] - 0x30;
					if (m_RecvCnt >= lDataCount + 10)
					{						
						int lPortID = (m_RecvBuf[5] - 0x30) * 10 + m_RecvBuf[6] - 0x30;
						m_Main_RcvCOM_ID = lPortID;

						if (m_Main_COM_ID == m_Main_RcvCOM_ID)
						{
							m_ComAck = COM_ACK_OK;
							if (AvSwitchBoxCtrl.m_nAvSwitchWaitFlag == 1)
							{
								memcpy(AvSwitchBoxCtrl.m_strReceive, m_RecvBuf, m_RecvCnt);
								AvSwitchBoxCtrl.m_nReceiveCount = m_RecvCnt;
								AvSwitchBoxCtrl.m_nAvSwitchWaitFlag = 0;
							}
						}
						memcpy(lDatabuf, &m_RecvBuf[8], lDataCount);

						strMsg = "<< ";
						for (int i = 0; i < m_RecvCnt; i++)
						{
							if ((m_RecvBuf[i] < ' ') || (m_RecvBuf[i] > 'z'))
							{
								strTmp.Format("x%02X", m_RecvBuf[i]);
								strMsg += strTmp;
							}
							else
							{
								//strTmp.SetAt(0,)
								strMsg += m_RecvBuf[i];
							}
							if (strMsg.GetLength() > 30)
							{
								ComLog_AddString(strMsg);
								strMsg = "";
							}
						}
						//strMsg += "";
						ComLog_AddString(strMsg);
						
						m_RecvCnt = 0;
					}
					else
					{
						break;
					}
				}
				else if(strncmp((char *)&m_RecvBuf[1], "DREADY", 6) == 0)
				{
					if (AvSwitchBoxCtrl.m_nAvSwitchWaitFlag == 1)
					{
						memcpy(AvSwitchBoxCtrl.m_strReceive, m_RecvBuf, m_RecvCnt);
						AvSwitchBoxCtrl.m_nReceiveCount = m_RecvCnt;
						AvSwitchBoxCtrl.m_nAvSwitchWaitFlag = 0;
					}
					if (m_Main_COM_ID == 0)
					{
						m_ComAck = COM_ACK_OK;
					}
					strMsg = "<< ";
					for (int i = 0; i < m_RecvCnt; i++)
					{
						if ((m_RecvBuf[i] < ' ') || (m_RecvBuf[i] > 'z'))
						{
							strTmp.Format("x%02X", m_RecvBuf[i]);
							strMsg += strTmp;
						}
						else
						{
							//strTmp.SetAt(0,)
							strMsg += m_RecvBuf[i];
						}
						if (strMsg.GetLength() > 30)
						{
							ComLog_AddString(strMsg);
							strMsg = "";
						}
					}
					//strMsg += "";
					ComLog_AddString(strMsg);

					m_RecvCnt = 0;
					m_cLb_ComMain.put_BackColor(0x00FF00);
				}
				else if(strncmp((char *)&m_RecvBuf[1], "DBUSY ", 6) == 0)
				{
					if (AvSwitchBoxCtrl.m_nAvSwitchWaitFlag == 1)
					{
						memcpy(AvSwitchBoxCtrl.m_strReceive, m_RecvBuf, m_RecvCnt);
						AvSwitchBoxCtrl.m_nReceiveCount = m_RecvCnt;
						AvSwitchBoxCtrl.m_nAvSwitchWaitFlag = 0;
					}
					m_ComAck = COM_ACK_BUSY;
					strMsg = "<< ";
					for (int i = 0; i < m_RecvCnt; i++)
					{
						if ((m_RecvBuf[i] < ' ') || (m_RecvBuf[i] > 'z'))
						{
							strTmp.Format("x%02X", m_RecvBuf[i]);
							strMsg += strTmp;
						}
						else
						{
							//strTmp.SetAt(0,)
							strMsg += m_RecvBuf[i];
						}
						if (strMsg.GetLength() > 30)
						{
							ComLog_AddString(strMsg);
							strMsg = "";
						}
					}
					//strMsg += "";
					ComLog_AddString(strMsg);
					m_RecvCnt = 0;
					m_cLb_ComMain.put_BackColor(0x00FF00);
				}
				else if (strncmp((char *)&m_RecvBuf[1], "DV", 2) == 0)
				{
					if (m_RecvCnt >= 13)
					{
						m_cLb_ComMain.put_BackColor(0x00FF00);
						

						strMsg = "<< ";

						for (int i = 0; i < m_RecvCnt; i++)
						{
							if ((m_RecvBuf[i] < 0x20)|| (m_RecvBuf[i] > 0x7F))
							{
								strTmp.Format("x%02X", m_RecvBuf[i]);
								strMsg += strTmp;
							}
							else
							{
								//strTmp.SetAt(0,)
								strMsg += m_RecvBuf[i];
							}

						}
						ComLog_AddString(strMsg);


						if (m_RecvBuf[10] == 0x03)
						{
							m_ComAck = COM_ACK_OK;
							m_ReadMIOComAck = COM_ACK_OK;
							m_ReadVoltID = (m_RecvBuf[3] - 0x30) * 10 + m_RecvBuf[4] - 0x30;
							m_RecvBuf[10] = 0;
							m_ReadVoltData = atoi((char *)&(m_RecvBuf[5]))/100.0;	
							if ((m_ReadVoltID >= 0) && (m_ReadVoltID < 32))
								g_ReadVoltData[m_ReadVoltID] = m_ReadVoltData;
						}
						else
						{
							m_ComAck = COM_ACK_BUSY;
							m_ReadMIOComAck = COM_ACK_BUSY;
						}
						
						m_RecvCnt = 0;
					}
					else
					{
						break;
					}
				}
				else if (strncmp((char *)&m_RecvBuf[1], "DI", 2) == 0)
				{
					//if ((m_RecvCnt >= 15)&&((char)m_RecvBuf[12] == 0x03))
					//int m_ComType = _NEW_DFT_24PORT_MODE;
					int m_ComRcvByte = 3;
					if (m_RecvCnt >= 13)
					{
						if ((char)m_RecvBuf[10] == 0x03)
						{
							m_ComRcvByte = 2;
						}
						else if ((char)m_RecvBuf[12] == 0x03)
						{
							if (m_RecvCnt >= 15)
							{
								m_ComRcvByte = 3;
							}
							else
							{
								break;
							}
						}

						m_cLb_ComMain.put_BackColor(0x00FF00);

						m_ComAck = COM_ACK_OK;
						m_ReadMIOComAck = COM_ACK_OK;
						strMsg = "<< ";

						for (int i = 0; i < m_RecvCnt; i++)
						{
							if ((m_RecvBuf[i] < 'A') || (m_RecvBuf[i] > 'Z'))
							{
								strTmp.Format(" %02X", m_RecvBuf[i]);
								strMsg += strTmp;
							}
							else
							{
								//strTmp.SetAt(0,)
								strMsg += m_RecvBuf[i];
							}

						}

						ComLog_AddString(strMsg);
						int  lIndex;
						BYTE lInData[3] = { 0, 0, 0 };
						lIndex = (m_RecvBuf[3] - 0x30) * 10 + (m_RecvBuf[4] - 0x30);
						//lInData[3] = hex2dec(m_RecvBuf[2 + i])
						if (lIndex == 99)
						{
							for (int j = 0; j < m_ComRcvByte; j++)
							{
								lInData[j] = hex2dec(m_RecvBuf[6 + j * 2]);
								lInData[j] = lInData[j] << 4;
								lInData[j] += hex2dec(m_RecvBuf[7 + j * 2]);
								for (int i = 0; i < 8; i++)
								{
									if (lInData[j] & (0x01 << i))
									{
										gDiRcvData[j * 8 + i] = 1;
									}
									else
									{
										gDiRcvData[j * 8 + i] = 0;
									}
								}
							}
						}
						else if ((lIndex >= 0) && (lIndex < 24))
						{
							lInData[0] = hex2dec(m_RecvBuf[6]);
							if (lInData[0])
								gDiRcvData[lIndex] = 1;
							else
								gDiRcvData[lIndex] = 0;
						}
						else
						{
							m_ComAck = COM_ACK_BUSY;
							m_ReadMIOComAck = COM_ACK_BUSY;
						}
						//	FindNextStart(int lCnt);
						//		GetNextData(15);
						m_RecvCnt = 0;											   
					}
					else
					{
						break;
					}
				}
				else if (strncmp((char *)&m_RecvBuf[1], "DO", 2) == 0)
				{
				//if ((m_RecvCnt >= 15)&&((char)m_RecvBuf[12] == 0x03))
				//int m_ComType = _NEW_DFT_24PORT_MODE;
				int m_ComRcvByte = 3;
				if (m_RecvCnt >= 13)
				{
					if ((char)m_RecvBuf[10] == 0x03)
					{
						m_ComRcvByte = 2;
					}
					else if ((char)m_RecvBuf[12] == 0x03)
					{
						if (m_RecvCnt >= 15)
						{
							m_ComRcvByte = 3;
						}
						else
						{
							break;
						}
					}

					m_cLb_ComMain.put_BackColor(0x00FF00);

					m_ComAck = COM_ACK_OK;
					m_ReadMIOComAck = COM_ACK_OK;
					strMsg = "<< ";

					for (int i = 0; i < m_RecvCnt; i++)
					{
						if( ((m_RecvBuf[i] >= 'A') && (m_RecvBuf[i] <= 'z'))
							||((m_RecvBuf[i] >= '0') && (m_RecvBuf[i] <= '9')))
						{
							strMsg += m_RecvBuf[i];
						}
						else
						{
							//strTmp.SetAt(0,)
							strTmp.Format("x%02X", m_RecvBuf[i]);
							strMsg += strTmp;
						}

					}

					ComLog_AddString(strMsg);
					int  lIndex;
					BYTE lInData[3] = { 0, 0, 0 };
					lIndex = (m_RecvBuf[3] - 0x30) * 10 + (m_RecvBuf[4] - 0x30);
					//lInData[3] = hex2dec(m_RecvBuf[2 + i])
					if ((lIndex == 99)|| ((lIndex >= 0) && (lIndex < 24)))
					{
						for (int j = 0; j < m_ComRcvByte; j++)
						{
							lInData[j] = hex2dec(m_RecvBuf[6 + j * 2]);
							lInData[j] = lInData[j] << 4;
							lInData[j] += hex2dec(m_RecvBuf[7 + j * 2]);
							for (int i = 0; i < 8; i++)
							{
								if (lInData[j] & (0x01 << i))
								{
									gDoConfirmData[j * 8 + i] = 1;
								}
								else
								{
									gDoConfirmData[j * 8 + i] = 0;
								}
							}
						}
					}
					/*else if ((lIndex >= 0) && (lIndex < 24))
					{
						lInData[0] = hex2dec(m_RecvBuf[6]);
						if (lInData[0])
							gDoConfirmData[lIndex] = 1;
						else
							gDoConfirmData[lIndex] = 0;
					}*/
					else
					{
						m_ComAck = COM_ACK_BUSY;
						m_ReadMIOComAck = COM_ACK_BUSY;
					}
					//	FindNextStart(int lCnt);
					//		GetNextData(15);
					m_RecvCnt = 0;
				}
				else
				{
					break;
				}
				}
				else
				{	
					strMsg = "<< ";

					for (int i = 0; i < m_RecvCnt; i++)
					{
						if ((m_RecvBuf[i] < 0x20) || (m_RecvBuf[i] > 0x7F))
						{
							strTmp.Format("x%02X", m_RecvBuf[i]);
							strMsg += strTmp;
						}
						else
						{
							//strTmp.SetAt(0,)
							strMsg += m_RecvBuf[i];
						}

					}
					ComLog_AddString(strMsg);
					m_RecvCnt = 0;
					
				}
			}
			else
			{
				break; 
			}
		}		
		else
		{
			m_RecvCnt = 0;
		}
	}
	sUsingBuf = 0;
	return 0;
}


long CAcqVoltageSamples_IntClkDlg::OnReceiveDataPCB(WPARAM wParam, LPARAM lParam )
{
	CString str;
	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	if((m_RecvCntPCB < 0)||(m_RecvCntPCB > 4095))
		m_RecvCntPCB = 0;

	memcpy(lbuf,(void *)lParam,lcnt);

	for(int i = 0; i < lcnt; i++)
	{
		m_RecvBufPCB[m_RecvCntPCB++] = lbuf[i];
		if(m_RecvCntPCB > 4095)
			m_RecvCntPCB = 0;
	}
		
	

	if(m_RecvCntPCB > 2)
	{
		if(m_RecvBufPCB[0] == 0xBB)
		{
			if(m_RecvCntPCB >= m_RecvBufPCB[1]+2)
			{

		/*		memcpy(lbuf,m_RecvBufPCB,m_RecvCntPCB);
				lbuf[m_RecvCntPCB] = 0;
				str = lbuf;
				CFileControl lfile;
				lfile.SaveProcessLOG(str, 1);*/

				AddPCBLog(m_RecvBufPCB,m_RecvCntPCB, 1);
			//	memset(lbuf,0,sizeof(lbuf));
				unsigned char lCheckSum = 0;
				for(int i = 0; i < m_RecvBufPCB[1]+1; i++)
				{
					lCheckSum ^= m_RecvBufPCB[i];
				}
				TVCommCtrl.m_ReadComplete = 1;
				TVCommCtrl.m_nReceiveLength = m_RecvCntPCB;
				memcpy(TVCommCtrl.m_nReceiveData, m_RecvBufPCB, m_RecvCntPCB);

				if(m_RecvBufPCB[m_RecvBufPCB[1]+1] == lCheckSum)
				{
					m_PCBComAck = COM_ACK_OK;
					if ((m_UartOkAckDataCnt > 0) && (m_UartOkAckDataCnt <= 10))
					{
						m_UartREADCnt = m_RecvBufPCB[1] - 3;
						if (m_UartREADCnt > 0)
						{
							for (int i = 0; i < m_UartREADCnt; i++)
							{
								m_UartREADData[i] = m_RecvBufPCB[4 + i];
							}
						}
						if (m_UartREADCnt == m_UartOkAckDataCnt)
						{
							for (int i = 0; i < m_UartOkAckDataCnt; i++)
							{
								//int m_UartOkAckDataCnt;
								if (m_RecvBufPCB[4 + i] == m_UartOkAckData[i])
								{
									if (m_PCB_CheckOK == 0)
									{
										m_PCB_CheckOK = 1;
									}
								}
								else
								{
									m_PCB_CheckOK = 2;
									//break;
								}
							}
						}
						else
						{
							m_PCB_CheckOK = 2;
						}
					}
				}
				else
				{
					m_PCBComAck = COM_ACK_BUSY;
				}


				CString strtmp;
				CString strReceive ;
				CString strMsg;
				int lASCII_Data = 0;
				if (m_RecvBufPCB[1] > 7)
				{
					
					for (int i = 4; i < m_RecvCntPCB - 1; i++)
					{
						if ((m_RecvBufPCB[i] == 0x20)
							|| ((m_RecvBufPCB[i] >= 0x30) && (m_RecvBufPCB[i] <= 0x3A))
							|| ((m_RecvBufPCB[i] >= 0x41) && (m_RecvBufPCB[i] <= 0x5A))
							|| ((m_RecvBufPCB[i] >= 0x61) && (m_RecvBufPCB[i] <= 0x7A)))
						{
							lASCII_Data = 1;
						}
						else
						{
							lASCII_Data = 0;
							break;
						}
					}
				}
				if (m_RecvCntPCB > 50)
				{
					m_RecvCntPCB = 0;
					return 0;
				}
					
				for (int i = 0; i < 4; i++)
				{

					strtmp.Format(_T("%02X "), m_RecvBufPCB[i]);
					strReceive += strtmp;
				}
				if (lASCII_Data == 1)
				{
					char buf[64];
					memcpy(buf, &m_RecvBufPCB[4], m_RecvCntPCB - 5);
					buf[m_RecvCntPCB - 5] = 0;
					strtmp = buf;
					strReceive += strtmp;
					strtmp.Format(_T(" %02X"), m_RecvBufPCB[m_RecvCntPCB-1]);
					strReceive += strtmp;
				}
				else
				{
					for (int i = 4; i < m_RecvCntPCB; i++)
					{
						strtmp.Format(_T("%02X "), m_RecvBufPCB[i]);
						strReceive += strtmp;
					}
				}
				strMsg = "<< ";
				strMsg += strReceive;
				
				ComLog_AddString(strMsg);

#ifdef __MESSAGE_DEBUG_MODE__
				MessageDisplay(2, strReceive);//SetDlgItemText(IDC_EDIT_READ_DATA,strReceive.GetBuffer());
#endif
			//	m_PCBComAck = COM_ACK_OK;
				m_RecvCntPCB = 0;
							
			}
		}
		else
		{
			m_RecvCntPCB = 0;
		}
	}



	return 0;
}

long CAcqVoltageSamples_IntClkDlg::OnReceiveDataSCAN(WPARAM wParam, LPARAM lParam )
{
	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	if((m_RecvCntSCAN < 0)||(m_RecvCntSCAN > 4095))
		m_RecvCntSCAN = 0;

	memcpy(lbuf,(void *)lParam,lcnt);

	for(int i = 0; i < lcnt; i++)
	{
		m_RecvBufSCAN[m_RecvCntSCAN++] = lbuf[i];
		if(m_RecvCntSCAN > 4095)
			m_RecvCntSCAN = 0;
	}
	

	if(m_RecvCntSCAN > 3)
	{
		if((m_RecvBufSCAN[m_RecvCntSCAN-1] == 0x0d) || (m_RecvBufSCAN[m_RecvCntSCAN-1] == 0x0a))
		{
			m_RecvBufSCAN[m_RecvCntSCAN] = 0;
			m_BarcodeString = m_RecvBufSCAN;	
			m_BarcodeString.Trim();
			m_BarcodeString.MakeUpper();
			m_BarCode.put_Caption(m_BarcodeString);
			m_stcBarCode1.SetWindowText(m_BarcodeString);
			m_stcBarCode1.Invalidate();
			m_RecvCntSCAN = 0;	
			UpdateData(FALSE);
			m_BarcodeString = _T("");
		}
		else if(m_RecvCntSCAN >= 30)
		{
			MessageDisplay(1, "BARCODE Scan Error !");
			m_RecvCntSCAN = 0;
			UpdateData(FALSE);
			m_BarcodeString = _T("");
		}		
	}
	

	return 0;
}


long CAcqVoltageSamples_IntClkDlg::OnReceiveDataLED(WPARAM wParam, LPARAM lParam )
{


		BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	if((m_RecvCntLED < 0)||(m_RecvCntLED > 4095))
		m_RecvCntLED = 0;

	memcpy(lbuf,(void *)lParam,lcnt);

	for(int i = 0; i < lcnt; i++)
	{
		m_RecvBufLED[m_RecvCntLED++] = lbuf[i];
		if(m_RecvCntLED > 4095)
			m_RecvCntLED = 0;
	}


	if(m_RecvCntLED > 2)
	{
		if(m_RecvBufLED[0] == 0x02)
		{
			if(m_RecvCntLED >= 10)
			{

				if(strncmp((char *)&m_RecvBufLED[1], "DLED", 4) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
						
					/*for(int i = 0; i < 4; i++)
					{*/

					m_LEDReadData[0] = m_RecvBufLED[5]&m_LEDOkAckData[0];
					m_LEDReadData[1] = m_RecvBufLED[6]&m_LEDOkAckData[1];
					m_LEDReadData[2] = m_RecvBufLED[7]&m_LEDOkAckData[2];
					m_LEDReadData[3] = m_RecvBufLED[8]&m_LEDOkAckData[3];
					
					if((m_LEDOkAckData[0] == m_LEDReadData[0])
						&&(m_LEDOkAckData[1] == m_LEDReadData[1])
						&&(m_LEDOkAckData[2] == m_LEDReadData[2])
						&&(m_LEDOkAckData[3] == m_LEDReadData[3]))
					{
						m_LED_CheckOK = 1;
					}
					m_RecvCntLED = 0;

				}			
				else if(strncmp((char *)&m_RecvBufLED[1], "DOUT", 4) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
				
					m_RecvCntLED = 0;
					//m_LED_Up_DO_ReadData[0] = m_RecvBufLED[5];
					//m_LED_Up_DO_ReadData[1] = m_RecvBufLED[6];
					//m_LED_Up_DO_ReadData[2] = m_RecvBufLED[7];
					//m_LED_Up_DO_ReadData[3] = m_RecvBufLED[8];
					for(int i = 0; i < 4; i++)
					{
						m_LED_Up_DO_ReadData[i] = m_RecvBufLED[i+5] & 0x0F;
						if(m_LED_Up_DO_ReadData[i] != 0)
						{					
							/*if(m_Led_UP_DI_ON[i].get_BackColor() != 0x0000FF00)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x0000FF00);	
							}*/
						}
						else
						{
							/*	
							if(m_Led_UP_DI_ON[i].get_BackColor() != 0x00808080)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x00808080);	
							}*/
						}
					}
					

				}			
				else if(strncmp((char *)&m_RecvBufLED[1], "D_IN", 4) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
					
					//	//	m_LED_Up_DI_ReadData
					//m_LED_Up_DI_ReadData[0] = m_RecvBufLED[5];
					//m_LED_Up_DI_ReadData[1] = m_RecvBufLED[6];
					//m_LED_Up_DI_ReadData[2] = m_RecvBufLED[7];
					//m_LED_Up_DI_ReadData[3] = m_RecvBufLED[8];
					//for(int i = 0; i < 4; i++)
					//{
					//	m_LED_Up_DI_ReadData[1] = m_RecvBufLED[i] & 0x0F;
					//	if(m_RecvBufLED[i] != 0)
					//	{					
					//	/*	if(m_LED_Up_DI_ReadData[1] == m_RecvBufLED[5])						
					//		{
					//			m_LED_CheckOK = 1;
					//		}*/
					//	}
					//}

					for(int i = 0; i < 4; i++)
					{
						m_LED_Up_DI_ReadData[i] = m_RecvBufLED[i+5] & 0x0F;
						if(m_LED_Up_DI_ReadData[i] != 0)
						{					
							/*if(m_Led_UP_DI_ON[i].get_BackColor() != 0x0000FF00)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x0000FF00);	
							}*/
						}
						else
						{
							/*	
							if(m_Led_UP_DI_ON[i].get_BackColor() != 0x00808080)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x00808080);	
							}*/
						}
					}
					m_RecvCntLED = 0;

				}		
				else if(strncmp((char *)&m_RecvBufLED[1], "DREADY", 6) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
					m_RecvCntLED = 0;
				}
				else
				{
					m_LEDComAck = COM_ACK_BUSY;
					m_LEDResendCnt = 0;
					m_RecvCntLED = 0;
				}

				m_RecvCntLED = 0;
			}
		}
		else
		{
			m_RecvCntLED = 0;
		}
	}
	return 0;
}

long CAcqVoltageSamples_IntClkDlg::OnReceiveDataEthernet(WPARAM wParam, LPARAM lParam )
{


	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	return 0;
}


long CAcqVoltageSamples_IntClkDlg::OnParseDataEthernet( )
{
	BYTE lbuf[4096];
	int lcnt;
	int lpos;
	int lendpos;
	CString l_Receivestr; 
	CString str1; 
	CString str2; 
	bool lReadFlag = 0;

	lcnt = m_strEthernetReceive.GetLength();




	if((m_strEthernetReceive.Find("<EIF") >= 0)&&(m_strEthernetReceive.Find("</EIF>") >= 0))
	{
		m_GMES_NGCNT = 0;
		AddGmesLog(m_strEthernetReceive, 1);

		m_GMES_Alive_WaitCnt = 0;
		m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
		l_Receivestr = m_strEthernetReceive;

		m_strEthernetReceive = "";
		switch(m_EthernetMode)
		{
		case ETHERNET_MODE_HOST_CHECK:
			
			//Send Are You There
			//=> Are You There Data		
			if(l_Receivestr.Find("\"S1F2\"")>=0)
			{
				lReadFlag = 1;
//				m_EthernetMode = ETHERNET_MODE_EQIP_CONNECT;
				m_EthernetMode = ETHERNET_MODE_RUN;//ETHERNET_MODE_TIME_SEND;
				MessageDisplay(0, "GMES Socket OPEN!");

				//g_strEQPID						
				lpos = l_Receivestr.Find("<EQPID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+7);
				lpos = str1.Find("</EQPID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strEQPID = str1;


				lpos = l_Receivestr.Find("<EQPNAME>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<EQPNAME>"));
				lpos = str1.Find("</EQPNAME>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strEQPName = str1;

				lpos = l_Receivestr.Find("<PROCID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<PROCID>"));
				lpos = str1.Find("</PROCID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strProcID = str1;


				lpos = l_Receivestr.Find("<ORGID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<ORGID>"));
				lpos = str1.Find("</ORGID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strORGID = str1;


				lpos = l_Receivestr.Find("<LINEID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<LINEID>"));
				lpos = str1.Find("</LINEID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strLineID = str1;

//<EIF VERSION="1.8" ID="S1F1" NAME="AreYouThereRequest">
//</EIF>

//<EIFVERSION="1.8"ID="S1F2"NAME="AreYouThereData">
//<ELEMENT>
//<EQPID></EQPID>
//<EQPNAME></EQPNAME>
//<PROCID></PROCID>
//<ORGID></ORGID>
//<LINEID></LINEID>
//</ELEMENT>
//</EIF>
//				CString g_strEQPID;
//CString g_strEQPName;
//CString g_strProcID;
//CString g_strORGID;
//CString g_strLineID;
//lpos = str1.Find("ID=");
//str1 = str1.Mid(lpos);
//lpos = str1.Find("\"");
//str1 = str1.Mid(lpos+1);
//lpos = str1.Find("\"");
//str1 = str1.Left(lpos);

			}			
			break;

		case  ETHERNET_MODE_TIME_SEND:
//			if(l_Receivestr.Find("S2F32") >= 0)
//			{
//
//				#include "time.h" 
//
//SYSTEMTIME datetime; 
//datetime.wYear = 2012; 
//datetime.wMonth = 11; 
//datetime.wDay = 10; 
//
//datetime.wHour = 9; 
//datetime.wMinute = 8; 
//datetime.wSecond = 7; 
////datetime.wMilliseconds = 0; 
//SetSystemTime(&datetime); 
//
////E=>H
////<EIFVERSION="1.8"ID="S2F31"NAME="DataandTimeSend">
////<ELEMENT>
////<EQPID></EQPID>
////</ELEMENT>
////<ITEM>
////<TIME></TIME>
////</ITEM>
////</EIF>
//
//				
////H=>E
////<EIFVERSION="1.8"ID="S2F32"NAME="DataandTimeAcknowledge">
////<ELEMENT>
////<EQPID></EQPID>
////</ELEMENT>
////<ITEM>
////<ACK></ACK>
////</ITEM>
////</EIF>
//
//			}

			break;

//		case ETHERNET_MODE_EQIP_CONNECT:
//
////<EIFVERSION="1.8"ID="S1F4"NAME="EquipmentStatusAcknowledge">
////<ELEMENT>
////<EQPID></EQPID>
////</ELEMENT>
////<ITEM>
////<ACK></ACK>
////</ITEM>
////</EIF>
//			
//
//
//			break;

		default:
			break;

		}



		if(lReadFlag == 0)
		{
			
			
			if(l_Receivestr.Find("\"S1F4\"")>=0)
			{
				lReadFlag = 0;
				//m_EthernetMode = ETHERNET_MODE_RUN;

			}
			else if(l_Receivestr.Find("\"S2F3\"")>=0)
			{

				GMESLinkTestResponse();
				
//<EIFVERSION="1.8"ID="S2F3"NAME="LinkTestRequest">
//</EIF>


//<EIFVERSION="1.8"ID="S2F4"NAME="LinkTestResponse">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//</EIF>
//Notice
//<EQPID>EquipmentID

			}				
			
			else if(l_Receivestr.Find("\"S2F17\"")>=0)
			{
				GMESDateandTimeData();
//<EIFVERSION="1.8"ID="S2F17"NAME="DateandTimeRequest">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//</EIF>

//<EIFVERSION="1.8"ID="S2F18"NAME="DateandTimeData">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<TIME></TIME>
//</ITEM>
//</EIF>

			}
			else if(l_Receivestr.Find("\"S2F25\"")>=0)
			{

//<EIFVERSION="1.8"ID="S2F25"NAME="LoopbackdiagnosticsTestRequest">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM>
//</EIF>

//<EIFVERSION="1.8"ID="S2F26"NAME="LoopbackdiagnosticsTestAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM></EIF >

				lpos = l_Receivestr.Find("<AS>");
				str1 = l_Receivestr.Mid(lpos+strlen("<AS>"));
				lpos = str1.Find("</AS>");
				str1 = str1.Left(lpos);

				GMESLinkLoopbackResponce(str1);

			}
			else if(l_Receivestr.Find("\"S2F26\"")>=0)
			{

				m_GMES_Alive_WaitCnt = 0;
//
//				<EIFVERSION="1.8"ID="S2F26"NAME="LoopbackdiagnosticsTestAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<AS></AS>
//</ITEM></EIF >
			}
			else if(l_Receivestr.Find("\"S2F31\"") >= 0)
			{

//#include "time.h" 
		
				SYSTEMTIME datetime; 
				GetLocalTime(&datetime);

				

				int lAck =1;
				int litemp = 0;
					//YYYYMMDDhhmmss						
				lpos = l_Receivestr.Find("<TIME>");
				str1 = l_Receivestr.Mid(lpos+strlen("<TIME>"));
				lpos = str1.Find("</TIME>");
				str1 = str1.Left(lpos);

				str2 = str1.Left(4);
				datetime.wYear = _ttoi(str2);
				if(datetime.wYear < 2015)
					lAck = 0;


				str2 = str1.Mid(4, 2);
				datetime.wMonth = _ttoi(str2);
				if((datetime.wMonth < 0)||(datetime.wMonth > 12))
					lAck = 0;

				str2 = str1.Mid(6,2);
				datetime.wDay = _ttoi(str2); 
				if((datetime.wDay < 0)||(datetime.wDay > 31))
					lAck = 0;

				str2 = str1.Mid(8,2);
				datetime.wHour = _ttoi(str2); 
				if((datetime.wHour < 0)||(datetime.wHour > 24))
					lAck = 0;

				str2 = str1.Mid(10,2);
				datetime.wMinute = _ttoi(str2); 
				if((datetime.wMinute < 0)||(datetime.wMinute > 60))
					lAck = 0;
				
				str2 = str1.Mid(12,2);
				datetime.wSecond = _ttoi(str2); 
				if((datetime.wSecond < 0)||(datetime.wSecond > 60))
					lAck = 0;

				//datetime.wMilliseconds = 0; 
				if(lAck == 0)
					GetLocalTime(&datetime);//GetSystemTime(&datetime);

				//190522  SetSystemTime(&datetime); 
				//SetLocalTime(&datetime); 

				GMESDataandTimeAcknowledge(lAck);

//H=>E
//<EIFVERSION="1.8"ID="S2F31"NAME="DataandTimeSend">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<TIME></TIME>
//</ITEM>
//</EIF>
			

				
//E=>H
//<EIFVERSION="1.8"ID="S2F32"NAME="DataandTimeAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<ACK></ACK>
//</ITEM>
//</EIF>

			}			
			else if(l_Receivestr.Find("\"S5F2\"")>=0)
			{
//E => H
//<EIFVERSION="1.8"ID="S5F1"NAME="AlarmSetReportSend">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<SUBITEMLISTCOUNT="n">
//<ALCD></ALCD>
//<ALNAME></ALNAME>
//<ALTX></ALTX>
//</SUBITEMLIST>
//</ITEM>
//</EIF>

//H => E
//<EIFVERSION="1.8"ID="S5F2"NAME="AlarmSetReportAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<ACK></ACK>
//</ITEM>
//</EIF>

			}
			else if(l_Receivestr.Find("\"S5F4\"")>=0)
			{

//E => H
//<EIFVERSION="1.8"ID="S5F3"NAME="AlarmResetReportSend">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<SUBITEMLISTCOUNT="n">
//<ALCD></ALCD>
//<ALNAME></ALNAME>
//<ALTX></ALTX>
//</SUBITEMLIST>
//</ITEM>
//</EIF>

//H => E
//<EIFVERSION="1.8"ID="S5F4"NAME="AlarmResetReportAcknowledge">
//<ELEMENT>
//<EQPID></EQPID>
//</ELEMENT>
//<ITEM>
//<ACK></ACK>
//</ITEM>
//</EIF>

			}	
			else if(l_Receivestr.Find("\"S6F2\"")>=0)
			{




				lpos = l_Receivestr.Find("<SETID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<SETID>"));
				lpos = str1.Find("</SETID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				
				if(g_strSetID.Compare(str1) != 0)
				{
					MessageDisplay(1, "Set ID Missmatch!");
				}


		//lpos = l_Receivestr.Find("<MODEL>");	//</EQPID>	
		//		str1 = l_Receivestr.Mid(lpos+strlen("<MODEL>"));
		//		lpos = str1.Find("</MODEL>");	//</EQPID>	
		//		str1 = str1.Left(lpos);

		//lpos = l_Receivestr.Find("<ID>");	//</EQPID>	
		//		str1 = l_Receivestr.Mid(lpos+strlen("<ID>"));
		//		lpos = str1.Find("</ID>");	//</EQPID>	
		//		str1 = str1.Left(lpos);
		//		g_strModelID = str1;

		
				lpos = l_Receivestr.Find("<ACK>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<ACK>"));
				lpos = str1.Find("</ACK>");	//</EQPID>	
				str1 = str1.Left(lpos);
				if(str1.Compare("0") == 0)
				{
					MessageDisplay(0, "GEMS OK");
					gSaveInfo.bMesSts = 1;
				}
				else
				{
					lpos = l_Receivestr.Find("<REASON>");	//</EQPID>	
					str1 = l_Receivestr.Mid(lpos+strlen("<REASON>"));
					lpos = str1.Find("</REASON>");	//</EQPID>	
					str1 = str1.Left(lpos);
					MessageDisplay(1, str1.GetBuffer());

					str1 += "  [GMES]";
					m_Deisplay_ErrorName = str1;
					NG_Display(str1);
					m_TaskRun = TASK_WAIT_SELECT_PROCESS;
					m_GMES_CommError = 1;
					//MessageBox(str1);
					gSaveInfo.bMesSts = 0;
				}

				m_EthernetAck = 1;
				
			}		
			else if(l_Receivestr.Find("\"S6F5\"")>=0)
			{




				lpos = l_Receivestr.Find("<WOID>");	//<WOID></WOID>
				str1 = l_Receivestr.Mid(lpos+strlen("<WOID>"));
				lpos = str1.Find("</WOID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strEQPID = str1;

				lpos = l_Receivestr.Find("<ORGID>");	//<WOID></WOID>
				str1 = l_Receivestr.Mid(lpos+strlen("<ORGID>"));
				lpos = str1.Find("</ORGID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strORGID = str1;

				lpos = l_Receivestr.Find("<LINEID>");	//<WOID></WOID>
				str1 = l_Receivestr.Mid(lpos+strlen("<LINEID>"));
				lpos = str1.Find("</LINEID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strLineID = str1;

				lpos = l_Receivestr.Find("<EQPID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+7);
				lpos = str1.Find("</EQPID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strEQPID = str1;


				lpos = l_Receivestr.Find("<PROCID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<PROCID>"));
				lpos = str1.Find("</PROCID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strProcID = str1;


				lpos = l_Receivestr.Find("<SETID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<SETID>"));
				lpos = str1.Find("</SETID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strSetID = str1;


				lpos = l_Receivestr.Find("<MODEL>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<MODEL>"));
				lpos = str1.Find("</MODEL>");	//</EQPID>	
				str1 = str1.Left(lpos);

				lpos = l_Receivestr.Find("<ID>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<ID>"));
				lpos = str1.Find("</ID>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strModelID = str1;

				lpos = l_Receivestr.Find("<NAME>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<NAME>"));
				lpos = str1.Find("</NAME>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strMesModelName = str1;

				lpos = l_Receivestr.Find("<SUFFIX>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<SUFFIX>"));
				lpos = str1.Find("</SUFFIX>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strModelSuffix = str1;

				str1 = g_strMesModelName;
				str1 += ".";
				str1 += g_strModelSuffix;

				m_EthernetAck = 1;
				GMESProductDataAcknowledge();//S6F6		
				
				if(gTestSeqData.strModelName.Find(str1) >= 0)
				{
				}
				else
				{
					ChangeModelCheckOpen(str1);// ChangeModel(str1);
				}
				
			}		
			else if(l_Receivestr.Find("\"S6F12\"")>=0)
			{
				lpos = l_Receivestr.Find("<ACK>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<ACK>"));
				lpos = str1.Find("</ACK>");	//</EQPID>	
				str1 = str1.Left(lpos);
				if(str1.Compare("0") == 0)
				{
					MessageDisplay(0, "GEMS OK");
				}
				else
				{
					lpos = l_Receivestr.Find("<REASON>");	//</EQPID>	
					str1 = l_Receivestr.Mid(lpos+strlen("<REASON>"));
					lpos = str1.Find("</REASON>");	//</EQPID>	
					str1 = str1.Left(lpos);
					MessageDisplay(1, str1.GetBuffer());
					gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;

					str1 += "  [GMES]";

					m_Deisplay_ErrorName = str1;
					NG_Display(str1);
					m_TaskRun = TASK_WAIT_SELECT_PROCESS;
					m_GMES_CommError = 1;

					m_EthernetAck = 1;//
					//MessageBox(str1);
				}
			}
			else if(l_Receivestr.Find("\"S9F3\"")>=0)
			{

			}
		}

		m_strEthernetReceive = "";


	}


	return 0;
}

void CAcqVoltageSamples_IntClkDlg::OnDestroy()
{
	CDialog::OnDestroy();
//	gbShutdown = true;

	StopCapture();

	if (m_previewWindow != NULL)
	{
		m_previewWindow->Release();
		m_previewWindow = NULL;
		delete m_previewWindow;
	}

	// Release DeckLink discovery instance
	if (m_deckLinkDiscovery != NULL)
	{
		m_deckLinkDiscovery->Disable();
		m_deckLinkDiscovery->Release();
		m_deckLinkDiscovery = NULL;
	}
	Sleep(200);

	ShowWindow(SW_HIDE);
    RemoveEventHandler();
	for(int i = 0; i < 16; i++)
	{
		if (m_task[i].get() != NULL)
		{
			m_task[i]->Control(DAQmxTaskAbort);
		}
	}
    CleanUpIfNecessary();


	SaveRegistrySetting();

#ifdef __G_MES_SET_MODE__
	//CloseEthernetScocket();
	if (m_pUDPSocket)
	{
		m_pUDPSocket->Close();
		delete m_pUDPSocket;

		m_pUDPSocket  = NULL;

	}	
#else
	g_MesDb.Close();
#endif





	/*
	if( vcap.isOpened() )
	{

		vcap.release();
		
	}*/

	if (mpDlgResult != NULL)
	{
		delete mpDlgResult;
		mpDlgResult = NULL;
	}

	if (mpDlgBarcode != NULL)
	{
		delete mpDlgBarcode;
		mpDlgBarcode = NULL;
	}

	if (mpDlgSimpleInform != NULL)
	{
		delete mpDlgSimpleInform;
		mpDlgSimpleInform = NULL;
	}

	while(m_deviceListCombo.GetCount() > 0)
	{
		DeckLinkDevice* device = (DeckLinkDevice*)m_deviceListCombo.GetItemDataPtr(0);
		device->Release();
		m_deviceListCombo.DeleteString(0);
	}


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	gbShutdown = true;

	StopCapture();
	if (m_previewWindow != NULL)
	{
		m_previewWindow->Release();
		m_previewWindow = NULL;
		delete m_previewWindow;
	}

	// Release DeckLink discovery instance
	if (m_deckLinkDiscovery != NULL)
	{
		m_deckLinkDiscovery->Disable();
		m_deckLinkDiscovery->Release();
		m_deckLinkDiscovery = NULL;
	}
	Sleep(200);


	//Sleep(10);
	//if( vcap.isOpened() )
	//{

	//	vcap.release();
	//	
	//}


	CDialog::OnOK();
}





void CAcqVoltageSamples_IntClkDlg::SetTimeCheck(int  lIndex)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	//MessageDisplay(0, _T("Model Mouse Down!!"));

	/*time_t ti;
	time(&ti);
	struct tm *t = localtime(&ti);		
	char sDate[32];
	sprintf(sDate, "%4d/%02d/%02d %02dh %02dm %02ds",
		t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

	static CTime sOldTime;

	CTime m_CurrentTime;
	

	m_CurrentTime = m_CurrentTime.GetCurrentTime();*/

	//
	//if((mstartT_1 == 0) || (lIndex == 1))
	//{
	//	mstartT_1 = GetTickCount();

	//}

	//if((mstartT_2 == 0) || (lIndex == 2))
	//{
	//	mstartT_2 = GetTickCount();

	//}	
	//
	//if((mstartT_3 == 0) || (lIndex == 3))
	//{
	//	mstartT_3 = GetTickCount();

	//}	
	//
	//if((mstartT_4 == 0) || (lIndex == 4))
	//{
	//	mstartT_4 = GetTickCount();

	//}
	//
	//if((mstartT_5 == 0) || (lIndex == 5))
	//{
	//	mstartT_5 = GetTickCount();

	//}	
	//
	//if((mstartT_6 == 0) || (lIndex == 6))
	//{
	//	mstartT_6 = GetTickCount();

	//}

	for(int i = 0; i < 64; i++)
	{
		if((mstartT[i] == 0) || (lIndex == i))
		{
			mstartT[i] = GetTickCount();
		}
	}
	
}


unsigned long  CAcqVoltageSamples_IntClkDlg::GetTimeCheck(int  lIndex)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//MessageDisplay(0, _T("Model Mouse Up!!"));

	/*	static unsigned long mstartT_1 = 0;
	static unsigned long mstartT_2 = 0;
	static unsigned long mstartT_3 = 0;*/

	unsigned long lCheckTime = GetTickCount();
	unsigned long lCheckDelayTime = 0;

	/*if(lIndex == 1)
	{
		lCheckDelayTime = lCheckTime - mstartT_1;

	}
	else if(lIndex == 2)
	{
		lCheckDelayTime = lCheckTime - mstartT_2 ;

	}
	else if(lIndex == 3)
	{
		lCheckDelayTime = lCheckTime - mstartT_3;

	}
	else if(lIndex == 4)
	{
		lCheckDelayTime = lCheckTime - mstartT_4;

	}
	else if(lIndex == 5)
	{
		lCheckDelayTime = lCheckTime - mstartT_5;

	}	
	else if(lIndex == 6)
	{
		lCheckDelayTime = lCheckTime - mstartT_6;

	}*/

	for(int i = 0; i < 64; i++)
	{
		if(lIndex == i)
		{
			lCheckDelayTime = lCheckTime - mstartT[i];
		}
	}

	return lCheckDelayTime;

}


void  CAcqVoltageSamples_IntClkDlg::DisplayTimeLap()
{
	CString str;
	unsigned long lCheck_Time ;
	if(CheckTimeOn)
	{
		lCheck_Time = GetTimeCheck(4);
		str.Format(_T("%4.1f"), lCheck_Time/1000.0);
		//m_CheckTimeLabel.put_Caption(str);
		if (str != m_CtrlListMainProcess.GetItemText(StepList.GetSize(), 3))
		{
			m_CtrlListMainProcess.SetItemText(StepList.GetSize(), 3, str);
			m_stcTime.SetWindowText(str);//
		}
	}


	//if(CycleTimeOn)
	//{
	//	lCheck_Time = GetTimeCheck(5);
	//	str.Format(_T("%.1f (s)"), lCheck_Time/1000.0);
	//	m_CycleTimeLabel.put_Caption(str);

	//	if(lCheck_Time > 100000)
	//	{
	//		CycleTimeOn = 0;
	//	}
	//}
}


void CAcqVoltageSamples_IntClkDlg::LoadTestData(CString lstrModelname)
{
	CString lstrModelPathName = _T("");
	//lstrModelname  = _T("TEST");
	CFileControl lFile;

	if (lFile.CheckModelSeqFile(lstrModelname))
		return;

	lFile.OpenModelSeq(lstrModelname);
	lstrModelPathName = PATH_BASE_DIR;
	lstrModelPathName += _T("\\Model\\");
	lstrModelPathName += lstrModelname;
	//lstrModelPathName += _T("\\");
	//lstrModelPathName += lstrModelname;
	//lstrModelPathName += _T(".seq");

	gTestSeqData.lTime = lFile.GetModifyTime(lstrModelPathName);



	
}


bool CAcqVoltageSamples_IntClkDlg::SeqFileModified(CString lstrModelname)
{

	CString lstrModelPathName = _T("");
	CFileControl lFile;


	lstrModelPathName = PATH_BASE_DIR;
	lstrModelPathName += _T("\\Model\\");
	lstrModelPathName += lstrModelname;
	//lstrModelPathName += _T("\\");
	//lstrModelPathName += lstrModelname;
	//lstrModelPathName += _T(".seq");

	if (gTestSeqData.lTime == lFile.GetModifyTime(lstrModelPathName))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void CAcqVoltageSamples_IntClkDlg::DisplayTestData()
{
	SetSubListControl();
	
}



void CAcqVoltageSamples_IntClkDlg::SetListControl()
{
	
//	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListMainProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListMainProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 36); 
	m_CtrlListMainProcess.InsertColumn(1, _T("STEP"), LVCFMT_CENTER, 140);// 리스트 행 추가
	m_CtrlListMainProcess.InsertColumn(2, _T("OK/NG"), LVCFMT_CENTER, 54);// 리스트 행 추가
	m_CtrlListMainProcess.InsertColumn(3, _T("T/T"), LVCFMT_CENTER, 45);// 리스트 행 추가
	//m_CtrlListMainProcess.InsertColumn(4, _T("Discription"), LVCFMT_LEFT, 350);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(3, _T("Wait"), LVCFMT_LEFT, 50);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(4, _T("Time"), LVCFMT_CENTER, 70);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(5, _T("Ref1"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(6, _T("Ref2"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(7, _T("Value"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(8, _T("OK/NG"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(9, _T("T/T"), LVCFMT_CENTER, 50);// 리스트 행 추가

	m_CtrlListMainProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
	m_CtrlListMainProcess.SetItem(0, 1, LVIF_TEXT, _T("FM TEST"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	m_CtrlListMainProcess.SetItem(0, 2, LVIF_TEXT, _T("97.8Hz"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 3, LVIF_TEXT, _T("2.5"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 4, LVIF_TEXT, _T("0.0"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 5, LVIF_TEXT, _T("0"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 6, LVIF_TEXT, _T("80%"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 7, LVIF_TEXT, _T("90%"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 8, LVIF_TEXT, _T("OK"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 

	
	
	font = new CFont;
	font->CreateFontA( 16,                          // nHeight
					0,                          // nWidth
					0,                          // nEscapement
					0,                          // nOrientation
					400,                           // nWeight
					0,                          // bItalic
					0,                          // bUnderline 
					0,                          // cStrikeOut 
					0,                          // nCharSet
					0,           // nOutPrecision 
					0,                          // nClipPrecision 
					PROOF_QUALITY,              // nQuality
					0,  // nPitchAndFamily 
					_T("Arial"));                     // lpszFacename


	//font->CreateFontA( 20,                          // nHeight
	//				   0,                          // nWidth
	//				   0,                          // nEscapement
	//				   0,                          // nOrientation
	//				   400,                           // nWeight
	//				   0,                          // bItalic
	//				   0,                          // bUnderline 
	//				   0,                          // cStrikeOut 
	//				   0,                          // nCharSet
	//				   0,           // nOutPrecision 
	//				   0,                          // nClipPrecision 
	//				 PROOF_QUALITY,              // nQuality
	//				 0,  // nPitchAndFamily 
	//				 _T("Arial"));                     // lpszFacename
	//font->CreatePointFont(20,_T("Arial"));   
//	m_CtrlListMainProcess.SetFont(font);

	delete font;
	
}


void CAcqVoltageSamples_IntClkDlg::SetSubListControl()
{
	InsertStepData2Grid(CurrentSet->nDisplayType);
	return;
	CSize lSize;
	CString strTemp;

	m_CtrlListMainProcess.DeleteAllItems();

	mCheckAll = 1;
	
	for(int  i = 0; i < gTestSeqData.TestCnt; i++)
	{
		strTemp.Format(_T("%d"), i+1);
		m_CtrlListMainProcess.InsertItem(i, strTemp);   


		strTemp = gTestSeqData.TestStepList[i].strStepName;
		m_CtrlListMainProcess.SetItem(i, 1, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);
		m_CtrlListMainProcess.SetItem(i, 2, LVIF_TEXT, "", NULL, NULL, NULL, NULL);
		m_CtrlListMainProcess.SetItem(i, 3, LVIF_TEXT, "0", NULL, NULL, NULL, NULL);
		strTemp = gTestSeqData.TestStepList[i].strStepWork;
//		m_CtrlListMainProcess.SetItem(i, 4, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);

		gTestSeqData.TestStepList[i].bEnable = 1;
		if(gTestSeqData.TestStepList[i].bEnable == 1)
		{
			m_CtrlListMainProcess.SetCheck(i,1);
		}
		else
		{
			m_CtrlListMainProcess.SetCheck(i,0);
		}			
	}

	m_CtrlListMainProcess.Invalidate();
}
void CAcqVoltageSamples_IntClkDlg::InitMainGrid(int nGridType)
{
	CString sTmp;

	//char *sHeader1[] = { "", "NO","STEP", "RESULT", "", "NO", "STEP", "RESULT", "", "NO", "STEP", "RESULT" };
	char *sHeader2[14] = { "NO","STEP", "OK/NG", "T/T", "MEAS", "TARGET", "L-LIMIT", "U-LIMIT", "UNIT","A/T(FREQ,LVL)", "A/M(FREQ,LVL)", "TIME", "MESSAGE","" };
	int  nWidth[14] = { 40, 140, 55,45, 70, 90, 75, 75, 65, 200, 200, 76, 500,10 }; //int  nWidth[13] = { 300,  400, 2400, 900, 700, 900, 750, 750, 650, 2000, 2000, 760, 5000};


	//m_ctrlSummaryGrid.SetRedraw(flexRDNone);

	////	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
//	m_CtrlListMainProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	//m_CtrlListMainProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 35);
	//m_CtrlListMainProcess.InsertColumn(1, _T("STEP"), LVCFMT_CENTER, 142);// 리스트 행 추가
	//m_CtrlListMainProcess.InsertColumn(2, _T("RESULT"), LVCFMT_CENTER, 50);// 리스트 행 추가
	//m_CtrlListMainProcess.InsertColumn(3, _T("T/T"), LVCFMT_CENTER, 45);// 리스트 행 추가


	//m_CtrlListMainProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
	//m_CtrlListMainProcess.SetItem(0, 1, LVIF_TEXT, _T("FM TEST"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListMainProcess.SetItem(0, 2, LVIF_TEXT, _T("97.8Hz"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 





	CFont *font = new CFont;
	font->CreateFontA(16,                          // nHeight
		0,                          // nWidth
		0,                          // nEscapement
		0,                          // nOrientation
		400,                           // nWeight
		0,                          // bItalic
		0,                          // bUnderline 
		0,                          // cStrikeOut 
		0,                          // nCharSet
		0,           // nOutPrecision 
		0,                          // nClipPrecision 
		PROOF_QUALITY,              // nQuality
		0,  // nPitchAndFamily 
		_T("Arial"));                     // lpszFacename

	delete font;



	//CSize lSize;
	//CString strTemp;

	//m_CtrlListMainProcess.DeleteAllItems();

	//mCheckAll = 1;

	//for (int i = 0; i < gTestSeqData.TestCnt; i++)
	//{
	//	strTemp.Format(_T("%d"), i + 1);
	//	m_CtrlListMainProcess.InsertItem(i, strTemp);


	//	strTemp = gTestSeqData.TestStepList[i].strStepName;
	//	m_CtrlListMainProcess.SetItem(i, 1, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);
	//	m_CtrlListMainProcess.SetItem(i, 2, LVIF_TEXT, "", NULL, NULL, NULL, NULL);
	//	m_CtrlListMainProcess.SetItem(i, 3, LVIF_TEXT, "0", NULL, NULL, NULL, NULL);
	//	strTemp = gTestSeqData.TestStepList[i].strStepWork;
	//	//		m_CtrlListMainProcess.SetItem(i, 4, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);

	//	gTestSeqData.TestStepList[i].bEnable = 1;
	//	if (gTestSeqData.TestStepList[i].bEnable == 1)
	//	{
	//		m_CtrlListMainProcess.SetCheck(i, 1);
	//	}
	//	else
	//	{
	//		m_CtrlListMainProcess.SetCheck(i, 0);
	//	}
	//}
	//m_CtrlListMainProcess.Invalidate();

	///////////////////////////////////////////////////////////

	m_CtrlListMainProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가


	if (nGridType == DETAILEDGRID)
	{
		//m_ctrlSummaryGrid.SetCols(13);
		//m_ctrlSummaryGrid.SetRows(1);
		//m_ctrlSummaryGrid.SetExtendLastCol(TRUE);
		////		m_ctrlSummaryGrid.SetFrozenCols(3);	
		//m_ctrlSummaryGrid.SetFrozenCols(2);

		// Set Column Alignment & Column Title
		for (int nCol = 0; nCol < MAX_COLUMN_NO; nCol++)
		{
			m_CtrlListMainProcess.InsertColumn(nCol, _T(sHeader2[nCol]), LVCFMT_CENTER, nWidth[nCol]);


		}

		m_CtrlListMainProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
		m_CtrlListMainProcess.SetItem(0, 1, LVIF_TEXT, _T("FM TEST"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
		m_CtrlListMainProcess.SetItem(0, 2, LVIF_TEXT, _T("97.8Hz"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 


	}

	m_CtrlListMainProcess.Invalidate();
}

void CAcqVoltageSamples_IntClkDlg::InsertStepData2Grid(int nGridType)
{
	char *sHeader2[13] = { "", "NO","STEP", "RESULT", "MEAS", "TARGET", "L-LIMIT", "U-LIMIT", "UNIT","A/T(FREQ,LVL)", "A/M(FREQ,LVL)", "TIME", "MESSAGE" };
	int  nWidth[13] = { 30,  140, 90, 70, 90, 75, 75, 65, 200, 200, 76, 500, };

	//return;

	//+Insert Step Default Data
	POSITION Position;
	CStep* pStep;
	CString sTmp;
	int nTmp = 0;


	m_CtrlListMainProcess.DeleteAllItems();

	Position = StepList.GetHeadPosition();

	if (nGridType == DETAILEDGRID)
	{
		//m_ctrlSummaryGrid.SetRow(0);
		//		m_ctrlSummaryGrid.SetFrozenCols(3);
		//m_ctrlSummaryGrid.SetFrozenCols(2);
		//for (nTmp = 0; nTmp < MAX_COLUMN_NO; nTmp++)
		//{
		//	m_CtrlListMainProcess.InsertColumn(nTmp, _T(sHeader2[nTmp]), LVCFMT_CENTER, nWidth[nTmp]);
		//}

		if (StepList.GetCount() > 0)
		{
			nTmp = 0;

			while (Position)
			{
				pStep = StepList.GetNext(Position);

				//(Column 1) Step No
				sTmp.Format("%d", pStep->GetStepNo());
				m_CtrlListMainProcess.InsertItem(nTmp, sTmp);   // 첫째행(0), 첫째열에 삽입
				//(Column 0) Step Check 

				if (pStep->GetTest() == TRUE)
				{
					m_CtrlListMainProcess.SetCheck(nTmp, 1); //  m_ctrlSummaryGrid.SetCellChecked(flexChecked);
					m_LockStatus[nTmp] = 1;
				}
				else
				{
					m_CtrlListMainProcess.SetCheck(nTmp, 0); // m_ctrlSummaryGrid.SetCellChecked(flexUnchecked);
					m_LockStatus[nTmp] = 0;
				}


				//(Column 2) Step Name

				if (pStep->m_nTestType == ADC_TEST || pStep->m_nTestType == TV_COMM_TEST)
				{
					m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(189, 231, 97)); //  m_ctrlSummaryGrid.SetCellBackColor(RGB(189, 231, 97));
					m_CtrlListMainProcessEx.SetCellForeColor(nTmp, RGB(255, 255, 255));//m_ctrlSummaryGrid.SetCellForeColor(RGB(	255,	 255,   255 ));
				}
				else
				{
					m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(255, 255, 255));
					m_CtrlListMainProcessEx.SetCellForeColor(nTmp, RGB(0, 0, 0));
				}
				m_CtrlListMainProcess.SetItem(nTmp, 1, LVIF_TEXT, pStep->GetStepName(), NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nTmp, 2, pStep->GetStepName());


				//(Column 4) Measure
		/*		m_ctrlSummaryGrid.SetCol(4);
				m_ctrlSummaryGrid.SetColDataType(4, flexDTString);*/

				if (pStep->m_nStepType == CHECK_FUNCTION)
				{
					if (pStep->GetFuncType() == MEAS_BOOL)
					{
						if (pStep->GetNominal_Bool() == FALSE) sTmp.Format(_T("%s"), "FALSE");
						else sTmp.Format(_T("%s"), "TRUE");
					}
					else sTmp.Format("%4.1f", pStep->GetNominal_float());

					// (Column 5) Target
					//m_ctrlSummaryGrid.SetCol(5);
					//m_ctrlSummaryGrid.SetColDataType(5, flexDTString);
					m_CtrlListMainProcess.SetItem(nTmp, 5, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nTmp, 5, sTmp);



					if (pStep->GetFuncType() != MEAS_BOOL)
					{
						// (Column 6) Low Limit
						sTmp.Format("%4.1f", pStep->GetLowLimit());
						//m_ctrlSummaryGrid.SetCol(6);
						//m_ctrlSummaryGrid.SetColDataType(6, flexDTString);
						m_CtrlListMainProcess.SetItem(nTmp, 6, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 6, sTmp);

						// (Column 7) High Limit
						sTmp.Format("%4.1f", pStep->GetHighLimit());
						//m_ctrlSummaryGrid.SetCol(7);
						//m_ctrlSummaryGrid.SetColDataType(7, flexDTString);
						m_CtrlListMainProcess.SetItem(nTmp, 7, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 7, sTmp);

						// (Column 8) Unit
						sTmp.Format(_T("%s"), pStep->GetUnit());
						//	m_ctrlSummaryGrid.SetCol(8);
						//	m_ctrlSummaryGrid.SetColDataType(8, flexDTString);
						m_CtrlListMainProcess.SetItem(nTmp, 8, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 8, sTmp);


					}
					//+2007.10.15 Add BY USY
					if (pStep->m_bRunAudioTest == TRUE)
					{
						// (Column 9) Audio Target
						// change 090323
						if (pStep->m_nMeasureAudioType == LEVEL_CHECK) {
							sTmp.Format(_T("X, X, %d, %d"), pStep->m_nLeftLevel[0], pStep->m_nRightLevel[0]);
						}
						else if (pStep->m_nMeasureAudioType == FREQUENCY_CHECK) {
							sTmp.Format(_T("%d, %d, X, X"), pStep->m_nLeftFreq[0], pStep->m_nRightFreq[0]);
						}
						else {
							sTmp.Format(_T("%d, %d, %d, %d"), pStep->m_nLeftFreq[0], pStep->m_nRightFreq[0], pStep->m_nLeftLevel[0], pStep->m_nRightLevel[0]);
						}

						//m_ctrlSummaryGrid.SetCol(9);
						//m_ctrlSummaryGrid.SetColDataType(9, flexDTString);
						m_CtrlListMainProcess.SetItem(nTmp, 9, LVIF_TEXT, sTmp, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 9, sTmp);
					}
					//-
				}
				nTmp++;
			}
			//Result Row
			;
			//(Column 1) Step No
			//sTmp.Format("%d", StepList.GetCount() + 1);
			///m_ctrlSummaryGrid.SetCol(1);
			//m_ctrlSummaryGrid.SetColDataType(1, flexDTString);
			m_CtrlListMainProcess.InsertItem(nTmp, _T("")); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 1, _T(""));		
			m_CtrlListMainProcess.SetItem(nTmp, 1, LVIF_TEXT, "Total", NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nTmp, 2, "Total");

			//m_ctrlSummaryGrid.SetRow(0);
			//m_ctrlSummaryGrid.SetCol(0);
			//m_ctrlSummaryGrid.SetCellChecked(flexChecked);
			//+ 2007.10.10 Add BY USY
			m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(247, 247, 231));
			//			m_ctrlSummaryGrid.SetGridColor(RGB(210,216,176));
			//m_ctrlSummaryGrid.SetGridColor(RGB(200, 200, 176));
			//-
		}
	}
	m_CtrlListMainProcess.Invalidate();
	return;
}


void CAcqVoltageSamples_IntClkDlg::OnHdnItemclickListMainProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

		
	int lint  = phdr->iItem;
	int i,lcnt;
	if(lint == 0)
	{
		if(mCheckAll)
		{
			mCheckAll = 0;
			lcnt = m_CtrlListMainProcess.GetItemCount();
			for(i = 0; i < lcnt; i++)
			{
				m_CtrlListMainProcess.SetCheck(i, 0);
			}
		}
		else
		{
			mCheckAll = 1;
			lcnt = m_CtrlListMainProcess.GetItemCount();
			for(i = 0; i < lcnt; i++)
			{
				m_CtrlListMainProcess.SetCheck(i, 1);
			}
		}
	}
	*pResult = 0;

}


void CAcqVoltageSamples_IntClkDlg::OnNMClickListMainProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;
	*pResult = 0;
	/*
	int i,lcnt;	
	lcnt = m_CtrlListMainProcess.GetItemCount();
		
	for(i = 0; i < lcnt; i++)
	{
		if(gTestSeqData.TestStepList[i].bEnable == 1)
		{
			m_CtrlListMainProcess.SetCheck(i, 1);
		}
		else
		{
			m_CtrlListMainProcess.SetCheck(i, 0);
		}
	}	*/
}


void CAcqVoltageSamples_IntClkDlg::OnNMCustomdrawListMainProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
#if 0


	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	CString strCol = _T("");



	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}
	case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
	{
		COLORREF crText, crBkgnd;

		//	nCol= m_CtrlListMainProcess.getse.GetSelectedColumn();
		//	nRow= m_CtrlListMainProcess.GetItemCount();

		int l_nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //row
		int l_nSubItem = (int)(pLVCD->iSubItem);

		//if ((m_CurrentStep > 0) && (m_CurrentStep < 200)&&(l_nItem == m_CurrentStep-1)&&(l_nSubItem < 2))
		//{
		//	crText = RGB(0, 0, 0);		//글자색
		//	crBkgnd = RGB(128, 128, 255);	//배경색으로 한다   
		//}
		//else if ((l_nItem >= 0) && (l_nItem < 200) && (l_nSubItem >= 0) && (l_nSubItem < 20))
		//{
		//	crText = m_CtrlListMainProcessEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
		//	crBkgnd = m_CtrlListMainProcessEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		//}

		if (l_nSubItem == 2)
		{
			strCol = m_CtrlListMainProcess.GetItemText(l_nItem, l_nSubItem);
			if (strCol.Find("OK") >= 0)
			{
				crText = RGB(255, 255, 255); //글자색
				crBkgnd = RGB(0, 0, 255); //배경색으로 한다   
			}
			else if (strCol.Find("NG") >= 0)
			{
				crText = RGB(255, 255, 255); //글자색
				crBkgnd = RGB(255, 0, 0); //배경색으로 한다 
			}
			else if (l_nItem == m_CurrentStep - 1)
			{
				crText = RGB(0, 0, 0); //글자색
				crBkgnd = RGB(255, 255, 0); //배경색으로 한다 


			}
			else
			{
				crText = RGB(0, 0, 0); //글자색
				crBkgnd = RGB(230, 200, 255);//배경색으로 한다   
			}
		}
		else
		{
			if (l_nItem == m_CurrentStep - 1)
			{
				crText = RGB(0, 0, 0); //글자색
				crBkgnd = RGB(255, 255, 0); //배경색으로 한다 


			}
			else
			{
				crText = RGB(0, 0, 0); //글자색
				crBkgnd = RGB(230, 200, 255);//배경색으로 한다   
			}
		}


		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;


		*pResult = CDRF_DODEFAULT;
		return;
	}
	}

	*pResult = 0;
#else
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	//int nRow=0;
	//int nCol=0;
	CString strCol=_T("");



	switch(pLVCD->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;
		}
		case CDDS_ITEMPREPAINT:
		{
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			return;
		}
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			COLORREF crText, crBkgnd;
			
		//	nCol= m_CtrlListMainProcess.getse.GetSelectedColumn();
		//	nRow= m_CtrlListMainProcess.GetItemCount();

			int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec ); //row



			if(2==(int)(pLVCD->iSubItem) )
			{
				strCol= m_CtrlListMainProcess.GetItemText(pLVCD->nmcd.dwItemSpec,2);
				if( strCol=="NG") // 두번째열의 값이 "10"일 때, 그 값 부분만			
				{
					crText = RGB(0,0,0); //글자색
					crBkgnd = RGB(255,0,0); //배경색으로 한다    
				}
				else if(2==(int)(pLVCD->iSubItem) && strCol=="OK")          
				{
					crText = RGB(0,0,0);
					crBkgnd = RGB(0,255,0);
				}	
				else
				{
					if((nItem == m_nCurrentNumber)&&(m_TaskRun != TASK_RUN_IDLE))//else if(nItem == m_Process_Index)          
					{
						crText = RGB(0,0,0);
						crBkgnd = RGB(255,255,100);
					}
					else 
					{
						crText = RGB(0,0,0);
						crBkgnd = RGB(255,255,255);
					}
				}
		
			}
			else
			{
				//int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec ); //row
				//m_TaskRun;m_Process_Index
	//int		m_nCurrentNumber;
				if((nItem == m_nCurrentNumber)&&(m_TaskRun != TASK_RUN_IDLE))
				{
					//if(pLVCD->iSubItem >= 1)
					{
						crText = RGB(0,0,0);
						crBkgnd = RGB(255,255,100);
					}
			
				}
				else
				{

					crText = RGB(0,0,0);
					crBkgnd = RGB(255,255,255);
				}
			}

			pLVCD->clrText = crText;
			pLVCD->clrTextBk= crBkgnd;			


			*pResult = CDRF_DODEFAULT; 
			return;
		}
	}
	
	*pResult = 0;
#endif
}


//
//void CAcqVoltageSamples_IntClkDlg::ProcessOcr()
//{
//	if(g_CameraFound == 0)
//		return;
//
//	Mat src_Mat;
//	Mat org_Mat;
//	Mat gray_Mat;
//	Mat edge_Mat;
//	Mat edgeGray_Mat;
//
//
//	Mat image(Template_Rslt);
//
//	Mat imageGray(image.rows, image.cols, 1);
//	
//	Mat imageThres;
//	Mat imageThres2;
//	Mat imageThres3;
//
//	cvtColor(image,imageGray,CV_BGR2GRAY);
//	cv::GaussianBlur(imageGray, imageGray, cv::Size(0,0), 0.5 );	
//
//#ifdef __IMAGE_DEBUG__
//	imshow("blur",imageGray);
//#endif
//
//	//이미지 선명하게
//	Mat sharpen_image;
//	
//	Mat sharpen_kernel = (Mat_<char>(3,3) << -1,-1, -1,
//											-1, 9, -1,
//											-1, -1, -1);
//
//	
//	Mat sharpen_kernel2 = (Mat_<char>(3,3) << -1,-1, -1,
//											-1, 9, -1,
//											-1, -1, -1);
//	
//	filter2D(imageGray, sharpen_image, imageGray.depth(), sharpen_kernel2);
//
//	sharpen_image.convertTo(gray_Mat,CV_8UC1);
//
//	Canny(gray_Mat,edge_Mat,tres1,tres2);
//	
//	gray_Mat.copyTo(edgeGray_Mat);
//	EdgeGray(&gray_Mat, &edge_Mat, &edgeGray_Mat);	
//	
//	threshold(edgeGray_Mat,imageThres, mTres, mTresMax, CV_THRESH_BINARY);
//
//	threshold(sharpen_image,imageThres2, mTres, mTresMax, CV_THRESH_BINARY);
//
//	adaptiveThreshold(sharpen_image,imageThres3,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,5,tres2);
//	
//
//#ifdef __IMAGE_DEBUG__	//#endif
//
//	imshow("sharpen_image",sharpen_image);
//	imshow("thres",imageThres);
//	imshow("thres2",imageThres2);
//	imshow("thres3",imageThres3);
//#endif
//
//	
//	for ( int i = 0 ; i < nErode; i++ )
//	{
//		erode(imageThres2,imageThres2,Mat());
//		//cvErode( edgeGray_Mat, edgeGray_Mat,0,1);
//	}
//
//	for ( int i = 0 ; i < nDilate ; i ++)
//	{
//		dilate(imageThres2,imageThres2,Mat());
//		//cvDilate (edgeGray, edgeGray);
//	}
//
//	
//	//mX,mY;	
//	//int mXW,mYH
//	//	int m_ocrX,m_ocrY;	
//	//int m_ocrXW,m_ocrYH;
//	int lx = m_ocrX - mX ;
//	int ly = m_ocrY - mY ;
//
//	if(lx < 0)
//		lx = 0;
//
//	if(ly < 0)
//		ly = 0;
//
////	Mat crop = imageThres2(Rect(0,imageThres.size().height/6*2,imageThres.size().width,imageThres.size().height/6*3));
//	Mat crop = imageThres2(Rect(lx,ly, m_ocrXW, m_ocrYH));
//	//Mat crop = sharpen_image(Rect(lx,ly, m_ocrXW, m_ocrYH));
//#ifdef __IMAGE_DEBUG__	//#endif		
//	imshow("crop",crop);
//#endif
//
////	DisplayImage2(&IplImage(crop));//	DisplayImage(&IplImage(org_img));
//
//	char *outText;
//	api.SetImage((uchar*)crop.data,crop.size().width,crop.size().height,crop.channels(),crop.step1());
//	
//	outText = api.GetUTF8Text();
//	GetDlgItem(IDC_EDIT_RSLT)->SetWindowTextA(outText);		
//}


//void CAcqVoltageSamples_IntClkDlg::EdgeGray(cv::Mat *gray, cv::Mat *edge, cv::Mat *outImage)
//{
//	for(int y = 0; y < gray->rows; ++y){
//		uchar *gpt = (uchar*)(gray->data + gray->step1() * y);
//		uchar *ept = (uchar*)(edge->data + edge->step1() * y);
//		uchar *opt = (uchar*)(outImage->data + outImage->step1() * y);
//
//		for(int x = 0; x < gray->cols; ++x){
//			if(*ept == 255)
//				*opt = 0;
//			else
//				*opt = *gpt;
//			++gpt;
//			++ept;
//			++opt;
//		}
//	}
//}
//
//
//void CAcqVoltageSamples_IntClkDlg::DisplayImage(IplImage* img)
//{
//	IplImage* img_resize=NULL;
////	IplImage* img_orgsize=NULL;
//
//	CRect prevRect = rect;
//
//
//	ResizeImage(img,&img_resize,&rect);
//
//	DisplayBitmap(&memDC,rect,img_resize);
//	
//	//나머지 공간 흰색으로 채우기
//	//m_pDC->PatBlt(0,0,prevRect.Width(), prevRect.Height(), WHITENESS);
//	m_pDC->BitBlt(0,0,img_resize->width,img_resize->height,&memDC,0,0,SRCCOPY);
//	
//	if(img_resize)
//	{
//		cvReleaseImage(&img_resize);
//	}
//}
//
//
//
//void CAcqVoltageSamples_IntClkDlg::SelectImage()
//{
//	////이미지 처리
//	//Mat org_img;
//	////org_img = cvarrToMat(src);
//	//org_img = src_Mat;//Mat showMat;
//
//	////int x,y,h,s,v;
//	////
//
//	////	CvPoint point1,point2;
//	////	CvScalar scal= {255,255,255};
//	////if(m_CheckSelect.GetCheck())
//	////{
//	////
//	////	point1.x = mX;
//	////	point1.y = mY;
//	////	
//	////	point2.x = mX + mXW;
//	////	point2.y = mY + mYH;
//	////	
//	////	
//	////	scal.val[0]= 255;
//	////	scal.val[1]= 255;
//	////	scal.val[2]= 255;
//	////	cvRectangle(&IplImage(org_img),point1,point2,scal,2);
//	////}
//	////else
//	////{
//
//	////	//int m_ocrX,m_ocrY;	
//	////	//int m_ocrXW,m_ocrYH;	
//
//	////	point1.x = m_ocrX;
//	////	point1.y = m_ocrY;
//	////	
//	////	point2.x = m_ocrX + m_ocrXW;
//	////	point2.y = m_ocrY + m_ocrYH;
//
//	////	scal.val[0]= 0;
//	////	scal.val[1]= 255;
//	////	scal.val[2]= 255;
//	//////	scal.val[3]= 0,255,255};
//	////	cvRectangle(&IplImage(org_img),point1,point2,scal,2);
//	////}
//
//	////	
//	////int lx,ly,lw,lh;
//	////lx = 500;//org_img.cols*0.8;
//	////ly = 500;//org_img.rows*0.8;
//	////lw = 500;//org_img.cols*0.8;
//	////lh = 500;//org_img.rows*0.8;
//	//////m_point1,m_point2
//	//////Template_Rslt = org_img(cv::Rect(org_img.cols*0.8, org_img.rows*0.8, org_img.cols*0.8, org_img.rows*0.8));
//	//////Template_Rslt = org_img(cv::Rect(lx,ly,lw,lh));
//
//	//DisplayImage(&IplImage(org_img));
//
//
//
//}
//
//void CAcqVoltageSamples_IntClkDlg::ResizeImage(IplImage* src_img, IplImage** dst_img, CRect* rect)
//{
//	//int ndst_width=0,ndst_height=0;
//	////먼저 영상의 가로와 세로중 장축을 구한다.
//	//
//
//	//if(src_img->width/rect->Width() > src_img->height/rect->Height())
//	//{
//	//	ndst_width  = rect->Width();
//	//	if ( src_img->width > 0 )
//	//		ndst_height  = (src_img->height * rect->Width()) / src_img->width; 
//
//	//	rect->right   = rect->left + ndst_width;
//	////	rect->top = rect->top  + rect->Height()/2 - ndst_height/2;
//	//	rect->bottom  = rect->top + ndst_height;
//	//}
//	//else
//	//{
//	//	if ( src_img->height > 0 )
//	//		ndst_width  = (src_img->width * rect->Height()) / src_img->height;
//	//	ndst_height  = rect->Height(); 
//
//	//	//rect->left = rect->left  + rect->Width()/2 - ndst_width/2;
//	//	rect->right   = rect->left + ndst_width;
//	//	rect->bottom  = rect->top + ndst_height;
//	//}
//
//	//(*dst_img) = cvCreateImage(cvSize(ndst_width,ndst_height),IPL_DEPTH_8U,src_img->nChannels);
//	//
//	//cvResize(src_img,(*dst_img));
//}

//void CAcqVoltageSamples_IntClkDlg::ResizeImage(IplImage* src_img, IplImage** dst_img, CRect* rect)
//{
//	int ndst_width=0,ndst_height=0;
//	//먼저 영상의 가로와 세로중 장축을 구한다.
//
//	if(src_img->width > src_img->height)
//	{
//		ndst_width  = rect->Width();
//		if ( src_img->width > 0 )
//			ndst_height  = (src_img->height * rect->Width()) / src_img->width; 
//	}
//	else
//	{
//		if ( src_img->height > 0 )
//			ndst_width  = (src_img->width * rect->Height()) / src_img->height;
//		ndst_height  = rect->Height(); 
//	}
//
//	(*dst_img) = cvCreateImage(cvSize(ndst_width,ndst_height),IPL_DEPTH_8U,src_img->nChannels);
//	
//	cvResize(src_img,(*dst_img));
//	rect->right   = rect->left + ndst_width;
//	rect->bottom  = rect->top + ndst_height;
//}
//

//void CAcqVoltageSamples_IntClkDlg::DisplayBitmap(CDC* pDC, CRect rect, IplImage* img)
//{
//	BITMAPINFO bitmapInfo;
//	bitmapInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
//	bitmapInfo.bmiHeader.biPlanes=1;
//	bitmapInfo.bmiHeader.biCompression=BI_RGB;
//	bitmapInfo.bmiHeader.biXPelsPerMeter=100;
//	bitmapInfo.bmiHeader.biYPelsPerMeter=100;
//	bitmapInfo.bmiHeader.biClrUsed=0;
//	bitmapInfo.bmiHeader.biClrImportant=0;
//	bitmapInfo.bmiHeader.biSizeImage=0;
//	bitmapInfo.bmiHeader.biWidth=img->width;
//	bitmapInfo.bmiHeader.biHeight=-img->height;
//
//	if (img->nChannels == 3)
//	{
//		bitmapInfo.bmiHeader.biBitCount=img->depth * img->nChannels;
//		pDC->SetStretchBltMode(COLORONCOLOR);
//		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
//		0, 0, img->width, img->height, img->imageData, &bitmapInfo,
//		DIB_RGB_COLORS, SRCCOPY);
//	}
//	else
//	{
//		pDC->SetStretchBltMode(COLORONCOLOR);
//		IplImage * tmp = cvCreateImage(cvGetSize(img),img->depth,3);
//		cvCvtColor(img,tmp,CV_GRAY2BGR);
//
//		bitmapInfo.bmiHeader.biBitCount=tmp->depth * tmp->nChannels;
//		
//		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
//		0, 0, tmp->width, tmp->height, tmp->imageData, &bitmapInfo,
//		DIB_RGB_COLORS, SRCCOPY);
//		cvReleaseImage(&tmp);
//		delete tmp;
//	}
//}
//
//
//void CAcqVoltageSamples_IntClkDlg::OnStnDblclickStaticPic()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	
//}
//
//
//void CAcqVoltageSamples_IntClkDlg::OnStnClickedStaticPic()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDlgImage ldlg;
//	ldlg.DoModal();
//}
BEGIN_EVENTSINK_MAP(CAcqVoltageSamples_IntClkDlg, CDialog)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_CAMREA_NAME, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelCamreaName, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabel, VTS_DISPATCH)
//	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG1, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelOK1, VTS_DISPATCH)
//	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG2, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelOK2, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_COM_GMES, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelComGmes, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_COM_MAIN, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelComMain, VTS_DISPATCH)
//	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG1, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelOK1, VTS_NONE)
//	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG2, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelOK2, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_CHECK_TIME, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelCheckTime, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_NG_CNT, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelNgCnt, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_MANAGER, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelManager, VTS_DISPATCH)
	
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_IMAGE_SET, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelImageSet, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_IMAGE_SAVE_AS, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelImageSaveAs, VTS_NONE)

	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_BARCODE_MARK, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelBarcodeMark, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__NAME1, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelName1, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__NAME2, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelName2, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__NAME3, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelName3, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__NAME4, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelName4, VTS_NONE)
END_EVENTSINK_MAP()


void CAcqVoltageSamples_IntClkDlg::ClickLabelCamreaName()
{
//	static int 
	/*if(m_nSource < 3)
	{
		m_nSource++;
	}
	else
	{
		m_nSource = 1;
	}*/


	if(m_nSource == 1)
	{
		m_nSource++;
		SetInputVideo( m_nSource);
	}
	else if(m_nSource == 2)
	{
		m_nSource++;
		SetInputVideo( m_nSource);
	}
	else if(m_nSource == 3)
	{
		m_nSource = 1;
		SetInputVideo( m_nSource);
	}
	else
	{
		SetInputVideo( 1);
		m_nSource = 1;
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//if(g_CameraFound == 0)
	//{
	//	return;
	//}
	//if(gbManualScopeMode)
	//{
	//	MessageBox("MANUAL SCOPE MODE!!");
	//	return;

	//}
	//if(m_TaskRun != TASK_RUN_IDLE)
	//{	
	//	
	//	return;
	//}
	//m_Camera_Capture_Flag = 0;//m_Camera_Capture_Flag = 1;
	//CDlgImage ldlg;
	//if(g_CameraFound == 1)
	//{
	//	ldlg.m_ImageFileName = m_strCameraCheckIMGfile;
	//	ldlg.DoModal();
	//}
	//else
	//{
	//	MessageBox("Camrea Not Connected!");
	//}
	//	
	//if(g_CameraFound == 1)
	//	m_Camera_Capture_Flag = 1;//m_Camera_Capture_Flag = 1;
}


void CAcqVoltageSamples_IntClkDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//SetChannelData(0);
	//InitChannel();
	//if(m_InitAiChannel == 0)
	//{
	//	MessageBox("Audio Capture Card INIT FAIL!!");
	//	g_NIAuioBoardFail = 1;//AUDIO Board Fail
	//}
	m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
	CDialog::OnRButtonDblClk(nFlags, point);
}

void CAcqVoltageSamples_IntClkDlg::SendOkSignalToJig()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(g_SetComOnlyMode == 1)
	{
		return;
	}
	BYTE lbuf[128]; 
	//int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CSENDOK01");
  //sprintf((char *)&lbuf[1], "CMAC_READ");
	
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	

	memcpy(m_SendBufLED, lbuf, 13); 	
	m_SendCntLED = 13;

	//ComLedRead();

	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	
}

void CAcqVoltageSamples_IntClkDlg::SendNGSignalToJig(int lON)//m_NG_SignalON
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(g_SetComOnlyMode == 1)
	{
		return;
	}

	
	BYTE lbuf[128];

	lbuf[0] = 0x02;		
	if(lON)
	{
		sprintf((char *)&lbuf[1], "CDOUT02ON");
		m_NG_SignalON = 1;
		SetTimeCheck(TIME_CHECK_NG_OUTPUTL_DELAYTIME);
	}
	else
	{
		sprintf((char *)&lbuf[1], "CDOUT02OF");	
		m_NG_SignalON = 0;
	}
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	

	memcpy(m_SendBufLED, lbuf, 13); 	
	m_SendCntLED = 13;

	//ComLedRead();


	

	//lbuf[0] = 0x02;		
	//sprintf((char *)&lbuf[1], "CDOUT02OF");	
	//lbuf[10] = 0x03;
	//lbuf[11] = 0x0d;
	//lbuf[12] = 0x0a;
	//

	//memcpy(m_SendBufLED, lbuf, 13); 	
	//m_SendCntLED = 13;

	//ComLedRead();




	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	
	
	//unsigned long GetTimeCheck(int  lIndex);
	
}

void CAcqVoltageSamples_IntClkDlg::NG_Display(CString lstr)
{

	mpDlgSimpleInform->ShowWindow(SW_HIDE);

	gSaveInfo.strTestDiscription = m_GMES_ErrorName;
	gSaveInfo.strTestDiscription += m_GMES_ErrorValue;


	mpDlgResult->m_DisplayString = m_Deisplay_ErrorName;//m_GMES_ErrorName;
	mpDlgResult->m_DetailMessage = m_Deisplay_ErrorDetail;//m_GMES_ErrorValue;
	CString m_NgWaveFile  = _T(PATH_BASE_DIR);
	m_NgWaveFile  += _T("\\Sound\\NG_CHECK.wav");//OK_CHECK.wav

	sndPlaySound( m_NgWaveFile , SND_ASYNC);
	Beep(1200, 300);
	/*	if(ldlg.DoModal() == IDOK)
		{
		}*/

	mpDlgResult->m_Barcode = "";
	mpDlgResult->m_Result = 0;
	mpDlgResult->m_ReturnFlag = 0;
	CRect rectP;
	CRect rect;		
		
	this->GetWindowRect(&rectP);
	mpDlgResult->GetWindowRect(&rect);

	mpDlgResult->ShowWindow(SW_SHOW);
	//mpDlgResult->SetWindowPos(this,rectP.left+ 270,rectP.top+150,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);
	mpDlgResult->SetWindowPos(this,rectP.left+ 150,rectP.top+250,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);

	if(CurrentSet->nUseUserRetry > m_NG_Retry_Count)
	{
	}
	else
	{
		SendNGSignalToJig(1);
	}

}

void CAcqVoltageSamples_IntClkDlg::OK_Display()
{

	mpDlgSimpleInform->ShowWindow(SW_HIDE);
		//CDlgResult ldlg;
		//ldlg.m_Result = 1;
		//Beep(800, 300);
		//if(ldlg.DoModal() == IDOK)
		//{
		//}
		mpDlgResult->m_Barcode = "";
		
		mpDlgResult->m_Result = 1;
		mpDlgResult->m_ReturnFlag = 0;
		CRect rectP;
		CRect rect;		
		
		this->GetWindowRect(&rectP);
		mpDlgResult->GetWindowRect(&rect);

		mpDlgResult->ShowWindow(SW_SHOW);
		//if (g_nRunningProcessNo == 1)
		//{
		//	mpDlgResult->SetWindowPos(this, rectP.left+50 , rectP.top + 50, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
		//}
		//else
		{
			mpDlgResult->SetWindowPos(this, rectP.left+150, rectP.top + 150, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);

		}

		gSaveInfo.strTestDiscription = "CHECK PASS";

}

void CAcqVoltageSamples_IntClkDlg::BarcodeErrorDisplay()
{
		//CDlgResult ldlg;
		//ldlg.m_Result = 1;
		//Beep(800, 300);
		//if(ldlg.DoModal() == IDOK)
		//{
		//}

		
		mpDlgBarcode->m_Barcode = "";
		mpDlgBarcode->m_ReturnFlag = 0;
		CRect rectP;
		CRect rect;		
		
		this->GetWindowRect(&rectP);
		mpDlgBarcode->GetWindowRect(&rect);

		mpDlgBarcode->ShowWindow(SW_SHOW);
		mpDlgBarcode->SetWindowPos(this,rectP.left+ 270,rectP.top+400,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);

}


void CAcqVoltageSamples_IntClkDlg::CLOSE_Result_Display()
{
	if(mpDlgResult->IsWindowEnabled())
	{
		if(mpDlgResult->m_Barcode.GetLength() > 6)
		{
			m_BarCode.put_Caption(mpDlgResult->m_Barcode);
		}
	}
	mpDlgResult->ShowWindow(SW_HIDE);
	mpDlgBarcode->ShowWindow(SW_HIDE);
	mpDlgSimpleInform->ShowWindow(SW_HIDE);		
	m_pUserMsgDlg->ShowWindow(SW_HIDE);

	//CDlgResult ldlg;
		//ldlg.m_Result = 1;
		//Beep(800, 500);
		//if(ldlg.DoModal() == IDOK)
		//{
		//}
}

CString CAcqVoltageSamples_IntClkDlg::GetMyIPAddress()
{
    char        chName[255];
    CString        sAddress;
    PHOSTENT    pHostEntry;
    IN_ADDR        inAddr;

    if( gethostname( chName, 255 ) != 0 ) return "";
    else
    {
        if( ( pHostEntry = gethostbyname( chName ) ) == NULL ) return "";
        else
        {
            memcpy( &inAddr, pHostEntry->h_addr, 4 );
            sAddress.Format( "%s", inet_ntoa( inAddr ) );
            return sAddress;
        }
    }
}

void CAcqVoltageSamples_IntClkDlg::DblClickLabel(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//
	//if(m_TaskRun != TASK_RUN_IDLE) 
	//{
	//	MessageBox("TEST PROCESSING");
	//	return;
	//}

	//if(gbManualScopeMode == 1)		
	//{

	//	gbManualScopeMode = 0;
	//	SetGuiPos(gbManualScopeMode);

	//	SetChannelData(0);
	//	
	//	InitChannel();
	//	if(m_InitAiChannel == 0)
	//	{
	//		MessageBox("Audio Capture Card INIT FAIL!!");
	//		g_NIAuioBoardFail = 1;//AUDIO Board Fail
	//	}

	//	m_cLbOkNg.put_Caption(_T("WAIT"));
	//	m_cLbOkNg.put_BackColor(0x0000FFFF);
	//	Invalidate();
	//}
	//else
	//{
	//	g_ManualId[0] = 4;
	//	g_ManualId[1] = 5;
	//	g_ManualId[2] = 6;
	//	g_ManualId[3] = 7;
	//	g_ManualId[4] = 0;
	//	g_ManualId[5] = 1;
	//	g_ManualId[6] = 2;
	//	g_ManualId[7] = 3;


	//	gbManualScopeMode = 1;
	//	SetGuiPos(gbManualScopeMode);	
	//	
	//	
	//	SetChannelDataManual(0);
	//	
	//	InitChannel();
	//	if(m_InitAiChannel == 0)
	//	{
	//		MessageBox("Audio Capture Card INIT FAIL!!");
	//		g_NIAuioBoardFail = 1;//AUDIO Board Fail
	//	}
	//	m_cLbOkNg.put_Caption(_T("SCOPE MODE"));
	//	m_cLbOkNg.put_BackColor(0x0000FFFF);
	//	
	//	//m_cLb_Test1.put_Caption(_T("MIC1"));
	//	//m_cLb_Test1.put_BackColor(0x0000FFFF);
	//
	//	//m_cLb_Test2.put_Caption(_T("MIC2"));
	//	//m_cLb_Test2.put_BackColor(0x0000FFFF);
	//


	//	Invalidate();
	//}
}

//
//void CAcqVoltageSamples_IntClkDlg::SetGuiPos(int IsScopeMode)
//{	
//	return;
//	int Xoffset = 10;
//
//	GetDlgItem(IDC_PREVIEW_BOX)->SetWindowPos(NULL, Xoffset, 110, 640, 360, SWP_ASYNCWINDOWPOS);
//	m_CtrlListMainProcess.SetWindowPos(NULL, 645 + Xoffset, 110, 280, 515, SWP_ASYNCWINDOWPOS);//1015
//
//
//
//	if(IsScopeMode)
//	{
//
//
//		 Xoffset = -20;
//	//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
//		m_cComboName[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_cComboName[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//		m_cLb_Test1.SetWindowPos(NULL,235+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//		//m_cLb_Test1.SetWindowPos(NULL,1600+35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//		//m_cLb_Test1.put_Caption("MIC1");
//		//m_cLb_Test1.put_BackColor(0x0000FFFF);
//	//	m_cLb_Test1.Invalidate();
//
//		/////////////
//		m_cComboName[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_cComboName[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//		//m_cLb_Test2.SetWindowPos(NULL,1600+345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//		m_cLb_Test2.SetWindowPos(NULL,545+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//		//m_cLb_Test2.put_Caption("MIC2");
//		//m_cLb_Test2.put_BackColor(0x0000FFFF);
//	/*	RECT lRect;
//		lRect.top = 540+95;
//		lRect.bottom = 540+95+30;
//		lRect.left = 35+Xoffset;
//		lRect.top = 35+Xoffset +345+ 80+300+80 ;
//		InvalidateRect(&lRect);*/
//	//	m_cLb_Test2.Invalidate();
//
//		m_cComboName[4].SetWindowPos(NULL,655+80*2+Xoffset, 150, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[4].SetWindowPos(NULL,775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[4].SetWindowPos(NULL,865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_cComboName[5].SetWindowPos(NULL,655+80*2+Xoffset, 345+45, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[5].SetWindowPos(NULL,775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[5].SetWindowPos(NULL,865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//		m_cLb_Test3.SetWindowPos(NULL,1600+655+80*2+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//	//m_cLb_Test3.SetWindowPos(NULL,655+80*2+Xoffset, 540+95, 100,30,SWP_ASYNCWINDOWPOS);
//
//			
//		//m_cLbDisplayMark.SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 500, 28,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_PREVIEW_BOX)->SetWindowPos(NULL,1600+1205+Xoffset, 150, 325, 240,SWP_ASYNCWINDOWPOS);
//
//		
//		m_cLB_ImageSet.SetWindowPos(NULL,1600+670+80*2+Xoffset, 560, 200, 30,SWP_ASYNCWINDOWPOS);
//		m_cLB_ImageSaveAs.SetWindowPos(NULL,1600+910+80*2+Xoffset, 560, 200, 30,SWP_ASYNCWINDOWPOS);
//
//		m_cComboName[6].SetWindowPos(NULL,965+80*3+Xoffset, 150, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[6].SetWindowPos(NULL,1600+965+80*3+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[6].SetWindowPos(NULL,1085+80*3+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[6].SetWindowPos(NULL,1175+80*3+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,965+80*3+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_cComboName[7].SetWindowPos(NULL,965+80*3+Xoffset, 345+45, 120+10, 330,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[7].SetWindowPos(NULL,1600+965+80*3+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[7].SetWindowPos(NULL,1085+80*3+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[7].SetWindowPos(NULL,1175+80*3+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,965+80*3+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//		m_CtrlListMainProcess.SetWindowPos(NULL,1600+1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
//		//GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 380, 110,SWP_ASYNCWINDOWPOS);
//
//		
//	//	m_cLabelCableManager.SetWindowPos(NULL,1205+Xoffset, 575+95, 220, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cLabelCableMessage.SetWindowPos(NULL,1205+Xoffset, 575+125, 220, 80,SWP_ASYNCWINDOWPOS);
//		
//		m_cLabelCableManager.SetWindowPos(NULL,1325+Xoffset, 575+95, 275, 26,SWP_ASYNCWINDOWPOS);
//		m_cLabelCableMessage.SetWindowPos(NULL,1325+Xoffset, 573+125, 275, 82,SWP_ASYNCWINDOWPOS);
//
//
//	
//		//965
//	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
//	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125
//
//	//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
//		m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+255,35,SWP_ASYNCWINDOWPOS);
//
//		//95
//
//
//		m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
//		m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
//		/*	
//		m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
//		m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
//	*/
//		m_CheckTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 688+95, 110,18,SWP_ASYNCWINDOWPOS);
//		m_CycleTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 707+95, 110,18,SWP_ASYNCWINDOWPOS);
//		m_CheckTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 688+95, 85,18,SWP_ASYNCWINDOWPOS);
//		m_CycleTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 707+95, 85,18,SWP_ASYNCWINDOWPOS);
//
//	
//		
//		m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 820,110,SWP_ASYNCWINDOWPOS);//345+80+Xoffset, 540+95, 300+80  // 310+300+80
////		m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 720+240,110,SWP_ASYNCWINDOWPOS);
//
//	
//		m_LanLabelName.SetWindowPos(NULL,35+Xoffset, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_Usb1LabelName.SetWindowPos(NULL,35+Xoffset, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_Usb2LabelName.SetWindowPos(NULL,35+Xoffset, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_CameraLabelName.SetWindowPos(NULL,35+Xoffset, 659+95, 80,26,SWP_ASYNCWINDOWPOS);
//
//		m_cLb_Lan.SetWindowPos(NULL,115+Xoffset, 575+95, 110,26,SWP_ASYNCWINDOWPOS);
//		m_cLb_Usb1.SetWindowPos(NULL,115+Xoffset, 603+95, 110,26,SWP_ASYNCWINDOWPOS);
//		m_cLb_Usb2.SetWindowPos(NULL,115+Xoffset, 631+95, 110,26,SWP_ASYNCWINDOWPOS);
//		m_cLb_Camera.SetWindowPos(NULL,115+Xoffset, 659+95, 110,26,SWP_ASYNCWINDOWPOS);
//
//		m_cLb_ComMain.SetWindowPos(NULL,	40+Xoffset + 775+255,	575+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComSet.SetWindowPos(NULL,		40+Xoffset + 775+255,	603+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComLed.SetWindowPos(NULL,		40+Xoffset + 775+255,	631+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComMainGmes.SetWindowPos(NULL,40+Xoffset + 775+255,	659+95, 245,	26,SWP_ASYNCWINDOWPOS);
//
//
//	}
//	else
//	{
//		 Xoffset = 10;
//
//
//
////	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
//		m_NameLabel[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_NameLabel[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//		//m_cLb_Test1.SetWindowPos(NULL,35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//
//		/////////////
//		m_NameLabel[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_NameLabel[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
////		m_cLb_Test2.SetWindowPos(NULL,345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//
//		m_NameLabel[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[4].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[4].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_NameLabel[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[5].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[5].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//	//	m_cLb_Test3.SetWindowPos(NULL,655+80*2+Xoffset, 540+95, 500,30,SWP_ASYNCWINDOWPOS);
//
//
//
//
//		m_NameLabel[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[6].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[6].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//		m_NameLabel[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_cComboName[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//		m_FreqLabel[7].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		m_VoltLabel[7].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//		//m_cLbDisplayMark.SetWindowPos(NULL,655+80*2+Xoffset, 150, 500, 28,SWP_ASYNCWINDOWPOS);
//		GetDlgItem(IDC_PREVIEW_BOX)->SetWindowPos(NULL,Xoffset, 180, 640, 360,SWP_ASYNCWINDOWPOS);
//
//		m_cLB_ImageSet.SetWindowPos(NULL,670+80*2+Xoffset, 560, 200, 30,SWP_ASYNCWINDOWPOS);
//		m_cLB_ImageSaveAs.SetWindowPos(NULL,910+80*2+Xoffset, 560, 200, 30,SWP_ASYNCWINDOWPOS);
//
//	//	m_CtrlListMainProcess.SetWindowPos(NULL,1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
//		m_CtrlListMainProcess.SetWindowPos(NULL,1325+Xoffset, 150, 275, 515,SWP_ASYNCWINDOWPOS);//1015
//		//GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 400, 300,SWP_ASYNCWINDOWPOS);
//
//	
//		//965
//	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
//	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125
//
//	//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
//		m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+300,35,SWP_ASYNCWINDOWPOS);
//
//		//95
//
//
//		m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
//		m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
//		m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
//
//		m_CheckTimeLabelName.SetWindowPos(NULL,1425+Xoffset, 688+95, 80,18,SWP_ASYNCWINDOWPOS);
//		m_CycleTimeLabelName.SetWindowPos(NULL,1425+Xoffset, 707+95, 80,18,SWP_ASYNCWINDOWPOS);
//		m_CheckTimeLabel.SetWindowPos(NULL,1510+Xoffset, 688+95, 80,18,SWP_ASYNCWINDOWPOS);
//		m_CycleTimeLabel.SetWindowPos(NULL,1510+Xoffset, 707+95, 80,18,SWP_ASYNCWINDOWPOS);
//	
//		m_cLbOkNg.SetWindowPos(NULL,35+Xoffset, 575+95, 770,110,SWP_ASYNCWINDOWPOS);//345+80+Xoffset, 540+95, 300+80  // 310+300+80
//		
//		m_LanLabelName.SetWindowPos(NULL,	40+Xoffset + 775, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_Usb1LabelName.SetWindowPos(NULL,	40+Xoffset + 775, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_Usb2LabelName.SetWindowPos(NULL,	40+Xoffset + 775, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
//		m_CameraLabelName.SetWindowPos(NULL,40+Xoffset + 775, 659+95, 80,26,SWP_ASYNCWINDOWPOS);
//
//		m_cLb_Lan.SetWindowPos(NULL,	121+Xoffset + 775, 575+95, 168,	26,	SWP_ASYNCWINDOWPOS);
//		m_cLb_Usb1.SetWindowPos(NULL,	121+Xoffset + 775, 603+95, 168,	26,	SWP_ASYNCWINDOWPOS);
//		m_cLb_Usb2.SetWindowPos(NULL,	121+Xoffset + 775, 631+95, 168,	26,	SWP_ASYNCWINDOWPOS);
//		m_cLb_Camera.SetWindowPos(NULL,	121+Xoffset + 775, 659+95, 168,	26,	SWP_ASYNCWINDOWPOS);
//	
//		m_cLb_ComMain.SetWindowPos(NULL,	40+Xoffset + 775+255,	575+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComSet.SetWindowPos(NULL,		40+Xoffset + 775+255,	603+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComLed.SetWindowPos(NULL,		40+Xoffset + 775+255,	631+95, 245,	26,SWP_ASYNCWINDOWPOS);
//		m_cLb_ComMainGmes.SetWindowPos(NULL,40+Xoffset + 775+255,	659+95, 245,	26,SWP_ASYNCWINDOWPOS);
//
//		m_cLabelCableManager.SetWindowPos(NULL,1325+Xoffset, 575+95, 275, 26,SWP_ASYNCWINDOWPOS);
//		m_cLabelCableMessage.SetWindowPos(NULL,1325+Xoffset, 573+125, 275, 82,SWP_ASYNCWINDOWPOS);
//	////	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
//	//	m_NameLabel[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//	//	m_NameLabel[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Test1.SetWindowPos(NULL,35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Test1.put_Caption("WAIT");
//	//	/////////////
//	//	m_NameLabel[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//	//	m_NameLabel[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Test2.SetWindowPos(NULL,345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Test2.put_Caption("WAIT");
//
//	//
//	//	GetDlgItem(IDC_PREVIEW_BOX)->SetWindowPos(NULL,1205+Xoffset, 150, 325, 240,SWP_ASYNCWINDOWPOS);
//
//	//	m_NameLabel[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[4].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[4].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//	//	m_NameLabel[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[5].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[5].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Test3.SetWindowPos(NULL,1600+655+80*2+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
//
//	//	m_NameLabel[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[6].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[6].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//
//	//	m_NameLabel[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cComboName[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
//	//	m_FreqLabel[7].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	m_VoltLabel[7].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
//	//	GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
//
//	//	m_CtrlListMainProcess.SetWindowPos(NULL,1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
//	////	GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 380, 110,SWP_ASYNCWINDOWPOS);
//
//	//	m_cLabelCableManager.SetWindowPos(NULL,1305+Xoffset, 575+95, 220, 30,SWP_ASYNCWINDOWPOS);
//	//	m_cLabelCableMessage.SetWindowPos(NULL,1305+Xoffset, 575+125, 220, 80,SWP_ASYNCWINDOWPOS);
//
//	//
//	//	//965
//	////	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
//	////	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125
//
//	////	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
//	//	m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+255,35,SWP_ASYNCWINDOWPOS);
//
//	//	//95
//
//
//	//	m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
//	//	m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
//	//	m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
//	//	m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
//	//	/*	
//	//	m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
//	//	m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
//	//	m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
//	//	m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
//	//*/
//	//	m_CheckTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 688+95, 110,18,SWP_ASYNCWINDOWPOS);
//	//	m_CycleTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 707+95, 110,18,SWP_ASYNCWINDOWPOS);
//	//	m_CheckTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 688+95, 85,18,SWP_ASYNCWINDOWPOS);
//	//	m_CycleTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 707+95, 85,18,SWP_ASYNCWINDOWPOS);
//
//	//
//
//	//	m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 720+240,110,SWP_ASYNCWINDOWPOS);
//
//	//
//	//	m_LanLabelName.SetWindowPos(NULL,35+Xoffset, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
//	//	m_Usb1LabelName.SetWindowPos(NULL,35+Xoffset, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
//	//	m_Usb2LabelName.SetWindowPos(NULL,35+Xoffset, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
//	//	m_CameraLabelName.SetWindowPos(NULL,35+Xoffset, 659+95, 80,26,SWP_ASYNCWINDOWPOS);
//
//	//	m_cLb_Lan.SetWindowPos(NULL,115+Xoffset, 575+95, 110,26,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Usb1.SetWindowPos(NULL,115+Xoffset, 603+95, 110,26,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Usb2.SetWindowPos(NULL,115+Xoffset, 631+95, 110,26,SWP_ASYNCWINDOWPOS);
//	//	m_cLb_Camera.SetWindowPos(NULL,115+Xoffset, 659+95, 110,26,SWP_ASYNCWINDOWPOS);
//	}
//}

void CAcqVoltageSamples_IntClkDlg::ManualSelchangePort(int lport)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for(int  i = 0; i < 8; i++)
	{
		g_ManualId[i] = m_cComboName[i].GetCurSel();
	}

	CFileControl lFile;

	lFile.SaveINIModel();
	SetChannelDataManual(lport);


}

void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort( 0);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(1);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(2);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(3);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(4);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(5);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(6);
}
void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ManualSelchangePort(7);
}


void CAcqVoltageSamples_IntClkDlg::AddGmesLog(CString LogStr, int Recv)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		
	CFileControl lFile;
	lFile.SaveGmesLOG(LogStr, Recv);
}


void CAcqVoltageSamples_IntClkDlg::AddProcessLog(CString LogStr, int New)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CFileControl lFile;
	lFile.SaveProcessLOG(LogStr, New);
}


void CAcqVoltageSamples_IntClkDlg::AddPCBLog(BYTE *LogData, int Cnt, int Rcv)
{
	
	CFileControl lFile;
	CString LogStr;
	CString StrTmp;
	if(Rcv == 1)
	{
		LogStr = ">>SET ";
	}
	else
	{
		LogStr = ">>PC ";
	}

	for(int i = 0; i < Cnt; i++)
	{
		StrTmp.Format("%02X ", LogData[i]);
		StrTmp.MakeUpper();
		LogStr += StrTmp;
	}
	lFile.SaveProcessLOG(LogStr, 0);
	ComLog_AddString(LogStr);
}




void CAcqVoltageSamples_IntClkDlg::DblClickLabelComGmes(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFileControl lFile;
	if(CurrentSet->bGMES_Connection)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		CurrentSet->bGMES_Connection = 0;
		CloseEthernetScocket() ;

		


		//lFile.SaveModel(gTestSeqData.strModelName);
		
	}
	else
	{
		CloseEthernetScocket() ;
		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		m_EthernetWaitCnt = 0;
		g_nPortReopen = 0;
		CurrentSet->bGMES_Connection = 1;
		//lFile.SaveModel(gTestSeqData.strModelName);
	}
}


void CAcqVoltageSamples_IntClkDlg::DblClickLabelComMain(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_nPreCurrentStep = 0;	
	m_nPreCurrentProcess = 0;
	m_nPreCurrentNumber = 0;
	m_PreTaskRun = TASK_RUN_START;
		
	MessageDisplay(2, "Preprocess Start");
}

void CAcqVoltageSamples_IntClkDlg::OnBnClickedButtonFreqSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	
	lbuf[0] = 0x02;

	sprintf((char *)&lbuf[1], "CFSET%03d%03d%03d%03d000000%03d%03d%03d%03d%03d%03d%03d%03d", 
		CurrentSet->nAudioGenFreq[0]/10,
		CurrentSet->nAudioGenFreq[1]/10,
		CurrentSet->nAudioGenFreq[2]/10,
		CurrentSet->nAudioGenFreq[3]/10,
		CurrentSet->nAudioGenFreq[4]/10,
		CurrentSet->nAudioGenFreq[5]/10,
		CurrentSet->nAudioGenFreq[6]/10,
		CurrentSet->nAudioGenFreq[7]/10,
		CurrentSet->nAudioGenFreq[8] / 10,
		CurrentSet->nAudioGenFreq[9] / 10,
		CurrentSet->nAudioGenFreq[10] / 10,
		CurrentSet->nAudioGenFreq[11] / 10
	);
	
	lbuf[48] = 0x03;
	lbuf[49] = 0x0d;
	lbuf[50] = 0x0a;
	lbuf[51] = 0;
	SendData(lbuf, 51, COM_ID_AUDIO_PORT);
	
	//m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	// m_ComAck =COM_ACK_WAIT;
	// m_WaitCnt = 0;
	// m_ResendCnt = 0;
	 MessageDisplay(2, "Frequency Set ALL!");

	 m_MIC_Init = 0;
}


void CAcqVoltageSamples_IntClkDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialog::OnRButtonDown(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CAcqVoltageSamples_IntClkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int lx;
	int ly ;
	int lstx;
	int lsty ;
	int lwidth;
	int lheight ;

	CRect lRect;
	CRect lMainRect;
	m_previewBox.GetWindowRect(&lRect);
	this->GetWindowRect(&lMainRect);
	lstx = lRect.left - lMainRect.left; 
	lsty = lRect.top - lMainRect.top;
	lx = point.x-lstx+7;
	ly = point.y-lsty+29;

	
	lwidth =  lRect.right - lRect.left;
	lheight =  lRect.bottom - lRect.top;


	if(m_Image_SaveMode == 1)
	{

		if((lx > 0)&&(ly > 0)&&(lx+1 < lwidth)&&(ly+1 <= lheight))
		{
	
			//unsigned int m_Height_y;
			m_Start_x = lx;
			m_Start_y = ly;
			m_End_x = lx;;
			m_End_y = ly;;
		//	m_Width_x = 1;
		//	m_Height_y = 1;

			m_SettingMode = SETTING_MODE_RANGE1;
		//	SetLoadImage("");
			//MarkEdge(m_hMemDC, lx,  ly, m_Width_x, m_Height_y);
			lRect.left = m_Start_x;
			lRect.right = m_End_x;
			lRect.top = m_Start_y;
			lRect.bottom = m_End_y;

			m_previewWindow->SetRange(1,lRect);
			m_previewWindow->m_DisplayOK = 1;
		}
		else
		{
			m_SettingMode = SETTING_MODE_IDLE;
		}

	}
	CDialog::OnLButtonDown(nFlags, point);//CDialogEx::OnLButtonDown(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_SettingMode = SETTING_MODE_IDLE;

	
	m_Rect_Image.left = m_Start_x;
	m_Rect_Image.right = m_End_x;
	m_Rect_Image.top = m_Start_y;
	m_Rect_Image.bottom = m_End_y;

	CDialog::OnLButtonUp(nFlags, point);//CDialogEx::OnLButtonUp(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if(m_SettingMode == SETTING_MODE_RANGE1)
	{
		int lx;
		int ly ;
		int lstx;
		int lsty ;
		int lwidth;
		int lheight ;

		CRect lRect;
		CRect lMainRect;
		m_previewBox.GetWindowRect(&lRect);
		this->GetWindowRect(&lMainRect);
		lstx = lRect.left - lMainRect.left; 
		lsty = lRect.top - lMainRect.top;
		
		lx = point.x-lstx+6;
		ly = point.y-lsty+29;

	
		lwidth =  lRect.right - lRect.left;
		lheight =  lRect.bottom - lRect.top;


		//if(m_Image_SaveMode == 1)
		//{

		if((lx > 0)&&(ly > 0)&&(lx+1 < lwidth)&&(ly+1 <= lheight))
		{
	
			//unsigned int m_Height_y;
			//m_Start_x = lx;
			//m_Start_y = ly;
			if(m_Start_x > lx)
			{
				m_End_x = m_Start_x;
			}
			else
			{
				m_End_x =  lx;
			}
				
			if(m_Start_y > ly)
			{
				m_End_y = m_Start_y;
			}
			else
			{
				m_End_y = ly;
			}
			
			
	

			lRect.left = m_Start_x;
			lRect.right = m_End_x;
			lRect.top = m_Start_y;
			lRect.bottom = m_End_y;

			m_previewWindow->SetRange(1,lRect);
			m_previewWindow->m_DisplayOK = 1;
		}
		else
		{
			m_SettingMode = SETTING_MODE_IDLE;
			m_previewWindow->SetRange(0,lRect);
			m_previewWindow->m_DisplayOK = 1;
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::ClickLabelOK1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static int sMic_1_Status = 1;
	if(sMic_1_Status)
	{
		sMic_1_Status = 0;
		SetFreqSend(4, 0);	
		//m_cLb_Test1.put_Caption("MIC 1 OFF");
	}
	else
	{
		sMic_1_Status = 1;
		SetFreqSend(4, 1 );
	//	m_cLb_Test1.put_Caption("MIC 1 ON");
	}
	
}


void CAcqVoltageSamples_IntClkDlg::ClickLabelOK2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static int sMic_2_Status = 1;
	if(sMic_2_Status)
	{
		sMic_2_Status = 0;
		SetFreqSend(5, 0);	
		m_cLb_Test2.put_Caption("MIC 2 OFF");
	}
	else
	{
		sMic_2_Status = 1;
		SetFreqSend(5, 1 );
		m_cLb_Test2.put_Caption("MIC 2 ON");
	}
	
}

void CAcqVoltageSamples_IntClkDlg::DblClickLabelOK1(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//SetFreqSend(4, 0);	
	//m_cLb_Test1.put_Caption("MIC 1 OFF");
}

void CAcqVoltageSamples_IntClkDlg::DblClickLabelOK2(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//SetFreqSend(5, 0);	
	//m_cLb_Test1.put_Caption("MIC 2 OFF");
}

int CAcqVoltageSamples_IntClkDlg::MessageWindow(CString str)
{
	CDlgMessage dlg;
	dlg.m_EditMessage = str;
	int rtn  = dlg.DoModal();
	return rtn;
}

CString CAcqVoltageSamples_IntClkDlg::GetModelList(CString NewName)
{
	BOOL rtnValue = 0;
	
	CString pathName;
	CString fileName;

//	int lFileRename = 0;
	//CString PathNameList[200];
	CString fileNameList[2000];
	
	//CString titleNameList[200];
	//CString  accpathName;
	//CString  ukpathName;
	//CString  chkpathName;
	char lBuf[2048];
	char ltmpBuf[2048];


	int nFileCnt = 0;
	CString str;

	CFileFind finder;
	// build a string with wildcards   
	CString strWildcard;
		

	//int nIndexPos = 0;
	BOOL bFileFound = 0;
	//BOOL rtnValue = 0;
	CFileException ex;

   
	strWildcard = PATH_BASE_DIR;
	strWildcard += _T("\\Model\\*.mdl");//"C:\\Program Files\\SM Digital\\nagra\\HDCPKey"
  
	BOOL bWorking = finder.FindFile(strWildcard);
	
	nFileCnt = 0;
	bFileFound = 0;
	while (bWorking)
	{   
		bWorking = finder.FindNextFile();
		
		// skip . and .. files; otherwise, we'd
		// recur infinitely!!
		fileName = finder.GetFileName();
		//str = (LPCTSTR)finder.GetRoot();
		//str = finder.GetFileTitle();
		pathName = finder.GetFilePath();
		//str = finder.GetFileURL();
		//str = finder.GetFileName();

	//	PathNameList[nFileCnt] = pathName;
		fileNameList[nFileCnt] = fileName;
	//	titleNameList[nFileCnt] = finder.GetFileTitle();
			
		nFileCnt++;
		if(nFileCnt >= 1000)
		{
				
			break;
		}
		bFileFound = 1;
				
	}

	finder.Close();

	CString m_strModelNameList[1000];
	CString lCheckModelName;

	if(bFileFound)
	{
		int l_nModelSelNum = 0;
		
		for(int i = 0 ; i < nFileCnt; i++)
		{
			m_strModelNameList[i] = fileNameList[i].Left(fileNameList[i].GetLength() - 4);

		
			if(m_strModelNameList[i].Find(NewName) >= 0)
			{
				lCheckModelName = m_strModelNameList[i];
				return lCheckModelName;
			}
		}

		if(lCheckModelName.GetLength() < 2)
		{		
			MessageDisplay(1, "Model Test File(*.mdl) Not Found!!");
			MessageBox("Model Test File(*.mdl) Not Found!!");
		}
	}
	else
	{
		MessageDisplay(1, "Model Test File(*.mdl) Not Found!!");
		MessageBox("Model Test File(*.mdl) Not Found!!");
	}
	return lCheckModelName;
}
//
//void CAcqVoltageSamples_IntClkDlg::ChangeModel(CString lModel)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//
//	int lGMES_Opened = 0;
//	int lGMES_Port = 0;
//	int lOldPortType = g_nRemotePortType;
////	if(g_nRemotePortType == LINE_CM89)
//
//	lGMES_Opened = CurrentSet->bGMES_Connection;
//
//
//	CString str;
//	CString lFindName;		
//	CFileControl lFile;
//	str = "Check S/N is";
//	str += lModel;
//	str += " MODEL. \r\n \r\n";
//	str += "  Do You Change MODEL ?";
//
//	m_TaskRun = TASK_RUN_IDLE;
//
//	m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
//	m_LED_COM_PROCESS = COM_MODE_IDLE;
//	m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//						//m_EthernetMode = 
//
//						//m_NG_WaitFlag = 0;
//						//TestFinishGMES();//
//						//TestFinish();
//
////	if(IDOK == MessageWindow(str))
//	if(IDYES == MessageBox(str,"New Model Detected", MB_YESNO))
//	{
//
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("1");
//#endif
//		lFindName =	GetModelList(lModel);
//		if(lFindName.GetLength() > 3)
//		{
//
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("1");
//#endif
//			if(lFile.OpenModel(lFindName))
//			{
//				MessageDisplay(2, "MODEL  FILE NOT FOUND !");
//				MessageBox("MODEL  FILE NOT FOUND !");
//				return;
//			}
//
//			if(lFile.OpenModelSeq(gTestSeqData.strSeqFileName))
//			{
//				lFile.OpenModel(gTestSeqData.strModelName);
//				MessageDisplay(2, "MODEL SEQUENCE FILE NOT FOUND !");
//				MessageBox("MODEL SEQUENCE FILE NOT FOUND !");
//				return;
//			}
//		}
//		else
//		{
//			return;
//		}
//
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("2");
//#endif
//
//		gTestSeqData.strModelName = lFindName;
//		lFile.SaveINIModel();
//
//		LoadTestData(gTestSeqData.strSeqFileName);
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("3");
//#endif
//		//SetListControl();
//		DisplayTestData();		
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("4");
//#endif
//		GetRmtCodeList(CurrentSet->sRemoconTitle);
//
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("5");
//#endif
//		str = gTestSeqData.strModelName;
//		m_cLbModel.put_Caption((LPCSTR)str);
//		m_DO_Writedata = 0;	
//#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("6");
//#endif
//		if(CurrentSet->bGMES_Connection)
//		{			
//			if(lGMES_Opened)
//			{
//				if(lOldPortType != g_nRemotePortType)
//				{
//					CloseEthernetScocket() ;
//					m_EthernetMode =  ETHERNET_MODE_IDLE;
//					m_EthernetWaitCnt = 0;
//					g_nPortReopen = 0;
//					CurrentSet->bGMES_Connection = 0;	
//
//					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
//				}
//			}
//			else
//			{
//				//CloseEthernetScocket() ;
//				m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
//				m_EthernetWaitCnt = 0;
//				g_nPortReopen = 0;
//				CurrentSet->bGMES_Connection = 1;	
//
//				m_cLb_ComMainGmes.put_BackColor(0x000000FF);
//			}
//		}
//		else
//		{
//			if(lGMES_Opened)
//			{				
//				CloseEthernetScocket() ;
//				m_EthernetMode =  ETHERNET_MODE_IDLE;
//				m_EthernetWaitCnt = 0;
//				g_nPortReopen = 0;
//			//	CurrentSet->bGMES_Connection = 1;	
//
//				m_cLb_ComMainGmes.put_BackColor(0x000000FF);
//				
//			}
//		}
//		#ifdef _CHANGE_MODEL_DEBUG__
//		MessageBox("7");
//#endif
//	}
//
//	OnBnClickedButtonFreqSet();
//
//}
//

void CAcqVoltageSamples_IntClkDlg::DblClickLabelCheckTime(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_EnableCount == 1)
	{
		m_EnableCount = 0;
	}
	else
	{
		m_EnableCount = 1;
		m_RoopCnt = 0;
	}
}


void CAcqVoltageSamples_IntClkDlg::DblClickLabelNgCnt(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	g_nNGCnt = 0;
	CFileControl lFile;
	lFile.SaveCountData();
	
	CString str;
	str.Format(_T("%d"), g_nOKCnt);	
	m_OKCntLabel.put_Caption(str);

	str.Format(_T("%d"), g_nNGCnt);	
	m_NGCntLabel.put_Caption(str);
}


void CAcqVoltageSamples_IntClkDlg::DblClickLabelManager(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CCableChangeDlg ldlg;

	ldlg.DoModal();

	
	int lcountError = 0;
	CString str = "";
	if(gCableManager.nUSB_CableCount >= gCableManager.nUSB_CableCountMax)
	{
		str = _T("Change USB Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}

	if(gCableManager.nPort_CableCount >= gCableManager.nPort_CableCountMax)
	{
		str += _T("Change Portable Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}


	if(gCableManager.nCM4CheckerCount >= gCableManager.nCM4CheckerCountMax)
	{
		str += _T("Change CM4 Checker Pin \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}	
	if(gCableManager.nCM5CheckerCount >= gCableManager.nCM5CheckerCountMax)
	{
		str += _T("Change CM5 Checker Pin \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}
	if(gCableManager.nMIC_CableCount >= gCableManager.nMIC_CableCountMax)
	{
		str += _T("Change MIC Cable \r\n");
		m_cLabelCableMessage.put_BackColor(0x00008FFF);
		lcountError++;
	}		
		
	if(lcountError > 0)
	{
	}
	else
	{
		m_cLabelCableMessage.put_BackColor(0x0008FF00);
		str += _T("\r\n\r\nCheck Cable OK\r\n");
	}
	m_cLabelCableMessage.put_Caption(str);
}


void CAcqVoltageSamples_IntClkDlg::StartCapture()
{
	bool applyDetectedInputMode = 1;//(m_applyDetectedInputModeCheckbox.GetCheck() == BST_CHECKED);

	if(m_CaptureCardEnable != 1)
	{		
		m_cLb_Camera.put_BackColor(0x0000FF);
		//m_cLb_Camera.put_Caption("NOT READY");
		return;
	}
	if(m_CaptureCardReady != 1)
	{
		NewDeviceSelect();
	}
	//else
	{
	if (m_selectedDevice &&
		m_selectedDevice->StartCapture(0, m_previewWindow, applyDetectedInputMode))
	{
		// Update UI
		//m_startStopButton.SetWindowText(_T("Stop capture"));
	//	EnableInterface(false);
		m_CaptureCardReady = 1;
		MessageDisplay(0, "Capture On");
	}
	}
}

void CAcqVoltageSamples_IntClkDlg::StopCapture()
{
	if (m_selectedDevice)
	{
		if (m_selectedDevice->IsCapturing())
		{
			m_selectedDevice->StopCapture();
		}
	}

	//MessageDisplay(0,"Capture Off", 9);
	// Update UI
	//m_startStopButton.SetWindowText(_T("Start capture"));
//	EnableInterface(true);
	//m_invalidInputLabel.ShowWindow(SW_HIDE);
}



void CAcqVoltageSamples_IntClkDlg::ShowErrorMessage(TCHAR* msg, TCHAR* title)
{
	MessageBox(msg, title);
}

void CAcqVoltageSamples_IntClkDlg::NewDeviceSelect()
{
	int		selectedDeviceIndex;

	selectedDeviceIndex = m_deviceListCombo.GetCurSel();
	if (m_deviceListCombo.GetCount() >= 1)
	{
		selectedDeviceIndex = 0;
	}
	else
	{
		return;
	}
	//if (selectedDeviceIndex < 0)
	//	return;

	m_selectedDevice = (DeckLinkDevice*)m_deviceListCombo.GetItemDataPtr(selectedDeviceIndex);

	// Update the video mode popup menu
	RefreshVideoModeList();

	// Enable the interface
	//EnableInterface(true);

	if (m_selectedDevice->SupportsFormatDetection())
		;//m_applyDetectedInputModeCheckbox.SetCheck(BST_CHECKED);
}





void CAcqVoltageSamples_IntClkDlg::RefreshVideoModeList()
{
	vector<CString>	modeNames;
	unsigned int	modeIndex = 0;

	// Clear the menu
	m_modeListCombo.ResetContent();

	// Get the mode names
	m_selectedDevice->GetDisplayModeNames(modeNames);

	// Add them to the menu
	while (modeIndex < modeNames.size())
		m_modeListCombo.AddString(modeNames[modeIndex++]);

	m_modeListCombo.SetCurSel(0);
}


void	CAcqVoltageSamples_IntClkDlg::UpdateAncillaryData(AncillaryDataStruct& ancillaryData)
{
	// Copy ancillary data under protection of critsec object
	if (m_deckLinkDiscovery == NULL)
	{
		return;
	}
	DWORD lcheck = int(&m_deckLinkDiscovery);
	if ((lcheck & 0xFF == (lcheck >> 8) & 0xFF)
		&&(lcheck & 0xFF == (lcheck >> 16) & 0xFF)
		&&(lcheck & 0xFF == (lcheck >> 24) & 0xFF))	
		{
		return;
	}
		
	m_critSec.Lock();
	m_ancillaryData = ancillaryData;
	m_critSec.Unlock();
}



void CAcqVoltageSamples_IntClkDlg::OnStartStopBnClicked()
{
	//return;
	//if (m_selectedDevice == NULL)
	//	return;
	//if(m_CaptureCardEnable != 1) 
	//{
	//	return;
	//}

	//if (m_selectedDevice->IsCapturing())
	//{
	//	StopCapture();
	//	MessageDisplay(0,"Capture Off");
	//}
	//else
	RefreshHDMI();
	CaptureControl(1);
}

void CAcqVoltageSamples_IntClkDlg::OnBnClickedStopCaptureButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CaptureControl(0);
}


void CAcqVoltageSamples_IntClkDlg::CaptureControl(int lon)
{
	//return;
	if(m_CaptureCardEnable != 1) 
	{
		m_cLb_Camera.put_BackColor(0x0000FF);
		//m_cLb_Camera.put_Caption("NOT READY");
		return;
	}
	if (m_selectedDevice == NULL)
	{
		m_cLb_Camera.put_BackColor(0x0000FF);
		//m_cLb_Camera.put_Caption("NO DEVICE");
		return;
	}
	if(lon == 0)
	{
		if (m_selectedDevice->IsCapturing())
			StopCapture();
	}
	else if(m_selectedDevice->IsCapturing() == 0)
	{
		StartCapture();
	}
}



void CAcqVoltageSamples_IntClkDlg::AddDevice(IDeckLink* deckLink)
{	
	int deviceIndex;
	DeckLinkDevice* newDevice = new DeckLinkDevice(this, deckLink);

	// Initialise new DeckLinkDevice object
	if (!newDevice->Init())
	{
		newDevice->Release();
		return;
	}

	// Add this DeckLink device to the device list
	deviceIndex = m_deviceListCombo.AddString(newDevice->GetDeviceName());
	if (deviceIndex < 0)
		return;

	m_deviceListCombo.SetItemDataPtr(deviceIndex, newDevice);

	if (m_deviceListCombo.GetCount() == 1)
	{
		// We have added our first item, refresh and enable UI
		m_deviceListCombo.SetCurSel(0);
		OnNewDeviceSelected();

		//m_startStopButton.EnableWindow(TRUE);
		EnableInterface(true);

		m_CaptureCardEnable = 1;
		m_cLb_Camera.put_BackColor(0x0000FFFF);
		//m_cLb_Camera.put_Caption("CONNECT");
	}

	//newDevice->Release();
}

void CAcqVoltageSamples_IntClkDlg::RemoveDevice(IDeckLink* deckLink)
{
	int deviceIndex = -1;
	DeckLinkDevice* deviceToRemove  = NULL;

	// Find the combo box entry to remove (there may be multiple entries with the same name, but each
	// will have a different data pointer).
	for (deviceIndex = 0; deviceIndex < m_deviceListCombo.GetCount(); ++deviceIndex)
	{
		deviceToRemove = (DeckLinkDevice*)m_deviceListCombo.GetItemDataPtr(deviceIndex);
		if (deviceToRemove->DeckLinkInstance() == deckLink)
			break;
	}

	if (deviceToRemove == NULL)
		return;

	// Stop capturing before removal
	if (deviceToRemove->IsCapturing())
		deviceToRemove->StopCapture();

	// Remove device from list
	m_deviceListCombo.DeleteString(deviceIndex);

	// Refresh UI
	//m_startStopButton.SetWindowText(_T("Start capture"));

	// Check how many devices are left
	if (m_deviceListCombo.GetCount() == 0)
	{
		// We have removed the last device, disable the interface.
		//m_startStopButton.EnableWindow(FALSE);
		EnableInterface(false);
		m_selectedDevice = NULL;
	}
	else if (m_selectedDevice == deviceToRemove)
	{
		// The device that was removed was the one selected in the UI.
		// Select the first available device in the list and reset the UI.
		m_deviceListCombo.SetCurSel(0);
		OnNewDeviceSelected();

		//m_startStopButton.EnableWindow(TRUE);
	//	m_invalidInputLabel.ShowWindow(SW_HIDE);
	}

	// Release DeckLinkDevice instance
	deviceToRemove->Release();
}

void CAcqVoltageSamples_IntClkDlg::EnableInterface(bool enabled)
{
	m_deviceListCombo.EnableWindow((enabled) ? TRUE : FALSE);
	m_modeListCombo.EnableWindow((enabled) ? TRUE : FALSE);

	if (enabled)
	{
		if (m_selectedDevice && m_selectedDevice->SupportsFormatDetection())
		{
			;//m_applyDetectedInputModeCheckbox.EnableWindow(TRUE);
		}
		else
		{
			;//m_applyDetectedInputModeCheckbox.EnableWindow(FALSE);
			;//m_applyDetectedInputModeCheckbox.SetCheck(BST_UNCHECKED);
		}
	}
	else
		;//m_applyDetectedInputModeCheckbox.EnableWindow(FALSE);
}

LRESULT	CAcqVoltageSamples_IntClkDlg::OnErrorRestartingCapture(WPARAM wParam, LPARAM lParam)
{
	// A change in the input video mode was detected, but the capture could not be restarted.
	StopCapture();
	ShowErrorMessage(_T("This application was unable to apply the detected input video mode."), _T("Error restarting the capture."));
	return 0;
}

LRESULT CAcqVoltageSamples_IntClkDlg::OnSelectVideoMode(WPARAM wParam, LPARAM lParam)
{
	// A new video mode was selected by the user
	m_modeListCombo.SetCurSel((unsigned int) wParam);
	return 0;
}


LRESULT CAcqVoltageSamples_IntClkDlg::OnAddDevice(WPARAM wParam, LPARAM lParam)
{
	// A new device has been connected
	AddDevice((IDeckLink*)wParam);

	StartCapture();

	return 0;
}

LRESULT	CAcqVoltageSamples_IntClkDlg::OnRemoveDevice(WPARAM wParam, LPARAM lParam)
{
	// An existing device has been disconnected
	RemoveDevice((IDeckLink*)wParam);
	return 0;
}


LRESULT  CAcqVoltageSamples_IntClkDlg::OnRefreshInputStreamData(WPARAM wParam, LPARAM lParam)
{

	#ifndef NO_CAPTURE_MODE__
	CString StrTmp;
	// Update the UI under protection of critsec object
	m_critSec.Lock();

	//m_vitcTcF1.SetWindowText(m_ancillaryData.vitcF1Timecode);
	//m_vitcUbF1.SetWindowText(m_ancillaryData.vitcF1UserBits);
	//m_vitcTcF2.SetWindowText(m_ancillaryData.vitcF2Timecode);
	//m_vitcUbF2.SetWindowText(m_ancillaryData.vitcF2UserBits);

	//m_rp188Vitc1Tc.SetWindowText(m_ancillaryData.rp188vitc1Timecode);
	//m_rp188Vitc1Ub.SetWindowText(m_ancillaryData.rp188vitc1UserBits);
	//m_rp188Vitc2Tc.SetWindowText(m_ancillaryData.rp188vitc2Timecode);
	//m_rp188Vitc2Ub.SetWindowText(m_ancillaryData.rp188vitc2UserBits);
	//m_rp188LtcTc.SetWindowText(m_ancillaryData.rp188ltcTimecode);
	//m_rp188LtcUb.SetWindowText(m_ancillaryData.rp188ltcUserBits);
	StrTmp = m_ancillaryData.vitcF1Timecode;
	m_critSec.Unlock();
	if(wParam)
	{
		StrTmp += "1";

		m_VideoSignalAlive = 0;

	}
	else
	{
		StrTmp += "0";
		m_VideoSignalAlive = 1;
	}
	SetDlgItemText(IDC_STOP_CAPTURE_BUTTON, StrTmp);
//	m_invalidInputLabel.ShowWindow((wParam) ? SW_SHOW : SW_HIDE);
#endif
	return 0;
}

void CAcqVoltageSamples_IntClkDlg::OnNewDeviceSelected()
{
	int		selectedDeviceIndex;

	selectedDeviceIndex = m_deviceListCombo.GetCurSel();
	if (selectedDeviceIndex < 0)
		return;

	m_selectedDevice = (DeckLinkDevice*) m_deviceListCombo.GetItemDataPtr(selectedDeviceIndex);

	// Update the video mode popup menu
	RefreshVideoModeList();

	// Enable the interface
	EnableInterface(true);

	if (m_selectedDevice->SupportsFormatDetection())
		;//m_applyDetectedInputModeCheckbox.SetCheck(BST_CHECKED);
}


void CAcqVoltageSamples_IntClkDlg::SaveAsImage()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
		
	CString InitNewName = _T("HDMI.bmp");

	//CString lCurrentFileName = _T("");
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Data\\");

	CString lCurrentFileName =  lstrPath;
	lCurrentFileName += "current.bmp";	

	ScreenCapture( lCurrentFileName, _T(" "), 1);
	
	CFileDialog FileDlg(FALSE, _T("bmp"), InitNewName, OFN_OVERWRITEPROMPT, _T("BMP FILE(*.bmp)|*.bmp||")); 
	FileDlg.m_ofn.lpstrInitialDir = CurrentSet->sRefFolder;
	if (FileDlg.DoModal() == IDOK) {   
		// 파일경로 가져오기    
		CString Filename = FileDlg.GetPathName();
		//CFile lCurrentFile("current.bmp");//::Duplicate("current.bmp", )
		CopyFile(lCurrentFileName,  Filename, 0);
		CFileControl lFileCtrl;
		lFileCtrl.SaveImageRangeData(Filename,m_Rect_Image);

	}
}



void CAcqVoltageSamples_IntClkDlg::ClickLabelImageSet()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_Image_SaveMode == 1)
	{
		m_Image_SaveMode = 0;
		m_cLB_ImageSet.put_ForeColor(0x808080);
	}
	else
	{
		m_Image_SaveMode = 1;
		m_cLB_ImageSet.put_ForeColor(0x00FF00);
	}
}


void CAcqVoltageSamples_IntClkDlg::ClickLabelImageSaveAs()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect lRect;
	m_previewWindow->SetRange(0,lRect);
	m_previewWindow->m_DisplayOK = 1;
	Sleep(100);
	ScreenCapture();
	SaveAsImage();
}

void CAcqVoltageSamples_IntClkDlg ::SetInputVideo( int DisplayNo)
{
	BYTE lbuf[128]; 
	if(	DisplayNo == 2)
	{
		sprintf((char *)&lbuf, "@C1V_SEL_8_01$");
		SendData(lbuf, 14);
	}
	else if(DisplayNo == 3)
	{
		sprintf((char *)&lbuf, "@C1V_SEL_8_02$");
		SendData(lbuf, 14);
	}
	else
	{
		sprintf((char *)&lbuf, "@C1V_SEL_8_00$");//sprintf((char *)&lbuf, "@C%dV_SEL_8_00$", g_DisplayVideoPortNo);
		SendData(lbuf, 14);
	}
	
	//m_MainPAGE_COM_PROCESS = COM_MODE_SET_WAIT_ACK;
	//
	//if((SelPortNo < 8)&&(SelPortNo >= 0))
	//	m_CurrentComport =	SelPortNo;
	//else
	//	m_CurrentComport = 0;//lSelPortNo
	//	
	//m_ComSetAck[m_CurrentComport] = COM_ACK_WAIT;
	
}


void CAcqVoltageSamples_IntClkDlg ::RefreshHDMI( void)
{

	BYTE lbuf[128]; 
	int lcnt;
	CString str;
	//UINT m_EditFreq1;
//	UpdateData();

//	lbuf[0] = 0x02;
	//@CA_SEL_8_
	//Command : @ + C + HSW_SEL_nn$ , 13Bytes
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	//sprintf((char *)&lbuf, "@C0DBUG20RESET_HDMI$");
	//SendData(lbuf, 20);



	
	//m_MainPAGE_COM_PROCESS = COM_MODE_SET_WAIT_ACK;
	//
	//if((SelPortNo < 8)&&(SelPortNo >= 0))
	//	m_CurrentComport =	SelPortNo;
	//else
	//	m_CurrentComport = 0;//lSelPortNo
	//	
	//m_ComSetAck[m_CurrentComport] = COM_ACK_WAIT;
	
}

void CAcqVoltageSamples_IntClkDlg::SetRange( int lDisplayFlag,int lDisplayOK , CRect rect)
{	
	m_previewWindow->SetRange(1, rect );
	m_previewWindow->m_DisplayOK = 1;// lDisplayOK;		
}


void CAcqVoltageSamples_IntClkDlg::ClearRange()
{
	CRect rect;
	m_previewWindow->SetRange(0, rect );
	//m_previewWindow->m_DisplayOK = lDisplayOK;	
}


void CAcqVoltageSamples_IntClkDlg::SetRangeColor( int lDisplayOK)
{	
	m_previewWindow->m_DisplayOK = 1;;// lDisplayOK;		
}


int CAcqVoltageSamples_IntClkDlg::CompareImage( CString lrefFilename ,CRect rect)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Data\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) == 0)
	{
		rect = lReadrect;
	}


	CString lsavPathName = lstrPath;
	
	lsavPathName += "current.bmp";	
	

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	int llNG = CompareImage(lsavPathName, lRefPathName,  rect  );
	if(llNG)
		SetRange(  1, 0,  rect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  rect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;
}


int CAcqVoltageSamples_IntClkDlg::CompareImage(CString lcheckFilename, CString lrefFilename, CRect rect  )
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	int llNG = 0;
	//CString lstrPath = PATH_BASE_DIR;
	//lstrPath += _T("\\Image\\");

	//CString lRefPathName = lstrPath;
	//lRefPathName += lrefFilename;
	//lRefPathName += ".bmp";

	//CString lCheckPathName = lstrPath;
	//lRefPathName += lcheckFile;
	//lRefPathName += ".bmp";

	//CString lsavPathName = lstrPath;
	//lsavPathName += "current.bmp";	

	ATL::CImage capImage;
	HRESULT lResult = capImage.Load(lcheckFilename);
	if(lResult != S_OK)
	{
		return 1;
	}	

	ATL::CImage RefImage;
	 lResult = RefImage.Load(lrefFilename);
	if(lResult != S_OK)
	{
		return 1;
	}


	//capImage.GetBits();
	COLORREF lColorRef ;//= capImage.GetPixel(0,0);
	COLORREF lColor ;//= capImage.GetPixel(0,0);

	CFileControl lfCtrl;
	RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int ErrorCnt = 0;
	int TotalCnt = 0;
	int nX_RefWidth = RefImage.GetWidth();
	int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width >= nX_RefWidth ? nX_RefWidth:nX_Width;
	int leny = nY_Height >= nY_RefHeight ? nY_RefHeight:nY_Height;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		return 1;
	}
	if((rect.bottom < leny)&&(rect.right < lenX))	
	{
			
	}
	else
	{
		return 1;
	}

	rect.left += 1;
	rect.right -= 1; 
	rect.top  += 1;
	rect.bottom  -= 1;

	int CheckWidthX = rect.right - rect.left;
	int	CheckWidthY = rect.bottom - rect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = rect.left; x < rect.right; x++)
	{
		for(int y = rect.top; y < rect.bottom; y++)
		{
				lBmpColorRef = lfCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
				lBmpColor = lfCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
				if((abs(lBmpColorRef.b-lBmpColor.b)*100./255. > 10)  ||(abs(lBmpColorRef.g-lBmpColor.g)*100./255. > 10)||(abs(lBmpColorRef.r-lBmpColor.r)*100./255. > 10))
				{
					ErrorCnt++;
				}

			//lColorRef
		}
	}

		

	if((100.* ErrorCnt  / TotalCnt) > 10)
	{
		llNG = ErrorCnt;
	}
	
	
	return llNG;
}

int CAcqVoltageSamples_IntClkDlg::ScreenCheck( )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int l_NG = 0;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;

	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect);
	

	this->GetWindowRect(&rectMain);
	int width = rect.right-rect.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect.bottom-rect.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect.left, rect.top, SRCCOPY);
	/*{
		capImage.Save(lSaveFileName, Gdiplus::ImageFormatBMP);
	}*/


	//Black Image Check
	//capImage.
	CFileControl lfCtrl;
		
	int ColourCnt = 0;
	int ErrorCnt = 0;
	int TotalCnt = 0;
	for(int i = 0; i < capImage.GetWidth();i++)
	{
		COLORREF lColorRef = capImage.GetPixel(i, 100);
		RgbColor lBmpColor = lfCtrl.COLORREF_to_BMP3Byte(capImage.GetPixel(i, 100));
		if((lBmpColor.r < 10)&&(lBmpColor.g < 10)&&(lBmpColor.b < 10))
		{
			ErrorCnt++;
		}
		else
		{
			ColourCnt++;
		}
		TotalCnt++;
	}

	

	capImage.ReleaseDC();

	CString str;
	str.Format(_T("CNT : %d/%d/%03d"), ColourCnt,sErrcnt,sCheckcnt);
	SetDlgItemText(IDC_STATIC_CNT, str);
	sCheckcnt++;
	if(sCheckcnt > 999)
		sCheckcnt = 0;

	if(ColourCnt < 50)
	{
		//if(sErrcnt == 0)
		//{
		//	SetTimeCheck(TIME_CHECK_NOSIGNAL_TIME);
		//}
		//else
		//{
		//	if(GetTimeCheck(TIME_CHECK_NOSIGNAL_TIME) > 6000)			
		//	{
		//		sErrcnt = 0;

				return 0;
		/*	}
		}
		sErrcnt++;*/
	}
	else
	{
		sErrcnt = 0;
	}
	return 1;
}


int CAcqVoltageSamples_IntClkDlg::ScreenMovingPicCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	CString lrefFilename;
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int lOk = 0;
	CString str;

	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;

	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Data\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	
	lRefPathName = g_GrabImage.m_szFilePath;
	CRect lReadrect;
	CFileControl lFileCtrl;

	//if (lFileCtrl.ReadImageRangeData(lRefRangePathName, &lReadrect) != 0)
	//{
	//	str = "Image Rect File Not Found:";
	//	str += lRefPathName;
	//	MessageDisplay(1, str);
	//	return 1;
	//}


	if (!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);


	this->GetWindowRect(&rectMain);
	int width = rect1.right - rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom - rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);

	lReadrect = rect1;
	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if (!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc, 0, 0, width, height, DeskTopDC.m_hDC, rect1.left, rect1.top, SRCCOPY);
	/*{
		capImage.Save(lSaveFileName, Gdiplus::ImageFormatBMP);
	}*/

	ATL::CImage RefImage;
	HRESULT lResult = RefImage.Load(lRefPathName);
	if (lResult != S_OK)
	{
		CString str;

		//MessageBox(lRefPathName, "Image File Not Found");
		capImage.ReleaseDC();

		str = "Image Rect File Not Found:";
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	//capImage.GetBits();
	COLORREF lColorRef;//= capImage.GetPixel(0,0);
	COLORREF lColor;//= capImage.GetPixel(0,0);

	CFileControl lfCtrl;
	RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int ErrorCnt = 0;
	int TotalCnt = 0;
	int nX_RefWidth = RefImage.GetWidth();
	int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width >= nX_RefWidth ? nX_RefWidth : nX_Width;
	int leny = nY_Height >= nY_RefHeight ? nY_RefHeight : nY_Height;


	if ((lenX > 0) && (leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		return 0;
	}
	//if ((lReadrect.bottom < leny) && (lReadrect.right < lenX))
	//{

	//}
	//else
	//{
	//	return 1;
	//}

	lReadrect.left += 1;
	lReadrect.right -= 1;
	lReadrect.top += 1;
	lReadrect.bottom -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = nX_Width * nY_Height;// CheckWidthX * CheckWidthY;
	for (int x = 0; x < nX_Width; x++)
	{
		for (int y = 0; y < nY_Height; y++)
		{
			lBmpColorRef = lfCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x, y));
			lBmpColor = lfCtrl.COLORREF_to_BMP3Byte(capImage.GetPixel(x, y));

			if ((abs(lBmpColorRef.b - lBmpColor.b)*100. / 255. > 5) || (abs(lBmpColorRef.g - lBmpColor.g)*100. / 255. > 5) || (abs(lBmpColorRef.r - lBmpColor.r)*100. / 255. > 5))
			{
				ErrorCnt++;
			}
		}
	}
	capImage.Save(g_GrabImage.m_szFilePath, Gdiplus::ImageFormatBMP);
	capImage.ReleaseDC();
	//RefImage.ReleaseDC();	

	if ((100.* ErrorCnt / TotalCnt) > 5)
	{
		lOk = 1;
	}




	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	lReadrect.left = 10;
	lReadrect.right = nX_Width-20;
	lReadrect.top = 10;
	lReadrect.bottom = nY_Height-20;
	if (lOk)
	{
		SetRange(1, 1, lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
		Moving_Pic_Count++;	
		if (Moving_Pic_Count > NO_GRAB_FOR_MOVING_PIC_TEST)
		{

			return TEST_PASS;
		}
	}
	else
	{
		lOk = 0;
		SetRange(1, 0, lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	}

	return TEST_WAIT;




}


int CAcqVoltageSamples_IntClkDlg::ScreenCheck(CString lrefFilename  )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Image\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) != 0)
	{
		str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);
	

	this->GetWindowRect(&rectMain);
	int width = rect1.right-rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom-rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect1.left, rect1.top, SRCCOPY);
	/*{
		capImage.Save(lSaveFileName, Gdiplus::ImageFormatBMP);
	}*/

	ATL::CImage RefImage;
	HRESULT lResult = RefImage.Load(lRefPathName);
	if(lResult != S_OK)
	{
		CString str;
		
		//MessageBox(lRefPathName, "Image File Not Found");
		capImage.ReleaseDC();
		
		str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	//capImage.GetBits();
	COLORREF lColorRef ;//= capImage.GetPixel(0,0);
	COLORREF lColor ;//= capImage.GetPixel(0,0);

	CFileControl lfCtrl;
	RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int ErrorCnt = 0;
	int TotalCnt = 0;
	int nX_RefWidth = RefImage.GetWidth();
	int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width >= nX_RefWidth ? nX_RefWidth:nX_Width;
	int leny = nY_Height >= nY_RefHeight ? nY_RefHeight:nY_Height;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		return 1;
	}
	if((lReadrect.bottom < leny)&&(lReadrect.right < lenX))	
	{
			
	}
	else
	{
		return 1;
	}

	lReadrect.left += 1;
	lReadrect.right -= 1; 
	lReadrect.top  += 1;
	lReadrect.bottom  -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = lReadrect.left; x < lReadrect.right; x++)
	{
		for(int y = lReadrect.top; y < lReadrect.bottom; y++)
		{
			lBmpColorRef = lfCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lfCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
			if((abs(lBmpColorRef.b-lBmpColor.b)*100./255. > 5)  ||(abs(lBmpColorRef.g-lBmpColor.g)*100./255. > 5)||(abs(lBmpColorRef.r-lBmpColor.r)*100./255. > 5))
			{
				ErrorCnt++;
			}			
		}
	}

	capImage.ReleaseDC();	
	//RefImage.ReleaseDC();	

	if((100.* ErrorCnt  / TotalCnt) > 3)
	{
		llNG = ErrorCnt;
	}
	
	


	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	
	if(llNG)
		SetRange(  1, 0,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;





}


int CAcqVoltageSamples_IntClkDlg::ScreenColorCheck(CString lrefFilename  ,RgbColor lBmpColorRef  )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Image\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	//CRect rect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) != 0)
	{
		//MessageBox(lRefRangePathName, "ColorCheck Image Rect File Not Found");
				str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);
	

	this->GetWindowRect(&rectMain);
	int width = rect1.right-rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom-rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect1.left, rect1.top, SRCCOPY);
	/*{
		capImage.Save(lSaveFileName, Gdiplus::ImageFormatBMP);
	}*/

	//ATL::CImage RefImage;
	//HRESULT lResult = RefImage.Load(lrefFilename);
	//if(lResult != S_OK)
	//{
	//	return 1;
	//}


	//capImage.GetBits();
	//= capImage.GetPixel(0,0);
	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//CFileControl lfCtrl;
	//RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int OKCnt = 0;
	int TotalCnt = 0;
	//int nX_RefWidth = RefImage.GetWidth();
	//int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width ;
	int leny = nY_Height ;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}
	if((lReadrect.bottom < leny)&&(lReadrect.right < lenX))	
	{
			
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}

	lReadrect.left += 1;
	lReadrect.right -= 1; 
	lReadrect.top  += 1;
	lReadrect.bottom  -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = lReadrect.left; x < lReadrect.right; x++)
	{
		for(int y = lReadrect.top; y < lReadrect.bottom; y++)
		{
		//	lBmpColorRef = lFileCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lFileCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
			if(
				(
					(
						(lBmpColorRef.b < lBmpColor.b)
						&&(100 > lBmpColor.g)
						&&(100 > lBmpColor.r)
					)
					||
					(
						(100 > lBmpColor.b)
						&&(lBmpColorRef.g < lBmpColor.g)
						&&(100 > lBmpColor.r)
					)
					||
					(
						(100 > lBmpColor.b)
						&&(100 > lBmpColor.g)
						&&(lBmpColorRef.r < lBmpColor.r)
					)
					||
					(
						(
							(abs(lBmpColor.g - lBmpColor.b) > 100 )
							||(abs(lBmpColor.g - lBmpColor.r) > 100 )
							||(abs(lBmpColor.b - lBmpColor.r) > 100 )
						)
					
					)				
				)
				&&(lBmpColor.b < 200)
			)
			{
				OKCnt++;
			}			
		}
	}
			

	if((100.* OKCnt  / TotalCnt) > 20)
	{
		llNG = 0;
	}
	else
	{
		llNG = 1;
	}
	
	
	capImage.ReleaseDC();	

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	
	if(llNG)
		SetRange(  1, 0,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;


	////capImage.
	//CFileControl lfCtrl;
	//	
	//int ColourCnt = 0;
	//int ErrorCnt = 0;
	//int TotalCnt = 0;
	//for(int i = 0; i < capImage.GetWidth();i++)
	//{
	//	COLORREF lColorRef = capImage.GetPixel(i, 100);
	//	RgbColor lBmpColor = lfCtrl.COLORREF_to_BMP3Byte(capImage.GetPixel(i, 100));
	//	if((lBmpColor.r < 10)&&(lBmpColor.g < 10)&&(lBmpColor.b < 10))
	//	{
	//		ErrorCnt++;
	//	}
	//	else
	//	{
	//		ColourCnt++;
	//	}
	//	TotalCnt++;
	//}

	//

	//capImage.ReleaseDC();

	//CString str;
	//str.Format(_T("CNT : %d/%d/%03d"), ColourCnt,sErrcnt,sCheckcnt);
	//SetDlgItemText(IDC_STATIC_CNT, str);
	//sCheckcnt++;
	//if(sCheckcnt > 999)
	//	sCheckcnt = 0;

	//if(ColourCnt < 50)
	//{
	//	if(sErrcnt == 0)
	//	{
	//		SetTimeCheck(TIME_CHECK_NOSIGNAL_TIME);
	//	}
	//	else
	//	{
	//		if(GetTimeCheck(TIME_CHECK_NOSIGNAL_TIME) > 6000)			
	//		{
	//			sErrcnt = 0;

	//			return 0;
	//		}
	//	}
	//	sErrcnt++;
	//}
	//else
	//{
	//	sErrcnt = 0;
	//}
	//return 1;

	//if(lSave == 0)
	//{

	//	ATL::CImage RefImage;
	//	HRESULT lResult = RefImage.Load(lRefFileName);
	//	if(lResult != S_OK)
	//	{
	//		return 1;
	//	}
	//	//capImage.GetBits();
	//	COLORREF lColorRef ;//= capImage.GetPixel(0,0);
	//	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//	CFileControl lfCtrl;
	//	RgbColor lBmpColorRef;
	//	RgbColor lBmpColor;
	//	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	//	int ErrorCnt = 0;
	//	int TotalCnt = 0;
	//	int nX_RefWidth = RefImage.GetHeight();
	//	int nY_RefHeight = RefImage.GetHeight();

	//	int nX_Width = capImage.GetHeight();
	//	int nY_Height = capImage.GetHeight();


	//	int lenX = nX_Width >= nX_RefWidth ? nX_RefWidth:nX_Width;
	//	int leny = nY_Height >= nY_RefHeight ? nY_RefHeight:nY_Height;

	//	
	//	if((lenX > 0)&&(leny > 0))
	//	{
	//		TotalCnt = lenX * leny;
	//	}
	//	else
	//	{
	//		return 1;
	//	}

	//	for(int x = 0; x < lenX; x++)
	//	{
	//		for(int y = 0; y < leny; y++)
	//		{
	//			 lBmpColorRef = lfCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
	//			 lBmpColor = lfCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
	//		
	//			 if(((lBmpColorRef.b-lBmpColor.b)*100./255. > 10)  ||((lBmpColorRef.b-lBmpColor.b)*100./255. > 10)||((lBmpColorRef.b-lBmpColor.b)*100./255. > 10))
	//			 {
	//				 ErrorCnt++;
	//			 }

	//			//lColorRef
	//		}
	//	}

	//	

	//	if((100.* ErrorCnt  / TotalCnt) > 10)
	//	{
	//		l_NG = 1;
	//	}
	//}
//	return l_NG;


}


int CAcqVoltageSamples_IntClkDlg::ScreenRGBTest(CString lCheckFilename, CString lrefFilename, CString lMaskFilename,float &MaxDiffernece, BOOL bUseMaskImage)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	int lTestResult = TEST_PASS;
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;

	ATL::CImage capImage;
	ATL::CImage RefImage;
	ATL::CImage MaskImage;
	ScreenCapture(pCurStep->m_strGrabPath, "");

	HRESULT lResult = capImage.Load(lCheckFilename);
	if (lResult != S_OK)
	{
		return 0;
	}

	lResult = RefImage.Load(lrefFilename);
	if(lResult != S_OK)
	{
		return 0;
	}

	//if (bUseMaskImage == 1)
	//{
	//	lResult = MaskImage.Load(lMaskFilename);
	//	if (lResult != S_OK)
	//	{
	//		return 0;
	//	}
	//}
	CFileControl lFile;
	CRect rect;
	lFile.ReadImageRangeData(lrefFilename,&rect);



	COLORREF lColor;

	RgbColor lBmpColorRef;
	RgbColor lBmpColor;	

	int OKCnt = 0;
	int NGCnt = 0;
	int TotalCnt = 0;
	
	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();

	int lenX = nX_Width;
	int leny = nY_Height;

	if ((lenX > 0) && (leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
	//	capImage.ReleaseDC();
		return 1;
	}
	
	CFileControl lFileCtrl;
	int nStartXposition, nEndXposition, nStartYposition, nEndYposition;

	nStartXposition = rect.left;
	nEndXposition = rect.right;
	nStartYposition = rect.top;
	nEndYposition = rect.bottom;

	//g_ImageProc.CalcTestRange(g_GrabImage, nStartXposition, nEndXposition, nStartYposition, nEndYposition);
	int n_LowerLimit = g_ImageProc.Percentage2Level((float)pCurStep->m_fLowLimit, 256);
	int n_UpperLimit = g_ImageProc.Percentage2Level( (float)pCurStep->m_fHighLimit,256);
	//g_ImageProc.SetColorMargin
	
	nStartXposition = nStartXposition < 0  ? 0 : nStartXposition;
	nEndXposition = nEndXposition > nX_Width ? nX_Width : nEndXposition;

	nStartYposition = nStartYposition < 0 ? 0 : nStartYposition;
	nEndYposition = nEndYposition > nY_Height ? nY_Height : nEndYposition;



	int CheckWidthX = nEndXposition - nStartXposition;
	int	CheckWidthY = nEndYposition - nStartYposition;

	TotalCnt = CheckWidthX * CheckWidthY;
	for (int x = nStartXposition; x < nEndXposition; x++)
	{
		for (int y = nStartYposition; y < nEndYposition; y++)
		{
			lBmpColorRef = lFileCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lFileCtrl.COLORREF_to_BMP3Byte(capImage.GetPixel(x, y));

			
			//if (abs((lBmpColorRef.b - lBmpColor.b)*100./256)  < 5
			//	&& abs((lBmpColorRef.g - lBmpColor.g)*100. / 256) < 5
			//	&& abs((lBmpColorRef.r - lBmpColor.r)*100. / 256) < 5)
			if ((((lBmpColorRef.b - lBmpColor.b) > n_LowerLimit)&&((lBmpColorRef.b - lBmpColor.b) < n_UpperLimit))
				&&(((lBmpColorRef.g - lBmpColor.g) > n_LowerLimit) && ((lBmpColorRef.g - lBmpColor.g) < n_UpperLimit))
				&&(((lBmpColorRef.r - lBmpColor.r) > n_LowerLimit) && ((lBmpColorRef.r - lBmpColor.r) < n_UpperLimit)))
				
			{
				OKCnt++;
			}
			else
			{
				NGCnt++;
			}
		}
	}


	if (OKCnt == TotalCnt)//((100.* OKCnt / TotalCnt) > 99)
	{
		llNG = 0;
		lTestResult = TEST_PASS;
	}
	else
	{
		llNG = 1;
		lTestResult = TEST_FAIL;
	}


//	capImage.ReleaseDC();

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	CRect lReadrect;
	lReadrect.left = nStartXposition;
	lReadrect.right = nEndXposition;
	lReadrect.top = nStartYposition;
	lReadrect.bottom = nEndYposition;

	if (llNG)
		SetRange(1, 0, lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(1, 1, lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return lTestResult;




}

int CAcqVoltageSamples_IntClkDlg::ScreenColorRedCheck(CString lrefFilename  ,RgbColor lBmpColorRef , float lOK_Percent )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Image\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	//CRect rect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) != 0)
	{
		//MessageBox(lRefRangePathName, "Image Rect File Not Found");
		str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);
	

	this->GetWindowRect(&rectMain);
	int width = rect1.right-rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom-rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect1.left, rect1.top, SRCCOPY);

	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//CFileControl lfCtrl;
	//RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int OKCnt = 0;
	int TotalCnt = 0;
	//int nX_RefWidth = RefImage.GetWidth();
	//int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width ;
	int leny = nY_Height ;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}
	if((lReadrect.bottom < leny)&&(lReadrect.right < lenX))	
	{
			
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}

	lReadrect.left += 1;
	lReadrect.right -= 1; 
	lReadrect.top  += 1;
	lReadrect.bottom  -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = lReadrect.left; x < lReadrect.right; x++)
	{
		for(int y = lReadrect.top; y < lReadrect.bottom; y++)
		{
		//	lBmpColorRef = lFileCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lFileCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
			if((lBmpColorRef.b > lBmpColor.b)
				&&(lBmpColorRef.g > lBmpColor.g)
				&&(lBmpColorRef.r < lBmpColor.r))
			{
				OKCnt++;
			}			
		}
	}
			

	if((100.* OKCnt  / TotalCnt) > lOK_Percent)
	{
		llNG = 0;
	}
	else
	{
		llNG = 1;
	}
	
	
	capImage.ReleaseDC();	

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	
	if(llNG)
		SetRange(  1, 0,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;




}


int CAcqVoltageSamples_IntClkDlg::ScreenColorBlueCheck(CString lrefFilename  ,RgbColor lBmpColorRef , float lOK_Percent  )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Image\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	//CRect rect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) != 0)
	{
		//MessageBox(lRefRangePathName, "Image Rect File Not Found");
		str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);
	

	this->GetWindowRect(&rectMain);
	int width = rect1.right-rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom-rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect1.left, rect1.top, SRCCOPY);

	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//CFileControl lfCtrl;
	//RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int OKCnt = 0;
	int TotalCnt = 0;
	//int nX_RefWidth = RefImage.GetWidth();
	//int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width ;
	int leny = nY_Height ;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}
	if((lReadrect.bottom < leny)&&(lReadrect.right < lenX))	
	{
			
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}

	lReadrect.left += 1;
	lReadrect.right -= 1; 
	lReadrect.top  += 1;
	lReadrect.bottom  -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = lReadrect.left; x < lReadrect.right; x++)
	{
		for(int y = lReadrect.top; y < lReadrect.bottom; y++)
		{
		//	lBmpColorRef = lFileCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lFileCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
			if((lBmpColorRef.b < lBmpColor.b)
				&&(lBmpColorRef.g > lBmpColor.g)
				&&(lBmpColorRef.r > lBmpColor.r))
			{
				OKCnt++;
			}			
		}
	}
			

	if((100.* OKCnt  / TotalCnt) > lOK_Percent)
	{
		llNG = 0;
	}
	else
	{
		llNG = 1;
	}
	
	
	capImage.ReleaseDC();	

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	
	if(llNG)
		SetRange(  1, 0,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;




}


int CAcqVoltageSamples_IntClkDlg::ScreenColorGreenCheck(CString lrefFilename  ,RgbColor lBmpColorRef , float lOK_Percent  )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	static int sErrcnt = 0;
	static int sCheckcnt = 0;
	int llNG = 0;
	CString str;
 
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;


	CString lRefRangePathName;
	
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Image\\");

	CString lRefPathName = lstrPath;
	lRefPathName += lrefFilename;
	lRefRangePathName = lRefPathName;
	lRefPathName += ".bmp";
	//lRefRangePathName += ".txt";

	CRect lReadrect;
	//CRect rect;
	CFileControl lFileCtrl;
	
	if(lFileCtrl.ReadImageRangeData(lRefRangePathName,&lReadrect) != 0)
	{
		//MessageBox(lRefRangePathName, "Image Rect File Not Found");
		str = "Image Rect File Not Found:"; 
		str += lRefPathName;
		MessageDisplay(1, str);
		return 1;
	}


	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect1;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect1);
	

	this->GetWindowRect(&rectMain);
	int width = rect1.right-rect1.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect1.bottom-rect1.top;//::GetDeviceCaps(h_screen_dc, VERTRES);


	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);
	if(!capImage.Create(width, height, 32))
		return 1;
	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect1.left, rect1.top, SRCCOPY);

	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//CFileControl lfCtrl;
	//RgbColor lBmpColorRef;
	RgbColor lBmpColor;
	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	int OKCnt = 0;
	int TotalCnt = 0;
	//int nX_RefWidth = RefImage.GetWidth();
	//int nY_RefHeight = RefImage.GetHeight();

	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();


	int lenX = nX_Width ;
	int leny = nY_Height ;

		
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}
	if((lReadrect.bottom < leny)&&(lReadrect.right < lenX))	
	{
			
	}
	else
	{
		capImage.ReleaseDC();
		return 1;
	}

	lReadrect.left += 1;
	lReadrect.right -= 1; 
	lReadrect.top  += 1;
	lReadrect.bottom  -= 1;

	int CheckWidthX = lReadrect.right - lReadrect.left;
	int	CheckWidthY = lReadrect.bottom - lReadrect.top;

	TotalCnt = CheckWidthX*CheckWidthY;
	for(int x = lReadrect.left; x < lReadrect.right; x++)
	{
		for(int y = lReadrect.top; y < lReadrect.bottom; y++)
		{
		//	lBmpColorRef = lFileCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
			lBmpColor = lFileCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			
			if((lBmpColorRef.b > lBmpColor.b)
				&&(lBmpColorRef.g < lBmpColor.g)
				&&(lBmpColorRef.r > lBmpColor.r))
			{
				OKCnt++;
			}			
		}
	}
			

	if((100.* OKCnt  / TotalCnt) > lOK_Percent)
	{
		llNG = 0;
	}
	else
	{
		llNG = 1;
	}
	
	
	capImage.ReleaseDC();	

	//int llNG = ScreenCapture(lIndex, lsavPathName, lRefPathName,  0);
	
	if(llNG)
		SetRange(  1, 0,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );
	else
		SetRange(  1, 1,  lReadrect);//SetRange(int lIndex, int lDisplayFlag,int lDisplayOK,  rect);///m_previewWindow->SetRange(1, rect );


	return llNG;




}

int  CAcqVoltageSamples_IntClkDlg::ScreenCapture()
{
	CString lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\data\\");

	CString lCapturFileName = lstrPath;
	lCapturFileName += "current";
	lCapturFileName += ".bmp";
	int l_NG = ScreenCapture(  lCapturFileName, " ", 1);
	return l_NG;
}

int CAcqVoltageSamples_IntClkDlg::ScreenCapture( CString lSaveFileName, CString lRefFileName, int lSave)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	ShowWindow(SW_HIDE);
	int l_NG = 0;
	ClearRange();
	ATL::CImage capImage;
	CWnd* pDesktopWnd = GetDesktopWindow();
	HDC h_screen_dc = NULL;

	if(!pDesktopWnd)
		return 1;

	CWindowDC DeskTopDC(pDesktopWnd);

	RECT rect;
	RECT rectMain;
	m_previewBox.GetWindowRect(&rect);	

	this->GetWindowRect(&rectMain);
	int width = rect.right-rect.left;//::GetDeviceCaps(h_screen_dc, HORZRES);
	int height = rect.bottom-rect.top;//::GetDeviceCaps(h_screen_dc, VERTRES);

	int nx = GetSystemMetrics(SM_CXSCREEN);
	int ny = GetSystemMetrics(SM_CYSCREEN);

	if (!capImage.Create(width, height, 24))//if (!capImage.Create(width, height, 32))
		return 1;

	h_screen_dc = capImage.GetDC();

	::BitBlt(h_screen_dc,0,0, width, height, DeskTopDC.m_hDC,rect.left, rect.top, SRCCOPY);
	
	capImage.Save(lSaveFileName, Gdiplus::ImageFormatBMP);
	//	
	int nX_Width = capImage.GetWidth();
	int nY_Height = capImage.GetHeight();

	int lenX = nX_Width;// >= nX_RefWidth ? nX_RefWidth : nX_Width;
	int leny = nY_Height;// >= nY_RefHeight ? nY_RefHeight : nY_Height;
	int TotalCnt;
	if((lenX > 0)&&(leny > 0))
	{
		TotalCnt = lenX * leny;
	}
	else
	{
		return 1;
	}
	
	CFileControl lfCtrl;	
	RgbColor lBmpColor;

	//BYTE*			 m_pImageData;
	m_ImageWidth = lenX;
	m_ImageHeight = leny;
	m_ImageSize = m_ImageWidth *m_ImageHeight*3;

	//if (m_pImageData != NULL) { delete m_pImageData; m_pImageData = NULL; }

	//m_pImageData = new BYTE[m_ImageSize];
	
/*

	for(int y = 0; y < leny; y++)
	{
		for(int x = 0; x < lenX; x++)
		{
			lBmpColor = lfCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
			m_pImageData[(y*lenX + x) * 3] = lBmpColor.r;
			m_pImageData[(y*lenX + x) * 3+1] = lBmpColor.g;
			m_pImageData[(y*lenX + x) * 3+2] = lBmpColor.b;
		}
	}	*/			
	capImage.ReleaseDC();
	//ATL::CImage RefImage;
	//	HRESULT lResult = RefImage.Load(lRefFileName);
	//	if(lResult != S_OK)
	//	{
	//		return 1;
	//	}

	//if(lSave == 0)
	//{

	//	ATL::CImage RefImage;
	//	HRESULT lResult = RefImage.Load(lRefFileName);
	//	if(lResult != S_OK)
	//	{
	//		return 1;
	//	}
	//	//capImage.GetBits();
	//	COLORREF lColorRef ;//= capImage.GetPixel(0,0);
	//	COLORREF lColor ;//= capImage.GetPixel(0,0);

	//	CFileControl lfCtrl;
	//	RgbColor lBmpColorRef;
	//	RgbColor lBmpColor;
	//	//RgbColor  CFileControl::COLORREF_to_BMP3Byte(COLORREF lCoolorRef)//

	//	int ErrorCnt = 0;
	//	int TotalCnt = 0;
	//	int nX_RefWidth = RefImage.GetHeight();
	//	int nY_RefHeight = RefImage.GetHeight();

	//	int nX_Width = capImage.GetHeight();
	//	int nY_Height = capImage.GetHeight();

	//	int lenX = nX_Width >= nX_RefWidth ? nX_RefWidth:nX_Width;
	//	int leny = nY_Height >= nY_RefHeight ? nY_RefHeight:nY_Height;
	//	
	//	if((lenX > 0)&&(leny > 0))
	//	{
	//		TotalCnt = lenX * leny;
	//	}
	//	else
	//	{
	//		return 1;
	//	}

	//	for(int x = 0; x < lenX; x++)
	//	{
	//		for(int y = 0; y < leny; y++)
	//		{
	//			 lBmpColorRef = lfCtrl.COLORREF_to_BMP3Byte(RefImage.GetPixel(x,y));
	//			 lBmpColor = lfCtrl.COLORREF_to_BMP3Byte( capImage.GetPixel(x,y));
	//		
	//			 if(((lBmpColorRef.b-lBmpColor.b)*100./255. > 10)  ||((lBmpColorRef.b-lBmpColor.b)*100./255. > 10)||((lBmpColorRef.b-lBmpColor.b)*100./255. > 10))
	//			 {
	//				 ErrorCnt++;
	//			 }
	//		}
	//	}				

	//	if((100.* ErrorCnt  / TotalCnt) > 10)
	//	{
	//		l_NG = 1;
	//	}
	//}
	//
	
	return l_NG;

}



void CAcqVoltageSamples_IntClkDlg::DblClickLabelBarcodeMark(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
  	if(g_SetComOnlyMode == 1)
	{
		g_SetComOnlyMode = 0;
		m_cLbOkNg.put_Caption(_T("WAIT"));
	}
	else
	{
		g_SetComOnlyMode = 1;
		SetChannelData(0);
		m_cLbOkNg.put_Caption(_T("SET COM MODE"));
	}
}


void CAcqVoltageSamples_IntClkDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int i = 0;
	LoadTestData(gTestSeqData.strSeqFileName);				
	DisplayTestData();

	CDialog::OnLButtonDblClk(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedCheckDisplayContinue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bCheckDisplayContinue = m_cCheckDisplayContinue.GetCheck();
}
void CAcqVoltageSamples_IntClkDlg::InitVersionGrid()
{
	CString sTmp;

	m_CtrlListVersionProcess.DeleteAllItems();

	char *sHeader[] = { "BE Ver.", "FE Ver.", "Micom Ver.", "DSP Ver.", "Sub DSP Ver.", "EQ Ver.", "MEQ Ver.", "Touch Ver.", "Demo Ver.", "DJ Sound Ver.", "WirelessTx Ver.", "WirelessRx Ver.",
		"Woofer Rx Version","Rear Kit Rx Version","Rear SPK L Version","Rear SPK R Version","BT Version", "HDMI Version", "Checksum" };


	// Set Column Alignment & Column Title
	m_CtrlListVersionProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListVersionProcess.InsertColumn(0, _T("No"), LVCFMT_CENTER, 30);
	m_CtrlListVersionProcess.InsertColumn(1, _T("ITEM"), LVCFMT_CENTER, 117);
	m_CtrlListVersionProcess.InsertColumn(2, _T("VERSION"), LVCFMT_CENTER, 110);

	int lCount = 0;
	for (int nRow = 0; nRow < 19; nRow++)
	{
		if (CurrentSet->bVerChecked[nRow] == 1)
		{

			sTmp.Format(_T("%2d"), nRow + 1);
			m_CtrlListVersionProcess.InsertItem(lCount, sTmp);   // 첫째행(0), 첫째열에 삽입	
			m_CtrlListVersionProcess.SetItem(lCount, 1, LVIF_TEXT, sHeader[nRow], NULL, NULL, NULL, NULL);
			lCount++;
		}

	}
	////	m_ctrlVersionGrid.SetFixedAlignment(0,flexAlignRightCenter);
	//	m_ctrlVersionGrid.SetColAlignment(0,flexAlignRightCenter);
	//	m_ctrlVersionGrid.SetColAlignment(1,flexAlignCenterCenter);
	//
	//	m_ctrlVersionGrid.SetCol(-1);
	//	m_ctrlVersionGrid.SetRow(-1);

	//	m_ctrlVersionGrid.SetRedraw(-1);
	//	m_ctrlVersionGrid.Refresh();
}


void CAcqVoltageSamples_IntClkDlg::UpdateVersionInfo()
{
	UpdateData(TRUE);
	InitVersionGrid();
#if 1
	CString saVersion[19];
	saVersion[0] = CurrentSet->sBE_Version;
	saVersion[1] = CurrentSet->sFE_Version;
	saVersion[2] = CurrentSet->sMicom_Version;
	saVersion[3] = CurrentSet->sDSP_Version;
	saVersion[4] = CurrentSet->sSubDSP_Version;
	saVersion[5] = CurrentSet->sEQ_Version;
	saVersion[6] = CurrentSet->sMEQ_Version;
	saVersion[7] = CurrentSet->sTouch_Version;
	saVersion[8] = CurrentSet->sDemo_Version;
	saVersion[9] = CurrentSet->sDJSound_Version;
	saVersion[10] = CurrentSet->sWirelessTx_Version;
	saVersion[11] = CurrentSet->sWirelessRx_Version;
	saVersion[12] = CurrentSet->sWoofer_Rx_Version;
	saVersion[13] = CurrentSet->sRear_Kit_Rx_Version;
	saVersion[14] = CurrentSet->sRear_SPK_L_Version;
	saVersion[15] = CurrentSet->sRear_SPK_R_Version;
	saVersion[16] = CurrentSet->sBT_Version;
	saVersion[17] = CurrentSet->sHDMI_Version;
	saVersion[18] = CurrentSet->sChecksum;
	int lCount = 0;
	for (int nRow = 0; nRow < 19; nRow++)
	{
		if (CurrentSet->bVerChecked[nRow] == 1)
		{
			m_CtrlListVersionProcess.SetItem(lCount, 2, LVIF_TEXT, saVersion[nRow], NULL, NULL, NULL, NULL);
			lCount++;
		}
	}
#else
	//m_CtrlListMainProcess.SetItem(nTmp, 1, LVIF_TEXT, pStep->GetStepName(), NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(0, 2, LVIF_TEXT, CurrentSet->sBE_Version, NULL, NULL, NULL, NULL);  //SetTextMatrix(1, 1, CurrentSet->sBE_Version);
//	m_CtrlListVersionProcess.SetItem(0, 2, LVIF_TEXT, "sBE_Version", NULL, NULL, NULL, NULL);  //SetTextMatrix(1, 1, CurrentSet->sBE_Version);
	m_CtrlListVersionProcess.SetItem(1, 2, LVIF_TEXT, CurrentSet->sFE_Version, NULL, NULL, NULL, NULL);
	//	m_CtrlListVersionProcess.SetItem(1, 2, LVIF_TEXT, "sFE_Version", NULL, NULL, NULL, NULL);


	m_CtrlListVersionProcess.SetItem(2, 2, LVIF_TEXT, CurrentSet->sMicom_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(3, 2, LVIF_TEXT, CurrentSet->sDSP_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(4, 2, LVIF_TEXT, CurrentSet->sSubDSP_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(5, 2, LVIF_TEXT, CurrentSet->sEQ_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(6, 2, LVIF_TEXT, CurrentSet->sMEQ_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(7, 2, LVIF_TEXT, CurrentSet->sTouch_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(8, 2, LVIF_TEXT, CurrentSet->sDemo_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(9, 2, LVIF_TEXT, CurrentSet->sDJSound_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(10, 2, LVIF_TEXT, CurrentSet->sWirelessTx_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(11, 2, LVIF_TEXT, CurrentSet->sWirelessRx_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(12, 2, LVIF_TEXT, CurrentSet->sBT_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(13, 2, LVIF_TEXT, CurrentSet->sHDMI_Version, NULL, NULL, NULL, NULL);
	m_CtrlListVersionProcess.SetItem(14, 2, LVIF_TEXT, CurrentSet->sChecksum, NULL, NULL, NULL, NULL);
#endif

}

void CAcqVoltageSamples_IntClkDlg::OnNMCustomdrawListVersionProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;


	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	CString strCol = _T("");



	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}
	case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
	{
		COLORREF crText, crBkgnd;

		//	nCol= m_CtrlListMainProcess.getse.GetSelectedColumn();
		//	nRow= m_CtrlListMainProcess.GetItemCount();

		int l_nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //row
		int l_nSubItem = (int)(pLVCD->iSubItem);

		//if ((m_CurrentStep > 0) && (m_CurrentStep < 200)&&(l_nItem == m_CurrentStep-1)&&(l_nSubItem < 2))
		//{
		//	crText = RGB(0, 0, 0);		//글자색
		//	crBkgnd = RGB(128, 128, 255);	//배경색으로 한다   
		//}
		//else if ((l_nItem >= 0) && (l_nItem < 200) && (l_nSubItem >= 0) && (l_nSubItem < 20))
		//{
		//	crText = m_CtrlListMainProcessEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
		//	crBkgnd = m_CtrlListMainProcessEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		//}

		//if (l_nSubItem == 2)
		//{
		//	strCol = m_CtrlListMainProcess.GetItemText(l_nItem, l_nSubItem);
		//	if (strCol.Find("OK") >= 0)
		//	{
		//		crText = RGB(255, 255, 255); //글자색
		//		crBkgnd = RGB(0, 0, 255); //배경색으로 한다   
		//	}
		//	else if (strCol.Find("NG") >= 0)
		//	{
		//		crText = RGB(255, 255, 255); //글자색
		//		crBkgnd = RGB(255, 0, 0); //배경색으로 한다 
		//	}
		//	else if (l_nItem == m_CurrentStep - 1)
		//	{
		//		crText = RGB(0, 0, 0); //글자색
		//		crBkgnd = RGB(255, 255, 0); //배경색으로 한다 


		//	}
		//	else
		//	{
		//		crText = RGB(0, 0, 0); //글자색
		//		crBkgnd = RGB(255, 200, 200);//배경색으로 한다   
		//	}
		//}
		//else
		//{
		//	if (l_nItem == m_CurrentStep - 1)
		//	{
		//		crText = RGB(0, 0, 0); //글자색
		//		crBkgnd = RGB(255, 255, 0); //배경색으로 한다 


		//	}
		//	else
		//	{
		//		crText = RGB(0, 0, 0); //글자색
		//		crBkgnd = RGB(255, 200, 200);//배경색으로 한다   
		//	}
		//}

		crText = RGB(0, 0, 0); //글자색			
		crBkgnd = RGB(230, 200, 255);//배경색으로 한다   

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;


		*pResult = CDRF_DODEFAULT;
		return;
	}
	}

	*pResult = 0;
}


void CAcqVoltageSamples_IntClkDlg::OnNMDblclkListMainProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedOptButton()
{
	COptionDlg dlg("Option");
	dlg.DoModal();
	UpdateVersionInfo();

}


void CAcqVoltageSamples_IntClkDlg::ClickLabelName1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static int sSource = 0;
	if (m_TaskRun == TASK_RUN_IDLE)
	{
		sSource++;
		if (sSource >= 4)
			sSource = 0;
		SetChannelDataSeq(1, sSource * 4 + 1);
		SetChannelDataSeq(2, sSource * 4 + 2);
		SetChannelDataSeq(3, sSource * 4 + 3);
		SetChannelDataSeq(4, sSource * 4 + 4);
	}
	
	//if (gbManualScopeMode == 1)
	//{
	//	if (g_ManualId[0] == 0)
	//	{
	//		g_ManualId[0] = 4;
	//		g_ManualId[1] = 5;
	//		g_ManualId[2] = 6;
	//		g_ManualId[3] = 7;
	//		g_ManualId[4] = 0;
	//		g_ManualId[5] = 1;
	//		g_ManualId[6] = 2;
	//		g_ManualId[7] = 3;
	//	}
	//	else
	//	{
	//		g_ManualId[0] = 0;
	//		g_ManualId[1] = 1;
	//		g_ManualId[2] = 2;
	//		g_ManualId[3] = 3;
	//		g_ManualId[4] = 4;
	//		g_ManualId[5] = 5;
	//		g_ManualId[6] = 6;
	//		g_ManualId[7] = 7;

	//	}
	//	
	//	SetChannelDataManual(0);
	//}
	////SetGuiPos(gbManualScopeMode);


	
}

void CAcqVoltageSamples_IntClkDlg::ClickLabelName2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CAcqVoltageSamples_IntClkDlg::ClickLabelName3()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CAcqVoltageSamples_IntClkDlg::ClickLabelName4()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CAcqVoltageSamples_IntClkDlg::SetUSBSel(int Sel1, int Sel2)
{
	BYTE lbuf[128];
	//0x02CUSEL0111 s 0x03//
	int lport1 = 0, lport2 = 1;

	if (Sel1 == 3)
	{
		lport1 = 3;
	}
	if (Sel2 == 3)
	{
		lport2 = 3;
	}

	sprintf((char *)&lbuf, "@CUSEL%d%d%d%ds$", lport1, Sel1, lport2, Sel2);
	lbuf[0] = 0x02;
	lbuf[11] = 0x03;

	SendData(lbuf, 12);
		

	

}




void CAcqVoltageSamples_IntClkDlg::OnBnClickedSyntaxButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadTestData(gTestSeqData.strSeqFileName);
	SetSubListControl();

}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedViewButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char buf[1024];
	
	CString Filename = "C:\\WINDOWS\\system32\\notepad.exe ";
		
	Filename += CurrentSet->sSeqPath;
	//Filename += _T("\\Model\\");
	//Filename += lstrModelname;


	//sprintf(buf, "C:\\WINDOWS\\system32\\notepad.exe %s", Filename.GetBuffer());

	WinExec(Filename, SW_SHOW);//WinExec(buf, SW_SHOW);

	return;


}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedNewButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	if (m_TaskRun != TASK_RUN_IDLE)
	{
		MessageBox("TEST PROCESSING");
		return;
	}
	CSelectGenerateModel lDlg;

	if (IDOK == lDlg.DoModal())
	{

	}
	//SM_ModelNewOpen();
	return;

}
BOOL CAcqVoltageSamples_IntClkDlg::GetResultFromDetailedGrid(int nStepNo, CString& sMsg)
{
	if ((nStepNo > (m_CtrlListMainProcess.GetItemCount() - 1)) || (nStepNo <= 0)) return FALSE;

	sMsg = m_CtrlListMainProcess.GetItemText(nStepNo, 12);

	return TRUE;
}

void CAcqVoltageSamples_IntClkDlg::InsertMsg2DetailedGrid(int nStepNo, CString sMsg)
{
	CString szDetailMessage = sMsg;

	if ((nStepNo > (m_CtrlListMainProcess.GetItemCount() - 1)) || (nStepNo <= 0)) return;

	//	m_ctrlSummaryGrid.SetRedraw(flexRDNone);
	//	m_ctrlSummaryGrid.SetRow(nStepNo);
	m_CtrlListMainProcess.SetItem(nStepNo - 1, 12, LVIF_TEXT, szDetailMessage, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 12, szDetailMessage);

//	m_ctrlSummaryGrid.SetRedraw(-1);
//	m_ctrlSummaryGrid.Refresh();
//	m_CtrlListMainProcess.Invalidate();
}

void CAcqVoltageSamples_IntClkDlg::InsertTotalData2Grid(int nGridType, BOOL bResult, CString sElapsedTime)
{
	if (nGridType == DETAILEDGRID)
	{
		if (StepList.GetCount() > 0)
		{
			CString sTmp;
			//m_ctrlSummaryGrid.SetRedraw(flexRDNone);
			//m_ctrlSummaryGrid.SetCol(3);
			//m_ctrlSummaryGrid.SetRow(StepList.GetCount() + 1);
			if (bResult == TRUE)
			{
				//	m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
				m_CtrlListMainProcessEx.SetCellBackColor(StepList.GetCount(), 2, RGB(0, 0, 255));
				m_CtrlListMainProcessEx.SetCellForeColor(StepList.GetCount(), 2, RGB(255, 255, 255));
				m_CtrlListMainProcess.SetItem(StepList.GetCount(), 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(StepList.GetCount() + 1, 3, "OK");
			}
			else if (bResult == FALSE)
			{

				//	m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
				m_CtrlListMainProcessEx.SetCellBackColor(StepList.GetCount(), 2, RGB(255, 0, 0));
				m_CtrlListMainProcessEx.SetCellForeColor(StepList.GetCount(), 2, RGB(255, 255, 255));
				m_CtrlListMainProcess.SetItem(StepList.GetCount(), 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(StepList.GetCount() + 1, 3, "NG");
			}


			//	m_ctrlSummaryGrid.SetCol(11);
				//m_ctrlSummaryGrid.SetColDataType(11, flexDTString);
			m_CtrlListMainProcess.SetItem(StepList.GetCount(), 11, LVIF_TEXT, sElapsedTime, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(StepList.GetCount() + 1, 11, sElapsedTime);

			m_CtrlListMainProcess.SetItem(StepList.GetCount(), 3, LVIF_TEXT, sElapsedTime, NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(StepList.GetCount() + 1, 11, sElapsedTime);

		//	m_ctrlSummaryGrid.SetRedraw(-1);
		//	m_ctrlSummaryGrid.Refresh();
			m_CtrlListMainProcess.Invalidate();
		}
	}
}

void CAcqVoltageSamples_IntClkDlg::InsertPcbid2Grid(CString sWipID)
{
	if (StepList.GetCount() > 0)
	{
		//m_ctrlSummaryGrid.SetCol(12);
		//m_ctrlSummaryGrid.SetColDataType(12, flexDTString);
		m_CtrlListMainProcess.SetItem(StepList.GetCount(), 12, LVIF_TEXT, sWipID, NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(StepList.GetCount() + 1, 12, sWipID);

	//	m_ctrlSummaryGrid.SetRedraw(-1);
	//	m_ctrlSummaryGrid.Refresh();
		m_CtrlListMainProcess.Invalidate();
	}
}


//-

void CAcqVoltageSamples_IntClkDlg::DeleteResultDataFromGrid(int nGridType, int nStepNo)
{
	if (nGridType == DETAILEDGRID) DeleteResultDataFromDetailedGrid(nStepNo);
}
void CAcqVoltageSamples_IntClkDlg::DeleteResultDataFromDetailedGrid(int nStepNo)
{
	if ((nStepNo > (m_CtrlListMainProcess.GetItemCount() - 1)) || (nStepNo <= 0)) return;

	CString sTmp;
	//	m_ctrlSummaryGrid.SetRedraw(flexRDNone);
	//	m_ctrlSummaryGrid.SetRow(nStepNo);

		//if(nStepNo % 7 == 0) m_CtrlListMainProcess.Scroll(nStepNo*20);

		// (Column 11) Elapsed Time
	if (pCurStep->m_nStepType == PROCESS_FUNCTION)
	{
		//m_ctrlSummaryGrid.SetCol(11);
		//m_ctrlSummaryGrid.SetColDataType(11, flexDTString);
		m_CtrlListMainProcess.SetItem(nStepNo, 11, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); // m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 11, _T(""));

	//	m_ctrlSummaryGrid.SetRedraw(-1);
	//	m_ctrlSummaryGrid.Refresh();

		return;
	}

	// (Column 3) Result
	//m_ctrlSummaryGrid.SetCol(3);
	//m_ctrlSummaryGrid.SetColDataType(3, flexDTString);
	m_CtrlListMainProcessEx.SetCellBackColor(StepList.GetCount(), 2, RGB(255, 255, 255));
	m_CtrlListMainProcessEx.SetCellForeColor(StepList.GetCount(), 2, RGB(255, 255, 255));
	m_CtrlListMainProcess.SetItem(nStepNo, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 3, _T(""));

	if (pCurStep->m_bRunAudioTest)
	{
		// (Column 10) Audio Measure
		//m_ctrlSummaryGrid.SetCol(10);
		//m_ctrlSummaryGrid.SetColDataType(10, flexDTString);
		m_CtrlListMainProcess.SetItem(nStepNo, 10, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo , 10, _T(""));

	}

	// (Column 4) Measure
//	m_ctrlSummaryGrid.SetCol(4);
//	m_ctrlSummaryGrid.SetColDataType(4, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 4, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 4, _T(""));

	//m_ctrlSummaryGrid.SetCol(5);
	//m_ctrlSummaryGrid.SetColDataType(5, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 5, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 5, sTmp);


	// (Column 11) Elapsed Time
	//m_ctrlSummaryGrid.SetCol(11);
	//m_ctrlSummaryGrid.SetColDataType(11, flexDTString);
	m_CtrlListMainProcess.SetItem(nStepNo, 11, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL); //m_ctrlSummaryGrid.SetTextMatrix(nStepNo, 11, _T(""));

	//m_ctrlSummaryGrid.SetRow(0);
	//m_ctrlSummaryGrid.SetCol(0);
	//m_ctrlSummaryGrid.SetRedraw(-1);
	//m_ctrlSummaryGrid.Refresh();
	m_CtrlListMainProcess.Invalidate();
	return;
}

void CAcqVoltageSamples_IntClkDlg::SetGrabInfo(CBaseImage* pBaseImage)
{
	BOOL bChanged = FALSE;

	int nRowWidth = 0;
	int nImageSize = 0;


	//+add kwmoon 080402
	CString szErrMsg = _T("");
	//	int		m_ImageWidth;
	//	int		m_ImageHeight;
	//	int		m_ImageSize;
		//if(m_ImageWidth>m_ImageHeight) != 
	if (m_ImageWidth < 0 || m_ImageWidth > 9000 || m_ImageHeight < 0 || m_ImageHeight > 9000)
	{
		m_ImageWidth = 1920;
		m_ImageHeight = 1080;
		m_ImageSize = m_ImageWidth  * m_ImageHeight ;
	}



	pBaseImage->InitHeaders(COLOR_24BIT, m_ImageWidth, m_ImageHeight, m_ImageSize);

	if (pBaseImage->m_pImageData != NULL) { delete pBaseImage->m_pImageData; pBaseImage->m_pImageData = NULL; }

	pBaseImage->m_pImageData = new BYTE[pBaseImage->m_InfoHeader.biSizeImage];

}



void CAcqVoltageSamples_IntClkDlg::OnBnClickedRefButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//gbManualRefMode = 1;
	//RunTestStart(); //OnBnClickedStart(gbManualRefMode);
	
	if (m_Image_SaveMode == 1)
	{

		CRect lRect;
		m_previewWindow->SetRange(0, lRect);
		m_previewWindow->m_DisplayOK = 1;
		Sleep(100);
		ScreenCapture();
		SaveAsImage();
	}
	else
	{
		m_Image_SaveMode = 1;
	}

}
