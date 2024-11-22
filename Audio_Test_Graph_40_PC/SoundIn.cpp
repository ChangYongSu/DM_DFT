// SoundIn.cpp: implementation of the CSoundIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundIn.h"
// include callback class



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CSoundIn, CWinThread)

CSoundIn::CSoundIn()
{
	m_QueuedBuffers = 0;
	m_hRecord = NULL;
	m_bRecording = false;
	DataFromSoundIn = NULL;
	m_pOwner = NULL;
	CreateThread();
	m_bAutoDelete = false;

	m_uDeviceID = 0;
}

CSoundIn::~CSoundIn()
{
	if(m_bRecording)
		Stop();
	::PostQuitMessage(0);
}

BOOL CSoundIn::InitInstance()
{
	m_ThreadID = ::GetCurrentThreadId();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CSoundIn, CWinThread)
	//{{AFX_MSG_MAP(CSoundIn)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(MM_WIM_DATA, OnMM_WIM_DATA)
END_MESSAGE_MAP()

bool CSoundIn::Start(WAVEFORMATEX* format)
{
	MMRESULT mmReturn = 0;
	
	if(m_bRecording || DataFromSoundIn == NULL || m_pOwner == NULL)
	{
		// already recording!
		return FALSE;
	}
	else
	{
		if(format != NULL)
			m_Format = *format;

		// open wavein device
	//	mmReturn = ::waveInOpen(&m_hRecord, WAVE_MAPPER, &m_Format, m_ThreadID, NULL, CALLBACK_THREAD);
		mmReturn = ::waveInOpen(&m_hRecord, m_uDeviceID, &m_Format, m_ThreadID, NULL, CALLBACK_THREAD);

		if(mmReturn)
		{
			waveInErrorMsg(mmReturn, "in Start()");
			return FALSE;
		}
		else
		{
			// make several input buffers and add them to the input queue
			for(int i=0; i<3; i++)
			{
				AddInputBufferToQueue();
			}
			
			// start recording
			mmReturn = ::waveInStart(m_hRecord);
			if(mmReturn )
			{
				waveInErrorMsg(mmReturn, "in Start()");
				return FALSE;
			}
			m_bRecording = true;
		}
	}
	return TRUE;
}

void CSoundIn::Stop()
{
	MMRESULT mmReturn = MMSYSERR_NOERROR;
	if(!m_bRecording)
	{
	
		return;
	}
	else
	{
		m_bReadStopped = 0;
		m_bRecording = FALSE;
		for (int i = 0; i < 20; i++)
		{
			Sleep(50);
			if (m_bReadStopped)
				break;
		}

		mmReturn = ::waveInReset(m_hRecord);
		if(mmReturn)
		{
			waveInErrorMsg(mmReturn, "in Stop()");
			return;
		}
		else
		{
			Sleep(500);
			mmReturn = ::waveInClose(m_hRecord);
			if(mmReturn) waveInErrorMsg(mmReturn, "in Stop()");
		}
		if(m_QueuedBuffers != 0) TRACE("Still %d buffers in waveIn queue!", m_QueuedBuffers); //ErrorMsg("Still %d buffers in waveIn queue!", m_QueuedBuffers);
	}
}

void CSoundIn::OnMM_WIM_DATA(WPARAM parm1, LPARAM parm2)
{
	static UINT readcount = 0;
	MMRESULT mmReturn = 0;
	
	LPWAVEHDR pHdr = (LPWAVEHDR) parm2;

	mmReturn = ::waveInUnprepareHeader(m_hRecord, pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		//waveInErrorMsg(mmReturn, "in OnWIM_DATA()");
		TRACE("in OnWIM_DATA() %4d\n", mmReturn);
		return;
	}
	readcount++;
	//TRACE("WIM_DATA %4d, %4d\n", pHdr->dwBytesRecorded,readcount );
	
	if(m_bRecording)
	{
		CBuffer buf(pHdr->lpData, pHdr->dwBufferLength);

		// virtual processing function supplyed by user
		DataFromSoundIn(&buf, m_pOwner);

		if (m_bRecording)
		{


			try
			{


				// reuse the buffer:
				// prepare it again
				mmReturn = ::waveInPrepareHeader(m_hRecord, pHdr, sizeof(WAVEHDR));
				if (mmReturn)
				{
					TRACE("in OnWIM_DATA() %4d\n", mmReturn); //waveInErrorMsg(mmReturn, "in OnWIM_DATA()");
				}
				else // no error
				{
					// add the input buffer to the queue again
					mmReturn = ::waveInAddBuffer(m_hRecord, pHdr, sizeof(WAVEHDR));
					if (mmReturn) TRACE("in OnWIM_DATA() %4d\n", mmReturn); //waveInErrorMsg(mmReturn, "in OnWIM_DATA()");
					else return;  // no error
				}
			}
			catch (int e)
			{
				TRACE("in OnWIM_DATA()Error %4d\n", e);
			}
		}
		else
		{
			m_bReadStopped = 1;
		}
	}
	else
	{
		m_bReadStopped = 1;
	}

	// we are closing the waveIn handle, 
	// all data must be deleted
	// this buffer was allocated in Start()
	delete pHdr->lpData;
	delete pHdr;
	m_QueuedBuffers--;
}

int CSoundIn::AddInputBufferToQueue()
{
	MMRESULT mmReturn = 0;
	
	// create the header
	LPWAVEHDR pHdr = new WAVEHDR;
	if(pHdr == NULL) return NULL;
	ZeroMemory(pHdr, sizeof(WAVEHDR));

	// new a buffer
	CBuffer buf(m_Format.nBlockAlign*m_BufferSize, false);
	pHdr->lpData = buf.ptr.c;
	pHdr->dwBufferLength = buf.ByteLen;
	
	// prepare it
	mmReturn = ::waveInPrepareHeader(m_hRecord,pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		waveInErrorMsg(mmReturn, "in AddInputBufferToQueue()");
		return m_QueuedBuffers;
	}

	// add the input buffer to the queue
	mmReturn = ::waveInAddBuffer(m_hRecord, pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		waveInErrorMsg(mmReturn, "in AddInputBufferToQueue()");
		return m_QueuedBuffers;
	}

	// no error
	// increment the number of waiting buffers
	return m_QueuedBuffers++;
}

void CSoundIn::waveInErrorMsg(MMRESULT result, LPCTSTR addstr)
{
	// say error message
	char errorbuffer[100];
	waveInGetErrorText(result, errorbuffer,100);
	ErrorMsg("WAVEIN:%x:%s %s", result, errorbuffer, addstr);
}
