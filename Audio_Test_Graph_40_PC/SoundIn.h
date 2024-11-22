// SoundIn.h: interface for the CSoundIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDIN_H__DFF637AC_D133_4419_B4CA_241DFAC75789__INCLUDED_)
#define AFX_SOUNDIN_H__DFF637AC_D133_4419_B4CA_241DFAC75789__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//
//#include <complex>
//#include <valarray>
//#include <math.h>
//
//const double PI = 3.141592653589793238460 ;
//
//
//
//typedef complex<double> Complex;
//typedef valarray<Complex> CArray;


#include "soundbase.h"

				// CWinThread must be before CSoundBase -> and it's very difficult to debug!
				// Trust me!   Thomas.Holme@openmpeg4.org
class CSoundIn : public CWinThread, public CSoundBase
{
	DECLARE_DYNCREATE(CSoundIn)

public:
	CSoundIn();
	virtual ~CSoundIn();


	// pointer to callback function
	void (*DataFromSoundIn)(CBuffer* buffer, void* Owner);
	void* m_pOwner;

	virtual void Stop();
	virtual bool Start(WAVEFORMATEX* format = NULL);
	static void waveInErrorMsg(MMRESULT result, LPCTSTR addstr);


	afx_msg void OnMM_WIM_DATA(WPARAM parm1, LPARAM parm2);
	DECLARE_MESSAGE_MAP()

public:
	UINT         m_uDeviceID;

protected:
	BOOL InitInstance();
	int AddInputBufferToQueue();

protected:
	bool m_bRecording;
	bool m_bReadStopped;
	HWAVEIN m_hRecord;
	int m_QueuedBuffers;
	DWORD m_ThreadID;

};

#endif // !defined(AFX_SOUNDIN_H__DFF637AC_D133_4419_B4CA_241DFAC75789__INCLUDED_)
