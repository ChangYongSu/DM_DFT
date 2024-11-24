// COptEtcPage.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptEtcPage.h"

extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg;
extern CAcqVoltageSamples_IntClkDlg* g_pView;
// COptEtcPage
//IMPLEMENT_DYNCREATE(COptEtcPage, CPropertyPage)
//
//COptEtcPage::COptEtcPage() : CPropertyPage(COptEtcPage::IDD)
//{
//	//{{AFX_DATA_INIT(COptGrabberPage)
//
//	//}}AFX_DATA_INIT
//}
//
//COptEtcPage::~COptEtcPage()
//{
//}
//
//void COptEtcPage::DoDataExchange(CDataExchange* pDX)
//{
//	CPropertyPage::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(COptEtcPage)
//
//	//}}AFX_DATA_MAP
//}
//
//
//BEGIN_MESSAGE_MAP(COptEtcPage, CPropertyPage)
//	//{{AFX_MSG_MAP(COptEtcPage)
//
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(COptEtcPage, CPropertyPage)

COptEtcPage::COptEtcPage() : CPropertyPage(COptEtcPage::IDD)
{
	//{{AFX_DATA_INIT(COptGrabberPage)

	//}}AFX_DATA_INIT
}

COptEtcPage::~COptEtcPage()
{
}

void COptEtcPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptEtcPage)
	DDX_Text(pDX, IDC_EDIT_FREQ15, m_EditFreq[0]);
	DDX_Text(pDX, IDC_EDIT_FREQ2,  m_EditFreq[1]);
	DDX_Text(pDX, IDC_EDIT_FREQ3,  m_EditFreq[2]);
	DDX_Text(pDX, IDC_EDIT_FREQ4,  m_EditFreq[3]);
	DDX_Text(pDX, IDC_EDIT_FREQ5,  m_EditFreq[4]);
	DDX_Text(pDX, IDC_EDIT_FREQ6,  m_EditFreq[5]);
	DDX_Text(pDX, IDC_EDIT_FREQ7,  m_EditFreq[6]);
	DDX_Text(pDX, IDC_EDIT_FREQ8,  m_EditFreq[7]);
	DDX_Text(pDX, IDC_EDIT_FREQ9,  m_EditFreq[8]);
	DDX_Text(pDX, IDC_EDIT_FREQ10, m_EditFreq[9]);
	DDX_Text(pDX, IDC_EDIT_FREQ11, m_EditFreq[10]);
	DDX_Text(pDX, IDC_EDIT_FREQ12, m_EditFreq[11]);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptEtcPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptEtcPage)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FREQ_SET, &COptEtcPage::OnBnClickedButtonFreqSet)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_READ, &COptEtcPage::OnBnClickedButtonFreqRead)
	//ON_BN_CLICKED(IDC_BUTTON_MIC1_ON, &COptEtcPage::OnBnClickedButtonMic1On)
	//ON_BN_CLICKED(IDC_BUTTON_MIC2_ON, &COptEtcPage::OnBnClickedButtonMic2On)
	ON_BN_CLICKED(IDC_BUTTON_FREQ1, &COptEtcPage::OnBnClickedButtonFreq1)
	ON_BN_CLICKED(IDC_BUTTON_FREQ2, &COptEtcPage::OnBnClickedButtonFreq2)
	ON_BN_CLICKED(IDC_BUTTON_FREQ3, &COptEtcPage::OnBnClickedButtonFreq3)
	ON_BN_CLICKED(IDC_BUTTON_FREQ4, &COptEtcPage::OnBnClickedButtonFreq4)
	ON_BN_CLICKED(IDC_BUTTON_FREQ5, &COptEtcPage::OnBnClickedButtonFreq5)
	ON_BN_CLICKED(IDC_BUTTON_FREQ6, &COptEtcPage::OnBnClickedButtonFreq6)
	ON_BN_CLICKED(IDC_BUTTON_FREQ7, &COptEtcPage::OnBnClickedButtonFreq7)
	ON_BN_CLICKED(IDC_BUTTON_FREQ8, &COptEtcPage::OnBnClickedButtonFreq8)
	ON_BN_CLICKED(IDC_BUTTON_FREQ9, &COptEtcPage::OnBnClickedButtonFreq9)
	ON_BN_CLICKED(IDC_BUTTON_FREQ10, &COptEtcPage::OnBnClickedButtonFreq10)
	ON_BN_CLICKED(IDC_BUTTON_FREQ11, &COptEtcPage::OnBnClickedButtonFreq11)
	ON_BN_CLICKED(IDC_BUTTON_FREQ12, &COptEtcPage::OnBnClickedButtonFreq12)

	ON_BN_CLICKED(IDC_BUTTON_FREQ_SET, &COptEtcPage::OnBnClickedButtonFreqSet)
	ON_BN_CLICKED(IDC_BUTTON_FREQ_READ, &COptEtcPage::OnBnClickedButtonFreqRead)

	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COptEtcPage::OnBnClickedButtonSave)
END_MESSAGE_MAP()

BOOL COptEtcPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString sTmp;
	//   
	   //CString lStrComName[18] = {
	   //	_T("HDMI_R"),_T("HDMI_L"),
	   //	_T("OPTICAL_R"),_T("OPTICAL_L"),
	   //	_T("SPEAKER_1R"),_T("SPEAKER_1L"),
	   //	_T("SPEAKER_2R"),_T("SPEAKER_2L"),
	   //	_T("SPEAKER_3R"),_T("SPEAKER_3L"),
	   //	_T("SPEAKER_4R"),_T("SPEAKER_4L"),
	   //	_T("AUX_R"),_T("AUX_L"),
	   //	_T("PORTABLE_R"),_T("PORTABLE_L"), 
	   //	_T("COAX_R"),_T("COAX_L")};
	//   // Return TRUE unless you set the focus to a control.




	g_pView->m_ComAck = 0;

	for (int i = 0; i < 12; i++)
	{
		m_EditFreq[i] = CurrentSet->nAudioGenFreq[i];
		if (m_EditFreq[i] == 0)
			m_EditFreq[i] = 1000;
	}
	



	UpdateData(FALSE);

	SetTimer(1, 30, NULL);

	OnBnClickedButtonFreqRead();


	return TRUE;
}



void COptEtcPage::OnBnClickedButtonFreq1()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(0, m_EditFreq[0]);
}

void COptEtcPage::OnBnClickedButtonFreq2()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(1, m_EditFreq[1]);
}

void COptEtcPage::OnBnClickedButtonFreq3()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(2, m_EditFreq[2]);
}

void COptEtcPage::OnBnClickedButtonFreq4()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(3, m_EditFreq[3]);
}

void COptEtcPage::OnBnClickedButtonFreq5()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(6, m_EditFreq[4]);
}

void COptEtcPage::OnBnClickedButtonFreq6()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(7, m_EditFreq[5]);
}

void COptEtcPage::OnBnClickedButtonFreq7()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(8, m_EditFreq[6]);
}

void COptEtcPage::OnBnClickedButtonFreq8()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(9, m_EditFreq[7]);
}

void COptEtcPage::OnBnClickedButtonFreq9()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(10, m_EditFreq[8]);
}

void COptEtcPage::OnBnClickedButtonFreq10()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(11, m_EditFreq[9]);
}

void COptEtcPage::OnBnClickedButtonFreq11()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(12, m_EditFreq[10]);
}

void COptEtcPage::OnBnClickedButtonFreq12()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.

	//UINT m_EditFreq1;
	UpdateData();

	g_pView->SetFreqSend(13, m_EditFreq[11]);
}

void COptEtcPage::OnBnClickedButtonFreqSet()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
	BYTE lbuf[128];
	int lcnt;
	//UINT m_EditFreq1;
	UpdateData();

	lbuf[0] = 0x02;

	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFSET%03d%03d%03d%03d000000%03d%03d%03d%03d%03d%03d%03d%03d",
		m_EditFreq[0] / 10,
		m_EditFreq[1] / 10,
		m_EditFreq[2 ]/ 10,
		m_EditFreq[3 ]/ 10,
		m_EditFreq[4 ]/ 10,
		m_EditFreq[5 ]/ 10,
		m_EditFreq[6 ]/ 10,
		m_EditFreq[7 ]/ 10,
		m_EditFreq[8 ]/ 10,
		m_EditFreq[9 ]/ 10,
		m_EditFreq[10] / 10,
		m_EditFreq[11] / 10
	);

	lbuf[48] = 0x03;
	lbuf[49] = 0x0d;
	lbuf[50] = 0x0a;
	lbuf[51] = 0;
	g_pView->SendData(lbuf, 51, COM_ID_AUDIO_PORT);//ComSend(lbuf, 39);

	
	g_pView->m_ComAck = COM_ACK_WAIT;

}

void COptEtcPage::OnBnClickedButtonFreqRead()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
	BYTE lbuf[128];
	int lcnt;
	//UINT m_EditFreq1;

	lbuf[0] = 0x02;

	//sprintf((char *)&lbuf[1], "CFREQ%02d%03d", 
	sprintf((char *)&lbuf[1], "CFREQREAD");

	lbuf[10] = 0x03;
	lbuf[11] = 0x0d;
	lbuf[12] = 0x0a;
	//ReceiveData[18] == 0x03) && (ReceiveData[19] == 0x0d) && (ReceiveData[20] == 0x0a
	g_pView->SendData(lbuf, 13, COM_ID_AUDIO_PORT);//ComSend(lbuf, 13);

//	m_TESTPAGE_COM_PROCESS = COM_MODE_WAIT_ACK;
	g_pView->m_ComAck = COM_ACK_WAIT;
//	m_WaitCnt = 0;
//	m_ResendCnt = 0;
//	MessageDisplay(2, "Frequency Read!");
}

//void COptEtcPage::OnBnClickedButtonMic1On()
//{
//	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
//	m_pMainDlg->SetFreqSend(4, 1);
//}
//
//void COptEtcPage::OnBnClickedButtonMic2On()
//{
//	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
//	m_pMainDlg->SetFreqSend(5, 1);
//}



void COptEtcPage::OnBnClickedButtonSave()
{
	// TODO: 

	UpdateData();
	for (int i = 0; i < 12; i++)
	{
		CurrentSet->nAudioGenFreq[i] = m_EditFreq[i];
	}


	if (FileExists(CurrentSet->sModelIni))
	{
		SaveModelIniFile(CurrentSet->sModelIni);
	}
	
	g_pView->SaveRegistrySetting();

}
