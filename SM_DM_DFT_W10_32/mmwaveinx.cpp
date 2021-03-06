// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "mmwaveinx.h"

// Dispatch interfaces referenced by this interface
#include "mmdspcomponentx.h"

/////////////////////////////////////////////////////////////////////////////
// CMMWaveInX

IMPLEMENT_DYNCREATE(CMMWaveInX, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CMMWaveInX properties

/////////////////////////////////////////////////////////////////////////////
// CMMWaveInX operations

long CMMWaveInX::GetNumdevs()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMMWaveInX::GetDriverVersion()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMMWaveInX::GetBytesRecorded()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMMWaveInX::GetPosition()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMMWaveInX::GetHandle()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMMWaveInX::GetBufferSize()
{
	long result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetBufferSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetCallBackMode()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetCallBackMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetDeviceID()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetDeviceID(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetNumBuffers()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetNumBuffers(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetMode()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetBitLength()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetBitLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetSampleRate()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetSampleRate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CMMWaveInX::GetProductName()
{
	CString result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetProductName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CMMWaveInX::GetTimeFormat()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetTimeFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetMaxRecordTime()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetMaxRecordTime(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CMMWaveInX::Open()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMMWaveInX::Close()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMMWaveInX::Start()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMMWaveInX::Pause()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMMWaveInX::Restart()
{
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMMWaveInX::Stop()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CMMWaveInX::GetState()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CMMWaveInX::GetDeviceName(long DeviceID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		DeviceID);
	return result;
}

BOOL CMMWaveInX::DeviceFullDuplex(long DeviceID, long pwfx)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		DeviceID, pwfx);
	return result;
}

BOOL CMMWaveInX::DeviceReady(long DeviceID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		DeviceID);
	return result;
}

long CMMWaveInX::GetPriority()
{
	long result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMMWaveInX::GetPWaveFormat()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetPWaveFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CMMDspComponentX CMMWaveInX::GetOutput()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CMMDspComponentX(pDispatch);
}

void CMMWaveInX::SetOutput(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CMMWaveInX::GetOutputX()
{
	CString result;
	InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMMWaveInX::SetOutputX(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void CMMWaveInX::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
