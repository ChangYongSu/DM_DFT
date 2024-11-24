#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptSpecPage.h"
#include "step.h"
#include "Global.h"
#include "TVCommCtrl.h"
#include "parser.h"

extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg; 
extern CAcqVoltageSamples_IntClkDlg* g_pView;



CTVCommCtrl				TVCommCtrl;
//extern CDATsysView*		g_pView;
extern CString			m_strWipId;	//Wip ID

//+change 090213(Modification No1)
//extern CStdioFile g_LogFile;
//extern BOOL	g_LogFileOpen;


CTVCommCtrl::CTVCommCtrl()
{
	m_bPortOpen				= FALSE;
	m_nPortID				= -1;
	//+change kwmoon 080904
//	m_nResult				= T_NOTEST;
	m_nResult				= TEST_NOTEST;
	m_strErrMsg				= _T("");
	
	m_bThreadRunning		= FALSE;
	m_bExitThread			= FALSE;

	//+change 090213(Modification No1)
//	m_hThread				= NULL;
	m_pAdcThread			= NULL;

//	m_hAdcThreadKillEvent	= NULL;
	m_hReadEvent            = NULL;
	m_strErrMsg				= _T("");	

	memset(m_nReceiveData, 0, 256);
	memset(m_nSendData, 0, 5);
	m_nReceiveLength = 0;

	m_aCmd1.RemoveAll();
	m_aCmd2.RemoveAll();
	m_aSetId.RemoveAll();
	m_aData.RemoveAll();
	m_aWaitLimit.RemoveAll();
	
	m_nCheckType			= 0;	
	m_strTargetAvg			= _T("");	
	m_nAvgMargin			= 0;	

	memset(m_nAdcI2cData,0,256);

	// add 090417
	m_nResultCheckType      = 0;
	memset(m_nResultTarget, 0, 9);
	memset(m_nResultData, 0, 9);
	memset(m_nResultMargin, 0, 3);
	m_bResultRead = FALSE;
	m_aCheckType.RemoveAll();
	m_aCheckOption.RemoveAll();

	m_sCheckCmd			= _T("");		
	m_nWaitLimit = 0;

	m_aMacAdd.RemoveAll();
	m_nIfTest_Data1 = 0;
	m_nIfTest_Data2 = 0;
	m_bCheckReadVersion = 0;



m_sVersionName[0]  = "BE_Version";
m_sVersionName[1]  = "FE_Version";
m_sVersionName[2]  = "Micom_Version";
m_sVersionName[3]  = "DSP_Version";
m_sVersionName[4]  = "SubDSP_Version";
m_sVersionName[5]  = "EQ_Version";
m_sVersionName[6]  = "MEQ_Version";
m_sVersionName[7]  = "Touch_Version";
m_sVersionName[8]  = "Demo_Version";
m_sVersionName[9]  = "DJSound_Version";
m_sVersionName[10] = "WirelessTx_Version";
m_sVersionName[11] = "WirelessRx_Version";
m_sVersionName[12] = "Woofer_Rx_Version";
m_sVersionName[13] = "Rear_Kit_Rx_Version";
m_sVersionName[14] = "Rear_SPK_L_Version";
m_sVersionName[15] = "Rear_SPK_R_Version";
m_sVersionName[16] = "BT_Version";
m_sVersionName[17] = "HDMI_Version";
m_sVersionName[18] = "Checksum";
//else if (strncmp(lbuf, "BE Version=", strlen("BE Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sBE_Version = strTemp.Mid(strlen("BE Version="));
//				}
//else if (strncmp(lbuf, "FE Version=", strlen("FE Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sFE_Version = strTemp.Mid(strlen("FE Version="));
//				}
//else if (strncmp(lbuf, "Micom Version=", strlen("Micom Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sMicom_Version = strTemp.Mid(strlen("Micom Version="));
//				}
//else if (strncmp(lbuf, "DSP Version=", strlen("DSP Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sDSP_Version = strTemp.Mid(strlen("DSP Version="));
//				}
//else if (strncmp(lbuf, "DSP Sub Version=", strlen("DSP Sub Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sSubDSP_Version = strTemp.Mid(strlen("DSP Sub Version="));
//				}
//else if (strncmp(lbuf, "EQ Version=", strlen("EQ Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sEQ_Version = strTemp.Mid(strlen("EQ Version="));
//				}
//else if (strncmp(lbuf, "MEQM Version=", strlen("MEQM Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sMEQ_Version = strTemp.Mid(strlen("MEQM Version="));
//				}
//else if (strncmp(lbuf, "Touch Version=", strlen("Touch Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sTouch_Version = strTemp.Mid(strlen("Touch Version="));
//				}
//else if (strncmp(lbuf, "Demo Version=", strlen("Demo Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sDemo_Version = strTemp.Mid(strlen("Demo Version="));
//				}
//else if (strncmp(lbuf, "DJ Sound Version=", strlen("DJ Sound Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sDJSound_Version = strTemp.Mid(strlen("DJ Sound Version="));
//				}
//else if (strncmp(lbuf, "Wireless Tx Version=", strlen("Wireless Tx Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sWirelessTx_Version = strTemp.Mid(strlen("Wireless Tx Version="));
//				}
//else if (strncmp(lbuf, "Wireless Rx Version=", strlen("Wireless Rx Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sWirelessRx_Version = strTemp.Mid(strlen("Wireless Rx Version="));
//				}
//else if (strncmp(lbuf, "Woofer Rx Version=", strlen("Woofer Rx Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sWoofer_Rx_Version = strTemp.Mid(strlen("Woofer Rx Version="));
//				}
//else if (strncmp(lbuf, "sRear Kit Rx Version=", strlen("sRear Kit Rx Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sRear_Kit_Rx_Version = strTemp.Mid(strlen("sRear Kit Rx Version="));
//				}
//else if (strncmp(lbuf, "Rear SPK L Version=", strlen("Rear SPK L Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sRear_SPK_L_Version = strTemp.Mid(strlen("Rear SPK L Version="));
//				}
//else if (strncmp(lbuf, "Rear SPK R Version=", strlen("Rear SPK R Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sRear_SPK_R_Version = strTemp.Mid(strlen("Rear SPK R Version="));
//				}
//else if (strncmp(lbuf, "BT Version=", strlen("BT Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sBT_Version = strTemp.Mid(strlen("BT Version="));
//				}
//else if (strncmp(lbuf, "HDMI Version=", strlen("HDMI Version=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sHDMI_Version = strTemp.Mid(strlen("HDMI Version="));
//				}
//else if (strncmp(lbuf, "Checksum=", strlen("Checksum=")) == 0)
//				{
//				lbuf[strlen(lbuf)] = 0;
//				strTemp = lbuf;
//				CurrentSet->sChecksum = strTemp.Mid(strlen("Checksum="));
}

CTVCommCtrl::~CTVCommCtrl()
{
	if(m_hReadEvent != NULL)
	{
		CloseHandle(m_hReadEvent); m_hReadEvent = NULL;
	}

}


BOOL CTVCommCtrl::Create(CString sComPort, DWORD nBaudRate)
{
	CString sTmp = sComPort;
	sTmp.Delete(0, sTmp.Find("COM")+3);
	m_nPortID = atoi(sTmp);

	m_strErrMsg = _T("");

//	if( !m_ctrlTVCommCtrl.OpenPort( sComPort, nBaudRate, m_nPortID) )
//	if( !m_ctrlTVCommCtrl.OpenPort( sComPort, nBaudRate, m_nPortID, 8, 0, 0,TRUE) )
//	if( !m_ctrlTVCommCtrl.OpenPort( sComPort, nBaudRate, m_nPortID, 8, NOPARITY, 0,TRUE) )
//	if( !m_ctrlTVCommCtrl.OpenPort( sComPort, nBaudRate, m_nPortID, 8, EVENPARITY, 0,TRUE) )
	g_pView->OpenComportPCB();
	if(! (m_ComPortPCB.mPort_Opened))
	{
		m_strErrMsg.Format("[TV CommPort] \n%s Init Failed!", sComPort);
		m_bPortOpen = FALSE;
		return FALSE;
	}
	else m_bPortOpen = TRUE;

//	_Wait(150);

//	m_hAdcThreadKillEvent = ::CreateEvent(NULL,false,false,NULL);
//	m_hReadEvent = ::CreateEvent(NULL,false,false,NULL);
	
	return TRUE;
}

void CTVCommCtrl::PortClose()
{
	//m_ctrlTVCommCtrl.ClosePort();
	//m_bPortOpen = FALSE;
}

BOOL CTVCommCtrl::Init()
{
////	memset(m_strReceive, 0, 225);
	m_sReceive = _T("");
	return TRUE;
}

BOOL CTVCommCtrl::SendCommString(CString str)
{
	//m_ctrlTVCommCtrl.m_QueueRead.Clear();

	//::ResetEvent(m_hReadEvent);

	m_sReceive = _T("");
	m_nReceiveLength = 0;
	m_ReadComplete = 0;
	
	memcpy(g_pView->m_SendBufPCB, m_nSendData, 5);
	g_pView->m_SendCntPCB = 5;
	g_pView->ComPCBSend();
	//int nRtn = m_ctrlTVCommCtrl.WriteComm((BYTE*)(LPCTSTR)str, str.GetLength());
	
	//if(nRtn != str.GetLength()) return FALSE;

	return TRUE;
}
BOOL CTVCommCtrl::Send_ResultKey( BOOL bResult) 
{
	int i;
	BYTE nCheckSum = 0x00;
	int nRtn;
	CString szPrevMsg = _T("");
	CString szCmdString;
	m_sReceive = _T("");
	m_nReceiveLength = 0;
	m_ReadComplete = 0;

	if(CurrentSet->nProcessType > 1){return TRUE;}

	for(int i=0; i<5; i++)
	{
		m_nSendData[i] = 0x00;
	}

	
	m_nSendData[0] = 0xFF;
	m_nSendData[1] = 0x03;
	if(CurrentSet->nProcessType == 0){
		m_nSendData[2] = 0x0A;
	}
	else{
		m_nSendData[2] = 0x0B;
	}

	if(bResult){
		m_nSendData[3] = 0x01;
	}
	else{
		m_nSendData[3] = 0x00;
	}

	nCheckSum	= m_nSendData[0] ^ m_nSendData[1] ^ m_nSendData[2] ^ m_nSendData[3];

	m_nSendData[4] = nCheckSum;


	szCmdString.Format("%02X %02X %02X %02X %02X", m_nSendData[0], m_nSendData[1], m_nSendData[2], m_nSendData[3], m_nSendData[4]);
	if(CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
	{
		AddStringToStatus("DFT>:" + szCmdString);
	}
	//::ResetEvent(m_hReadEvent);
	//m_ctrlTVCommCtrl.m_QueueRead.Clear();
	memset(m_nReceiveData, 0, 225);


	memcpy(g_pView->m_SendBufPCB, m_nSendData, 5);
	g_pView->m_SendCntPCB = 5;
	g_pView->ComPCBSend();
	//nRtn = m_ctrlTVCommCtrl.WriteComm(m_nSendData, 5);

	
	//if(nRtn != 5) return FALSE;

	return TRUE;
}

BOOL CTVCommCtrl::SendCommand(BYTE nCmd)
{
	int i;
	BYTE nCheckSum = 0x00;
	int nRtn;
	CString szPrevMsg = _T("");
	CString szCmdString;
	m_sReceive = _T("");
	m_nReceiveLength = 0;
	m_ReadComplete = 0;
	m_nSendCmd = nCmd;
	if (m_bPortOpen == 0)
	{
		g_pView->OpenComportPCB();
		if (!(m_ComPortPCB.mPort_Opened))
		{
			//_ttoi(CurrentSet->sTVComPort.Mid(CurrentSet->sTVComPort.Find("COM") + 3)),
			//	CurrentSet->wTVBaudRate, lParityChar[CurrentSet->nTVParity]
			m_strErrMsg.Format("[TV CommPort] \n%s Init Failed!", CurrentSet->sTVComPort);
			m_bPortOpen = FALSE;
			return FALSE;
		}
		else m_bPortOpen = TRUE;		
	}

	for(int i=0; i<5; i++)
	{
		m_nSendData[i] = 0x00;
	}

	
	m_nSendData[0] = 0xAA;
	m_nSendData[1] = 0x03;
	m_nSendData[2] = CurrentSet->nChipType;
	m_nSendData[3] = nCmd;

	nCheckSum	= m_nSendData[0] ^ m_nSendData[1] ^ m_nSendData[2] ^ m_nSendData[3];

	m_nSendData[4] = nCheckSum;


	szCmdString.Format("%02X %02X %02X %02X %02X", m_nSendData[0], m_nSendData[1], m_nSendData[2], m_nSendData[3], m_nSendData[4]);
	//if(CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
	{
		AddStringToStatus("DFT>:" + szCmdString);
	}
	//if((g_pView->m_Rs232cAdcManualCheckDlg.GetSafeHwnd() != NULL)
	//&& (g_pView->m_Rs232cAdcManualCheckDlg.m_bActive == TRUE))
	//{
	//	g_pView->m_Rs232cAdcManualCheckDlg.WriteLog("DFT>:" + szCmdString);
	//}

//	::ResetEvent(m_hReadEvent);
////	m_ctrlTVCommCtrl.ClearPort();
//	m_ctrlTVCommCtrl.m_QueueRead.Clear();
	memset(m_nReceiveData, 0, 225);

	//nRtn = m_ctrlTVCommCtrl.WriteComm(m_nSendData, 5);
	memcpy(g_pView->m_SendBufPCB, m_nSendData, 5);
	g_pView->m_SendCntPCB = 5;
	g_pView->ComPCBSend();
	//{
	//	//SendData(m_SendBuf, m_SendCnt);
	//	//	void ComSend(BYTE lbuf, int lcnt);
	//	if (m_ComPortPCB.mPort_Opened)
	//	{

	//		m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);

	if(CurrentSet->bIsRunning)
	{
		g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
		
		if(szPrevMsg != _T(""))
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szCmdString);
			pCurStep->m_strMsg = szPrevMsg + " , " + szCmdString;
		}
		else
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szCmdString);
			pCurStep->m_strMsg = szCmdString;
		}		
	}
	
	//if(nRtn != 5) return FALSE;

	return TRUE;
}


BOOL CTVCommCtrl::ReceiveCommString(int nWaitLimit)
{
	BOOL	bDoing;
    clock_t	start;
	CString	sTemp;
	int     nPos = -1;
	int     nTemp;
	int     nTemp2;
	int		i, j;
	BYTE    nHeader = 0x00;
//	int		nRevLength = 0;
//	char	nReceiveData[256];
	MSG		msg;
	DWORD dwEventResult = 0;

	if(!m_bPortOpen) return FALSE;

	if (m_nReceiveLength > 0)
	{
		for (nPos = 0; nPos < 256; nPos++)
		{
			nHeader = m_nReceiveData[nPos];
			if (nHeader == 0xbb) {
				break;
			}
		}

		if ((m_nReceiveLength - nPos > 3)&&(m_nReceiveLength - nPos >= m_nReceiveData[nPos + 1]+1))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}		
	}
	else
	{
		return FALSE;
	}

	//memset(m_nRevData, 0, 225);
	//m_nRevLength = 0;
	//bDoing = TRUE;
	//start = clock();
	//while (bDoing)
	//{
	//	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{
	//		if (msg.message == WM_QUIT)
	//		{
	//			CurrentSet->bIsRunning = FALSE;
	//			::PostQuitMessage(0);
	//			break;
	//		}
	//		if (!AfxGetApp()->PreTranslateMessage(&msg))
	//		{
	//			::TranslateMessage(&msg);
	//			::DispatchMessage(&msg);
	//		}
	//	}   
	//	dwEventResult = WaitForSingleObject(m_hReadEvent, nWaitLimit);
	//		
	//	if(dwEventResult == WAIT_OBJECT_0 )
	//	{
	//		::ResetEvent(m_hReadEvent);
	//	}
	//	if(m_nReceiveLength > 0)
	//	{
	//		if(m_nRevLength == 0)
	//		{
	//			for(nPos =0; nPos <256; nPos++)
	//			{
	//				nHeader = m_nReceiveData[nPos]; 
	//				if( nHeader == 0xbb){
	//					break;
	//				}
	//			}
	//			if(nPos < 255){
	//				nTemp = m_nReceiveData[nPos + 1];
	//			}
	//			else
	//			{
	//				return FALSE;
	//			}
	//			nTemp2 = nPos + nTemp + 1;
	//			if(nTemp2 > 255)
	//			{
	//				for( i= 0, j= nPos; j < 256; i++, j++)
	//				{
	//					m_nRevData[i] = m_nReceiveData[j];
	//				}
	//				m_nRevLength = i;

	//				if ((clock() - start)*1000/CLOCKS_PER_SEC <= nWaitLimit) 
	//				{	continue; }
	//			}
	//			else{
	//				for( i= 0, j= nPos; j <= nTemp2; i++, j++)
	//				{
	//					m_nRevData[i] = m_nReceiveData[j];
	//				}
	//				m_nRevLength = i;

	//				m_ctrlTVCommCtrl.m_QueueRead.Clear();
	//				m_strSendStr = _T("");
	//				return TRUE;
	//			}
	//		}			
	//		else{
	//			nTemp2 = nTemp + 2 - m_nRevLength;
	//			if((nTemp + 2) <= (m_nRevLength + m_nReceiveLength)){
	//				for( i= m_nRevLength, j= 0; j < nTemp2; i++, j++)
	//				{
	//					m_nRevData[i] = m_nReceiveData[j];
	//				}
	//				m_nRevLength = m_nRevLength  + nTemp2;
	//				m_ctrlTVCommCtrl.m_QueueRead.Clear();
	//				m_strSendStr = _T("");
	//				return TRUE;
	//			}
	//			else{
	//				for( i= m_nRevLength, j= 0; j < m_nReceiveLength; i++, j++)
	//				{
	//					m_nRevData[i] = m_nReceiveData[j];
	//				}
	//				m_nRevLength = m_nRevLength + m_nReceiveLength;
	//				if ((clock() - start)*1000/CLOCKS_PER_SEC <= nWaitLimit) 
	//				{	continue; }
	//			}
	//		}
	//	}
 //       if ((clock() - start)*1000/CLOCKS_PER_SEC > nWaitLimit) 
 //       {
	//		m_ctrlTVCommCtrl.m_QueueRead.Clear();
	//		m_strSendStr = _T("");
	//		m_bCheckReadVersionCommError = 1;
	//		return FALSE;
	//	}
	//	if(CurrentSet->bRunAbort)
	//	{
	//		m_ctrlTVCommCtrl.m_QueueRead.Clear();
	//		m_strSendStr = _T("");
	//		return FALSE;
	//	}
	//}
	return TRUE;	
}


UINT CTVCommCtrl::IfTest(BYTE nCmd, int nMaxDelay, BOOL bIfCheck)
{
	CString sReadData = _T("");
	BYTE nCheckSum  = 0x00;
	int i;
	int nFind;
	CString szPrevMsg = _T("");
	CString szMsg1 = _T("");
	CString sData1 = _T("");
	CString sData2 = _T("");
	CString sTemp = _T("");

	m_nResult = TEST_PASS; //  TEST_NO_CHECK;

	m_nIfTest_Data1 = 1000;
	m_nIfTest_Data2 = 1000;
	//==============
	// Send Command
	//==============
	m_nSendCmd = nCmd;
	if (!SendCommand(nCmd))
	{
		m_nResult = TEST_FAIL;
		szMsg1 = "Send Fail";
		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	}

	//}
	//else if (g_pView->m_InterProcess = STEP_FUNC_RUN)
	//{
	//	//20210120 Time //Sleep(1000);
	//	//==================
	//	// Receive Response
	//	//==================
	//	if (!ReceiveCommString(nMaxDelay))
	//	{
	//		m_nResult = TEST_TIMEOUT;
	//		szMsg1 = "Read TimeOut";
	//		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//	}
	//	else
	//	{

	//		for (i = 0; i < m_nRevLength; i++)
	//		{
	//			sTemp.Format("%02X ", m_nRevData[i]);
	//			szMsg1 = szMsg1 + sTemp;
	//		}
	//		for (i = 0; i < m_nRevLength - 1; i++)
	//		{
	//			nCheckSum = nCheckSum ^ m_nRevData[i];
	//		}

	//		if (nCheckSum != m_nRevData[m_nRevLength - 1]) {
	//			szMsg1 = szMsg1 + ",CheckSum Fail";
	//			m_nResult = TEST_CHKSUM_FAIL;
	//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//		}
	//		if (nCmd != m_nRevData[3]) {
	//			szMsg1 = szMsg1 + ",Command Fail";
	//			m_nResult = TEST_COMMAND_FAIL;
	//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//		}

	//		if (bIfCheck) {
	//			if (m_nRevData[4] == 0x01) {
	//				m_nResult = TEST_PASS;
	//				szMsg1 = szMsg1 + "(OK)";
	//			}
	//			else {
	//				m_nResult = TEST_FAIL;
	//				szMsg1 = szMsg1 + "(NG)";
	//			}
	//		}

	//		if (m_nRevData[1] > 0x04)
	//		{
	//			for (i = 5; i < m_nRevLength - 1; i++)
	//			{
	//				sTemp.Format("%c", m_nRevData[i]);
	//				sReadData = sReadData + sTemp;
	//			}

	//			nFind = sReadData.Find(',');
	//			if (nFind == -1) {
	//				m_nIfTest_Data1 = atoi(sReadData);
	//			}
	//			else {
	//				sData1 = sReadData.Left(nFind);
	//				sData2 = sReadData.Right(sReadData.GetLength() - (nFind + 1));

	//				m_nIfTest_Data1 = atoi(sData1);
	//				m_nIfTest_Data2 = atoi(sData2);
	//			}

	//		}
	//		//END_THREAD:
	//		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
	//	}
	//}
	//
	////if(CurrentSet->bIsRunning)
	////{
	////	g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
	////	
	////	if(szPrevMsg != _T(""))
	////	{
	////		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
	////		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
	////	}
	////	else
	////	{
	////		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
	////		pCurStep->m_strMsg = szMsg1;
	////	}		
	////}

	////m_bThreadRunning = FALSE;

	return m_nResult;
	
}

UINT CTVCommCtrl::UartCheck()
{
	BOOL bResult = TRUE;
	int nNoTest = 0;
	CString sMAC_Add;
	CString sReadData = _T("");
	BYTE nCheckSum  = 0x00;
	int i;
	int nFind;
	int nPos, nHeader;
	CString szPrevMsg = _T("");
	CString szMsg1 = _T("");
	CString sData1 = _T("");
	CString sData2 = _T("");
	CString sTemp = _T("");

	m_nResult = TEST_WAIT; //  TEST_NO_CHECK;

	m_nIfTest_Data1 = 1000;
	m_nIfTest_Data2 = 1000;
	//==============
	// Send Command
	//==============
	
	if (TVCommCtrl.m_ReadComplete == 1)//if (m_nReceiveLength > 0)
	{
		for (nPos = 0; nPos < 256; nPos++)
		{
			nHeader = m_nReceiveData[nPos];
			if (nHeader == 0xbb) {
				break;
			}
		}

		m_nRevLength = m_nReceiveLength - nPos;
		//if ((nPos > 0) && (m_nReceiveLength > nPos))
		{			
			for (int i = 0; i < m_nRevLength; i++)
			{
				m_nRevData[i] = m_nReceiveData[i + nPos];
			}			
		}



		//BYTE			m_nRevData[256];
		//int				m_nRevSize;
		//int				m_nRevLength;
		if ((m_nRevLength > 3) && (m_nRevLength >= m_nRevData[nPos + 1] + 1))
		{
					//return TRUE;
			for (i = 0; i < m_nRevLength; i++)
			{
				sTemp.Format("%02X ", m_nRevData[i]);
				szMsg1 = szMsg1 + sTemp;
			}
			for (i = 0; i < m_nRevLength - 1; i++)
			{
				nCheckSum = nCheckSum ^ m_nRevData[i];
			}
#ifdef DEBUG
			if (nCheckSum != m_nRevData[m_nRevLength - 1]) {
				szMsg1 = szMsg1 + ",CheckSum Fail";
				m_nResult = TEST_CHKSUM_FAIL;
				pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;

				return FALSE;
			}

#endif // DEBUG
//#define COMAND_CHECK_TYPE		0
//#define COMAND_LAN_MAC_TYPE		1
//#define COMAND_WIFI_MAC_TYPE	2


			switch (m_nCommandTestType)
			{
			case COMAND_CHECK_TYPE:


				if ((m_nSendCmd != m_nRevData[3]) && (m_nResult = TEST_WAIT)) {
					szMsg1 = szMsg1 + ",Command Fail";
					m_nResult = TEST_COMMAND_FAIL;
					pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
				}

				if (m_nResult == TEST_WAIT)
				{
					if (m_nRevData[4] == 0x01) {
						m_nResult = TEST_PASS;
						szMsg1 = szMsg1 + "(OK)";
					}
					else {
						m_nResult = TEST_FAIL;
						szMsg1 = szMsg1 + "(NG)";
					}
				}
				pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
				break;
			case COMAND_LAN_MAC_TYPE:
			case COMAND_WIFI_MAC_TYPE:
				//for (i = 0; i < m_nRevLength; i++)
				//{
				//	sTemp.Format("%02X ", m_nRevData[i]);
				//	szMsg1 = szMsg1 + sTemp;
				//}
				//for (i = 0; i < m_nRevLength - 1; i++)
				//{
				//	nCheckSum1 = nCheckSum1 ^ m_nRevData[i];
				//}

				//nCheckSum2 = m_nRevData[m_nRevLength - 1];
				//if (nCheckSum1 != nCheckSum2) {
				//	sTemp.Format(",CheckSum Fail(%02X,%02X)", nCheckSum1, nCheckSum2);
				//	szMsg1 = szMsg1 + sTemp;
				//	bCheckSum_Check = FALSE;
				//}
				//m_nSendCmd
				for (i = 4; i < m_nRevLength - 1; i++)
				{
					sTemp.Format("%c", m_nRevData[i]);
					sReadData = sReadData + sTemp;
				}
//
//#define _COMMAND_BT_MAC_READ     0x44
//#define _COMMAND_LAN_MAC_READ     0x45
//#define _COMMAND_WIFI_MAC_READ
				if (m_nSendCmd == _COMMAND_LAN_MAC_READ)
				{
					sTemp.Format("LAN MAC Add : %s)", sReadData);
				}
				else if (m_nSendCmd == _COMMAND_WIFI_MAC_READ)
				{
					sTemp.Format("WIFI MAC Add : %s)", sReadData);
				}
				else if (m_nSendCmd == _COMMAND_BT_MAC_READ)
				{
					sTemp.Format("BT MAC Add : %s)", sReadData);
				}

				if (CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
				{
					AddStringToStatus(sTemp);
				}

				if ((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
				{
					g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg);

					if (szPrevMsg != _T(""))
					{
						g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
						pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1 + sTemp;
					}
					else
					{
						g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
						pCurStep->m_strMsg = szMsg1 + sTemp;
					}
				}
				

				sReadData.MakeUpper();
				nNoTest = m_aMacAdd.GetSize();

				if (sReadData.Find("00:00:00:00:00:00") != -1)
				{
					bResult = FALSE;
				}
				else if (sReadData.Find("FF:FF:FF:FF:FF:FF") != -1)
				{
					bResult = FALSE;
				}
				else if (sReadData.Find("00:10:18:26:08:E0") != -1)
				{
					bResult = FALSE;
				}
				else if (sReadData.Find("00:F0:FF:00:F0:FF") != -1)
				{
					bResult = FALSE;
				}
				if (!bResult) {
					return FALSE;
				}

				 sMAC_Add = sReadData.Left(8);
				if (nNoTest == 0) return FALSE;
				bResult = FALSE;

				for (int i = 0; i < nNoTest; i++)
				{
					if (sMAC_Add.Compare(m_aMacAdd.GetAt(i)) == 0) {
						bResult = TRUE;
					}
				}

				m_aMacAdd.RemoveAll();

				return bResult;
			default:

				break;
			}
		}
		else
		{
			m_nResult = TEST_WAIT;
		}
	}
	else
	{
		m_nResult = TEST_WAIT;
	}

	if (m_nResult == TEST_WAIT)
	{

	}

		//	if (m_nRevData[1] > 0x04)
		//	{
		//		for (i = 5; i < m_nRevLength - 1; i++)
		//		{
		//			sTemp.Format("%c", m_nRevData[i]);
		//			sReadData = sReadData + sTemp;
		//		}

		//		nFind = sReadData.Find(',');
		//		if (nFind == -1) {
		//			m_nIfTest_Data1 = atoi(sReadData);
		//		}
		//		else {
		//			sData1 = sReadData.Left(nFind);
		//			sData2 = sReadData.Right(sReadData.GetLength() - (nFind + 1));

		//			m_nIfTest_Data1 = atoi(sData1);
		//			m_nIfTest_Data2 = atoi(sData2);
		//		}

		//	}
		//	//END_THREAD:
		//	pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
		//}
	//}


	//}
	//else if (g_pView->m_InterProcess = STEP_FUNC_RUN)
	//{
	//	//20210120 Time //Sleep(1000);
	//	//==================
	//	// Receive Response
	//	//==================
	//	if (!ReceiveCommString(nMaxDelay))
	//	{
	//		m_nResult = TEST_TIMEOUT;
	//		szMsg1 = "Read TimeOut";
	//		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//	}
	//	else
	//	{

	//		for (i = 0; i < m_nRevLength; i++)
	//		{
	//			sTemp.Format("%02X ", m_nRevData[i]);
	//			szMsg1 = szMsg1 + sTemp;
	//		}
	//		for (i = 0; i < m_nRevLength - 1; i++)
	//		{
	//			nCheckSum = nCheckSum ^ m_nRevData[i];
	//		}

	//		if (nCheckSum != m_nRevData[m_nRevLength - 1]) {
	//			szMsg1 = szMsg1 + ",CheckSum Fail";
	//			m_nResult = TEST_CHKSUM_FAIL;
	//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//		}
	//		if (nCmd != m_nRevData[3]) {
	//			szMsg1 = szMsg1 + ",Command Fail";
	//			m_nResult = TEST_COMMAND_FAIL;
	//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;
	//		}

	//		if (bIfCheck) {
	//			if (m_nRevData[4] == 0x01) {
	//				m_nResult = TEST_PASS;
	//				szMsg1 = szMsg1 + "(OK)";
	//			}
	//			else {
	//				m_nResult = TEST_FAIL;
	//				szMsg1 = szMsg1 + "(NG)";
	//			}
	//		}

	//		if (m_nRevData[1] > 0x04)
	//		{
	//			for (i = 5; i < m_nRevLength - 1; i++)
	//			{
	//				sTemp.Format("%c", m_nRevData[i]);
	//				sReadData = sReadData + sTemp;
	//			}

	//			nFind = sReadData.Find(',');
	//			if (nFind == -1) {
	//				m_nIfTest_Data1 = atoi(sReadData);
	//			}
	//			else {
	//				sData1 = sReadData.Left(nFind);
	//				sData2 = sReadData.Right(sReadData.GetLength() - (nFind + 1));

	//				m_nIfTest_Data1 = atoi(sData1);
	//				m_nIfTest_Data2 = atoi(sData2);
	//			}

	//		}
	//		//END_THREAD:
	//		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
	//	}
	//}
	//
	////if(CurrentSet->bIsRunning)
	////{
	////	g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
	////	
	////	if(szPrevMsg != _T(""))
	////	{
	////		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
	////		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
	////	}
	////	else
	////	{
	////		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
	////		pCurStep->m_strMsg = szMsg1;
	////	}		
	////}

	////m_bThreadRunning = FALSE;

	return m_nResult;
	
}

void CTVCommCtrl::ResetArray()
{
	m_strErrMsg		= _T("");	
	m_aCmd1.RemoveAll();
	m_aCmd2.RemoveAll();
	m_aSetId.RemoveAll();
	m_aData.RemoveAll();
	m_aWaitLimit.RemoveAll();
	
	m_nCheckType	= 0;	
	m_strTargetAvg  = _T("");	
	m_nAvgMargin    = 0;	
	
	// add 090417
	m_nResultCheckType      = 0;
	memset(m_nResultTarget, 0, 9);
	memset(m_nResultMargin, 0, 3);
	memset(m_nResultData, 0, 9);
	m_bResultRead = FALSE;
	m_aCheckType.RemoveAll();
	m_aCheckOption.RemoveAll();
}


BOOL CTVCommCtrl::Firmware_VersionCheck()
{
	BOOL bHexType = FALSE;
	BYTE nCmd;
	CString sReadData = _T("");
	CString sTemp;
	CString sVerName;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");
	BYTE nCheckSum1  = 0x00;
	BYTE nCheckSum2  = 0x00;

	int nPos;
	BYTE nHeader;
	int i;
	BOOL bCheckSum_Check = TRUE;
	m_bCheckReadVersion = 0;

	if (m_bPortOpen == 0)
	{
		m_bCheckReadVersionCommError = 1;
		return FALSE;
	}
		
	//TVCommCtrl.m_ReadComplete = 0;
	//TVCommCtrl.m_bCheckReadVersion = 1;
	//TVCommCtrl.m_ReadCheckNo = 0;	


	if (TVCommCtrl.m_ReadComplete == 1)//if (m_nReceiveLength > 0)
	{
		for (nPos = 0; nPos < 256; nPos++)
		{
			nHeader = m_nReceiveData[nPos];
			if (nHeader == 0xbb) {
				break;
			}
		}

		m_nRevLength = m_nReceiveLength - nPos;
		//if ((nPos > 0) && (m_nReceiveLength > nPos))
		{
			for (int i = 0; i < m_nRevLength; i++)
			{
				m_nRevData[i] = m_nReceiveData[i + nPos];
			}
		}
		if ((m_nRevLength > 3) && (m_nRevLength >= m_nRevData[nPos + 1] + 1))
		{
			
			for (i = 0; i < m_nRevLength; i++)
			{
				sTemp.Format("%02X ", m_nRevData[i]);
				szMsg1 = szMsg1 + sTemp;
			}
			nCheckSum1 = 0x00;
			for (i = 0; i < m_nRevLength - 1; i++)
			{
				nCheckSum1 = nCheckSum1 ^ m_nRevData[i];
			}
#ifdef DEBUG
			if (nCheckSum1 != m_nRevData[m_nRevLength - 1]) {
				szMsg1 = szMsg1 + ",CheckSum Fail";
				m_nResult = TEST_CHKSUM_FAIL;
				pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1; //goto END_THREAD;

				return FALSE;
			}

#endif // DEBUG
			
			
			if ((CurrentSet->nChipType == CHIP_MCS)
					&& (m_ReadCheckNo + 1 >= WIRELESS_TX_VER)
					&& (m_ReadCheckNo + 1 <= CHECKSUM_VER))
			{
					bHexType = TRUE;
			}
			
			if (m_nRevLength > 5)
			{
				for (i = 4; i < m_nRevLength - 1; i++)
				{
					if (bHexType) {
						sTemp.Format("%02X", m_nRevData[i]);
					}
					else {
						sTemp.Format("%c", m_nRevData[i]);
					}
					sReadData = sReadData + sTemp;

				}
			}
			else
			{
				sReadData = "**RCV DATA: ";
				for (i = 0; i < m_nRevLength; i++)
				{
					//if (bHexType) {
					sTemp.Format("%02X ", m_nRevData[i]);
					//}

					sReadData = sReadData + sTemp;

				}
			}
						
			if ((TVCommCtrl.m_ReadCheckNo >= 0) && (TVCommCtrl.m_ReadCheckNo < 19))
			{
				if (CurrentSet->sVersionArray[TVCommCtrl.m_ReadCheckNo] == sReadData)
				{
					//m_ctrlAudioVerSpecList.SetItemText(TVCommCtrl.m_ReadCheckNo, 1, sReadData);
					szMsg1 = m_sVersionName[TVCommCtrl.m_ReadCheckNo];
					szMsg1 += ": ";
					szMsg1 += sReadData;
					szMsg1 += "[PASS]";
					sTemp = szMsg1;
					AddStringToStatus(sTemp);
					m_nResult = TEST_PASS;
					
					m_ReadCheckNo++;
				}
				else
				{
					szMsg1 = m_sVersionName[TVCommCtrl.m_ReadCheckNo];
					szMsg1 += ": ";
					szMsg1 += sReadData;
					szMsg1 += "!=";
					szMsg1 += CurrentSet->sVersionArray[TVCommCtrl.m_ReadCheckNo];
					szMsg1 += "[FAIL]";
					sTemp = szMsg1;
					AddStringToStatus(sTemp);
					return FALSE;
				}
			}
			else
			{
				//MessageBox("Index Error", "Index Error");
				return FALSE;
				//TVCommCtrl.m_ReadComplete = 0;
				//TVCommCtrl.m_bCheckReadVersion = 0;
			}
			
		}
		else
		{
			m_nResult = TEST_WAIT;
		}
	}
	else
	{
		m_nResult = TEST_WAIT;
	}

	if (m_nResult == TEST_WAIT)
	{
		return m_nResult;
	}
	if (TVCommCtrl.m_ReadCheckNo + 1 >= MAX_NUM_VER_COUNT)
	{
		return TEST_PASS;
	}
	for (int i = TVCommCtrl.m_ReadCheckNo; i < MAX_NUM_VER_COUNT; i++)
	{
		TVCommCtrl.m_ReadCheckNo = i;
		if (CurrentSet->bVerChecked[TVCommCtrl.m_ReadCheckNo] == 1)
		{
			TVCommCtrl.Firmware_VersionRead(TVCommCtrl.m_ReadCheckNo + 1);	
			return TEST_WAIT;
			break;
		}
		else
		{
			if (TVCommCtrl.m_ReadCheckNo+1 >= MAX_NUM_VER_COUNT)
			{
				return TEST_PASS;
			}
		}		
	}

	//	//	int  nI2cResult;
//	int i;
//	int nData[3]   = {0,0,0};
//
//	if(CurrentSet->nChipType == CHIP_MCS)
//	{
//		if (CurrentSet->bVerChecked[DSP_VER - 1] == 1)
//		{
//			for (i = 0; i < 3; i++) {
//				bResult1 = TVCommCtrl.Firmware_VersionCheck(DSP_VER, CurrentSet->sDSP_Version);
//				if (bResult1) { break; }
//				if (CurrentSet->bRunAbort) { return 0.0; }	
//				if (bResult1 == FALSE)
//				{
//					if(TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					 return 0.0;
//				}
//			}
//			_Wait(200);
//		}
//		if (CurrentSet->bVerChecked[BE_VER - 1] == 1)
//		{
//			
//			for (i = 0; i < 3; i++) {
//				bResult2 = TVCommCtrl.Firmware_VersionCheck(BE_VER, CurrentSet->sBE_Version);
//				if (bResult2) { break; }
//				if (CurrentSet->bRunAbort) { return 0.0; }	
//				if (bResult2 == FALSE)
//				{
//					if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//				}
//			}
//				
//			_Wait(200);
//			
//		}
//	}	
//	else{
//		if (CurrentSet->bVerChecked[BE_VER - 1] == 1)
//		{
//			for (i = 0; i < 3; i++) {
//				bResult1 = TVCommCtrl.Firmware_VersionCheck(BE_VER, CurrentSet->sBE_Version);
//				if (bResult1) { break; }
//				if (CurrentSet->bRunAbort) { return 0.0; }	
//				if (bResult1 == FALSE)
//				{
//					if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//				}
//			}
//			_Wait(200);
//		}
//
//		if (CurrentSet->bVerChecked[DSP_VER - 1] == 1)
//		{
//			
//			for (i = 0; i < 3; i++) {
//				bResult2 = TVCommCtrl.Firmware_VersionCheck(DSP_VER, CurrentSet->sDSP_Version);
//				if (bResult2) { break; }
//				if (CurrentSet->bRunAbort) { return 0.0; }	
//				if (bResult2 == FALSE)
//				{
//					if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//				}
//
//			}
//				
//
//			_Wait(200);
//		}
//	}	
//
//	if (CurrentSet->bVerChecked[FE_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult3 = TVCommCtrl.Firmware_VersionCheck(FE_VER, CurrentSet->sFE_Version);
//			if (bResult3) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }	
//			if (bResult3 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//		}
//		_Wait(200);
//		
//	}
//
//	if (CurrentSet->bVerChecked[MICOM_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult4 = TVCommCtrl.Firmware_VersionCheck(MICOM_VER, CurrentSet->sMicom_Version);
//			if (bResult4) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }	
//			if (bResult4 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//		}
//		_Wait(200);
//		
//	}
//
//	if (CurrentSet->bVerChecked[SUB_DSP_VER - 1] == 1)
//	{
//		
//			for (i = 0; i < 3; i++) {
//				bResult5 = TVCommCtrl.Firmware_VersionCheck(SUB_DSP_VER, CurrentSet->sSubDSP_Version);
//				if (bResult5) { break; }
//				if (CurrentSet->bRunAbort) { return 0.0; }		
//				if (bResult5 == FALSE)
//				{
//					if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//				}
//			}
//			_Wait(200);
//		
//	}
//	
//	if (CurrentSet->bVerChecked[EQ_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult6 = TVCommCtrl.Firmware_VersionCheck(EQ_VER, CurrentSet->sEQ_Version);
//			if (bResult6) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }	
//			if (bResult6 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//		}
//		_Wait(200);
//		
//	}
//
//	if (CurrentSet->bVerChecked[MEQ_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult7 = TVCommCtrl.Firmware_VersionCheck(MEQ_VER, CurrentSet->sMEQ_Version);
//			if (bResult7) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult7 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);	
//	}
//
//	if (CurrentSet->bVerChecked[TOUCH_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult8 = TVCommCtrl.Firmware_VersionCheck(TOUCH_VER, CurrentSet->sTouch_Version);
//			if (bResult8) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult8 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);
//		
//	}
//
//
//
//	if (CurrentSet->bVerChecked[DEMO_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult9 = TVCommCtrl.Firmware_VersionCheck(DEMO_VER, CurrentSet->sDemo_Version);
//			if (bResult9) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult9 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);
//		
//	}
//
//	if (CurrentSet->bVerChecked[DJ_SOUND_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult10 = TVCommCtrl.Firmware_VersionCheck(DJ_SOUND_VER, CurrentSet->sDJSound_Version);
//			if (bResult10) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult10 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);
//		
//	}
//
//
//	if (CurrentSet->bVerChecked[WIRELESS_TX_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult11 = TVCommCtrl.Firmware_VersionCheck(WIRELESS_TX_VER, CurrentSet->sWirelessTx_Version);
//			if (bResult11) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult11 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}	
//		}
//
//		_Wait(200);
//		
//	}
//
//
//	if (CurrentSet->bVerChecked[WIRELESS_RX_VER - 1] == 1)
//	{		
//		for (i = 0; i < 3; i++) {
//			bResult12 = TVCommCtrl.Firmware_VersionCheck(WIRELESS_RX_VER, CurrentSet->sWirelessRx_Version);
//			if (bResult12) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }	
//			if (bResult12 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);		
//	}
//	if (CurrentSet->bVerChecked[WOOFER_RX_VER - 1] == 1)
//	{
//		for (i = 0; i < 3; i++) {
//			bResult13 = TVCommCtrl.Firmware_VersionCheck(WOOFER_RX_VER, CurrentSet->sWoofer_Rx_Version);
//			if (bResult13) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult13 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//			}
//
//		}
//		_Wait(200);
//	}
//	if (CurrentSet->bVerChecked[REAR_KIT_RX_VER - 1] == 1)
//	{
//		for (i = 0; i < 3; i++) {
//			bResult14 = TVCommCtrl.Firmware_VersionCheck(REAR_KIT_RX_VER, CurrentSet->sRear_Kit_Rx_Version);
//			if (bResult14) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult14 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//			}
//
//		}
//		_Wait(200);
//	}
//	if (CurrentSet->bVerChecked[REAR_SPK_L_VER - 1] == 1)
//	{
//		for (i = 0; i < 3; i++) {
//			bResult15 = TVCommCtrl.Firmware_VersionCheck(REAR_SPK_L_VER, CurrentSet->sRear_SPK_L_Version);
//			if (bResult15) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult15 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//			}
//
//		}
//		_Wait(200);
//	}
//	if (CurrentSet->bVerChecked[REAR_SPK_R_VER - 1] == 1)
//	{
//		for (i = 0; i < 3; i++) {
//			bResult16 = TVCommCtrl.Firmware_VersionCheck(REAR_SPK_R_VER, CurrentSet->sRear_SPK_R_Version);
//			if (bResult16) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult16 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//					return 0.0;
//			}
//
//		}
//		_Wait(200);
//	}
//	
//	///////////////////////////////////////////////////
//	if (CurrentSet->bVerChecked[BT_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult17 = TVCommCtrl.Firmware_VersionCheck(BT_VER, CurrentSet->sBT_Version);
//			if (bResult17) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//			if (bResult17 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		_Wait(200);
//		
//	}
//
//
//	if (CurrentSet->bVerChecked[HDMI_VER - 1] == 1)
//	{		
//		for (i = 0; i < 3; i++) {
//			bResult18 = TVCommCtrl.Firmware_VersionCheck(HDMI_VER, CurrentSet->sHDMI_Version);
//			if (bResult18) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }
//
//			if (bResult18 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//		}
//		_Wait(200);		
//	}
//
//	//////////////////////////////////////////////////
//	if (CurrentSet->bVerChecked[CHECKSUM_VER - 1] == 1)
//	{
//		
//		for (i = 0; i < 3; i++) {
//			bResult19 = TVCommCtrl.Firmware_VersionCheck(CHECKSUM_VER, CurrentSet->sChecksum);
//			if (bResult19) { break; }
//			if (CurrentSet->bRunAbort) { return 0.0; }	
//			if (bResult19 == FALSE)
//			{
//				if (TVCommCtrl.m_bCheckReadVersionCommError == 1)
//				return 0.0;
//			}
//
//		}
//		
//	}
//
//
//	if(bResult1 && bResult2 && bResult3 && bResult4 && bResult5 && bResult6 && bResult7 && bResult8 && bResult9 && bResult10
//		 && bResult11 && bResult12 && bResult13 && bResult14 && bResult15 && bResult16 && bResult17 && bResult18 && bResult19)
//	{
//		return 1.0;	
//	}
//	else


	
#if 1

#else

	if(!SendCommand(nCmd))
	{
		m_bCheckReadVersionCommError = 1;
		return FALSE;
	}
	//20210120 Time //_Wait(200);

	if(!ReceiveCommString(5000))
	{

		return FALSE;
	}

	for(i =0; i < m_nRevLength; i++)
	{
		sTemp.Format("%02X ", m_nRevData[i]);
		szMsg1 = szMsg1 + sTemp;
	}
	for(i =0; i < m_nRevLength - 1; i++)
	{
		nCheckSum1 = nCheckSum1 ^ m_nRevData[i];
	}

	nCheckSum2 = m_nRevData[m_nRevLength - 1];
	if(nCheckSum1 != nCheckSum2){
		sTemp.Format(",CheckSum Fail(%02X,%02X)", nCheckSum1, nCheckSum2);
		//szMsg1 = szMsg1 + sTemp;
		bCheckSum_Check = FALSE;
		AddStringToStatus(sTemp);
	}
	
	for(i =4; i < m_nRevLength - 1; i++)
	{
		if(bHexType){
			sTemp.Format("%02X", m_nRevData[i]);
		}
		else{
			sTemp.Format("%c", m_nRevData[i]);
		}
		sReadData = sReadData + sTemp;

	}
	sTemp.Format("(%s%s)", sVerName, sReadData); 
	if(CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
	{
		AddStringToStatus(sTemp);
	}

	if((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
	{
		g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
		
		if(szPrevMsg != _T(""))
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1 + sTemp;
		}
		else
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
			pCurStep->m_strMsg = szMsg1 + sTemp;
		}		
	}

	if(!bCheckSum_Check){return FALSE;}

//	sVersion.MakeUpper(); 
	if ((sReadData.GetLength() > 0) && (sVersion.GetLength() > 0)&&(sReadData.Compare(sVersion) == 0)){
		
		return TRUE;
	}
	else{
		return FALSE;
	}
#endif
}

BOOL CTVCommCtrl::Firmware_VersionRead(int nIndex)
{
	BOOL bHexType = FALSE;
	BYTE nCmd;
	CString sReadData = _T("");
	CString sTemp;
	CString sVerName;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");
	BYTE nCheckSum1 = 0x00;
	BYTE nCheckSum2 = 0x00;
	int i;
	BOOL bCheckSum_Check = TRUE;
	
	m_ReadComplete = 0;
	memset(m_nReceiveData, 0, 225);
	m_nReceiveLength = 0;
	//m_ReadCheckNo= 0;

	switch (nIndex)
	{
	case BE_VER:
		nCmd = 0x21;
		sVerName = "BE_Ver:";
		break;

	case FE_VER:
		nCmd = 0x22;
		sVerName = "FE_Ver:";
		break;

	case MICOM_VER:
		nCmd = 0x23;
		sVerName = "MICOM_Ver:";
		break;

	case DSP_VER:
		nCmd = 0x24;
		sVerName = "DSP_Ver:";
		break;

	case SUB_DSP_VER:
		nCmd = 0x25;
		sVerName = "SUB_DSP_Ver:";
		break;

	case EQ_VER:
		nCmd = 0x26;
		sVerName = "EQ_Ver:";
		break;

	case MEQ_VER:
		nCmd = 0x27;
		sVerName = "MEQ_Ver:";
		break;

	case TOUCH_VER:
		nCmd = 0x28;
		sVerName = "TOUCH_Ver:";
		break;

	case DEMO_VER:
		nCmd = 0x29;
		sVerName = "DEMO_Ver:";
		break;


	case DJ_SOUND_VER:
		nCmd = 0x2A;
		sVerName = "DJ_SOUND_Ver:";
		break;

	case WIRELESS_TX_VER:
		nCmd = 0x2B;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "WirelessTx_Ver:";
		break;

	case WIRELESS_RX_VER:
		nCmd = 0x2C;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "WirelessRx_Ver:";
		break;
	case BT_VER:
		nCmd = 0x2F;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "BT_Ver:";
		break;
	case HDMI_VER:
		nCmd = 0x2E;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "HDMI_Ver:";
		break;
		//0x4C	Woofer Rx Version
			//	0x4D	Rear Kit Rx Version
			//	0x4E	Rear SPK L Version
			//	0x4F	Rear SPK R Version
	case WOOFER_RX_VER:
		nCmd = 0x4C;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "WooferRxVersion:";
		break;

	case REAR_KIT_RX_VER:
		nCmd = 0x4D;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "RearKitRxVersion:";
		break;

	case REAR_SPK_L_VER:
		nCmd = 0x4E;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "RearSPK_L_Version:";
		break;

	case REAR_SPK_R_VER:
		nCmd = 0x4F;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "RearSPK_R_Version:";
		break;
	case CHECKSUM_VER:
		nCmd = 0x2D;
		if (CurrentSet->nChipType == CHIP_MCS)
		{
			bHexType = TRUE;
		}
		sVerName = "CheckSum_Ver:";
		break;


	default:
		return FALSE;
		break;
	}

	m_pMainDlg->m_UartCommandCnt = 1;
	m_pMainDlg->m_UartCommand[0] = nCmd;
	m_pMainDlg->UartCommandPcbSend();
	
	   	 
	return TRUE;
}


BOOL CTVCommCtrl::Send_TVControl_Command(BYTE nCommand, int nWait)
{
	//CString sReadData;
	//CString szMsg1 = _T("");
	//CString szPrevMsg = _T("");
	//PortClear();
	//if(!SendCommand(nCommand))
	//{
	//	return FALSE;
	//}
	////==================
	//// Receive Response
	////==================
	//if ((g_pView->m_Rs232cAdcManualCheckDlg.GetSafeHwnd() != NULL)
	//	&& (g_pView->m_Rs232cAdcManualCheckDlg.m_bActive == TRUE))
	//{
	//}
	//else
	//{
	//	if (!ReceiveCommString(nWait))
	//	{
	//		return FALSE;
	//	}
	//}
	return TRUE;
}

BOOL CTVCommCtrl::InputSourceChange(BYTE nCode)
{
	//CString sCmd;
	//CString sData;
	//CString sReadData;
	//CString szMsg1 = _T("");
	//CString szPrevMsg = _T("");

	//m_strSendStr.Format("xb 00 %02x%c", nCode, 0x0d); 

	//PortClear();
	//if(CurrentSet->bCommDisplay)
	//{
	//	AddStringToStatus("TV-Com : " + m_strSendStr);
	//}
	//if(!SendCommString(m_strSendStr))
	//{
	//	return FALSE;
	//}

	//if(!ReceiveCommString(3000))
	//{
	//	return FALSE;
	//}
	////090522
	//int nIndex;
	//nIndex = sReadData.Find(0x0d);
	//if(nIndex != -1)
	//{
	//	szMsg1 = sReadData.Left(nIndex + 1);
	//}
	//else{
	//	szMsg1 = sReadData;
	//}

	//if((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
	//{
	//	g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
	//	
	//	if(szPrevMsg != _T(""))
	//	{
	//		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
	//		pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
	//	}
	//	else
	//	{
	//		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
	//		pCurStep->m_strMsg = szMsg1;
	//	}		
	//}

	//sReadData.MakeUpper( );
	//if(sReadData.Find("NG") != -1)
	//{
	//	return FALSE;
	//}

	return TRUE;
}

BOOL CTVCommCtrl::PortClear()
{
	int nRev;
	CString sTVComPort;
	int nPortNo;

	nRev = m_ctrlTVCommCtrl.ClearPort();
	
	nPortNo = m_ctrlTVCommCtrl.m_wPortID;

	if((nPortNo >= 1) && (nPortNo <= 9))
	{
		sTVComPort.Format("COM%d",nPortNo);
	}
	else if((nPortNo >= 10) && (nPortNo <= 16))
	{
		sTVComPort.Format("\\\\.\\COM%d",nPortNo);
	}
	else
		return FALSE;

	if(nRev == 0)
	{
		PortClose();
		
//		_Wait(500);
		if(Create(sTVComPort,m_ctrlTVCommCtrl.dwBaudRate) == FALSE)
		{
			PortClose();

			if(Create(sTVComPort,m_ctrlTVCommCtrl.dwBaudRate) == FALSE)
			{
				return FALSE;
			}
		}
	}	

	return TRUE;
}

//TVCommCtrl.m_nReceiveData[TVCommCtrl.m_nReceiveLength

BOOL CTVCommCtrl::Boot_Check(int nWait)
{
	CString sIndex;
	CString sReadData;
	CString sTemp;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");

	////BOOL bResult = TRUE;
	////int nNoTest = m_aMacAdd.GetSize();
	////if (bWifi) { nCmd = 0x46; }

	//BYTE nCmd = 0xF7; 

	//if (!SendCommand(nCmd))
	//{
	//	return FALSE;
	//}
	//
	//if(!ReceiveCommString( nWait))
	//{
	//	return FALSE;
	//}

	////[BB] [04] [02] [F7] [01] [XX]

	//if( (m_nRevData[0] == 0xBB) && (m_nRevData[3] == 0xF7) && (m_nRevData[4] == 0x01))
	//{ 
	//	return TRUE;
	//}
	//else{
	//	return FALSE;
	//}

	return TRUE;

}
//
////+add 090415
//BOOL CTVCommCtrl::Set_Mic_OnOff(BOOL bFlag, int nWait)
//{
///*	CString sIndex;
//	CString sReadData;
//	CString sTemp;
//	CString szMsg1 = _T("");
//	CString szPrevMsg = _T("");
//
//	if(bFlag)
//	{
//		sTemp = _T("Mic On");
//		sIndex.Format("%02x", 0x10);
//	}
//	else
//	{
//		sTemp = _T("Mic Off");
//		sIndex.Format("%02x", 0x20);
//	}
//
//	if((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
//	{
//		g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, sTemp);
//	}
//
//	PortClear();
//	if(!SendRun("a", "m", 0, sIndex))
//	{
//		return FALSE;
//	}
//	if(!ReceiveCommString(4, nWait, sReadData))
//	{
//		return FALSE;
//	}
//
//	//090522
//	int nIndex;
//	nIndex = sReadData.Find(0x0d);
//	if(nIndex != -1)
//	{
//		szMsg1 = sReadData.Left(nIndex + 1);
//	}
//	else{
//		szMsg1 = sReadData;
//	}
//
//	if(sReadData.Find("OK") != -1)
//	{ 
//		return TRUE;
//	}
//	else{
//		return FALSE;
//	}
//	*/
//	return TRUE;
//
//}
//	//+add PSH 090417
//BOOL CTVCommCtrl::Check_Value(int nData, int nTarget, int nMargin)
//{
//	int nMin = nTarget - nMargin;
//	int nMax = nTarget + nMargin;
//
//	if(	(nMin <= nData) && (nData <= nMax))
//	{
//		return TRUE;
//	}
//	else{
//		return FALSE;
//	}
//}
void CTVCommCtrl::Set_MAC_Address(CString sData)
{
	sData.MakeUpper();
	m_aMacAdd.Add(sData);	
}

BOOL CTVCommCtrl::MAC_AddressCheck(int nMacKind)
{
	BYTE nCmd;
//	CString sData;
	CString sReadData;
	CString sMAC_Add;
	CString sTemp;
//	int nTemp;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");
	BYTE nCheckSum1  = 0x00;
	BYTE nCheckSum2  = 0x00;
	int i;
	BOOL bCheckSum_Check = TRUE;

	BOOL bResult = TRUE;
	int nNoTest = m_aMacAdd.GetSize();

	//if (nMacKind == 1) { nCmd = _COMMAND_WIFI_MAC_READ; }
	//else if (nMacKind == 2) { nCmd = _COMMAND_BT_MAC_READ; }
	//else { nCmd = _COMMAND_LAN_MAC_READ; }

	

	
	//if(!SendCommand(nCmd))
	//{
	//	return FALSE;
	//}
	//

	//if(!ReceiveCommString(5000))
	//{
	//	return FALSE;
	//}
	//m_nReceiveLength
	m_nRevLength = m_nReceiveLength;
	memcpy(m_nRevData, m_nReceiveData, m_nRevLength);
	if(m_nReceiveLength < 4)
		return TEST_WAIT;
	if (m_nRevLength < m_nRevData[1] + 2)
	{
		return TEST_WAIT;
	}
	if ((m_nSendCmd != m_nRevData[3]) || (m_nSendCmd != m_nRevData[3]))
	{
		return FALSE;
	}

	for(i =0; i < m_nRevLength; i++)
	{
		sTemp.Format("%02X ", m_nRevData[i]);
		szMsg1 = szMsg1 + sTemp;
	}
	for(i =0; i < m_nRevLength - 1; i++)
	{
		nCheckSum1 = nCheckSum1 ^ m_nRevData[i];
	}

	nCheckSum2 = m_nRevData[m_nRevLength - 1];
	if(nCheckSum1 != nCheckSum2){
		sTemp.Format(",CheckSum Fail(%02X,%02X)", nCheckSum1, nCheckSum2);
		szMsg1 = szMsg1 + sTemp;
		bCheckSum_Check = FALSE;
	}
	
	for(i =4; i < m_nRevLength - 1; i++)
	{
		sTemp.Format("%c", m_nRevData[i]);
		sReadData = sReadData + sTemp;
	}

	if (m_nSendCmd == _COMMAND_WIFI_MAC_READ)
	{
		CurrentSet->sWifiMacAdd = sReadData;
		sTemp.Format("Wifi MAC Add : %s)", sReadData);
	}
	else if (m_nSendCmd == _COMMAND_BT_MAC_READ)
	{
		CurrentSet->sBTMacAdd = sReadData;
		sTemp.Format("BT MAC Add : %s)", sReadData);
	}
	else if (m_nSendCmd == _COMMAND_LAN_MAC_READ)
	{
		CurrentSet->sMacAdd = sReadData;
		sTemp.Format("MAC Add : %s)", sReadData);
	}
	else
	{
		sTemp.Format("MAC Command Error : %s)", sReadData);
		bResult = FALSE;
	}
	
	if(CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
	{
		AddStringToStatus(sTemp);
	}

	if((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
	{
		g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
		
		if(szPrevMsg != _T(""))
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1 + sTemp;
		}
		else
		{
			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
			pCurStep->m_strMsg = szMsg1 + sTemp;
		}		
	}
	if(!bCheckSum_Check){return FALSE;}

	sReadData.MakeUpper();

	if(sReadData.Find("00:00:00:00:00:00") != -1)
	{
		bResult = FALSE;
	}
	else if(sReadData.Find("FF:FF:FF:FF:FF:FF") != -1)
	{
		bResult = FALSE;
	}
	else if(sReadData.Find("00:10:18:26:08:E0") != -1)
	{
		bResult = FALSE;
	}
	else if(sReadData.Find("00:F0:FF:00:F0:FF") != -1)
	{
		bResult = FALSE;
	}
	if(!bResult){
		return FALSE;
	}

	

	sMAC_Add = sReadData.Left(8);
	if(nNoTest == 0) return FALSE; 
	bResult = FALSE;

	for(int i=0; i<nNoTest; i++)
	{
		if(sMAC_Add.Compare(m_aMacAdd.GetAt(i)) == 0){
			bResult = TRUE;
		}
	}
	
	m_aMacAdd.RemoveAll();

	return bResult;
}

BOOL CTVCommCtrl::MAC_AddressRead( int nMacKind)
{
	BYTE nCmd;
	CString sReadData;
	CString sMAC_Add;
	CString sTemp;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");
	BYTE nCheckSum1 = 0x00;
	BYTE nCheckSum2 = 0x00;
	int i;
	BOOL bCheckSum_Check = TRUE;

	BOOL bResult = TRUE;

	if (nMacKind == _COMMAND_WIFI_MAC_READ) 
	{ 
		nCmd = _COMMAND_WIFI_MAC_READ;
	}
	else if (nMacKind == _COMMAND_BT_MAC_READ) 
	{
		nCmd = _COMMAND_BT_MAC_READ;
	}
	else
	{ 
		nCmd = _COMMAND_LAN_MAC_READ;
	}

	m_nSendCmd = nCmd;

	if (!SendCommand(nCmd))
	{
		return FALSE;
	}
	pCurFunc->m_nFuncTestType = _FUNC_MAC_ADD_TEST_TYPE;

	return TRUE;	
}

BOOL CTVCommCtrl::MAC_AddressRead(CString &sMac_add, int nMacKind)
{
	BYTE nCmd;
	CString sReadData;
	CString sMAC_Add;
	CString sTemp;
	CString szMsg1 = _T("");
	CString szPrevMsg = _T("");
	BYTE nCheckSum1  = 0x00;
	BYTE nCheckSum2  = 0x00;
	int i;
	BOOL bCheckSum_Check = TRUE;

	BOOL bResult = TRUE;

	if (nMacKind == _COMMAND_WIFI_MAC_READ)
	{
		nCmd = _COMMAND_WIFI_MAC_READ;
	}
	else if (nMacKind == _COMMAND_BT_MAC_READ)
	{
		nCmd = _COMMAND_BT_MAC_READ;
	}
	else
	{
		nCmd = _COMMAND_LAN_MAC_READ;
	}

	m_nSendCmd = nCmd;

	if(!SendCommand(nCmd))
	{
		return FALSE;
	}
	pCurFunc->m_nFuncTestType = _FUNC_MAC_ADD_TEST_TYPE;
	return TRUE;

}
//
//BOOL CTVCommCtrl::Serial_NumberCheck()
//{
//	BYTE nCmd;
//	CString sTemp;
//	CString sReadData;
//	CString szMsg1 = _T("");
//	CString szPrevMsg = _T("");
//	BYTE nCheckSum1  = 0x00;
//	BYTE nCheckSum2  = 0x00;
//	int i;
//	BOOL bCheckSum_Check = TRUE;
//
//	BOOL bResult = FALSE;
//
//	nCmd = 0xB4;
//
//	if(!SendCommand(nCmd))
//	{
//		return FALSE;
//	}
//	//20210120 Time //_Wait(100);
//
//	if(!ReceiveCommString(5000))
//	{
//		return FALSE;
//	}
//
//	for(i =0; i < m_nRevLength; i++)
//	{
//		sTemp.Format("%02X ", m_nRevData[i]);
//		szMsg1 = szMsg1 + sTemp;
//	}
//	for(i =0; i < m_nRevLength - 1; i++)
//	{
//		nCheckSum1 = nCheckSum1 ^ m_nRevData[i];
//	}
//
//	nCheckSum2 = m_nRevData[m_nRevLength - 1];
//	if(nCheckSum1 != nCheckSum2){
//		sTemp.Format(",CheckSum Fail(%02X,%02X)", nCheckSum1, nCheckSum2);
//		szMsg1 = szMsg1 + sTemp;
//		bCheckSum_Check = FALSE;
//	}
//	
//	for(i =4; i < m_nRevLength - 1; i++)
//	{
//		sTemp.Format("%c", m_nRevData[i]);
//		sReadData = sReadData + sTemp;
//	}
//	sTemp.Format("S/N : %s)", sReadData); 
//	if(CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
//	{
//		AddStringToStatus(sTemp);
//	}
//
//	if((CurrentSet->bIsRunning) && (CurrentSet->nDisplayType == DETAILEDGRID))
//	{
//		g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
//		
//		if(szPrevMsg != _T(""))
//		{
//			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1 + sTemp;
//		}
//		else
//		{
//			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
//			pCurStep->m_strMsg = szMsg1 + sTemp;
//		}		
//	}
//	if(!bCheckSum_Check){return FALSE;}
//
//	sReadData.MakeUpper();
//
//	if(sReadData.Compare(m_strWipId) == 0){
//			bResult = TRUE;
//	}
//	
//	return bResult;
//}
//
//BOOL CTVCommCtrl::Check_MicDiffLevel()
//{
//	BYTE nCmd;
//	CString sTemp;
//	CString sReadData;
//	CString szMsg1 = _T("");
//	CString szPrevMsg = _T("");
//	BYTE nCheckSum  = 0x00;
//	int i;
//	BOOL bCheckSum_Check = TRUE;
//
//	BOOL bResult = FALSE;
//
//	nCmd = 0xF1;
//
//	//==============
//	// Send Command
//	//==============
//	if(!SendCommand(nCmd))
//	{
//		szMsg1 = "Send Fail";
//		goto END_THREAD;
//	}
//
//	//20210120 Time //_Wait(500);
//	//==================
//	// Receive Response
//	//==================
//	if(!ReceiveCommString(5000))
//	{
//		szMsg1 = "Read TimeOut";
//		goto END_THREAD;
//	}
//
//	for(i =0; i < m_nRevLength; i++)
//	{
//		sTemp.Format("%02X ", m_nRevData[i]);
//		szMsg1 = szMsg1 + sTemp;
//	}
//	for(i =0; i < m_nRevLength - 1; i++)
//	{
//		nCheckSum = nCheckSum ^ m_nRevData[i];
//	}
//
//	if(nCheckSum != m_nRevData[m_nRevLength - 1]){
//		szMsg1 = szMsg1 + ",CheckSum Fail";
//		goto END_THREAD;
//	}
//	if(nCmd != m_nRevData[3]){
//		szMsg1 = szMsg1 + ",Command Fail";
//		goto END_THREAD;
//	}
//
//	if(m_nRevData[4] == 0x01){		
//		bResult = TRUE;
//		szMsg1 = szMsg1 + "(OK)";
//	}
//	else{  
//		bResult = FALSE;
//		szMsg1 = szMsg1 + "(NG)";
//	}
//
//END_THREAD :
//	if(CurrentSet->bIsRunning)
//	{
//		g_pView->GetResultFromDetailedGrid(pCurStep->m_nStep, szPrevMsg); 
//		
//		if(szPrevMsg != _T(""))
//		{
//			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szPrevMsg + " , " + szMsg1);
//			pCurStep->m_strMsg = szPrevMsg + " , " + szMsg1;
//		}
//		else
//		{
//			g_pView->InsertMsg2DetailedGrid(pCurStep->m_nStep, szMsg1);
//			pCurStep->m_strMsg = szMsg1;
//		}		
//	}
//
//
//	
//	return bResult;
//}