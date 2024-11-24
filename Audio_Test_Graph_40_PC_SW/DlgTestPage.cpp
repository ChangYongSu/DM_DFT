// DlgTestPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "DlgTestPage.h"
#include "afxdialogex.h"
#include "FileControl.h"
#include "DlgPassword.h"
#include "DlgConfig.h"


// CDlgTestPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTestPage, CDialogEx)

CDlgTestPage::CDlgTestPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTestPage::IDD, pParent)
	, m_CheckDO_1(FALSE)
	, m_CheckDO_2(FALSE)
	, m_CheckDO_3(FALSE)
	, m_CheckDO_4(FALSE)
	, m_EditFreq1 (400)
	, m_EditFreq2 (400)
	, m_EditFreq3 (400)
	, m_EditFreq4 (400)
	, m_EditFreq5 (400)
	, m_EditFreq6 (400)
	, m_EditFreq7 (400)
	, m_EditFreq8 (400)
	, m_EditFreq9 (400)
	, m_EditFreq10(400)
	
	, m_EditNewMac(_T(""))
	, m_EditMac1(_T(""))
	, m_EditMac2(_T(""))
	, m_EditMac3(_T(""))
	, m_EditMac4(_T(""))
	, m_CheckDOLED_1(FALSE)
	, m_CheckDOLED_2(FALSE)
	, m_CheckDOLED_3(FALSE)
	, m_CheckDOLED_4(FALSE)
{

}

CDlgTestPage::~CDlgTestPage()
{
}

void CDlgTestPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_RM_TYPE, m_ComboRmType);

	DDX_Check(pDX, IDC_CHECK_DO_1, m_CheckDO_1);
	DDX_Check(pDX, IDC_CHECK_DO_2, m_CheckDO_2);
	DDX_Check(pDX, IDC_CHECK_DO_3, m_CheckDO_3);
	DDX_Check(pDX, IDC_CHECK_DO_4, m_CheckDO_4);

	//DDX_Check(pDX, IDC_CHECK_DI_1, m_Check_DI_1);
	//DDX_Check(pDX, IDC_CHECK_DI_2, m_Check_DI_2);
	//DDX_Check(pDX, IDC_CHECK_DI_3, m_Check_DI_3);
	//DDX_Check(pDX, IDC_CHECK_DI_4, m_Check_DI_4);

	DDX_Control(pDX, IDC_LABEL_LED_DI_1, m_LedDi_1);//IDC_LED_DI_1
	DDX_Control(pDX, IDC_LABEL_LED_DI_2, m_LedDi_2);//IDC_LED_DI_1
	DDX_Control(pDX, IDC_LABEL_LED_DI_3, m_LedDi_3);//IDC_LED_DI_1
	DDX_Control(pDX, IDC_LABEL_LED_DI_4, m_LedDi_4);//IDC_LED_DI_1
	/*
	CLabel_text m_LedLAN;
	CLabel_text m_LedUSB1;
	CLabel_text m_LedUSB2;
	*/
	DDX_Control(pDX, IDC_LABEL_LED_LAN, m_LedLAN);//
	DDX_Control(pDX, IDC_LABEL_LED_USB1, m_LedUSB1);//
	DDX_Control(pDX, IDC_LABEL_LED_USB2, m_LedUSB2);//


	DDX_Text(pDX, IDC_EDIT_FREQ1,	m_EditFreq1);
	DDX_Text(pDX, IDC_EDIT_FREQ2,	m_EditFreq2);
	DDX_Text(pDX, IDC_EDIT_FREQ3,	m_EditFreq3);
	DDX_Text(pDX, IDC_EDIT_FREQ4,	m_EditFreq4);
	DDX_Text(pDX, IDC_EDIT_FREQ5,	m_EditFreq5);
	DDX_Text(pDX, IDC_EDIT_FREQ6,	m_EditFreq6);
	DDX_Text(pDX, IDC_EDIT_FREQ7,	m_EditFreq7);
	DDX_Text(pDX, IDC_EDIT_FREQ8,	m_EditFreq8);
	DDX_Text(pDX, IDC_EDIT_FREQ9,	m_EditFreq9);
	DDX_Text(pDX, IDC_EDIT_FREQ10,	m_EditFreq10);
	DDV_MinMaxUInt(pDX, m_EditFreq1 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq2 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq3 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq4 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq5 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq6 , 0, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq7 , 100, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq8 , 100, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq9 , 100, 5000);
	DDV_MinMaxUInt(pDX, m_EditFreq10, 100, 5000);

	DDX_Control(pDX, IDC_COMBO_SIGNAL, m_cComboSignalCarrier);

	DDX_Control(pDX, IDC_COMBO_RM_TEST1 , m_cComboRmTest[0]);	
	DDX_Control(pDX, IDC_COMBO_RM_TEST2 , m_cComboRmTest[1] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST3 , m_cComboRmTest[2] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST4 , m_cComboRmTest[3] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST5 , m_cComboRmTest[4] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST6 , m_cComboRmTest[5] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST7 , m_cComboRmTest[6] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST8 , m_cComboRmTest[7] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST9 , m_cComboRmTest[8] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST10, m_cComboRmTest[9] );
	DDX_Control(pDX, IDC_COMBO_RM_TEST11, m_cComboRmTest[10]);
	DDX_Control(pDX, IDC_COMBO_RM_TEST12, m_cComboRmTest[11]);

	//DDX_Control(pDX, IDC_TEXTBOX_TPG_MESSAGE, m_cTestPageMessage);
	DDX_Control(pDX, IDC_LABEL_TPG_MESSAGE, m_cTpgMessage);
	DDX_Control(pDX, IDC_COMBO_RMT_OUT, m_cComboRmtSelect);
	DDX_Text(pDX, IDC_EDIT_NEW_MAC, m_EditNewMac);
	DDX_Text(pDX, IDC_EDIT_MAC1, m_EditMac1);
	DDX_Text(pDX, IDC_EDIT_MAC2, m_EditMac2);
	DDX_Text(pDX, IDC_EDIT_MAC3, m_EditMac3);
	DDX_Text(pDX, IDC_EDIT_MAC4, m_EditMac4);
	DDX_Control(pDX, IDC_COMBO_PCB_TYPE, m_ComboPcbType);
	DDX_Control(pDX, IDC_LABEL_LED_ON1, m_Led_ON[0]);
	DDX_Control(pDX, IDC_LABEL_LED_ON2, m_Led_ON[1]);
	DDX_Control(pDX, IDC_LABEL_LED_ON3, m_Led_ON[2]);
	DDX_Control(pDX, IDC_LABEL_LED_ON4, m_Led_ON[3]);
	DDX_Control(pDX, IDC_LABEL_LED_ON5, m_Led_ON[4]);
	DDX_Control(pDX, IDC_LABEL_LED_ON6, m_Led_ON[5]);
	DDX_Control(pDX, IDC_LABEL_LED_ON7, m_Led_ON[6]);
	DDX_Control(pDX, IDC_LABEL_LED_ON8, m_Led_ON[7]);
	DDX_Control(pDX, IDC_LABEL_LED_ON9, m_Led_ON[8]);
	DDX_Control(pDX, IDC_LABEL_LED_ON10, m_Led_ON[9]);
	DDX_Control(pDX, IDC_LABEL_LED_ON11, m_Led_ON[10]);
	DDX_Control(pDX, IDC_LABEL_LED_ON12, m_Led_ON[11]);
	DDX_Control(pDX, IDC_LABEL_LED_ON13, m_Led_ON[12]);
	DDX_Control(pDX, IDC_LABEL_LED_ON14, m_Led_ON[13]);
	DDX_Control(pDX, IDC_LABEL_LED_ON15, m_Led_ON[14]);
	DDX_Control(pDX, IDC_LABEL_LED_ON16, m_Led_ON[15]);
	DDX_Check(pDX, IDC_CHECK_DO_LED1, m_CheckDOLED_1);
	DDX_Check(pDX, IDC_CHECK_DO_LED2, m_CheckDOLED_2);
	DDX_Check(pDX, IDC_CHECK_DO_LED3, m_CheckDOLED_3);
	DDX_Check(pDX, IDC_CHECK_DO_LED4, m_CheckDOLED_4);

	DDX_Control(pDX, IDC_LABEL_LED_UP_DI_1, m_Led_UP_DI_ON[0]);
	DDX_Control(pDX, IDC_LABEL_LED_UP_DI_2, m_Led_UP_DI_ON[1]);
	DDX_Control(pDX, IDC_LABEL_LED_UP_DI_3, m_Led_UP_DI_ON[2]);
	DDX_Control(pDX, IDC_LABEL_LED_UP_DI_4, m_Led_UP_DI_ON[3]);
	DDX_Control(pDX, IDC_COMBO_COMPORT_TEMP_PCB, m_cComboPCBTempPort);
	DDX_Control(pDX, IDC_COMBO_PCB_TEMP_BAUD, m_cComboTempSetBaud);
	DDX_Control(pDX, IDC_COMBO_TEMP_PCB_PARITY, m_cComboTempSetParity);
}


BEGIN_MESSAGE_MAP(CDlgTestPage, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_DO_1, &CDlgTestPage::OnBnClickedCheckDo1)
	ON_BN_CLICKED(IDC_CHECK_DO_2, &CDlgTestPage::OnBnClickedCheckDo2)
	ON_BN_CLICKED(IDC_CHECK_DO_3, &CDlgTestPage::OnBnClickedCheckDo3)
	ON_BN_CLICKED(IDC_CHECK_DO_4, &CDlgTestPage::OnBnClickedCheckDo4)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveData)
	ON_MESSAGE(WM_COMM_RXCHAR_PCB,OnReceiveDataPCB)
	ON_MESSAGE(WM_COMM_RXCHAR_LED,OnReceiveDataLED)
	ON_BN_CLICKED(IDC_BUTTON_FREQ1 , &CDlgTestPage::OnBnClickedButtonFreq1 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ2 , &CDlgTestPage::OnBnClickedButtonFreq2 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ3 , &CDlgTestPage::OnBnClickedButtonFreq3 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ4 , &CDlgTestPage::OnBnClickedButtonFreq4 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ5 , &CDlgTestPage::OnBnClickedButtonFreq5 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ6 , &CDlgTestPage::OnBnClickedButtonFreq6 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ7 , &CDlgTestPage::OnBnClickedButtonFreq7 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ8 , &CDlgTestPage::OnBnClickedButtonFreq8 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ9 , &CDlgTestPage::OnBnClickedButtonFreq9 )
	ON_BN_CLICKED(IDC_BUTTON_FREQ10, &CDlgTestPage::OnBnClickedButtonFreq10)

	ON_BN_CLICKED(IDC_BUTTON_FREQ_SET, &CDlgTestPage::OnBnClickedButtonFreqSet)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_READ, &CDlgTestPage::OnBnClickedButtonFreqRead)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_1, &CDlgTestPage::OnBnClickedButtonRmtest1)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_2, &CDlgTestPage::OnBnClickedButtonRmtest2)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_3, &CDlgTestPage::OnBnClickedButtonRmtest3)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_4, &CDlgTestPage::OnBnClickedButtonRmtest4)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_5, &CDlgTestPage::OnBnClickedButtonRmtest5)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_6, &CDlgTestPage::OnBnClickedButtonRmtest6)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_7, &CDlgTestPage::OnBnClickedButtonRmtest7)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_8, &CDlgTestPage::OnBnClickedButtonRmtest8)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_9, &CDlgTestPage::OnBnClickedButtonRmtest9)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_10, &CDlgTestPage::OnBnClickedButtonRmtest10)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_11, &CDlgTestPage::OnBnClickedButtonRmtest11)
	ON_BN_CLICKED(IDC_BUTTON_RMTEST_12, &CDlgTestPage::OnBnClickedButtonRmtest12)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_RM_TYPE, &CDlgTestPage::OnCbnSelchangeComboSelectRmType)
	ON_BN_CLICKED(IDC_BUTTON_MAC_SET, &CDlgTestPage::OnBnClickedButtonMacSet)
	ON_BN_CLICKED(IDC_BUTTON_MAC_READ, &CDlgTestPage::OnBnClickedButtonMacRead)
	ON_BN_CLICKED(IDC_BUTTON_LED_READ, &CDlgTestPage::OnBnClickedButtonLedRead)
	ON_BN_CLICKED(IDC_BUTTON_PCB_SEND, &CDlgTestPage::OnBnClickedButtonPcbSend)
	ON_BN_CLICKED(IDC_BUTTON_LED_CLEAR, &CDlgTestPage::OnBnClickedButtonLedClear)
	ON_BN_CLICKED(IDC_CHECK_DO_LED1, &CDlgTestPage::OnBnClickedCheckDoLed1)
	ON_BN_CLICKED(IDC_CHECK_DO_LED2, &CDlgTestPage::OnBnClickedCheckDoLed2)
	ON_BN_CLICKED(IDC_CHECK_DO_LED3, &CDlgTestPage::OnBnClickedCheckDoLed3)
	ON_BN_CLICKED(IDC_CHECK_DO_LED4, &CDlgTestPage::OnBnClickedCheckDoLed4)
	ON_BN_CLICKED(IDC_BUTTON_MIC1_ON, &CDlgTestPage::OnBnClickedButtonMic1On)
	ON_BN_CLICKED(IDC_BUTTON_MIC2_ON, &CDlgTestPage::OnBnClickedButtonMic2On)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_MIC1_ON, &CDlgTestPage::OnBnDoubleclickedButtonMic1On)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_MIC2_ON, &CDlgTestPage::OnBnDoubleclickedButtonMic2On)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT_TEMP_PCB, &CDlgTestPage::OnCbnSelchangeComboComportTempPcb)
	ON_CBN_SELCHANGE(IDC_COMBO_PCB_TEMP_BAUD, &CDlgTestPage::OnCbnSelchangeComboPcbTempBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_TEMP_PCB_PARITY, &CDlgTestPage::OnCbnSelchangeComboTempPcbParity)
	ON_BN_CLICKED(IDC_BUTTON_UPDIN_READ, &CDlgTestPage::OnBnClickedButtonUpdinRead)
END_MESSAGE_MAP()



BOOL CDlgTestPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if(pMsg->wParam == VK_RETURN)
		{
			//ClickCbtnStart();		
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

// CDlgTestPage 메시지 처리기입니다.
BOOL CDlgTestPage::OnInitDialog()
{
    CDialog::OnInitDialog();
 //   
	//CString lStrComName[18] = {
	//	_T("HDMI_R"),_T("HDMI_L"),
	//	_T("OPTICAL_R"),_T("OPTICAL_L"),
	//	_T("SPEAKER_1R"),_T("SPEAKER_1L"),
	//	_T("SPEAKER_2R"),_T("SPEAKER_2L"),
	//	_T("SPEAKER_3R"),_T("SPEAKER_3L"),
	//	_T("SPEAKER_4R"),_T("SPEAKER_4L"),
	//	_T("AUX_R"),_T("AUX_L"),
	//	_T("PORTABLE_R"),_T("PORTABLE_L"), 
	//	_T("COAX_R"),_T("COAX_L")};
 //   // Return TRUE unless you set the focus to a control.
	//for(int i = 0; i < 12; i++)
	//{
	//	for(int j = 0; j < 18; j++)
	//	{
	//		m_ComboPort[i].AddString(lStrName[j]);
	//	}
	//	m_ComboPort[i].SetCurSel(i%6);
	//}
	//m_CtrlComboStart.AddString("LIMIT SW");
	//m_CtrlComboStart.AddString("START ON");
	//m_CtrlComboStart.AddString("MES");
	//m_CtrlComboStart.SetCurSel(0);

	InitPage();
	OpenComport();
	OpenComportPCB();
	OpenComportLED();

	

	m_DO_Writedata = 0;
	m_TESTPAGE_COM_PROCESS = 0;
	m_ComAck = 0;

	m_RecvCnt = 0;
	m_WaitCnt = 0;
	m_ResendCnt = 0;

	m_EditFreq1 = 400;
	m_EditFreq2 = 1000;
	m_EditFreq3 = 400;
	m_EditFreq4 = 1000;
	m_EditFreq5 = 400;
	m_EditFreq6 = 1000;
	m_EditFreq7 = 400;
	m_EditFreq8 = 1000;
	m_EditFreq9 = 400;
	m_EditFreq10 = 1000;

	m_MAC_SendFlag = 0;

	SetDlgItemText(IDC_EDIT_PCB_COMMAND,"2D");

	UpdateData(FALSE);

	SetTimer(1, 30, NULL);

	OnBnClickedButtonFreqRead();
	m_WaitPCB_Ack_Limit = 60;
    return TRUE;
}

BOOL CDlgTestPage::InitPage()
{
	/*
	CString lStrCompName[6] = {
		_T("BD_PLAYER"),_T("HOME_THEATER"),
		_T("NA_HT"),_T("SO_HT"),
		_T("PN_HT"),_T("LG_NORMAL")
	};
		
	for(int i = 0; i < 6; i++)
	{
		m_ComboRmType.AddString(lStrCompName[i]);		
	}
	m_ComboRmType.SetCurSel(0);
	*/

	CString strTemp;
	CString strTempCom;
	CDlgConfig cfgdlg;
	cfgdlg.GetDeviceInfo();
	m_cComboPCBTempPort.ResetContent();

	m_nPortPcb = gTestSeqData.nPort_Pcb;
	m_nBaudPcb = gTestSeqData.nBaud_Pcb;
	m_nParityPcb = gTestSeqData.nParity_Pcb;

	if (cfgdlg.m_PortCnt > 0)
	{
		for (int i = 0; i < cfgdlg.m_PortCnt; i++)
		{
			strTemp = cfgdlg.strPort[i].Mid(cfgdlg.strPort[i].Find("COM") + 3);
			strTemp = strTemp.Left(strTemp.Find(")"));

			strTempCom = cfgdlg.strPort[i].Mid(cfgdlg.strPort[i].Find("COM"));
			strTempCom = strTempCom.Left(strTempCom.Find(")"));

			m_cComboPCBTempPort.AddString(strTempCom);


			nNumberPort[i] = _ttoi(strTemp);


			if (m_nPortPcb == nNumberPort[i])
			{
				m_cComboPCBTempPort.SetCurSel(i);
			}

		}

		//	strTemp.Format(_T("컴포트 %d개가 검색되었습니다."), m_cComboPortSel.GetCount());
		//	MessageBox(strTemp);		

	}
	else
	{
		MessageBox("COM Port NOT DETECTED");
	}


	mbaud_List[0] = 9600;
	mbaud_List[1] = 19200;
	mbaud_List[2] = 38400;
	mbaud_List[3] = 57600;
	mbaud_List[4] = 115200;

	m_cComboTempSetBaud.AddString("9600");
	m_cComboTempSetBaud.AddString("19200");
	m_cComboTempSetBaud.AddString("38400");
	m_cComboTempSetBaud.AddString("57600");
	m_cComboTempSetBaud.AddString("115200");
	m_cComboTempSetBaud.SetCurSel(4);
	for (int i = 0; i < 5; i++)
	{
		if (m_nBaudPcb == mbaud_List[i])
		{
			m_cComboTempSetBaud.SetCurSel(i);
		}
	}


	m_cComboTempSetParity.AddString("NONE");
	m_cComboTempSetParity.AddString("EVEN");
	m_cComboTempSetParity.AddString("ODD");
	m_cComboTempSetParity.SetCurSel(m_nParityPcb);


	GetRemoconList();

	GetRmtCodeList(gTestSeqData.strRemoconFileName);//GetRmtCodeList(CString lRmtFile)//gTestSeqData.strRemoconFileName;

	m_cComboSignalCarrier.AddString("IR REMOTE");
	m_cComboSignalCarrier.AddString("CABLE WIRE");
	m_cComboSignalCarrier.SetCurSel(gTestSeqData.nRemoconSigType);

	m_cComboRmtSelect.AddString("MP_KEY_OUT");
	m_cComboRmtSelect.AddString("PRE_KEY_OUT");
	m_cComboRmtSelect.AddString("MP_KEY_REPEAT");
	m_cComboRmtSelect.AddString("MP_KEY_REPEAT10");

	m_cComboRmtSelect.SetCurSel(0);


	
	m_ComboPcbType.AddString("01 : MCS");//m_cComboModelPcbType
	m_ComboPcbType.AddString("02 : MTK");
	m_ComboPcbType.AddString("03 : BCM");
	m_ComboPcbType.SetCurSel(gTestSeqData.nComPcbType);
//	m_ComboPcbType.SetCurSel(0);


	SetRemoconButton();	
	InitDioChannel();
	return 0;
}

BOOL CDlgTestPage::SetRemoconButton()
{
	return 0;
}


void CDlgTestPage::GetRemoconList()
{

	BOOL rtnValue = 0;
	
	CString pathName;
	CString fileName;

//	int lFileRename = 0;
	//CString PathNameList[200];
	CString fileNameList[100];
	

//	CString m_strRemoconList[100];
//	int m_nRecomonCount = 0;
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
		strWildcard += _T("\\Remote\\*.rmt");//"C:\\Program Files\\SM Digital\\nagra\\HDCPKey"
  
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
			if(nFileCnt >= 100)
			{
				
				break;
			}
			bFileFound = 1;
				
		}

		finder.Close();


		if(bFileFound)
		{
			/*
			CString m_strRemoconList[100];
			int m_nRecomonCount = 0;
			*/
			g_nRemoconSelNum = 0;//g_strRemoconFileName
			m_nRecomonCount = nFileCnt;
			for(int i = 0 ; i < nFileCnt; i++)
			{
				m_strRemoconList[i] = fileNameList[i];
				m_ComboRmType.AddString(m_strRemoconList[i]);
				
				if(m_strRemoconList[i].Compare(gTestSeqData.strRemoconFileName) == 0)
				{
					g_nRemoconSelNum = i;
				}
			}

			m_ComboRmType.SetCurSel(g_nRemoconSelNum);
		}
		else
		{
			MessageBox("Remote Control File(*.rmt) Not Found!!");
		}
}

void CDlgTestPage::GetRmtCodeList(CString lRmtFile)//gTestSeqData.strRemoconFileName;
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
		for(int id = 0; id < 12; id++)
		{
			m_cComboRmTest[id].ResetContent();
			for(int i = 0; i < m_RemoconModel.m_Cnt; i++)
			{
				str = m_RemoconModel.Data[i].m_Company;
				str += _T(" : "); 
				str += m_RemoconModel.Data[i].m_Name;
				m_cComboRmTest[id].AddString(str);
			}
			if(m_RemoconModel.m_Cnt > id)
			{
				m_cComboRmTest[id].SetCurSel(id);
			}
			else
			{
				m_cComboRmTest[id].SetCurSel(0);
			}
		}
	} 
}


BOOL CDlgTestPage::InitDioChannel()
{

	//UpdateData(TRUE);
 //   CWaitCursor wait;

 // //  CNiString port;//Dev1/port0
 // //  m_port.GetWindowText(port);

	//try
	//{
 //       // Create the task
	//	//CNiDAQmxTask digitalReadTask;
	//	
 //       // Create the digital input channel
	//	digitalReadTask.DIChannels.CreateChannel(
	//	    "Dev1/port0",
	//	    "",
	//	    DAQmxOneChannelForAllLines);

 //       // Create the reader
	//	CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

 //       // Read the data
	//	//unsigned long data = reader.ReadSingleSamplePortUInt32();
	//	m_DI_Readdata = reader.ReadSingleSamplePortUInt32();

 //       // Display the data
 //       //m_hexData.Format(_T("0x%X"),data);//0x3F
	//	//UpdateData(FALSE);
	//	m_DIportOpen = 1;
	//}
	//catch(CNiDAQmxException *exception)
	//{
	//	exception->ReportError();
	//	exception->Delete();
	//	m_DIportOpen = 0;
	//}	

	//m_DO_Writedata = 0;
	// try
 //   {
 //       // Create the task
 //    //   CNiDAQmxTask digitalWriteTask;

 //       //  Create an Digital Output channel and name it.
 //       digitalWriteTask.DOChannels.CreateChannel(
 //           "Dev1/port1",
 //           "",
 //           DAQmxOneChannelForAllLines);

 //       //  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
 //       //  of digital data on demand, so no timeout is necessary.
 //       CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);
 //       
 //      // CNiString(m_dataToWrite) >> dataToWrite;
 //       writer.WriteSingleSamplePort(true, m_DO_Writedata);
	//	m_DOportOpen = 1;
 //   }
 //   catch (CNiDAQmxException *e)
 //   {
 //       e->ReportError();
 //       e->Delete();
	//	m_DOportOpen = 0;
 //   }


	return 0;
}

#if 1
BOOL CDlgTestPage::SetD_OUT(ULONG lSetVal)
{
	/*if(m_DOportOpen == 0)
	{
		return 0;
	}*/

	m_DO_Writedata = lSetVal;
	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		EDO_9111_Config(0, P9111_EDO_OUT_EDO);
		//#define P9111_EDO_INPUT    1
//#define P9111_EDO_OUT_EDO  2
//#define P9111_EDO_OUT_CHN  3
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
BOOL CDlgTestPage::ReadD_IN()
{
	if (m_DIportOpen == 0)
	{
		return 0;
	}
	int inputData;
	if (g_nNI_CardSel == AI_ADLINK_PCI_9111)
	{
		inputData = 0;
		DI_ReadPort(0, P9111_CHANNEL_EDI, &m_DI_Readdata);
		if ((m_DI_Readdata & 0x0000F) != 0x00000)
		{
			inputData = (UINT)m_DI_Readdata;
			inputData = (UINT)m_DI_Readdata;
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
			m_DI_Readdata = reader.ReadSingleSamplePortUInt32();


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
			m_DI_Readdata = reader.ReadSingleSamplePortUInt32();


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
BOOL CDlgTestPage::SetD_OUT(ULONG lSetVal)
{
	/*if(m_DOportOpen == 0)
	{
		return 0;
	}*/

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
    }

	return 1;

}
BOOL CDlgTestPage::ReadD_IN()
{
	if(m_DIportOpen == 0)
	{
		return 0;
	}

	try
	{       

		CNiDAQmxTask digitalReadTask;
		
        // Create the digital input channel
		digitalReadTask.DIChannels.CreateChannel(
		    "Dev1/port0",
		    "",
		    DAQmxOneChannelForAllLines);
        // Create the reader
		CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

        // Read the data
		//unsigned long data = reader.ReadSingleSamplePortUInt32();
		m_DI_Readdata = reader.ReadSingleSamplePortUInt32();

        // Display the data
        //m_hexData.Format(_T("0x%X"),data);//0x3F		
		//UpdateData(FALSE);		
	}
	catch(CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
		m_DIportOpen = 0;
	}	

	return 1;
}
#endif


/*

	CWaitCursor wait;
    unsigned long dataToWrite;
    UpdateData(TRUE);

    CNiString physicalChannel;
    m_physicalChannel.GetWindowText(physicalChannel);

   
	*/
	/*
	   UpdateData(TRUE);
    CWaitCursor wait;

    CNiString port;//Dev1/port0
    m_port.GetWindowText(port);

	try
	{
        // Create the task
		CNiDAQmxTask digitalReadTask;
		
        // Create the digital input channel
		digitalReadTask.DIChannels.CreateChannel(
		    port,
		    "",
		    DAQmxOneChannelForAllLines);

        // Create the reader
		CNiDAQmxDigitalSingleChannelReader reader(digitalReadTask.Stream);

        // Read the data
		unsigned long data = reader.ReadSingleSamplePortUInt32();

        // Display the data
        m_hexData.Format(_T("0x%X"),data);//0x3F
		UpdateData(FALSE);
	}
	catch(CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
	}
	*/

	/*

	CWaitCursor wait;
    unsigned long dataToWrite;
    UpdateData(TRUE);

    CNiString physicalChannel;
    m_physicalChannel.GetWindowText(physicalChannel);

    try
    {
        // Create the task
        CNiDAQmxTask digitalWriteTask;

        //  Create an Digital Output channel and name it.
        digitalWriteTask.DOChannels.CreateChannel(
            physicalChannel,
            "",
            DAQmxOneChannelForAllLines);

        //  Write digital port data. WriteDigitalSingChanSingSampPort writes a single sample
        //  of digital data on demand, so no timeout is necessary.
        CNiDAQmxDigitalSingleChannelWriter writer(digitalWriteTask.Stream);
        
        CNiString(m_dataToWrite) >> dataToWrite;
        writer.WriteSingleSamplePort(true, dataToWrite);
    }
    catch (CNiDAQmxException *e)
    {
        e->ReportError();
        e->Delete();
    }
*/




void CDlgTestPage::OnBnClickedCheckDo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//m_CheckDO_1

	if(m_CheckDO_1)
		m_DO_Writedata |= 0x01; 
	else
		m_DO_Writedata &= ~0x01; 

	if(m_CheckDO_2)
		m_DO_Writedata |= (0x01<<1); 
	else
		m_DO_Writedata &= ~(0x01<<1); 

	if(m_CheckDO_3)
		m_DO_Writedata |= (0x01<<2); 
	else
		m_DO_Writedata &= ~(0x01<<2); 

	if(m_CheckDO_4)
		m_DO_Writedata |= (0x01<<3); 
	else
		m_DO_Writedata &= ~(0x01<<3); 
	
	SetD_OUT(m_DO_Writedata);



}


void CDlgTestPage::OnBnClickedCheckDo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//m_CheckDO_1

	if(m_CheckDO_1)
		m_DO_Writedata |= 0x01; 
	else
		m_DO_Writedata &= ~0x01; 

	if(m_CheckDO_2)
		m_DO_Writedata |= (0x01<<1); 
	else
		m_DO_Writedata &= ~(0x01<<1); 

	if(m_CheckDO_3)
		m_DO_Writedata |= (0x01<<2); 
	else
		m_DO_Writedata &= ~(0x01<<2); 

	if(m_CheckDO_4)
		m_DO_Writedata |= (0x01<<3); 
	else
		m_DO_Writedata &= ~(0x01<<3); 
	
	SetD_OUT(m_DO_Writedata);

}


void CDlgTestPage::OnBnClickedCheckDo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//m_CheckDO_1

	if(m_CheckDO_1)
		m_DO_Writedata |= 0x01; 
	else
		m_DO_Writedata &= ~0x01; 

	if(m_CheckDO_2)
		m_DO_Writedata |= (0x01<<1); 
	else
		m_DO_Writedata &= ~(0x01<<1); 

	if(m_CheckDO_3)
		m_DO_Writedata |= (0x01<<2); 
	else
		m_DO_Writedata &= ~(0x01<<2); 

	if(m_CheckDO_4)
		m_DO_Writedata |= (0x01<<3); 
	else
		m_DO_Writedata &= ~(0x01<<3); 

	SetD_OUT(m_DO_Writedata);
}


void CDlgTestPage::OnBnClickedCheckDo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//m_CheckDO_1

	if(m_CheckDO_1)
		m_DO_Writedata |= 0x01; 
	else
		m_DO_Writedata &= ~0x01; 

	if(m_CheckDO_2)
		m_DO_Writedata |= (0x01<<1); 
	else
		m_DO_Writedata &= ~(0x01<<1); 

	if(m_CheckDO_3)
		m_DO_Writedata |= (0x01<<2); 
	else
		m_DO_Writedata &= ~(0x01<<2); 

	if(m_CheckDO_4)
		m_DO_Writedata |= (0x01<<3); 
	else
		m_DO_Writedata &= ~(0x01<<3);

	SetD_OUT(m_DO_Writedata);
}


void CDlgTestPage::UpdateRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int lOldDi[4] = {3,3,3,3};

	static int lOldLan = 0;
	static int lOldUsb1 = 0;
	static int lOldUsb2 = 0;


	if(m_DI_Readdata  & 0x01) 
	{
		m_Check_DI_1 = 1;
	}
	else
	{
		m_Check_DI_1 = 0;
	}

	if(m_DI_Readdata  & (0x01<<1)) 
	{
		m_Check_DI_2 = 1;
	}
	else
	{
		m_Check_DI_2 = 0;
	}

			
	if(m_DI_Readdata  & (0x01<<2)) 
	{
		m_Check_DI_3 = 1;
	}
	else
	{
		m_Check_DI_3 = 0;
	}

				
	if(m_DI_Readdata  & (0x01<<3)) 
	{
		m_Check_DI_4 = 1;
	}
	else
	{
		m_Check_DI_4 = 0;
	}

	if(m_Check_DI_1 != lOldDi[0])
	{
		lOldDi[0] = m_Check_DI_1;
		if(m_Check_DI_1)
			m_LedDi_1.put_BackColor(0x0000FF00);			
		else
			m_LedDi_1.put_BackColor(0x00808080);
			
	}

	if(m_Check_DI_2 != lOldDi[1])
	{
		lOldDi[1] = m_Check_DI_2;
		if(m_Check_DI_2)
			m_LedDi_2.put_BackColor(0x0000FF00);
			
		else
			m_LedDi_2.put_BackColor(0x00808080);
			
	}
			
	if(m_Check_DI_3 != lOldDi[2])
	{
		lOldDi[2] = m_Check_DI_3;
		if(m_Check_DI_3)
			m_LedDi_3.put_BackColor(0x0000FF00);
			
		else
			m_LedDi_3.put_BackColor(0x00808080);
	}
			
	if(m_Check_DI_4 != lOldDi[3])
	{
		lOldDi[3] = m_Check_DI_4;
		if(m_Check_DI_4)
			m_LedDi_4.put_BackColor(0x0000FF00);
		else
			m_LedDi_4.put_BackColor(0x00808080);
	}
		
	CString str;

	if(m_LAN_TestOK != lOldLan)
	{
		lOldLan = m_LAN_TestOK;
		if(m_LAN_TestOK == 3)
		{
			m_LedLAN.put_BackColor(0x0000FF00);
			str.Format(_T("O K"));
		}
		else if(m_LAN_TestOK == 0) 
		{
			m_LedLAN.put_BackColor(0x00808080);
			str.Format(_T("N C"));
		}
		else if(m_LAN_TestOK == 2) 
		{
			m_LedLAN.put_BackColor(0x00808000);
			str.Format(_T("MAC ERR"));
		}
		else if(m_LAN_TestOK == 1) 
		{
			m_LedLAN.put_BackColor(0x00008080);
			str.Format(_T("LINE"));
		}

		
		m_LedLAN.put_Caption(str.GetBuffer());
	}
		
	if(m_USB1_TestOK != lOldUsb1)
	{
		lOldUsb1 = m_USB1_TestOK;
		if(m_USB1_TestOK == 7)
			m_LedUSB1.put_BackColor(0x0000FF00);
		else if(m_USB1_TestOK == 0)
			m_LedUSB1.put_BackColor(0x00808080);
		else
			m_LedUSB1.put_BackColor(0x00808000);

		if(m_USB1_TestOK == 7)
		{
			str.Format(_T("O K"));
		}
		else
		{
			str.Format(_T("NG"));
		
			if((m_USB1_TestOK & 0x01) == 0)
			{
				str +=_T(":V");
			}
			
			if((m_USB1_TestOK & 0x02) == 0)
			{
				str +=_T(":C");
			}

			if((m_USB1_TestOK & 0x04) == 0)
			{
				str +=_T(":G");
			}
		}

		m_LedUSB1.put_Caption(str.GetBuffer());


	}
	
	if(m_USB2_TestOK != lOldUsb2)
	{
		lOldUsb2 = m_USB2_TestOK;
		if(m_USB2_TestOK == 7)
			m_LedUSB2.put_BackColor(0x0000FF00);
		else if(m_USB2_TestOK == 0)
			m_LedUSB2.put_BackColor(0x00808080);
		else
			m_LedUSB2.put_BackColor(0x00808000);

		if(m_USB2_TestOK == 7)
		{
			str.Format(_T("O K"));
		}
		else
		{
			str.Format(_T("NG"));
		
			if((m_USB2_TestOK & 0x01) == 0)
			{
				str +=_T(":V");
			}
			
			if((m_USB2_TestOK & 0x02) == 0)
			{
				str +=_T(":C");
			}

			if((m_USB2_TestOK & 0x04) == 0)
			{
				str +=_T(":G");
			}
		}

		m_LedUSB2.put_Caption(str.GetBuffer());
	}
}



void CDlgTestPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	KillTimer(1);

	ReadD_IN();
	UpdateRead();



	switch(m_TESTPAGE_COM_PROCESS)
	{
	case COM_MODE_IDLE:
		break;
	case COM_MODE_WAIT_ACK:

		if(m_ComAck == COM_ACK_OK)
		{
			m_ComAck = COM_ACK_WAIT;
			m_TESTPAGE_COM_PROCESS = COM_MODE_IDLE;
			//MessageBox("COM OK !! ");
			MessageDisplay(0, "COM OK !! ");
		}
		else if(m_ComAck == COM_ACK_BUSY)
		{
			//MessageBox("COM Fail !! ");
			MessageDisplay(1, "COM FAIL !! ");
			m_TESTPAGE_COM_PROCESS = COM_MODE_IDLE;
		}
		else
		{
			/*
			int m_WaitCnt;
			int m_ResendCnt;
			*/
			m_WaitCnt++;

			if(m_WaitCnt > 30)
			{
			
				m_ResendCnt++;
				if(m_ResendCnt < 3)
				{
					ComResend();
				}
				else
				{
					//MessageBox("COM Time Out !! ");
					MessageDisplay(1, "COM Time Out !!");
					m_TESTPAGE_COM_PROCESS = COM_MODE_IDLE;
				}
			}
		}
		break;
	default:
		break;

	}

	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;
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
			MessageDisplay(0, "COM OK !! ");
		}
		else if(m_LEDComAck == COM_ACK_BUSY)
		{
			//MessageBox("COM Fail !! ");
			MessageDisplay(1, "COM FAIL !! ");
			m_LED_COM_PROCESS = COM_MODE_IDLE;
		}
		else
		{
			/*
			int m_WaitCnt;
			int m_ResendCnt;
			*/
			m_LEDWaitCnt++;

			if(m_LEDWaitCnt > 30)
			{			
				m_LEDResendCnt++;
				if(m_LEDResendCnt < 3)
				{
					ComLedRead();
				}
				else
				{
					//MessageBox("COM Time Out !! ");
					MessageDisplay(1, "COM Time Out !!");
					m_LED_COM_PROCESS = COM_MODE_IDLE;
				}
			}
		}
		break;
	default:
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
			MessageDisplay(0, "COM OK !! ");
		}
		else if(m_PCBComAck == COM_ACK_BUSY)
		{
			//MessageBox("COM Fail !! ");
			MessageDisplay(1, "COM FAIL !! ");
			m_PCB_COM_PROCESS = COM_MODE_IDLE;
		}
		else
		{
			/*
			int m_WaitCnt;
			int m_ResendCnt;
			*/
			m_PCBWaitCnt++;

			if(m_PCBWaitCnt > m_WaitPCB_Ack_Limit)
			{
			
				m_PCBResendCnt++;
				if(m_PCBResendCnt < 3)
				{
					ComPCBSend();
				}
				else
				{
					//MessageBox("COM Time Out !! ");
					MessageDisplay(1, "COM Time Out !!");
					m_PCB_COM_PROCESS = COM_MODE_IDLE;
				}
			}
		}
		break;
	default:
		break;

	}
	SetTimer(1, 30, NULL);

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgTestPage::OnDestroy()
{
	CDialogEx::OnDestroy();
		
	//digitalReadTask.
	// digitalWriteTask;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//m_ComPort.ClosePort();
	if(m_ComPort.mPort_Opened == TRUE)
		m_ComPort.ClosePort();
		
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
		
	if(m_ComPortLED.mPort_Opened == TRUE)
		m_ComPortLED.ClosePort();
		
}


void CDlgTestPage::ComResend()
{
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
	//SendData(m_SendBuf, m_SendCnt);
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

void CDlgTestPage::ComSend(BYTE *lbuf, int lcnt)
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	if(m_ComPort.mPort_Opened)
	{
		memcpy(m_SendBuf, lbuf, lcnt); 
		m_SendCnt = lcnt;
		m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
	}
	else
	{
		OpenComport();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPort.mPort_Opened)
		{
			memcpy(m_SendBuf, lbuf, lcnt); 
			m_SendCnt = lcnt;
			m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
		}
	}
}

void CDlgTestPage::ComLedRead()
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
}

void CDlgTestPage::ComPCBSend()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	if(m_ComPortPCB.mPort_Opened)
	{
		
		m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
	}
	else
	{
		OpenComportPCB();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPortPCB.mPort_Opened)
		{
			
			m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
		}
	}
}

void CDlgTestPage::OpenComport()
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
		str.Format(_T("Set COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
	}
}
void CDlgTestPage::OpenComportPCB()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = { 'N', 'E', 'O' };



	if (m_nParityPcb > 2)
	{
		m_nParityPcb = 0;
	}

	if (m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
	if (m_ComPortPCB.InitPort(this, m_nPortPcb, m_nBaudPcb, lParityChar[m_nParityPcb], 8, 1, EV_RXCHAR, 4096))
	{
		m_ComPortPCB.StartMonitoring();
		m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
	}
	else
	{
		str.Format(_T("Audio COM Port %d Open FAIL !!"), m_nPortPcb);

		MessageDisplay(1, str);

	}

	//if(gTestSeqData.nParity_Pcb > 2)
	//{
	//	gTestSeqData.nParity_Pcb = 0;
	//}

	//if(m_ComPortPCB.mPort_Opened)
	//{
	//	m_ComPortPCB.ClosePort();
	//}
	//if(m_ComPortPCB.InitPort(this, g_nPort_Pcb, gTestSeqData.nBaud_Pcb, lParityChar[gTestSeqData.nParity_Pcb], 8, 1, EV_RXCHAR, 4096 ))
	//{		
	//	m_ComPortPCB.StartMonitoring();
	//	m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
	//}
	//else
	//{
	//	str.Format(_T("Audio COM Port %d Open FAIL !!"),  g_nPort_Pcb);
	//	//MessageBox(str);
	//	MessageDisplay(1, str);
	//	/*StatusDisplayMsg(str, 1 );*/
	//}

	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_PCB;
}


void CDlgTestPage::OpenComportLED()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
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
		str.Format(_T("Set COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
	}
	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_LED;
}

void CDlgTestPage::OpenComportSCAN()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
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
		str.Format(_T("Set COM Port %d Open FAIL !!"),  g_nPort_LED, g_nBaud_LED);
		//MessageBox(str);
		MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
	}
	m_ComPortScanner.m_RxMessageID = WM_COMM_RXCHAR_SCAN;
}

//""

//extern unsigned char TransBuff[4096];
long CDlgTestPage::OnReceiveData(WPARAM wParam, LPARAM lParam )
{
	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

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

				}
				else if(strncmp((char *)&m_RecvBuf[1], "DBUSY ", 6) == 0)
				{
					m_ComAck = COM_ACK_BUSY;
					m_RecvCnt = 0;
				}
				else if(strncmp((char *)&m_RecvBuf[1], "DFREQ", 5) == 0)
				{
					if(m_RecvCnt >= 39)
					{
						if((m_RecvBuf[36] == 0x03)&&(m_RecvBuf[37] == 0x0d)&&( m_RecvBuf[38] == 0x0a))
						{
							m_ComAck = COM_ACK_OK;
							UINT lfreq[10];
							for(int i = 0 ; i < 10; i++)
							{
								lfreq[i] =  (m_RecvBuf[6+i*3]-0x30)*100 + (m_RecvBuf[7+i*3]-0x30)*10 + (m_RecvBuf[8+i*3]-0x30);
							}							
							
							m_EditFreq1  = lfreq[0]*10;
							m_EditFreq2  = lfreq[1]*10;
							m_EditFreq3  = lfreq[2]*10;
							m_EditFreq4  = lfreq[3]*10;
							m_EditFreq5  = lfreq[4]*10;
							m_EditFreq6  = lfreq[5]*10;
							m_EditFreq7  = lfreq[6]*10;
							m_EditFreq8  = lfreq[7]*10;
							m_EditFreq9  = lfreq[8]*10;
							m_EditFreq10 = lfreq[9]*10;
							UpdateData(FALSE);
						}
						else
						{
							m_ComAck = COM_ACK_BUSY;
						}

						m_RecvCnt = 0;
					}
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
		int m_LAN_TestOK;
		int m_USB1_TestOK;
		int m_USB2_TestOK;
*/
					if(m_RecvBuf[1] == '3')
					{
						m_LAN_TestOK = 3;
					}
					else if(m_RecvBuf[1] == '0')
					{
						m_LAN_TestOK = 0;
					}else 
					{
						m_LAN_TestOK = m_RecvBuf[1] - '0';
					}

								
					if(m_RecvBuf[2] == '7')
					{
						m_USB1_TestOK = 7;
					}
					else if(m_RecvBuf[2] == '0')
					{
						m_USB1_TestOK = 0;
					}
					else
					{
						m_USB1_TestOK = m_RecvBuf[2] - '0';
					}
						
					if(m_RecvBuf[3] == '7')
					{
						m_USB2_TestOK = 7;
					}
					else if(m_RecvBuf[3] == '0')
					{
						m_USB2_TestOK = 0;
					}
					else
					{
						
						m_USB2_TestOK = m_RecvBuf[3] - '0';
					}

					m_RecvCnt = 0;

				}
				else if((m_RecvBuf[1]== 'D') && (m_RecvBuf[2]== 'M') && (m_RecvBuf[3]== 'A') && (m_RecvBuf[4]== 'C') && (m_RecvBuf[5]== '_'))
				{

					if(m_RecvCnt >= 37)
					{

						if(m_RecvBuf[36] == '#')
						{
							char lbuf[32];
							memset(lbuf, 0, sizeof(lbuf));
							strncpy(lbuf, (char *)&(m_RecvBuf[6]), 6);
							m_EditMac1 = lbuf;

							memset(lbuf, 0, sizeof(lbuf));
							strncpy(lbuf, (char *)&(m_RecvBuf[12]), 6);
							m_EditMac2 = lbuf;

							memset(lbuf, 0, sizeof(lbuf));
							strncpy(lbuf, (char *)&(m_RecvBuf[18]), 6);
							m_EditMac3 = lbuf;

							memset(lbuf, 0, sizeof(lbuf));
							strncpy(lbuf, (char *)&(m_RecvBuf[24]), 6);
							m_EditMac4 = lbuf;

							if(m_MAC_SendFlag == 0)
							{
								memset(lbuf, 0, sizeof(lbuf));
								strncpy(lbuf, (char *)&(m_RecvBuf[30]), 6);
								m_EditNewMac = lbuf;
							}
							UpdateData(FALSE);
							
						}	
	
						m_RecvCnt = 0;
					}
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


long CDlgTestPage::OnReceiveDataPCB(WPARAM wParam, LPARAM lParam )
{
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
		
	//int m_PCB_COM_PROCESS;
	//int m_PCBComAck;
	//int m_PCBWaitCnt;
	//int m_PCBResendCnt;

	if(m_RecvCntPCB > 2)
	{
		if(m_RecvBufPCB[0] == 0xBB)
		{
			if(m_RecvCntPCB+2 >= m_RecvBufPCB[1])
			{
			//	memset(lbuf,0,sizeof(lbuf));
				unsigned char lCheckSum = 0;
				for(int i = 0; i < m_RecvBufPCB[1]+1; i++)
				{
					lCheckSum ^= m_RecvBufPCB[i];
				}

				if(m_RecvBufPCB[m_RecvBufPCB[1]+1] == lCheckSum)
				{
					m_PCBComAck = COM_ACK_OK;
				}
				else
				{
					m_PCBComAck = COM_ACK_BUSY;
				}


				CString strtmp;
				CString strReceive = _T("");

				for(int i = 0; i < m_RecvCntPCB; i++)
				{
					strtmp.Format(_T(" %02X"), m_RecvBufPCB[i]);//strtmp.Format(_T(""), m_RecvBufPCB[i]);
					strReceive += strtmp;
				}	

				SetDlgItemText(IDC_EDIT_READ_DATA,strReceive.GetBuffer());
				strReceive = "";
				for (int i = 0; i < m_RecvCntPCB; i++)
				{
					strtmp = "";
					if(i == 4)
						strtmp += "[ ";
					else if(i == m_RecvCntPCB - 2)
						strtmp += "] ";

					if ((m_RecvBufPCB[i] > 0x20) 
						&& (m_RecvBufPCB[i] <= 0x7E) 
						&& (i > 3) && (i < m_RecvCntPCB-2))
					{
						
						strtmp += m_RecvBufPCB[i];
						strtmp += ' ';
					}
					else
					{
						strtmp.Format(_T("%02X "), m_RecvBufPCB[i]);//strtmp.Format(_T(""), m_RecvBufPCB[i]);

					}
					strReceive += strtmp;
				}

				SetDlgItemText(IDC_EDIT_READ_DATA_ASCII, strReceive.GetBuffer());

				m_PCBComAck = COM_ACK_OK;
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


long CDlgTestPage::OnReceiveDataLED(WPARAM wParam, LPARAM lParam )
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
	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;

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
					for(int i = 0; i < 4; i++)
					{
						if(m_RecvBufLED[5]&(0x01<<i))
						{
							m_Led_ON[i].put_BackColor(0x0000FF00);	
						}
						else
						{
							m_Led_ON[i].put_BackColor(0x00808080);
						}

						if(m_RecvBufLED[6]&(0x01<<i))
						{
							m_Led_ON[i+4].put_BackColor(0x0000FF00);	
						}
						else
						{
							m_Led_ON[i+4].put_BackColor(0x00808080);
						}
						if(m_RecvBufLED[7]&(0x01<<i))
						{
							m_Led_ON[i+8].put_BackColor(0x0000FF00);	
						}
						else
						{
							m_Led_ON[i+8].put_BackColor(0x00808080);
						}

						
						if(m_RecvBufLED[8]&(0x01<<i))
						{
							m_Led_ON[i+12].put_BackColor(0x0000FF00);	
						}
						else
						{
							m_Led_ON[i+12].put_BackColor(0x00808080);
						}
					}
					m_RecvCntLED = 0;
				}
				else if(strncmp((char *)&m_RecvBufLED[1], "D_IN", 4) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
					//	m_LED_Up_DI_ReadData
					//m_LED_Up_DI_ReadData[0] = m_RecvBufLED[5];
					//m_LED_Up_DI_ReadData[1] = m_RecvBufLED[6];
					//m_LED_Up_DI_ReadData[2] = m_RecvBufLED[7];
					//m_LED_Up_DI_ReadData[3] = m_RecvBufLED[8];
					unsigned char l_LED_Up_DI_ReadData[4];
					for(int i = 0; i < 4; i++)
					{
						l_LED_Up_DI_ReadData[i] = m_RecvBufLED[i+5] & 0x0F;
						if(l_LED_Up_DI_ReadData[i] != 0)
						{					
							if(m_Led_UP_DI_ON[i].get_BackColor() != 0x0000FF00)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x0000FF00);	
							}
						}
						else
						{
							if(m_Led_UP_DI_ON[i].get_BackColor() != 0x00808080)						
							{
								m_Led_UP_DI_ON[i].put_BackColor(0x00808080);	
							}
						}
					}
					m_RecvCntLED = 0;

				}			
			/*	else if(strncmp((char *)&m_RecvBufLED[1], "DLED", 4) == 0)
				{
					m_LEDComAck = COM_ACK_OK;
					m_LEDResendCnt = 0;
					for(int i = 0; i < 4; i++)
					{
					}
				}*/
				else
				{
					m_LEDComAck = COM_ACK_BUSY;
					m_LEDResendCnt = 0;
					m_RecvCntLED = 0;
				}
			}
		}
		else
		{
			m_RecvCntLED = 0;
		}
	}
	
	

	return 0;
}

void CDlgTestPage::SetFreqSend(UINT lPort, UINT lFreq )
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	CString str;
	//UINT m_EditFreq1;
	UpdateData();

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFREQ%02d%03d       ", lPort, lFreq/10);
	
	lbuf[18] = 0x03;
	lbuf[19] = 0x0d;
	lbuf[20] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	ComSend(lbuf, 21);

	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	 m_ComAck =COM_ACK_WAIT;
	 m_WaitCnt = 0;
	 m_ResendCnt = 0;
	
	MessageDisplay(2, "Frequency Set !");


}

void CDlgTestPage::OnBnClickedButtonFreq1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(0, m_EditFreq1 );
}

void CDlgTestPage::OnBnClickedButtonFreq2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(1, m_EditFreq2 );
}

void CDlgTestPage::OnBnClickedButtonFreq3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(2, m_EditFreq3 );
}

void CDlgTestPage::OnBnClickedButtonFreq4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(3, m_EditFreq4 );
}

void CDlgTestPage::OnBnClickedButtonFreq5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(4, m_EditFreq5 );
}

void CDlgTestPage::OnBnClickedButtonFreq6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(5, m_EditFreq6 );
}

void CDlgTestPage::OnBnClickedButtonFreq7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(6, m_EditFreq7 );
}

void CDlgTestPage::OnBnClickedButtonFreq8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(7, m_EditFreq8 );
}

void CDlgTestPage::OnBnClickedButtonFreq9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(8, m_EditFreq9 );
}

void CDlgTestPage::OnBnClickedButtonFreq10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//UINT m_EditFreq1;
	UpdateData();

	SetFreqSend(9, m_EditFreq10 );
}


void CDlgTestPage::OnBnClickedButtonFreqSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	//UINT m_EditFreq1;
	UpdateData();

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFSET%03d%03d%03d%03d%03d%03d%03d%03d%03d%03d", 
		m_EditFreq1/10,
		m_EditFreq2/10,
		m_EditFreq3/10,
		m_EditFreq4/10,
		m_EditFreq5/10,
		m_EditFreq6/10,
		m_EditFreq7/10,
		m_EditFreq8/10,
		m_EditFreq9/10,
		m_EditFreq10/10
		);
	
	lbuf[36] = 0x03;
	lbuf[37] = 0x0d;
	lbuf[38] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	ComSend(lbuf, 39);

	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	 m_ComAck =COM_ACK_WAIT;
	 m_WaitCnt = 0;
	 m_ResendCnt = 0;
	 MessageDisplay(2, "Frequency Set ALL!");
}


void CDlgTestPage::OnBnClickedButtonFreqRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;
	
	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFREQREAD");
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	ComSend(lbuf, 13);

	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_ComAck =COM_ACK_WAIT;
	m_WaitCnt = 0;
	m_ResendCnt = 0;
	MessageDisplay(2, "Frequency Read!");
}


void CDlgTestPage::SendIRCode(int lRmtCodeIndex)
{
	BYTE lbuf[128]; 
	int lcnt;
	CString str;

	memset(lbuf, 0x20, sizeof(lbuf));

	lbuf[0] = 0x02;

	if(m_cComboRmtSelect.GetCurSel() == 1)
	{
		sprintf((char *)&lbuf[1], "CRSNF");
	}
	else if(m_cComboRmtSelect.GetCurSel() == 2)
	{
		sprintf((char *)&lbuf[1], "CRSNE");
	}
	else if(m_cComboRmtSelect.GetCurSel() == 3)
	{
		sprintf((char *)&lbuf[1], "CRSN2");
	}
	else
	{
		sprintf((char *)&lbuf[1], "CRSND");
	}

	if(lRmtCodeIndex < m_RemoconModel.m_Cnt)
	{
		if(m_cComboSignalCarrier.GetCurSel() == 0)
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
		ComSend(lbuf, 21);

		m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
		 m_ComAck =COM_ACK_WAIT;
		 m_WaitCnt = 0;
		 m_ResendCnt = 0;

		 MessageDisplay(2, "IR CODE Send!!");

	}
	else
	{
		//MessageBox("Send IR CODE FAIL!!");
		MessageDisplay(1, "Send IR CODE FAIL!!");
	}
}


void CDlgTestPage::OnBnClickedButtonRmtest1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[0].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[1].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[2].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[3].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[4].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[5].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[6].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[7].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[8].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[9].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[10].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnBnClickedButtonRmtest12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lRmtCodeIndex = m_cComboRmTest[11].GetCurSel();
	SendIRCode(lRmtCodeIndex);
}


void CDlgTestPage::OnCbnSelchangeComboSelectRmType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	m_ComboRmType.GetLBText(m_ComboRmType.GetCurSel(),str);

	GetRmtCodeList(str);
}



void CDlgTestPage::MessageDisplay(int lError, CString sMessage)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cTpgMessage.put_Caption(sMessage);

	if(lError == 0)
	{
		m_cTpgMessage.put_ForeColor(0x00FF0000);
	}
	else if(lError == 1)
	{
		m_cTpgMessage.put_ForeColor(0x000000FF);
	}
	else if(lError == 2)
	{
		m_cTpgMessage.put_ForeColor(0x0000FFFF);
	}

}
BEGIN_EVENTSINK_MAP(CDlgTestPage, CDialogEx)
	ON_EVENT(CDlgTestPage, IDC_BUTTON_TEST_CONFIG, DISPID_CLICK, CDlgTestPage::ClickButtonTestConfig, VTS_NONE)
	ON_EVENT(CDlgTestPage, IDC_LABEL_LED_UP_DI_1, DISPID_CLICK, CDlgTestPage::ClickLabelLedUpDi1, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgTestPage::ClickButtonTestConfig()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CFileControl lFile;

	//CDlgPassword dlgpw;
	if(m_ComPort.mPort_Opened == TRUE)
		m_ComPort.ClosePort();
		
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
		
	if(m_ComPortLED.mPort_Opened == TRUE)
		m_ComPortLED.ClosePort();
		
	
	//OpenComport();
	//OpenComportPCB();
	//OpenComportLED();

	//dlgpw.m_sPassword = g_strPassword;
	//if(dlgpw.DoModal()==IDOK)
	{
		//m_sPassword.Compare(
		//if(strncmp(m_sPassword.GetBuffer(),dlgpw.m_EditCurrentPW.GetBuffer(), m_sPassword.GetLength()) == 0)
		//if(g_strPassword == dlgpw.m_sPassword)
		{
			CDlgConfig dlg;

		//	dlg.m_nBaud = g_nBaud_Set;
		//	dlg.m_nPort = g_nPort_Set;
		//	dlg.m_nParity = g_nParity_Set;

		//	//dlg.m_nBaudPcb = gTestSeqData.nBaud_Pcb;
		//	//dlg.m_nPortPcb = gTestSeqData.nPort_Pcb;
		//	//dlg.m_nParityPcb = gTestSeqData.nParity_Pcb;
		//	


		//	dlg.m_nBaudLED = g_nBaud_LED;
		//	dlg.m_nPortLED = g_nPort_LED;
		//	dlg.m_nParityLED = g_nParity_LED;

		//	dlg.m_nPortScan  = g_nPort_Scanner;
		//	dlg.m_nBaudScan  = g_nBaud_Scanner;
		//	dlg.m_nParityScan =  g_nParity_Scanner;

		////fprintf(m_fp, "%d %d\n", g_nLocalPortNumber, g_nRemotePortNumber);
		////fprintf(m_fp, "%d %d\n", g_nReplyTimeOut, g_nTransTimeOut);
		////fprintf(m_fp, "%s\n", g_strEQPID.GetString());
		////fprintf(m_fp, "%s\n", g_strEQPName.GetString());	
		////fprintf(m_fp, "%s\n", g_strProcID.GetString());	
		////fprintf(m_fp, "%s\n", g_strORGID.GetString());	
		////fprintf(m_fp, "%s\n", g_strLineID.GetString());
		//	dlg.m_IPaddressGmes = g_nRemoteIPAddress;
		//	//dlg.m_PortNumber.Format(_T("%d"),g_nLocalPortNumber);
		//	dlg.m_ServerPortNumberCM45.Format(_T("%d"),g_nRemotePortNumberCM45);
		//	dlg.m_ServerPortNumberCM89.Format(_T("%d"),g_nRemotePortNumberCM89);
		//	dlg.m_GmesWaitTime.Format(_T("%d"),g_nGmesWaitTime);

		//	dlg.m_nNI_CardSel = g_nNI_CardSel;
		//	//dlg.m_EditMesTnsTimeout.Format(_T("%d"),g_nTransTimeOut);
		//	//dlg.m_EditMesAvnReplyTimeout.Format(_T("%d"),g_nReplyTimeOut);
		//	//dlg.m_EditMesUserID_CEID =  g_strEQPID;
		//	//dlg.m_EditMesPswrdRPTID = g_strORGID;
		//	//dlg.m_EditMesLine =  g_strLineID;
		//	//dlg.m_EditMesInspStep = g_strProcID;

			if(dlg.DoModal()==IDOK)
			{

			//	g_nBaud_Set = dlg.m_nBaud     ;
			//	g_nPort_Set = dlg.m_nPort     ;
			//	g_nParity_Set = dlg.m_nParity   ;

			//	//g_nBaud_Pcb = dlg.m_nBaudPcb  ;
			////	gTestSeqData.nPort_Pcb = dlg.m_nPortPcb  ;
			//	//g_nParity_Pcb = dlg.m_nParityPcb;

			//	g_nBaud_LED = dlg.m_nBaudLED  ;
			//	g_nPort_LED = dlg.m_nPortLED  ;
			//	g_nParity_LED = dlg.m_nParityLED;

			//	g_nPort_Scanner = dlg.m_nPortScan		;
			//	g_nBaud_Scanner = dlg.m_nBaudScan		;
			//	g_nParity_Scanner = dlg.m_nParityScan	;

			//	g_nRemoteIPAddress = dlg.m_IPaddressGmes;
			//	//g_nLocalPortNumber = _ttoi(dlg.m_PortNumber);
			//	g_nRemotePortNumberCM45 = _ttoi(dlg.m_ServerPortNumberCM45);
			//	g_nRemotePortNumberCM89 = _ttoi(dlg.m_ServerPortNumberCM89);
			//	g_nGmesWaitTime = _ttoi(dlg.m_GmesWaitTime);
			//	
			//	if(g_nRemotePortType == LINE_CM89)
			//	{
			//		g_nRemotePortNumber = g_nRemotePortNumberCM89;
			//	}
			//	else
			//	{
			//		g_nRemotePortNumber =  g_nRemotePortNumberCM45;
			//	}
			//	g_nNI_CardSel = dlg.m_nNI_CardSel;
			//	//g_nTransTimeOut = _ttoi(dlg.m_EditMesTnsTimeout);
			//	//g_nReplyTimeOut = _ttoi(dlg.m_EditMesAvnReplyTimeout);
			//	//g_strEQPID = dlg.m_EditMesUserID_CEID  ;
			//	//g_strORGID = dlg.m_EditMesPswrdRPTID ;
			//	//g_strLineID = dlg.m_EditMesLine  ;
			//	//g_strProcID = dlg.m_EditMesInspStep ;


			//	/*g_strMesTns = dlg.m_EditMesTnsTimeout;
			//	g_strMesAvn = dlg.m_EditMesAvnReplyTimeout;
			//	g_strMesUserID = dlg.m_EditMesUserID_CEID ;
			//	g_strMesPassword = dlg.m_EditMesPswrdRPTID ;
			//	g_strMesLine = dlg.m_EditMesLine;
			//	g_strMesInspStep = dlg.m_EditMesInspStep;*/
			//	lFile.SaveConfigSeqData();

			}
		}
		//else
		//{
		//	g_strPassword = dlgpw.m_sPassword;
		//	lFile.SaveConfigSeqData();
		//}
	}

	OpenComport();
	OpenComportPCB();
	OpenComportLED();
}


void CDlgTestPage::OnBnClickedButtonMacSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;
	CString str;
	int i = 0;
	//UINT m_EditFreq1;
	UpdateData();

	if(m_EditNewMac.GetLength() != 6)
	{
		MessageBox("MAC Address Must Be 3Bytes HEX!!");
		return;
	}
	lbuf[0] = 0x02;
	sprintf((char *)&lbuf[1], "CMSET");

	m_EditNewMac.MakeUpper();
	for(i = 0; i < 6 ; i++)
	{
		if(((m_EditNewMac.GetAt(i) >= '0') && (m_EditNewMac.GetAt(i) <= '9'))
			||((m_EditNewMac.GetAt(i) >= 'A') && (m_EditNewMac.GetAt(i) <= 'F')))
		{
			lbuf[6+i] = m_EditNewMac.GetAt(i);
			continue;
		}
		else
		{
			MessageBox("MAC Address Must Be 3Bytes HEX!!");
			return;
		}
	}

	
	
	lbuf[12] = 0x03;
	lbuf[13] = 0x0d;
	lbuf[14] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	ComSend(lbuf, 15);

	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	 m_ComAck =COM_ACK_WAIT;
	 m_WaitCnt = 0;
	 m_ResendCnt = 0;
	
	MessageDisplay(2, "MAC Address Set !");

	m_MAC_SendFlag = 1;
}


void CDlgTestPage::OnBnClickedButtonMacRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
BYTE lbuf[128]; 
	int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CMAC_READ");
	
	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	ComSend(lbuf, 13);

	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_ComAck =COM_ACK_WAIT;
	m_WaitCnt = 0;
	m_ResendCnt = 0;
	MessageDisplay(2, "MAC Address Read!");

	m_MAC_SendFlag = 0;

}


void CDlgTestPage::OnBnClickedButtonLedRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

#if 1
void CDlgTestPage::OnBnClickedButtonPcbSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128];
	int lcnt;

	int lType = m_ComboPcbType.GetCurSel();
	CString Str;
	GetDlgItemText(IDC_EDIT_PCB_COMMAND, Str);

	char lchar = 0;
	Str.MakeUpper();

	lbuf[0] = 0xAA;
	lbuf[1] = 0x03;
	lbuf[2] = lType + 1;


	lchar = Str.GetAt(0);
	if (lchar > 0x39)
	{
		lchar = lchar - 'A' + 0x0A;
	}
	else
	{
		lchar = lchar - 0x30;
	}
	lbuf[3] = lchar * 0x10;

	lchar = Str.GetAt(1);
	if (lchar > 0x39)
	{
		lchar = lchar - 'A' + 0x0A;
	}
	else
	{
		lchar = lchar - 0x30;
	}
	lbuf[3] = lbuf[3] + lchar;



	unsigned char lCheckSum = 0;
	for (int i = 0; i < 4; i++)
	{
		lCheckSum ^= lbuf[i];
	}
	lbuf[4] = lCheckSum;

	memcpy(m_SendBufPCB, lbuf, 5);
	m_SendCntPCB = 5;

	ComPCBSend();

	m_PCB_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_PCBComAck = COM_ACK_WAIT;
	m_PCBWaitCnt = 0;
	m_PCBResendCnt = 0;

	if (m_SendBufPCB[3] == 0xc1)
		m_WaitPCB_Ack_Limit = 500;
	else
		m_WaitPCB_Ack_Limit = 100;


	MessageDisplay(2, "Command Send!");
}

#else

void CDlgTestPage::OnBnClickedButtonPcbSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	int lcnt;

	int lType = m_ComboPcbType.GetCurSel();
	CString Str;
	GetDlgItemText(IDC_EDIT_PCB_COMMAND,Str);

	char lchar = 0;
	Str.MakeUpper();

	lbuf[0] = 0xAA;
	lbuf[1] = 0x03;
	lbuf[2] = lType + 1;


	lchar = Str.GetAt(0);
	if(lchar > 0x39)
	{
		lchar = lchar - 'A' + 0x0A;
	}
	else
	{
		lchar = lchar - 0x30;
	}
	lbuf[3] = lchar * 0x10;

	lchar = Str.GetAt(1);
	if(lchar > 0x39)
	{
		lchar = lchar - 'A' + 0x0A;
	}
	else
	{
		lchar = lchar - 0x30;
	}
	lbuf[3] = lbuf[3] + lchar ;



	unsigned char lCheckSum = 0;
	for(int i = 0; i < 4; i++)
	{
		lCheckSum ^= lbuf[i];
	}
	lbuf[4] = lCheckSum;

	memcpy(m_SendBufPCB, lbuf, 5); 	
	m_SendCntPCB = 5;

	ComPCBSend();

	m_PCB_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_PCBComAck =COM_ACK_WAIT;
	m_PCBWaitCnt = 0;
	m_PCBResendCnt = 0;

	if(m_SendBufPCB[3] == 0xc1)
		m_WaitPCB_Ack_Limit = 500;
	else
		m_WaitPCB_Ack_Limit = 100;


	MessageDisplay(2, "Command Send!");
}
#endif

void CDlgTestPage::OnBnClickedButtonLedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE lbuf[128]; 
	//int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;	
	
	sprintf((char *)&lbuf[1], "CCLEARLED");//CCHECKLED //CLEARLED

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


void CDlgTestPage::OnBnClickedCheckDoLed1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	//m_CheckDO_1


	BYTE lbuf[128]; 


	lbuf[0] = 0x02;	
	
	if(m_CheckDOLED_1)
		sprintf((char *)&lbuf[1], "CDOUT01ON");
	else
		sprintf((char *)&lbuf[1], "CDOUT01OF");

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
	
}


void CDlgTestPage::OnBnClickedCheckDoLed2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		
	UpdateData();

	BYTE lbuf[128];

	lbuf[0] = 0x02;	
	
	if(m_CheckDOLED_2)
		sprintf((char *)&lbuf[1], "CDOUT02ON");
	else
		sprintf((char *)&lbuf[1], "CDOUT02OF");

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


void CDlgTestPage::OnBnClickedCheckDoLed3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData();
	BYTE lbuf[128];

	lbuf[0] = 0x02;	
	
	if(m_CheckDOLED_3)
		sprintf((char *)&lbuf[1], "CDOUT03ON");
	else
		sprintf((char *)&lbuf[1], "CDOUT03OF");

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


void CDlgTestPage::OnBnClickedCheckDoLed4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		UpdateData();

	BYTE lbuf[128]; 

	lbuf[0] = 0x02;	
	
	if(m_CheckDOLED_4)
		sprintf((char *)&lbuf[1], "CDOUT04ON");
	else
		sprintf((char *)&lbuf[1], "CDOUT04OF");

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


void CDlgTestPage::OnBnClickedButtonMic1On()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetFreqSend(4, 10 );
}


void CDlgTestPage::OnBnClickedButtonMic2On()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetFreqSend(5, 10 );
}


void CDlgTestPage::OnBnDoubleclickedButtonMic1On()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//SetFreqSend(4, 0 );
}


void CDlgTestPage::OnBnDoubleclickedButtonMic2On()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//SetFreqSend(5, 0 );
}


void CDlgTestPage::ClickLabelLedUpDi1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	

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

void CDlgTestPage::OnCbnSelchangeComboComportTempPcb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//	int		m_nPortPcb;
	//int		m_nBaudPcb;
	//int		m_nParityPcb;
	//	CComboBox m_cComboPCBTempPort;
	//CComboBox m_cComboTempSetBaud;
	//CComboBox m_cComboTempSetParity;

	m_nPortPcb = nNumberPort[m_cComboPCBTempPort.GetCurSel()];
	m_nBaudPcb = mbaud_List[m_cComboTempSetBaud.GetCurSel()];
	m_nParityPcb = m_cComboTempSetParity.GetCurSel();
	OpenComportPCB();

}


void CDlgTestPage::OnCbnSelchangeComboPcbTempBaud()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_nPortPcb = nNumberPort[m_cComboPCBTempPort.GetCurSel()];
	m_nBaudPcb = mbaud_List[m_cComboTempSetBaud.GetCurSel()];
	m_nParityPcb = m_cComboTempSetParity.GetCurSel();
	OpenComportPCB();
}


void CDlgTestPage::OnCbnSelchangeComboTempPcbParity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_nPortPcb = nNumberPort[m_cComboPCBTempPort.GetCurSel()];
	m_nBaudPcb = mbaud_List[m_cComboTempSetBaud.GetCurSel()];
	m_nParityPcb = m_cComboTempSetParity.GetCurSel();
	OpenComportPCB();
}


void CDlgTestPage::OnBnClickedButtonUpdinRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
	m_LEDComAck = COM_ACK_WAIT;
	m_LEDWaitCnt = 0;
	m_LEDResendCnt = 0;

	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;
	MessageDisplay(2, "UP DI Read!");
}
