// COptUserInfoPage.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptUserInfoPage.h"

extern CAcqVoltageSamples_IntClkDlg* m_pMainDlg;
// COptUserInfoPage
IMPLEMENT_DYNCREATE(COptUserInfoPage, CPropertyPage)

COptUserInfoPage::COptUserInfoPage() : CPropertyPage(COptUserInfoPage::IDD)
{
	//{{AFX_DATA_INIT(COptUserInfoPage)

	//}}AFX_DATA_INIT
}

COptUserInfoPage::~COptUserInfoPage()
{
}

void COptUserInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptUserInfoPage)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_VOLT_PROCESS, m_CtrlListVoltProcess);
	DDX_Control(pDX, IDC_LIST_DI_PROCESS, m_CtrlListDiProcess);
	//DDX_Control(pDX, IDC_LIST_DO_PROCESS, m_CtrlListDoProcess);
}


BEGIN_MESSAGE_MAP(COptUserInfoPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptGrabberPage)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &COptUserInfoPage::OnBnClickedButtonCheck)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_DIO_CHECK, &COptUserInfoPage::OnBnClickedButtonDioCheck)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DI_PROCESS, &COptUserInfoPage::OnNMClickListDiProcess)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_DI_PROCESS, &COptUserInfoPage::OnNMCustomdrawListDiProcess)
END_MESSAGE_MAP()
//
//IMPLEMENT_DYNAMIC(COptUserInfoPage, CMFCPropertyPage)
//
//COptUserInfoPage::COptUserInfoPage()
//{
//
//}
//
//COptUserInfoPage::~COptUserInfoPage()
//{
//}
//
//
//BEGIN_MESSAGE_MAP(COptUserInfoPage, CMFCPropertyPage)
//END_MESSAGE_MAP()
//
//
//
//// COptUserInfoPage 메시지 처리기
//
//


BOOL COptUserInfoPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetListControl();
	SetSubListControl();
	SetTimer(1, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COptUserInfoPage::OnOK()
{
	int  i = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPropertyPage::OnOK();
}



void COptUserInfoPage::SetListControl()
{

	//	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListVoltProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListVoltProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 36);
	m_CtrlListVoltProcess.InsertColumn(1, _T("NAME"), LVCFMT_CENTER, 100);// 리스트 행 추가
	m_CtrlListVoltProcess.InsertColumn(2, _T("TARGET"), LVCFMT_CENTER, 70);// 리스트 행 추가
	m_CtrlListVoltProcess.InsertColumn(3, _T("READ"), LVCFMT_CENTER, 70);// 리스트 행 추가
	

	m_CtrlListVoltProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
	m_CtrlListVoltProcess.SetItem(0, 1, LVIF_TEXT, _T("FM TEST"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	m_CtrlListVoltProcess.SetItem(0, 2, LVIF_TEXT, _T("97.8Hz"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 

	   

	m_CtrlListDiProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListDiProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 36);
	m_CtrlListDiProcess.InsertColumn(1, _T("DI"), LVCFMT_CENTER, 100);// 리스트 행 추가
	m_CtrlListDiProcess.InsertColumn(2, _T("DO"), LVCFMT_CENTER, 100);// 리스트 행 추가
	
	m_CtrlListDiProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
	m_CtrlListDiProcess.SetItem(0, 1, LVIF_TEXT, _T("ON"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	m_CtrlListDiProcess.SetItem(0, 2, LVIF_TEXT, _T("OFF"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
		   
	CFont *font;

	font = new CFont;
	font->CreateFontA(16,                          // nHeight
		0,                          // nWidth
		0,                          // nEscapement
		0,                          // nOrientation
		400,                           // nWeight
		0,                          // bItalic
		0,                          // bUnderline 
		0,                          // cStrikeOut 
		0,                          // nCharSet
		0,           // nOutPrecision 
		0,                          // nClipPrecision 
		PROOF_QUALITY,              // nQuality
		0,  // nPitchAndFamily 
		_T("Arial"));                     // lpszFacename


	delete font;

}


void COptUserInfoPage::SetSubListControl()
{

	CSize lSize;
	CString strTemp;

	m_CtrlListVoltProcess.DeleteAllItems();

	//mCheckAll = 1;

	for (int i = 0; i < 32; i++)
	{
		strTemp.Format(_T("%d"), i + 1);
		m_CtrlListVoltProcess.InsertItem(i, strTemp);


		strTemp.Format(_T("VOLT %d"), i + 1);// = gTestSeqData.TestStepList[i].strStepName;
		m_CtrlListVoltProcess.SetItem(i, 1, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);
		m_CtrlListVoltProcess.SetItem(i, 2, LVIF_TEXT, "3.3", NULL, NULL, NULL, NULL);
		m_CtrlListVoltProcess.SetItem(i, 3, LVIF_TEXT, "0", NULL, NULL, NULL, NULL);
		m_CtrlListVoltProcess.SetCheck(i, 1);		
	}
	m_CtrlListVoltProcess.Invalidate();

	m_CtrlListDiProcess.DeleteAllItems();
	for (int i = 0; i < 20; i++)
	{
		strTemp.Format(_T("%d"), i + 1);
		m_CtrlListDiProcess.InsertItem(i, strTemp);


		//strTemp.Format(_T("VOLT %d"), i + 1);// = gTestSeqData.TestStepList[i].strStepName;
		m_CtrlListDiProcess.SetItem(i, 1, LVIF_TEXT, "NC", NULL, NULL, NULL, NULL);
		m_CtrlListDiProcess.SetItem(i, 2, LVIF_TEXT, "NC", NULL, NULL, NULL, NULL);
	//	m_CtrlListDiProcess.SetItem(i, 3, LVIF_TEXT, "0", NULL, NULL, NULL, NULL);
	//	m_CtrlListDiProcess.SetCheck(i, 1);


	}

	m_CtrlListDiProcess.Invalidate();
}


void COptUserInfoPage::OnBnClickedButtonCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ReadNo1 = 0;

	m_pMainDlg->ReadVolt(m_ReadNo1);
	for (int i = 0; i < 32; i++)
	{
		m_CtrlListVoltProcess.SetItemText(i, 3, "Wait...");
	}
	
	SetTimer(100, 500, NULL);

}


void COptUserInfoPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static BYTE DiOld[24] = {
		3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3
	};
	static BYTE DoOld[24] = {
		3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3
	};
	CString Stemp;
	if (nIDEvent == 1)
	{
		if (m_ClearFlag == 1)
		{
			for (int i = 0; i < 20; i++)
			{
				DiOld[i] = 3;
				//DoOld[i] = 3;
			}
			m_ClearFlag = 0;

		}
		for (int i = 0; i < 20; i++)
		{
			if (DiOld[i] != gDiRcvData[i])
			{
				DiOld[i] = gDiRcvData[i];
				if (gDiRcvData[i] == 0)
				{
					Stemp = m_CtrlListDiProcess.GetItemText(i, 1);
					if (Stemp != "ON")
					{
						m_CtrlListDiProcess.SetItemText(i, 1, "ON");
					}					
				}
				else
				{
					Stemp = m_CtrlListDiProcess.GetItemText(i, 1);
					if (Stemp != "OFF")
					{
						m_CtrlListDiProcess.SetItemText(i, 1, "OFF");
					}
				}				
			}
			if (DoOld[i] != gDoConfirmData[i])
			{
				DoOld[i] = gDoConfirmData[i];
				if (gDoConfirmData[i] == 1)
				{					
					Stemp = m_CtrlListDiProcess.GetItemText(i, 2);
					if (Stemp != "ON")
					{
						m_CtrlListDiProcess.SetItemText(i, 2, "ON");
					}
				}
				else
				{					
					Stemp = m_CtrlListDiProcess.GetItemText(i, 2);
					if (Stemp != "OFF")
					{
						m_CtrlListDiProcess.SetItemText(i, 2, "OFF");
					}
				}
			}
			//extern BYTE gDoConfirmData[24];
			//extern BYTE gDiRcvData[24];
		}
	}
	else if (nIDEvent == 100)
	{
		KillTimer(nIDEvent);
		if (m_pMainDlg->m_ReadMIOComAck == COM_ACK_OK)
		{
			m_pMainDlg->m_ReadVoltID;
			if (m_ReadNo1 == m_pMainDlg->m_ReadVoltID)
			{
				
				Stemp.Format("%.2f", m_pMainDlg->m_ReadVoltData);
				m_CtrlListVoltProcess.SetItemText(m_ReadNo1, 3, Stemp);
				m_ReadNo1++;
				if (m_ReadNo1 < 32)
				{
					//Sleep(100);
					m_pMainDlg->ReadVolt(m_ReadNo1);
				}
					
			}
			else
			{

			}
				
		}
		//m_ReadNo1 = 0;
	

		SetTimer(100, 100, NULL);
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}


void COptUserInfoPage::OnBnClickedButtonDioCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//0x02CDR000000W000000 s 0x03 0x0d
	//for (int i = 0; i < 20; i++)
	//{
	//	m_CtrlListDiProcess.SetItemText(i, 1, "Wait..");
	//}
	m_ClearFlag = 1;
	m_pMainDlg->ReadSMIO();
	SetTimer(1, 100, NULL);
}


void COptUserInfoPage::OnNMClickListDiProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;
	//NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	//int nSubItem = pLVCD->iSubItem;
	//int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);

	//
	//nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //
	//nSubItem = (int)(pLVCD->iSubItem);
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	int lint = phdr->iItem;
	m_ClearFlag = 1;
	if ((lint >= 0) && (lint < 24))
	{
		if (gDoConfirmData[lint] == 1)
		{
			gDoData[lint] = 0;
		}
		else
		{
			gDoData[lint] = 1;
		}

		m_pMainDlg->WriteSM_Out(lint);
		SetTimer(1, 100, NULL);
	}
	
	*pResult = 0;
}


void COptUserInfoPage::OnNMCustomdrawListDiProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//*pResult = 0;

	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	// TODO: ?ш린??而⑦듃濡??뚮┝ 泥섎━湲?肄붾뱶瑜?異붽??⑸땲??
	*pResult = 0;

	//int nRow=0;
	//int nCol=0;
	CString strCol = _T("");



	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}
	case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
	{
		COLORREF crText, crBkgnd;

		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //row
		if (1 == (int)(pLVCD->iSubItem))
		{
			strCol = m_CtrlListDiProcess.GetItemText(pLVCD->nmcd.dwItemSpec, 1);
			if (strCol == "ON") // ?먮쾲吏몄뿴??媛믪씠 "10"???? 洹?媛?遺遺꾨쭔			
			{
				crText = RGB(255, 255, 0);
				crBkgnd = RGB(0, 0, 0);
			}
			else if (strCol == "OFF")
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(100, 100, 100);
			}
			else
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(100, 100, 100);
			}
		}
		else if (2 == (int)(pLVCD->iSubItem))
		{
			strCol = m_CtrlListDiProcess.GetItemText(pLVCD->nmcd.dwItemSpec, 2);
			if (strCol == "ON") // ?먮쾲吏몄뿴??媛믪씠 "10"???? 洹?媛?遺遺꾨쭔			
			{
				crText = RGB(255, 255, 0);
				crBkgnd = RGB(0, 0, 0);
			}
			else if (strCol == "OFF")
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(100, 100, 100);
			}
			else
			{

				crText = RGB(0, 0, 0);
				crBkgnd = RGB(100, 100, 100);

			}

		}
		else
		{
			crText = RGB(0, 0, 0);
			crBkgnd = RGB(255, 255, 255);
		}


		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;


		*pResult = CDRF_DODEFAULT;
		return;
	}
	}

	*pResult = 0;
}
