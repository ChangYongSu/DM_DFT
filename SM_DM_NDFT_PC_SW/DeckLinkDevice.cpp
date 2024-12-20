/* -LICENSE-START-
** Copyright (c) 2013 Blackmagic Design
**
** Permission is hereby granted, free of charge, to any person or organization
** obtaining a copy of the software and accompanying documentation covered by
** this license (the "Software") to use, reproduce, display, distribute,
** execute, and transmit the Software, and to prepare derivative works of the
** Software, and to permit third-parties to whom the Software is furnished to
** do so, all subject to the following:
** 
** The copyright notices in the Software and this entire statement, including
** the above license grant, this restriction and the following disclaimer,
** must be included in all copies of the Software, in whole or in part, and
** all derivative works of the Software, unless such copies or derivative
** works are solely in the form of machine-executable object code generated by
** a source language processor.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
** SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
** FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
** -LICENSE-END-
*/
#include "stdafx.h"
#include <comutil.h>
#include "DeckLinkDevice.h"

using namespace std;


DeckLinkDevice::DeckLinkDevice(CAcqVoltageSamples_IntClkDlg* ui, IDeckLink* device)
: m_uiDelegate(ui), m_deckLink(device),  m_deckLinkInput(NULL), m_supportsFormatDetection(false),
m_refCount(1), m_currentlyCapturing(false), m_applyDetectedInputMode(false)
{
	m_deckLink->AddRef();
}

DeckLinkDevice::~DeckLinkDevice()
{
	if (m_deckLinkInput != NULL)
	{
		m_deckLinkInput->Release();
		m_deckLinkInput = NULL;
	}

	while(! m_modeList.empty())
	{
		m_modeList.back()->Release();
		m_modeList.pop_back();
	}

	if (m_deckLink != NULL)
	{
		m_deckLink->Release();
		m_deckLink = NULL;
	}
}

HRESULT	STDMETHODCALLTYPE DeckLinkDevice::QueryInterface(REFIID iid, LPVOID *ppv)
{
	HRESULT			result = E_NOINTERFACE;

	if (ppv == NULL)
		return E_INVALIDARG;

	// Initialise the return result
	*ppv = NULL;

	// Obtain the IUnknown interface and compare it the provided REFIID
	if (iid == IID_IUnknown)
	{
		*ppv = this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkInputCallback)
	{
		*ppv = (IDeckLinkInputCallback*)this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkNotificationCallback)
	{
		*ppv = (IDeckLinkNotificationCallback*)this;
		AddRef();
		result = S_OK;
	}

	return result;
}

ULONG STDMETHODCALLTYPE DeckLinkDevice::AddRef(void)
{
	return InterlockedIncrement((LONG*)&m_refCount);
}

ULONG STDMETHODCALLTYPE DeckLinkDevice::Release(void)
{
	int		newRefValue;

	newRefValue = InterlockedDecrement((LONG*)&m_refCount);
	if (newRefValue == 0)
	{
		delete this;
		return 0;
	}

	return newRefValue;
}

bool		DeckLinkDevice::Init()
{
	IDeckLinkAttributes*            deckLinkAttributes = NULL;
	IDeckLinkDisplayModeIterator*   displayModeIterator = NULL;
	IDeckLinkDisplayMode*           displayMode = NULL;
	BSTR							deviceNameBSTR = NULL;

	// Get input interface
	if (m_deckLink->QueryInterface(IID_IDeckLinkInput, (void**) &m_deckLinkInput) != S_OK)
		return false;

	// Check if input mode detection is supported.
	if (m_deckLink->QueryInterface(IID_IDeckLinkAttributes, (void**) &deckLinkAttributes) == S_OK)
	{
		if (deckLinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &m_supportsFormatDetection) != S_OK)
			m_supportsFormatDetection = false;

		deckLinkAttributes->Release();
	}

	// Retrieve and cache mode list
	if (m_deckLinkInput->GetDisplayModeIterator(&displayModeIterator) == S_OK)
	{
		while (displayModeIterator->Next(&displayMode) == S_OK)
			m_modeList.push_back(displayMode);

		displayModeIterator->Release();
	}

	// Get device name
	if (m_deckLink->GetDisplayName(&deviceNameBSTR) == S_OK)
	{
		m_deviceName = CString(deviceNameBSTR);
		::SysFreeString(deviceNameBSTR);
	}
	else
	{
		m_deviceName = _T("DeckLink");
	}

	return true;
}

void		DeckLinkDevice::GetDisplayModeNames(vector<CString>& modeNames)
{
	unsigned int	modeIndex;
	BSTR			modeNameBstr;

	for (modeIndex = 0; modeIndex < m_modeList.size(); modeIndex++)
	{			
		if (m_modeList[modeIndex]->GetName(&modeNameBstr) == S_OK)
		{
			CString		modeName(modeNameBstr);
			modeNames.push_back(modeName);
			SysFreeString(modeNameBstr);
		}
		else 
		{
			modeNames.push_back(_T("Unknown mode"));
		}
	}
}

bool		DeckLinkDevice::StartCapture(unsigned int videoModeIndex, IDeckLinkScreenPreviewCallback* screenPreviewCallback, bool applyDetectedInputMode)
{
	BMDVideoInputFlags		videoInputFlags = bmdVideoInputFlagDefault;

	m_applyDetectedInputMode = applyDetectedInputMode;

	// Enable input video mode detection if the device supports it
	if (m_supportsFormatDetection == TRUE)
		videoInputFlags |=  bmdVideoInputEnableFormatDetection;

	// Get the IDeckLinkDisplayMode from the given index
	if ((videoModeIndex < 0) || (videoModeIndex >= m_modeList.size()))
	{
		m_uiDelegate->ShowErrorMessage(_T("An invalid display mode was selected."), _T("Error starting the capture"));
		return false;
	}

	// Set the screen preview
	m_deckLinkInput->SetScreenPreviewCallback(screenPreviewCallback);

	// Set capture callback
	m_deckLinkInput->SetCallback(this);

	// Set the video input mode
	if (m_deckLinkInput->EnableVideoInput(m_modeList[videoModeIndex]->GetDisplayMode(), bmdFormat8BitYUV, videoInputFlags) != S_OK)
	{
		m_uiDelegate->ShowErrorMessage(_T("This application was unable to select the chosen video mode. Perhaps, the selected device is currently in-use."), _T("Error starting the capture"));
		return false;
	}
	// Set the video input mode
	if (m_deckLinkInput->EnableAudioInput(bmdAudioSampleRate48kHz, bmdAudioSampleType16bitInteger, AUDIO_CHANNEL_NO) != S_OK)
	//if (m_deckLinkInput->EnableAudioInput(bmdAudioSampleRate48kHz, bmdAudioSampleType16bitInteger, 8) != S_OK)
	{
		m_uiDelegate->ShowErrorMessage(_T("Audio mode. Perhaps, the selected device is currently in-use."), _T("Error starting the Audio Capture"));
		return false;
	}
	// Start the capture
	if (m_deckLinkInput->StartStreams() != S_OK)
	{
		m_uiDelegate->ShowErrorMessage(_T("This application was unable to start the capture. Perhaps, the selected device is currently in-use."), _T("Error starting the capture"));
		return false;
	}

	m_currentlyCapturing = true;

	return true;
}

void		DeckLinkDevice::StopCapture()
{
	if (m_deckLinkInput != NULL)
	{
		// Stop the capture
		m_deckLinkInput->StopStreams();

		//
		m_deckLinkInput->SetScreenPreviewCallback(NULL);

		// Delete capture callback
		m_deckLinkInput->SetCallback(NULL);
	}

	m_currentlyCapturing = false;
}


HRESULT		DeckLinkDevice::VideoInputFormatChanged (/* in */ BMDVideoInputFormatChangedEvents notificationEvents, /* in */ IDeckLinkDisplayMode *newMode, /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags)
{	
	unsigned int	modeIndex = 0;
	BMDPixelFormat	pixelFormat = bmdFormat10BitYUV;

	// Restart capture with the new video mode if told to
	if (! m_applyDetectedInputMode)
		goto bail;

	if (detectedSignalFlags & bmdDetectedVideoInputRGB444)
		pixelFormat = bmdFormat10BitRGB;

	// Stop the capture
	m_deckLinkInput->StopStreams();

	// Set the video input mode
	if (m_deckLinkInput->EnableVideoInput(newMode->GetDisplayMode(), pixelFormat, bmdVideoInputEnableFormatDetection) != S_OK)
	{
		// Let the UI know we couldnt restart the capture with the detected input mode
		PostMessage(m_uiDelegate->GetSafeHwnd(), WM_ERROR_RESTARTING_CAPTURE_MESSAGE, 0, 0);
		goto bail;
	}

	// Start the capture
	if (m_deckLinkInput->StartStreams() != S_OK)
	{
		// Let the UI know we couldnt restart the capture with the detected input mode
		PostMessage(m_uiDelegate->GetSafeHwnd(), WM_ERROR_RESTARTING_CAPTURE_MESSAGE, 0, 0);
		goto bail;
	}		

	// Find the index of the new mode in the mode list so we can update the UI
	while (modeIndex < m_modeList.size()) {
		if (m_modeList[modeIndex]->GetDisplayMode() == newMode->GetDisplayMode())
		{
			PostMessage(m_uiDelegate->GetSafeHwnd(), WM_SELECT_VIDEO_MODE_MESSAGE, modeIndex, 0);
			break;
		}
		modeIndex++;
	}

bail:
	return S_OK;
}

BYTE gSumBYTE[51200];

HRESULT 	DeckLinkDevice::VideoInputFrameArrived (/* in */ IDeckLinkVideoInputFrame* videoFrame, /* in */ IDeckLinkAudioInputPacket* audioPacket)
{
	AncillaryDataStruct		ancillaryData;


	if (audioPacket)
	{
		
		long lSampleCount = 0;
		lSampleCount = audioPacket->GetSampleFrameCount();
		UINT _audioSamplesPerframe = (bmdAudioSampleType16bitInteger/8) * AUDIO_CHANNEL_NO * lSampleCount;
		BYTE* pBYTE = NULL;
		audioPacket->GetBytes((LPVOID*)&pBYTE);
	/*		if (m_pFileIn == NULL)
			{
				fopen_s(&m_pFileIn, "D:\\AudioIn.pcm", "wb+");
			}
		if (m_pFileIn)
		{
			fwrite(pBYTE, sizeof(BYTE), _audioSamplesPerframe, m_pFileIn);
		}*/
	/*	_cs.Lock();
		_AudioByteBuffQueue.push(pBYTE);
		_cs.UnLock();*/
		int n = 0;
		//audioPacket->GetSampleFrameCount();
		static UINT FrameCnt = 0;
		static UINT SumCount = 0;
		UINT SumCountOld = 0;
#if 1
		if (_audioSamplesPerframe >= 12800)
		{
			
			SumCountOld = SumCount;
			SumCount +=  _audioSamplesPerframe;
			FrameCnt++;
			if (SumCount < 51200)
			{
				//if()
				memcpy(&gSumBYTE[SumCountOld], pBYTE, _audioSamplesPerframe);
				//memcpy(&gSumBYTE[SumCountOld], pBYTE, 12800);
				if (SumCount >= 25600)
				{
					if (SumCount != 25600)
						TRACE("SumCount  :%d\n", SumCount);
					FrameCnt = 0;
					UINT BufCount[2];
					BufCount[0] = SumCount;
					BufCount[1] = FrameCnt;
					SendMessage(m_uiDelegate->GetSafeHwnd(), WM_REFRESH_INPUT_AUDIO_DATA_MESSAGE, (WPARAM)SumCount, (LPARAM)gSumBYTE);
					SumCount = 0;
				}
			}
		}
		else
		{
			FrameCnt = 0;
			SumCount = 0;
			SumCountOld = 0;
		}
#else
		if (_audioSamplesPerframe > 12800)
		{
			FrameCnt = 0;
			SumCount = 0;
			SumCountOld = 0;
		}
		else if (_audioSamplesPerframe == 12800)
		{			
			SumCountOld = SumCount;
			SumCount += _audioSamplesPerframe;
			
			memcpy(&gSumBYTE[SumCountOld], pBYTE, _audioSamplesPerframe);
			
			FrameCnt++;
			if (FrameCnt >= 2)
			{
				FrameCnt = 0;
				UINT BufCount[2];
				BufCount[0] = SumCount;
				BufCount[1] = FrameCnt;
				//SumCount += (FrameCnt << 16);
				//PostMessage(m_uiDelegate->GetSafeHwnd(), WM_REFRESH_INPUT_AUDIO_DATA_MESSAGE, (WPARAM)SumCount, (LPARAM)gSumBYTE);
				SendMessage(m_uiDelegate->GetSafeHwnd(), WM_REFRESH_INPUT_AUDIO_DATA_MESSAGE, (WPARAM)SumCount, (LPARAM)gSumBYTE);
				SumCount = 0;
			}
			
		}
		else
		{
			FrameCnt = 0;
			SumCount = 0;
			SumCountOld = 0;
		}
#endif

	}

	if (videoFrame == NULL)
		return S_OK;

	// Get the various timecodes and userbits attached to this frame
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeVITC, &ancillaryData.vitcF1Timecode, &ancillaryData.vitcF1UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeVITCField2, &ancillaryData.vitcF2Timecode, &ancillaryData.vitcF2UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188VITC1, &ancillaryData.rp188vitc1Timecode, &ancillaryData.rp188vitc1UserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188LTC, &ancillaryData.rp188ltcTimecode, &ancillaryData.rp188ltcUserBits);
	GetAncillaryDataFromFrame(videoFrame, bmdTimecodeRP188VITC2, &ancillaryData.rp188vitc2Timecode, &ancillaryData.rp188vitc2UserBits);

	m_uiDelegate->UpdateAncillaryData(ancillaryData);

//	long lHeight =  videoFrame->GetHeight();
//	long lWidth = videoFrame->GetWidth();
//	long lRowBytes = videoFrame->GetRowBytes();
//	//videoFrame->GetFrameCount();
//	/*short lBuffer[2048][2048];
//	videoFrame->GetBytes((void **)lBuffer);
//*/
//	BYTE ImageData[1920][1280 * 4];
//	//BYTE *pImageData;
//	//ImageData = new BYTE[1920][1280*3];
//videoFrame->GetBytes((void **)ImageData);
////memcpy(pImageData, ImageData, sizeof(pImageData));
//int lR, lG, lB, lK;
//
//for (int k = 0; k < 1080; k++)
//{
//
//	
//
//	for (int i = 0; i < 1920; i++)
//	{
//
//		lR = ImageData[k][i * 4];
//		lG = ImageData[k][i * 4 + 1];
//		lB = ImageData[k][i * 4 + 2];
//		lK = ImageData[k][i * 4 + 2];
//		//	videoFrame->GetBytes((void **)ImageData);	
//	}
//}

//delete ImageData;
	BMDPixelFormat lPort = videoFrame->GetPixelFormat();
	// Update the UI
	PostMessage(m_uiDelegate->GetSafeHwnd(), WM_REFRESH_INPUT_STREAM_DATA_MESSAGE, (videoFrame->GetFlags() & bmdFrameHasNoInputSource), 0);

	return S_OK;
}

void	DeckLinkDevice::GetAncillaryDataFromFrame(IDeckLinkVideoInputFrame* videoFrame, BMDTimecodeFormat timecodeFormat, CString* timecodeString, CString* userBitsString)
{
	IDeckLinkTimecode*		timecode = NULL;
	BSTR					timecodeBstr;
	BMDTimecodeUserBits		userBits = 0;

	if ((videoFrame != NULL) && (timecodeString != NULL) && (userBitsString != NULL)
		&& (videoFrame->GetTimecode(timecodeFormat, &timecode) == S_OK))
	{
		if (timecode->GetString(&timecodeBstr) == S_OK)
		{
			*timecodeString = timecodeBstr;
			SysFreeString(timecodeBstr);
		}
		else
		{
			*timecodeString = _T("");
		}

		timecode->GetTimecodeUserBits(&userBits);
		userBitsString->Format(_T("0x%08X"), userBits);

		timecode->Release();
	}
	else
	{
		*timecodeString = _T("");
		*userBitsString = _T("");
	}


}


DeckLinkDeviceDiscovery::DeckLinkDeviceDiscovery(CAcqVoltageSamples_IntClkDlg* delegate)
: m_uiDelegate(delegate), m_deckLinkDiscovery(NULL), m_refCount(1)
{
	if (CoCreateInstance(CLSID_CDeckLinkDiscovery, NULL, CLSCTX_ALL, IID_IDeckLinkDiscovery, (void**)&m_deckLinkDiscovery) != S_OK)
		m_deckLinkDiscovery = NULL;
}


DeckLinkDeviceDiscovery::~DeckLinkDeviceDiscovery()
{
	if (m_deckLinkDiscovery != NULL)
	{
		// Uninstall device arrival notifications and release discovery object
		m_deckLinkDiscovery->UninstallDeviceNotifications();
		m_deckLinkDiscovery->Release();
		m_deckLinkDiscovery = NULL;
	}
}

bool        DeckLinkDeviceDiscovery::Enable()
{
	HRESULT     result = E_FAIL;

	// Install device arrival notifications
	if (m_deckLinkDiscovery != NULL)
		result = m_deckLinkDiscovery->InstallDeviceNotifications(this);

	return result == S_OK;
}

void        DeckLinkDeviceDiscovery::Disable()
{
	// Uninstall device arrival notifications
	if (m_deckLinkDiscovery != NULL)
		m_deckLinkDiscovery->UninstallDeviceNotifications();
}

HRESULT     DeckLinkDeviceDiscovery::DeckLinkDeviceArrived (/* in */ IDeckLink* deckLink)
{
	deckLink->AddRef();
	// Update UI (add new device to menu) from main thread
	PostMessage(m_uiDelegate->GetSafeHwnd(), WM_ADD_DEVICE_MESSAGE, (WPARAM)deckLink, 0); 
	return S_OK;
}

HRESULT     DeckLinkDeviceDiscovery::DeckLinkDeviceRemoved (/* in */ IDeckLink* deckLink)
{
	// Update UI (remove device from menu) from main thread
	PostMessage(m_uiDelegate->GetSafeHwnd(), WM_REMOVE_DEVICE_MESSAGE, (WPARAM)deckLink, 0); 
	deckLink->Release();
	return S_OK;
}

HRESULT	STDMETHODCALLTYPE DeckLinkDeviceDiscovery::QueryInterface(REFIID iid, LPVOID *ppv)
{
	HRESULT			result = E_NOINTERFACE;

	if (ppv == NULL)
		return E_INVALIDARG;

	// Initialise the return result
	*ppv = NULL;

	// Obtain the IUnknown interface and compare it the provided REFIID
	if (iid == IID_IUnknown)
	{
		*ppv = this;
		AddRef();
		result = S_OK;
	}
	else if (iid == IID_IDeckLinkDeviceNotificationCallback)
	{
		*ppv = (IDeckLinkDeviceNotificationCallback*)this;
		AddRef();
		result = S_OK;
	}

	return result;
}

ULONG STDMETHODCALLTYPE DeckLinkDeviceDiscovery::AddRef(void)
{
	return InterlockedIncrement((LONG*)&m_refCount);
}

ULONG STDMETHODCALLTYPE DeckLinkDeviceDiscovery::Release(void)
{
	ULONG		newRefValue;

	newRefValue = InterlockedDecrement((LONG*)&m_refCount);
	if (newRefValue == 0)
	{
		delete this;
		return 0;
	}

	return newRefValue;
}

