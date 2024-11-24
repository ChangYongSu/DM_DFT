// COptComportPage.cpp: 구현 파일
//


#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptComportPage.h"
//#include "afxdialogex.h"
#include <InitGuid.h>
#include "FileControl.h"

#include "Global.h"
extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg;
extern CAcqVoltageSamples_IntClkDlg* g_pView;
// COptComportPage 
IMPLEMENT_DYNCREATE(COptComportPage, CPropertyPage)

COptComportPage::COptComportPage() : CPropertyPage(COptComportPage::IDD)
{
	//{{AFX_DATA_INIT(COptGrabberPage)

	//}}AFX_DATA_INIT
}

COptComportPage::~COptComportPage()
{
}

void COptComportPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptComportPage)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_MAIN_PORT, m_cComboMainPort);
	DDX_Control(pDX, IDC_COMBO_MAIN_BAUD, m_cComboMainBaud);
	//DDX_Control(pDX, IDC_COMBO_MAIN_PARITY, m_cComboMainParity);
	//DDX_Control(pDX, IDC_COMBO_HDMI_PARITY, m_cComboHdmiParity);
	DDX_Control(pDX, IDC_COMBO_HDMI_BAUD, m_cComboHdmiBaud);
	DDX_Control(pDX, IDC_COMBO_HDMI_PORT, m_cComboHdmiPort);


	DDX_Control(pDX, IDC_COMBO_SCAN_BAUD, m_cComboScanBaud);
	DDX_Control(pDX, IDC_COMBO_SCAN_PORT, m_cComboScanPort);

	DDX_Control(pDX, IDC_COMBO_USB_PORT, m_cComboUsbPort);
	DDX_Control(pDX, IDC_COMBO_USB_BAUD, m_cComboUsbBaud);
	DDX_Control(pDX, IDC_COMBO_USB_PARITY, m_cComboUsbParity);
	DDX_Control(pDX, IDC_COMBO_CHIP_TYPE, m_cComboChipType);
}


BEGIN_MESSAGE_MAP(COptComportPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptComportPage)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_SAVE_BUTTON, &COptComportPage::OnBnClickedSaveButton)
	ON_CBN_SELCHANGE(IDC_COMBO_USB_PORT, &COptComportPage::OnCbnSelchangeComboUsbPort)
END_MESSAGE_MAP()

BOOL COptComportPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	mbaud_List[0] = 9600;
	mbaud_List[1] = 19200;
	mbaud_List[2] = 38400;
	mbaud_List[3] = 57600;
	mbaud_List[4] = 115200;
	m_cComboMainBaud.AddString("9600");
	m_cComboMainBaud.AddString("19200");
	m_cComboMainBaud.AddString("38400");
	m_cComboMainBaud.AddString("57600");
	m_cComboMainBaud.AddString("115200");
	m_cComboMainBaud.SetCurSel(4);
	for (int i = 0; i < 5; i++)
	{
		if (CurrentSet ->wAvSwitchBoxBaudRate == mbaud_List[i])
		{
			m_cComboMainBaud.SetCurSel(i);
		}
	}
	//dlg.m_nBaud = g_nBaud_Set;
	//dlg.m_nPort = g_nPort_Set;
	//dlg.m_nParity = g_nParity_Set;
	//sHDMIComPort
	//m_cComboMainParity.AddString("NONE");
	//m_cComboMainParity.AddString("EVEN");
	//m_cComboMainParity.AddString("ODD");
	//m_cComboMainParity.SetCurSel(g_nParity_Set);


	//m_EditPortString.Format(_T("%d"),m_nPort );
/////////////////////////////////////////////////////
	

	m_cComboHdmiBaud.AddString("9600");
	m_cComboHdmiBaud.AddString("19200");
	m_cComboHdmiBaud.AddString("38400");
	m_cComboHdmiBaud.AddString("57600");
	m_cComboHdmiBaud.AddString("115200");
	m_cComboHdmiBaud.SetCurSel(4);
	for (int i = 0; i < 5; i++)
	{
		if (CurrentSet->wHDMIBaudRate == mbaud_List[i])
		{
			m_cComboHdmiBaud.SetCurSel(i);
		}
	}

	m_cComboScanBaud.AddString("9600");
	m_cComboScanBaud.AddString("19200");
	m_cComboScanBaud.AddString("38400");
	m_cComboScanBaud.AddString("57600");
	m_cComboScanBaud.AddString("115200");
	m_cComboScanBaud.SetCurSel(4);
	for (int i = 0; i < 5; i++)
	{
		if (CurrentSet->wScannerBaudRate == mbaud_List[i])
		{
			m_cComboScanBaud.SetCurSel(i);
		}
	}	//UINT g_nPort_HDMI = 3;
	//UINT g_nBaud_HDMI = 19200;
	//UINT g_nParity_HDMI = 1;

	m_cComboChipType.AddString("01 MCS");
	m_cComboChipType.AddString("02 MTK");
	m_cComboChipType.AddString("03 BCM");
	m_cComboChipType.SetCurSel(CurrentSet->nChipType-1);

	m_cComboUsbBaud.AddString("9600");
	m_cComboUsbBaud.AddString("19200");
	m_cComboUsbBaud.AddString("38400");
	m_cComboUsbBaud.AddString("57600");
	m_cComboUsbBaud.AddString("115200");
	m_cComboUsbBaud.SetCurSel(4);
	for (int i = 0; i < 5; i++)
	{
		if (CurrentSet->wHDMIBaudRate == mbaud_List[i])
		{
			m_cComboHdmiBaud.SetCurSel(i);
		}
	}

	m_cComboUsbParity.AddString("NONE");
	m_cComboUsbParity.AddString("EVEN");
	m_cComboUsbParity.AddString("ODD");
	m_cComboUsbParity.AddString("MARK");
	m_cComboUsbParity.AddString("SPACE");
	m_cComboUsbParity.SetCurSel(CurrentSet->nTVParity);


	//m_EditSetPortString.Format(_T("%d"),m_nPortPcb );
////////////////////////////////

	


	//	m_EditLEDPortString.Format(_T("%d"),m_nPortLED );


	//m_cComboScanBaud.AddString("9600");
	//m_cComboScanBaud.AddString("19200");
	//m_cComboScanBaud.AddString("38400");
	//m_cComboScanBaud.AddString("57600");
	//m_cComboScanBaud.AddString("115200");
	//m_cComboScanBaud.SetCurSel(0);
	//for (int i = 0; i < 5; i++)
	//{
	//	if (m_nBaudScan == mbaud_List[i])
	//	{
	//		m_cComboScanBaud.SetCurSel(i);
	//	}
	//}


	//m_cComboScanParity.AddString("NONE");
	//m_cComboScanParity.AddString("EVEN");
	//m_cComboScanParity.AddString("ODD");
	//m_cComboScanParity.SetCurSel(m_nParityScan);

	//SetDlgItemText(IDC_IPADDRESS_GMES, m_IPaddressGmes);


	//m_cComboNI_CardSel.SetCurSel(m_nNI_CardSel);

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

	//OnBnClickedCheckUseUsbScanner();

	UpdateData(FALSE);
	ComportSearch();
	   
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void COptComportPage::ComportSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	CString strTempCom;

	int ArrPort[256];
	//SearchPort(ArrPort);
	GetDeviceInfo();
		
	m_cComboMainPort.ResetContent();	
	m_cComboHdmiPort.ResetContent();
	m_cComboScanPort.ResetContent();

	if (m_PortCnt > 0)
	{
		for (int i = 0; i < m_PortCnt; i++)
		{
			//m_cComboMainPort.AddString(strPort[i]);

			strTemp = strPort[i].Mid(strPort[i].Find("(COM") + 4);
			strTemp = strTemp.Left(strTemp.Find(")"));

			strTempCom = strPort[i].Mid(strPort[i].Find("(COM")+1);
			strTempCom = strTempCom.Left(strTempCom.Find(")"));

			//m_cComboMainPort.AddString(strTempCom);			
			//m_cComboHdmiPort.AddString(strTempCom);

			//nNumberPort[i] = _ttoi(strTemp);

			//if (g_nPort_Set == nNumberPort[i])
			//{
			//	m_cComboMainPort.SetCurSel(i);
			//}
			//if (g_nPort_HDMI == nNumberPort[i])
			//{
			//	m_cComboHdmiPort.SetCurSel(i);
			//}

			int lPortNum = _ttoi(strTemp);
			if ((lPortNum > 0) && (lPortNum < 50))
			{
				nNumberPort[lPortNum] = 1;
			}
		}
		int lPortCount = 0;
		for (int i = 1; i < 50; i++)
		{
			if (nNumberPort[i] == 1)
			{
				strTempCom.Format("COM %d", i);
				m_cComboMainPort.AddString(strTempCom);			
				m_cComboHdmiPort.AddString(strTempCom);
				m_cComboScanPort.AddString(strTempCom);
				m_cComboUsbPort.AddString(strTempCom);
				if (10 > i)
				{
					strTemp.Format("COM%d", i);
				}
				else
				{
					strTemp.Format("\\\\.\\COM%d", i);
				}

				if(CurrentSet->sAvSwitchBoxComPort == strTemp)
				{
					m_cComboMainPort.SetCurSel(lPortCount);
				}
				if (CurrentSet->sHDMIComPort == strTemp)
				{
					m_cComboHdmiPort.SetCurSel(lPortCount);
				}		
				if (CurrentSet->sScannerComPort == strTemp)
				{
					m_cComboScanPort.SetCurSel(lPortCount);
				}		
				
				if (CurrentSet->sTVComPort == strTemp)
				{
					m_cComboUsbPort.SetCurSel(lPortCount);
				}
				lPortCount++;
			}
		}		

		//strTemp.Format(_T("COM Port %d EA ARE DETECTED!"), m_cComboPortSel.GetCount());
		//MessageBox(strTemp);
	}
	else
	{
		//MessageBox("COM Port NOT DETECTED!");
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


DEFINE_GUID(GUID_PCIE, 0x4d36e978L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

void COptComportPage::GetDeviceInfo()
{
	m_PortCnt = 0;
	GUID Input_GUID = GUID_PCIE;//GUID_DEVINTERFACE_USB_DEVICE;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&Input_GUID, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return;
	}
	DWORD i = 0;
	DWORD ComCount = 0;
	for (i = 0; true; ++i)
	{
		SP_DEVINFO_DATA devInfo;
		devInfo.cbSize = sizeof(SP_DEVINFO_DATA);
		BOOL succ = SetupDiEnumDeviceInfo(hDevInfo, i, &devInfo);
		if (GetLastError() == ERROR_NO_MORE_ITEMS)
			break;
		if (!succ) continue;

		SP_INTERFACE_DEVICE_DATA ifInfo;

		ifInfo.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
		if (TRUE != SetupDiEnumDeviceInterfaces(hDevInfo, &devInfo, &(Input_GUID), 0, &ifInfo))
		{
			if (GetLastError() != ERROR_NO_MORE_ITEMS)
				break;
		}
		interfaces.push_back(ifInfo);


		//	WCHAR  szDesc[MAX_PATH] = {0};
		char  szDesc[MAX_PATH] = { 0 };
		SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfo,
			SPDRP_DEVICEDESC,
			0L,
			(PBYTE)szDesc,
			2048,
			0);
		//	wchar_t  szFriendly[MAX_PATH] = {0};
		char  szFriendly[MAX_PATH] = { 0 };
		SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfo,
			SPDRP_FRIENDLYNAME,
			0L,
			(PBYTE)szFriendly,
			2048,
			0);


		DWORD requiredSize = 0;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &(interfaces.at(i)), NULL, NULL, &requiredSize, NULL);
		SP_INTERFACE_DEVICE_DETAIL_DATA* data = (SP_INTERFACE_DEVICE_DETAIL_DATA*)malloc(requiredSize);

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
		if (str1.Find("(COM") >= 0)
		{

			strPort[ComCount] = str1;
			ComCount++;
		}
		//strPort[i] = str1;
		//strPort[i] += str2;


	//	strPort[i].Format( _T("Desc	: %ws %ws %s") ,(CString)szDesc , (CString)szFriendly , (CString)data->DevicePath);

		devicePaths.push_back(data);

		delete data;
		if (i >= 49)
			break;
	}

	m_PortCnt = i;
	//if(m_Port.InitPort(this, CString(devicePaths[1]->DevicePath), 19200, 'N', 8, 1,  EV_RXCHAR, 4096 ))
	//{		
	//	m_Port.m_hWnd_ToSend = this->m_hWnd;
	//	m_Port.StartMonitoring();
	//}

}



void COptComportPage::OnBnClickedSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int l_port = 0;
	int lBaud = 0;
	int lParity = 0;

	if (m_PortCnt <= 0)
	{
		//	return;
	}
	else
	{
		CString str1;
		m_cComboMainPort.GetLBText(m_cComboMainPort.GetCurSel(), str1);		
		l_port = _ttoi(str1.Mid(3));		
		//g_nPort_Set = l_port;// 
		if (l_port > 9)
		{
			str1.Format("\\\\.\\COM%d", l_port);
		}
		else
		{
			str1.Format("COM%d", l_port);
		}
		CurrentSet->sAvSwitchBoxComPort = str1;

		m_cComboHdmiPort.GetLBText(m_cComboHdmiPort.GetCurSel(), str1);
		l_port = _ttoi(str1.Mid(3));
		if (l_port > 9)
		{
			str1.Format("\\\\.\\COM%d", l_port);
		}
		else
		{
			str1.Format("COM%d", l_port);
		}
		CurrentSet->sHDMIComPort = str1;

		m_cComboScanPort.GetLBText(m_cComboScanPort.GetCurSel(), str1);
		l_port = _ttoi(str1.Mid(3));
		if (l_port > 9)
		{
			str1.Format("\\\\.\\COM%d", l_port);
		}
		else
		{
			str1.Format("COM%d", l_port);
		}
		CurrentSet->sScannerComPort = str1;

		m_cComboUsbPort.GetLBText(m_cComboUsbPort.GetCurSel(), str1);
		l_port = _ttoi(str1.Mid(3));

		if (l_port > 9)
		{
			str1.Format("\\\\.\\COM%d", l_port);
		}
		else
		{
			str1.Format("COM%d", l_port);
		}
		
		CurrentSet->sTVComPort = str1;// 
				
	}

	lBaud = mbaud_List[m_cComboMainBaud.GetCurSel()];
	if ((lBaud >= 9600) && (lBaud <= 115200))
	{
		CurrentSet ->wAvSwitchBoxBaudRate = lBaud;
	}

	//lParity = m_cComboMainParity.GetCurSel();
	//if ((lParity >= 0) && (lParity <= 2))
	//{
	//	g_nParity_Set = lParity;
	//}

	//UINT g_nPort_HDMI = 3;
	//UINT g_nBaud_HDMI = 19200;
	//UINT g_nParity_HDMI = 1;


	lBaud = mbaud_List[m_cComboHdmiBaud.GetCurSel()];
	if ((lBaud >= 9600) && (lBaud <= 115200))
	{
		CurrentSet->wHDMIBaudRate = lBaud;
	}


	lBaud = mbaud_List[m_cComboScanBaud.GetCurSel()];
	if ((lBaud >= 9600) && (lBaud <= 115200))
	{
		CurrentSet->wScannerBaudRate = lBaud;
	}


	lBaud = mbaud_List[m_cComboUsbBaud.GetCurSel()];
	if ((lBaud >= 9600) && (lBaud <= 115200))
	{
		CurrentSet->wTVBaudRate = lBaud;
	}


	lParity = m_cComboUsbParity.GetCurSel();
	if ((lParity >= 0) && (lParity <= 4))
	{
		CurrentSet->nTVParity = lParity;
	}

	
	int lChiptype = m_cComboChipType.GetCurSel();
	if ((lChiptype >= 0) && (lChiptype <= 2))
	{
		CurrentSet->nChipType = lChiptype+1;
	}
	/*
	m_Ini.SetProfileString(GENERAL_S, "TV Link ComPort Number1", CurrentSet->sTVComPort);
	m_Ini.SetProfileInt(TV_CONTROL_S, "Micom Chip Type1", CurrentSet->nChipType);
	m_Ini.SetProfileInt(GENERAL_S, "TV Link ComPort Parity1", CurrentSet->nTVParity);
	m_Ini.SetProfileInt(GENERAL_S, "TV Link ComPort Baud Rate1", CurrentSet->wTVBaudRate);
	*/

	g_pView->SaveRegistrySetting();

	if (FileExists(CurrentSet->sModelIni))
	{
		SaveModelIniFile(CurrentSet->sModelIni);
	}
	else
	{
		CString sMsg;
		CreateModelIniFile(CurrentSet->sModelIni);
		sMsg.Format("File is created.\n[%s]", CurrentSet->sModelIni);
		AfxMessageBox(sMsg);
	}
	//CFileControl lFile;
	//lFile.SaveConfigSeqData();

}


void COptComportPage::OnCbnSelchangeComboUsbPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
