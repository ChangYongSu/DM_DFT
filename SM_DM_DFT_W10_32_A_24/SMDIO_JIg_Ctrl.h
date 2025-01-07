// 명    칭 : DAT(Digital Auto Test)
// 창작일자 : 2000. 4. 0
// 소    속 : LG전자(LG생산기술원 MIT 박승화)
// File  명 : Inst.h


#ifndef	__SMDIO_Jig_Ctrl_H_
#define __SMDIO_Jig_Ctrl_H_

#include <afxmt.h>

#include <conio.h>      // for ISA Bus, _inp, _oup
#include "Resource.h"
//#include "comm.h"
#include "CommThread.h"




class CSMDIO_Jig_Ctrl : public CObject
{
public :
	CSMDIO_Jig_Ctrl();
	virtual ~CSMDIO_Jig_Ctrl();

//	CMSComm	m_CommCtrl;
	CCommThread	m_CommCtrl;
	BOOL	CreateComm(CString sComPort, DWORD nBaudRate);
	void	CloseComm(); 
	BOOL SendCommand(byte* command, int Count);
	//BOOL	SendString(CString str);
	BOOL	ReceiveData();

	int m_CheckDIChannel[32];
	BOOL m_CheckDITrue[32];
	BOOL m_ReceiveDIValue[32];
	BOOL m_ReceiveDOValue[32];

	BOOL m_WriteDOValue[32];


	int m_CheckVIChannel[32];;
	double m_CheckVIMinVal[32];
	double m_CheckVIMaxVal[32];
	double m_ReceiveVIVal[32];


	double	SetTargetDi(int lCh, BOOL lOn );
	double	SetTargetDo(int lCh, BOOL lOn);
	double	WriteTargetDOUT();
	double	SetTargetVi(int lCh, double lVoltMin, double lVoltMax);
	double	CheckTargetInput();
	double	ReadTargetInput();
	double  CheckTargetVoltage();
	double  ReadTargetVoltage();
	double	ReadTargetVoltage(int lPort);
	void	ResetTargetValue();

	double	MeasureTh();

	int		m_nPortID;
	BYTE	m_strReceive[225];
	int		m_ReceiveCount;
	int		m_WaitReceive;

	BYTE	m_strCommand[225];
	int		m_CommandCount;
	BOOL	m_bCommError;
	CString	m_strErrMsg;		
	BOOL	m_bPortOpen;
private:

};



// Global Object
extern CSMDIO_Jig_Ctrl gSMDIO_Ctrl;

#endif	// __INSTRUMENTS_H__