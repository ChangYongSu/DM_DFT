#include "stdafx.h"
#include <afxmt.h>
#include "CommThread.h"
#include "global.h"

// �޼����� ���� ������ �ڵ�, �θ� �����쿡�� HWND hCommWnd= this->m_hWnd��
// ������ �ش�.
extern HWND g_hCommWnd;

//extern CCriticalSection critic;

// CQueue ������========================================= 

// Queue�� ������
CQueue::CQueue()
{
	Clear();
}

// Initialize Queue
void CQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff, 0, BUFF_SIZE);
}

// Queue�� ��� �ִ� �ڷ� ����.
int CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

// Queue�� 1 byte ����.
BOOL CQueue::PutByte(BYTE b)
{
	if (GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}

// Queue���� 1 byte ����.
BOOL CQueue::GetByte(BYTE* pb)
{
	if (GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}

CCommThread::CCommThread( )
{
//	hReadEnd = CreateEvent(NULL, TRUE/*bManualReset*/, FALSE /*bInitialState*/, NULL);
	m_bConnected = FALSE;
	m_hThreadWatchComm= NULL;
	m_osRead.hEvent = NULL;
	m_osWrite.hEvent = NULL;

}
CCommThread::~CCommThread( )
{

	ClosePort();
}


//+ 2007.9.28 Add BY USY
BOOL CCommThread::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID, BYTE bByteSize, BYTE bParity, BYTE bStopBits,BOOL bWatch)
//BOOL CCommThread::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID)
//-
{
	// Local ����.
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	// Initialize variables?
	m_bConnected = FALSE;
	m_wPortID	= wPortID; // COM1-> 0, COM2->1,,,,,

	// Initialize overlapped structure
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;

	if (! (m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	return FALSE;

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) return FALSE;
	
	// Open COM port?
	m_sPortName = sPortName;

	m_hComm = CreateFile( m_sPortName, 
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
		NULL);
	
	if (m_hComm == (HANDLE) -1) return FALSE;

	// ��Ʈ ���� ����.

	// EV_RXCHAR event ����
	SetCommMask( m_hComm, EV_RXCHAR);	

	//+change 090218(Modification No2)
	// InQueue, OutQueue ũ�� ����.
//	SetupComm( m_hComm, 2048, 2048);	
	SetupComm( m_hComm, 1024*32, 1024*32); // 32KB	

	// ��Ʈ ����.
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout ����.
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / (dwBaud+1);
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts( m_hComm, &timeouts);

	// dcb ����
	dcb.DCBlength = sizeof(DCB);
	GetCommState( m_hComm, &dcb);	// ���� ���� ����.
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = bByteSize; //8;
	dcb.Parity = bParity; //0;
	dcb.StopBits = bStopBits; //0;
	dcb.fInX = dcb.fOutX = 0 ; //XON/XOFF ���Ѱ�
//	dcb.XonChar = ASCII_XON ;
//	dcb.XoffChar = ASCII_XOFF ;

//	dcb.fInX = dcb.fOutX = 0;		// Xon, Xoff ���.
//	dcb.XonChar = ASCII_XON;
//	dcb.XoffChar = ASCII_XOFF;
//	dcb.XonChar = 0x02;
//	dcb.XoffChar = 0x03;

//	dcb.XonLim = 100;
//	dcb.XoffLim = 100;

	if (! SetCommState( m_hComm, &dcb))	return FALSE;

	// ��Ʈ ���� ������ ����.
	m_bConnected = TRUE;

	//+ 2007.9.28 Mod BY USY
	if(bWatch == TRUE)
	{
		m_hThreadWatchComm = CreateThread( NULL, 0, 
		(LPTHREAD_START_ROUTINE)ThreadWatchComm, this, 0, &dwThreadID);
		if (! m_hThreadWatchComm)
		{
			ClosePort();
			return FALSE;
		}
	}

	return TRUE;
}
	
// ��Ʈ�� �ݴ´�.
void CCommThread::ClosePort()
{
	DWORD dwExitCode = 0;
	//+add 090228(Modification No2)
	if(m_bConnected)
	{
		m_bConnected = FALSE;
		if (m_hThreadWatchComm)
		{
			WaitForSingleObject(m_hThreadWatchComm, 2000);
			if(m_hThreadWatchComm){
				TerminateThread(m_hThreadWatchComm,dwExitCode);
				CloseHandle(m_hThreadWatchComm);         
				m_hThreadWatchComm = NULL;
			}
		}

		SetCommMask( m_hComm, 0);
    
		EscapeCommFunction( m_hComm, CLRDTR ) ;

		PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
		CloseHandle( m_hComm);
	}
		//090919
	if(m_osRead.hEvent != NULL)
	{
		CloseHandle(m_osRead.hEvent); 
		m_osRead.hEvent = NULL;
	}

	if(m_osWrite.hEvent != NULL)
	{
		CloseHandle(m_osWrite.hEvent); 
		m_osWrite.hEvent = NULL;
	}
}

DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	DWORD   Error;
	COMSTAT	comstat;

	if (! WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		//+2007.12.11 Add BY USY
		Error = GetLastError();

		if(Error == ERROR_IO_PENDING)
		{
//			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, FALSE))
			{
				dwError = GetLastError();

				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

// ��Ʈ�κ��� pBuff�� nToWrite��ŭ �д´�.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//----------------- system queue�� ������ byte���� �̸� �д´�.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	
	if (dwRead > 0)
	{
		if (! ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}
/*
//����Ÿ�� �а� ����Ÿ�� �о��ٴ�
//�޼����� �����Ѵ�.
void CCommThread::SetReadData(LPTSTR data)
{

	lstrcpy((LPTSTR)abIn,(LPCTSTR)data);
   //ConverData
   //������ �����쿡 WM_RECEIVEDATA�޼����� �����־� ���� ����Ÿ�� ���Դٴ°���
   //�˷��ش�.

//	::SendMessage(g_hCommWnd, WM_RECEIVEDATA, pComm->m_wPortID, 0 );//CSerialComDlg�� �����Ͱ� ���Դٴ� �޽����� ����
	::SendMessage(g_hCommWnd,WM_RECEIVEDATA, m_wPortID, 0);
}


DWORD	ThreadWatchComm(CCommThread* pComm)
{
	DWORD		dwEvent;
	OVERLAPPED	os;
	BOOL		bOk = TRUE;
	char		buff[2049];	 // �б� ����
	DWORD		dwRead;	 // ���� ����Ʈ��.

	// Event, OS ����.
	memset( &os, 0, sizeof(OVERLAPPED));
	if (! (os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)))
		bOk = FALSE;
	if (! SetCommMask( pComm->m_hComm, EV_RXCHAR))
		bOk = FALSE;
	if (! bOk)
	{
		AfxMessageBox("Error while creating ThreadWatchComm, " + pComm->m_sPortName);
		return FALSE;
	}

	// ��Ʈ�� �����ϴ� ����.
	while (pComm->m_bConnected)
	{
		dwEvent = 0;
		
		// ��Ʈ�� ���� �Ÿ��� �ö����� ��ٸ���.
		//+2007.10.17 Mod BY MKW
//		WaitCommEvent( pComm->m_hComm, &dwEvent, &os);
		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);		//-

		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{

			do
		   {
			   memset(buff,0, 2048);
				if (dwRead = pComm->ReadComm( buff, 2048))
				{
					pComm->SetReadData(buff);
				}
		   }
		   while ( dwRead > 0 ) ;
		}
		Sleep(0); //ResetEvent(os.hEvent);

		
			//	�о� ������ �޽����� ������.
//			if(dwRead > 0) ::PostMessage(g_hCommWnd,WM_COMM_READ, pComm->m_wPortID, 0);
		//	::SendMessage(g_hCommWnd,WM_COMM_READ, pComm->m_wPortID, 0);
		//	::PostMessage(g_hCommWnd,WM_COMM_READ, pComm->m_wPortID, 0);
			//
			//-
		//	SetEvent(pComm->hReadEnd);

	}	
	
	// ��Ʈ�� ClosePort�� ���� ������ m_bConnected �� FALSE�� �Ǿ� ����.

	CloseHandle( os.hEvent);
	CloseHandle(pComm->m_hThreadWatchComm);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}
*/

DWORD	ThreadWatchComm(CCommThread* pComm)
{
   DWORD           dwEvent;
   OVERLAPPED      os;
   BOOL            bOk = TRUE;
   BYTE            buff[2048];      // �б� ����
   DWORD           dwRead;  // ���� ����Ʈ��.
 

   // Event, OS ����.
   memset( &os, 0, sizeof(OVERLAPPED));
   
   //--> �̺�Ʈ ����..
   if( !(os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)) )
   {
		bOk = FALSE;
   }

   //--> �̺�Ʈ ����ũ..
   if( !SetCommMask( pComm->m_hComm, EV_RXCHAR) )
   {
	   bOk = FALSE;
   }

   //--> �̺�Ʈ��..����ũ ������ ������..
   if( !bOk )
   {
		AfxMessageBox("Error while creating ThreadWatchComm, " + pComm->m_sPortName);
		return FALSE;
   }
  
   while (pComm ->m_bConnected)//��Ʈ�� ����Ǹ� ���� ������ ��
   {
 		dwEvent = 0;
	
        // ��Ʈ�� ���� �Ÿ��� �ö����� ��ٸ���.
        WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);
	
	
		//--> �����Ͱ� ���ŵǾ��ٴ� �޼����� �߻��ϸ�..
        if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
        {
            // ��Ʈ���� ���� �� �ִ� ��ŭ �д´�.
				//--> buff �� �޾Ƴ���..
			do
			{
				dwRead = pComm->ReadComm( buff, 2048); //���� ������ �о� ���� 
				if(BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for( WORD i = 0; i < dwRead; i++ )
					{
						pComm->m_QueueRead.PutByte(buff[i]);//ť ���ۿ�  ���� ������ �ֱ� 
					}
				}
				else
				{
					AfxMessageBox("buff full"); //ť������ ũ�⸦ �ʰ��ϸ� ��� �޽��� ����
					PurgeComm(pComm->m_hComm,
						PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
				}
			}while(dwRead);
//			::PostMessage(g_hCommWnd, WM_COMM_READ, pComm->m_wPortID, 0 );//CSerialComDlg�� �����Ͱ� ���Դٴ� �޽����� ����
			::SendMessage(g_hCommWnd, WM_COMM_READ, pComm->m_wPortID, 0 );//CSerialComDlg�� �����Ͱ� ���Դٴ� �޽����� ����
		}
		Sleep(0);	// ���� �����͸� ȭ�鿡 ������ �ð��� ���� ����.
					// �����͸� �������� ������ cpu�������� 100%�� �Ǿ� ȭ�鿡 �ѷ��ִ� �۾��� �� �ȵǰ�. ��������� 
					// ť ���ۿ� �����Ͱ� ���̰� ��
   }
   
	CloseHandle( os.hEvent);

   //--> ������ ���ᰡ �ǰ���?
	CloseHandle(pComm->m_hThreadWatchComm);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;

}
//+ 2007.11.22 Add BY USY
int CCommThread::ClearPort()
{
	int nResult = 0;
	// ��Ʈ ����.
	nResult = PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	return nResult;
}

void CCommThread::SetComPort(int port,DWORD rate,BYTE bytesize,BYTE stop,BYTE parity)
{
   bPort=port;
   dwBaudRate=rate;
   bByteSize=bytesize;
   bStopBits=stop;
   bParity=parity;
}
