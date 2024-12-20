// 명    칭 : AIAS(Automatic Inline Alignment System)
// 창작일자 : 1997. 2. 21
// 소    속 : LG전자(LG생산기술원 MI Gr. 오구환)
// File  명 : Dmm.cpp

// DMM.cpp : implementation file
//
 

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "SMDIO_Jig_Ctrl.h"
#include "global.h"
#include "realmeas.h"
#include "parser.h"
#include "step.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg;
CSMDIO_Jig_Ctrl gSMDIO_Ctrl;

CSMDIO_Jig_Ctrl::CSMDIO_Jig_Ctrl()
{
	m_nPortID = -1;
	m_bPortOpen = FALSE;
	m_strErrMsg				= _T("");
	m_bCommError = FALSE;
};

CSMDIO_Jig_Ctrl::~CSMDIO_Jig_Ctrl()
{

};

//BOOL CSMDIO_Jig_Ctrl::CreateComm(CString sComPort, DWORD nBaudRate)
//{
//	CString sTmp = sComPort;
//	sTmp.Delete(0, sTmp.Find("COM")+3);
//	m_nPortID = atoi(sTmp);
//
//	m_strErrMsg = _T("");
//
//	if (!m_CommCtrl.OpenPort(sComPort, nBaudRate, m_nPortID, 8, NOPARITY, ONESTOPBIT, FALSE))//if (!m_CommCtrl.OpenPort(sComPort, nBaudRate, m_nPortID, 8, NOPARITY, ONESTOPBIT, FALSE))
//	{
//		m_strErrMsg.Format("[SM DIO Ctrl CommPort] \n%s Init Failed!", sComPort);
//		m_bPortOpen = FALSE;
//		m_bCommError = TRUE;
//		return FALSE;
//	}
//	
//	m_bPortOpen = TRUE;
//	m_bCommError = FALSE;
//
//	_Wait(150);
//
//	return TRUE;
//}
//void CSMDIO_Jig_Ctrl::CloseComm()
//{
//	m_CommCtrl.ClosePort();
//	m_bPortOpen = FALSE;
//}

BOOL CSMDIO_Jig_Ctrl::ReceiveData()
{
	BOOL		bDoing;
    clock_t		start;
	int			i/*, nWaitLimit*/;
	BYTE		buf;
	DWORD		dwRead;			// Read Byte Count
	BYTE		buff[2048];		// Read Buffer
	CString		sTmp;
	CString str;
	int idx1 = 0;
	int lRcvCount = 0;

	if(m_bCommError) return FALSE;

	memset(m_strReceive, 0, 225);
	bDoing = TRUE;
	start = clock();

	//m_CommCtrl.m_QueueRead.Clear();

	while (bDoing)
	{
		do	
		{

			dwRead = m_CommCtrl.ReadComm( buff, 2048);
			if (dwRead == 0) break;		
			if (BUFF_SIZE - m_CommCtrl.m_QueueRead.GetSize() > (int)dwRead)
			{
				for ( WORD i = 0; i < dwRead; i++)
					m_CommCtrl.m_QueueRead.PutByte(buff[i]);
			}
			else
			{
				return FALSE;
			}

			if ((clock() - start)*1000/CLOCKS_PER_SEC > 3000) 
			{//Over Limit Time.....False Return
				m_CommCtrl.m_QueueRead.Clear();
				return FALSE;
			}
			  
		} while (dwRead); 

		int rrv = m_CommCtrl.m_QueueRead.GetSize();

		if (rrv > 0)
		{
			for(int i=0; i<rrv; i++)
			{
				m_CommCtrl.m_QueueRead.GetByte(&buf);
				m_strReceive[lRcvCount] = buf;
				lRcvCount++;
			}

		//	sTmp.Format("%s",m_strReceive);
			//str += sTmp;
			
			idx1 = idx1 + rrv;

			//idx1 = str.Find(0x03);
			if(lRcvCount >= 13){
				m_CommCtrl.m_QueueRead.Clear();
				return TRUE;
			}
			Sleep(50);
		}
		
        if ((clock() - start)*1000/CLOCKS_PER_SEC > 3000) 
        {//Over Limit Time.....False Return
			m_CommCtrl.m_QueueRead.Clear();
			return FALSE;
		}
	}
	
	return TRUE;	
}


BOOL CSMDIO_Jig_Ctrl::SendCommand(byte* command, int Count)
{
	//BYTE *command;
	
	if(m_bCommError) return FALSE;
	//m_strCommand[225];
	//int		m_ReceiveCount;
	//command = (BYTE*)(LPCTSTR)str;
	
	for (int i = 0; i < Count; i++) {
		m_CommCtrl.WriteComm(command + i, 1);
	}

	m_CommCtrl.m_QueueRead.Clear();
	return TRUE;
}
double	CSMDIO_Jig_Ctrl::SetTargetDi(int lCh, BOOL lOn)
{
	if ((lCh >= 0) && (lCh < 8))
	{
		m_CheckDIChannel[lCh] = 1;
		m_CheckDITrue[lCh] = lOn;
	}
	else
	{
		return 0;
	}
	return 1;
}
double	CSMDIO_Jig_Ctrl::SetTargetDo(int lCh, BOOL lOn)
{
	CString sTemp;
	double dValue = 1;
	if ((lCh >= 0) && (lCh < 24))
	{
		gDoData[lCh] = lOn;

		dValue = 1;
		m_pMainDlg->WriteSM_Out(lCh);
		m_Current_MioNumber = _MIO_P_DO_CHECK;
		pCurFunc->m_nFuncTestType = _FUNC_MIO_TEST_TYPE;
	}
	else
	{
		sTemp.Format("Write DO Port Nuumber Error:%d", lCh);;// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	return dValue;
#if 0
	CString sTemp;
	double dValue = 1;
	
	m_CommCtrl.m_QueueRead.Clear();

	///02 C WO nn WWWW 03 0d 0a

	m_strCommand[0] = STX;
	if (lOn)
	{
		sprintf((char*)&m_strCommand[1], "CWO%02d1111", lCh);
	}
	else
	{
		sprintf((char*)&m_strCommand[1], "CWO%02d0000", lCh);
	}
	m_strCommand[10] = ETX;
	m_strCommand[11] = '\r';
	m_strCommand[12] = '\n';
	m_CommandCount = 13;
	if (!SendCommand(m_strCommand, m_CommandCount))
	{
		sTemp = "Write DO Send Command Error";// 
		AddStringToStatus(sTemp);
		return 0.0;
	}

	if (ReceiveData())
	{
		//0x02DI_ddnnnn0x03/r/n
		int lRevPort = (m_strReceive[3] - 0x30) * 10 + m_strReceive[4] - 0x30;
		if (lRevPort == lCh)
		{
			//m_strReceive[6]
			//m_strReceive[7]
			//m_strReceive[8]
			//m_strReceive[9]
			m_strReceive[10] = 0;
			//CString Stemp1;
			//CString Stemp2;
			//Stemp1 = &(m_strReceive[6]);
			//Stemp2 = Stemp1.Mid(2, 2);
			//Stemp1 = Stemp1.Left(2);
			BYTE HexRcv[2];
			HexRcv[0] = (hex2dec(m_strReceive[6]) << 4) + hex2dec(m_strReceive[7]);
			HexRcv[1] = (hex2dec(m_strReceive[8]) << 4) + hex2dec(m_strReceive[9]);

			for (int i = 0; i < 8; i++)
			{
				if (HexRcv[0] & (0x01 << i))
				{
					m_ReceiveDOValue[i] = 1;
				}
				else
				{
					m_ReceiveDOValue[i] = 0;
				}

				if (HexRcv[1] & (0x01 << i))
				{
					m_ReceiveDOValue[i+8] = 1;
				}
				else
				{
					m_ReceiveDOValue[i+8] = 0;
				}

			}
		//	m_ReceiveDOValue[lCh] = m_strReceive[9] - 0x30;

			if (lOn == m_ReceiveDOValue[lCh])
			{
				sTemp.Format("DO SET %d: OK,", lCh + 1);
				AddStringToStatus(sTemp); //sTemp += sTemp1;
				dValue = 1;
			}
			else
			{
				sTemp.Format("DO SET %d: FAIL,", lCh + 1);
				AddStringToStatus(sTemp); //sTemp += sTemp1;

				dValue = 0;
			}
		}
		else
		{
			sTemp = "DO SET Port Error";// 
			AddStringToStatus(sTemp);
			dValue = 0;
		}

	}
	else
	{
		sTemp = "DO Reeceive Error";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}


	return dValue;
#endif

}
double	CSMDIO_Jig_Ctrl::SetTargetVi(int lCh, double lVoltMin, double lVoltMax)
{

	if ((lCh >= 0) && (lCh < 8))
	{
		m_CheckVIChannel[lCh] = 1;
		m_CheckVIMinVal[lCh] = lVoltMin*100.0;
		m_CheckVIMaxVal[lCh] = lVoltMax*100.0;

	}
	else
	{
		return 0;
	}
	return 1;
}
double CSMDIO_Jig_Ctrl::CheckTargetInput()
{
	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;
	pCurFunc->m_nFuncTestType = _FUNC_MIO_TEST_TYPE;
	for (int i = 0; i < 24; i++)
	{
		if (m_CheckDIChannel[i] != 1)
			continue;
		checkCount++;
	}
	if (checkCount == 0)
	{
		sTemp = "READ SM DI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount > 0)
	{
		dValue = 1;
		m_pMainDlg->ReadSMIO();
		m_Current_MioNumber = _MIO_P_DI_CHECK;
	}
	else
	{
		dValue = 0;
	}


	return dValue;

#if 0

	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;

	//double lReturn = 0;

	if(!m_bPortOpen) return 0.0;

	//int m_CheckDIChannel[32];
	//BOOL m_CheckDITrue[32];
	//BOOL m_ReceiveDIValue[32];
	for (int i = 0; i < 8; i++)
	{
		if (m_CheckDIChannel[i] != 1)
			continue;
		checkCount++;
		



		m_CommCtrl.m_QueueRead.Clear();
		m_strCommand[0] = STX;
		sprintf((char*)&m_strCommand[1], "CREADI_%02d", i);
		m_strCommand[10] = ETX;
		m_strCommand[11] = '\r';
		m_strCommand[12] = '\n';
		m_CommandCount = 13;
		if (!SendCommand(m_strCommand, m_CommandCount))
		{
			sTemp = "READ DI Send Command Error";// 
			AddStringToStatus(sTemp);
			return 0.0;
		}

		if (ReceiveData())
		{
			//0x02DI_ddnnnn0x03/r/n
			int lRevPort =( m_strReceive[3] - 0x30)*10 + m_strReceive[4] - 0x30;
			if (lRevPort == i)
			{

				m_ReceiveDIValue[i] = m_strReceive[9] - 0x30;

				if (m_CheckDITrue[i] == m_ReceiveDIValue[i])
				{
					sTemp1.Format("CH %d: OK,", i + 1);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					OKCount++;
				}
				else
				{
					sTemp1.Format("CH %d: NG,", i + 1);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;

					dValue = 0;
				}
			}
			else
			{
				sTemp = "READ DI Port Error";// 
				AddStringToStatus(sTemp);
				dValue = 0;
			}

		}
	}
	if (checkCount == 0)
	{
		sTemp = "READ DI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount == OKCount)
	{
		dValue = 1;
	}
	else
	{
		dValue = 0;
	}
	

	return dValue;
#endif
}


double CSMDIO_Jig_Ctrl::CheckTargetVoltage()
{
	
	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;
	pCurFunc->m_nFuncTestType = _FUNC_MIO_TEST_TYPE;
	for (int i = 0; i < 32; i++)
	{
		if (m_CheckVIChannel[i] != 1)
			continue;
		checkCount++;
		m_Current_MioNumber = i;
	}
	if (checkCount == 0)
	{
		sTemp = "READ SM VI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount > 0)
	{
		dValue = 1;
		m_pMainDlg->ReadVolt(m_Current_MioNumber); //m_pMainDlg->ReadSMIO();
		//m_Current_MioNumber = _MIO_P_DI_CHECK;
	}
	else
	{
		dValue = 0;
	}


	return dValue;
#if 0
	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;

	//double lReturn = 0;

	if (!m_bPortOpen) return 0.0;

	//int m_CheckDIChannel[32];
	//BOOL m_CheckDITrue[32];
	//BOOL m_ReceiveDIValue[32];
	for (int i = 0; i < 8; i++)
	{
		if (m_CheckVIChannel[i] != 1)
			continue;
		checkCount++;




		m_CommCtrl.m_QueueRead.Clear();
		m_strCommand[0] = STX;
		sprintf((char*)&m_strCommand[1], "CREADV_%02d", i);
		m_strCommand[10] = ETX;
		m_strCommand[11] = '\r';
		m_strCommand[12] = '\n';
		m_CommandCount = 13;
		if (!SendCommand(m_strCommand, m_CommandCount))
		{
			sTemp = "READ VI Send Command Error";// 
			AddStringToStatus(sTemp);
			return 0.0;
		}

		if (ReceiveData())
		{
			//0x02DVddnnnnn0x03/r/n
			int lRevPort = (m_strReceive[3] - 0x30) * 10 + m_strReceive[4] - 0x30;
			if ((lRevPort == i)&&(m_strReceive[10] == ETX))
			{
				CString StrNum;
				m_strReceive[10] = 0;
				StrNum = (char *)&(m_strReceive[5]);
				m_ReceiveVIVal[i] = _ttoi(StrNum);
				//double m_CheckVIMinVal[32];
				//double m_CheckVIMaxVal[32];
				//double m_ReceiveVIVal[32];
				if ((m_CheckVIMinVal[i] <= m_ReceiveVIVal[i])&&(m_CheckVIMaxVal[i] >= m_ReceiveVIVal[i]))
				{
					sTemp1.Format("ADCH %d: OK:%.2fV (%.2f~%.2f) ", i + 1, m_ReceiveVIVal[i] / 100.0, m_CheckVIMinVal[i] / 100.0, m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					OKCount++;
				}
				else
				{
					sTemp1.Format("ADCH %d: NG:%.2fV (%.2f~%.2f) ", i + 1,  m_ReceiveVIVal[i]/100.0, m_CheckVIMinVal[i] / 100.0,m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;

					dValue = 0;
				}
			}
			else
			{
				sTemp = "READ SM VI Port Error";// 
				AddStringToStatus(sTemp);
				dValue = 0;
			}

		}
	}
	if (checkCount == 0)
	{
		sTemp = "READ SM VI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount == OKCount)
	{
		dValue = 1;
	}
	else
	{
		dValue = 0;
	}


	return dValue;
#endif
}

double CSMDIO_Jig_Ctrl::CheckTargetMIO()
{
	double	dValue = 0.0;
	m_pMainDlg->ReadSMIO();	
	m_Current_MioNumber = _MIO_P_DI_CHECK;
	pCurFunc->m_nFuncTestType = _FUNC_MIO_TEST_TYPE;
	return 1;
#if 0
	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;

	//double lReturn = 0;

	if (!m_bPortOpen) return 0.0;

	//int m_CheckDIChannel[32];
	//BOOL m_CheckDITrue[32];
	//BOOL m_ReceiveDIValue[32];
	for (int i = 0; i < 8; i++)
	{
		if (m_CheckVIChannel[i] != 1)
			continue;
		checkCount++;




		m_CommCtrl.m_QueueRead.Clear();
		m_strCommand[0] = STX;
		sprintf((char*)&m_strCommand[1], "CREADV_%02d", i);
		m_strCommand[10] = ETX;
		m_strCommand[11] = '\r';
		m_strCommand[12] = '\n';
		m_CommandCount = 13;
		if (!SendCommand(m_strCommand, m_CommandCount))
		{
			sTemp = "READ VI Send Command Error";// 
			AddStringToStatus(sTemp);
			return 0.0;
		}

		if (ReceiveData())
		{
			//0x02DVddnnnnn0x03/r/n
			int lRevPort = (m_strReceive[3] - 0x30) * 10 + m_strReceive[4] - 0x30;
			if ((lRevPort == i) && (m_strReceive[10] == ETX))
			{
				CString StrNum;
				m_strReceive[10] = 0;
				StrNum = (char *)&(m_strReceive[5]);
				m_ReceiveVIVal[i] = _ttoi(StrNum);
				//double m_CheckVIMinVal[32];
				//double m_CheckVIMaxVal[32];
				//double m_ReceiveVIVal[32];
				if ((m_CheckVIMinVal[i] <= m_ReceiveVIVal[i]) && (m_CheckVIMaxVal[i] >= m_ReceiveVIVal[i]))
				{
					sTemp1.Format("ADCH %d: OK:%.2fV (%.2f~%.2f) ", i + 1, m_ReceiveVIVal[i] / 100.0, m_CheckVIMinVal[i] / 100.0, m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					OKCount++;
				}
				else
				{
					sTemp1.Format("ADCH %d: NG:%.2fV (%.2f~%.2f) ", i + 1, m_ReceiveVIVal[i] / 100.0, m_CheckVIMinVal[i] / 100.0, m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;

					dValue = 0;
				}
			}
			else
			{
				sTemp = "READ SM VI Port Error";// 
				AddStringToStatus(sTemp);
				dValue = 0;
			}

		}
	}
	if (checkCount == 0)
	{
		sTemp = "READ SM VI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount == OKCount)
	{
		dValue = 1;
	}
	else
	{
		dValue = 0;
	}


	return dValue;
#endif
}


int CSMDIO_Jig_Ctrl::CheckResultMIO()
{
	int		nChecked = 0;
	CString sReadData;
	CString sValue;
	CString sTemp;
	CString sTemp1;
	double	dValue = 0.0;
	int		nValue;
	BYTE	nConfig1;
	BYTE	nConfig2;
	int checkCount = 0;
	int OKCount = 0;
	int NGCount = 0;

	//double lReturn = 0;
	pCurFunc->m_nFuncTestType = _FUNC_MIO_TEST_TYPE;
	//if (!m_bPortOpen) return TEST_FAIL;


	if (m_pMainDlg->m_ReadMIOComAck == COM_ACK_OK)
	{
		if (m_Current_MioNumber == _MIO_P_DI_CHECK)
		{
			for (int i = 0; i < 24; i++)
			{
				if (m_CheckDIChannel[i] != 1)
					continue;
				m_ReceiveDIValue[i] = gDiRcvData[i];
				if (m_CheckDITrue[i] == m_ReceiveDIValue[i])
				{
					sTemp1.Format("DI %d: OK,", i + 1);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					OKCount++;
				}
				else
				{
					sTemp1.Format("DI %d: NG,", i + 1);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					NGCount++;
					
				}
			}
			if (NGCount > 0)
			{
				return TEST_FAIL;
			}
			else
			{
				for (int i = 0; i < 32; i++)
				{
					if (m_CheckVIChannel[i] != 1)
						continue;
					m_Current_MioNumber = i;
					m_pMainDlg->ReadVolt(m_Current_MioNumber);
					return TEST_WAIT;

				}
				return TEST_PASS;

			}
		}//g_ReadVoltData
		else if (m_Current_MioNumber == _MIO_P_DO_CHECK)
		{
			for (int i = 0; i < 24; i++)
			{
				if (gDoConfirmData[i] != gDoData[i])
				{
					return TEST_FAIL;
				}
			}
			return TEST_PASS;
		}
		else
		{
			if ((m_Current_MioNumber >= 0) && (m_Current_MioNumber < 32))
			{
				if (m_CheckVIChannel[m_Current_MioNumber] == 1)
				{
					m_ReceiveVIVal[m_Current_MioNumber] = g_ReadVoltData[m_Current_MioNumber];
					if ((m_CheckVIMinVal[m_Current_MioNumber] <= m_ReceiveVIVal[m_Current_MioNumber])
						&& (m_CheckVIMaxVal[m_Current_MioNumber] >= m_ReceiveVIVal[m_Current_MioNumber]))
					{
						sTemp1.Format("VI %d:%.2f(%.2f~%.2f) OK,", m_Current_MioNumber,
							m_ReceiveVIVal[m_Current_MioNumber], m_CheckVIMinVal[m_Current_MioNumber], m_CheckVIMaxVal[m_Current_MioNumber]);
						AddStringToStatus(sTemp1); //sTemp += sTemp1;
					}
					else
					{
						sTemp1.Format("VI %d:%.2f(%.2f~%.2f) NG,", m_Current_MioNumber,
							m_ReceiveVIVal[m_Current_MioNumber], m_CheckVIMinVal[m_Current_MioNumber], m_CheckVIMaxVal[m_Current_MioNumber]);
						AddStringToStatus(sTemp1); //sTemp += sTemp1;

						return TEST_FAIL;
					}
				}
				m_Current_MioNumber++;
				for (int i = m_Current_MioNumber; i < 32; i++)
				{
					if (m_CheckVIChannel[i] != 1)
						continue;
					m_Current_MioNumber = i;
					m_pMainDlg->ReadVolt(m_Current_MioNumber);
					return TEST_WAIT;

				}
				return TEST_PASS;
			}
			
		}
	}
	else if(m_pMainDlg->m_ReadMIOComAck == COM_ACK_BUSY)
	{
		return TEST_FAIL;
	}
	else//(m_pMainDlg->m_ReadMIOComAck == COM_ACK_WAIT)
	{
		return TEST_WAIT;
	}

	return TEST_WAIT;

	//int m_CheckDIChannel[32];
	//BOOL m_CheckDITrue[32];
	//BOOL m_ReceiveDIValue[32];
	for (int i = 0; i < 8; i++)
	{
		if (m_CheckVIChannel[i] != 1)
			continue;
		checkCount++;




		m_CommCtrl.m_QueueRead.Clear();
		m_strCommand[0] = STX;
		sprintf((char*)&m_strCommand[1], "CREADV_%02d", i);
		m_strCommand[10] = ETX;
		m_strCommand[11] = '\r';
		m_strCommand[12] = '\n';
		m_CommandCount = 13;
		if (!SendCommand(m_strCommand, m_CommandCount))
		{
			sTemp = "READ VI Send Command Error";// 
			AddStringToStatus(sTemp);
			return 0.0;
		}

		if (ReceiveData())
		{
			//0x02DVddnnnnn0x03/r/n
			int lRevPort = (m_strReceive[3] - 0x30) * 10 + m_strReceive[4] - 0x30;
			if ((lRevPort == i) && (m_strReceive[10] == ETX))
			{
				CString StrNum;
				m_strReceive[10] = 0;
				StrNum = (char *)&(m_strReceive[5]);
				m_ReceiveVIVal[i] = _ttoi(StrNum);
				//double m_CheckVIMinVal[32];
				//double m_CheckVIMaxVal[32];
				//double m_ReceiveVIVal[32];
				if ((m_CheckVIMinVal[i] <= m_ReceiveVIVal[i]) && (m_CheckVIMaxVal[i] >= m_ReceiveVIVal[i]))
				{
					sTemp1.Format("ADCH %d: OK:%.2fV (%.2f~%.2f) ", i + 1, m_ReceiveVIVal[i] / 100.0, m_CheckVIMinVal[i] / 100.0, m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;
					OKCount++;
				}
				else
				{
					sTemp1.Format("ADCH %d: NG:%.2fV (%.2f~%.2f) ", i + 1, m_ReceiveVIVal[i] / 100.0, m_CheckVIMinVal[i] / 100.0, m_CheckVIMaxVal[i] / 100.0);
					AddStringToStatus(sTemp1); //sTemp += sTemp1;

					dValue = 0;
				}
			}
			else
			{
				sTemp = "READ SM VI Port Error";// 
				AddStringToStatus(sTemp);
				dValue = 0;
			}

		}
	}
	if (checkCount == 0)
	{
		sTemp = "READ SM VI No Check Port";// 
		AddStringToStatus(sTemp);
		dValue = 0;
	}
	else if (checkCount == OKCount)
	{
		dValue = 1;
	}
	else
	{
		dValue = 0;
	}


	return dValue;
}


void	CSMDIO_Jig_Ctrl::ResetTargetValue()
{
	for (int i = 0; i < 32; i++)
	{
		m_CheckDIChannel[i] = 0;
		m_CheckDITrue[i] = 0;
		m_CheckVIChannel[i] = 0;
		m_CheckVIMinVal[i] = 100;
		m_CheckVIMaxVal[i] = 0;
	}
}

