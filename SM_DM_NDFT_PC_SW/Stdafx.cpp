
// stdafx.cpp : source file that includes just the standard includes
// AcqVoltageSamples_IntClk.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

bool gbManualScopeMode = false;
bool gbManualRefMode = false;
int g_ManualId[8] = {4,5,6,7,0,1,2,3};


UINT g_NIAuioBoardFail = 0;

UINT g_nPort_Set = 1;
UINT g_nBaud_Set = 19200;
UINT g_nParity_Set = 0;

//UINT g_nPort_Pcb = 2;
//UINT g_nBaud_Pcb = 19200;
//UINT g_nParity_Pcb = 0;

UINT g_nPort_HDMI = 3;
UINT g_nBaud_HDMI = 19200;
UINT g_nParity_HDMI = 1;

UINT g_nPort_Scanner = 4;
UINT g_nBaud_Scanner = 19200;
UINT g_nParity_Scanner = 1;
UINT g_CheckUseUSB_Scanner = 0;
UINT g_nNI_CardSel = 3;
UINT g_nVIDEO_CardSel = 1;


CSerialPort m_ComPort;
CSerialPort m_ComPortPCB;
CSerialPort m_ComPortHDMI;
CSerialPort m_ComPortScanner;


CString g_strPassword = _T("1111");

CString g_strMesTns;
CString g_strMesAvn;
CString g_strMesUserID;
CString g_strMesPassword;
CString g_strMesLine;
CString g_strMesInspStep;


UINT g_nPortReopen = 0;
UINT g_nReplyTimeOut = 10;
UINT g_nTransTimeOut = 10;
UINT g_nRemotePortNumber = 8090;
UINT g_nRemotePortNumberCM45;
UINT g_nRemotePortNumberCM89;

UINT g_nRemotePortType = LINE_CM45;
UINT g_nLocalPortNumber = 7000;
CString g_nRemoteIPAddress = _T("10.213.191.7");


CString g_strEQPID;
CString g_strEQPName;
CString g_strCEID = _T("20100");
CString g_strRPTID = _T("20100");

CString g_strProcID;

CString g_strWOID;
CString g_strORGID;
CString g_strLineID;
CString g_strSetID;
CString g_strModelID;
CString g_strMesModelName;
CString g_strModelSuffix;
CString g_strProcessFileName;
//<EIFVERSION="1.8"ID="S1F2"NAME="AreYouThereData">
//<ELEMENT>
//<EQPID></EQPID>
//<EQPNAME></EQPNAME>
//<PROCID></PROCID>
//<ORGID></ORGID>
//<LINEID></LINEID>
//</ELEMENT>
//</EIF>



int g_nOKCnt = 0;
int g_nNGCnt = 0;



//DB_Set_DataT CurrentSet;




//CString g_strModelName;
//int g_nModelSelNum;
//CString g_strRemoconFileName;
int g_nRemoconSelNum;//
//TestModelDataT	gTestSeqData;
TestSeqDataT	gTestSeqData;


SaveLogDataT gSaveInfo;
//CString constPortName[18]= {
//		_T("HDMI_R"),_T("HDMI_L"),
//		_T("OPTICAL_R"),_T("OPTICAL_L"),
//		_T("SPEAKER_1R"),_T("SPEAKER_1L"),
//		_T("SPEAKER_2R"),_T("SPEAKER_2L"),
//		_T("SPEAKER_3R"),_T("SPEAKER_3L"),
//		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
//		_T("AUX_R"),_T("AUX_L"),
//		_T("PORTABLE_R"),_T("PORTABLE_L"), 
//		_T("COAX_R"),_T("COAX_L")};
CString constPortName[18]= {
		_T("HDMI_R"),_T("HDMI_L"),
		_T("OPTICAL_R"),_T("OPTICAL_L"),
		_T("Front R"),_T("Front L"),
		_T("Rear R"),_T("Rear L"),
		_T("Center"),_T("Woofer"),
		_T("SPEAKER_4R"),_T("SPEAKER_4L"),
		_T("AUX_R"),_T("AUX_L"),
		_T("PORTABLE_R"),_T("PORTABLE_L"), 
		_T("COAX_R"),_T("COAX_L")};


//cv::VideoCapture vcap; 
//cv::Mat gCuptureimage;
//bool gbShutdown;
//bool gbCapture = TRUE;
//
//int g_CameraFound = 0;
//int g_CameraCount = 0;

CableManagerT gCableManager;
int g_SetComOnlyMode = 0;

int g_nRunningProcessNo = 1;

BYTE gDoData[24] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};


BYTE gDoConfirmData[24] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};


BYTE gDiRcvData[24] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

float g_ReadVoltData[32] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

