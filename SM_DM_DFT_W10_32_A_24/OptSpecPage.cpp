// OptSpecPage.cpp : implementation file
//

#include "stdafx.h"
#include "datsys.h"
#include "OptSpecPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "Global.h"
#include "Step.h"
#include <TVCommCtrl.h>

extern _InputSource	InputDefined[];

extern  CTVCommCtrl	TVCommCtrl;

/////////////////////////////////////////////////////////////////////////////
// COptSpecPage property page

IMPLEMENT_DYNCREATE(COptSpecPage, CPropertyPage)

COptSpecPage::COptSpecPage() : CPropertyPage(COptSpecPage::IDD)
{
	//{{AFX_DATA_INIT(COptSpecPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptSpecPage::~COptSpecPage()
{
}

void COptSpecPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptSpecPage)
	//	DDX_Control(pDX, IDC_AUDIO_SPEC_GRID, m_ctrlVerSpecGrid);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_AUDIO_SPEC_LIST, m_ctrlAudioVerSpecList);
	DDX_Control(pDX, IDC_EDIT_OPT_VERSION, m_cEditOptVersion);
}


BEGIN_MESSAGE_MAP(COptSpecPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptSpecPage)
	ON_BN_CLICKED(IDC_BTN_OPT_APPLY, OnBtnOptApply)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_AUDIO_SPEC_LIST, &COptSpecPage::OnNMDblclkListAudioSpecList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_AUDIO_SPEC_LIST, &COptSpecPage::OnNMClickListAudioSpecList)
	ON_EN_CHANGE(IDC_EDIT_OPT_VERSION, &COptSpecPage::OnEnChangeEditOptVersion)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_VERSION, &COptSpecPage::OnBnClickedButtonUpdateVersion)
	ON_WM_TIMER()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &COptSpecPage::OnHdnItemclickListAudioSpecList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptSpecPage message handlers
//0x4C	Woofer Rx Version
//0x4D	Rear Kit Rx Version
//0x4E	Rear SPK L Version
//0x4F	Rear SPK R Version
void COptSpecPage::InitVerSpecGrid()
{
	CString sTmp;
	char *sHeader[] = {"BE Ver.", "FE Ver.", "Micom Ver.", "DSP Ver.", "Sub DSP Ver.", "EQ Ver.", "MEQ Ver.", "Touch Ver.", "Demo Ver.", "DJ Sound Ver.", "WirelessTx Ver.", "WirelessRx Ver.",
		"Woofer Rx Version","Rear Kit Rx Version","Rear SPK L Version","Rear SPK R Version", "BT Version", "HDMI Version","Checksum"};
	m_ctrlAudioVerSpecList.DeleteAllItems();	
//	m_ctrlAudioVerSpecList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_ctrlAudioVerSpecList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_ctrlAudioVerSpecList.InsertColumn(0, "ITEM", LVCFMT_CENTER, 110);
	m_ctrlAudioVerSpecList.InsertColumn(1, "VERSION", LVCFMT_CENTER, 260);

	for(int nRow = 0; nRow < 19 ; nRow++)
	{
		m_ctrlAudioVerSpecList.InsertItem(nRow, sHeader[nRow]);
	}
	
	m_ctrlAudioVerSpecList.Invalidate();
}


void COptSpecPage::UpdateVerSpecGrid()
{	
	m_ctrlAudioVerSpecList.SetItem(0, 1, LVIF_TEXT,CurrentSet->sBE_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(1, 1, LVIF_TEXT,CurrentSet->sFE_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(2, 1, LVIF_TEXT,CurrentSet->sMicom_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(3, 1, LVIF_TEXT,CurrentSet->sDSP_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(4, 1, LVIF_TEXT,CurrentSet->sSubDSP_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(5, 1, LVIF_TEXT,CurrentSet->sEQ_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(6, 1, LVIF_TEXT,CurrentSet->sMEQ_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(7, 1, LVIF_TEXT,CurrentSet->sTouch_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(8, 1, LVIF_TEXT,CurrentSet->sDemo_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(9, 1, LVIF_TEXT,CurrentSet->sDJSound_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(10, 1,LVIF_TEXT, CurrentSet->sWirelessTx_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(11, 1,LVIF_TEXT, CurrentSet->sWirelessRx_Version, NULL, NULL, NULL, NULL);

	m_ctrlAudioVerSpecList.SetItem(12, 1,LVIF_TEXT, CurrentSet->sWoofer_Rx_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(13, 1,LVIF_TEXT, CurrentSet->sRear_Kit_Rx_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(14, 1,LVIF_TEXT, CurrentSet->sRear_SPK_L_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(15, 1,LVIF_TEXT, CurrentSet->sRear_SPK_R_Version, NULL, NULL, NULL, NULL);

	m_ctrlAudioVerSpecList.SetItem(16, 1, LVIF_TEXT, CurrentSet->sBT_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(17, 1, LVIF_TEXT, CurrentSet->sHDMI_Version, NULL, NULL, NULL, NULL);
	m_ctrlAudioVerSpecList.SetItem(18, 1, LVIF_TEXT, CurrentSet->sChecksum, NULL, NULL, NULL, NULL);
	for (int i = 0; i < 19; i++)
	{
		if (CurrentSet->bVerChecked[i] == 1)
		{		
			m_ctrlAudioVerSpecList.SetCheck(i, 1);
		}
		else
		{
			m_ctrlAudioVerSpecList.SetCheck(i, 0);
		}
	}
	m_ctrlAudioVerSpecList.Invalidate();
}


BOOL COptSpecPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	GetDlgItem(IDC_EDIT_OPT_VERSION)->SetWindowPos(NULL, 2500, 20, 150, 23, SWP_ASYNCWINDOWPOS);
	
	// TODO: Add extra initialization here
	InitVerSpecGrid();
	UpdateVerSpecGrid();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(COptSpecPage, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(COptSpecPage)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void COptSpecPage::OnBtnOptApply() 
{
	// TODO: Add your control notification handler code here
	CString sTemp;

	for (int i = 0; i < 19; i++)
	{
		if (m_ctrlAudioVerSpecList.GetCheck(i) == 1)
		{
			CurrentSet->bVerChecked[i] = 1;
		}
		else
		{
			CurrentSet->bVerChecked[i] = 0;
		}
	}

	for (int i = 0; i < 19; i++)
	{
		if (m_ctrlAudioVerSpecList.GetCheck(i) == 1)
		{
			sTemp  = m_ctrlAudioVerSpecList.GetItemText(i, 1);
			if ((sTemp.Find("WAIT") > 0) || (sTemp.GetLength() < 2))
			{
				MessageBox("Check Version Value!!");
				return;
			}
		}		
	}



	CurrentSet->sBE_Version			= m_ctrlAudioVerSpecList.GetItemText(0, 1);  /// m_ctrlVerSpecGrid.GetTextMatrix(1, 1);
	CurrentSet->sFE_Version			= m_ctrlAudioVerSpecList.GetItemText(1, 1);
	CurrentSet->sMicom_Version		= m_ctrlAudioVerSpecList.GetItemText(2, 1);
	CurrentSet->sDSP_Version		= m_ctrlAudioVerSpecList.GetItemText(3, 1);
	CurrentSet->sSubDSP_Version		= m_ctrlAudioVerSpecList.GetItemText(4, 1);
	CurrentSet->sEQ_Version			= m_ctrlAudioVerSpecList.GetItemText(5, 1);
	CurrentSet->sMEQ_Version		= m_ctrlAudioVerSpecList.GetItemText(6, 1);
	CurrentSet->sTouch_Version		= m_ctrlAudioVerSpecList.GetItemText(7, 1);
	CurrentSet->sDemo_Version		= m_ctrlAudioVerSpecList.GetItemText(8, 1);
	CurrentSet->sDJSound_Version	= m_ctrlAudioVerSpecList.GetItemText(9,  1);
	CurrentSet->sWirelessTx_Version	= m_ctrlAudioVerSpecList.GetItemText(10, 1);
	CurrentSet->sWirelessRx_Version = m_ctrlAudioVerSpecList.GetItemText(11, 1);
	CurrentSet->sWoofer_Rx_Version  = m_ctrlAudioVerSpecList.GetItemText(12, 1);
	CurrentSet->sRear_Kit_Rx_Version = m_ctrlAudioVerSpecList.GetItemText(13, 1);
	CurrentSet->sRear_SPK_L_Version = m_ctrlAudioVerSpecList.GetItemText(14, 1);
	CurrentSet->sRear_SPK_R_Version = m_ctrlAudioVerSpecList.GetItemText(15, 1);
	CurrentSet->sBT_Version = m_ctrlAudioVerSpecList.GetItemText(16, 1);
	CurrentSet->sHDMI_Version = m_ctrlAudioVerSpecList.GetItemText(17, 1);
	CurrentSet->sChecksum = m_ctrlAudioVerSpecList.GetItemText(18, 1);

	
}

void COptSpecPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	OnBtnOptApply();
	
	CPropertyPage::OnOK();
}

//+add kwmoon 080904
void COptSpecPage::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	//+add kwmoon 080910
	if((CurrentSet->nAuthority != AUTHORITY_DEV) && (CurrentSet->nAuthority != AUTHORITY_ADMIN))
	{
		CString sTmp = _T("");
		sTmp.LoadString(ERROR_ADMIN_LOGIN);
		AfxMessageBox(sTmp); return;
	}

	OnBtnOptApply();

	SaveModelIniFile(CurrentSet->sModelIni);
}

BOOL COptSpecPage::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
		{
			if (m_EditMode == 1)
			{
				if (pMsg->wParam != VK_SPACE)
				{
					m_EditMode = 0;
					//m_SelectItem = nItem;
					//m_SelectShell = nShell;
					CString strtemp;
					GetDlgItemText(IDC_EDIT_OPT_VERSION, strtemp);
					m_ctrlAudioVerSpecList.SetItemText(m_SelectItem, m_SelectShell, strtemp);
					GetDlgItem(IDC_EDIT_OPT_VERSION)->SetWindowPos(NULL, 2500, 20, 150, 23, SWP_ASYNCWINDOWPOS);
					return TRUE;
				}

			}
			return TRUE;
		}
           
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}


void COptSpecPage::OnNMDblclkListAudioSpecList(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nItem = pNMItemActivate->iItem;
	int nShell = pNMItemActivate->iSubItem;


	m_EditMode = 0;
	if (nShell == 1)//m_cEditPinName
	{

		if (nItem < m_ctrlAudioVerSpecList.GetItemCount())
		{

			RECT lMainRect, lRect;
			this->GetWindowRect(&lMainRect);

			m_ctrlAudioVerSpecList.GetWindowRect(&lRect);

			int x = lRect.left - lMainRect.left;
			int y = lRect.top - lMainRect.top;

			//m_cEditPinName.SetWindowPos(this, lRect.left+70, lRect.top+nItem*30, 70, 30, SWP_ASYNCWINDOWPOS);
			GetDlgItem(IDC_EDIT_OPT_VERSION)->SetWindowPos(NULL, x + 120, y + nItem * 17 + 20, 250, 20, SWP_ASYNCWINDOWPOS);
			//	m_cEditPinName.SetRect(&lRect);
			SetDlgItemText(IDC_EDIT_OPT_VERSION, m_ctrlAudioVerSpecList.GetItemText(nItem, 1));//CurrentSet->sBE_Version			= m_ctrlAudioVerSpecList.GetItemText(0, 1);  

			m_cEditOptVersion.SetFocus();
			//m_cEditOptVersion.SetSel(0);
			m_SelectItem = nItem;
			m_SelectShell = nShell;

			m_EditMode = 1;
		}

	}
	
	*pResult = 0;
}


void COptSpecPage::OnNMClickListAudioSpecList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int nItem = pNMItemActivate->iItem;
	int nShell = pNMItemActivate->iSubItem;
	if (m_EditMode == 1)
	{
		if ((m_SelectItem != nItem) || (m_SelectShell != nShell))
		{
			CString strtemp;
			GetDlgItemText(IDC_EDIT_OPT_VERSION, strtemp);
			if (strtemp.GetLength() > 0)
			{
				m_ctrlAudioVerSpecList.SetItemText(m_SelectItem, m_SelectShell, strtemp);
			}
			GetDlgItem(IDC_EDIT_OPT_VERSION)->SetWindowPos(NULL, 2500, 20, 250, 20, SWP_ASYNCWINDOWPOS);
			m_EditMode = 0;
		}
	}
}


void COptSpecPage::OnEnChangeEditOptVersion()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CPropertyPage::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_EditMode == 1)
	{
		CString strtemp;
		GetDlgItemText(IDC_EDIT_OPT_VERSION, strtemp);

		m_ctrlAudioVerSpecList.SetItemText(m_SelectItem, m_SelectShell, strtemp);

	
	}
}


void COptSpecPage::OnBnClickedButtonUpdateVersion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lCheckFlag = 0;
	CString sTempVersion;
	for (int i = 0; i < 19; i++)
	{
	lCheckFlag = m_ctrlAudioVerSpecList.GetCheck(i);
		if (lCheckFlag == 1)
		{
			m_ctrlAudioVerSpecList.SetItemText(i, 1, "WAIT....");
		}
		else
		{
			m_ctrlAudioVerSpecList.SetItemText(i, 1, "");
		}
			
	}
	

	SetTimer(1, 20, NULL);
	TVCommCtrl.m_ReadComplete = 0;
	TVCommCtrl.m_bCheckReadVersion = 1;
	TVCommCtrl.m_ReadCheckNo = 0;
	lCheckFlag = m_ctrlAudioVerSpecList.GetCheck(TVCommCtrl.m_ReadCheckNo);
	if (lCheckFlag == 1)
		TVCommCtrl.Firmware_VersionRead(TVCommCtrl.m_ReadCheckNo + 1);
	else
		ReadNextUpdateVersion();
	m_WaitCount = 0;

}
void COptSpecPage::ReadNextUpdateVersion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lCheckFlag = 0;

	TVCommCtrl.m_ReadComplete = 0;
	TVCommCtrl.m_bCheckReadVersion = 1;
	TVCommCtrl.m_ReadCheckNo++;

	if (TVCommCtrl.m_ReadCheckNo >= MAX_NUM_VER_COUNT)
	{
		TVCommCtrl.m_bCheckReadVersion = 0;
		MessageBox("Read Version OK!!", "VERSION CHECK OK");

	}
	else
	{

		lCheckFlag = m_ctrlAudioVerSpecList.GetCheck(TVCommCtrl.m_ReadCheckNo);
		if (lCheckFlag == 1)
			TVCommCtrl.Firmware_VersionRead(TVCommCtrl.m_ReadCheckNo + 1);
		else
			ReadNextUpdateVersion();
		m_WaitCount = 0;
	}
}


void COptSpecPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	int nPos = 0;
	BYTE nHeader;
	BYTE nReadCount = 0;
	if (nIDEvent == 1)
	{
		KillTimer(1);
		if (TVCommCtrl.m_ReadComplete == 1)
		{

			if (TVCommCtrl.m_nReceiveLength > 0)
			{
				TVCommCtrl.m_nRevLength = 0;
				if (TVCommCtrl.m_nRevLength == 0)
				{
					for (int nPos = 0; nPos < 256; nPos++)
					{
						nHeader = TVCommCtrl.m_nReceiveData[nPos];
						if (nHeader == 0xbb) {
							break;
						}
					}

					//if (nPos < 255) {
					//	nTemp = TVCommCtrl.m_nReceiveData[nPos + 1];
					//}
					//else
					//{
					//	return FALSE;
					//}
					//nTemp2 = nPos + nTemp + 1;
					nReadCount = TVCommCtrl.m_nReceiveData[nPos+1] + 2;
					int i, j;
					for (i = 0, j = nPos; (i < nReadCount)&&(j < 256); i++, j++)
					{
						TVCommCtrl.m_nRevData[i] = TVCommCtrl.m_nReceiveData[j];
					}
					TVCommCtrl.m_nRevLength = i;


				}
				if (TVCommCtrl.m_nRevLength == TVCommCtrl.m_nRevData[1] + 2)
				{



					for (int i = 0; i < TVCommCtrl.m_nRevLength; i++)
					{
						sTemp.Format("%02X ", TVCommCtrl.m_nRevData[i]);
						szMsg1 = szMsg1 + sTemp;
					}
					for (int i = 0; i < TVCommCtrl.m_nRevLength - 1; i++)
					{
						nCheckSum1 = nCheckSum1 ^ TVCommCtrl.m_nRevData[i];
					}

					nCheckSum2 = TVCommCtrl.m_nRevData[TVCommCtrl.m_nRevLength - 1];
					if (nCheckSum1 != nCheckSum2) {
						sTemp.Format(",CheckSum Fail(%02X,%02X)", nCheckSum1, nCheckSum2);
						//szMsg1 = szMsg1 + sTemp;
						bCheckSum_Check = FALSE;
						AddStringToStatus(sTemp);
					}

					if ((CurrentSet->nChipType == CHIP_MCS)
						&& (TVCommCtrl.m_ReadCheckNo + 1 >= WIRELESS_TX_VER)
						&& (TVCommCtrl.m_ReadCheckNo + 1 <= CHECKSUM_VER))
					{
						bHexType = TRUE;
						if (TVCommCtrl.m_ReadCheckNo + 1 == BT_VER)
						{
							for (i = 4; i < TVCommCtrl.m_nRevLength - 1; i++)
							{
								if (((TVCommCtrl.m_nRevData[i] > '0') && (TVCommCtrl.m_nRevData[i] < '9'))
									|| ((TVCommCtrl.m_nRevData[i] > 'A') && (TVCommCtrl.m_nRevData[i] < 'F'))
									|| ((TVCommCtrl.m_nRevData[i] > 'a') && (TVCommCtrl.m_nRevData[i] < 'f')))
								{
									bHexType = FALSE;
								}
								else
								{
									bHexType = TRUE;
									break;
								}
							}
						}
					}
					
					if (TVCommCtrl.m_nRevLength > 5)
					{
						for (i = 4; i < TVCommCtrl.m_nRevLength - 1; i++)
						{
							if (bHexType) {
								sTemp.Format("%02X", TVCommCtrl.m_nRevData[i]);
							}
							else {
								sTemp.Format("%c", TVCommCtrl.m_nRevData[i]);
							}
							sReadData = sReadData + sTemp;

						}
					}
					else
					{
						sReadData = "**RCV DATA: ";
						for (i = 0; i < TVCommCtrl.m_nRevLength; i++)
						{
							//if (bHexType) {
								sTemp.Format("%02X ", TVCommCtrl.m_nRevData[i]);
							//}
							
							sReadData = sReadData + sTemp;

						}
					}

					
					//sTemp.Format("(%s%s)", sVerName, sReadData);
					//if (CurrentSet->bIsRunning && CurrentSet->bCommDisplay)
					//{
					//	AddStringToStatus(sTemp);
					//}


					if (!bCheckSum_Check)
					{
						sTemp.Format("READ %d, CHECKSUM ERROR,Cal:%02X, Rcv: %02X ",
							TVCommCtrl.m_ReadCheckNo + 1, nCheckSum1, nCheckSum2);
						MessageBox(sTemp, "Checksum Error");
						ReadNextUpdateVersion();
					//	TVCommCtrl.m_ReadComplete = 0;
					//	TVCommCtrl.m_bCheckReadVersion = 0;
					}
					else
					{
						if ((TVCommCtrl.m_ReadCheckNo >= 0)&&(TVCommCtrl.m_ReadCheckNo <= 19))
						{
							m_ctrlAudioVerSpecList.SetItemText(TVCommCtrl.m_ReadCheckNo , 1, sReadData);
							ReadNextUpdateVersion();
						}
						else
						{
							MessageBox("Index Error", "Index Error");
							ReadNextUpdateVersion();
							//TVCommCtrl.m_ReadComplete = 0;
							//TVCommCtrl.m_bCheckReadVersion = 0;
						}
					}
				}
				else
				{
					MessageBox("Data Length Error", "Data Error");
					ReadNextUpdateVersion();
					//TVCommCtrl.m_ReadComplete = 0;
					//TVCommCtrl.m_bCheckReadVersion = 0;
				}


			}
			else
			{
				MessageBox("Data No Error", "Data Error");
				//TVCommCtrl.m_ReadComplete = 0;
				//TVCommCtrl.m_bCheckReadVersion = 0;
				ReadNextUpdateVersion();
			}

		}
		else if( TVCommCtrl.m_bCheckReadVersion == 1)
		{
			m_WaitCount++;
			if (m_WaitCount > 250)
			{
				sTemp.Format("READ %d, Read Time Out ",
					TVCommCtrl.m_ReadCheckNo);
				m_ctrlAudioVerSpecList.SetItemText(TVCommCtrl.m_ReadCheckNo, 1, "Time Out");
				MessageBox(sTemp, "Read Time Out");
				//TVCommCtrl.m_ReadComplete = 0;
				//TVCommCtrl.m_bCheckReadVersion = 0;
				ReadNextUpdateVersion();
			}
		}
		
		SetTimer(1, 20, NULL);
	}

	/*for (int i = 0; i < 15; i++)
	{
		lCheckFlag = m_ctrlAudioVerSpecList.GetCheck(i);
		if (lCheckFlag == 1)
		{
			if (TVCommCtrl.Firmware_VersionRead(i + 1, sTempVersion))
			{
				m_ctrlAudioVerSpecList.SetItemText(i, 1, sTempVersion);
			}
			else
			{
				MessageBox("Read Version Error","RS232 Com Error");
				TVCommCtrl.m_bCheckReadVersion = 0;
				return;
			}
			
		}
		else
		{
			m_ctrlAudioVerSpecList.SetItemText(i, 1, "");
		}
	}
	MessageBox("Read Version OK", "VERSION CHECK OK");
*/


	CPropertyPage::OnTimer(nIDEvent);
}


void COptSpecPage::OnHdnItemclickListAudioSpecList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
		int lint = phdr->iItem;
		int i, lcnt;
		if (lint == 0)
		{
			if (mCheckAll == 1)
			{
				mCheckAll = 0;
				lcnt = m_ctrlAudioVerSpecList.GetItemCount();
				for (i = 0; i < lcnt; i++)
				{
					m_ctrlAudioVerSpecList.SetCheck(i, 0);
					
				}
			}
			else
			{
				mCheckAll = 1;
				lcnt = m_ctrlAudioVerSpecList.GetItemCount();
				for (i = 0; i < lcnt; i++)
				{
					m_ctrlAudioVerSpecList.SetCheck(i, 1);
					
				}
			}
		}
	
	
	*pResult = 0;
}
