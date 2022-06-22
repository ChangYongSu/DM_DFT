// DlgConfig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgConfig.h"
#include "afxdialogex.h"

#include <InitGuid.h>
// CDlgConfig 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgConfig, CDialogEx)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfig::IDD, pParent)
//	, m_EditPortString(_T(""))
	//, m_EditMesTnsTimeout(_T(""))
	//, m_EditMesAvnReplyTimeout(_T(""))
	//, m_EditMesUserID_CEID(_T(""))
	//, m_EditMesPswrdRPTID(_T(""))
	//, m_EditMesLine(_T(""))
	//, m_EditMesInspStep(_T(""))
//	, m_EditSetPortString(_T(""))
//	, m_EditLEDPortString(_T(""))
	//, m_PortNumber(_T(""))
	, m_Edit_RX_Data(_T(""))
	//, m_ServerPortNumber(_T(""))
	, m_GmesWaitTime(_T(""))
{

	m_RecvCnt = 0;
	m_RecvCntPCB = 0;
	m_RecvCntLED = 0;
}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_COMPORT, m_EditPortString);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_cComboBaud);


	//DDX_Text(pDX, IDC_EDIT_MES_TNS, m_EditMesTnsTimeout);
	//DDX_Text(pDX, IDC_EDIT_MES_AVN, m_EditMesAvnReplyTimeout);
	//DDX_Text(pDX, IDC_EDIT_MES_USERID, m_EditMesUserID_CEID);
	//DDX_Text(pDX, IDC_EDIT_MES_PSWRD, m_EditMesPswrdRPTID);
	//DDX_Text(pDX, IDC_EDIT_MES_LINE, m_EditMesLine);
	//DDX_Text(pDX, IDC_EDIT_MES_INSP_STEP, m_EditMesInspStep);


	//DDX_Text(pDX, IDC_EDIT_COMPORT2, m_EditSetPortString);
	//DDX_Text(pDX, IDC_EDIT_COMPORT3, m_EditLEDPortString);

	DDX_Control(pDX, IDC_COMBO_BAUD2, m_cComboSetBaud);
	DDX_Control(pDX, IDC_COMBO_BAUD3, m_cComboLEDBaud);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_cComboParity);
	DDX_Control(pDX, IDC_COMBO_PARITY2, m_cComboSetParity);
	DDX_Control(pDX, IDC_COMBO_PARITY3, m_cComboLedParity);
	//	DDX_Control(pDX, IDC_IPADDRESS_GMES, m_CtrlIpaddressGmes);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT1, m_ServerPortNumberCM45);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT2, m_ServerPortNumberCM89);



	DDX_Control(pDX, IDC_COMBO_PORT_SEARCH, m_cComboPortSel);
	DDX_Control(pDX, IDC_COMBO_BAUD4, m_cComboScanBaud);
	DDX_Control(pDX, IDC_COMBO_PARITY4, m_cComboScanParity);
	DDX_Control(pDX, IDC_COMBO_COMPORT_SCAN, m_cComboScanPort);
	DDX_Control(pDX, IDC_COMBO_COMPORT_LED, m_cComboLEDPort);
	DDX_Control(pDX, IDC_COMBO_COMPORT_PCB, m_cComboPCBPort);
	DDX_Control(pDX, IDC_COMBO_COMPORT_MAIN, m_cComboMainPort);
	DDX_Text(pDX, IDC_EDIT_RX_DATA, m_Edit_RX_Data);
	//	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_ServerPortNumber);
	DDX_Text(pDX, IDC_EDIT_GMES_WAIT, m_GmesWaitTime);
	DDX_Control(pDX, IDC_COMBO_NI_CARD_SEL, m_cComboNI_CardSel);
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgConfig::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PORT_CHECK, &CDlgConfig::OnBnClickedButtonPortCheck)
	ON_WM_TIMER()
	ON_WM_DESTROY()
		
	ON_MESSAGE(WM_COMM_RXCHAR,OnReceiveData)
	ON_MESSAGE(WM_COMM_RXCHAR_PCB,OnReceiveDataPCB)
	ON_MESSAGE(WM_COMM_RXCHAR_LED,OnReceiveDataLED)
	ON_MESSAGE(WM_COMM_RXCHAR_SCAN,OnReceiveDataSCAN)
	ON_BN_CLICKED(IDC_BUTTON_SET_PORT_CHECK, &CDlgConfig::OnBnClickedButtonSetPortCheck)
	ON_BN_CLICKED(IDC_BUTTON_LED_PORT_CHECK2, &CDlgConfig::OnBnClickedButtonLedPortCheck2)
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_PORT_CHECK, &CDlgConfig::OnBnClickedButtonScannerPortCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPORT_SCAN, &CDlgConfig::OnCbnSelchangeComboComportScan)
END_MESSAGE_MAP()


// CDlgConfig 메시지 처리기입니다.

BOOL CDlgConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	mbaud_List[0] = 9600;
	mbaud_List[1] = 19200;
	mbaud_List[2] = 38400;
	mbaud_List[3] = 57600;
	mbaud_List[4] = 115200;
	m_cComboBaud.AddString("9600");
	m_cComboBaud.AddString("19200");
	m_cComboBaud.AddString("38400");
	m_cComboBaud.AddString("57600");
	m_cComboBaud.AddString("115200");
	m_cComboBaud.SetCurSel(4);
	for(int i = 0; i < 5; i++)
	{
		if(m_nBaud == mbaud_List[i])
		{
			m_cComboBaud.SetCurSel(i);
		}
	}

	m_cComboParity.AddString("NONE");
	m_cComboParity.AddString("EVEN");
	m_cComboParity.AddString("ODD");
	m_cComboParity.SetCurSel(m_nParity);


	//m_EditPortString.Format(_T("%d"),m_nPort );
/////////////////////////////////////////////////////

	m_cComboSetBaud.AddString("9600");
	m_cComboSetBaud.AddString("19200");
	m_cComboSetBaud.AddString("38400");
	m_cComboSetBaud.AddString("57600");
	m_cComboSetBaud.AddString("115200");
	m_cComboSetBaud.SetCurSel(4);
	for(int i = 0; i < 5; i++)
	{
		if(m_nBaudPcb == mbaud_List[i])
		{
			m_cComboSetBaud.SetCurSel(i);
		}
	}

	
	m_cComboSetParity.AddString("NONE");
	m_cComboSetParity.AddString("EVEN");
	m_cComboSetParity.AddString("ODD");
	m_cComboSetParity.SetCurSel(m_nParityPcb);


	//m_EditSetPortString.Format(_T("%d"),m_nPortPcb );
////////////////////////////////
	
	m_cComboLEDBaud.AddString("9600");
	m_cComboLEDBaud.AddString("19200");
	m_cComboLEDBaud.AddString("38400");
	m_cComboLEDBaud.AddString("57600");
	m_cComboLEDBaud.AddString("115200");
	m_cComboLEDBaud.SetCurSel(4);
	for(int i = 0; i < 5; i++)
	{
		if(m_nBaudLED == mbaud_List[i])
		{
			m_cComboLEDBaud.SetCurSel(i);
		}
	}

	
	m_cComboLedParity.AddString("NONE");
	m_cComboLedParity.AddString("EVEN");
	m_cComboLedParity.AddString("ODD");
	m_cComboLedParity.SetCurSel(m_nParityLED);


//	m_EditLEDPortString.Format(_T("%d"),m_nPortLED );

	
		
	m_cComboScanBaud.AddString("9600");
	m_cComboScanBaud.AddString("19200");
	m_cComboScanBaud.AddString("38400");
	m_cComboScanBaud.AddString("57600");
	m_cComboScanBaud.AddString("115200");
	m_cComboScanBaud.SetCurSel(0);
	for(int i = 0; i < 5; i++)
	{
		if(m_nBaudScan == mbaud_List[i])
		{
			m_cComboScanBaud.SetCurSel(i);
		}
	}

	
	m_cComboScanParity.AddString("NONE");
	m_cComboScanParity.AddString("EVEN");
	m_cComboScanParity.AddString("ODD");
	m_cComboScanParity.SetCurSel(m_nParityScan);


	SetDlgItemText(IDC_IPADDRESS_GMES,m_IPaddressGmes);

	m_cComboNI_CardSel.SetCurSel(m_nNI_CardSel);

	/*	
		
int		m_nPortSet;
int		m_nBaudSet;
int		m_nParitySet;

		
int		m_nPortLED;
int		m_nBaudLED;
int		m_nParityLED;	CString m_EditMesLine;
CString m_EditMesInspStep;
CString m_EditSetPortString;
CString m_EditLEDPortString;
CComboBox m_cComboSetBaud;
CComboBox m_cComboLEDBaud;
CComboBox m_cComboParity;
CComboBox m_cComboSetParity;
CComboBox m_cComboLedParity;
		*/


	UpdateData(FALSE);

	ComportSearch();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgConfig::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//nNumberPort[50];
	//int			m_PortCnt;
	UpdateData(TRUE);
	int l_port = 0;
	int lBaud = 0;
	int lParity = 0;

	if(m_PortCnt <= 0)
	{
	//	return;
	}
	else
	{
		l_port = nNumberPort[m_cComboMainPort.GetCurSel()];
		if((l_port > 0)&&(l_port < 128))
		{
			m_nPort = l_port;	
		}
		
		l_port =nNumberPort[m_cComboPCBPort.GetCurSel()];	
		if((l_port > 0)&&(l_port < 128))
		{
			m_nPortPcb = l_port;	
		}

		l_port = nNumberPort[m_cComboLEDPort.GetCurSel()];	
		if((l_port > 0)&&(l_port < 128))
		{
			m_nPortLED = l_port;	
		}

		l_port = nNumberPort[m_cComboScanPort.GetCurSel()];	
		if((l_port > 0)&&(l_port < 128))
		{
			m_nPortScan = l_port;	
		}
	}

	lBaud = mbaud_List[m_cComboBaud.GetCurSel()];
	if((lBaud >= 9600)&&(lBaud <= 115200))
	{
		m_nBaud = lBaud;	
	}

	lParity = m_cComboParity.GetCurSel();
	if((lParity >= 0)&&(lParity <= 2))
	{
		m_nParity = lParity;	
	}




	lBaud = mbaud_List[m_cComboSetBaud.GetCurSel()];
	if((lBaud >= 9600)&&(lBaud <= 115200))
	{
		m_nBaudPcb = lBaud;	
	}
	lParity = m_cComboSetParity.GetCurSel();
	if((lParity >= 0)&&(lParity <= 2))
	{
		m_nParityPcb = lParity;	
	}


	lBaud =  mbaud_List[m_cComboLEDBaud.GetCurSel()];
	if((lBaud >= 9600)&&(lBaud <= 115200))
	{
		m_nBaudLED = lBaud;	
	}
	lParity = m_cComboLedParity.GetCurSel();
	if((lParity >= 0)&&(lParity <= 2))
	{
		m_nParityLED = lParity;	
	}



	lBaud =  mbaud_List[m_cComboScanBaud.GetCurSel()];
	if((lBaud >= 9600)&&(lBaud <= 115200))
	{
		m_nBaudScan = lBaud;	
	}
	lParity = m_cComboScanParity.GetCurSel();
	if((lParity >= 0)&&(lParity <= 2))
	{
		m_nParityScan = lParity;	
	}

	//
	//CString m_EditMesTnsTimeout;
	//CString m_EditMesAvnReplyTimeout;
	//CString m_EditMesUserID_CEID;
	//CString m_EditMesPswrdRPTID;
	//CString m_EditMesLine;
	//CString m_EditMesInspStep;
		
	//m_IPaddressGmes = m_CtrlIpaddressGmes.get

	GetDlgItemText(IDC_IPADDRESS_GMES,m_IPaddressGmes);
	
	//m_PortNumber;		
	//m_IPaddressGmes;//m_CtrlIpaddressGmes
	int l_nNI_CardSel = m_cComboNI_CardSel.GetCurSel();
	if ((l_nNI_CardSel >= 0) && (l_nNI_CardSel <= 2))
	{
		m_nNI_CardSel = l_nNI_CardSel;
	}

	CDialogEx::OnOK();
}



void CDlgConfig::OpenComport()
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
		MessageBox(str);
		//MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
	}
}

void CDlgConfig::OpenComportPCB()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
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
	if(m_ComPortPCB.InitPort(this, g_nPort_Pcb,gTestSeqData.nBaud_Pcb, lParityChar[gTestSeqData.nParity_Pcb], 8, 1, EV_RXCHAR, 4096 ))//
	{		
		m_ComPortPCB.StartMonitoring();
		m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
	}
	else
	{
		str.Format(_T("Audio COM Port %d Open FAIL !!"),  g_nPort_Pcb);
		MessageBox(str);
		//MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
	}

	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_PCB;
}

void CDlgConfig::OpenComportLED()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
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
		
		/*StatusDisplayMsg(str, 1 );*/
	}
	m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_LED;
}


void CDlgConfig::ComportSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	CString strTempCom;

	int ArrPort[256];
	SearchPort( ArrPort);
	GetDeviceInfo();

	m_cComboPortSel.ResetContent();
	m_cComboMainPort.ResetContent();
	m_cComboScanPort.ResetContent();
	m_cComboLEDPort.ResetContent();
	m_cComboPCBPort.ResetContent();
	/*		m_cComboMainPort.SetCurSel(i);
			m_cComboPCBPort.SetCurSel(i);
				m_cComboLEDPort.SetCurSel(i);
				m_cComboScanPort.SetCurSel(i);*/
		

	if(m_PortCnt > 0)
	{
		for(int i = 0; i < m_PortCnt; i++)
		{		
			m_cComboPortSel.AddString(strPort[i]);

			strTemp = strPort[i].Mid(strPort[i].Find("COM")+3);
			strTemp = strTemp.Left(strTemp.Find(")"));

			strTempCom = strPort[i].Mid(strPort[i].Find("COM"));
			strTempCom = strTempCom.Left(strTempCom.Find(")"));
				
			m_cComboMainPort.AddString(strTempCom);
			m_cComboScanPort.AddString(strTempCom);
			m_cComboLEDPort.AddString(strTempCom);
			m_cComboPCBPort.AddString(strTempCom);

		
			nNumberPort[i] = _ttoi(strTemp);

			if(m_nPort == nNumberPort[i])
			{
				m_cComboMainPort.SetCurSel(i);
			}
			if(m_nPortPcb == nNumberPort[i])
			{
				m_cComboPCBPort.SetCurSel(i);
			}
			if(m_nPortLED == nNumberPort[i])
			{
				m_cComboLEDPort.SetCurSel(i);
			}
			if(m_nPortScan == nNumberPort[i])
			{
				m_cComboScanPort.SetCurSel(i);
			}
					
	
		}
		m_cComboPortSel.SetCurSel(0);	

		strTemp.Format(_T("컴포트 %d개가 검색되었습니다."), m_cComboPortSel.GetCount());
		MessageBox(strTemp);		
				
	}
	else
	{
		MessageBox("사용가능한 통신 포트가 없습니다.");
	}




	//for(int i = 1; i < 64; i++)
	//{
	//	if(mComport.m_bConnected)
	//	{
	//		mComport.ClosePort();
	//	}
	//	if(mComport.InitPort(this, (UINT)i, 115200, 'N', 8, 1, EV_RXCHAR, 4096 ))
	//	{
	//		mComport.ClosePort();
	//		strTemp.Format(_T("COM %d"), i);
	//		m_cComboPortSel.AddString(strTemp);	
	//		if(m_nPort == i)
	//		{
	//			m_cComboPortSel.SetCurSel(m_cComboPortSel.GetCount()-1);
	//		}			
	//	}
	//	m_cProgress_Search.SetPos(i*100/64);

	//}
	//m_cProgress_Search.SetPos(100);
	//if(m_cComboPortSel.GetCount() > 0)
	//{
	//	if(m_cComboPortSel.GetCurSel() <= 0)
	//		m_cComboPortSel.SetCurSel(0);	

	//	strTemp.Format(_T("컴포트 %d개가 검색되었습니다."), m_cComboPortSel.GetCount());
	//	SetDlgItemText(IDC_STATIC_STATUS, strTemp);		
	//}
	//else
	//{
	//	MessageBox("사용가능한 통신 포트가 없습니다.");
	//}	
}

void CDlgConfig::SearchPort(int* ArrPort)
{
	//HKEY h_CommKey;
 //   LONG Reg_Ret;
 //   DWORD Size = MAX_PATH;
 //   char i_str[MAX_PATH];
	//LPCSTR path=_T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	//	
 //   Reg_Ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE,path, 0, KEY_READ | KEY_QUERY_VALUE, &h_CommKey);   
	//
	//int ArrayPort[MAX_PATH]={0,};

	//ArrPort[0] = 0;

	//if(Reg_Ret == ERROR_SUCCESS)
	//{
	//	for(int i = 0; Reg_Ret == ERROR_SUCCESS; i++)
	//	{
	//		Reg_Ret = RegEnumValue(h_CommKey, i, i_str, &Size, NULL, NULL, NULL, NULL);
	//		if(Reg_Ret == ERROR_SUCCESS)
	//		{
	//				DWORD dwType, dwSize = MAX_PATH;
	//				char szBuffer[MAX_PATH];
 //   
	//				RegQueryValueEx(h_CommKey, i_str, 0, &dwType, (LPBYTE)szBuffer, &dwSize);
	//						
	//				if(szBuffer != "")
	//				{
	//					ArrPort[0] ++;
	//					if(szBuffer[4]==0)
	//					{
	//						ArrPort[i+1] = szBuffer[3]-48;
	//					}
	//					else if(szBuffer[5]==0)
	//					{
	//						ArrPort[i+1] = (szBuffer[3]-48)*10 +(szBuffer[4]-48);
	//					}
	//				}
	//		}
	//		Size = MAX_PATH;
	//	}
	//}

	//return ArrayPort;
}


DEFINE_GUID( GUID_PCIE,                 0x4d36e978L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 );

void CDlgConfig::GetDeviceInfo()
{
	m_PortCnt = 0;
	GUID Input_GUID = GUID_PCIE;//GUID_DEVINTERFACE_USB_DEVICE;
	HDEVINFO hDevInfo = SetupDiGetClassDevs( &Input_GUID, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
    if(hDevInfo == INVALID_HANDLE_VALUE)
    {
        return ;
    }
	DWORD i = 0;

    for ( i = 0; true; ++i)
    {
        SP_DEVINFO_DATA devInfo;
        devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL succ = SetupDiEnumDeviceInfo(hDevInfo, i, &devInfo);
        if (GetLastError() == ERROR_NO_MORE_ITEMS)
            break;
        if (!succ) continue;

        SP_INTERFACE_DEVICE_DATA ifInfo;
		
        ifInfo.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
        if (TRUE != SetupDiEnumDeviceInterfaces(hDevInfo, &devInfo,  &(Input_GUID), 0, &ifInfo))
        {
            if (GetLastError() != ERROR_NO_MORE_ITEMS)
                break;
        }
        interfaces.push_back(ifInfo);

		
	//	WCHAR  szDesc[MAX_PATH] = {0};
		char  szDesc[MAX_PATH] = {0};
		SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfo,
													  SPDRP_DEVICEDESC,
													  0L,
													  (PBYTE)szDesc,
													  2048,
													  0);
	//	wchar_t  szFriendly[MAX_PATH] = {0};
		char  szFriendly[MAX_PATH] = {0};
		SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfo,
													  SPDRP_FRIENDLYNAME,
													  0L,
													  (PBYTE)szFriendly,
													  2048,
													  0);
		

        DWORD requiredSize = 0;
        SetupDiGetDeviceInterfaceDetail(hDevInfo, &(interfaces.at(i)), NULL, NULL, &requiredSize, NULL);
        SP_INTERFACE_DEVICE_DETAIL_DATA* data = (SP_INTERFACE_DEVICE_DETAIL_DATA*) malloc(requiredSize);

        data->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

        if (!SetupDiGetDeviceInterfaceDetail(hDevInfo, &(interfaces.at(i)), data, requiredSize, NULL, NULL))
        {
            continue;
        }
		
		//m_List.AddString(_T("Desc	: ") + CString(szDesc) + _T("\r\n"));
		//m_List.AddString(_T("Name	: ") + CString(szFriendly) + _T("\r\n"));
		//m_List.AddString(_T("Path	: ") + CString(data->DevicePath) + _T("\r\n"));
		//m_List.AddString(_T("\r\n"));

		CString str;
		str = szDesc;

		CString str1(szFriendly);
		CString str2(data->DevicePath);
		//strPort[i] = str;
		strPort[i] = str1;
		//strPort[i] += str2;


	//	strPort[i].Format( _T("Desc	: %ws %ws %s") ,(CString)szDesc , (CString)szFriendly , (CString)data->DevicePath);
		
        devicePaths.push_back(data);

		delete data;
		if(i >= 49)
			break;
    }

	m_PortCnt = i;
	//if(m_Port.InitPort(this, CString(devicePaths[1]->DevicePath), 19200, 'N', 8, 1,  EV_RXCHAR, 4096 ))
	//{		
	//	m_Port.m_hWnd_ToSend = this->m_hWnd;
	//	m_Port.StartMonitoring();
	//}

}



void CDlgConfig::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// PORTCHEK_MODE_IDLE__
//#define PORTCHEK_MODE_MAIN__		1
//#define PORTCHEK_MODE_PCBSET__		2
//#define PORTCHEK_MODE_LEDCHECK__	3
	CString str;

	KillTimer(1);
	switch(m_CheckMode)
	{
	case PORTCHEK_MODE_IDLE__:
		break;

	case PORTCHEK_MODE_MAIN__:
				m_WaitCnt++;
		

		if(m_ComAck == COM_ACK_OK)
		{
			//m_EditPortString.Format(_T("%d"), nNumberPort[m_PortCntCurrent]);
			m_cComboMainPort.SetCurSel(m_PortCntCurrent);
		
			UpdateData(FALSE);
			m_CheckMode = PORTCHEK_MODE_IDLE__;
			if(m_ComPort.mPort_Opened)
			{
				m_ComPort.ClosePort();
			}
			str.Format(_T("Main Com Port Found COM%d ."), nNumberPort[m_PortCntCurrent]);

			MessageBox(str);
		}
		else
		{
			if(m_WaitCnt > 20)
			{
				m_ComAck = COM_ACK_WAIT;
				m_WaitCnt = 0;

				m_PortCntCurrent++;

				if(m_PortCnt > m_PortCntCurrent)
				{

					if(m_ComPort.mPort_Opened)
					{
						m_ComPort.ClosePort();
					}
					if(m_ComPort.InitPort(this, nNumberPort[m_PortCntCurrent], 19200, 'N', 8, 1, EV_RXCHAR, 4096 ))
					{		
						m_ComPort.StartMonitoring();
					}
					else
					{
						str.Format(_T("Set COM Port Open FAIL !!"));
						MessageBox(str);
						//MessageDisplay(1, str);
						/*StatusDisplayMsg(str, 1 );*/
					}
				}
				else
				{
					str.Format(_T("MAIN COM Port Search FAIL !!"));
					MessageBox(str);
					m_CheckMode = PORTCHEK_MODE_IDLE__;
					if(m_ComPort.mPort_Opened)
					{
						m_ComPort.ClosePort();
					}
				}
			}
		}

	


	
		break;

	case PORTCHEK_MODE_PCBSET__:
		m_WaitCnt++;
		
	
		if(m_PCBComAck == COM_ACK_OK)
		{
			//m_EditSetPortString.Format(_T("%d"), nNumberPort[m_PortCntCurrent]);
			m_cComboPCBPort.SetCurSel(m_PortCntCurrent);
				

			UpdateData(FALSE);
			m_CheckMode = PORTCHEK_MODE_IDLE__;
			if(m_ComPortPCB.mPort_Opened)
			{
				m_ComPortPCB.ClosePort();
			}

			
			str.Format(_T("SET Com Port Found COM%d ."), nNumberPort[m_PortCntCurrent]);

			MessageBox(str);
		}
		else
		{
			
			if(m_WaitCnt > 30)
			{
				m_ComAck = COM_ACK_WAIT;
				m_WaitCnt = 0;

				m_PortCntCurrent++;

				if(m_PortCnt > m_PortCntCurrent)
				{					

					if(m_ComPortPCB.mPort_Opened)
					{
						m_ComPortPCB.ClosePort();
					}
				//	if(m_ComPortPCB.InitPort(this, nNumberPort[m_PortCntCurrent], 57600, 'N', 8, 1, EV_RXCHAR, 4096 ))
					char lParityChar[3] = {'N', 'E', 'O'};		
					m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
					if(m_ComPortPCB.InitPort(this, nNumberPort[m_PortCntCurrent], mbaud_List[m_cComboSetBaud.GetCurSel()], lParityChar[m_cComboSetParity.GetCurSel()], 8, 1, EV_RXCHAR, 4096 )) 
					{		
						m_ComPortPCB.StartMonitoring();
						
					}
					else
					{
						str.Format(_T("SET COM Port %d Open FAIL !!"), nNumberPort[m_PortCntCurrent]);
						MessageBox(str);
						//MessageDisplay(1, str);
						/*StatusDisplayMsg(str, 1 );*/
					}
				}
				else
				{
					str.Format(_T("SET COM Port Search FAIL !!"));
					MessageBox(str);
					m_CheckMode = PORTCHEK_MODE_IDLE__;
					if(m_ComPortPCB.mPort_Opened)
					{
						m_ComPortPCB.ClosePort();
					}
				}
			}
			else if(m_WaitCnt%5 == 0)
			{
				ComPCBSend();
			}
		}
		break;
	



	case PORTCHEK_MODE_LEDCHECK__:

			m_WaitCnt++;
		/*	m_CheckMode = PORTCHEK_MODE_MAIN__;*/

	//		CString m_EditSetPortString;
	//CString m_EditLEDPortString;
	
		if(m_LEDComAck == COM_ACK_OK)
		{
			//m_EditLEDPortString.Format(_T("%d"), nNumberPort[m_PortCntCurrent]);
				
			m_cComboLEDPort.SetCurSel(m_PortCntCurrent);
			//	CComboBox m_cComboScanPort;

			UpdateData(FALSE);
			m_CheckMode = PORTCHEK_MODE_IDLE__;
			if(m_ComPortLED.mPort_Opened)
			{
				m_ComPortLED.ClosePort();
			}

			
			str.Format(_T("LED Com Port Found COM%d ."), nNumberPort[m_PortCntCurrent]);

			MessageBox(str);
		}
		else
		{
			
			if(m_WaitCnt > 20)
			{
				m_ComAck = COM_ACK_WAIT;
				m_WaitCnt = 0;

				m_PortCntCurrent++;

				if(m_PortCnt > m_PortCntCurrent)
				{					

					if(m_ComPortLED.mPort_Opened)
					{
						m_ComPortLED.ClosePort();
					}
					if(m_ComPortLED.InitPort(this, nNumberPort[m_PortCntCurrent], 19200, 'N', 8, 1, EV_RXCHAR, 4096 ))
					{		
						m_ComPortLED.StartMonitoring();
						ComLedRead();
					}
					else
					{
						str.Format(_T("LED COM Port %d Open FAIL !!"),nNumberPort[m_PortCntCurrent]);
						MessageBox(str);
						//MessageDisplay(1, str);
						/*StatusDisplayMsg(str, 1 );*/
					}
				}
				else
				{
					str.Format(_T("LED COM Port Search FAIL !!"));
					MessageBox(str);
					m_CheckMode = PORTCHEK_MODE_IDLE__;
					if(m_ComPortLED.mPort_Opened)
					{
						m_ComPortLED.ClosePort();
					}
				}
			}
			else if(m_WaitCnt%5 == 0)
			{
				ComLedRead();
			}
		}
		break;

	case PORTCHEK_MODE_SCANCHECK__:

	//		m_WaitCnt++;
	//	/*	m_CheckMode = PORTCHEK_MODE_MAIN__;*/

	////		CString m_EditSetPortString;
	////CString m_EditLEDPortString;
	//
	//	if(m_SCANComAck == COM_ACK_OK)
	//	{
	//		m_EditLEDPortString.Format(_T("%d"), nNumberPort[m_PortCntCurrent]);
	//		UpdateData(FALSE);
	//		m_CheckMode = PORTCHEK_MODE_IDLE__;
	//		if(m_ComPortLED.mPort_Opened)
	//		{
	//			m_ComPortLED.ClosePort();
	//		}

	//		
	//		str.Format(_T("LED Com Port Found COM%d ."), nNumberPort[m_PortCntCurrent]);

	//		MessageBox(str);
	//	}
	//	else
	//	{
	//		
	//		if(m_WaitCnt > 20)
	//		{
	//			m_ComAck = COM_ACK_WAIT;
	//			m_WaitCnt = 0;

	//			m_PortCntCurrent++;

	//			if(m_PortCnt > m_PortCntCurrent)
	//			{					

	//				if(m_ComPortLED.mPort_Opened)
	//				{
	//					m_ComPortLED.ClosePort();
	//				}
	//				if(m_ComPortLED.InitPort(this, nNumberPort[m_PortCntCurrent], 19200, 'N', 8, 1, EV_RXCHAR, 4096 ))
	//				{		
	//					m_ComPortLED.StartMonitoring();
	//					ComLedRead();
	//				}
	//				else
	//				{
	//					str.Format(_T("LED COM Port %d Open FAIL !!"),nNumberPort[m_PortCntCurrent]);
	//					MessageBox(str);
	//					//MessageDisplay(1, str);
	//					/*StatusDisplayMsg(str, 1 );*/
	//				}
	//			}
	//			else
	//			{
	//				str.Format(_T("LED COM Port Search FAIL !!"));
	//				MessageBox(str);
	//				m_CheckMode = PORTCHEK_MODE_IDLE__;
	//				if(m_ComPortLED.mPort_Opened)
	//				{
	//					m_ComPortLED.ClosePort();
	//				}
	//			}
	//		}
	//		else if(m_WaitCnt%5 == 0)
	//		{
	//			ComLedRead();
	//		}
	//	}
		break;
	default:
		m_CheckMode = PORTCHEK_MODE_IDLE__;
		m_WaitCnt++;
		break;

	}

	SetTimer(1, 50, NULL);
	CDialogEx::OnTimer(nIDEvent);
}




void CDlgConfig::ComSend()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	//if(m_ComPort.mPort_Opened)
	//{
	//	memcpy(m_SendBuf, lbuf, lcnt); 
	//	m_SendCnt = lcnt;
	//	m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
	//}
	//else
	//{
	//	OpenComport();
	//	//MessageBox(_T("Com Port Not Opened !!"));
	//	if(m_ComPort.mPort_Opened)
	//	{
	//		memcpy(m_SendBuf, lbuf, lcnt); 
	//		m_SendCnt = lcnt;
	//		m_ComPort.WriteToPort(m_SendBuf, m_SendCnt);
	//	}
	//}

		m_WaitCnt = 0;
}

void CDlgConfig::ComLedRead()
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
	

	//memcpy(m_SendBufLED, lbuf, 13); 	
	//m_SendCntLED = 13;

	//ComLedRead();

	if(m_ComPortLED.mPort_Opened)
	{
		
		m_ComPortLED.WriteToPort(lbuf, 13);
	}
	
	//m_WaitCnt = 0;

}

void CDlgConfig::ComPCBSend()
{
	
	BYTE lbuf[128]; 
	int lcnt;

//int lType = m_ComboPcbType.GetCurSel();
	CString Str;
	GetDlgItemText(IDC_EDIT_PCB_COMMAND,Str);

	char lchar = 0;
	Str.MakeUpper();

	lbuf[0] = 0xAA;
	lbuf[1] = 0x03;
	lbuf[2] = 0x01;


	lbuf[3] = 0x2D;

	unsigned char lCheckSum = 0;
	for(int i = 0; i < 4; i++)
	{
		lCheckSum ^= lbuf[i];
	}
	lbuf[4] = lCheckSum;

	//	void ComSend(BYTE lbuf, int lcnt);
	if(m_ComPortPCB.mPort_Opened)
	{
		
		m_ComPortPCB.WriteToPort(lbuf, 5);
	}
	
}


//extern unsigned char TransBuff[4096];
long CDlgConfig::OnReceiveData(WPARAM wParam, LPARAM lParam )
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

		if(m_RecvBuf[0] == '@')
		{
			if(m_RecvCnt >= 5) 
			{
				if(m_RecvBuf[4] == '#')
				{
					m_ComAck = COM_ACK_OK;
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


long CDlgConfig::OnReceiveDataPCB(WPARAM wParam, LPARAM lParam )
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


long CDlgConfig::OnReceiveDataLED(WPARAM wParam, LPARAM lParam )
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
					m_RecvCntLED = 0;
				}					
				else
				{
					m_LEDComAck = COM_ACK_BUSY;				
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


long CDlgConfig::OnReceiveDataSCAN(WPARAM wParam, LPARAM lParam )
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
	//	int m_LED_COM_PROCESS;
	//int m_LEDComAck;
	//int m_LEDWaitCnt;
	//int m_LEDResendCnt;

	if(m_RecvCntSCAN > 3)
	{
		if((m_RecvBufSCAN[m_RecvCntSCAN-2] == 0x0d) && (m_RecvBufSCAN[m_RecvCntSCAN-1] == 0x0a))
		{
			m_RecvBufSCAN[m_RecvCntSCAN] = 0;
			m_Edit_RX_Data = m_RecvBufSCAN;
			m_RecvCntSCAN = 0;	
			UpdateData(FALSE);
		}
		else if(m_RecvCntSCAN >= 30)
		{
			m_RecvBufSCAN[m_RecvCntSCAN] = 0;
			m_Edit_RX_Data = (char *)m_RecvBufSCAN;
			m_RecvCntSCAN = 0;
			UpdateData(FALSE);
		}
	}
	
	

	return 0;
}

void CDlgConfig::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.



	//m_ComPort.ClosePort();
	if(m_ComPort.mPort_Opened == TRUE)
		m_ComPort.ClosePort();
		
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
		
	if(m_ComPortLED.mPort_Opened == TRUE)
		m_ComPortLED.ClosePort();

	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}	

	
}



void CDlgConfig::OnBnClickedButtonPortCheck()
{
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
				

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
					

	if(m_ComPortLED.mPort_Opened)
	{
		m_ComPortLED.ClosePort();
	}

	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}		
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;



	if(m_PortCnt > 0)
	{
		m_PortCntCurrent = 0;

		if(m_ComPort.mPort_Opened)
		{
			m_ComPort.ClosePort();
		}
		if(m_ComPort.InitPort(this, nNumberPort[m_PortCntCurrent], 19200, 'N', 8, 1, EV_RXCHAR, 4096 ))
		{		
			m_ComPort.StartMonitoring();
			m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR;
		}
		else
		{
			str.Format(_T("Set COM Port %d Open FAIL !!"),  g_nPort_Set, g_nBaud_Set);
			MessageBox(str);
			//MessageDisplay(1, str);
			/*StatusDisplayMsg(str, 1 );*/
		}
	}

	m_CheckMode = PORTCHEK_MODE_MAIN__;

	m_ComAck = COM_ACK_WAIT;
	m_WaitCnt = 0;

	SetTimer(1, 50, NULL);

	//	UINT		nNumberPort[50];
}
	//int m_ComAck;	
	//int m_LEDComAck;	
	//int m_PCBComAck;
// PORTCHEK_MODE_IDLE__
//#define PORTCHEK_MODE_MAIN__		1
//#define PORTCHEK_MODE_PCBSET__		2
//#define PORTCHEK_MODE_LEDCHECK__	3

void CDlgConfig::OnBnClickedButtonSetPortCheck()
{
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
				

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
					

	if(m_ComPortLED.mPort_Opened)
	{
		m_ComPortLED.ClosePort();
	}

	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}		
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	//	m_nBaudPcb = mbaud_List[m_cComboSetBaud.GetCurSel()];
	//m_nParityPcb = m_cComboSetParity.GetCurSel();
//	char lParityChar[3] = {'N', 'E', 'O'};
	if(m_PortCnt > 0)
	{
		m_PortCntCurrent = 0;

		if(m_ComPortPCB.mPort_Opened)
		{
			m_ComPortPCB.ClosePort();
		}
		char lParityChar[3] = {'N', 'E', 'O'};
		if(m_ComPortPCB.InitPort(this, nNumberPort[m_PortCntCurrent], mbaud_List[m_cComboSetBaud.GetCurSel()], lParityChar[m_cComboSetParity.GetCurSel()], 8, 1, EV_RXCHAR, 4096 ))
		{		
			m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
			m_ComPortPCB.StartMonitoring();
			ComPCBSend();
			
		}
		else
		{
			str.Format(_T("Audio SET COM Port %d Open FAIL !!"),nNumberPort[m_PortCntCurrent]);
			MessageBox(str);
			//MessageDisplay(1, str);
			/*StatusDisplayMsg(str, 1 );*/
		}
	}

	SetTimer(1, 50, NULL);

	m_CheckMode = PORTCHEK_MODE_PCBSET__;

	m_PCBComAck = COM_ACK_WAIT;
	m_WaitCnt = 0;


}

// PORTCHEK_MODE_IDLE__
//#define PORTCHEK_MODE_MAIN__		1
//#define PORTCHEK_MODE_PCBSET__		2
//#define PORTCHEK_MODE_LEDCHECK__	3



void CDlgConfig::OnBnClickedButtonLedPortCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
				

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
					

	if(m_ComPortLED.mPort_Opened)
	{
		m_ComPortLED.ClosePort();
	}

	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}		
	CString str;
	if(m_PortCnt > 0)
	{
		m_PortCntCurrent = 0;

		if(m_ComPortLED.mPort_Opened)
		{
			m_ComPortLED.ClosePort();
		}

		char lParityChar[3] = {'N', 'E', 'O'};
		if(m_ComPortLED.InitPort(this, nNumberPort[m_PortCntCurrent], 
			mbaud_List[m_cComboLEDBaud.GetCurSel()],
			lParityChar[m_cComboLedParity.GetCurSel()], 8, 1, EV_RXCHAR, 4096 ))
		{		
			m_ComPortLED.StartMonitoring();
			m_ComPortLED.m_RxMessageID = WM_COMM_RXCHAR_LED;
			ComLedRead();
		}
		else
		{
			str.Format(_T("LED COM Port %d Open FAIL !!"), nNumberPort[m_PortCntCurrent]);
			MessageBox(str);
			//MessageDisplay(1, str);
			/*StatusDisplayMsg(str, 1 );*/
		}
	}

	SetTimer(1, 50, NULL);
	m_CheckMode = PORTCHEK_MODE_LEDCHECK__;

	m_LEDComAck = COM_ACK_WAIT;
	m_WaitCnt = 0;
}
	//int		m_nPortPcb;
	//int		m_nBaudPcb;
	//int		m_nParityPcb;
//CSerialPort m_ComPort;
//CSerialPort m_ComPortPCB;
//CSerialPort m_ComPortLED;
	//	
	//int		m_nPortLED;
	//int		m_nBaudLED;
//int		m_nParityLED;

void CDlgConfig::OnBnClickedButtonScannerPortCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_ComPort.mPort_Opened)
	{
		m_ComPort.ClosePort();
	}
				

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
					

	if(m_ComPortLED.mPort_Opened)
	{
		m_ComPortLED.ClosePort();
	}

	if(m_ComPortScanner.mPort_Opened)
	{
		m_ComPortScanner.ClosePort();
	}			

	CString str;
	if(m_PortCnt > 0)
	{
		m_PortCntCurrent = m_cComboScanPort.GetCurSel();

		
//		if(m_ComPortScanner.InitPort(this, nNumberPort[m_PortCntCurrent], 9600, 'N', 8, 1, EV_RXCHAR, 4096 ))
		char lParityChar[3] = {'N', 'E', 'O'};
		if(m_ComPortScanner.InitPort(this, nNumberPort[m_PortCntCurrent], mbaud_List[m_cComboScanBaud.GetCurSel()], lParityChar[m_cComboScanParity.GetCurSel()], 8, 1, EV_RXCHAR, 4096 ))
		
		{		
			m_ComPortScanner.StartMonitoring();
			m_ComPortScanner.m_RxMessageID = WM_COMM_RXCHAR_SCAN;
			
		}
		else
		{
			str.Format(_T("Scanner COM Port %d Open FAIL !!"),nNumberPort[m_PortCntCurrent] );
			MessageBox(str);
			//MessageDisplay(1, str);
			/*StatusDisplayMsg(str, 1 );*/
		}
	}
		m_Edit_RX_Data = "";
	m_RecvCntSCAN = 0;	
	UpdateData(FALSE);
	//SetTimer(1, 50, NULL);
	//m_CheckMode = PORTCHEK_MODE_SCANCHECK__;

	//m_SCANComAck = COM_ACK_WAIT;
	//m_WaitCnt = 0;
}


void CDlgConfig::OnCbnSelchangeComboComportScan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Edit_RX_Data = "";
	m_RecvCntSCAN = 0;	
	UpdateData(FALSE);

	CString str;
	if(m_PortCnt > 0)
	{
		m_PortCntCurrent = m_cComboScanPort.GetCurSel();

		if(m_ComPortScanner.mPort_Opened)
		{
			m_ComPortScanner.ClosePort();
		}
			
		char lParityChar[3] = {'N', 'E', 'O'};
		if(m_ComPortScanner.InitPort(this, nNumberPort[m_PortCntCurrent], mbaud_List[m_cComboScanBaud.GetCurSel()], lParityChar[m_cComboScanParity.GetCurSel()], 8, 1, EV_RXCHAR, 4096 ))
		{		
			m_ComPortScanner.StartMonitoring();
			m_ComPortScanner.m_RxMessageID = WM_COMM_RXCHAR_SCAN;
			
		}
		else
		{
			str.Format(_T("Scanner COM Port %d Open FAIL !!"),nNumberPort[m_PortCntCurrent]);
			MessageBox(str);
			//MessageDisplay(1, str);
			/*StatusDisplayMsg(str, 1 );*/
		}
	}

	m_Edit_RX_Data = "";
	m_RecvCntSCAN = 0;	
	UpdateData(FALSE);
}
