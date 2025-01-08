
#ifndef	__COMMTHREAD_H_
#define __COMMTHREAD_H_


//---------------------------- ��� ���� --------------------------//
#define	BUFF_SIZE		8192
#define	WM_COMM_READ	(WM_USER+2)		

//#define	ASCII_LF		0x0a
//#define	ASCII_CR		0x0d
#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13

// Queue Ŭ���� ���� //
class	CQueue
{
public:
	BYTE	buff[BUFF_SIZE];
	int		m_iHead, m_iTail;
	CQueue();
	void	Clear();
	int		GetSize();
	BOOL	PutByte(BYTE b);		// 1 byte �ֱ�
	BOOL	GetByte(BYTE *pb);		// 1 byte ������
};


//	��� Ŭ����	CCommThread 

// ��Ʈ ���� : OpenPort("COM1", CBR_9600);
// ��Ʈ���� �б� :
//   ��Ʈ�� �� �Ŀ� ��Ʈ�� �ڷᰡ �����ϸ� WM_COMM_READ �޽����� ���� 
//   �����쿡 ���޵ȴ�. ON_MESSAGE ��ũ�θ� �̿�, �Լ��� �����ϰ�
//   m_ReadData String�� ����� �����͸� �̿� �б�
// ��Ʈ�� ���� : WriteComm(buff, 30)�� ���� ���ۿ� �� ũ�⸦ �ǳ׸� �ȴ�.

class	CCommThread
{
public:
	CCommThread( );
	//--------- ȯ�� ���� -----------------------------------------//
	HANDLE		m_hComm;				// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;			// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bConnected;			// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead, m_osWrite;	// ��Ʈ ���� Overlapped structure
	HANDLE		m_hThreadWatchComm;		// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;				// WM_COMM_READ�� �Բ� ������ �μ�.
	BYTE		abIn[2049] ;//����Ʈ���� ������ ����Ÿ

	//--------- ��� ���� -----------------------------------------//
	CQueue	m_QueueRead;

	//--------- �ܺ� ��� �Լ� ------------------------------------//
	//+ 2007.9.28 Mod BY USY
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam, BYTE bByteSize =8, BYTE bParity=0, BYTE bStopBits=0, BOOL bWatch = FALSE);

//	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam);
	//-
	void	ClosePort();
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

	//--------- ���� ��� �Լ� ------------------------------------//
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

	//+ 2007.11.22 Add BY USY
	int		ClearPort();
	//-
	//+ 2008.05.30 Add BY PSH
//	HANDLE	   hReadEnd;

	void SetComPort(int port,DWORD rate,BYTE bytesize,BYTE stop,BYTE parity);
	
	void SetReadData(LPTSTR data);

// Attributes
public:
   BYTE        bPort;
   BOOL         fXonXoff;
   BYTE        bByteSize, bFlowCtrl, bParity, bStopBits ;
   DWORD       dwBaudRate ;
   HANDLE hWatchThread;
//   HWND        hTermWnd ;
   DWORD       dwThreadID ;
   OVERLAPPED  osWrite, osRead ;

public:
	virtual ~CCommThread();

};

// Thread�� ����� �Լ� 
DWORD	ThreadWatchComm(CCommThread* pComm);


#endif	// __COMMTHREAD_H__