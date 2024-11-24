/******************************************************************************
*
* Example program:
*   AcqVoltageSamples_IntClk
*
* Category:
*   AI
*
* Description:
*   This example demonstrates how to acquire a finite amount of data using an
*   internal clock.
*
* Instructions for running:
*   1.  Select the physical channel corresponding to the input signal on the DAQ
*       device.
*   2.  Enter the minimum and maximum voltage ranges.
*       Note:  For better accuracy, try to match the input ranges to the expected
*       voltage level of the measured signal.
*   3.  Select the number of samples per channel to acquire.
*   4.  Set the rate in Hz for the internal clock.
*       Note:  The rate should be at least twice as fast as the maximum frequency
*       component of the signal being acquired.
*
* Steps:
*   1.  Create a new task and an analog input voltage channel.
*   2.  Configure the task to use the internal clock.
*   3.  Create a CNiDAQmxAnalogMultiChannelReader and associate it with the task
*       by using the task's stream.
*   4.  Call CNiDAQmxAnalogMultiChannelReader::ReadMultiSample to acquire and
*       display the data.
*   5.  Destroy the CNiDAQmxTask object to clean-up any resources associated
*       with the task.
*   6.  Handle any CNiDAQmxExceptions, if they occur.
*
* I/O Connections Overview:
*   Make sure your signal input terminals match the physical channel text box. 
*   For more information on the input and output terminals for your device, open
*   the NI-DAQmx Help, and refer to the NI-DAQmx Device Terminals and Device
*   Considerations books in the table of contents.
*
* Microsoft Windows Vista User Account Control
*   Running certain applications on Microsoft Windows Vista requires
*   administrator privileges, because the application name contains keywords
*   such as setup, update, or install. To avoid this problem, you must add an
*   additional manifest to the application that specifies the privileges
*   required to run the application. Some Measurement Studio NI-DAQmx examples
*   for Visual Studio include these keywords. Therefore, all examples for Visual
*   Studio are shipped with an additional manifest file that you must embed in
*   the example executable. The manifest file is named
*   [ExampleName].exe.manifest, where [ExampleName] is the NI-provided example
*   name. For information on how to embed the manifest file, refer to http://msdn2.microsoft.com/en-us/library/bb756929.aspx.
*   
*   Note: The manifest file is not provided with examples for Visual Studio .NET
*   2003.
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
#include "DlgModelSetupSeq.h"

#include "IcmpEcho.h"
//#include "ping.h"

//#include "DlgImage.h"
#include "time.h" 


#include "CableChangeDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define 	TASK_RUN_IDLE				0
#define 	TASK_RUN_START				1
#define 	TASK_RUN_PROCESS			2
#define 	TASK_WAIT_SELECT_PROCESS	3
#define 	TASK_FINISH_PROCESS			4
#define 	TASK_WAIT_BARCODE_PROCESS	5

#define DIG_OPTICAL_SELECT	0
#define DIG_COAX_SELECT		1



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

	m_CheckDelayTime = 100;

	m_MainCOM_NG_Count = 0;

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
	DDX_Control(pDX, IDC_STOP_BUTTON, m_cStopButton);
	DDX_Control(pDX, IDC_TEST_BUTTON, m_cTestButton);
	DDX_Control(pDX, IDOK, m_cExitButton);

	//	DDX_Control(pDX, IDC_TEXTBOX_MODEL, m_TextModel);

	DDX_Control(pDX, IDC_LABEL_BARCODE, m_BarCode);
	DDX_Control(pDX, IDC_LABEL_BARCODE_MARK, m_BarCodeMark);
	DDX_Control(pDX, IDC_LABEL_MODEL, m_cLbModel);
	DDX_Control(pDX, IDC_LABEL__OKNG, m_cLbOkNg);
	DDX_Control(pDX, IDC_LABEL__OKNG1, m_cLb_Test1);
	DDX_Control(pDX, IDC_LABEL__OKNG2, m_cLb_Test2);
	DDX_Control(pDX, IDC_LABEL__OKNG3, m_cLb_Test3);

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
	DDX_Control(pDX, IDC_STATIC_PIC, m_pic);
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
	DDX_Control(pDX, IDC_CHECK_RUN_AUTO, m_CheckRunMode);
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
	//ON_STN_DBLCLK(IDC_STATIC_PIC, &CAcqVoltageSamples_IntClkDlg::OnStnDblclickStaticPic)
	//ON_STN_CLICKED(IDC_STATIC_PIC, &CAcqVoltageSamples_IntClkDlg::OnStnClickedStaticPic)
	ON_WM_RBUTTONDBLCLK()
	ON_CBN_SELCHANGE(IDC_COMBO_NAME_1, &CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName1)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_CHECK_RUN_AUTO, &CAcqVoltageSamples_IntClkDlg::OnBnClickedCheckRunAuto)
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


#define _MANUAL_SCOPE_ADDMODE
// CAcqVoltageSamples_IntClkDlg message handlers

CAcqVoltageSamples_IntClkDlg *mp_MainControl;


BOOL CAcqVoltageSamples_IntClkDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // Set the icon for this dialog.  The framework does this automatically
    // when the application's main window is not a dialog.
    SetIcon(m_hIcon, TRUE);     // Set big icon
    SetIcon(m_hIcon, FALSE);    // Set small icon

	mp_MainControl = this;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	CString strTemp;
	
	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.*/   
		strTemp.Format("WSAStartup failed with error: %d\n", err);
		MessageBox(strTemp);
		return 1;
	}

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
	m_ComSMAV_1100APOk = 0;
	m_WaitPCB_Ack_Limit = 30;
	int lMakeflag = 0;

	CString str, BaseStr;
	BaseStr = _T(PATH_BASE_DIR);
	
	str = _T("D:\\SM Digital");
	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;
	}	
	
	if(_mkdir(BaseStr.GetBuffer())==0)
	{
		lMakeflag = 1;
	}

	//str = _T(PATH_BASE_Back_DIR);
	str = BaseStr + _T("\\Log");
	
	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\log]");
	}		
	
	str = BaseStr + _T("\\Remote");

	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	}		
	
	str = BaseStr + _T("\\Model");

	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	}	
	str = BaseStr + _T("\\Image");

	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	}	

	str = BaseStr + _T("\\Sound");

	if(_mkdir(str.GetBuffer())==0)
	{
		lMakeflag = 1;//MessageBox("Make New Directory => [d:\\nagra\\data]");
	}	

#ifdef _MANUAL_SCOPE_ADDMODE

	this->SetWindowPos(NULL,0, 0,1590,850,SWP_ASYNCWINDOWPOS|SWP_NOMOVE);


	m_cSetupButton.LoadBitmaps(IDB_BITMAP_MODEL_ON, IDB_BITMAP_MODEL_OFF);
	GetDlgItem(IDC_SETUP_BUTTON)->SetWindowPos(NULL,70, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
	GetDlgItem(IDC_START_BUTTON)->SetWindowPos(NULL,145, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
	GetDlgItem(IDC_STOP_BUTTON)->SetWindowPos(NULL,220, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cTestButton.LoadBitmaps(IDB_BITMAP_TEST_ON, IDB_BITMAP_TEST_OFF);
	GetDlgItem(IDC_TEST_BUTTON)->SetWindowPos(NULL,295, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cExitButton.LoadBitmaps(IDB_BITMAP_EXIT_ON, IDB_BITMAP_EXIT_OFF);
	GetDlgItem(IDOK)->SetWindowPos(NULL,370, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cStopButton.LoadBitmaps(IDB_BITMAP_STOP_ON, IDB_BITMAP_STOP_OFF);
	GetDlgItem(IDOK)->SetWindowPos(NULL,370, 85,60,60,SWP_ASYNCWINDOWPOS);

  
	m_cLbModel.SetWindowPos(NULL,450, 95,620+100,40,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_STATIC_MODEL_GROUP)->SetWindowPos(NULL,440, 80,640+100,65,SWP_ASYNCWINDOWPOS);


	m_BarCodeMark.SetWindowPos(NULL,1090+100, 85,235+140,30,SWP_ASYNCWINDOWPOS);
	m_BarCode.SetWindowPos(NULL,1090+100, 115,235+140,30,SWP_ASYNCWINDOWPOS);


	int Xoffset = -20;
//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
	m_NameLabel[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


	m_NameLabel[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
	m_cLb_Test1.SetWindowPos(NULL,35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);

	/////////////
	m_NameLabel[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


	m_NameLabel[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
	m_cLb_Test2.SetWindowPos(NULL,345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);

	m_NameLabel[4].SetWindowPos(NULL,655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[4].SetWindowPos(NULL,775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[4].SetWindowPos(NULL,865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


	m_NameLabel[5].SetWindowPos(NULL,655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[5].SetWindowPos(NULL,775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[5].SetWindowPos(NULL,865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
	m_cLb_Test3.SetWindowPos(NULL,655+80*2+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);

	m_NameLabel[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[6].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[6].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);


	m_NameLabel[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_cComboName[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[7].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[7].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);

	m_CtrlListMainProcess.SetWindowPos(NULL,1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
	GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 220, 110,SWP_ASYNCWINDOWPOS);

	m_cLabelCableManager.SetWindowPos(NULL,1205+Xoffset, 575+95, 220, 30,SWP_ASYNCWINDOWPOS);
	m_cLabelCableMessage.SetWindowPos(NULL,1205+Xoffset, 575+125, 220, 85,SWP_ASYNCWINDOWPOS);
	
	//965
//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125

//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
	m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+300,35,SWP_ASYNCWINDOWPOS);

	//95


	m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
	m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
	/*	
	m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
	m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
*/
	m_CheckTimeLabelName.SetWindowPos(NULL,1425+Xoffset, 688+95, 80,18,SWP_ASYNCWINDOWPOS);
	m_CycleTimeLabelName.SetWindowPos(NULL,1425+Xoffset, 707+95, 80,18,SWP_ASYNCWINDOWPOS);
	m_CheckTimeLabel.SetWindowPos(NULL,1505+Xoffset, 688+95, 80,18,SWP_ASYNCWINDOWPOS);
	m_CycleTimeLabel.SetWindowPos(NULL,1505+Xoffset, 707+95, 80,18,SWP_ASYNCWINDOWPOS);

	

	m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 720+240,110,SWP_ASYNCWINDOWPOS);

	
	m_LanLabelName.SetWindowPos(NULL,35+Xoffset, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
	m_Usb1LabelName.SetWindowPos(NULL,35+Xoffset, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
	m_Usb2LabelName.SetWindowPos(NULL,35+Xoffset, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
	m_CameraLabelName.SetWindowPos(NULL,35+Xoffset, 659+95, 80,26,SWP_ASYNCWINDOWPOS);

	m_cLb_Lan.SetWindowPos(NULL,115+Xoffset, 575+95, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Usb1.SetWindowPos(NULL,115+Xoffset, 603+95, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Usb2.SetWindowPos(NULL,115+Xoffset, 631+95, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Camera.SetWindowPos(NULL,115+Xoffset, 659+95, 110,26,SWP_ASYNCWINDOWPOS);

	m_cLb_ComMain.SetWindowPos(NULL,1425+Xoffset,  575+95, 160,26,SWP_ASYNCWINDOWPOS);
	m_cLb_ComSet.SetWindowPos(NULL,1425+Xoffset, 603+95, 160,26,SWP_ASYNCWINDOWPOS);
	m_cLb_ComLed.SetWindowPos(NULL,1425+Xoffset, 631+95, 160,26,SWP_ASYNCWINDOWPOS);
	m_cLb_ComMainGmes.SetWindowPos(NULL,1425+Xoffset, 659+95, 160,26,SWP_ASYNCWINDOWPOS);


#else


	this->SetWindowPos(NULL,0, 0,1360,765,SWP_ASYNCWINDOWPOS|SWP_NOMOVE);
	//this->SetWindowPlacement(



	m_cSetupButton.LoadBitmaps(IDB_BITMAP_MODEL_ON, IDB_BITMAP_MODEL_OFF);
	GetDlgItem(IDC_SETUP_BUTTON)->SetWindowPos(NULL,70, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
	GetDlgItem(IDC_START_BUTTON)->SetWindowPos(NULL,145, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cBtnStart.LoadBitmaps(IDB_BITMAP_START_ON, IDB_BITMAP_START_OFF);
	GetDlgItem(IDC_STOP_BUTTON)->SetWindowPos(NULL,220, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cTestButton.LoadBitmaps(IDB_BITMAP_TEST_ON, IDB_BITMAP_TEST_OFF);
	GetDlgItem(IDC_TEST_BUTTON)->SetWindowPos(NULL,295, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cExitButton.LoadBitmaps(IDB_BITMAP_EXIT_ON, IDB_BITMAP_EXIT_OFF);
	GetDlgItem(IDOK)->SetWindowPos(NULL,370, 85,60,60,SWP_ASYNCWINDOWPOS);

	m_cStopButton.LoadBitmaps(IDB_BITMAP_STOP_ON, IDB_BITMAP_STOP_OFF);
	GetDlgItem(IDOK)->SetWindowPos(NULL,370, 85,60,60,SWP_ASYNCWINDOWPOS);

  
	m_cLbModel.SetWindowPos(NULL,450, 95,620,40,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_STATIC_MODEL_GROUP)->SetWindowPos(NULL,440, 80,640,65,SWP_ASYNCWINDOWPOS);


	m_BarCodeMark.SetWindowPos(NULL,1090, 85,235,30,SWP_ASYNCWINDOWPOS);
	m_BarCode.SetWindowPos(NULL,1090, 115,235,30,SWP_ASYNCWINDOWPOS);

#if 1

//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
	m_NameLabel[0].SetWindowPos(NULL,35, 150, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[0].SetWindowPos(NULL,155, 150, 90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[0].SetWindowPos(NULL,245, 150, 90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35, 180, 300,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[1].SetWindowPos(NULL,35,  345, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[1].SetWindowPos(NULL,155, 345,  90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[1].SetWindowPos(NULL,245, 345,  90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35, 375, 300,160,SWP_ASYNCWINDOWPOS);
	m_cLb_Test1.SetWindowPos(NULL,35, 540, 300,30,SWP_ASYNCWINDOWPOS);

	/////////////
	m_NameLabel[2].SetWindowPos(NULL,345, 150, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[2].SetWindowPos(NULL,465, 150, 90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[2].SetWindowPos(NULL,555, 150, 90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345, 180, 300,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[3].SetWindowPos(NULL,345, 345, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[3].SetWindowPos(NULL,465, 345,  90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[3].SetWindowPos(NULL,555, 345,  90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345, 375, 300,160,SWP_ASYNCWINDOWPOS);
	m_cLb_Test2.SetWindowPos(NULL,345, 540, 300,30,SWP_ASYNCWINDOWPOS);

	m_NameLabel[4].SetWindowPos(NULL,655, 150, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[4].SetWindowPos(NULL,775, 150,  90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[4].SetWindowPos(NULL,865, 150,  90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,655, 180, 300,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[5].SetWindowPos(NULL,655, 345, 120, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[5].SetWindowPos(NULL,775, 345, 90, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[5].SetWindowPos(NULL,865, 345, 90, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,655, 375, 300,160,SWP_ASYNCWINDOWPOS);

	m_cLb_Test3.SetWindowPos(NULL,655, 540, 300,30,SWP_ASYNCWINDOWPOS);

	m_CtrlListMainProcess.SetWindowPos(NULL,965, 150, 360, 420,SWP_ASYNCWINDOWPOS);//1015
#else
	//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
	m_NameLabel[0].SetWindowPos(NULL,35, 150, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[0].SetWindowPos(NULL,199, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[0].SetWindowPos(NULL,327, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35, 180, 420,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[1].SetWindowPos(NULL,35, 345, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[1].SetWindowPos(NULL,199, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[1].SetWindowPos(NULL,327, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35, 375, 420,160,SWP_ASYNCWINDOWPOS);
	m_cLb_Test1.SetWindowPos(NULL,35, 540, 420,30,SWP_ASYNCWINDOWPOS);

	m_NameLabel[2].SetWindowPos(NULL,470, 150, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[2].SetWindowPos(NULL,634, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[2].SetWindowPos(NULL,762, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,470, 180, 420,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[3].SetWindowPos(NULL,470, 345, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[3].SetWindowPos(NULL,634, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[3].SetWindowPos(NULL,762, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,470, 375, 420,160,SWP_ASYNCWINDOWPOS);
	m_cLb_Test2.SetWindowPos(NULL,470, 540, 420,30,SWP_ASYNCWINDOWPOS);

	m_NameLabel[4].SetWindowPos(NULL,905, 150, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[4].SetWindowPos(NULL,1069, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[4].SetWindowPos(NULL,1197, 150, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,905, 180, 420,160,SWP_ASYNCWINDOWPOS);


	m_NameLabel[5].SetWindowPos(NULL,905, 345, 164, 30,SWP_ASYNCWINDOWPOS);
	m_FreqLabel[5].SetWindowPos(NULL,1069, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	m_VoltLabel[5].SetWindowPos(NULL,1197, 345, 128, 30,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,905, 375, 420,160,SWP_ASYNCWINDOWPOS);

	m_cLb_Test3.SetWindowPos(NULL,905, 540, 420,30,SWP_ASYNCWINDOWPOS);
#endif
	

//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125

//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
	m_MessageDisplay.SetWindowPos(NULL,165, 690, 960,35,SWP_ASYNCWINDOWPOS);




	m_OKCntLabelName.SetWindowPos(NULL,35, 688, 50,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabelName.SetWindowPos(NULL,35, 707, 50,18,SWP_ASYNCWINDOWPOS);
	m_OKCntLabel.SetWindowPos(NULL,85, 688, 75,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabel.SetWindowPos(NULL,85, 707, 75,18,SWP_ASYNCWINDOWPOS);
	/*	
	m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
	m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
	m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
*/
	m_CheckTimeLabelName.SetWindowPos(NULL,1130, 688, 110,18,SWP_ASYNCWINDOWPOS);
	m_CycleTimeLabelName.SetWindowPos(NULL,1130, 707, 110,18,SWP_ASYNCWINDOWPOS);
	m_CheckTimeLabel.SetWindowPos(NULL,1240, 688, 85,18,SWP_ASYNCWINDOWPOS);
	m_CycleTimeLabel.SetWindowPos(NULL,1240, 707, 85,18,SWP_ASYNCWINDOWPOS);



	m_cLbOkNg.SetWindowPos(NULL,235, 575, 720,110,SWP_ASYNCWINDOWPOS);
	GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,965, 575, 360, 110,SWP_ASYNCWINDOWPOS);
	
	m_LanLabelName.SetWindowPos(NULL,35, 575, 80,26,SWP_ASYNCWINDOWPOS);
	m_Usb1LabelName.SetWindowPos(NULL,35, 603, 80,26,SWP_ASYNCWINDOWPOS);
	m_Usb2LabelName.SetWindowPos(NULL,35, 631, 80,26,SWP_ASYNCWINDOWPOS);
	m_CameraLabelName.SetWindowPos(NULL,35, 659, 80,26,SWP_ASYNCWINDOWPOS);

	m_cLb_Lan.SetWindowPos(NULL,115, 575, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Usb1.SetWindowPos(NULL,115, 603, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Usb2.SetWindowPos(NULL,115, 631, 110,26,SWP_ASYNCWINDOWPOS);
	m_cLb_Camera.SetWindowPos(NULL,115, 659, 110,26,SWP_ASYNCWINDOWPOS);
#endif



//	CString str;

	float lfval = 0.0;
	str.Format(_T("%.1f (s)"), lfval);	
	m_CheckTimeLabel.put_Caption(str);

	lfval = 0.0;
	str.Format(_T("%.1f (s)"), lfval);	
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

#ifdef __G_MES_SET_MODE__
	if(lFile.Read_ConfigSeqData())
	{
		lFile.SaveConfigSeqData();
	}
#else

	if(lFile.Read_ConfigData())
	{
		lFile.SaveConfigData();
	}

#endif


	m_CheckRunMode.SetCheck(g_RunModeType);

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


	lFile.Read_IniModel();//gTestSeqData.strModelName
	lFile.OpenModel(gTestSeqData.strModelName);
	LoadTestData(gTestSeqData.strSeqFileName);

	
	OpenComport();
	OpenComportPCB();
	OpenComportLED();
	OpenComportSCAN();
	

//	CString str;
if(m_ComPort.mPort_Opened== FALSE)
	{
		str.Format(_T("MAIN COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
	
		MessageBox(str);
	}
	if(m_ComPortPCB.mPort_Opened == FALSE)
	{	
		str.Format(_T("Audio COM Port %d Open FAIL !!"), gTestSeqData.nPort_Pcb);
		MessageBox(str);
	}
	
	if(m_ComPortLED.mPort_Opened == FALSE)
	{
		str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);		
		MessageBox(str);
	}
	
	if(m_ComPortScanner.mPort_Opened == FALSE)
	{	
		str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);		
		MessageBox(str);
	}



	SetListControl();
	DisplayTestData();
		
	CheckDigitalPort();

	GetRmtCodeList(gTestSeqData.strRemoconFileName);

	str = gTestSeqData.strModelName;
	m_cLbModel.put_Caption((LPCSTR)str);

	m_DO_Writedata = 0;

	m_DIportOpen = 1;
	m_DOportOpen = 1;

	m_NewSystemCheck = 0;
	m_RecvCnt = 0;
	m_MainPAGE_COM_PROCESS = 0;
	m_ComAck = 0;
	m_ResendCnt = 0;
	m_ComWaitCnt = 0;
	m_DigitalPort = DIG_OPTICAL_SELECT;

	m_PrecodeWait = 0;

	#ifdef __START_DEBUG_MODE_
	MessageBox("4");
#endif

	//if(lFile.Read_ConfigData())
	//{
	//	lFile.SaveConfigData();
	//}

	
	// Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
	//CString sMsg;
	//BOOL bRev =  g_MesDb.Mes_Open_Test(_T("DAVMDEV"),_T("oraspc"),_T("spcora00"),sMsg);//:Mes_Open_Test(CString strDsn, CString strUserID, CString strPassWD, CString &strRtn)
	///*
//	oraspc
//spcora00
//	*/
//	if(bRev == 0)
//	{
//		MessageDisplay(1, _T("MES CHECK ERROR!!"));
//
//	}

	//g_strMesTns = _T("DAVMDEV");
	//g_strMesAvn = _T("ORADAVMES");
	//g_strMesUserID = _T("oraspc");
	//g_strMesPassword = _T("spcora00");
	m_GMES_CommError = 0;
#ifdef __G_MES_SET_MODE__

	//Send Are You There
	

	//CreateEthernetSocket();
	m_GmesOpen = 0;
	if(gTestSeqData.bMesEnable)
	{

	}
	else
	{
		
		m_cLb_ComMainGmes.put_BackColor(0x000F8F8F);
	}
		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		m_EthernetWaitCnt = 0;


#else //#endif
		
	if(gTestSeqData.bMesEnable)
	{	
		CurrentSet.strMesDsn = g_strMesTns;
		CurrentSet.strMesUserId = g_strMesUserID;
		CurrentSet.strMesPassWord = g_strMesPassword;//g_strMesAvn
		CurrentSet.strMesAvn = g_strMesAvn;
		CurrentSet.strProductionLine = g_strMesLine;
		CurrentSet.strStepName = g_strMesInspStep;


		CString sMsg;
		int bRev = g_MesDb.Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
		if(bRev)
		{
			MessageDisplay(0, _T("MES OPEN TEST OK!!"));
			//MessageBox(sMsg);
		}
		else
		{
			MessageDisplay(1, _T("MES OPEN TEST NG!!"));
			MessageBox(sMsg);

		}	
	}

	//g_MesDb.Close()

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
		MessageBox("Audio Capture Card INIT FAIL!!");
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

	if(gTestSeqData.bMesEnable)
	{
		ulIP = ping.ResolveIP( g_nRemoteIPAddress.GetBuffer() );
		delay = ping.PingHostOK( ulIP, PING_TIMEOUT);


		if(delay > 100)
		{
			m_cLb_ComMainGmes.put_BackColor(0x000000FF);
			MessageBox("GMES NOT Connected!");
			m_GmesOpen = 0;// gTestSeqData.bMesEnable = 0;
			m_EthernetMode =  ETHERNET_MODE_IDLE;
		}
	}

#ifdef _CAMERA_CAPTURE_MIODE___
	CString MyIPstr = GetMyIPAddress();
	if(MyIPstr.Compare(gTestSeqData.strCameraIPAddress) == 0)
	{
		delay = 1000;
	}
	else
	{

		ulIP = ping.ResolveIP( gTestSeqData.strCameraIPAddress.GetBuffer() );
		delay = ping.PingHostOK( ulIP, PING_TIMEOUT);
	}
#ifdef __START_DEBUG_MODE_
	MessageBox("9");
#endif
	if(delay > 100)
	{
		if(IDYES == MessageBox("Camera Not Connected\r\nDo You Search Camera?? ", "Search Camera",MB_YESNO))
		{
			for(int i = 2; i < 10; i++)
			{
				strtmpIPAddress.Format(_T("192.168.0.%d"), i);
				if(MyIPstr.Compare(gTestSeqData.strCameraIPAddress) == 0)
				{
					continue;
				}
				ulIP = ping.ResolveIP( strtmpIPAddress.GetBuffer() );
				delay = ping.PingHostOK( ulIP, PING_TIMEOUT);
				if(delay < 100)
				{
					strtmp = "Camera Found IP: ";
					strtmp += strtmpIPAddress;
					MessageBox(strtmp);
					gTestSeqData.strCameraIPAddress = strtmpIPAddress;
					break;
				}
			}
		}
	}

#ifdef __START_DEBUG_MODE_
	MessageBox("10");
#endif
	strtmp = ping.RtnStr;
	if(delay < 100)
	{
		string videoStreamAddress = "rtsp://admin:admin@192.168.0.3/5554"; 
		CString strAddress  = _T("rtsp://admin:admin@");
		strAddress += gTestSeqData.strCameraIPAddress;
		strAddress += "/5554";

		videoStreamAddress = strAddress.GetBuffer();



		if (!vcap.open(videoStreamAddress)) 
		{ 
			AfxMessageBox("Camera Connect Fail");	
			m_Camera_Capture_Flag = 0;
			g_CameraFound = 0;
		}
		else
		{
			m_Camera_Capture_Flag = 1;
			g_CameraFound = 1;
		}
	}
	
	else
	{
		CString str = gTestSeqData.strCameraIPAddress;
		str += "  Camera Find Fail: ";
		str += strtmp;
		AfxMessageBox(str);
		
		//if(IDYES == MessageBox(str.GetBuffer(),"CAMERA", MB_YESNO))
		//{
		//	string videoStreamAddress =  "rtsp://admin:admin@192.168.0.2/5554"; 
		//	if (!vcap.open(videoStreamAddress)) 
		//	{ 
		//		AfxMessageBox("Camera Connect Fail");	
		//		//m_Camera_Capture_Flag = 0;
		//		g_CameraFound = 0;
		//	}
		//	else
		//	{
		//		m_Camera_Capture_Flag = 1;
		//		g_CameraFound = 1;
		//	}
		//}
		//else
		{
			m_Camera_Capture_Flag = 0;
			g_CameraFound = 0;
		}
	}
#else
	m_Camera_Capture_Flag = 0;
	g_CameraFound = 0;
	gbShutdown = true;
#endif

#ifdef __START_DEBUG_MODE_
	MessageBox("11");
#endif
//	bCapture = false;

	if(m_Camera_Capture_Flag ==1)
	{
		gbShutdown = false;
		pThreadCap = AfxBeginThread(threadCapture, this);


				
		m_pDC = m_pic.GetDC();
		m_pic.GetClientRect(&rect);
	
		memDC.CreateCompatibleDC(m_pDC);
		Bitmap.CreateCompatibleBitmap(m_pDC,rect.Width(),rect.Height());
	
		pOldBitmap = memDC.SelectObject(&Bitmap);
	}



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
	//#include "DlgSimpleInform.h"

	m_pUserMsgDlg = new CUserMsgDlg;
	m_pUserMsgDlg->Create(CUserMsgDlg::IDD, this);
	m_pUserMsgDlg->ShowWindow(SW_HIDE);//SetWindowPos(this,rectP.left+ 15,rectP.top+160,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);

#ifdef __START_DEBUG_MODE_
	MessageBox("12");
#endif

	//NG_Display("rorouerqrpotq\r\nuuhrthert\r\njhhguoyt");
	// Return TRUE unless you set the focus to a control.
    return TRUE;
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
	m_GmesOpen = 0;// gTestSeqData.bMesEnable = 0;
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
		m_GmesOpen = 0;//gTestSeqData.bMesEnable = 0;
		
		return FALSE;
	}
	if (m_strMesSend.GetLength() == 0) 
	{
		MessageDisplay(1, "GMES Data Strings ERROR to Send");
		//gTestSeqData.bMesEnable = 0;
		//m_EthernetMode =  ETHERNET_MODE_IDLE;
		return FALSE;
	}

	//if (g_nRemoteIPAddress.GetLength() == 0)
	//{
	//	MessageDisplay(1, "Please Type the remote IPaddress to Send to");
	//	m_EthernetMode =  ETHERNET_MODE_IDLE;
	//	gTestSeqData.bMesEnable = 0;
	//	return FALSE;
	//}


	if(m_pUDPSocket->m_Connected == 0)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		MessageDisplay(1, "GMES Socket Not Connected!!");
		m_EthernetMode =  ETHERNET_MODE_IDLE;
		m_GmesOpen = 0;//gTestSeqData.bMesEnable = 0;
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
		m_GmesOpen = 0;//gTestSeqData.bMesEnable = 0;
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
		m_GmesOpen = 0;//gTestSeqData.bMesEnable = 0;
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


void CAcqVoltageSamples_IntClkDlg::GMES_Scan_InformSend(int lSendForce) //S6F11
{
	if (lSendForce == 0)
	{
		if (m_GMES_Skipped == 1)
		{
			return;
		}
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
	m_strMesSend += g_strModelName;
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
	m_strMesSend += g_strModelName;
	m_strMesSend += _T("</NAME>\r\n");

	m_strMesSend += _T("    <SUFFIX>");
	m_strMesSend += g_strModelSuffix;
	m_strMesSend += _T("</SUFFIX>\r\n");

	m_strMesSend += _T("    </MODEL>\r\n");//</MODEL>

	m_strMesSend += _T("  </ELEMENT>\r\n");	


	m_strMesSend += _T("  <ITEM>\r\n");
//	m_strMesSend += _T("<SUBITEMLISTCOUNT=\"n\">");
//	str1.Format(    _T("    <SUBITEMLIST COUNT=\"%d\">\r\n"), m_AlarmNumber);
	str1 =  _T("    <SUBITEMLIST COUNT=\"6\">\r\n");
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

	m_strMesSend += _T("      <NAME>WIFI_MAC</NAME>\r\n");
	m_strMesSend += _T("      <VALUE>");
	//str1 = m_CheckTimeLabel.get_Caption();
	//str1 = str1.Left(str1.Find(" (s)"));
	m_strMesSend += gSaveInfo.strWifiMacAddress;
	m_strMesSend += _T("</VALUE>\r\n");

	m_strMesSend += _T("      <NAME>BT_MAC</NAME>\r\n");
	m_strMesSend += _T("      <VALUE>");
	//str1 = m_CheckTimeLabel.get_Caption();
	//str1 = str1.Left(str1.Find(" (s)"));
	m_strMesSend += gSaveInfo.strBTMacAddress;
	m_strMesSend += _T("</VALUE>\r\n");

	//if(m_TEST_Result == 0)
	//{
	//	m_strMesSend += _T("      <NAME>NG_ITEM</NAME>\r\n");
	//	m_strMesSend += _T("      <VALUE>");
	//	str1 = m_GMES_ErrorName;//m_GMES_ErrorValue;
	//	m_strMesSend += str1;
	//	m_strMesSend += _T("</VALUE>\r\n");

	//	m_strMesSend += _T("      <NAME>NG_VALUE</NAME>\r\n");
	//	m_strMesSend += _T("      <VALUE>");
	//	str1 = m_GMES_ErrorValue;
	//	m_strMesSend += str1;
	//	m_strMesSend += _T("</VALUE>\r\n");
	//}


	for (int i = 0; i < 3; i++)
	{
		if (gSaveInfo.strTestProcessResult[i].GetLength() > 0)
		{
			str1.Format(_T("      <NAME>PROCESS_RESULT %d</NAME>\r\n"), i + 1);// gSaveInfo.strTestProcessResult[i]);
			m_strMesSend += str1;// _T("      <NAME>PROCESS_RESULT</NAME>\r\n");
			m_strMesSend += _T("      <VALUE>");
			//	str1 = m_GMES_ErrorName;//m_GMES_ErrorValue;
			m_strMesSend += gSaveInfo.strTestProcessResult[i];
			m_strMesSend += _T("</VALUE>\r\n");
		}
		else 
		{
			break;
		}
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
//	if(gTestSeqData.bMesEnable)
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

	CLOSE_Result_Display();

	m_GMES_CommError = 0;
	m_WipID = m_BarCode.get_Caption();
	if(gbManualScopeMode)
	{
		MessageBox("MANUAL SCOPE MODE!!");
		return;

	}
		
	if((m_TaskRun != TASK_RUN_IDLE) && (m_TaskRun != TASK_WAIT_SELECT_PROCESS)&& (m_TaskRun != TASK_WAIT_BARCODE_PROCESS))
	{
		return;
	}
	gSaveInfo.strWifiMacAddress = "";
	gSaveInfo.strBTMacAddress = "";
	if(gTestSeqData.bMesEnable && (m_GmesOpen  == 1))
	{
		if(m_WipID.GetLength() > 5)
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
////In BH 181228
//		if(m_WipID.GetLength() > 5)
//		{
//			m_GMES_Skipped = 0;
//			g_strSetID = m_WipID;
//			GMES_Scan_InformSend();//m_WipID
//
//		}
//		else
//		{
//			MessageDisplay(1, _T("BAR CODE EMPTY!! "));
//			//MessageBox("Barcode Not Read !\r\n GMES not Availbele!");
//			BarcodeErrorDisplay();
//			m_TaskRun = TASK_WAIT_BARCODE_PROCESS;
//			return;
//			/*if(IDYES != MessageBox("Barcode Not Read !\r\n Contonue test?", "Barcode Error", MB_YESNO))
//			{
//				MessageDisplay(1, _T("TEST STOP !! "));
//					
//			}
//			else
//			{
//				m_GMES_Skipped = 1;
//			}*/
//		}

	}
//	//Emd In BH 181228

	//CFileControl lFile;
	//CString LogStr;
	//lFile.SaveProcessLOG(LogStr, 1);
	AddProcessLog("(START)", 1);
//	CLOSE_Result_Display();


	m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
	m_LED_COM_PROCESS = COM_MODE_IDLE;
	m_PCB_COM_PROCESS = COM_MODE_IDLE;

	
	SetTimeCheck(4);
	SetTimeCheck(6);

	CString str;
	unsigned long lCheck_Time = GetTimeCheck(4);

	str.Format(_T("%.1f (s)"), lCheck_Time/1000.0);
	m_CheckTimeLabel.put_Caption(str);

	lCheck_Time = GetTimeCheck(5);
	if(lCheck_Time > 1000000)
		lCheck_Time = 1000000;

//	g_CycleTime = 
	str.Format(_T("%.1f (s)"), lCheck_Time/1000.0);
	m_CycleTimeLabel.put_Caption(str);
	SetTimeCheck(5);

	CheckTimeOn = 1;
	CycleTimeOn = 1;


//	SetChannelData(0);
//	InitChannel();	
#ifdef __G_MES_SET_MODE__

#else //#endif
	if(gTestSeqData.bMesEnable)
	{
		MesStart();
	}
	else
	{
		m_bStartMES = FALSE;
	}
#endif
	m_TaskRun = TASK_RUN_START;
	m_RunCounter = 0;
	//SetTimer(1,10,NULL);	
	m_cLb_Test1.put_Caption(_T("WAIT"));
	m_cLb_Test1.put_BackColor(0x0000FFFF);
	
	m_cLb_Test2.put_Caption(_T("WAIT"));
	m_cLb_Test2.put_BackColor(0x0000FFFF);
	
	m_cLb_Test3.put_Caption(_T("WAIT"));
	m_cLb_Test3.put_BackColor(0x0000FFFF);

	


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
	
	for(int  i = 0; i < 6; i++)
	{
		m_CheckEnable[i] = 0;
	}

	for(int  i = 0; i < gTestSeqData.TestCnt; i++)
	{		

		m_CtrlListMainProcess.SetItem(i, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);   
		m_CtrlListMainProcess.SetItem(i, 3, LVIF_TEXT, _T("0"), NULL, NULL, NULL, NULL);   	
	//	m_CtrlListTestProcess.SetItem(i, 9, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);   

		if(m_CtrlListMainProcess.GetCheck(i))
		{
			gTestSeqData.TestStepList[i].bEnable = 1;			
		}
		else
		{
			if (gTestSeqData.bMesEnable && (m_GmesOpen  == 1))
			{
				gTestSeqData.TestStepList[i].bEnable = 1;	
				m_CtrlListMainProcess.SetCheck(i);
			}
			else
			{
				gTestSeqData.TestStepList[i].bEnable = 0;
			}
		}
		m_CtrlListMainProcess.Update(i);

		gTestSeqData.TestStepList[i].m_Result = 3;
		
	}

	for(int i = 0; i < 8; i++)
	{
				
		m_graph[i].Axes.Item("YAxis-1").Maximum = 1.2;
		m_graph[i].Axes.Item("YAxis-1").Minimum = -1.2;
	}

	gTestSeqData.m_TotalResult = 3;

	m_nCurrentNumber = 0;
	m_nCurrentProcess = 0;
	for(int i = m_nCurrentNumber;i < gTestSeqData.TestCnt; i++)
	{	
	
		m_nCurrentNumber = i;
		if(gTestSeqData.TestStepList[i].bEnable == 0)
		{
		}
		else
		{
			
			break;
		}
	}
	m_CtrlListMainProcess.Invalidate();

	//m_CtrlListMainProcess.click
	if(m_ComSMAV_1100APOk != 1)
		SetDigitalPortSelect(1, 1);
	
	m_NG_Retry_Count = 0;
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
		SetFunction();
		break;
	case 1:
		RunFunction();
		break;
	case 2:
		//GetFunction();m_nCurrentNumber

		m_nCurrentStep = 0;
		m_nCurrentProcess++;
		if (g_RunModeType == _ERROR_STOP)
		{
			if ((m_nCurrentProcess >= gTestSeqData.TestStepList[m_nCurrentNumber].nCount) || (gTestSeqData.TestStepList[m_nCurrentNumber].m_Result == 0))
			{
				for (int i = 0; i < 6; i++)
				{
					m_nBalanceEnable[i] = 0;
				}

				if (gTestSeqData.TestStepList[m_nCurrentNumber].m_Result == 1)
				{
					m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
				}
				else
				{
					m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);

					gTestSeqData.TestStepList[m_nCurrentNumber].strNG_Reason = m_GMES_ErrorName;
					gTestSeqData.TestStepList[m_nCurrentNumber].strNG_Reason += m_GMES_ErrorValue;

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

				unsigned long lCheck_Time = GetTimeCheck(6);
				CString str;
				str.Format(_T("%.1f"), lCheck_Time / 1000.0);
				m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				SetTimeCheck(6);

				m_nCurrentNumber++;

				int i;
				for (i = m_nCurrentNumber; i < gTestSeqData.TestCnt; i++)
				{
					if (gTestSeqData.TestStepList[i].bEnable == 0)
					{
					}
					else
					{
						break;
					}
				}
				m_nCurrentNumber = i;


				if (m_nCurrentNumber >= gTestSeqData.TestCnt)
				{
					TestFinishGMES();//TestFinish();
				}
				else
				{
					m_nCurrentProcess = 0;
					for (int i = 0; i < 6; i++)
					{
						m_CheckEnable[i] = 0;
					}
				}
				m_CtrlListMainProcess.Invalidate();

				m_NG_Retry_Count = 0;
				m_NG_WaitFlag = 0;
			}
		}
		else //AUTO CONTINUE
		{
			if ((m_nCurrentProcess >= gTestSeqData.TestStepList[m_nCurrentNumber].nCount) )
			{
				for (int i = 0; i < 6; i++)
				{
					m_nBalanceEnable[i] = 0;
				}

				if (gTestSeqData.TestStepList[m_nCurrentNumber].m_Result == 1)
				{
					m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
				}
				else
				{
					m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);

					gTestSeqData.TestStepList[m_nCurrentNumber].strNG_Reason = m_GMES_ErrorName;
					gTestSeqData.TestStepList[m_nCurrentNumber].strNG_Reason += m_GMES_ErrorValue;
				
					//NG_Display(m_GMES_ErrorName);
					//m_TaskRun = TASK_WAIT_SELECT_PROCESS;

					////m_NG_Retry_Count++;//m_NG_WaitFlag = 0;

					//break;
				}

				unsigned long lCheck_Time = GetTimeCheck(6);
				CString str;
				str.Format(_T("%.1f"), lCheck_Time / 1000.0);
				m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
				SetTimeCheck(6);

				m_nCurrentNumber++;

				int i;
				for (i = m_nCurrentNumber; i < gTestSeqData.TestCnt; i++)
				{
					if (gTestSeqData.TestStepList[i].bEnable == 0)
					{
					}
					else
					{
						break;
					}
				}
				m_nCurrentNumber = i;


				if (m_nCurrentNumber >= gTestSeqData.TestCnt)
				{
					TestFinishGMES();//TestFinish();
				}
				else
				{
					m_nCurrentProcess = 0;
					for (int i = 0; i < 6; i++)
					{
						m_CheckEnable[i] = 0;
					}
				}
				m_CtrlListMainProcess.Invalidate();

				m_NG_Retry_Count = 0;
				m_NG_WaitFlag = 0;
			}
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
//void CAcqVoltageSamples_IntClkDlg::CheckFunction()
//{
//	CString lFunctionString;
//
//	m_FunctionType = TEST_SEQ_TYPE_END;
//
//	lFunctionString = gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
//	int lpos, lendpos;
//	lpos = lFunctionString.Find("(");
//	lendpos = lFunctionString.Find(")");
//	lFunctionString = lFunctionString.Left(lendpos);
//	m_FunctionName = lFunctionString.Left(lpos);
//	m_FunctionName = m_FunctionName.MakeLower();
//	m_FunctionParameter = lFunctionString.Mid(lpos + 1);
//
//	if (m_FunctionName.Compare("delay") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_DELAY;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//		if (m_CheckDelayTime < 0)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}//TEST_SEQ_TYPE_BEEP
//	else if (m_FunctionName.Compare("beep") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_BEEP;
//
//		int lpos, lendpos;
//		DWORD lFreq, lDelay;
//
//
//		lpos = m_FunctionParameter.Find(",");
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
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
//		mpDlgSimpleInform->ShowWindow(SW_SHOW);
//		mpDlgSimpleInform->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
//		//mpDlgSimpleInform->ShowWindow(SW_SHOW);
//
//		CString m_NgWaveFile = _T(PATH_BASE_DIR);
//		m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//		sndPlaySound(m_NgWaveFile, SND_ASYNC);
//
//		m_nCurrentStep = 2;
//	}
//	else if (m_FunctionName.Compare("usermessage") == 0)
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
//		DWORD lFreq, lDelay;
//
//		lpos = m_FunctionParameter.Find(",");
//
//		str1 = m_FunctionParameter.Left(lpos);
//		str2 = m_FunctionParameter.Mid(lpos + 1);
//
//		str1.Trim();
//		str1.TrimLeft("\"");
//		str1.TrimRight("\"");
//
//		lpos = str2.Find(",");
//		if (lpos > 0)
//		{
//			str3 = str2.Left(lpos);
//			str4 = str2.Mid(lpos + 1);
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
//		m_pUserMsgDlg->m_Close_Result = _OPEN_DISPLAY_;
//
//		CRect rectP;
//		CRect rect;
//		this->GetWindowRect(&rectP);
//		m_pUserMsgDlg->GetWindowRect(&rect);
//
//		m_pUserMsgDlg->ShowWindow(SW_SHOW);
//		m_pUserMsgDlg->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
//
//
//		CString m_NgWaveFile = _T(PATH_BASE_DIR);
//		m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//		sndPlaySound(m_NgWaveFile, SND_ASYNC);
//
//
//
//
//		//BOOL _NotifyMessage()
//		//{
//		//
//		//	CString sMsg1;
//		//	CString sMsg2;
//		//	BOOL    bRetrun = TRUE;
//		//
//		//	pos = pCurFunc->m_ArgumentList.GetHeadPosition();
//		//	if (pos!= NULL)
//		//	{
//		//        sMsg1 = GetString();
//		//        sMsg2 = GetString();
//		//
//		//		g_pView->m_UserMsgDlg.SetMessage(sMsg1,sMsg2);
//		//		g_pView->m_UserMsgDlg.DoModal();
//		//
//		//		bRetrun = g_pView->m_UserMsgDlg.m_bYes;
//		//	
//		//	}
//		//
//		//	if(!bRetrun) CurrentSet->bRunAbort = TRUE;
//		////090408
//		////	return bRetrun;
//		//	return TRUE;
//		//}
//
//	}
//	else if (m_FunctionName.Compare("manual_check") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MANUAL_CHECK;
//
//		m_LED_Up_DI_ReadData[1] = 0;
//		m_LED_Up_DI_ReadData[2] = 0;
//
//		int lpos, lendpos;
//		DWORD lFreq, lDelay;
//
//
//		lpos = m_FunctionParameter.Find(",");
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
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
//		mpDlgSimpleInform->m_Close_Result = _OPEN_DISPLAY_;
//		mpDlgSimpleInform->ShowWindow(SW_SHOW);
//		mpDlgSimpleInform->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
//		//mpDlgSimpleInform->ShowWindow(SW_SHOW);
//
//		CString m_NgWaveFile = _T(PATH_BASE_DIR);
//		m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//		sndPlaySound(m_NgWaveFile, SND_ASYNC);
//
//		//m_nCurrentStep = 2;
//	}
//	else if (m_FunctionName.Compare("waitmessage") == 0)// waitmessage("ARC SPK Out Test" ,"" )
//	{
//		m_FunctionType = TEST_SEQ_TYPE_WAIT_MASSAGE;
//
//		m_LED_Up_DI_ReadData[1] = 0;
//		m_LED_Up_DI_ReadData[2] = 0;
//
//		int lpos, lendpos;
//		DWORD lFreq, lDelay;
//
//
//		lpos = m_FunctionParameter.Find(",");
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
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
//		m_pUserMsgDlg->m_Close_Result = _OPEN_DISPLAY_;
//
//		this->GetWindowRect(&rectP);
//		m_pUserMsgDlg->GetWindowRect(&rect);
//
//		m_pUserMsgDlg->ShowWindow(SW_SHOW);
//		m_pUserMsgDlg->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
//
//
//		CString m_NgWaveFile = _T(PATH_BASE_DIR);
//		m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
//		sndPlaySound(m_NgWaveFile, SND_ASYNC);
//
//
//	}
//	else if ((m_FunctionName.Compare("remocon_out") == 0) || (m_FunctionName.Compare("remocon_out1") == 0))
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_KEY;
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//
//
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("remocon_out2") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_PRE_KEY;
//		int lpos, lendpos;
//		/*	lpos = m_FunctionParameter.Find("\"");
//			lendpos = m_FunctionParameter.Find("\"");
//
//			CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);
//			m_strMP_Key = strtemp;*/
//
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("remocon_repeat") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		//////////////////////////////////////////////////
//		m_FunctionParameter = m_FunctionParameter.Mid(lendpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		strtemp = m_FunctionParameter.Left(lpos);
//		m_RepeatCount = _ttoi(strtemp);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		m_FunctionParameter.Mid(lpos + 1);
//		//	lpos = m_FunctionParameter.Find(",");
//
//		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
//		m_CheckDelayTime = _ttoi(strtemp);
//
//		////////////////////////////////////////////////
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//
//	else if (m_FunctionName.Compare("remocon_repeat10") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT10_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("remocon_repeat2") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_PRE_REPEAT_KEY;
//		int lpos, lendpos;
//		/*lpos = m_FunctionParameter.Find("\"");
//		lendpos = m_FunctionParameter.Find("\"");
//
//		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strMP_Key = strtemp;
//		//////////////////////////////////////////////////
//		m_FunctionParameter = m_FunctionParameter.Mid(lendpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		strtemp = m_FunctionParameter.Left(lpos);
//		m_RepeatCount = _ttoi(strtemp);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		m_FunctionParameter.Mid(lpos + 1);
//		//	lpos = m_FunctionParameter.Find(",");
//
//		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
//		m_CheckDelayTime = _ttoi(strtemp);
//
//		////////////////////////////////////////////////
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("set_audio_display") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_SET_DISPLAY;
//
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
//
//		int l_nChannel = _ttoi(str1);
//		int l_nRange = _ttoi(str2);
//
//		if (l_nChannel > 8)
//		{
//			for (int i = 0; i < 8; i++)
//			{
//
//				m_graph[i].Axes.Item("YAxis-1").Maximum = l_nRange / 1000.0 / 2.0;
//				m_graph[i].Axes.Item("YAxis-1").Minimum = -l_nRange / 1000.0 / 2.0;
//			}
//		}
//		else if ((l_nChannel > 0) && (l_nChannel <= 8))
//		{
//			m_graph[l_nChannel - 1].Axes.Item("YAxis-1").Maximum = l_nRange / 1000.0 / 2.0;
//			m_graph[l_nChannel - 1].Axes.Item("YAxis-1").Minimum = -l_nRange / 1000.0 / 2.0;
//		}
//
//		//if(m_CheckDelayTime < 50)
//		//{
//		//	m_CheckDelayTime = 1000;
//		//}
//
//		m_nCurrentStep = 2;
//	}
//	else if (m_FunctionName.Compare("set_audio_channel") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_SET_AUDIO;
//
//		int lpos, lendpos;
//		lpos = m_FunctionParameter.Find(",");
//
//		CString str1 = m_FunctionParameter.Left(lpos);
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
//
//		m_nChannel = _ttoi(str1);
//		m_nSource = _ttoi(str2);
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if ((m_FunctionName.Compare("check_audio_range") == 0) || (m_FunctionName.Compare("check_audio") == 0))
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO;
//		int lpos, lendpos;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_nChannel = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMin = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpFrequencyMax = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageMin = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageMax = _ttoi(str1);
//
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		m_TmpVoltageBalnce = _ttoi(str1);
//
//		if ((m_TmpVoltageBalnce > 95) || (m_TmpVoltageBalnce < 5))
//		{
//
//			m_TmpVoltageBalnce = 0;
//
//		}
//
//
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//
//	}
//	else if (m_FunctionName.Compare("check_balance") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_RL_BALANCE;
//		int lpos, lendpos;
//
//		//		int m_nBalanceEnable[8];
//		//int m_nBalanceChannel[8];
//		//int m_nBalanceValue[8];
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		int l_nBalance = _ttoi(str1);
//		if ((l_nBalance > 0) && (l_nBalance <= 8))
//		{
//			int lIndex = l_nBalance - 1;//Zero base
//			m_nBalanceEnable[lIndex] = 1;
//
//			m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//			lpos = m_FunctionParameter.Find(",");
//			str1 = m_FunctionParameter.Left(lpos);
//
//			m_nBalanceChannel[lIndex] = _ttoi(str1);
//			if ((m_nBalanceChannel[lIndex] > 0) && (m_nBalanceChannel[lIndex] <= 8))
//			{
//				m_nBalanceChannel[lIndex] = m_nBalanceChannel[lIndex] - 1;
//			}
//			else
//			{
//				m_nBalanceEnable[l_nBalance] = 0;
//			}
//
//
//			m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//			//m_FunctionParameter.Mid(lpos+1);
//		//	lpos = m_FunctionParameter.Find(",");
//			str1 = m_FunctionParameter;//.Left(lpos);
//			m_nBalanceValue[lIndex] = _ttoi(str1);
//
//
//
//			if (m_nBalanceValue[lIndex] < 0)
//			{
//				m_nBalanceValue[lIndex] = 0;
//				m_nBalanceEnable[lIndex] = 0;
//			}
//
//			if (m_CheckDelayTime < 50)
//			{
//				m_CheckDelayTime = 1000;
//			}
//		}
//		m_nCurrentStep = 2;
//
//	}
//	else if (m_FunctionName.Compare("check_audio_work") == 0)
//	{
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO_WORK;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//
//		InitChannel();
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("check_lan") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_LAN;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("check_usb1") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_USB1;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("check_usb2") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_TEST_USB2;
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("check_camera_ocr") == 0)
//	{
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_OCR;
//
//		int lpos, lendpos;
//		/*	lpos = m_FunctionParameter.Find("\"");
//			lendpos = m_FunctionParameter.Find("\"");
//			m_strCameraCheckChar = lFunctionString.Mid(lpos+1,lendpos);*/
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strCameraCheckIMGfile = strtemp;
//		if (m_CheckDelayTime < 50)
//		{
//			m_CheckDelayTime = 1000;
//		}
//
//	}
//	else if (m_FunctionName.Compare("check_camera_image") == 0)
//	{
//		m_Camera_CheckOK = 3;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE;
//
//		lpos = m_FunctionParameter.Find("\"");
//		CString strtemp = m_FunctionParameter.Mid(lpos + 1);
//		lendpos = strtemp.Find("\"");
//
//		strtemp = strtemp.Left(lendpos);
//		m_strCameraCheckIMGfile = strtemp;
//		//check_camera_image("check_sum.jpg",85,3000 )
//
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		m_Match_Percent = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		//lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter;//.Left(lpos);
//		m_CheckDelayTime = _ttoi(str1);
//		//	m_Match_Percent
//			//lpos = m_FunctionParameter.Find("\"");
//			//lendpos = m_FunctionParameter.Find("\"");
//			//m_strCameraCheckIMGfile = lFunctionString.Mid(lpos+1,lendpos);	
//		if ((m_Match_Percent < 50) || (m_Match_Percent > 95))
//			m_Match_Percent = 85;
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//	}
//	else if (m_FunctionName.Compare("uartcheck") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
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
//		for (int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if (lpos >= 0)
//			{
//				//	str1.Find("0/X");
//
//				m_UartCommand[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos + 4);
//
//				m_UartCommandCnt = i + 1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//		//		unsigned char m_UartCommand[50];
//		//int m_UartCommandCnt;
//		//unsigned char m_UartOkAckData[50];
//		//int m_UartOkAckDataCnt;
//			//m_UartCommand = _ttoi(str1);
//
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		str2 = str1;
//
//		str2.MakeUpper();
//		for (int i = 0; i < 50; i++)
//		{
//			lpos = str2.Find("0X");
//			if (lpos >= 0)
//			{
//
//				m_UartOkAckData[i] = lFile.ReadHex(str2);
//				str2 = str2.Mid(lpos + 4);
//				m_UartOkAckDataCnt = i + 1;
//			}
//			else
//			{
//				break;
//			}
//		}
//
//		//	m_UartOkAckData = lFile.ReadHex(str1);
//		lpos = m_FunctionParameter.Find(",");
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		//m_FunctionParameter.Mid(lpos+1);
//		lpos = m_FunctionParameter.Find(",");
//		///str1 = m_FunctionParameter.Mid(lpos+1);		
//
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 
//
//
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		UartCommandPcbSend();
//		m_PCB_CheckOK = 0;
//
//		//m_UartCommand();
//	}
//	else if (m_FunctionName.Compare("checksum") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_SUM_COMMAND;
//
//	
//		m_UartCommand[0] = 0x2D;
//		m_UartCommandCnt = 1;
//		if (gTestSeqData.CheckSum[2] == 0)
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
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		UartCommandPcbSend();
//		m_PCB_CheckOK = 0;
//
//		//m_UartCommand();
//	}
//	else if (m_FunctionName.Compare("wifimac") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
//	{
//	CFileControl lFile;
//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//	m_FunctionType = TEST_SEQ_TYPE_CHECK_SUM_COMMAND;
//
//
//	m_UartCommand[0] = _COMMAND_WIFI_MAC_READ;
//	m_UartCommandCnt = 1;
//	//if (gTestSeqData.CheckSum[2] == 0)
//	//{
//	//	m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
//	//	m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
//	//	m_UartOkAckDataCnt = 2;
//	//}
//	//else
//	//{
//	//	m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
//	//	m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
//	//	m_UartOkAckData[2] = gTestSeqData.CheckSum[2];
//	//	m_UartOkAckData[3] = gTestSeqData.CheckSum[3];
//	//	m_UartOkAckDataCnt = 4;
//	//}
//	m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 
//
//
//
//	if (m_CheckDelayTime <= 30)
//	{
//		m_CheckDelayTime = 1000;
//	}
//	UartCommandPcbSend();
//	m_PCB_CheckOK = 0;
//
//	//m_UartCommand();
//	}
//	else if (m_FunctionName.Compare("check_led") == 0)// check_led(4,4,4,4,1000 )
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_LED;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		int lledcnt = _ttoi(str1);
//		if (lledcnt == 1)
//			m_LEDOkAckData[0] = 0xF1;
//		else if (lledcnt == 2)
//			m_LEDOkAckData[0] = 0xF3;
//		else if (lledcnt == 3)
//			m_LEDOkAckData[0] = 0xF7;
//		else if (lledcnt == 4)
//			m_LEDOkAckData[0] = 0xFF;
//		else
//			m_LEDOkAckData[0] = 0xF0;
//		//m_UartCommand = _ttoi(str1);
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		lledcnt = _ttoi(str1);
//		if (lledcnt == 1)
//			m_LEDOkAckData[1] = 0xF1;
//		else if (lledcnt == 2)
//			m_LEDOkAckData[1] = 0xF3;
//		else if (lledcnt == 3)
//			m_LEDOkAckData[1] = 0xF7;
//		else if (lledcnt == 4)
//			m_LEDOkAckData[1] = 0xFF;
//		else
//			m_LEDOkAckData[1] = 0xF0;
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		lledcnt = _ttoi(str1);
//		if (lledcnt == 1)
//			m_LEDOkAckData[2] = 0xF1;
//		else if (lledcnt == 2)
//			m_LEDOkAckData[2] = 0xF3;
//		else if (lledcnt == 3)
//			m_LEDOkAckData[2] = 0xF7;
//		else if (lledcnt == 4)
//			m_LEDOkAckData[2] = 0xFF;
//		else
//			m_LEDOkAckData[2] = 0xF0;
//
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//		lpos = m_FunctionParameter.Find(",");
//		str1 = m_FunctionParameter.Left(lpos);
//		lledcnt = _ttoi(str1);
//		if (lledcnt == 1)
//			m_LEDOkAckData[3] = 0xF1;
//		else if (lledcnt == 2)
//			m_LEDOkAckData[3] = 0xF3;
//		else if (lledcnt == 3)
//			m_LEDOkAckData[3] = 0xF7;
//		else if (lledcnt == 4)
//			m_LEDOkAckData[3] = 0xFF;
//		else
//			m_LEDOkAckData[3] = 0xF0;
//
//
//		m_FunctionParameter = m_FunctionParameter.Mid(lpos + 1);
//
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		LEDReadSend();
//		m_LED_CheckOK = 0;
//		//m_UartCommand();
//	}
//	else if (m_FunctionName.Compare("clear_led") == 0)// check_led(4,4,4,4,1000 )
//	{
//		CFileControl lFile;
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CLEAR_LED;
//
//
//
//		m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		LEDClearSend();
//		//	m_LED_CheckOK = 0;
//			//m_UartCommand();
//	}
//	else if (m_FunctionName.Compare("check_fan") == 0)// check_fan(1,1000 )
//	{
//		CFileControl lFile;
//
//
//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
//		m_FunctionType = TEST_SEQ_TYPE_CHECK_FAN;
//
//		lpos = m_FunctionParameter.Find(",");
//		CString str1 = m_FunctionParameter.Left(lpos);
//		int l_FanDiPort = _ttoi(str1);
//
//		//if((l_FanDiPort > 0)&&(l_FanDiPort <= 4))
//		//{
//		//	m_FanDiPort = l_FanDiPort - 1;
//		//}
//		//else
//		{
//			m_FanDiPort = 0;
//		}
//		m_LED_Up_DI_ReadData[m_FanDiPort] = 0;
//
//
//		CString str2 = m_FunctionParameter.Mid(lpos + 1);
//		m_CheckDelayTime = _ttoi(str2);//check_led(4,4,4,4,1000 )		
//
//		if (m_CheckDelayTime <= 30)
//		{
//			m_CheckDelayTime = 1000;
//		}
//		LEDClearSend();
//		//	m_LED_CheckOK = 0;
//			//m_UartCommand();
//	}
//	else if ((m_FunctionName.Compare("set_mic") == 0) || (m_FunctionName.Compare("set_mic1") == 0))
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
//	else if (m_FunctionName.Compare("set_mic2") == 0)
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
//	m_OKcnt = 0;
//	SetTimeCheck(1);
//}


int CAcqVoltageSamples_IntClkDlg::SetFunction(CString lString, int lStringIn)
{
	CString lFunctionString;
	int lFileError = 0;
	
	m_FunctionType = TEST_SEQ_TYPE_END;

	if (lStringIn == 1)
	{
		lFunctionString = lString;
	}
	else
	{

		lFunctionString = gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
		if (gTestSeqData.TestStepList[m_nCurrentNumber].nCount < 1)
		{
			m_nCurrentStep = 2;
			return 0;
		}
		
		

	}
	int lpos, lendpos;
	lpos = lFunctionString.Find("(");
	lendpos = lFunctionString.Find(")");
	lFunctionString = lFunctionString.Left(lendpos);
	m_FunctionName = lFunctionString.Left(lpos);
	m_FunctionName = m_FunctionName.MakeLower();
	m_FunctionParameter = lFunctionString.Mid(lpos+1);

	if(m_FunctionName.Compare("delay") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_DELAY;
		m_CheckDelayTime = _ttoi(m_FunctionParameter);
		if(m_CheckDelayTime < 0)
		{
			m_CheckDelayTime = 1000;
		}
	}//TEST_SEQ_TYPE_BEEP
	else if(m_FunctionName.Compare("beep") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_BEEP;

		int lpos, lendpos;
		DWORD lFreq,lDelay;


		lpos = m_FunctionParameter.Find(",");	

		CString str1 = m_FunctionParameter.Left(lpos);
		CString str2 = m_FunctionParameter.Mid(lpos+1);
		//
		//lFreq = _ttoi(str1);
		lDelay = _ttoi(str2);
		//if(lFreq > 2000)
		//{
		//	lFreq = 800;
		//}
		//if(lDelay > 5000)
		//{
		//	lDelay = 300;
		//}
		//Beep(1200, 1000);
		if (lStringIn == 0)
		{
			mpDlgSimpleInform->m_DisplayString = str1;
			mpDlgSimpleInform->m_Count = lDelay;
			CRect rectP;
			CRect rect;

			this->GetWindowRect(&rectP);
			mpDlgSimpleInform->GetWindowRect(&rect);

			mpDlgSimpleInform->ShowWindow(SW_SHOW);
			mpDlgSimpleInform->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
			//mpDlgSimpleInform->ShowWindow(SW_SHOW);

			CString m_NgWaveFile = _T(PATH_BASE_DIR);
			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
			sndPlaySound(m_NgWaveFile, SND_ASYNC);

			m_nCurrentStep = 2;
		}
	}
	else if (m_FunctionName.Compare("usermessage") == 0)
	{
		CString str1;
		CString str2;
		CString str3;
		CString str4;


		m_FunctionType = TEST_SEQ_TYPE_USER_MASSAGE;

		m_LED_Up_DI_ReadData[1] = 0;
		m_LED_Up_DI_ReadData[2] = 0;

		int lpos, lendpos;
		DWORD lFreq, lDelay;

		lpos = m_FunctionParameter.Find(",");

		str1 = m_FunctionParameter.Left(lpos);
		str2 = m_FunctionParameter.Mid(lpos + 1);

		str1.Trim();
		str1.TrimLeft("\"");
		str1.TrimRight("\"");

		lpos = str2.Find(",");
		if (lpos > 0)
		{
			str3 = str2.Left(lpos);
			str4 = str2.Mid(lpos + 1);
			str3.Trim();
			str3.TrimLeft("\"");
			str3.TrimRight("\"");

			lDelay = _ttoi(str4);
			m_pUserMsgDlg->SetMessageTime(str1, str3, lDelay);
		}
		else
		{
			str2.Trim();
			str2.TrimLeft("\"");
			str2.TrimRight("\"");

			lDelay = _ttoi(str2);
			m_pUserMsgDlg->SetMessageTime(str1, "", lDelay);
		}
		m_pUserMsgDlg->m_bShowOkButton = 0;
		m_pUserMsgDlg->m_Close_Result = _OPEN_DISPLAY_;
		if (lStringIn == 0)
		{
			CRect rectP;
			CRect rect;
			this->GetWindowRect(&rectP);
			m_pUserMsgDlg->GetWindowRect(&rect);

			m_pUserMsgDlg->ShowWindow(SW_SHOW);
			m_pUserMsgDlg->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);


			CString m_NgWaveFile = _T(PATH_BASE_DIR);
			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
			sndPlaySound(m_NgWaveFile, SND_ASYNC);
		}



		//BOOL _NotifyMessage()
		//{
		//
		//	CString sMsg1;
		//	CString sMsg2;
		//	BOOL    bRetrun = TRUE;
		//
		//	pos = pCurFunc->m_ArgumentList.GetHeadPosition();
		//	if (pos!= NULL)
		//	{
		//        sMsg1 = GetString();
		//        sMsg2 = GetString();
		//
		//		g_pView->m_UserMsgDlg.SetMessage(sMsg1,sMsg2);
		//		g_pView->m_UserMsgDlg.DoModal();
		//
		//		bRetrun = g_pView->m_UserMsgDlg.m_bYes;
		//	
		//	}
		//
		//	if(!bRetrun) CurrentSet->bRunAbort = TRUE;
		////090408
		////	return bRetrun;
		//	return TRUE;
		//}

	}
	else if(m_FunctionName.Compare("manual_check") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_MANUAL_CHECK;

		m_LED_Up_DI_ReadData[1] = 0;
		m_LED_Up_DI_ReadData[2] = 0;

		int lpos, lendpos;
		DWORD lFreq,lDelay;


		lpos = m_FunctionParameter.Find(",");	

		CString str1 = m_FunctionParameter.Left(lpos);
		CString str2 = m_FunctionParameter.Mid(lpos+1);
		//
		//lFreq = _ttoi(str1);
		lDelay = _ttoi(str2);
		//if(lFreq > 2000)
		//{
		//	lFreq = 800;
		//}
		//if(lDelay > 5000)
		//{
		//	lDelay = 300;
		//}
		//Beep(1200, 1000);

		if (lStringIn == 0)
		{
			mpDlgSimpleInform->m_DisplayString = str1;
			mpDlgSimpleInform->m_Count = lDelay;
			CRect rectP;
			CRect rect;

			this->GetWindowRect(&rectP);
			mpDlgSimpleInform->GetWindowRect(&rect);

			mpDlgSimpleInform->m_Close_Result = _OPEN_DISPLAY_;
			mpDlgSimpleInform->ShowWindow(SW_SHOW);
			mpDlgSimpleInform->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);
			//mpDlgSimpleInform->ShowWindow(SW_SHOW);

			CString m_NgWaveFile = _T(PATH_BASE_DIR);
			m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
			sndPlaySound(m_NgWaveFile, SND_ASYNC);
		}
		
		//m_nCurrentStep = 2;
	}
	else if (m_FunctionName.Compare("waitmessage") == 0)// waitmessage("ARC SPK Out Test" ,"" )
	{
	m_FunctionType = TEST_SEQ_TYPE_WAIT_MASSAGE;

	m_LED_Up_DI_ReadData[1] = 0;
	m_LED_Up_DI_ReadData[2] = 0;

	int lpos, lendpos;
	DWORD lFreq, lDelay;

	CString str1 ;
	CString str2 ;
	lpos = m_FunctionParameter.Find(",");
	if (lpos > 0)
	{
		str1 = m_FunctionParameter.Left(lpos);
		str2 = m_FunctionParameter.Mid(lpos + 1);
	}
	else
	{
		str1 = m_FunctionParameter;
		str2 = "";

	}
	//

	str1.Trim();
	str1.TrimLeft("\"");
	str1.TrimRight("\"");

	str2.Trim();
	str2.TrimLeft("\"");
	str2.TrimRight("\"");


	CRect rectP;
	CRect rect;


	m_pUserMsgDlg->SetMessage(str1, str2);
	m_pUserMsgDlg->m_bShowOkButton = 1;
	m_pUserMsgDlg->m_Close_Result = _OPEN_DISPLAY_;

	this->GetWindowRect(&rectP);
	m_pUserMsgDlg->GetWindowRect(&rect);

	m_pUserMsgDlg->ShowWindow(SW_SHOW);
	m_pUserMsgDlg->SetWindowPos(this, rectP.left + 300, rectP.top + 350, rect.Width(), rect.Height(), SWP_ASYNCWINDOWPOS);


	CString m_NgWaveFile = _T(PATH_BASE_DIR);
	m_NgWaveFile += _T("\\Sound\\MANUAL.wav");//OK_CHECK.wav
	sndPlaySound(m_NgWaveFile, SND_ASYNC);


	}
	else if((m_FunctionName.Compare("remocon_out") == 0)||(m_FunctionName.Compare("remocon_out1") == 0))
	{
		m_FunctionType = TEST_SEQ_TYPE_MP_KEY;
		int lpos, lendpos;
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strMP_Key = strtemp;


		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("remocon_out2") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_PRE_KEY;
		int lpos, lendpos;
	/*	lpos = m_FunctionParameter.Find("\"");
		lendpos = m_FunctionParameter.Find("\"");

		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);
		m_strMP_Key = strtemp;*/
		
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strMP_Key = strtemp;
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("remocon_repeat") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT_KEY;
		int lpos, lendpos;
		/*lpos = m_FunctionParameter.Find("\"");
		lendpos = m_FunctionParameter.Find("\"");

		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strMP_Key = strtemp;
		//////////////////////////////////////////////////
		m_FunctionParameter = m_FunctionParameter.Mid(lendpos+1);
		lpos = m_FunctionParameter.Find(",");
		strtemp = m_FunctionParameter.Left(lpos);
		m_RepeatCount = _ttoi(strtemp);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		m_FunctionParameter.Mid(lpos+1);
	//	lpos = m_FunctionParameter.Find(",");
	
		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
		m_CheckDelayTime = _ttoi(strtemp);

		////////////////////////////////////////////////
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}	

	else if(m_FunctionName.Compare("remocon_repeat10") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_MP_REPEAT10_KEY;
		int lpos, lendpos;
		/*lpos = m_FunctionParameter.Find("\"");
		lendpos = m_FunctionParameter.Find("\"");

		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strMP_Key = strtemp;
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("remocon_repeat2") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_PRE_REPEAT_KEY;
		int lpos, lendpos;
		/*lpos = m_FunctionParameter.Find("\"");
		lendpos = m_FunctionParameter.Find("\"");

		CString strtemp = m_FunctionParameter.Mid(lpos+1,lendpos);*/
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strMP_Key = strtemp;
		//////////////////////////////////////////////////
		m_FunctionParameter = m_FunctionParameter.Mid(lendpos+1);
		lpos = m_FunctionParameter.Find(",");
		strtemp = m_FunctionParameter.Left(lpos);
		m_RepeatCount = _ttoi(strtemp);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		m_FunctionParameter.Mid(lpos+1);
	//	lpos = m_FunctionParameter.Find(",");
	
		strtemp = m_FunctionParameter;//	str1 = m_FunctionParameter.Left(lpos);
		m_CheckDelayTime = _ttoi(strtemp);

		////////////////////////////////////////////////
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("set_audio_display") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_SET_DISPLAY;

		int lpos, lendpos;
		lpos = m_FunctionParameter.Find(",");	

		CString str1 = m_FunctionParameter.Left(lpos);
		CString str2 = m_FunctionParameter.Mid(lpos+1);
		
		int l_nChannel = _ttoi(str1);
		int l_nRange = _ttoi(str2);

		if(l_nChannel > 8)
		{
			for(int i = 0; i < 8; i++)
			{
				
				m_graph[i].Axes.Item("YAxis-1").Maximum = l_nRange/1000.0/2.0;
				m_graph[i].Axes.Item("YAxis-1").Minimum = -l_nRange/1000.0/2.0;
			}
		}
		else if((l_nChannel > 0)&&(l_nChannel <= 8))
		{
			m_graph[l_nChannel-1].Axes.Item("YAxis-1").Maximum = l_nRange/1000.0/2.0;
			m_graph[l_nChannel-1].Axes.Item("YAxis-1").Minimum = -l_nRange/1000.0/2.0;
		}

		//if(m_CheckDelayTime < 50)
		//{
		//	m_CheckDelayTime = 1000;
		//}

		m_nCurrentStep = 2;
	}
	else if(m_FunctionName.Compare("set_audio_channel") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_SET_AUDIO;

		int lpos, lendpos;
		lpos = m_FunctionParameter.Find(",");	

		CString str1 = m_FunctionParameter.Left(lpos);
		CString str2 = m_FunctionParameter.Mid(lpos+1);
		
		m_nChannel = _ttoi(str1);
		m_nSource = _ttoi(str2);
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if((m_FunctionName.Compare("check_audio_range") == 0)||(m_FunctionName.Compare("check_audio") == 0))
	{
		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO;
		int lpos, lendpos;

		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		m_nChannel = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		m_TmpFrequencyMin = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		m_TmpFrequencyMax = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		m_TmpVoltageMin = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		m_TmpVoltageMax = _ttoi(str1);

		
		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		//m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		m_TmpVoltageBalnce = _ttoi(str1);

		if((m_TmpVoltageBalnce > 95)||(m_TmpVoltageBalnce < 5))
		{

			m_TmpVoltageBalnce = 0;

		}


		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}

	}
	else if(m_FunctionName.Compare("check_balance") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_CHECK_RL_BALANCE;
		int lpos, lendpos;

	//		int m_nBalanceEnable[8];
	//int m_nBalanceChannel[8];
	//int m_nBalanceValue[8];

		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		int l_nBalance = _ttoi(str1);
		if((l_nBalance > 0)&&(l_nBalance <= 8))
		{
			int lIndex = l_nBalance - 1;//Zero base
			m_nBalanceEnable[lIndex] = 1;

			m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
			lpos = m_FunctionParameter.Find(",");
			str1 = m_FunctionParameter.Left(lpos);
			
			m_nBalanceChannel[lIndex] = _ttoi(str1);
			if((m_nBalanceChannel[lIndex] > 0)&&(m_nBalanceChannel[lIndex] <= 8))
			{
				m_nBalanceChannel[lIndex] = m_nBalanceChannel[lIndex] - 1;
			}
			else
			{
				m_nBalanceEnable[l_nBalance] = 0;
			}
				

			m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
			//m_FunctionParameter.Mid(lpos+1);
		//	lpos = m_FunctionParameter.Find(",");
			str1 = m_FunctionParameter;//.Left(lpos);
			m_nBalanceValue[lIndex] = _ttoi(str1);

			

			if(m_nBalanceValue[lIndex] < 0)
			{
				m_nBalanceValue[lIndex] = 0;
				m_nBalanceEnable[lIndex] = 0;
			}

			if(m_CheckDelayTime < 50)
			{
				m_CheckDelayTime = 1000;
			}
		}
			m_nCurrentStep = 2;

	}
	else if(m_FunctionName.Compare("check_audio_work") == 0)
	{
		m_FunctionType = TEST_SEQ_TYPE_CHECK_AUDIO_WORK;
		m_CheckDelayTime = _ttoi(m_FunctionParameter);
		if (lStringIn == 0)
		InitChannel();	
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("check_lan") == 0)
	{
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_TEST_LAN;
		m_CheckDelayTime = _ttoi(m_FunctionParameter);
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("check_usb1") == 0)
	{
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_TEST_USB1;
		m_CheckDelayTime = _ttoi(m_FunctionParameter);
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("check_usb2") == 0)
	{
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_TEST_USB2;
		m_CheckDelayTime = _ttoi(m_FunctionParameter);
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("check_camera_ocr") == 0)
	{
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_OCR;	

		int lpos, lendpos;
	/*	lpos = m_FunctionParameter.Find("\"");
		lendpos = m_FunctionParameter.Find("\"");
		m_strCameraCheckChar = lFunctionString.Mid(lpos+1,lendpos);*/
		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strCameraCheckIMGfile = strtemp;
		if(m_CheckDelayTime < 50)
		{
			m_CheckDelayTime = 1000;
		}

	}
	else if(m_FunctionName.Compare("check_camera_image") == 0)
	{
		m_Camera_CheckOK = 3;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE;

		lpos = m_FunctionParameter.Find("\"");
		CString strtemp = m_FunctionParameter.Mid(lpos+1);
		lendpos = strtemp.Find("\"");

		strtemp = strtemp.Left(lendpos);
		m_strCameraCheckIMGfile = strtemp;
		//check_camera_image("check_sum.jpg",85,3000 )

		lpos = m_FunctionParameter.Find(",");
		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		m_Match_Percent = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		//lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter;//.Left(lpos);
		m_CheckDelayTime = _ttoi(str1);
	//	m_Match_Percent
		//lpos = m_FunctionParameter.Find("\"");
		//lendpos = m_FunctionParameter.Find("\"");
		//m_strCameraCheckIMGfile = lFunctionString.Mid(lpos+1,lendpos);	
		if((m_Match_Percent < 50) || (m_Match_Percent > 95))
			m_Match_Percent = 85;
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
	}
	else if(m_FunctionName.Compare("uartcheck") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
	{
		CFileControl lFile;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_UART_COMMAND;

		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		str1.MakeUpper();
		CString str2;
		str2 = str1;

		for(int i = 0; i < 50; i++)
		{
			lpos = str2.Find("0X");
			if(lpos  >= 0)
			{
			//	str1.Find("0/X");
				
				m_UartCommand[i] = lFile.ReadHex(str2);
				str2 = str2.Mid(lpos+4);

				m_UartCommandCnt = i+1;
			}
			else
			{
				break;
			}
		}

	//		unsigned char m_UartCommand[50];
	//int m_UartCommandCnt;
	//unsigned char m_UartOkAckData[50];
	//int m_UartOkAckDataCnt;
		//m_UartCommand = _ttoi(str1);

		lpos = m_FunctionParameter.Find(",");
		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		str2 = str1;

		str2.MakeUpper();
		for(int i = 0; i < 50; i++)
		{
			lpos = str2.Find("0X");
			if(lpos  >= 0)
			{			
				
				m_UartOkAckData[i] = lFile.ReadHex(str2);
				str2 = str2.Mid(lpos+4);
				m_UartOkAckDataCnt = i+1;
			}
			else
			{
				break;
			}
		}

	//	m_UartOkAckData = lFile.ReadHex(str1);
		lpos = m_FunctionParameter.Find(",");
		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		//m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		///str1 = m_FunctionParameter.Mid(lpos+1);		

		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 

		
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
		UartCommandPcbSend();
		m_PCB_CheckOK = 0;

		//m_UartCommand();
	}	
	else if(m_FunctionName.Compare("checksum") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
	{
		CFileControl lFile;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_SUM_COMMAND;

		//lpos = m_FunctionParameter.Find(",");
		//CString str1 = m_FunctionParameter.Left(lpos);
		//str1.MakeUpper();
		//CString str2;
		//str2 = str1;

		//for(int i = 0; i < 50; i++)
		//{
		//	lpos = str2.Find("0X");
		//	if(lpos  >= 0)
		//	{
		//	//	str1.Find("0/X");
		//		
		//		m_UartCommand[i] = lFile.ReadHex(str2);
		//		str2 = str2.Mid(lpos+4);

		//		m_UartCommandCnt = i+1;
		//	}
		//	else
		//	{
		//		break;
		//	}
		//}

	//		unsigned char m_UartCommand[50];
	//int m_UartCommandCnt;
	//unsigned char m_UartOkAckData[50];
	//int m_UartOkAckDataCnt;
		//m_UartCommand = _ttoi(str1);

	//	lpos = m_FunctionParameter.Find(",");
	//	m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
	//	lpos = m_FunctionParameter.Find(",");
	//	str1 = m_FunctionParameter.Left(lpos);
	//	str2 = str1;

	//	str2.MakeUpper();
	//	for(int i = 0; i < 50; i++)
	//	{
	//		lpos = str2.Find("0X");
	//		if(lpos  >= 0)
	//		{			
	//			
	//			m_UartOkAckData[i] = lFile.ReadHex(str2);
	//			str2 = str2.Mid(lpos+4);
	//			m_UartOkAckDataCnt = i+1;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}

	////	m_UartOkAckData = lFile.ReadHex(str1);
	//	lpos = m_FunctionParameter.Find(",");
	//	m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
	//	//m_FunctionParameter.Mid(lpos+1);
	//	lpos = m_FunctionParameter.Find(",");
	//	///str1 = m_FunctionParameter.Mid(lpos+1);		
		m_UartCommand[0] = 0x2D;
		m_UartCommandCnt = 1;
		if (gTestSeqData.CheckSum[2] == 0)
		{
			m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
			m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
			m_UartOkAckDataCnt = 2;
		}
		else
		{
			m_UartOkAckData[0] = gTestSeqData.CheckSum[0];
			m_UartOkAckData[1] = gTestSeqData.CheckSum[1];
			m_UartOkAckData[2] = gTestSeqData.CheckSum[2];
			m_UartOkAckData[3] = gTestSeqData.CheckSum[3];
			m_UartOkAckDataCnt = 4;
		}
		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 

		
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
		UartCommandPcbSend();
		m_PCB_CheckOK = 0;

		//m_UartCommand();
	}	
	else if (m_FunctionName.Compare("wifi_mac_read") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
	{
		CFileControl lFile;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_WIFI_MAC_READ;


		m_UartCommand[0] = _COMMAND_WIFI_MAC_READ;
		m_UartCommandCnt = 1;

		m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 



		if (m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
			UartCommandPcbSend();
		m_PCB_CheckOK = 0;

		//m_UartCommand();
	}
	else if (m_FunctionName.Compare("bt_mac_read") == 0)//uartcheck(0x81 ,0x01 ,3000 ) 
	{
	CFileControl lFile;
	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
	m_FunctionType = TEST_SEQ_TYPE_BT_MAC_READ;


	m_UartCommand[0] = _COMMAND_BT_MAC_READ;
	m_UartCommandCnt = 1;

	m_CheckDelayTime = _ttoi(m_FunctionParameter);//uartcheck(0x81 ,0x01 ,3000 ) 



	if (m_CheckDelayTime <= 30)
	{
		m_CheckDelayTime = 1000;
	}
	if (lStringIn == 0)
		UartCommandPcbSend();
	m_PCB_CheckOK = 0;

	//m_UartCommand();
	}
	else if(m_FunctionName.Compare("check_led") == 0)// check_led(4,4,4,4,1000 )
	{
		CFileControl lFile;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_LED;

		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		int lledcnt =   _ttoi(str1);
		if(lledcnt == 1)
			m_LEDOkAckData[0] = 0xF1;
		else if(lledcnt == 2)
			m_LEDOkAckData[0] = 0xF3;
		else if(lledcnt == 3)
			m_LEDOkAckData[0] = 0xF7;
		else if(lledcnt == 4)
			m_LEDOkAckData[0] = 0xFF;
		else
			m_LEDOkAckData[0] = 0xF0;
		//m_UartCommand = _ttoi(str1);

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		lledcnt =   _ttoi(str1);
		if(lledcnt == 1)
			m_LEDOkAckData[1] = 0xF1;
		else if(lledcnt == 2)
			m_LEDOkAckData[1] = 0xF3;
		else if(lledcnt == 3)
			m_LEDOkAckData[1] = 0xF7;
		else if(lledcnt == 4)
			m_LEDOkAckData[1] = 0xFF;
		else
			m_LEDOkAckData[1] = 0xF0;

		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		lledcnt =   _ttoi(str1);
		if(lledcnt == 1)
			m_LEDOkAckData[2] = 0xF1;
		else if(lledcnt == 2)
			m_LEDOkAckData[2] = 0xF3;
		else if(lledcnt == 3)
			m_LEDOkAckData[2] = 0xF7;
		else if(lledcnt == 4)
			m_LEDOkAckData[2] = 0xFF;
		else
			m_LEDOkAckData[2] = 0xF0;


		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
		lpos = m_FunctionParameter.Find(",");
		str1 = m_FunctionParameter.Left(lpos);
		lledcnt =   _ttoi(str1);
		if(lledcnt == 1)
			m_LEDOkAckData[3] = 0xF1;
		else if(lledcnt == 2)
			m_LEDOkAckData[3] = 0xF3;
		else if(lledcnt == 3)
			m_LEDOkAckData[3] = 0xF7;
		else if(lledcnt == 4)
			m_LEDOkAckData[3] = 0xFF;
		else
			m_LEDOkAckData[3] = 0xF0;


		m_FunctionParameter = m_FunctionParameter.Mid(lpos+1);
	
		m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
		LEDReadSend();
		m_LED_CheckOK = 0;
		//m_UartCommand();
	}
	else if(m_FunctionName.Compare("clear_led") == 0)// check_led(4,4,4,4,1000 )
	{
		CFileControl lFile;
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CLEAR_LED;

		
	
		m_CheckDelayTime = _ttoi(m_FunctionParameter);//check_led(4,4,4,4,1000 )		
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
		LEDClearSend();
	//	m_LED_CheckOK = 0;
		//m_UartCommand();
	}	
	else if(m_FunctionName.Compare("check_fan") == 0)// check_fan(1,1000 )
	{
		CFileControl lFile;

		
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_CHECK_FAN;

		lpos = m_FunctionParameter.Find(",");
		CString str1 = m_FunctionParameter.Left(lpos);
		int l_FanDiPort =   _ttoi(str1);

		//if((l_FanDiPort > 0)&&(l_FanDiPort <= 4))
		//{
		//	m_FanDiPort = l_FanDiPort - 1;
		//}
		//else
		{
			m_FanDiPort = 0;
		}
		m_LED_Up_DI_ReadData[m_FanDiPort] = 0;


		CString str2 = m_FunctionParameter.Mid(lpos+1);
		m_CheckDelayTime = _ttoi(str2);//check_led(4,4,4,4,1000 )		
		
		if(m_CheckDelayTime <= 30)
		{
			m_CheckDelayTime = 1000;
		}
		if (lStringIn == 0)
		LEDClearSend();
	//	m_LED_CheckOK = 0;
		//m_UartCommand();
	}
	else if((m_FunctionName.Compare("set_mic") == 0) || (m_FunctionName.Compare("set_mic1") == 0))
	{
		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_SET_MIC1;
		m_MIC_Status = _ttoi(m_FunctionParameter);
		
		//if(m_CheckDelayTime <= 0)
		{
			m_CheckDelayTime = 2000;
		}
	}	//set_mic
	else if(m_FunctionName.Compare("set_mic2") == 0)
	{
		//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
		m_FunctionType = TEST_SEQ_TYPE_SET_MIC2;
		m_MIC_Status = _ttoi(m_FunctionParameter);
		
		//if(m_CheckDelayTime <= 0)
		{
			m_CheckDelayTime = 2000;
		}
	}	//set_mic
	else
	{
		//Error
		CString str1;
		str1 = "Syntex Error : ";
		str1 += lString;//gTestSeqData.TestStepList[m_nCurrentNumber].FunctionCommand[m_nCurrentProcess];
		MessageDisplay(1, str1);
		if (m_TaskRun != TASK_RUN_IDLE)
		{
			MessageBox(lString, "Syntex Error");
		}


		m_TaskRun = TASK_RUN_IDLE;
		CycleTimeOn = 0;
		return 1;

	}
	m_OKcnt = 0;
	SetTimeCheck(1);
	return lFileError;

}



void CAcqVoltageSamples_IntClkDlg::RunFunction()
{
	static int sWaitCnt = 0;
	if(sWaitCnt > 0)
		sWaitCnt--;
	//if(m_TEST_Result == 0)//NG
	//{
	//	TestFinish();
	//	return;
	//}
	switch(m_FunctionType)//m_nCurrentNumber
	{
	case TEST_SEQ_TYPE_DELAY:
		if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			SetTimeCheck(1);
			m_nCurrentStep = 2;
			
		}

		break;

	case  TEST_SEQ_TYPE_MP_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
		SendIR_Code(m_strMP_Key, 0);
		m_nCurrentStep = 2;
	
		break;
		
	case  TEST_SEQ_TYPE_MP_REPEAT_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
		if(m_RepeatCount <= 5)
		{
			SendIR_Code(m_strMP_Key, 1);
		}
		else
		{
			SendIR_Code(m_strMP_Key, m_RepeatCount);
		}

		m_nCurrentStep = 2;
	
		break;
	case  TEST_SEQ_TYPE_MP_REPEAT10_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
		SendIR_Code(m_strMP_Key, 2);
		m_nCurrentStep = 2;
	
		break;

	case  TEST_SEQ_TYPE_PRE_REPEAT20_KEY:
		
		MessageDisplay(0, "TEST_SEQ_TYPE_MP_KEY!!");
		SendIR_Code(m_strMP_Key, 3);
		m_nCurrentStep = 2;
	
		break;
		
	case   TEST_SEQ_TYPE_SET_AUDIO:

		SetChannelDataSeq(m_nChannel, m_nSource);
		m_nCurrentStep = 2;

		break;

	case   TEST_SEQ_TYPE_CHECK_AUDIO:
		SetChannelDataRangeSeq(m_nChannel,m_TmpVoltageMin,m_TmpVoltageMax,m_TmpFrequencyMin,m_TmpFrequencyMax);
		m_nCurrentStep = 2;

		break;

	case   TEST_SEQ_TYPE_CHECK_AUDIO_WORK:
	//	SetChannelDataRangeSeq(m_nChannel,m_TmpVoltageMin,m_TmpVoltageMax,m_TmpFrequencyMin,m_TmpFrequencyMax);
		CheckOK();
		
		if((m_ChannelOK[0] == 1)
		&& (m_ChannelOK[1] == 1)
		&& (m_ChannelOK[2] == 1)
		&& (m_ChannelOK[3] == 1)
		&& (m_ChannelOK[4] == 1)
		&& (m_ChannelOK[5] == 1))
		{
			m_TotalOK = 1;
			m_OKcnt++;
			if(m_OKcnt > 5)
			{
				TestResultDisplay();
				gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
				m_nCurrentStep = 2;

				/*for(int i = 0; i< 6; i++)
				m_graph[i].Plots.RemoveAll();*/
				InitClearChannel();
			}
		}
		else
		{
			m_TotalOK = 0;
			m_OKcnt = 0;
		}
	

		if(GetTimeCheck(1) > m_CheckDelayTime)
		{	
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
			TestResultDisplay();
			m_nCurrentStep = 2;
			
		//if( ((m_PPVoltage[i] >= m_RefVoltageMin[i])&&(m_PPVoltage[i] <= m_RefVoltageMax[i])) )
		//if((m_Frequency[i] >= m_FrequencyMin[i]) &&	(m_Frequency[i] <= m_FrequencyMax[i]))

			CString str1, str2;
			CString strV1, strV2;
			m_GMES_ErrorName = "";
			for(int i = 0; i < 6; i++)
			{
	//			m_Deisplay_ErrorName;//
	//CString m_Deisplay_ErrorDetail
				if(m_ChannelOK[i] == 0)
				{
					if(m_FrequencyOK[i] == 0)
					{
						
						
						m_GMES_ErrorName = _T(" FREQUENCY ERROR: ");
						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
					
						m_Deisplay_ErrorName =  _T("FREQUENCY ERROR \r\n");// 频率  // 音量 // 版本// 频率 左右音量差异  // 音量 // 版本 // 命令 //检查 版本 回答
						m_Deisplay_ErrorName += _T("频率 NG ");
						
						//str1 += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
						str2.Format(_T("CH[%d] FREQ:%d[%d - %d] Hz"), i+1, (int)(m_Frequency[i]),m_FrequencyMin[i], m_FrequencyMax[i] );
						
						m_GMES_ErrorValue = str2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));
						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;
					}
					else if(m_VoltageOK[i] == 0)
					{						
						strV1 = _T("VOLUME_ERROR : ");
						m_GMES_ErrorName = _T(" VOLUME_ERROR :");
						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
						m_Deisplay_ErrorName = _T("VOLUME_ERROR \r\n");
						m_Deisplay_ErrorName += _T("音量 NG ");
						
						strV2.Format(_T("CH[%d] VOL:%d[%d - %d] mV"), i+1, (int)(m_PPVoltage[i]),(int)(m_RefVoltageMin[i]), (int)(m_RefVoltageMax[i]) );
						
						m_GMES_ErrorValue = strV2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));

						//m_Deisplay_ErrorName = m_GMES_ErrorName;
						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//m_Deisplay_ErrorName

						
					}
					else if(m_BalanceOK[i] == 0)
						{						
						//strV1 = _T("BALANCE ERROR : ");
						m_GMES_ErrorName = _T(" BALANCE ERROR: ");
						m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 频率 左右音量差异  // 音量 // 版本 // 命令 //检查 版本 回答
						m_Deisplay_ErrorName = _T("BALANCE ERROR \r\n");

					//	m_Deisplay_ErrorName += _T("左右音量差异 NG ");
						m_Deisplay_ErrorName += _T("左右音量差異 NG ");
						
						strV2.Format(_T("CH[%d] VOL:%d[%d - %d] mV"), i+1, (int)(m_PPVoltage[i]),(int)(m_PPVoltage[m_nBalanceChannel[i]]), (int)(m_RefVoltageMax[i]) );
						
						m_GMES_ErrorValue = strV2;//.Format(_T("%d Hz"), (int)(m_Frequency[i]));

						//m_Deisplay_ErrorName = m_GMES_ErrorName;
						m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//m_Deisplay_ErrorName

						
					}
					//break;
				}
				


			}

		}
		break;

	case   TEST_SEQ_TYPE_TEST_LAN:
		if(m_LAN_CheckOK == 1)
		{
			m_nCurrentStep = 2;	
			
			//m_TEST_Result = 1;
			m_cLb_Lan.put_Caption(_T("O K"));
			m_cLb_Lan.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

		//	m_cLbOkNg.put_Caption(_T("O K"));
		//	m_cLbOkNg.put_BackColor(0x0000FF00);
				
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			//m_TEST_Result = 0;
			m_cLb_Lan.put_Caption(_T("N G"));
			m_cLb_Lan.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						
		//	m_cLbOkNg.put_Caption(_T("N G"));
		//	m_cLbOkNg.put_BackColor(0x000000FF);
					
			m_nCurrentStep = 2;	
			m_GMES_ErrorName = _T("LAN_ERROR : ");
			m_Deisplay_ErrorName = _T("LAN_ERROR ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
			m_GMES_ErrorValue = _T("ERROR");
			//m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
		}
		break;	

	case   TEST_SEQ_TYPE_TEST_USB1:
		if(m_USB1_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;	
			//m_TEST_Result = 1;
			m_cLb_Usb1.put_Caption(_T("O K"));
			m_cLb_Usb1.put_BackColor(0x0000FF00);

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 0;
			m_cLb_Usb1.put_Caption(_T("N G"));
			m_cLb_Usb1.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						
			//m_cLbOkNg.put_Caption(_T("N G"));
			//m_cLbOkNg.put_BackColor(0x000000FF);	
			
			m_nCurrentStep = 2;	
			//m_GMES_ErrorName = gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
			m_GMES_ErrorName = _T("USB1_ERROR ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
						
			m_Deisplay_ErrorName = _T("USB1 ERROR \r\n");
			m_Deisplay_ErrorName += _T("USB1 检查 NG ");
		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
			m_GMES_ErrorValue = _T("ERROR");
				
			//m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
		}
		break;	

	case   TEST_SEQ_TYPE_TEST_USB2:
		if(m_USB2_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 1;
			m_cLb_Usb2.put_Caption(_T("O K"));
			m_cLb_Usb2.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 0;
			m_cLb_Usb2.put_Caption(_T("N G"));
			m_cLb_Usb2.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						
			//m_cLbOkNg.put_Caption(_T("N G"));
			//m_cLbOkNg.put_BackColor(0x000000FF);	
			
			
			m_GMES_ErrorName = _T("USB2_ERROR: ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;

			m_Deisplay_ErrorName = _T("USB2 ERROR \r\n");
			m_Deisplay_ErrorName += _T("USB2 检查 NG ");
			m_GMES_ErrorValue = _T("ERROR");

			// = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
		}
		break;	

	case   TEST_SEQ_TYPE_CHECK_CAMERA_OCR:
		m_nCurrentStep = 2;
		break;

	case   TEST_SEQ_TYPE_CHECK_CAMERA_IMAGE:
		
	//	ProcessGetImage();
		//ProcessTemplate();
		
		if(m_Camera_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;
#ifndef __IMAGE_DEBUG__		
			//m_cLb_Camera.put_Caption(_T("O K"));
#endif
			m_cLb_Camera.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;						
						
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			m_nCurrentStep = 2;
#ifndef __IMAGE_DEBUG__		
			//m_cLb_Camera.put_Caption(_T("N G"));
#endif			
			m_cLb_Camera.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;	
					
			//m_GMES_ErrorName = _T("IMAGE CHECK ERROR : ");
			//m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
			m_GMES_ErrorName = _T("IMAGE CHECK ERROR  ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
			m_GMES_ErrorValue = _T("ERROR");
		
			m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;
		}
		break;	
	case   TEST_SEQ_TYPE_CHECK_UART_COMMAND:

		
		if(m_PCB_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 1;
		//	m_cLb_Usb2.put_Caption(_T("O K"));
		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if((GetTimeCheck(1) > m_CheckDelayTime)||(m_PCB_CheckOK == 2))
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 0;
		//	m_cLb_Usb2.put_Caption(_T("N G"));
		//	m_cLb_Usb2.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						
			//m_cLbOkNg.put_Caption(_T("N G"));
			//m_cLbOkNg.put_BackColor(0x000000FF);	
			
			if(m_PCB_CheckOK == 2)
			{
				m_GMES_ErrorName = _T("USB ACK ERROR :");
				m_Deisplay_ErrorName= _T("USB ACK ERROR \r\n");// 频率  // 音量 // 版本 // 命令 //检查 版本 回答
				m_Deisplay_ErrorName += _T("USB 通信 NG ");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
				CString str;
				m_GMES_ErrorValue = "";
				for(int i = 0; i < m_UartOkAckDataCnt; i++)
				{
					m_GMES_ErrorValue += " ";
					str.Format(_T("%02X"), m_UartREADData[i]);
					m_GMES_ErrorName += str;
				}
				m_GMES_ErrorValue += "[";
				for(int i = 0; i < m_UartOkAckDataCnt; i++)
				{
					str.Format(_T("%02X "), m_UartOkAckData[i]);
				}
				m_GMES_ErrorValue += "]";
				//m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//

			}
			else
			{
				m_GMES_ErrorName = _T(" SET USB COMMAND NG ");
				m_Deisplay_ErrorName = _T("SET USB COMMAND NG \r\n");
				m_Deisplay_ErrorName += _T("SET USB 指令 NG ");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				m_GMES_ErrorValue = _T("ERROR");

				//m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
			}
			
		}
		break;	
	case   TEST_SEQ_TYPE_CHECK_SUM_COMMAND:

		
		if(m_PCB_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 1;
		//	m_cLb_Usb2.put_Caption(_T("O K"));
		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if((GetTimeCheck(1) > m_CheckDelayTime)||(m_PCB_CheckOK == 2))
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 0;
		//	m_cLb_Usb2.put_Caption(_T("N G"));
		//	m_cLb_Usb2.put_BackColor(0x000000FF);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						
			//m_cLbOkNg.put_Caption(_T("N G"));
			//m_cLbOkNg.put_BackColor(0x000000FF);	
			
			//m_GMES_ErrorName = gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
			if(m_PCB_CheckOK == 2)
			{
				m_GMES_ErrorName = _T("CHECK SUM ERROR :");
				m_Deisplay_ErrorName = _T("CHECK SUM ERROR\r\n");
				m_Deisplay_ErrorName += _T("版本 NG");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				CString str;
				for(int i = 0; i < m_UartOkAckDataCnt; i++)
				{
					m_GMES_ErrorName += " ";
					str.Format(_T("%02X"), m_UartREADData[i]);
					m_GMES_ErrorName += str;
				}
				m_GMES_ErrorName += "[";
				for(int i = 0; i < m_UartOkAckDataCnt; i++)
				{
					str.Format(_T("%02X "), m_UartOkAckData[i]);
				}
				m_GMES_ErrorName += "]";
			
			//	m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
				

			}
			else
			{
				m_GMES_ErrorName = _T("SET USB COMMAND ERROR ");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
				m_Deisplay_ErrorName = _T("SET USB COMMAND NG \r\n");
				m_Deisplay_ErrorName += _T("SET USB 指令 NG ");
				m_GMES_ErrorValue = _T("ERROR");
			//	m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
			}
		//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));
			
		}
		break;	

	case   TEST_SEQ_TYPE_WIFI_MAC_READ:


		if (m_PCB_CheckOK == 1)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 1;
		//	m_cLb_Usb2.put_Caption(_T("O K"));
		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				

		}
		else if ((GetTimeCheck(1) > m_CheckDelayTime) || (m_PCB_CheckOK == 2))
		{
			m_nCurrentStep = 2;
			
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;

			
			if (m_PCB_CheckOK == 2)
			{
				m_GMES_ErrorName = _T("Wif MAC READ ERROR :");
				m_Deisplay_ErrorName = _T("Wif MAC READ ERROR\r\n");
				m_Deisplay_ErrorName += _T("Wif MAC READ NG");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				CString str;
				

				//	m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//


			}
			else
			{
				m_GMES_ErrorName = _T("Wif MAC READ ERROR :");
				m_Deisplay_ErrorName = _T("Wif MAC READ ERROR\r\n");
				m_Deisplay_ErrorName += _T("Wif MAC READ NG");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				CString str;

				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
			}
			//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));

		}
		break;
			//m_nCurrentStep = 2;
	case   TEST_SEQ_TYPE_BT_MAC_READ:


		if (m_PCB_CheckOK == 1)
		{
			m_nCurrentStep = 2;
			//m_TEST_Result = 1;
		//	m_cLb_Usb2.put_Caption(_T("O K"));
		//	m_cLb_Usb2.put_BackColor(0x0000FF00);
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				

		}
		else if ((GetTimeCheck(1) > m_CheckDelayTime) || (m_PCB_CheckOK == 2))
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;


			if (m_PCB_CheckOK == 2)
			{
				m_GMES_ErrorName = _T("BT MAC READ ERROR :");
				m_Deisplay_ErrorName = _T("BT MAC READ ERROR\r\n");
				m_Deisplay_ErrorName += _T("BT MAC READ NG");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				CString str;


				//	m_Deisplay_ErrorName = m_GMES_ErrorName;
				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//


			}
			else
			{
				m_GMES_ErrorName = _T("BT MAC READ ERROR :");
				m_Deisplay_ErrorName = _T("BT MAC READ ERROR\r\n");
				m_Deisplay_ErrorName += _T("BT MAC READ NG");
				m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查 版本
				CString str;

				m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
			}
			//	m_GMES_ErrorValue.Format(_T("%d Hz"), (int)(m_Frequency[i]));

		}
		break;
		//m_nCurrentStep = 2;
	case   TEST_SEQ_TYPE_CHECK_LED:
		
		
		if(m_LED_CheckOK	 == 1)
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
					
			m_GMES_ErrorName = _T("LED OUT ERROR :");
			m_Deisplay_ErrorName = _T("LED OUT ERROR \r\n");
			m_Deisplay_ErrorName += _T("LED 检查 NG ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
			//CString str;
			//str.Format(_T(),)

			for(int j = 0; j < 4; j++)
			{
				for(int i = 0; i < 4; i++)
				{
					if((m_LEDReadData[j]>>i) & 0x01)
					{
						m_GMES_ErrorValue += "O";
					}
					else
					{					
						m_GMES_ErrorValue += "X";				
					}
				}
				m_GMES_ErrorValue += "[";
				for(int i = 0; i < 4; i++)
				{
					if((m_LEDOkAckData[j]>>i) & 0x01)
					{
						m_GMES_ErrorValue += "O";
					}
					else
					{					
						m_GMES_ErrorValue += "X";				
					}

				}
				m_GMES_ErrorValue += "]  ";
			}


			//m_GMES_ErrorValue = _T("ERROR");
			//m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
						

		}
		else
		{
			if(sWaitCnt <= 0)
			{
				sWaitCnt = 10;
				LEDReadSend();
			}			
		}
		break;	
	case   TEST_SEQ_TYPE_CHECK_FAN:
		
		
		if(m_LED_Up_DI_ReadData[m_FanDiPort] != 0)
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);				
						
		}
		else if(GetTimeCheck(1) > m_CheckDelayTime)
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
					
			m_GMES_ErrorName = _T("FAN CHECK ERROR :");
			m_Deisplay_ErrorName = _T("COOLING FAN ERROR \r\n");
			m_Deisplay_ErrorName += _T("FAN 检查 NG ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
			//CString str;
			//str.Format(_T(),)

	
			m_GMES_ErrorValue += "  ";
			


			//m_GMES_ErrorValue = _T("ERROR");
			//m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
						

		}
		else
		{
			if(sWaitCnt <= 0)
			{
				sWaitCnt = 10;
				UP_DIReadSend();
			}			
		}
		break;	

			
	case   TEST_SEQ_TYPE_MANUAL_CHECK:		
		
		if((m_LED_Up_DI_ReadData[1] != 0) || ( mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_OKCLICK))
		{
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

			//m_cLbOkNg.put_Caption(_T("O K"));
			//m_cLbOkNg.put_BackColor(0x0000FF00);	
			mpDlgSimpleInform->ShowWindow(SW_HIDE);
						
		}
		else if((m_LED_Up_DI_ReadData[2] != 0)
			||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_TIMEOUT)
			||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_CANCELCLICK))
		{

			mpDlgSimpleInform->m_Close_Result = _CLOSE_DISPLAY_TIMEOUT;

			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
					
			m_GMES_ErrorName = _T("MANUAL CHECK ERROR :");
			m_Deisplay_ErrorName = _T("USER CHECK ERROR \r\n");
			m_Deisplay_ErrorName += _T("USER MANUAL 检查 NG ");
			m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
			//CString str;
			//str.Format(_T(),)

	
			m_GMES_ErrorValue += "  ";
			


			//m_GMES_ErrorValue = _T("ERROR");
			//m_Deisplay_ErrorName = m_GMES_ErrorName;
			m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//

			mpDlgSimpleInform->ShowWindow(SW_HIDE); 
						

		}
		else
		{
			if(sWaitCnt <= 0)
			{
				sWaitCnt = 10;
				UP_DIReadSend();
				SetTimeCheck(LED_COM_DELAY_ID);
			}			
		}
		break;	

	case   TEST_SEQ_TYPE_USER_MASSAGE :

		if ((m_LED_Up_DI_ReadData[1] != 0) || (m_pUserMsgDlg->m_Close_Result == _CLOSE_DISPLAY_OKCLICK) || (m_pUserMsgDlg->m_bActivate == 0))
		{

			if (m_pUserMsgDlg->m_bActivate == 1)
			{
				m_pUserMsgDlg->ShowWindow(SW_HIDE);
			}
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

		}
		//else if((m_LED_Up_DI_ReadData[2] != 0)
		//	)
		//	//||(mpDlgSimpleInform->m_Close_Result == _CLOSE_DISPLAY_CANCELCLICK))
		//{

		//

		//	m_nCurrentStep = 2;

		//	gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
		//			
		//	m_GMES_ErrorName = _T("USER CHECK ERROR :");
		//	m_Deisplay_ErrorName = _T("USER CHECK ERROR \r\n");
		//	m_Deisplay_ErrorName += _T("USER MANUAL TEST NG ");
		//	m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;// 命令 //检查
		//	//CString str;
		//	//str.Format(_T(),)


		//	m_GMES_ErrorValue += "  ";
		//	


		//	//m_GMES_ErrorValue = _T("ERROR");
		//	//m_Deisplay_ErrorName = m_GMES_ErrorName;
		//	m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//
		//				

		//}
		else
		{
			if (sWaitCnt <= 0)
			{
				sWaitCnt = 10;
				UP_DIReadSend();
			}
		}
		break;
	case   TEST_SEQ_TYPE_WAIT_MASSAGE:
		if ((m_LED_Up_DI_ReadData[1] != 0) || (m_pUserMsgDlg->m_Close_Result == _CLOSE_DISPLAY_OKCLICK) || (m_pUserMsgDlg->m_bActivate == 0))
		{

			if (m_pUserMsgDlg->m_bActivate == 1)
			{
				m_pUserMsgDlg->ShowWindow(SW_HIDE);
			}
			m_nCurrentStep = 2;

			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;

		}
	
		else
		{
			if (sWaitCnt <= 0)
			{
				sWaitCnt = 10;
				UP_DIReadSend();
				SetTimeCheck(LED_COM_DELAY_ID);
			}
		}
		break;
	case   TEST_SEQ_TYPE_CLEAR_LED:			

			m_nCurrentStep = 2;
			gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 1;
		
		break;	
	case   TEST_SEQ_TYPE_SET_MIC1:
	
		m_MIC_Status = _ttoi(m_FunctionParameter);
		if(m_MIC_Status != 1)
			m_MIC_Status = 0;

		SetFreqSend(4, m_MIC_Status);//MIC : 4(m_MIC_Status);
		m_nCurrentStep = 2;
		break;	


	case   TEST_SEQ_TYPE_SET_MIC2:
	
		m_MIC_Status = _ttoi(m_FunctionParameter);
		if(m_MIC_Status != 1)
			m_MIC_Status = 0;

		SetFreqSend(5, m_MIC_Status);//MIC : 4(m_MIC_Status);
		m_nCurrentStep = 2;

		
		break;			


	default:
		break;

	}

}


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

void CAcqVoltageSamples_IntClkDlg::SendIR_Code(CString lCodeString,  int lRepeat)
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

	if(lRepeat == 1)
	{
		sprintf((char *)&lbuf[1], "CRSNE");
	}
	else if(lRepeat == 2)
	{
		sprintf((char *)&lbuf[1], "CRSN2");
	}
	else if(lRepeat > 5)
	{
		sprintf((char *)&lbuf[1], "CRS%02d", lRepeat);
	}
	else 
	{
		sprintf((char *)&lbuf[1], "CRSND");
	}

	if(lRmtCodeIndex < m_RemoconModel.m_Cnt)
	{
		if(gTestSeqData.nRemoconSigType == 0)
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

		 AddProcessLog(Logstr, 1);

	}
	else
	{
		//MessageBox("Send IR CODE FAIL!!");
		MessageDisplay(1, "Send IR CODE FAIL!!");
		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
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
		if(gTestSeqData.nRemoconSigType == 0)
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
		

		 

	}
	else
	{
		//MessageBox("Send IR CODE FAIL!!");
		MessageDisplay(1, "Send PRE IR CODE FAIL!!");
	}
}



void CAcqVoltageSamples_IntClkDlg::UartCommandPcbSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;

	int lType = 0x01;//m_ComboPcbType.GetCurSel();
	//CString Str;
	//GetDlgItemText(IDC_EDIT_PCB_COMMAND,Str);

	

	lbuf[0] = 0xAA;
	lbuf[1] = m_UartCommandCnt + 2;//0x03;
//	sprintf(lbuf,"PCB TYPE= %d\n", gTestSeqData.nComPcbType);// m_cComboModelPcbType
	if((gTestSeqData.nComPcbType >= 0)&&(gTestSeqData.nComPcbType < 3))
	{
		lbuf[2] = 0x01 + gTestSeqData.nComPcbType;
	}
	else
	{
		gTestSeqData.nComPcbType = 0;
		lbuf[2] = 0x01 + gTestSeqData.nComPcbType;
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

	m_PCB_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_PCBComAck =COM_ACK_WAIT;
	m_PCBWaitCnt = 0;
	m_PCBResendCnt = 0;
	if(m_SendBufPCB[3] == 0xc1)
		m_WaitPCB_Ack_Limit = 600;
	else
		m_WaitPCB_Ack_Limit = 200;


	MessageDisplay(2, "Command Send!");
}


void CAcqVoltageSamples_IntClkDlg::ComLedRead()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	if(m_ComPortLED.mPort_Opened)
	{
		
		m_ComPortLED.WriteToPort(m_SendBufLED, m_SendCntLED);
	}
	else
	{
		OpenComportLED();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPortLED.mPort_Opened)
		{
			
			m_ComPortLED.WriteToPort(m_SendBufLED, m_SendCntLED);
		}
	}

	m_RecvCntLED = 0;
}
void CAcqVoltageSamples_IntClkDlg::LEDReadSend()
{

	BYTE lbuf[128]; 
	//int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CCHECKLED");
  //sprintf((char *)&lbuf[1], "CMAC_READ");
	
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	

	memcpy(m_SendBufLED, lbuf, 13); 	
	m_SendCntLED = 13;

	ComLedRead();

	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;
	MessageDisplay(2, "LED Read!");
}
void CAcqVoltageSamples_IntClkDlg::UP_DIReadSend()
{

	BYTE lbuf[128]; 
	//int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CCHECKDIN");
  //sprintf((char *)&lbuf[1], "CMAC_READ");
	
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	

	memcpy(m_SendBufLED, lbuf, 13); 	
	m_SendCntLED = 13;

	ComLedRead();

	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;
	MessageDisplay(2, "UP DI Read!");
}
void CAcqVoltageSamples_IntClkDlg::LEDClearSend()
{

	BYTE lbuf[128]; 
	//int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CCLEARLED");
  //sprintf((char *)&lbuf[1], "CMAC_READ");
	
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	

	memcpy(m_SendBufLED, lbuf, 13); 	
	m_SendCntLED = 13;

	ComLedRead();

	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;
	MessageDisplay(2, "LED Clear!");
}

//SetMic
void CAcqVoltageSamples_IntClkDlg::SetFreqSend(UINT lPort, UINT lFreq )//MIC : 4
{
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
	}
	else
	{
		sprintf((char *)&lbuf[1], "CFREQ%02d%03d       ", lPort, lFreq/10);
	}
	
	lbuf[18] = 0x03;
	lbuf[19] = 0x0d;
	lbuf[20] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	SendData(lbuf, 21);	
	
	//MessageDisplay(2, "Frequency Set !");


}

void CAcqVoltageSamples_IntClkDlg::GetRmtCodeList(CString lRmtFile)//gTestSeqData.strRemoconFileName;
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

	

	str = PATH_BASE_DIR;
	str += _T("\\Remote\\");
	str += lRmtFile;//gTestSeqData.strRemoconFileName;
	
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
	} 
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedStopButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_TaskRun = false;
	m_TaskRun = TASK_RUN_IDLE;
	//m_startButton.EnableWindow(true);
	CycleTimeOn = 0;

	if (m_pUserMsgDlg->m_bActivate == 1)
	{
		m_pUserMsgDlg->ShowWindow(SW_HIDE);
	}

	//TestFinish();///test
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
	gbShutdown = true;
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

	if(mpDlgResult != NULL)
		delete mpDlgResult;

	if(mpDlgBarcode != NULL)
		delete mpDlgBarcode;

	if(mpDlgSimpleInform != NULL)
		delete mpDlgSimpleInform;

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
		//if(gTestSeqData.TestProcess.aSeqData[i].nSeqType == TEST_SEQ_TYPE_TEST_1)
		//{	
		//	
		//	for(int j = 0; j < 6; j++)
		//	{
		//		lPortData = gTestSeqData.SetPortTest_1[j];
		//		
		//		if((lPortData.nInput == 2) || (lPortData.nInput == 3))
		//		{				
		//			m_DigitalPort = DIG_OPTICAL_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//		else if((lPortData.nInput == 16) || (lPortData.nInput == 17))
		//		{				
		//			m_DigitalPort = DIG_COAX_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//	}
		//}
		//else if(gTestSeqData.TestProcess.aSeqData[i].nSeqType == TEST_SEQ_TYPE_TEST_2)
		//{	
		//	
		//	for(int j = 0; j < 6; j++)
		//	{
		//		lPortData = gTestSeqData.SetPortTest_2[j];
		//		
		//		if((lPortData.nInput == 2) || (lPortData.nInput == 3))
		//		{				
		//			m_DigitalPort = DIG_OPTICAL_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//		else if((lPortData.nInput == 16) || (lPortData.nInput == 17))
		//		{				
		//			m_DigitalPort = DIG_COAX_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//	}
		//}		
		//else if(gTestSeqData.TestProcess.aSeqData[i].nSeqType == TEST_SEQ_TYPE_TEST_3)
		//{	
		//	
		//	for(int j = 0; j < 6; j++)
		//	{
		//		lPortData = gTestSeqData.SetPortTest_3[j];
		//		
		//		if((lPortData.nInput == 2) || (lPortData.nInput == 3))
		//		{				
		//			m_DigitalPort = DIG_OPTICAL_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//		else if((lPortData.nInput == 16) || (lPortData.nInput == 17))
		//		{				
		//			m_DigitalPort = DIG_COAX_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//	}
		//}	
		//else if(gTestSeqData.TestProcess.aSeqData[i].nSeqType == TEST_SEQ_TYPE_TEST_4)
		//{	
		//	
		//	for(int j = 0; j < 6; j++)
		//	{
		//		lPortData = gTestSeqData.SetPortTest_4[j];
		//		
		//		if((lPortData.nInput == 2) || (lPortData.nInput == 3))
		//		{				
		//			m_DigitalPort = DIG_OPTICAL_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//		else if((lPortData.nInput == 16) || (lPortData.nInput == 17))
		//		{				
		//			m_DigitalPort = DIG_COAX_SELECT;
		//			lDigtalFound = 1;
		//			break;
		//		}
		//	}
		//}		
	}

	//SetDigitalPortSelect(m_DigitalPort, 1);
}

void CAcqVoltageSamples_IntClkDlg::SetDigitalPortSelect(int lDigSel, int lRefresh)
{

	if(lRefresh)
	{
		m_DigitalPort_Save = lDigSel;
	}
	else if(m_DigitalPort_Save == lDigSel)
	{
		return;
	}

	BYTE lbuf[128]; 
	int lcnt;
	CString str;
	//UINT m_EditFreq1;
	UpdateData();

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CA_SEL_%02d", lDigSel);
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	SendData(lbuf, 13);

	//m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	// m_ComAck =COM_ACK_WAIT;
	// m_WaitCnt = 0;
	// m_ResendCnt = 0;
	
	//MessageDisplay(2, "Frequency Set !");
}


void CAcqVoltageSamples_IntClkDlg::SetChannelData(int lTestNumber)
{
	
	//int lCheckID[6] = {0,1,2,3,14,15};
	/*CString lStrName[18] = {
		_T("HDMI_R"),_T("HDMI_L"),
		_T("OPTICAL_R"),_T("OPTICAL_L"),
		_T("SPEAKER_1R"),_T("SPEAKER_1L"),
		_T("SPEAKER_2R"),_T("SPEAKER_2L"),
		_T("SPEAKER_3R"),_T("SPEAKER_3L"),
		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		_T("AUX_R"),_T("AUX_L"),
		_T("PORTABLE_R"),_T("PORTABLE_L"), 
		_T("COAX_R"),_T("COAX_L")};	*/
		
		CString lStrName[18] = {
		_T("HDMI_R"),_T("HDMI_L"),
		_T("OPTICAL_R"),_T("OPTICAL_L"),
		_T("Front R"),_T("Front L"),
		_T("Rear R"),_T("Rear L"),
		_T("Center"),_T("Woofer"),
		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		_T("AUX_R"),_T("AUX_L"),
		_T("PORTABLE_R"),_T("PORTABLE_L"), 
		_T("COAX_R"),_T("COAX_L")};

	double l_RefVoltageMin[6] = {300,300,300,300,300,300};
	double l_RefVoltageMax[6] = {1500,1500,1500,1500,1500,1500};
	double l_FrequencyMin[6] = {10,10,10,10,10,10};
	double l_FrequencyMax[6] = {1200,1200,1200,1200,1200,1200};

	
	m_cLb_Test1.put_Caption(_T("WAIT"));
	m_cLb_Test1.put_BackColor(0x0000FFFF);
	
	m_cLb_Test2.put_Caption(_T("WAIT"));
	m_cLb_Test2.put_BackColor(0x0000FFFF);
	
	m_cLb_Test3.put_Caption(_T("WAIT"));
	m_cLb_Test3.put_BackColor(0x0000FFFF);

	


	//m_OkNgLabel.put_Text(_T("WAIT"));
	//m_OkNgLabel.put_BackColor(0x0000FFFF);
	
	m_cLbOkNg.put_Caption(_T("WAIT"));
	m_cLbOkNg.put_BackColor(0x0000FFFF);


	m_TotalOK = 3;

	//m_LevelSkip = 1;
	


	for(int i = 0; i < 8; i++)
	{
		m_CheckEnable[i] = 1;
		if(m_CheckEnable[i] )
		{							
			m_DigitalPort = DIG_OPTICAL_SELECT;					
			m_CheckID[i] = i+4;			

			m_ChnnelName[i] = lStrName[i+4];
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

		CString lStrName[18] = {
		_T("HDMI_R"),_T("HDMI_L"),
		_T("OPTICAL_R"),_T("OPTICAL_L"),
		_T("Front R"),_T("Front L"),
		_T("Rear R"),_T("Rear L"),
		_T("Center"),_T("Woofer"),
		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		_T("AUX_R"),_T("AUX_L"),
		_T("PORTABLE_R"),_T("PORTABLE_L"), 
		_T("COAX_R"),_T("COAX_L")};

	double l_RefVoltageMin[6] = {300,300,300,300,300,300};
	double l_RefVoltageMax[6] = {1500,1500,1500,1500,1500,1500};
	double l_FrequencyMin[6] = {10,10,10,10,10,10};
	double l_FrequencyMax[6] = {1200,1200,1200,1200,1200,1200};

	
	m_cLb_Test1.put_Caption(_T("WAIT"));
	m_cLb_Test1.put_BackColor(0x0000FFFF);
	
	m_cLb_Test2.put_Caption(_T("WAIT"));
	m_cLb_Test2.put_BackColor(0x0000FFFF);
	
	m_cLb_Test3.put_Caption(_T("WAIT"));
	m_cLb_Test3.put_BackColor(0x0000FFFF);

	


	//m_OkNgLabel.put_Text(_T("WAIT"));
	//m_OkNgLabel.put_BackColor(0x0000FFFF);
	
	m_cLbOkNg.put_Caption(_T("WAIT"));
	m_cLbOkNg.put_BackColor(0x0000FFFF);


	m_TotalOK = 3;

	//m_LevelSkip = 1;
	


	for(int i = 0; i < 8; i++)
	{
		m_CheckEnable[i] = 1;
		if(m_CheckEnable[i] )
		{							
			m_DigitalPort = DIG_OPTICAL_SELECT;					
			m_CheckID[i] = g_ManualId[i];

			m_ChnnelName[i] = lStrName[g_ManualId[i]];
			m_NameLabel[i].put_Caption(m_ChnnelName[i]);

			//m_RefVoltageMin[i] = l_RefVoltageMin[i];
			//m_RefVoltageMax[i] = l_RefVoltageMax[i];
			//m_FrequencyMin[i] = l_FrequencyMin[i];
			//m_FrequencyMax[i] = l_FrequencyMax[i];
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
	CString lStrName[18] = {
	_T("HDMI_R"),_T("HDMI_L"),
	_T("OPTICAL_R"),_T("OPTICAL_L"),
	_T("Front R"),_T("Front L"),
	_T("Rear R"),_T("Rear L"),
	_T("Center"),_T("Woofer"),
	_T("SPEAKER_4R"),_T("SPEAKER_4L"),
	_T("AUX_R"),_T("AUX_L"),
	_T("PORTABLE_R"),_T("PORTABLE_L"), 
	_T("COAX_R"),_T("COAX_L")};
	
	if((lTestChannel > 0)&&(lTestChannel < 7))//Zero Base Index
	{
		lTestChannel -= 1;
	}

	if((lSource > 0)&&(lSource < 19))//Zero Base Index
	{
		lSource -= 1;
	}
		
	if((lSource == 2) || (lSource == 3))
	{				
		m_DigitalPort = DIG_OPTICAL_SELECT;
	}
	else if((lSource == 16) || (lSource == 17))
	{				
		m_DigitalPort = DIG_COAX_SELECT;
	}

	if(lSource == 16)
	{
		m_CheckID[lTestChannel] = 2;
		//m_DigitalPort = DIG_COAX_SELECT;//DIG_OPTICAL_SELECT;
	}
	else if(lSource == 17)
	{
		m_CheckID[lTestChannel] = 3;
		//m_DigitalPort = DIG_COAX_SELECT;//DIG_OPTICAL_SELECT;
	}
	else if((lSource >= 0)&&(lSource <= 15))
	{
		m_CheckID[lTestChannel] = lSource;
	}
	else
	{
		m_CheckEnable[lTestChannel] = 0;
	}

	m_ChnnelName[lTestChannel] = lStrName[lSource];
	m_NameLabel[lTestChannel].put_Caption(m_ChnnelName[lTestChannel]);
	if((lSource == 2) || (lSource == 3)||(lSource == 16) || (lSource == 17))
	{				
	//	m_DigitalPort = DIG_COAX_SELECT;	
		SetDigitalPortSelect(m_DigitalPort, 0);
	}
}


void CAcqVoltageSamples_IntClkDlg::SetChannelDataRangeSeq(int lTestChannel,int l_RefVoltageMin,int l_RefVoltageMax,int l_FrequencyMin,int l_FrequencyMax)
{	

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


	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
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

	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
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
				AfxMessageBox(strTemp);
				m_InitAiChannel = 0;
			}
			err = AI_AsyncDblBufferMode(m_hCard, 0);
			if (err != 0) {
				strTemp.Format(TEXT("AI_DblBufferMode error=%d"), err);
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

	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		//m_InitAiChannel = 1;
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
	I16 err;
	CString 	strTemp;
	if (m_InitAiChannel == 0)
	{
		return;
	}

	if (m_CheckEnable[lch] == 0)
		return;
	if (g_SetComOnlyMode == 1)
	{
		return;
	}
	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
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
   
	//m_PPVoltage[CheckID] = PPVoltage;	
	//m_Frequency[CheckID] = Frequency;
			if((m_PPVoltage[lch] < 10)
				||((m_PPVoltage[lch] < 100) 
					&& (( m_CheckID[lch] < 4) || (m_CheckID[lch] > 11))))
			{
				m_graph[lch].Axes.Item("YAxis-1").Maximum = 1.2;
				m_graph[lch].Axes.Item("YAxis-1").Minimum = -1.2;
			}
			else if(m_PPVoltage[lch] < 100)
			{
   				if((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch]/2000*1.4 *3)||(m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch]/2000 *3))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 *5 ;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 *5;
				}
			}			
			else if(m_PPVoltage[lch] < 500)
			{
   				if((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch]/2000*2.5)||(m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch]/2000*2.5))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 *3;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 *3;
				}
			}
			else if(m_PPVoltage[lch] < 1000)
			{
   				if((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch]/2000*1.4*2)||(m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch]/2000*2))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 *2.5;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 *2.5;
				}
			}
			else if(m_PPVoltage[lch] < 2000)
			{
   				if((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch]/2000*1.4 *1.5)||(m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch]/2000 *1.5))
				{
					m_graph[lch].Axes.Item("YAxis-1").Maximum = m_PPVoltage[lch] * 1.2 / 2000 *1.5;
					m_graph[lch].Axes.Item("YAxis-1").Minimum = -m_PPVoltage[lch] * 1.2 / 2000 *1.5;
				}
			}
			else if(m_PPVoltage[lch] < 4000)
			{
   				if((m_graph[lch].Axes.Item("YAxis-1").Maximum > m_PPVoltage[lch]/2000*1.4)||(m_graph[lch].Axes.Item("YAxis-1").Maximum < m_PPVoltage[lch]/2000))
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
				m_graph[lch].Plots.Item(i+1).LineColor = m_colors[0];
			}
/*	
			for (unsigned int i = 0; i < 500; i++)
			{
				m_graph[lch].PlotY( Check_data[lch][i]);
			}
*/

			m_graph[lch].PlotY(Check_data[lch]);

		
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


	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
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

	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
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
	if(m_InitAiChannel == 0)
	{
		return 0;
	}

	if(m_DOportOpen == 0)
		return 0;


	m_DO_Writedata = lSetVal;

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

	return 1;

}


BOOL CAcqVoltageSamples_IntClkDlg::ReadD_IN(unsigned long *lReadData)
{
	if(m_InitAiChannel == 0)
	{
		return 0;
	}

	if(	m_DIportOpen == 0)
		return 0;


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

	return 1;
}
#endif
//#define TEMP_CHANGE_PORT__

void CAcqVoltageSamples_IntClkDlg::CheckControlInput()
{
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
	unsigned long lCheck_Time;

	//static int sEthernetWaitCnt = 0;



	if(gbManualScopeMode == 1)
	{
		if(nIDEvent == 2)
		{
			KillTimer(2);

			if (g_nPortReopen)
			{
				MessageDisplay(2, "GMES Port Change!");
				CloseEthernetScocket();
				m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
				m_EthernetWaitCnt = 0;

				m_GmesOpen = 1;// gTestSeqData.bMesEnable = 1;
				g_nPortReopen = 0;
			}

			//if (m_GmesOpen == 0)//gTestSeqData.bMesEnable == 0)
			//{
			//	m_EthernetMode = ETHERNET_MODE_IDLE;
			//}

			switch (m_EthernetMode)
			{
			case ETHERNET_MODE_CREATE_SOCKET:

				if (m_EthernetWaitCnt > 1)
				{
					if (CreateEthernetSocket())
					{
						m_EthernetMode = ETHERNET_MODE_HOST_CHECK;

						MessageDisplay(2, "GMES Socket Create!");
						//m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);

					}
					else
					{
						m_EthernetMode = ETHERNET_MODE_IDLE;

						MessageDisplay(1, "GMES Socket Create Fail!");
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);

						MessageBox("GMES Socket Create Fail!");

						m_GmesOpen = 0;// gTestSeqData.bMesEnable = 0;

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

				if (m_EthernetWaitCnt > 5)
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

				if (m_EthernetWaitCnt > 10)
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

				if (m_EthernetWaitCnt > 10)
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
				if (m_EthernetAck == 1)
				{
					m_EthernetWaitCnt = 0;
					m_EthernetMode = ETHERNET_MODE_RUN;//ETHERNET_MODE_WAIT
				}
				else if (m_EthernetWaitCnt > 250)//else if(m_EthernetWaitCnt > g_nGmesWaitTime/20)//else if(m_EthernetWaitCnt > 100)
				{
					m_EthernetResendCnt++;
					if (m_EthernetResendCnt > 1)
					{
						m_EthernetWaitCnt = 0;
						if (gTestSeqData.bMesEnable == 1)
						{
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
				if (gTestSeqData.bMesEnable == 1)
				{
					if (m_GMES_Alive_WaitCnt > 2500)
					{
						m_GmesOpen = 0;
						m_GMES_Alive_WaitCnt = 2;

						MessageBox("GMES Link Time Out");
						CloseEthernetScocket();
						m_GMES_NGCNT++;
						MessageDisplay(1, "GMES Link Time Out");
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);

						m_EthernetWaitCnt = 0;

					}
					else
					{

						if (m_GMES_Alive_WaitCnt == 20)
						{
							m_GmesOpen = 1;
							m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
							//m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
						}
						//else if (m_GMES_Alive_WaitCnt == 200)
						//{
						//	m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
						//	//		GMESLinkLoopbackTest();
						//}


					}
				}
				else
				{
					if (m_GMES_Alive_WaitCnt > 2500)
					{
						m_GmesOpen = 0;
						m_GMES_Alive_WaitCnt = 2;

						CloseEthernetScocket();
						MessageDisplay(1, "GMES Link Time Out");
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);

						m_EthernetWaitCnt = 0;

					}
					//else
					//{

					//	if (m_GMES_Alive_WaitCnt == 20)
					//	{
					//		m_GmesOpen = 1;
					//		m_cLb_ComMainGmes.put_BackColor(0x000F8F8F); //m_cLb_ComMainGmes.put_BackColor(0x0000FF00);

					//	}
					//	else if (m_GMES_Alive_WaitCnt == 200)
					//	{
					//		m_cLb_ComMainGmes.put_BackColor(0x00008F8F); //m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
					//	}
					//}
				}

				//SetTimer(2,20,NULL);

				break;
			default:

				if (m_EthernetWaitCnt > 100)
				{
					m_EthernetWaitCnt = 0;
					//if (gTestSeqData.bMesEnable == 1)
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
				}
				else
				{
					m_EthernetWaitCnt++;
				}
				//if(gTestSeqData.bMesEnable)
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
					m_RoopCnt++;
					str.Format(_T("%3d "),m_RoopCnt);
					m_CheckTimeLabel.put_Caption(str);
				}
			}
			
			m_RunCounter++;
			if(m_RunCounter > 120000)
			{
				m_RunCounter = 0;
			}


		////	if(m_Camera_Capture_Flag == 1)
		////	if(m_RunCounter%3 == 0)
		//	{
		//		ProcessGetImage();
		//		//if(m_TaskRun ==  TASK_RUN_IDLE)
		//		//	SelectImage();
		//	}


	

			switch(m_MainPAGE_COM_PROCESS)
			{
				case COM_MODE_WAIT_ACK:
					if(m_ComAck == COM_ACK_OK)
					{
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
		

	
			switch(m_LED_COM_PROCESS)
			{
			case COM_MODE_IDLE:
				break;
			case COM_MODE_WAIT_ACK:

				if(m_LEDComAck == COM_ACK_OK)
				{
					m_LEDComAck = COM_ACK_WAIT;
					m_LED_COM_PROCESS = COM_MODE_IDLE;
					//MessageBox("COM OK !! ");
					//MessageDisplay(0, "COM LED OK !! ");
				}
				else if(m_LEDComAck == COM_ACK_BUSY)
				{
					//MessageBox("COM Fail !! ");
					MessageDisplay(1, "COM LED FAIL !! ");
					m_LED_COM_PROCESS = COM_MODE_IDLE;
				}
				else
				{
					/*
					int m_WaitCnt;
					int m_ResendCnt;
					*/
				
					
					if(m_TaskRun == TASK_RUN_IDLE)
					{
						
						m_LEDWaitCnt++;

						if(m_LEDWaitCnt > 100)
						{			
							m_LEDResendCnt++;
							if(m_LEDResendCnt < 2)
							{
								ComLedRead();
							}
							else
							{
								//MessageBox("COM Time Out !! ");
								MessageDisplay(2, "COM LED Time Out !!");
								m_LED_COM_PROCESS = COM_MODE_IDLE;
							}
						}

					}
					else
					{
						if(GetTimeCheck(1) > m_CheckDelayTime)
						{
						//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
						//	if(IDYES == MessageBox("Main COM NG RETRY?" , "NG" , MB_YESNO))
						//	{
						//		m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
						//		//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
						////		m_nCurrentProcess = 0;
						////		if(GetTimeCheck(1) > m_CheckDelayTime)
						//		ComLedRead();
						//		SetTimeCheck(1);
		
						//	}
						//	else
						//	{
						//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
						//		TestFinish();
						//		m_LED_COM_PROCESS = COM_MODE_IDLE;
						//	}
						/*	m_TaskRun = TASK_WAIT_SELECT_PROCESS;
						
							NG_Display();
							m_NG_Retry_Count++;*/
							MessageDisplay(2, "COM LED Time Out !!");
							m_LED_COM_PROCESS = COM_MODE_IDLE;
						
						}
					}
				}
				break;
			default:
				m_LED_COM_PROCESS = COM_MODE_IDLE;
				break;

			}

			//int m_PCB_COM_PROCESS;
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

		if(g_nPortReopen)
		{
			MessageDisplay(2, "GMES Port Change!");
			CloseEthernetScocket() ;
			m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
			m_EthernetWaitCnt = 0;
		
		//	m_GmesOpen = 1;// gTestSeqData.bMesEnable = 1;
			g_nPortReopen = 0;
		}

		//if(m_GmesOpen == 0)//gTestSeqData.bMesEnable == 0)
		//{
		//	m_EthernetMode = ETHERNET_MODE_IDLE;
		//}

		switch(m_EthernetMode)
		{	
		case ETHERNET_MODE_CREATE_SOCKET:

			if(m_EthernetWaitCnt > 1)
			{
				if(CreateEthernetSocket())
				{
					m_EthernetMode = ETHERNET_MODE_HOST_CHECK;
					
						MessageDisplay(2, "GMES Socket Create!");
						//m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
					
				}
				else
				{
					m_EthernetMode = ETHERNET_MODE_IDLE;
					
						MessageDisplay(1, "GMES Socket Create Fail!");
						m_cLb_ComMainGmes.put_BackColor(0x000000FF);

						MessageBox("GMES Socket Create Fail!");
					
						m_GmesOpen = 0;// gTestSeqData.bMesEnable = 0;

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
			else if(m_EthernetWaitCnt > 250)//else if(m_EthernetWaitCnt > g_nGmesWaitTime/20)//else if(m_EthernetWaitCnt > 100)
			{
				m_EthernetResendCnt++;
				if(m_EthernetResendCnt > 1)
				{
					m_EthernetWaitCnt = 0;
					if (gTestSeqData.bMesEnable == 1)
					{
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
			if(gTestSeqData.bMesEnable == 1)
			{
				if (m_GMES_Alive_WaitCnt > 2500)
				{
					m_GmesOpen = 0;
					m_GMES_Alive_WaitCnt = 2;
					
					MessageBox("GMES Link Time Out");
					CloseEthernetScocket();
					m_GMES_NGCNT++;
					MessageDisplay(1, "GMES Link Time Out");
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);

					m_EthernetWaitCnt = 0;
					
				}
				else
				{
					
					if (m_GMES_Alive_WaitCnt == 20)
					{
						m_GmesOpen = 1;
						m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
						//m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
					}
					//else if (m_GMES_Alive_WaitCnt == 200)
					//{
					//	m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
					//	//		GMESLinkLoopbackTest();
					//}
					

				}
			}
			else
			{
				if (m_GMES_Alive_WaitCnt > 2500)
				{
					m_GmesOpen = 0;
					m_GMES_Alive_WaitCnt = 2;

					CloseEthernetScocket();
					MessageDisplay(1, "GMES Link Time Out");
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);

					m_EthernetWaitCnt = 0;

				}
				else
				{

					//if (m_GMES_Alive_WaitCnt == 20)
					//{
					//	m_GmesOpen = 1;
					//	m_cLb_ComMainGmes.put_BackColor(0x000F8F8F); //m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
					//	
					//}
					//else if (m_GMES_Alive_WaitCnt == 200)
					//{
					//	m_cLb_ComMainGmes.put_BackColor(0x000F8F8F); //m_cLb_ComMainGmes.put_BackColor(0x0000FFFF);
					//}
				}
			}
		
			//SetTimer(2,20,NULL);

			break;
		default:

			if(m_EthernetWaitCnt > 100)
			{
				m_EthernetWaitCnt = 0;
				//if (gTestSeqData.bMesEnable == 1)
					m_cLb_ComMainGmes.put_BackColor(0x000000FF);
			}
			else
			{
				m_EthernetWaitCnt++;
			}
			//if(gTestSeqData.bMesEnable)
			//{
			////	m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
			////	m_EthernetWaitCnt = 0;

			//}
			break;
		}

		//if ((m_UploadGmes == 1)&&(gTestSeqData.bMesEnable == 1))
		//{
		//	m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		//}

		SetTimer(2,20,NULL);
	}
	else if(nIDEvent == 1)
	{
		KillTimer(1);
	

		CheckControlInput();

		int i = m_RunCounter%6;
		if(m_CheckEnable[i] == 1)
		{
			//for(int i = 0; i < 6; i++)
			{
				ReadChannel(i);
			//	ReadChannelex(i);
			
				CheckData(i);
				UpdatePlot(i);

			}
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
		}


	//	if(m_Camera_Capture_Flag == 1)
	//	if(m_RunCounter%3 == 0)
		//{
		//	ProcessGetImage();
		//	//if(m_TaskRun ==  TASK_RUN_IDLE)
		//	//	SelectImage();
		//}


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
					m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
					m_ComWaitCnt = 0;

					m_MainCOM_NG_Count = 0;
				}
				else if(m_ComAck == COM_ACK_BUSY)
				{
					m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
					m_ComWaitCnt = 0;
					m_MainCOM_NG_Count = 0;
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

						if(m_ComWaitCnt > 60)
						{
							m_ComWaitCnt = 0;
							m_ResendCnt++;
							if(m_ResendCnt > 3)
							{
								int ltime = GetTimeCheck(1);
								//if(ltime > m_CheckDelayTime)
								{
									//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
									//m_TaskRun = TASK_WAIT_SELECT_PROCESS;
									m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
									//NG_Display();
									//m_NG_Retry_Count++;
									MessageDisplay(2, "COM WAIT TIME OUT !!!");
									m_MainCOM_NG_Count++;
									if (m_MainCOM_NG_Count > 10)
									{
										MessageBox("MAIN Control Box Disconnected !!!");
										MessageDisplay(1, "MAIN Control Box Disconnected !!!");
									}
								}
							}
							else
							{
								if (m_ResendCnt == 3)
									OpenComport();
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
		

	
		switch(m_LED_COM_PROCESS)
		{
		case COM_MODE_IDLE:
			break;
		case COM_MODE_WAIT_ACK:

			if(m_LEDComAck == COM_ACK_OK)
			{
				m_LEDComAck = COM_ACK_WAIT;
				m_LED_COM_PROCESS = COM_MODE_IDLE;
				//MessageBox("COM OK !! ");
				//MessageDisplay(0, "COM LED OK !! ");
			}
			else if(m_LEDComAck == COM_ACK_BUSY)
			{
				//MessageBox("COM Fail !! ");
				MessageDisplay(2, "COM LED FAIL !! ");
				m_LED_COM_PROCESS = COM_MODE_IDLE;
			}
			else
			{
				/*
				int m_WaitCnt;
				int m_ResendCnt;
				*/
				
					
				if(m_TaskRun == TASK_RUN_IDLE)
				{
						
					m_LEDWaitCnt++;

					if(m_LEDWaitCnt > 100)
					{			
						m_LEDResendCnt++;
						if(m_LEDResendCnt < 2)
						{
							ComLedRead();
						}
						else
						{
							//MessageBox("COM Time Out !! ");
							MessageDisplay(2, "COM LED Time Out !!");
							m_LED_COM_PROCESS = COM_MODE_IDLE;
						}
					}

				}
				else
				{
					if(GetTimeCheck(LED_COM_DELAY_ID) > 1000)//_CheckDelayTime)
					{
					//	m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "NG", NULL, NULL, NULL, NULL);
					//	if(IDYES == MessageBox("Main COM NG RETRY?" , "NG" , MB_YESNO))
					//	{
					//		m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
					//		//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
					////		m_nCurrentProcess = 0;
					////		if(GetTimeCheck(1) > m_CheckDelayTime)
					//		ComLedRead();
					//		SetTimeCheck(1);
		
					//	}
					//	else
					//	{
					//		gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 0;
					//		TestFinish();
					//		m_LED_COM_PROCESS = COM_MODE_IDLE;
					//	}
					/*	m_TaskRun = TASK_WAIT_SELECT_PROCESS;
						
						NG_Display();
						m_NG_Retry_Count++;*/
						MessageDisplay(1, "COM LED Time Out !!");
						m_LED_COM_PROCESS = COM_MODE_IDLE;
						
					}
				}
			}
			break;
		default:
			m_LED_COM_PROCESS = COM_MODE_IDLE;
			break;

		}

		//int m_PCB_COM_PROCESS;
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
						if (g_RunModeType == _ERROR_STOP)
						{

							m_GMES_ErrorName = _T("USB Communication Error");
							m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
							m_Deisplay_ErrorName = _T("USB Communication Error");

							m_Deisplay_ErrorName += _T("\r\n");
							m_Deisplay_ErrorName += _T("USB 通信 NG");// 频率  // 音量 // 版本
						//	m_Deisplay_ErrorName +=_T("USB 频率 音量  版本 左右音量差异 命令 检查  回答 NG");// 频率  // 音量 // 版本

							m_GMES_ErrorValue = _T("Ack Time Out");

							//m_Deisplay_ErrorName = m_GMES_ErrorName;
							m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//

							m_TaskRun = TASK_WAIT_SELECT_PROCESS;
							m_PCB_COM_PROCESS = COM_MODE_IDLE;
							//m_NG_Retry_Count++;
							NG_Display(m_GMES_ErrorName);
						}
						else
						{

							m_GMES_ErrorName = _T("USB Communication Error");
							m_GMES_ErrorName += gTestSeqData.TestStepList[m_nCurrentNumber].strStepName;
							m_Deisplay_ErrorName = _T("USB Communication Error");

							m_Deisplay_ErrorName += _T("\r\n");
							m_Deisplay_ErrorName += _T("USB 通信 NG");// 频率  // 音量 // 版本
						//	m_Deisplay_ErrorName +=_T("USB 频率 音量  版本 左右音量差异 命令 检查  回答 NG");// 频率  // 音量 // 版本

							m_GMES_ErrorValue = _T("Ack Time Out");

							//m_Deisplay_ErrorName = m_GMES_ErrorName;
							m_Deisplay_ErrorDetail = m_GMES_ErrorValue;//

							//m_TaskRun = TASK_WAIT_SELECT_PROCESS;
							m_PCB_COM_PROCESS = COM_MODE_IDLE;
							//m_NG_Retry_Count++;
							//NG_Display(m_GMES_ErrorName);
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
			&&(m_LED_COM_PROCESS == COM_MODE_IDLE)
			&&(m_PCB_COM_PROCESS == COM_MODE_IDLE)
			&&(m_EthernetMode  != ETHERNET_MODE_WAIT))
		{


			switch(m_PreTaskRun)
			{
			case TASK_RUN_IDLE:
			
		
				break;

		
			case TASK_RUN_START:
				m_nPreCurrentNumber = 0;//gTestSeqData.TestProcess.aSeqData[0].nSeqType;
				SetTimeCheck(2);//m_WaitCnt = 0;			
				m_PreTaskRun = TASK_RUN_PROCESS;			
			
				break;

			case TASK_RUN_PROCESS:
				CallPreProcess(m_nPreCurrentNumber);
		
				break;
			default:

				m_PreTaskRun = TASK_RUN_IDLE;
				break;
			}



		
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
				break;

		
			case TASK_WAIT_SELECT_PROCESS:
				if(m_NG_Retry_Count < 10)
				{
					//m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, _T(""), NULL, NULL, NULL, NULL);
					////m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
					//m_nCurrentProcess = 0;
					//m_nCurrentStep = 0;
					//m_NG_WaitFlag = 1;
					if(mpDlgResult->m_ReturnFlag == 1)
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
							m_nCurrentStep = 0;
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
			m_CtrlListMainProcess.SetItem(m_nCurrentNumber, 3, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		}

		//str.Format(_T("CNT : %d"), m_RunCounter);
		//SetDlgItemText(IDC_STATIC_CNT, str);
		SetTimer(1,5,NULL);
	}


	CDialog::OnTimer(nIDEvent);
}


#if 1
void CAcqVoltageSamples_IntClkDlg::CheckData(int CheckID)
{
	double     lbuf[4000];
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
		m_data[CheckID](0,i) = 1.0*sin(3.141592 / 500 * i)*(CheckID/12.0+1) ;
	}
#endif
//////////////////////////////////////
	lmaxSum = 0;
	for(i = 0; i < m_AI_SAMPLE_COUNT; i++)
	{
		lmaxSum += abs(m_data[CheckID](0,i));
	}
	lAverage = lmaxSum/ m_AI_SAMPLE_COUNT;
	
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

	for(i = 0; i < m_AI_SAMPLE_COUNT-3; i++)
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

	if(lSignalError)
	{
		Frequency = 0;
	}
	else
	{
	//	Frequency = 100000.0 / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
		Frequency = m_AI_SAMPLE_RATE / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
	
	}
/*	NI_SAMPLE_RATE		
 NI_SAMPLE_COUNT	*/	
	m_PPVoltage[CheckID] = PPVoltage;	
	m_Frequency[CheckID] = Frequency;

//	M_Vol[CheckID].Format(_T("P%02d : %4.0fmV"), CheckID, PPVoltage);
//	M_Frq[CheckID].Format(_T("F%02d : %4.0fHz"), CheckID, Frequency);
	UpdateData(FALSE);

	if((lStartNum < 0)||(lStartNum >= m_AI_SAMPLE_COUNT-NI_CHECK_COUNT-50))
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
	for(i = lStartNum; i < lStartNum+ m_AI_CHECK_COUNT; i++)
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
	for(i = 0; i < m_AI_CHECK_COUNT; i++)
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

		for(i = 0; i < m_AI_CHECK_COUNT; i++)
		{
			Check_data[CheckID](0,i) = Check_data[CheckID](0,i) * lScaleCoef;
		}
	}	
#endif
}
#else

void CAcqVoltageSamples_IntClkDlg::CheckData(int CheckID)
{
	double     lbuf[2000];
	double lMinCmp = 0, lmaxCmp = 0;

	double lMinSum = 0, lmaxSum = 0; 
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
	
	//CmpCoef1 = data[CheckID][0];
	memset(lMin, 0, sizeof(lMin));
	memset(lmax, 0, sizeof(lmax));
	//lMinCmp = -0.2;
	//lmaxCmp = 0.2;
	//m_data
	for(i = 0; i < 2999; i++)
	{
		CmpCoefBak = CmpCoefFwd;
		CmpCoefFwd = m_data[CheckID](0,i)+m_data[CheckID](0,i+1);
		if((-0.01 < CmpCoefFwd)&&(0.01 > CmpCoefBak)&&(lMinCmp <= -0.05))//&& (lmaxCmp >= 0.15))
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
			if((lMinCmp > CmpCoefFwd))
			{
				lMinCmp = CmpCoefFwd;
				lminEnable = 1;
			}
			if((lmaxCmp < CmpCoefFwd))
			{
				lmaxCmp = CmpCoefFwd;
				lmaxEnable = 1;
			}
			/*
			if((lMinCmp > CmpCoefFwd)&&(CmpCoefFwd < -0.001))
			{
				lMinCmp = CmpCoefFwd;
				lminEnable = 1;
			}
			if((lmaxCmp < CmpCoefFwd)&&(CmpCoefFwd > 0.001))
			{
				lmaxCmp = CmpCoefFwd;
				lmaxEnable = 1;
			}*/
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

		PPVoltage = (lmaxSum/lmaxCnt - lMinSum/lMinCnt)*1000 /2;
	}

	if(lSignalError)
	{
		Frequency = 0;
	}
	else
	{
		Frequency = 100000.0 / (lEndNum - lStartNum) * (lCheckCrossCnt-1);
	
	}
		
	m_PPVoltage[CheckID] = PPVoltage;	
	m_Frequency[CheckID] = Frequency;

//	M_Vol[CheckID].Format(_T("P%02d : %4.0fmV"), CheckID, PPVoltage);
//	M_Frq[CheckID].Format(_T("F%02d : %4.0fHz"), CheckID, Frequency);
	UpdateData(FALSE);

	if((lStartNum < 1)||(lStartNum >= 1000))
	{
		lStartNum = 0;
	}

	int j;
	j = 0;

	Check_data[CheckID].SetSize(1,2000);
	for(i = lStartNum; i < lStartNum+2000; i++)
	{
		
		Check_data[CheckID](0,j) = m_data[CheckID](0,i);
		j++;			
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

			if(m_nBalanceEnable[i] == 1)
			{
				MessageDisplay(1, "Cannot Check Volume Balance");
				MessageBox( "Sequence File NG\r\nCannot Check Volume Balance!", "Sequence File NG");
				CLOSE_Result_Display();
				m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
				m_LED_COM_PROCESS = COM_MODE_IDLE;
				m_PCB_COM_PROCESS = COM_MODE_IDLE;

				m_TaskRun = TASK_RUN_IDLE;
				m_cLbOkNg.put_Caption(_T("STOP"));//m_BarCode
				m_cLbOkNg.put_BackColor(0x0000FFFF);
			}
			continue;
		}

		if(m_nBalanceEnable[i] == 0)
		{
			m_BalanceOK[i] = 1;
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

		if(m_nBalanceEnable[i] == 1)
		{
			double lLarge,lSmall;

			if(m_PPVoltage[i] > m_PPVoltage[m_nBalanceChannel[i]])
			{
				lLarge = m_PPVoltage[i];
				lSmall = m_PPVoltage[m_nBalanceChannel[i]];
			}
			else
			{
				lLarge = m_PPVoltage[m_nBalanceChannel[i]];
				lSmall = m_PPVoltage[i];
			}

			//if(lLarge*(1+m_nBalanceValue[i]/100.) > lSmall)
			if((lLarge - lSmall) > lSmall*(m_nBalanceValue[i]/100.))
			{
				m_BalanceOK[i] = 0;
			}
			else
			{
				m_BalanceOK[i] = 1;
			}
		}
		else
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
#ifdef __OK_CHECK_FAST_MODE__
			if(m_ChannelOKCNT[i] > 1)
#else
			if(m_ChannelOKCNT[i] > 12)
#endif
			{
				m_ChannelOK[i] = 1;
			}
		}
		else
		{
			//m_ChannelOK[i] = 0;
		}

		m_CheckVoltage[i] = m_PPVoltage[i];
		m_CheckFrequency[i] = m_Frequency[i];

	}

	if((m_CheckEnable[0] )||(m_CheckEnable[1] ))
	{
		if((lOldchOk[0] != m_ChannelOK[0])||(lOldchOk[1] != m_ChannelOK[1]))
		{
			if((m_ChannelOK[0] == 1) && (m_ChannelOK[1] == 1) )//if(m_ChannelOK[0] && m_ChannelOK[1])
			{
				m_cLb_Test1.put_Caption(_T("O K"));
	/*			if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
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
				m_cLb_Test1.put_BackColor(0x0000FF00);
			}
			else
			{
				m_cLb_Test1.put_Caption(_T("WAIT"));
	//m_cLb_Test1.put_BackColor(0x0000FFFF);

				
		/*		if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
				{
					m_cLb_Test1.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
				{
					m_cLb_Test1.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
				{
					m_cLb_Test1.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
				{
					m_cLb_Test1.put_Caption(_T("WAIT"));
				}*/
				m_cLb_Test1.put_BackColor(0x0000FFFF);
			}
		}
	}
	if((m_CheckEnable[2] )||(m_CheckEnable[3] ))
	{
		if((lOldchOk[2] != m_ChannelOK[2])||(lOldchOk[3] != m_ChannelOK[3]))
		{
			if((m_ChannelOK[2] == 1) && (m_ChannelOK[3] == 1) )//if(m_ChannelOK[2] && m_ChannelOK[3])
			{
				m_cLb_Test2.put_Caption(_T("O K"));
			/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
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
				m_cLb_Test2.put_BackColor(0x0000FF00);
			}
			else
			{
				m_cLb_Test2.put_Caption(_T("WAIT"));
				/*if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
				{
					m_cLb_Test2.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
				{
					m_cLb_Test2.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
				{
					m_cLb_Test2.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
				{
					m_cLb_Test2.put_Caption(_T("WAIT"));
				}*/
				m_cLb_Test2.put_BackColor(0x0000FFFF);
			}
		}
	}

	if((m_CheckEnable[4] )||(m_CheckEnable[5] ))
	{
		if((lOldchOk[4] != m_ChannelOK[4])||(lOldchOk[5] != m_ChannelOK[5]))
		{
			if((m_ChannelOK[4] == 1) && (m_ChannelOK[5] == 1) )
			{
				m_cLb_Test3.put_Caption(_T("O K"));
			/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
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
				m_cLb_Test3.put_BackColor(0x0000FF00);
			}
			else
			{
				m_cLb_Test3.put_Caption(_T("WAIT"));
			/*	if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_1)
				{
					m_cLb_Test3.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_2)
				{
					m_cLb_Test3.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_3)
				{
					m_cLb_Test3.put_Caption(_T("WAIT"));
				}
				else if(gTestSeqData.TestProcess.aSeqData[m_nCurrentNumber].nSeqType == TEST_SEQ_TYPE_TEST_4)
				{
					m_cLb_Test3.put_Caption(_T("WAIT"));
				}*/
				m_cLb_Test3.put_BackColor(0x0000FFFF);
			}
		}
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
			m_cLb_Test1.put_Caption(_T("O K"));
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
			m_cLb_Test1.put_BackColor(0x0000FF00);
		}
		else
		{
			m_cLb_Test1.put_Caption(_T("N G"));
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
			m_cLb_Test1.put_BackColor(0x000000FF);
		}
		
	}
	if((m_CheckEnable[2] )||(m_CheckEnable[3] ))
	{
		
		if(m_ChannelOK[2] && m_ChannelOK[3])
		{
			m_cLb_Test2.put_Caption(_T("O K"));
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
			m_cLb_Test2.put_BackColor(0x0000FF00);
		}
		else
		{
			m_cLb_Test2.put_Caption(_T("N G"));
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
			m_cLb_Test2.put_BackColor(0x000000FF);
		}
		
	}

	if((m_CheckEnable[4] )||(m_CheckEnable[5] ))
	{
		
		if(m_ChannelOK[4] && m_ChannelOK[5])
		{
			m_cLb_Test3.put_Caption(_T("O K"));
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
			m_cLb_Test3.put_BackColor(0x0000FF00);
		}
		else
		{
			m_cLb_Test3.put_Caption(_T("N G"));
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
			m_cLb_Test3.put_BackColor(0x000000FF);
		}
		
	}
}

void CAcqVoltageSamples_IntClkDlg::TestFinishGMES()
{
	//ULONG lSetVal = 0x00;
	//CFileControl lFile;//SAVE LOG
	//lFile.ReadCountData();
	CString strTmp;
	CString strTmp2;
	//m_TEST_Result = 1;

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
	CString strTmp3;
	int lCount = 0;
	//strTmp3 = "TEST ";
	for (int i = 0; i < gTestSeqData.TestCnt; i++)
	{
		strTmp2.Format(" :%d=>", i+1);
		strTmp3 += strTmp2;
		if (gTestSeqData.TestStepList[i].m_Result == 0)
		{
			strTmp3 += "[NG] ";
			strTmp3 += gTestSeqData.TestStepList[i].strNG_Reason;
		}
		else if (gTestSeqData.TestStepList[i].m_Result == 1)
		{
			strTmp3 += "[OK] ";
		}
		else 
		{
			strTmp3 += "[SKIP] ";
		}

		strTmp3 += gTestSeqData.TestStepList[i].strStepName;
		if (strTmp.GetLength() + strTmp3.GetLength() > 200)
		{
			gSaveInfo.strTestProcessResult[lCount] = strTmp;
			lCount++;
			if (lCount >= 3)
				break;
			strTmp = "";
		}
		strTmp += strTmp3;
		strTmp3 = "";
	}
	//gSaveInfo.strTestDiscription = strTmp;
	if(lCount <= 2)
		gSaveInfo.strTestProcessResult[lCount] = strTmp;
	gSaveInfo.bMesSts = 0;
	if(m_GMES_CommError == 0)
	{
		GMES_Result_ReportSend();
		//gSaveInfo.bMesSts = 1;
	}
	else
	{
	}
	m_TaskRun = TASK_FINISH_PROCESS;
		
}

void CAcqVoltageSamples_IntClkDlg::TestFinish()
{
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
		if (g_RunModeType == _ERROR_AUTO)
		{
			NG_Display();
		}
		//NG_Display();
		//CLOSE_Result_Display();
		
	}

	CString str;
	unsigned long lCheck_Time = GetTimeCheck(4);
	str.Format(_T("%.1f (s)"), lCheck_Time/1000.0);
	m_CheckTimeLabel.put_Caption(str);

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

	 m_BarCode.put_Caption("");
	
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

	CString str = _T("");
	DlgModelSetupSeq dlg;
//	CDlgModelSetup dlg;
	m_Camera_Capture_Flag = 0;//

	if(m_ComPort.mPort_Opened == TRUE)
		m_ComPort.ClosePort();
		
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
		
	if(m_ComPortLED.mPort_Opened == TRUE)
		m_ComPortLED.ClosePort();
		

	int lrtn = dlg.DoModal();
	if((lrtn == IDOK)||(lrtn == IDCANCEL))
	{

		LoadTestData(gTestSeqData.strSeqFileName);

		//SetListControl();
		DisplayTestData();
		
		//m_TextModel.put_Text(gTestSeqData.strModelName);	

		CFileControl lFile;
		lFile.SaveINIModel();
		lFile.OpenModel(gTestSeqData.strModelName);

		CheckDigitalPort();
		GetRmtCodeList(gTestSeqData.strRemoconFileName);

		////str = _T("MODEL : ");
		str = gTestSeqData.strModelName;
		//m_TextModel.put_Text(str);
		m_cLbModel.put_Caption((LPCSTR)str);
		m_DO_Writedata = 0;
		if(gbManualScopeMode == 0)
		{
			SetChannelData(0);
			InitChannel();
		}

		CloseEthernetScocket() ;
		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		m_EthernetWaitCnt = 0;
		g_nPortReopen = 0;
		//gTestSeqData.bMesEnable = 1;	
		//if(gTestSeqData.bMesEnable)
		//{			
		//	m_UploadGmes = 1;
		//}
		//else
		//{
		//	m_UploadGmes = 0;
		//}
	}

	
	if(g_CameraFound == 1)
		m_Camera_Capture_Flag = 1;//m_Camera_Capture_Flag = 1;

		
	OpenComport();
	OpenComportPCB();
	OpenComportLED();
	OpenComportSCAN();
//	CString str;
	if(m_ComPort.mPort_Opened== FALSE)
	{
		str.Format(_T("MAIN COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
	
		MessageBox(str);
	}
	if(m_ComPortPCB.mPort_Opened == FALSE)
	{	
		str.Format(_T("Audio COM Port %d Open FAIL !!"), gTestSeqData.nPort_Pcb);
		MessageBox(str);
	}
	
	if(m_ComPortLED.mPort_Opened == FALSE)
	{
		str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);		
		MessageBox(str);
	}
	
	if(m_ComPortScanner.mPort_Opened == FALSE)
	{	
		str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);		
		MessageBox(str);
	}

	OnBnClickedButtonFreqSet();
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
		
	if(m_ComPortLED.mPort_Opened == TRUE)
		m_ComPortLED.ClosePort();
		
	

	if(dlg.DoModal() == IDOK)
	{
	}
	OpenComport();
	OpenComportPCB();
	OpenComportLED();
	OpenComportSCAN();
	CString str;
	if(m_ComPort.mPort_Opened== FALSE)
	{
		str.Format(_T("MAIN COM Port %d Open FAIL !!"),  g_nPort_Set);
	
		MessageBox(str);
	}
	if(m_ComPortPCB.mPort_Opened == FALSE)
	{	
		str.Format(_T("Audio COM Port %d Open FAIL !!"), gTestSeqData.nPort_Pcb);
		MessageBox(str);
	}
	
	if(m_ComPortLED.mPort_Opened == FALSE)
	{
		str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED);		
		MessageBox(str);
	}
	
	if(m_ComPortScanner.mPort_Opened == FALSE)
	{	
		str.Format(_T("SCANNER COM Port %d Open FAIL !!"),  g_nPort_Scanner);		
		MessageBox(str);
	}

	//if(g_CameraFound == 1)
	//	m_Camera_Capture_Flag = 1;
	//for(int i = 0; i< 6; i++)
	//			m_graph[i].Plots.RemoveAll();
	if(gbManualScopeMode == 0)
	{
		InitClearChannel();
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

}

void	CAcqVoltageSamples_IntClkDlg::SendData(BYTE *lbuf, int lcnt)
{

	m_MainPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_ComAck =COM_ACK_WAIT;
	m_ComWaitCnt = 0;
	m_ResendCnt = 0;

	memcpy(m_SendBuf, lbuf, lcnt); 
	m_SendCnt = lcnt;
	ComSend();
}


void CAcqVoltageSamples_IntClkDlg::ComSend()//void CAcqVoltageSamples_IntClkDlg::OpenComport()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
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
		
	}
}

void CAcqVoltageSamples_IntClkDlg::ComPCBSend()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
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
}


void CAcqVoltageSamples_IntClkDlg::OpenComport()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
	if(m_ComPort.InitPort(this, g_nPort_Set, g_nBaud_Set, 'N', 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPort.StartMonitoring();
	}
	else
	{
		str.Format(_T("MAIN COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}
}

void CAcqVoltageSamples_IntClkDlg::OpenComportPCB()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	if(gTestSeqData.nParity_Pcb > 2)
	{
		gTestSeqData.nParity_Pcb = 0;
	}

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
	if(m_ComPortPCB.InitPort(this, gTestSeqData.nPort_Pcb, gTestSeqData.nBaud_Pcb, lParityChar[gTestSeqData.nParity_Pcb], 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPortPCB.StartMonitoring();
	}
	else
	{
		str.Format(_T("Audio COM Port %d Open FAIL !!"), gTestSeqData.nPort_Pcb);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}

	m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
}

void CAcqVoltageSamples_IntClkDlg::OpenComportLED()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	if(g_nParity_LED > 2)
	{
		g_nParity_LED = 0;
	}
	if(m_ComPortLED.mPort_Opened)
	{
		m_ComPortLED.ClosePort();
	}
//	if(m_ComPortLED.InitPort(this, g_nPort_LED, g_nBaud_LED, 'N', 8, 1, EV_RXCHAR, 4096 ))
	if(m_ComPortLED.InitPort(this, g_nPort_LED, g_nBaud_LED, lParityChar[g_nParity_LED], 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPortLED.StartMonitoring();
	}
	else
	{
		str.Format(_T("LED COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}

	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_LED;
}


void CAcqVoltageSamples_IntClkDlg::OpenComportSCAN()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	if(g_nParity_Scanner > 2)
	{
		g_nParity_LED = 0;
	}
	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}
//	if(m_ComPortLED.InitPort(this, g_nPort_LED, g_nBaud_LED, 'N', 8, 1, EV_RXCHAR, 4096 ))
	if(m_ComPortScanner.InitPort(this, g_nPort_Scanner, g_nBaud_Scanner, lParityChar[g_nParity_Scanner], 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPortScanner.StartMonitoring();
	}
	else
	{
		str.Format(_T("SCANNER  COM Port %d Open FAIL !!"),  g_nPort_Scanner, g_nBaud_Scanner);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}
	m_ComPortScanner.m_RxMessageID = WM_COMM_RXCHAR_SCAN;
}



long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	if((m_RecvCnt < 0)||(m_RecvCnt > 4095))
		m_RecvCnt = 0;

	memcpy(lbuf,(void *)lParam,lcnt);

	for(int i = 0; i < lcnt; i++)
	{
		m_RecvBuf[m_RecvCnt++] = lbuf[i];
		if(m_RecvCnt > 4095)
			m_RecvCnt = 0;
	}

	if(m_RecvCnt > 2)
	{
		if(m_RecvBuf[0] == 0x02)
		{
			if(m_RecvCnt >= 10)
			{

				if(strncmp((char *)&m_RecvBuf[1], "DREADY", 6) == 0)
				{
					m_ComAck = COM_ACK_OK;
					m_RecvCnt = 0;
					m_ComSMAV_1100APOk = 1;
				}
				else if(strncmp((char *)&m_RecvBuf[1], "DBUSY ", 6) == 0)
				{
					m_ComAck = COM_ACK_BUSY;
					m_RecvCnt = 0;
				}
				
				else
				{
					m_RecvCnt = 0;
				}
			}
		}
		else if(m_RecvBuf[0] == '@')
		{
			if(m_RecvCnt >= 5) 
			{
				if(m_RecvBuf[4] == '#')
				{
	/*			
		int m_LAN_CheckOK;
		int m_USB1_CheckOK;
		int m_USB2_CheckOK;
	*/
					if(m_RecvBuf[1] == '3')
					{
						m_LAN_CheckOK = 1;
					}
					else
					{
						m_LAN_CheckOK = 0;
					}

								
					if(m_RecvBuf[2] == '7')
					{
						m_USB1_CheckOK = 1;
					}
					else if(m_RecvBuf[2] == '0')
					{
						m_USB1_CheckOK = 0;//m_USB2_CheckOK = 0;
					}
						
					if(m_RecvBuf[3] == '7')
					{
						m_USB2_CheckOK = 1;
					}
					else if(m_RecvBuf[2] == '0')
					{
						m_USB2_CheckOK = 0;
					}

					m_RecvCnt = 0;
				}
				else if((m_RecvBuf[1]== 'D') && (m_RecvBuf[1]== 'M') && (m_RecvBuf[1]== 'A') && (m_RecvBuf[1]== 'C') && (m_RecvBuf[1]== '_'))
				{
					m_RecvCnt = 0;
				}
				else
				{
					m_RecvCnt = 0;
				}
			}
		}
		else
		{
			m_RecvCnt = 0;
		}
	}

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
		
	

	while(m_RecvCntPCB > 2)
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

				if(m_RecvBufPCB[m_RecvBufPCB[1]+1] == lCheckSum)
				{
					m_PCBComAck = COM_ACK_OK;

					if (m_RecvBufPCB[3] == _COMMAND_WIFI_MAC_READ)
					{

						if (m_RecvBufPCB[1] == 20)
						{
							char wifibuffer[32];
							memcpy(wifibuffer, &m_RecvBufPCB[4], 17);
							if ((wifibuffer[2] == ':')
								&& (wifibuffer[5] == ':')
								&& (wifibuffer[8] == ':')
								&& (wifibuffer[11] == ':')
								&& (wifibuffer[14] == ':')
								)
							{
								wifibuffer[17] = 0;
								gSaveInfo.strWifiMacAddress = wifibuffer;
								m_PCB_CheckOK = 1;
							}
							else
							{
								m_PCB_CheckOK = 2;
							}
						}
						else
						{
							m_PCB_CheckOK = 2;
						}
					}
					else if (m_RecvBufPCB[3] == _COMMAND_BT_MAC_READ)
					{

						if (m_RecvBufPCB[1] == 20)
						{
							char wifibuffer[32];
							memcpy(wifibuffer, &m_RecvBufPCB[4], 17);
							if ((wifibuffer[2] == ':')
								&& (wifibuffer[5] == ':')
								&& (wifibuffer[8] == ':')
								&& (wifibuffer[11] == ':')
								&& (wifibuffer[14] == ':')
								)
							{
								wifibuffer[17] = 0;
								gSaveInfo.strBTMacAddress = wifibuffer;
								m_PCB_CheckOK = 1;
							}
							else
							{
								m_PCB_CheckOK = 2;
							}
						}
						else
						{
							m_PCB_CheckOK = 2;
						}
					}
					else
					{
						for(int i = 0; i < m_UartOkAckDataCnt; i++)
						{
							
							m_UartREADData[i] = m_RecvBufPCB[4+i];		
							if(m_RecvBufPCB[4+i] == m_UartOkAckData[i])
							{
								if(m_PCB_CheckOK == 0)
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
				}
				else
				{
					m_PCBComAck = COM_ACK_BUSY;
				}


				CString strtmp;
				CString strReceive ;

				for(int i = 0; i < m_RecvCntPCB; i++)
				{
					strtmp.Format(_T("0x%02x "), m_RecvBufPCB[i]);
					strReceive += strtmp;
				}	
#ifdef __MESSAGE_DEBUG_MODE__
				MessageDisplay(2, strReceive);//SetDlgItemText(IDC_EDIT_READ_DATA,strReceive.GetBuffer());
#endif
			//	m_PCBComAck = COM_ACK_OK;
				m_RecvCntPCB = 0;
							
			}
			else
			{
				break;
			}
		}
		else
		{
			int lFindBB = m_RecvCntPCB+1;
				
			for (int i = 0; i < m_RecvCntPCB; i++)
			{
				if (m_RecvBufPCB[i] == 0xBB)
				{
					lFindBB = i;
					for (int j = i; j< m_RecvCntPCB; j++)
					{
						m_RecvBufPCB[j - i] = m_RecvBufPCB[j];
					}
					
					break;
				}
			}

			if (lFindBB > m_RecvCntPCB)
			{
				m_RecvCntPCB = 0;
				break;
			}
			else
			{
				m_RecvCntPCB = m_RecvCntPCB - lFindBB;
			}
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

					m_LEDReadData[0] = m_RecvBufLED[5];
					m_LEDReadData[1] = m_RecvBufLED[6];
					m_LEDReadData[2] = m_RecvBufLED[7];
					m_LEDReadData[3] = m_RecvBufLED[8];
					
					if((m_LEDOkAckData[0] == m_RecvBufLED[5])
						&&(m_LEDOkAckData[1] == m_RecvBufLED[6])
						&&(m_LEDOkAckData[2] == m_RecvBufLED[7])
						&&(m_LEDOkAckData[3] == m_RecvBufLED[8]))
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
		if (gTestSeqData.bMesEnable == 1)
		{
			m_cLb_ComMainGmes.put_BackColor(0x0000FF00);
		}
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

				SetSystemTime(&datetime); 
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
				g_strModelName = str1;

				lpos = l_Receivestr.Find("<SUFFIX>");	//</EQPID>	
				str1 = l_Receivestr.Mid(lpos+strlen("<SUFFIX>"));
				lpos = str1.Find("</SUFFIX>");	//</EQPID>	
				str1 = str1.Left(lpos);
				g_strModelSuffix = str1;

				str1 = g_strModelName;
				str1 += ".";
				str1 += g_strModelSuffix;

				m_EthernetAck = 1;
				GMESProductDataAcknowledge();//S6F6		
				if (g_MesAutoChangeModel == 1)
				{

				
					if(gTestSeqData.strModelName.Find(str1) >= 0)
					{
					}
					else
					{
						ChangeModel(str1);
					}

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
/*<EIFVERSION="1.8"ID="S9F3"NAME="UnrecognizedStreamType">
<ELEMENT>
<EQPID></EQPID>
</ELEMENT>
</EIF>*/
			}
		}

		m_strEthernetReceive = "";


	}


	return 0;
}

void CAcqVoltageSamples_IntClkDlg::OnDestroy()
{
	CDialog::OnDestroy();
	gbShutdown = true;
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

	if(mpDlgResult != NULL)
		delete mpDlgResult;

	if(mpDlgBarcode != NULL)
		delete mpDlgBarcode;

	if(mpDlgSimpleInform != NULL)
		delete mpDlgSimpleInform;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	gbShutdown = true;

	Sleep(200);


	//Sleep(10);
	//if( vcap.isOpened() )
	//{

	//	vcap.release();
	//	
	//}


	CDialog::OnOK();
}


void CAcqVoltageSamples_IntClkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnLButtonDown(nFlags, point);
}


void CAcqVoltageSamples_IntClkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnLButtonUp(nFlags, point);
}



void CAcqVoltageSamples_IntClkDlg::SetTimeCheck(int  lIndex)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	for (int i = 0; i < 64; i++)
	{
		if ((mstartT[i] == 0) || (lIndex == i))
		{
			mstartT[i] = GetTickCount();
		}
	}
	
}


unsigned long  CAcqVoltageSamples_IntClkDlg::GetTimeCheck(int  lIndex)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//MessageDisplay(0, _T("Model Mouse Up!!"));

	unsigned long lCheckTime = GetTickCount();
	unsigned long lCheckDelayTime = 0;



	for (int i = 0; i < 64; i++)
	{
		if (lIndex == i)
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
		str.Format(_T("%.1f (s)"), lCheck_Time/1000.0);
		m_CheckTimeLabel.put_Caption(str);
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

	//lstrModelname  = _T("TEST");
	CFileControl lFile;
	lFile.OpenModelSeq(lstrModelname);

	
}

void CAcqVoltageSamples_IntClkDlg::DisplayTestData()
{
	SetSubListControl();
	
}



void CAcqVoltageSamples_IntClkDlg::SetListControl()
{
	
//	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListMainProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListMainProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 40); 
	m_CtrlListMainProcess.InsertColumn(1, _T("STEP"), LVCFMT_CENTER, 205);// 리스트 행 추가
	m_CtrlListMainProcess.InsertColumn(2, _T("RESULT"), LVCFMT_CENTER, 60);// 리스트 행 추가
	m_CtrlListMainProcess.InsertColumn(3, _T("T/T"), LVCFMT_CENTER, 50);// 리스트 행 추가
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
	m_CtrlListMainProcess.SetFont(font);

	delete font;
	
}


void CAcqVoltageSamples_IntClkDlg::SetSubListControl()
{
	
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
}

//void CAcqVoltageSamples_IntClkDlg::ProcessGetImage()
//{
//	//if(g_CameraFound)
//	//{
//
//	////	vcap >> gCuptureimage;	
//	//	if(m_Camera_Capture_Flag == 1)
//	//	{
//	//		src_Mat = gCuptureimage;		
//	//	}	
//	//}
//}


//void CAcqVoltageSamples_IntClkDlg::ProcessTemplate()
//{
////	if(g_CameraFound == 0)
////		return;
////	double min, max;
////	double smin = 100, smax = 0;
////	CString csMin,csMax;
////
////	cv::Point left_top;
////	
////	cv::Size Size;
////	Size.width = src_Mat.cols;
////	Size.height = src_Mat.rows;
////	
////	Mat showMat;
////
//////	namedWindow("image");
////
////	int cnt = 20;
////
////	int i = 0;
////	//for (  i = 0 ; i < cnt ; i++ )
////	{
////		Mat image(src_Mat);
////		//IplImage* image = cvCreateImage ( Size, src->depth, src->nChannels );
////		Mat imageGray(Size.height,Size.width,1);
////		//IplImage* imageGray = cvCreateImage ( Size, 8,1 );
////
////		cv::resize(src_Mat,image,Size);
////		//cvResize(src,image);
////
////		cvtColor(image,imageGray,CV_BGR2GRAY);
////		//cvCvtColor(image,imageGray,CV_BGR2GRAY);
////		CString str = PATH_BASE_DIR;
////		str += _T("\\Image\\");
////		CString lRefFile = str;
////		lRefFile +=  m_strCameraCheckIMGfile;//"portable.jpg";//lRefFile +=  "SearchImage.jpg";
////
////
////		Mat B = imread(lRefFile.GetBuffer(), -1); 
////	//	Mat B = imread("template1.jpg", -1); 
////		//IplImage *B = cvLoadImage("template\\template1.jpg", -1); 
////
////		Mat BGray(B.rows,B.cols,1);
////		//IplImage *BGray = cvCreateImage(cvGetSize(B), 8, 1);
////
////		cv::cvtColor(B,BGray,CV_BGR2GRAY);
////		//cvCvtColor(B,BGray,CV_BGR2GRAY);
////
////		Mat C(cv::Size( image.cols - B.cols+1, image.rows - B.rows+1 ) ,CV_32FC1 , 1);
////		//IplImage *C = cvCreateImage( cvSize( image->width - B->width+1, image->height - B->height+1 ), IPL_DEPTH_32F, 1 ); // 상관계수를 구할 이미지(C)
////
////		cv::matchTemplate(imageGray, BGray, C, CV_TM_CCOEFF_NORMED); 
////		//cvMatchTemplate(imageGray, BGray, C, CV_TM_CCOEFF_NORMED); // 상관계수를 구하여 C 에 그린다.
////		
////		cv::minMaxLoc(C, &min, &max, NULL, &left_top);
////		//cvMinMaxLoc(C, &min, &max, NULL, &left_top); // 상관계수가 최대값을 값는 위치 찾기 
////
////		showMat = image;
////
////		if ( max > 0.6 )
////		{
////			//매칭결과 이미지 잘라서 다른 이미지로 옮기기
////			Template_Rslt = showMat(cv::Rect(left_top.x, left_top.y, B.cols, B.rows));
////
////	//		i = cnt;
////
////	//		imshow("Template Result",Template_Rslt);
////
////			ProcessImage();
////		}
////		else
////		{
////			csMax.Format("NotFound:%.0f",max*100);
////			m_cLb_Camera.put_Caption(csMax);
////		}
////		
////
////#ifdef __IMAGE_DEBUG__
////		cv::rectangle(showMat,cv::Rect(left_top.x, left_top.y, B.cols, B.rows), CV_RGB(255,255,255),2);
////		
////		if(min < smin)
////			smin = min;
////		if(max > smax)
////			smax = max;
////
////		CString csMin,csMax;
////		csMin.Format("Min : %f",smin);
////		csMax.Format("Max : %f",smax);
////		string strMin = csMin;
////		string strMax = csMax;
////	
////		cv::putText(image,strMin,cv::Point(0,50),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);
////		cv::putText(image,strMax,cv::Point(0,80),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);
////		imshow("image",showMat);
////		cv::waitKey(1);
////
////#endif
////		////템플릿 매칭값이 충분하지 못함
////		//if ( i < cnt/2 )
////		//{
////		//	//사이즈값 축소
////		//	Size.width*=0.99;
////		//	Size.height*=0.99;
////		//}
////		//else if ( i == cnt/2 )
////		//{
////		//	Size.width = src_Mat.cols;
////		//	Size.height = src_Mat.rows;
////		//}
////		//else
////		//{
////		//	Size.width*=1.01;
////		//	Size.height*=1.01;
////		//}
////		
////	}
////	
//	
//}
//
//void CAcqVoltageSamples_IntClkDlg::ProcessImage()
//{
////		if(g_CameraFound == 0)
////		return;
////	
////	double min, max;
////	double smin = 100, smax = 0;
////	cv::Point left_top;
////	
////	cv::Size Size;
////	Size.width = src_Mat.cols;
////	Size.height = src_Mat.rows;
////	
////	Mat showMat;
////
//////		Mat image(src_Mat);
////	Mat image(Template_Rslt);//Template_Rslt	
////	Mat imageGray(Size.height,Size.width,1);
////	
////	//cv::resize(src_Mat,image,Size);
////	//cvResize(src,image);
////
////	cvtColor(image,imageGray,CV_BGR2GRAY);
////		//cvCvtColor(image,imageGray,CV_BGR2GRAY);
////	CString str = PATH_BASE_DIR;
////	str += _T("\\Image\\");
////	CString lRefFile = str;
////	lRefFile +=  m_strCameraCheckIMGfile;//"portable_terget.jpg";
////	lRefFile = lRefFile.Left(lRefFile.Find(".jpg"));
////	lRefFile += _T("_target.jpg");//
////
////
////	Mat B = imread(lRefFile.GetBuffer(), -1); 
////	Mat BGray(B.rows,B.cols,1);
////
////	cv::cvtColor(B,BGray,CV_BGR2GRAY);
////
////	Mat C(cv::Size( image.cols - B.cols+1, image.rows - B.rows+1 ) ,CV_32FC1 , 1);
////
////	cv::matchTemplate(imageGray, BGray, C, CV_TM_CCOEFF_NORMED); 
////	cv::minMaxLoc(C, &min, &max, NULL, &left_top);
////
////	showMat = image;
////	Mat lTarget;
////
////	if(m_Match_Percent < 50)
////		m_Match_Percent = 60;
////	else if(m_Match_Percent > 95)
////		m_Match_Percent = 95;
////	
////	double lmatch = m_Match_Percent/100.0;
////
////	if ( max > lmatch )
////	{
////	//  매칭결과 이미지 잘라서 다른 이미지로 옮기기
////		 lTarget = showMat(cv::Rect(left_top.x, left_top.y, B.cols, B.rows));
////
////#if 1//def __IMAGE_DEBUG__
////	//	imshow("Match Target",lTarget);	
////
////
////		CString csMin_Max;
////		csMin_Max.Format("Max:%.0f",max*100);
////	//	MessageDisplay(2, csMin_Max);
////
////		
////		m_cLb_Camera.put_Caption(csMin_Max);
////
////#endif
////		m_Camera_CheckOK = 1;
////			
////	}
////	else
////	{
////		m_Camera_CheckOK = 0;
////
////#if 1//def __IMAGE_DEBUG__
////	
////
////		CString csMin_Max;
////		csMin_Max.Format("Max:%.0f",max*100);
////	//	MessageDisplay(2, csMin_Max);
////
////		
////		m_cLb_Camera.put_Caption(csMin_Max);
////
////#endif
////	}
////	
////	cv::rectangle(showMat,cv::Rect(left_top.x, left_top.y, B.cols, B.rows), CV_RGB(255,255,0),2);
////	DisplayImage(&IplImage(showMat));
////#ifdef __IMAGE_DEBUG__
////		
////	/*if(min < smin)
////		smin = min;
////	if(max > smax)
////		smax = max;
////
////	CString csMin,csMax;
////	csMin.Format("Min : %f",smin);
////	csMax.Format("Max : %f",smax);
////	string strMin = csMin;
////	string strMax = csMax;
////	
////	cv::putText(image,strMin,cv::Point(0,50),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);
////	cv::putText(image,strMax,cv::Point(0,80),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);*/
////	imshow("Result Image",showMat);
////	cv::waitKey(1);
////
////
////	
////#endif
////	/*
////	double min, max;
////	double smin = 100, smax = 0;
////	cv::Point left_top;
////	
////	cv::Size Size;
////	Size.width = src_Mat.cols;
////	Size.height = src_Mat.rows;
////	
////	Mat showMat;
////
//////		Mat image(src_Mat);
////	Mat image(Template_Rslt);//Template_Rslt	
////	Mat imageGray(Size.height,Size.width,1);
////	
////	cv::resize(src_Mat,image,Size);
////	//cvResize(src,image);
////
////	cvtColor(image,imageGray,CV_BGR2GRAY);
////		//cvCvtColor(image,imageGray,CV_BGR2GRAY);
////	CString str = PATH_BASE_DIR;
////	str += _T("\\Image\\");
////	CString lRefFile = str;
////	lRefFile +=  "SearchImageTarget.jpg";
////
////
////	Mat B = imread(lRefFile.GetBuffer(), -1); 
////	Mat BGray(B.rows,B.cols,1);
////
////	cv::cvtColor(B,BGray,CV_BGR2GRAY);
////
////	Mat C(cv::Size( image.cols - B.cols+1, image.rows - B.rows+1 ) ,CV_32FC1 , 1);
////
////	cv::matchTemplate(imageGray, BGray, C, CV_TM_CCOEFF_NORMED); 
////	cv::minMaxLoc(C, &min, &max, NULL, &left_top);
////
////	showMat = image;
////
////	if ( max > 0.6 )
////	{
////	//  매칭결과 이미지 잘라서 다른 이미지로 옮기기
////	//	Template_Rslt = showMat(cv::Rect(left_top.x, left_top.y, B.cols, B.rows));
////	//	imshow("Template Result",Template_Rslt);		
////	}
////
////	cv::rectangle(showMat,cv::Rect(left_top.x, left_top.y, B.cols, B.rows), CV_RGB(255,255,255),2);
////		
////	if(min < smin)
////		smin = min;
////	if(max > smax)
////		smax = max;
////
////	CString csMin,csMax;
////	csMin.Format("Min : %f",smin);
////	csMax.Format("Max : %f",smax);
////	string strMin = csMin;
////	string strMax = csMax;
////	
////	cv::putText(image,strMin,cv::Point(0,50),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);
////	cv::putText(image,strMax,cv::Point(0,80),FONT_HERSHEY_SIMPLEX,1.0,CV_RGB(255,255,255),2);
////	imshow("image",showMat);
////	cv::waitKey(1);
////
////	*/
//
//}


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

//
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

//void CAcqVoltageSamples_IntClkDlg::OnStnDblclickStaticPic()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	
//}


//void CAcqVoltageSamples_IntClkDlg::OnStnClickedStaticPic()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDlgImage ldlg;
//	ldlg.DoModal();
//}
BEGIN_EVENTSINK_MAP(CAcqVoltageSamples_IntClkDlg, CDialog)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_CAMREA_NAME, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelCamreaName, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabel, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG1, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelOK1, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG2, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelOK2, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_COM_GMES, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelComGmes, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_COM_MAIN, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelComMain, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG1, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelOK1, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL__OKNG2, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelOK2, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_CHECK_TIME, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelCheckTime, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_NG_CNT, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelNgCnt, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_MANAGER, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelManager, VTS_DISPATCH)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_COM_GMES, DISPID_CLICK, CAcqVoltageSamples_IntClkDlg::ClickLabelComGmes, VTS_NONE)
	ON_EVENT(CAcqVoltageSamples_IntClkDlg, IDC_LABEL_BARCODE, DISPID_DBLCLICK, CAcqVoltageSamples_IntClkDlg::DblClickLabelBarcode, VTS_DISPATCH)
END_EVENTSINK_MAP()


void CAcqVoltageSamples_IntClkDlg::ClickLabelCamreaName()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//if(g_CameraFound == 0)
	{
		return;
	}
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

	ComLedRead();

	m_LED_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_LEDComAck =COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	
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
		mpDlgResult->SetWindowPos(this,rectP.left+ 270,rectP.top+150,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);


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
		mpDlgResult->SetWindowPos(this,rectP.left+ 270,rectP.top+150,rect.Width(),rect.Height(),SWP_ASYNCWINDOWPOS);

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
	
	if(m_TaskRun != TASK_RUN_IDLE) 
	{
		MessageBox("TEST PROCESSING");
		return;
	}

	if(gbManualScopeMode == 1)		
	{

		gbManualScopeMode = 0;
		SetGuiPos(gbManualScopeMode);

		SetChannelData(0);
		
		InitChannel();
		if(m_InitAiChannel == 0)
		{
			MessageBox("Audio Capture Card INIT FAIL!!");
			g_NIAuioBoardFail = 1;//AUDIO Board Fail
		}

		m_cLbOkNg.put_Caption(_T("WAIT"));
		m_cLbOkNg.put_BackColor(0x0000FFFF);
		Invalidate();
	}
	else
	{
		gbManualScopeMode = 1;
		SetGuiPos(gbManualScopeMode);	
		
		
		SetChannelDataManual(0);
		
		InitChannel();
		if(m_InitAiChannel == 0)
		{
			MessageBox("Audio Capture Card INIT FAIL!!");
			g_NIAuioBoardFail = 1;//AUDIO Board Fail
		}
		m_cLbOkNg.put_Caption(_T("SCOPE MODE"));
		m_cLbOkNg.put_BackColor(0x0000FFFF);
		
		m_cLb_Test1.put_Caption(_T("MIC1"));
		m_cLb_Test1.put_BackColor(0x0000FFFF);
	
		m_cLb_Test2.put_Caption(_T("MIC2"));
		m_cLb_Test2.put_BackColor(0x0000FFFF);
	


		Invalidate();
	}
}


void CAcqVoltageSamples_IntClkDlg::SetGuiPos(int IsScopeMode)
{
	if(IsScopeMode)
	{


		int Xoffset = -20;
	//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
		m_cComboName[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_cComboName[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		m_cLb_Test1.SetWindowPos(NULL,235+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		//m_cLb_Test1.SetWindowPos(NULL,1600+35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		//m_cLb_Test1.put_Caption("MIC1");
		//m_cLb_Test1.put_BackColor(0x0000FFFF);
	//	m_cLb_Test1.Invalidate();

		/////////////
		m_cComboName[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_cComboName[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		//m_cLb_Test2.SetWindowPos(NULL,1600+345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		m_cLb_Test2.SetWindowPos(NULL,545+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		//m_cLb_Test2.put_Caption("MIC2");
		//m_cLb_Test2.put_BackColor(0x0000FFFF);
	/*	RECT lRect;
		lRect.top = 540+95;
		lRect.bottom = 540+95+30;
		lRect.left = 35+Xoffset;
		lRect.top = 35+Xoffset +345+ 80+300+80 ;
		InvalidateRect(&lRect);*/
	//	m_cLb_Test2.Invalidate();

		m_cComboName[4].SetWindowPos(NULL,655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[4].SetWindowPos(NULL,775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[4].SetWindowPos(NULL,865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_cComboName[5].SetWindowPos(NULL,655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[5].SetWindowPos(NULL,775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[5].SetWindowPos(NULL,865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		m_cLb_Test3.SetWindowPos(NULL,1600+655+80*2+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
	//m_cLb_Test3.SetWindowPos(NULL,655+80*2+Xoffset, 540+95, 100,30,SWP_ASYNCWINDOWPOS);

		m_cComboName[6].SetWindowPos(NULL,965+80*3+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[6].SetWindowPos(NULL,1600+965+80*3+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[6].SetWindowPos(NULL,1085+80*3+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[6].SetWindowPos(NULL,1175+80*3+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,965+80*3+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_cComboName[7].SetWindowPos(NULL,965+80*3+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_NameLabel[7].SetWindowPos(NULL,1600+965+80*3+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[7].SetWindowPos(NULL,1085+80*3+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[7].SetWindowPos(NULL,1175+80*3+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,965+80*3+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);

		m_CtrlListMainProcess.SetWindowPos(NULL,1600+1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
		GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 380, 110,SWP_ASYNCWINDOWPOS);

		
		m_cLabelCableManager.SetWindowPos(NULL,1205+Xoffset, 575+95, 220, 30,SWP_ASYNCWINDOWPOS);
		m_cLabelCableMessage.SetWindowPos(NULL,1205+Xoffset, 575+125, 220, 80,SWP_ASYNCWINDOWPOS);

	
		//965
	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125

	//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
		m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+255,35,SWP_ASYNCWINDOWPOS);

		//95


		m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
		m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
		/*	
		m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
		m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
	*/
		m_CheckTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 688+95, 110,18,SWP_ASYNCWINDOWPOS);
		m_CycleTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 707+95, 110,18,SWP_ASYNCWINDOWPOS);
		m_CheckTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 688+95, 85,18,SWP_ASYNCWINDOWPOS);
		m_CycleTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 707+95, 85,18,SWP_ASYNCWINDOWPOS);

	

		m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 720+240,110,SWP_ASYNCWINDOWPOS);

	
		m_LanLabelName.SetWindowPos(NULL,35+Xoffset, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_Usb1LabelName.SetWindowPos(NULL,35+Xoffset, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_Usb2LabelName.SetWindowPos(NULL,35+Xoffset, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_CameraLabelName.SetWindowPos(NULL,35+Xoffset, 659+95, 80,26,SWP_ASYNCWINDOWPOS);

		m_cLb_Lan.SetWindowPos(NULL,115+Xoffset, 575+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Usb1.SetWindowPos(NULL,115+Xoffset, 603+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Usb2.SetWindowPos(NULL,115+Xoffset, 631+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Camera.SetWindowPos(NULL,115+Xoffset, 659+95, 110,26,SWP_ASYNCWINDOWPOS);

	}
	else
	{
		int Xoffset = -20;
	//	GetDlgItem(IDC_LABEL__NAME1)->SetWindowPos(NULL,60, 105, 160,60,SWP_ASYNCWINDOWPOS);
		m_NameLabel[0].SetWindowPos(NULL,35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[0].SetWindowPos(NULL,1600+35+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[0].SetWindowPos(NULL,155+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[0].SetWindowPos(NULL,245+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH0)->SetWindowPos(NULL,35+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_NameLabel[1].SetWindowPos(NULL,35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[1].SetWindowPos(NULL,1600+35+Xoffset,			345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[1].SetWindowPos(NULL,155+10+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[1].SetWindowPos(NULL,245+45+Xoffset,		345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH1)->SetWindowPos(NULL,35+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		m_cLb_Test1.SetWindowPos(NULL,35+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		m_cLb_Test1.put_Caption("WAIT");
		/////////////
		m_NameLabel[2].SetWindowPos(NULL,345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[2].SetWindowPos(NULL,1600+345+80+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[2].SetWindowPos(NULL,465+80+10+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[2].SetWindowPos(NULL,555+80+45+Xoffset, 150, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH2)->SetWindowPos(NULL,345+80+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_NameLabel[3].SetWindowPos(NULL,345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[3].SetWindowPos(NULL,1600+345+80+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[3].SetWindowPos(NULL,465+80+10+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[3].SetWindowPos(NULL,555+80+45+Xoffset, 345+45,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH3)->SetWindowPos(NULL,345+80+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		m_cLb_Test2.SetWindowPos(NULL,345+80+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);
		m_cLb_Test2.put_Caption("WAIT");

		m_NameLabel[4].SetWindowPos(NULL,655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[4].SetWindowPos(NULL,1600+655+80*2+Xoffset, 150, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[4].SetWindowPos(NULL,775+80*2+10+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[4].SetWindowPos(NULL,865+80*2+45+Xoffset, 150,  90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH4)->SetWindowPos(NULL,655+80*2+Xoffset, 180, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_NameLabel[5].SetWindowPos(NULL,655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[5].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[5].SetWindowPos(NULL,775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[5].SetWindowPos(NULL,865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH5)->SetWindowPos(NULL,655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);
		m_cLb_Test3.SetWindowPos(NULL,655+80*2+Xoffset, 540+95, 300+80,30,SWP_ASYNCWINDOWPOS);

		m_NameLabel[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[6].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[6].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[6].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH6)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);


		m_NameLabel[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_cComboName[7].SetWindowPos(NULL,1600+655+80*2+Xoffset, 345+45, 120+10, 30,SWP_ASYNCWINDOWPOS);
		m_FreqLabel[7].SetWindowPos(NULL,1600+775+80*2+10+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		m_VoltLabel[7].SetWindowPos(NULL,1600+865+80*2+45+Xoffset, 345+45, 90+35, 30,SWP_ASYNCWINDOWPOS);
		GetDlgItem(IDC_CWGRAPH7)->SetWindowPos(NULL,1600+655+80*2+Xoffset, 375+45, 300+80,160+40,SWP_ASYNCWINDOWPOS);

		m_CtrlListMainProcess.SetWindowPos(NULL,1205+Xoffset, 150, 380, 420+95,SWP_ASYNCWINDOWPOS);//1015
		GetDlgItem(IDC_STATIC_PIC)->SetWindowPos(NULL,1600+1205+Xoffset, 575+95, 380, 110,SWP_ASYNCWINDOWPOS);

		m_cLabelCableManager.SetWindowPos(NULL,1205+Xoffset, 575+95, 220, 30,SWP_ASYNCWINDOWPOS);
		m_cLabelCableMessage.SetWindowPos(NULL,1205+Xoffset, 575+125, 220, 80,SWP_ASYNCWINDOWPOS);

	
		//965
	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 1290,110,SWP_ASYNCWINDOWPOS);
	//	m_cLbOkNg.SetWindowPos(NULL,35, 575, 960+130,110,SWP_ASYNCWINDOWPOS);//1125

	//	m_MessageDisplay.SetWindowPos(NULL,35, 690, 1090,35,SWP_ASYNCWINDOWPOS);
		m_MessageDisplay.SetWindowPos(NULL,165+Xoffset, 785, 960+255,35,SWP_ASYNCWINDOWPOS);

		//95


		m_OKCntLabelName.SetWindowPos(NULL,35+Xoffset, 688+95, 50,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabelName.SetWindowPos(NULL,35+Xoffset, 707+95, 50,18,SWP_ASYNCWINDOWPOS);
		m_OKCntLabel.SetWindowPos(NULL,85+Xoffset, 688+95, 75,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabel.SetWindowPos(NULL,85+Xoffset, 707+95, 75,18,SWP_ASYNCWINDOWPOS);
		/*	
		m_OKCntLabelName.SetWindowPos(NULL,1130, 650, 50,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabelName.SetWindowPos(NULL,1130, 669, 50,18,SWP_ASYNCWINDOWPOS);
		m_OKCntLabel.SetWindowPos(NULL,1240, 650, 75,18,SWP_ASYNCWINDOWPOS);
		m_NGCntLabel.SetWindowPos(NULL,1240, 669, 75,18,SWP_ASYNCWINDOWPOS);
	*/
		m_CheckTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 688+95, 110,18,SWP_ASYNCWINDOWPOS);
		m_CycleTimeLabelName.SetWindowPos(NULL,1130+255+Xoffset, 707+95, 110,18,SWP_ASYNCWINDOWPOS);
		m_CheckTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 688+95, 85,18,SWP_ASYNCWINDOWPOS);
		m_CycleTimeLabel.SetWindowPos(NULL,1240+255+Xoffset, 707+95, 85,18,SWP_ASYNCWINDOWPOS);

	

		m_cLbOkNg.SetWindowPos(NULL,235+Xoffset, 575+95, 720+240,110,SWP_ASYNCWINDOWPOS);

	
		m_LanLabelName.SetWindowPos(NULL,35+Xoffset, 575+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_Usb1LabelName.SetWindowPos(NULL,35+Xoffset, 603+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_Usb2LabelName.SetWindowPos(NULL,35+Xoffset, 631+95, 80,26,SWP_ASYNCWINDOWPOS);
		m_CameraLabelName.SetWindowPos(NULL,35+Xoffset, 659+95, 80,26,SWP_ASYNCWINDOWPOS);

		m_cLb_Lan.SetWindowPos(NULL,115+Xoffset, 575+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Usb1.SetWindowPos(NULL,115+Xoffset, 603+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Usb2.SetWindowPos(NULL,115+Xoffset, 631+95, 110,26,SWP_ASYNCWINDOWPOS);
		m_cLb_Camera.SetWindowPos(NULL,115+Xoffset, 659+95, 110,26,SWP_ASYNCWINDOWPOS);
	}
}


void CAcqVoltageSamples_IntClkDlg::OnCbnSelchangeComboName1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for(int  i = 0; i < 8; i++)
	{
		g_ManualId[i] = m_cComboName[i].GetCurSel();
	}

	CFileControl lFile;

	lFile.SaveINIModel();
	SetChannelDataManual(0);


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
		LogStr = "DFT<< ";
	}
	else
	{
		LogStr = "DFT>> ";
	}

	for(int i = 0; i < Cnt; i++)
	{
		StrTmp.Format("%02x ", LogData[i]);
		StrTmp.MakeUpper();
		LogStr += StrTmp;
	}
	lFile.SaveProcessLOG(LogStr, 0);
}




void CAcqVoltageSamples_IntClkDlg::DblClickLabelComGmes(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CFileControl lFile;
	if(gTestSeqData.bMesEnable)
	{
		m_cLb_ComMainGmes.put_BackColor(0x000001FF);
		gTestSeqData.bMesEnable = 0;
	//	CloseEthernetScocket() ;
	//	m_UploadGmes = 0;
		


		lFile.SaveModel(gTestSeqData.strModelName);
		
	}
	else
	{
		CloseEthernetScocket() ;
		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		m_EthernetWaitCnt = 0;
		g_nPortReopen = 0;
		gTestSeqData.bMesEnable = 1;
		//m_UploadGmes = 1;
		lFile.SaveModel(gTestSeqData.strModelName);
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
	//UINT m_EditFreq1;
	

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFSET%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d", 
		gTestSeqData.Frequency[0]/10,
		gTestSeqData.Frequency[1]/10,
		gTestSeqData.Frequency[2]/10,
		gTestSeqData.Frequency[3]/10,
		gTestSeqData.Frequency[4]/10,
		gTestSeqData.Frequency[5]/10,
		gTestSeqData.Frequency[6]/10,
		gTestSeqData.Frequency[7]/10,
		gTestSeqData.Frequency[8]/10,
		gTestSeqData.Frequency[9]/10
		);
	
	lbuf[36] = 0x03;
	lbuf[37] = 0x0d;
	lbuf[38] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	SendData(lbuf, 39);//ComSend(lbuf, 39);
	
	//m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	// m_ComAck =COM_ACK_WAIT;
	// m_WaitCnt = 0;
	// m_ResendCnt = 0;
	 MessageDisplay(2, "Frequency Set ALL!");
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


void CAcqVoltageSamples_IntClkDlg::ClickLabelOK1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetFreqSend(4, 1 );
}


void CAcqVoltageSamples_IntClkDlg::ClickLabelOK2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetFreqSend(5, 1 );
}

void CAcqVoltageSamples_IntClkDlg::DblClickLabelOK1(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetFreqSend(4, 0);	
}

void CAcqVoltageSamples_IntClkDlg::DblClickLabelOK2(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetFreqSend(5, 0);	
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

		
			if(m_strModelNameList[i].Compare(NewName) == 0)
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

void CAcqVoltageSamples_IntClkDlg::ChangeModel(CString lModel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	int lGMES_Opened = 0;
	int lGMES_Port = 0;
	int lOldPortType = g_nRemotePortType;
//	if(g_nRemotePortType == LINE_CM89)

	lGMES_Opened = gTestSeqData.bMesEnable;


	CString str;
	CString lFindName;		
	CFileControl lFile;
	str = "Check S/N is";
	str += lModel;
	str += " MODEL. \r\n \r\n";
	str += "  Do You Change MODEL ?";

	m_TaskRun = TASK_RUN_IDLE;

	m_MainPAGE_COM_PROCESS = COM_MODE_IDLE;
	m_LED_COM_PROCESS = COM_MODE_IDLE;
	m_PCB_COM_PROCESS = COM_MODE_IDLE;//gTestSeqData.TestStepList[m_nCurrentNumber].m_Result = 3;
						//m_EthernetMode = 

						//m_NG_WaitFlag = 0;
						//TestFinishGMES();//
						//TestFinish();

//	if(IDOK == MessageWindow(str))
	if(IDYES == MessageBox(str,"New Model Detected", MB_YESNO))
	{

#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("1");
#endif
		lFindName =	GetModelList(lModel);
		if(lFindName.GetLength() > 3)
		{
#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("1");
#endif
			if(lFile.OpenModel(lFindName))
			{
				MessageDisplay(2, "MODEL  FILE NOT FOUND !");
				MessageBox("MODEL  FILE NOT FOUND !");
				return;
			}

			if(lFile.OpenModelSeq(gTestSeqData.strSeqFileName))
			{
				lFile.OpenModel(gTestSeqData.strModelName);
				MessageDisplay(2, "MODEL SEQUENCE FILE NOT FOUND !");
				MessageBox("MODEL SEQUENCE FILE NOT FOUND !");
				return;
			}
		}
		else
		{
			return;
		}

#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("2");
#endif

		gTestSeqData.strModelName = lFindName;
		lFile.SaveINIModel();

		LoadTestData(gTestSeqData.strSeqFileName);
#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("3");
#endif
		//SetListControl();
		DisplayTestData();		
#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("4");
#endif
		GetRmtCodeList(gTestSeqData.strRemoconFileName);

#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("5");
#endif
		str = gTestSeqData.strModelName;
		m_cLbModel.put_Caption((LPCSTR)str);
		m_DO_Writedata = 0;	
#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("6");
#endif
		if (gTestSeqData.bMesEnable)
		{
			if (m_GmesOpen == 1)
			{
				CloseEthernetScocket();
			}
			//CloseEthernetScocket() ;
			m_EthernetMode = ETHERNET_MODE_CREATE_SOCKET;
			m_EthernetWaitCnt = 0;
			g_nPortReopen = 0;


			m_cLb_ComMainGmes.put_BackColor(0x000000FF);

		}
		//if(gTestSeqData.bMesEnable)
		//{			
		//	if(lGMES_Opened)
		//	{
		//		if(lOldPortType != g_nRemotePortType)
		//		{
		//			CloseEthernetScocket() ;
		//			m_EthernetMode =  ETHERNET_MODE_IDLE;
		//			m_EthernetWaitCnt = 0;
		//			g_nPortReopen = 0;
		//			gTestSeqData.bMesEnable = 0;	

		//			m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		//		}
		//	}
		//	else
		//	{
		//		//CloseEthernetScocket() ;
		//		m_EthernetMode =  ETHERNET_MODE_CREATE_SOCKET;
		//		m_EthernetWaitCnt = 0;
		//		g_nPortReopen = 0;
		//		gTestSeqData.bMesEnable = 1;	

		//		m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		//	}
		//}
		//else
		//{
		//	if(lGMES_Opened)
		//	{				
		//		CloseEthernetScocket() ;
		//		m_EthernetMode =  ETHERNET_MODE_IDLE;
		//		m_EthernetWaitCnt = 0;
		//		g_nPortReopen = 0;
		//	//	gTestSeqData.bMesEnable = 1;	

		//		m_cLb_ComMainGmes.put_BackColor(0x000000FF);
		//		
		//	}
		//}
		#ifdef _CHANGE_MODEL_DEBUG__
		MessageBox("7");
#endif
	}

	OnBnClickedButtonFreqSet();

}


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


void CAcqVoltageSamples_IntClkDlg::ClickLabelComGmes()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CAcqVoltageSamples_IntClkDlg::DblClickLabelBarcode(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//if (gTestSeqData.bMesEnable && (m_GmesOpen == 0))
	if (m_GmesOpen == 1)
	{
		m_WipID = m_BarCode.get_Caption();
		if (gbManualScopeMode)
		{
			MessageBox("MANUAL SCOPE MODE!!");
			return;

		}

		if (m_TaskRun != TASK_RUN_IDLE) 
		{
			return;
		}
		
		if (m_WipID.GetLength() > 5)
		{
			//m_GMES_Skipped = 0;
			g_strSetID = m_WipID;
			GMES_Scan_InformSend(1);
		}
	}	
}


void CAcqVoltageSamples_IntClkDlg::OnBnClickedCheckRunAuto()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRunMode = m_CheckRunMode.GetCheck();

	g_RunModeType = lRunMode;
	CFileControl lFile;

	lFile.SaveConfigSeqData();
}
