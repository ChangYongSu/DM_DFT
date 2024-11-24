// CSelectChassisModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"//#include "datsys.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "CSelectChassisModelDlg.h"
#include "Global.h"
#include "AddModelDlg.h"
//
//#include "stdafx.h"
//#include "CSelectChassisModelDlg.h"
//#include "afxdialogex.h"

extern CStringArray g_Divisions;
// CSelectChassisModelDlg 대화 상자

IMPLEMENT_DYNAMIC(CSelectChassisModelDlg, CDialog)

CSelectChassisModelDlg::CSelectChassisModelDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SELECT_CHASSIS_MODEL, pParent)
	, m_szCurrentSeqFilePath(_T(""))
	, m_szModelInfoFilePath(_T(""))
	, m_szRefImgFolder(_T(""))
	, m_szSeqFilePath(_T(""))
	, m_szCurrentRefFilePath(_T(""))
{

}

CSelectChassisModelDlg::~CSelectChassisModelDlg()
{
}

void CSelectChassisModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT_SEQ, m_szCurrentSeqFilePath);
	DDX_Text(pDX, IDC_EDIT_MODEL_INFO, m_szModelInfoFilePath);
	DDX_Text(pDX, IDC_EDIT_REF_FOLDER, m_szRefImgFolder);
	DDX_Text(pDX, IDC_EDIT_SEQ, m_szSeqFilePath);
	DDX_Text(pDX, IDC_EDIT_CURRENT_REF, m_szCurrentRefFilePath);
	DDX_Control(pDX, IDC_LIST_CHASSIS, m_cListChassis);
	DDX_Control(pDX, IDC_LIST_MODEL, m_cListModel);
	DDX_Control(pDX, IDC_COMBO_DIVISION, m_ctrlComboDivision);
}


BEGIN_MESSAGE_MAP(CSelectChassisModelDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DIVISION, &CSelectChassisModelDlg::OnCbnSelchangeComboDivision)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHASSIS, &CSelectChassisModelDlg::OnNMClickListChassis)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CHASSIS, &CSelectChassisModelDlg::OnNMCustomdrawListChassis)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MODEL, &CSelectChassisModelDlg::OnNMClickListModel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MODEL, &CSelectChassisModelDlg::OnNMCustomdrawListModel)
	ON_BN_CLICKED(IDOK, &CSelectChassisModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectChassisModelDlg 메시지 처리기


void CSelectChassisModelDlg::OnCbnSelchangeComboDivision()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nDivision_Sel = m_ctrlComboDivision.GetCurSel();
	UpdateGrid();
}


void CSelectChassisModelDlg::OnNMClickListChassis(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_nChaassis_SelectRow = (int)m_cListChassis.GetFirstSelectedItemPosition() - 1; //  m_gridChassis.GetRow();
	//int			nModelRow = (int)m_cListModel.GetFirstSelectedItemPosition() - 1;// //m_gridModel.GetRow();
	//int			nChassisRow = m_nChaassis_SelectRow;
	//int			nModelRow = m_nModel_SelectRow;// //m_gridModel.GetRow();
	m_cListChassis.Invalidate();
	OnClickChassisGrid();
	*pResult = 0;
	
}


void CSelectChassisModelDlg::OnNMCustomdrawListChassis(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


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

		//	nCol= m_CtrlListMainProcess.getse.GetSelectedColumn();
		//	nRow= m_CtrlListMainProcess.GetItemCount();

		int l_nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //row
		int l_nSubItem = (int)(pLVCD->iSubItem);


		if (l_nItem == m_nChaassis_SelectRow)
		{
			crText = RGB(0, 0, 0); ////m_cListChassisEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
			crBkgnd = RGB(255, 0, 255); ////m_cListChassisEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		}
		else
		{
			crText = RGB(0, 0, 0); ////m_cListChassisEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
			crBkgnd = RGB(255, 255, 255); ////m_cListChassisEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		}


		//		if (2 == (int)(pLVCD->iSubItem))
		//		{
		//			strCol = m_CtrlListMainProcess.GetItemText(pLVCD->nmcd.dwItemSpec, 2);
		//			if (strCol == "NG") // 두번째열의 값이 "10"일 때, 그 값 부분만			
		//			{
		//				crText = RGB(0, 0, 0); //글자색
		//				crBkgnd = RGB(255, 0, 0); //배경색으로 한다    
		//			}
		//			else if (2 == (int)(pLVCD->iSubItem) && strCol == "OK")
		//			{
		//				crText = RGB(0, 0, 0);
		//				crBkgnd = RGB(0, 255, 0);
		//			}
		//			else
		//			{
		//				if ((nItem == m_nCurrentNumber) && (m_TaskRun != TASK_RUN_IDLE))//else if(nItem == m_Process_Index)          
		//				{
		//					crText = RGB(0, 0, 0);
		//					crBkgnd = RGB(255, 255, 100);
		//				}
		//				else
		//				{
		//					crText = RGB(0, 0, 0);
		//					crBkgnd = RGB(255, 255, 255);
		//				}
		//			}
		//
		//		}
		//		else
		//		{
		//			//int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec ); //row
		//			//m_TaskRun;m_Process_Index
		////int		m_nCurrentNumber;
		//			if ((nItem == m_nCurrentNumber) && (m_TaskRun != TASK_RUN_IDLE))
		//			{
		//				//if(pLVCD->iSubItem >= 1)
		//				{
		//					crText = RGB(0, 0, 0);
		//					crBkgnd = RGB(255, 255, 100);
		//				}
		//
		//			}
		//			else
		//			{
		//
		//				crText = RGB(0, 0, 0);
		//				crBkgnd = RGB(255, 255, 255);
		//			}
		//		}
		//
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;


		*pResult = CDRF_DODEFAULT;
		return;
	}
	}
	*pResult = 0;
}


void CSelectChassisModelDlg::OnNMClickListModel(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	m_nChaassis_SelectRow = (int)m_cListChassis.GetFirstSelectedItemPosition() - 1; //  m_gridChassis.GetRow();
	m_nModel_SelectRow = (int)m_cListModel.GetFirstSelectedItemPosition() - 1;// //m_gridModel.GetRow();
	m_cListModel.Invalidate();
	//int			nChassisRow = m_nChaassis_SelectRow;
	//int			nModelRow = m_nModel_SelectRow;// //m_gridModel.GetRow();
	OnClickModelGrid();
	*pResult = 0;

}


void CSelectChassisModelDlg::OnNMCustomdrawListModel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMHDR;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


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



		int l_nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec); //row
		int l_nSubItem = (int)(pLVCD->iSubItem);


		if (l_nItem == m_nModel_SelectRow)
		{
			crText = RGB(0, 0, 0); ////m_cListChassisEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
			crBkgnd = RGB(255, 0, 255); ////m_cListChassisEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		}
		else
		{
			crText = RGB(0, 0, 0); ////m_cListChassisEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
			crBkgnd = RGB(255, 255, 255); ////m_cListChassisEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		}


		//if ((l_nItem >= 0) && (l_nItem < 500) && (l_nSubItem >= 0) && (l_nSubItem < 20))
		//{
		//	crText = m_cListModelEx.nSelForeColor[l_nItem][l_nSubItem];// RGB(0, 0, 0); //글자색
		//	crBkgnd = m_cListModelEx.nSelBackColor[l_nItem][l_nSubItem];// = RGB(255, 0, 0); //배경색으로 한다   
		//}


		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;


		*pResult = CDRF_DODEFAULT;
		return;
	}
	}
	*pResult = 0;
}



void CSelectChassisModelDlg::OnClickChassisGrid()
{
	POSITION	Pos = NULL;
	CModelData* pModelData = NULL;

	int			nChassisRow = m_nChaassis_SelectRow; // (int)m_cListChassis.GetFirstSelectedItemPosition() - 1; //  m_gridChassis.GetRow();
	int			nCurModelRow = m_nModel_SelectRow;// //int			nCurModelRow = (int)m_cListModel.GetFirstSelectedItemPosition();// //m_gridModel.GetRow();

	int			nModelRow = 0;

	CString szChassisName = _T("");
	CString szModelName = _T("");

	m_cListModel.DeleteAllItems();

	if ((nChassisRow <= 0) && (m_cListChassis.GetItemCount() > 1))
	{
		//m_gridChassis.SetRow(1); 
		nChassisRow = 0;
	}
	else if ((nChassisRow >= m_cListChassis.GetItemCount()) && (m_cListChassis.GetItemCount() > 1))
	{
		//m_gridChassis.SetRow(m_gridChassis.GetRows() - 1); 
		nChassisRow = m_cListChassis.GetItemCount() - 1;
	}


	szChassisName = m_cListChassis.GetItemText(nChassisRow, 0);// m_gridChassis.GetTextMatrix(nChassisRow,0);

	Pos = CurrentSet->ModelList.GetHeadPosition();

	while (Pos)
	{
		pModelData = CurrentSet->ModelList.GetNext(Pos);

		if (pModelData->m_szChassisName != _T(""))
		{
			if (pModelData->m_szChassisName.Compare(szChassisName) == NULL)
			{
				szModelName = pModelData->m_szModelName;

				//m_gridModel.SetRows(nModelRow + 1);
				m_cListModel.InsertItem(nModelRow++, szModelName);// //m_gridModel.SetTextMatrix(nModelRow++, 0, szModelName);
				//SetItem(m_nCurrentNumber, 2, LVIF_TEXT, "OK", NULL, NULL, NULL, NULL);
			}
		}
	}
	ChangeRowColor(nChassisRow, CHASSIS_GRID);
	if (m_sSelChassis != szChassisName)
	{
		m_sSelChassis = szChassisName;
		m_cListModel.SetSelectionMark(0);//m_cListModelEx.SetCellBackColor(); //m_gridModel.SetRow(1);
	}
	else {
		if (nCurModelRow <= 0) {
			m_cListModel.SetSelectionMark(0);//m_gridModel.SetRow(1);
		}
		else if (nCurModelRow >= m_cListModel.GetItemCount())//m_gridModel.GetRows())
		{
			m_cListModel.SetSelectionMark(m_cListModel.GetItemCount() - 1);//mm_gridModel.SetRow(m_gridModel.GetRows() -1);
		}
		else {
			m_cListModel.SetSelectionMark(m_nModel_SelectRow);//m_gridModel.SetRow(m_nModel_SelectRow);
		}
	}
	m_nChaassis_SelectRow = nChassisRow;
	OnClickModelGrid();
}

void CSelectChassisModelDlg::OnClickModelGrid()
{
	POSITION	Pos = NULL;
	CModelData* pModelData = NULL;

	int			nChassisRow = m_nChaassis_SelectRow; //(int)m_cListChassis.GetFirstSelectedItemPosition() -1; //  m_gridChassis.GetRow();
	int			nModelRow = m_nModel_SelectRow;//(int)m_cListModel.GetFirstSelectedItemPosition()-1;// //m_gridModel.GetRow();


	CString szChassisName = _T("");
	CString szModelName = _T("");

	//	if((nModelRow <= 0) &&  (m_gridModel.GetRows() > 1))
	if ((nModelRow <= 0) && (m_cListModel.GetItemCount() > 1))//.GetRows() > 1))
	{
		//m_gridModel.SetRow(1); 
		m_cListModel.SetSelectionMark(0);
		nModelRow = 0;
	}
	else if ((nModelRow >= m_cListModel.GetItemCount()) && (m_cListModel.GetItemCount() > 1))
	{
		m_cListModel.SetSelectionMark(m_cListModel.GetItemCount());//m_gridModel.SetRow(m_gridModel.GetRows() - 1); 
		nModelRow = m_cListModel.GetItemCount() - 1;
	}

	szChassisName = m_cListChassis.GetItemText(nChassisRow, 0);// m_gridChassis.GetTextMatrix(nChassisRow, 0);
	szModelName = m_cListModel.GetItemText(nModelRow, 0);//m_gridModel.GetTextMatrix(nModelRow,0);
	m_sSelModel = szModelName;

	Pos = CurrentSet->ModelList.GetHeadPosition();

	while (Pos)
	{
		pModelData = CurrentSet->ModelList.GetNext(Pos);

		if (pModelData->m_szModelName != _T(""))
		{
			if ((pModelData->m_szChassisName.Compare(szChassisName) == NULL) &&
				(pModelData->m_szModelName.Compare(szModelName) == NULL))
			{
				m_szSeqFilePath = pModelData->m_szSeqFilePath;
				m_szModelInfoFilePath = pModelData->m_szModelInfoFilePath;
				m_szRefImgFolder = pModelData->m_szRefImgFolder;

				break;
			}
		}
	}

	UpdateData(FALSE);
	m_nModel_SelectRow = nModelRow;
	ChangeRowColor(nModelRow, MODEL_GRID);
	//	delete pModelData;
}

BOOL CSelectChassisModelDlg::OnInitDialog()
{
	//+add 090219(Modification No2)
//	CString szLog = "B:OnInitDialog\n";
//	if(g_LogFileOpen) g_LogFile.WriteString(szLog);

	CDialog::OnInitDialog();

	CString sTemp;
	CString sTemp2;
	// TODO: Add extra initialization here
	if (CurrentSet->sServerFolder.IsEmpty())
	{
		m_szCurrentSeqFilePath = "D:\\DM_HDFT";
	}
	else
	{
		m_szCurrentSeqFilePath = CurrentSet->sServerFolder;
	}

	if (CurrentSet->sRefRootFolder.IsEmpty())
	{
		m_szCurrentRefFilePath = "D:\\DM_HDFT";
	}
	else
	{
		m_szCurrentRefFilePath = CurrentSet->sRefRootFolder;
	}

	////+add kwmoon 080904
	//pCurrentSet->sServerFolder = pApp->GetProfileString(_T("Folder"), _T("Current Server Folder"), "D:\\DM_DFT");
	////+add PSH 081029
	//pCurrentSet->sRefRootFolder = pApp->GetProfileString(_T("Folder"), _T("Current Reference Image Root Folder"), "D:\\DM_DFT");
	////+add PSH 081211
	//pCurrentSet->sModelInfoFolder = pApp->GetProfileString(_T("Folder"), _T("Current Model Info  Root Foler"), "D:\\DM_DFT");




	UpdateData(FALSE);

	//	if(OpenModelListFile(CurrentSet->sModelListPath,m_nNoModel) == FALSE) return;	

	InitGrid();

	//	m_ctrlDivisionCmb.ResetContent();
	CStringArray lDivisionArray;
	m_ctrlComboDivision.AddString("ALL");
	for (int i = 0; i < g_Divisions.GetSize(); i++)
	{
		sTemp = g_Divisions.GetAt(i);
		int lSet = 0;
		for (int j = 0; j < lDivisionArray.GetSize(); j++)
		{
			sTemp2 = lDivisionArray.GetAt(j);
			if (sTemp < sTemp2)
			{
				lDivisionArray.InsertAt(j, sTemp);
				sTemp = sTemp2;
				lSet = 1;
				break;
			}
		}
		if (lSet == 0)
			lDivisionArray.Add(sTemp);
		//m_ctrlDivisionCmb.AddString(sTemp);
	}

	for (int i = 0; i < lDivisionArray.GetSize(); i++)
	{
		sTemp = lDivisionArray.GetAt(i);
		m_ctrlComboDivision.AddString(sTemp);
	}

	m_ctrlComboDivision.SetCurSel(0);
	//	m_nSelDivision = 0;
	m_nDivision_Sel = 0;
	m_nChaassis_SelectRow = 0;
	

	m_nModel_SelectRow = 0;
	UpdateGrid();

	//////////////////////////////////////////////////

	CString szChassisName;
	for (int i = 0; i < m_cListChassis.GetItemCount(); i++)
	{
		szChassisName = m_cListChassis.GetItemText(i, 0);
		if (szChassisName == CurrentSet->sChassisName)
		{
			m_nChaassis_SelectRow = i;
			break;
		}
	}
	m_cListChassis.Invalidate();//m_gridChassis.SetRedraw(TRUE);
	//m_gridChassis.Refresh();
	if (m_cListChassis.GetItemCount() > 1)
	{
		m_cListChassis.SetSelectionMark(m_nChaassis_SelectRow + 1);// GetFirstSelectedItemPosition(); //m_gridChassis.SetRow(m_nChaassis_SelectRow);
		OnClickChassisGrid();
	}
	   
	CString szModelName;
	m_nModel_SelectRow = 0;
	for (int i = 0; i < m_cListModel.GetItemCount(); i++)
	{
		szModelName = m_cListModel.GetItemText(i, 0);
		if (szModelName == CurrentSet->sModelName)
		{
			m_nModel_SelectRow = i;
			break;
		}
	}
	
	if (m_cListModel.GetItemCount() > 1)
	{
		m_cListModel.SetSelectionMark(m_nModel_SelectRow + 1);// GetFirstSelectedItemPosition(); //m_gridChassis.SetRow(m_nChaassis_SelectRow);
	}
	OnClickModelGrid(); 





	//if(m_gridChassis.GetRows() > 1)
	//{
	//	m_gridChassis.SetRow(1);
	//	OnClickChassisGrid();
	//}
//	else{
//		OnBtnAdd();
//	}

	ShowWindow(SW_SHOW);

	//+add 090219(Modification No2)
//	szLog = "E:OnInitDialog\n";
//	if(g_LogFileOpen) g_LogFile.WriteString(szLog);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectChassisModelDlg::InitGrid()
{
	//m_cListChassis);	
	//m_cListModel);

	m_cListChassis.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);// 리스트 컨트롤 초기화: 열 추가

	m_cListChassis.InsertColumn(0, _T("CHASSIS LIST"), LVCFMT_CENTER, 255);
	m_cListChassis.InsertItem(0, _T(" "));   // 첫째행(0), 첫째열에 삽입
	m_cListChassis.Invalidate();

	m_cListModel.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);// 리스트 컨트롤 초기화: 열 추가

	m_cListModel.InsertColumn(0, _T("MODEL LIST"), LVCFMT_CENTER, 270);
	m_cListModel.InsertItem(0, _T(" "));   // 첫째행(0), 첫째열에 삽입
	m_cListModel.Invalidate();

	/*m_gridChassis.SetRedraw(FALSE);
	m_gridChassis.SetAllowBigSelection(FALSE);
	m_gridChassis.SetExtendLastCol(TRUE);
	m_gridChassis.SetCols(1);
	m_gridChassis.SetRows(1);
	m_gridChassis.SetFixedRows(1);
	m_gridChassis.SetFixedCols(0);
	m_gridChassis.SetGridLines(flexGridFlat);
	m_gridChassis.SetTextMatrix(0, 0, "CHASSIS LIST");
	m_gridChassis.SetRedraw(TRUE);
	m_gridChassis.Refresh();

	m_gridChassis.SetBackColorFixed(RGB(210,216,176));
	m_gridChassis.SetForeColorFixed(RGB(51,102,153));
	m_gridChassis.SetBackColor(RGB(247,247,231));
	m_gridChassis.SetGridColor(RGB(210,216,176));
	m_gridChassis.SetColAlignment(0, flexAlignCenterCenter);


	m_gridModel.SetRedraw(FALSE);
	m_gridModel.SetAllowBigSelection(FALSE);
	m_gridModel.SetExtendLastCol(TRUE);
	m_gridModel.SetCols(1);
	m_gridModel.SetRows(1);
	m_gridModel.SetFixedRows(1);
	m_gridModel.SetFixedCols(0);
	m_gridModel.SetGridLines(flexGridFlat);
	m_gridModel.SetTextMatrix(0, 0, "MODEL LIST");
	m_gridModel.SetRedraw(TRUE);
	m_gridModel.Refresh();

	m_gridModel.SetBackColorFixed(RGB(210,216,176));
	m_gridModel.SetForeColorFixed(RGB(51,102,153));
	m_gridModel.SetBackColor(RGB(247,247,231));
	m_gridModel.SetGridColor(RGB(210,216,176));
	m_gridModel.SetColAlignment(0, flexAlignCenterCenter);*/
}

void CSelectChassisModelDlg::UpdateGrid()
{
	POSITION	Pos = NULL;
	CModelData* pModelData = NULL;
	CString		szChassisName = _T("");
	int			nChassisRow = 0;
	CString sTemp;

	//m_cListChassis);	
	//m_cListModel);
	m_cListChassis.DeleteAllItems();//  m_gridChassis.SetRedraw(FALSE);
	//m_gridChassis.Clear(COleVariant(long(flexClearScrollable)), COleVariant(long(flexClearEverything))); 

	Pos = CurrentSet->ModelList.GetHeadPosition();

	while (Pos)
	{
		pModelData = CurrentSet->ModelList.GetNext(Pos);

		szChassisName = pModelData->m_szChassisName;

		if (IsSameChassis(szChassisName) != TRUE)
		{
			if (m_nDivision_Sel == 0)
			{
				//m_gridChassis.SetRows(nChassisRow + 1);
				//m_gridChassis.SetTextMatrix(nChassisRow++, 0, szChassisName);
				m_cListChassis.InsertItem(nChassisRow, szChassisName);   // 첫째행(0), 첫째열에 삽입
				nChassisRow++;
			}
			else {
				m_ctrlComboDivision.GetLBText(m_nDivision_Sel, sTemp);
				if (sTemp == pModelData->m_szDivision)
				{
					m_cListChassis.InsertItem(nChassisRow, szChassisName);   // //m_gridChassis.SetRows(nChassisRow + 1);
					//m_gridChassis.SetTextMatrix(nChassisRow++, 0, szChassisName);
					nChassisRow++;
				}
			}
		}
	}


	//for (int i = 0; i < m_cListChassis.GetItemCount(); i++)
	//{
	//	szChassisName = m_cListChassis.GetItemText(i, 0);
	//	if (szChassisName == CurrentSet->sChassisName)
	//	{
	//		m_nChaassis_SelectRow = i;
	//		break;
	//	}
	//}
	m_cListChassis.Invalidate();//m_gridChassis.SetRedraw(TRUE);
	//m_gridChassis.Refresh();
	if (m_cListChassis.GetItemCount() > 1)
	{
		m_cListChassis.SetSelectionMark(m_nChaassis_SelectRow + 1);// GetFirstSelectedItemPosition(); //m_gridChassis.SetRow(m_nChaassis_SelectRow);
		OnClickChassisGrid();
	}


	//if(m_gridChassis.GetRows() > 1)
	//{
	//	m_gridChassis.SetRow(m_nChaassis_SelectRow);
	//	OnClickChassisGrid();
	//}

}

BOOL CSelectChassisModelDlg::IsSameChassis(CString szChassisName)
{
	CString	szRegisteredChassisName = _T("");
	//	POSITION lpos = m_cListChassis.GetFirstSelectedItemPosition();
	//	int	nNoChassis = (int)lpos;   //m_gridChassis.GetRows() - 1;
	int	nNoChassis = m_cListChassis.GetItemCount();
	szChassisName.MakeUpper();

	for (int i = 0; i < nNoChassis; i++)
	{
		szRegisteredChassisName = m_cListChassis.GetItemText(i, 0); // .GetTextMatrix(i+1, 0);

		szRegisteredChassisName.MakeUpper();

		if (szChassisName.Compare(szRegisteredChassisName) == NULL)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CSelectChassisModelDlg::ChangeRowColor(int nRow, int nGridType)
{
//	//===============
//	// Chassis Grid
//	//===============
//	int	nItemCount = 0;
//	if (nGridType == CHASSIS_GRID)
//	{
//		nItemCount = m_cListChassis.GetItemCount();
//		for (int nTotalRow = 0; nTotalRow < nItemCount; nTotalRow++)
//		{
//			//m_gridChassis.SetRow(nTotalRow);
//			//m_gridChassis.SetCol(0);
//			//m_gridChassis.SetCellBackColor(RGB(255,255,255));
//			//m_gridChassis.SetCellForeColor(RGB(0,0,0));
//			m_cListChassisEx.SetCellBackColor(nTotalRow, RGB(255, 255, 255)); // m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(189, 231, 97));
//			m_cListChassisEx.SetCellForeColor(nTotalRow, RGB(0, 0, 0)); // m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(189, 231, 97));
//		}
//		m_cListChassisEx.SetCellBackColor(nRow, RGB(255, 0, 255)); // m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(189, 231, 97));
//		m_cListChassisEx.SetCellForeColor(nRow, RGB(0, 0, 0)); // m_CtrlListMainProcessEx.SetCellBackColor(nTmp, RGB(189, 231, 97));
////		m_gridChassis.SetRow(nRow);
////		m_gridChassis.SetCol(0);
////
//////		m_gridChassis.SetCellBackColor(RGB(10, 36, 106 ));
////		m_gridChassis.SetCellBackColor(RGB(255, 0, 255 ));
//////		m_gridChassis.SetCellForeColor(RGB(255,255,255));
//
//		m_cListChassis.Invalidate();
//	}
//	//===============
//	// Chassis Grid
//	//===============
//	else
//	{
//		nItemCount = m_cListModel.GetItemCount();
//		for (int nTotalRow = 0; nTotalRow < nItemCount; nTotalRow++)
//		{
//			/*		m_gridModel.SetRow(nTotalRow);
//					m_gridModel.SetCol(0);
//					m_gridModel.SetCellBackColor(RGB(255,255,255));
//					m_gridModel.SetCellForeColor(RGB(0,0,0));*/
//			m_cListModelEx.SetCellBackColor(nTotalRow, RGB(255, 255, 255));
//			m_cListModelEx.SetCellForeColor(nTotalRow, RGB(0, 0, 0)); // 
//		}
//
//		//	m_gridModel.SetRow(nRow);
//		//	m_gridModel.SetCol(0);
//
//	//		m_gridModel.SetCellBackColor(RGB(10, 36,   106 ));
//		m_cListModelEx.SetCellBackColor(nRow, RGB(255, 0, 255));
//		//		m_gridModel.SetCellForeColor(RGB(255,255,255));
//
//		m_cListModel.Invalidate();
//	}
}



BOOL CSelectChassisModelDlg::CheckModel(CString sChassis, CString sModel)
{
	POSITION	Pos = NULL;
	CModelData* pModelData = NULL;
	//	int			nChassisRow		= m_gridChassis.GetRow();
		//int			nModelRow		= m_gridModel.GetRow();
	int	nChassisRow = (int)m_cListChassis.GetFirstSelectedItemPosition(); //m_gridChassis.GetRow();
	int	nModelRow = (int)m_cListModel.GetFirstSelectedItemPosition(); //m_gridModel.GetRow();

	CString szChassisName = _T("");
	CString szModelName = _T("");

	if ((nChassisRow <= 0) || (nChassisRow >= m_cListChassis.GetItemCount())) {
		szChassisName = _T("");
	}
	else {
		szChassisName = m_cListChassis.GetItemText(nChassisRow, 0);

	}

	if ((nModelRow <= 0) || (nModelRow >= m_cListModel.GetItemCount())) {
		szModelName = _T("");
	}
	else {
		szModelName = m_cListModel.GetItemText(nModelRow, 0); //(nModelRow,0);
	}

	Pos = CurrentSet->ModelList.GetHeadPosition();
	while (Pos)
	{
		pModelData = CurrentSet->ModelList.GetNext(Pos);

		//		if(pModelData == NULL) continue;
		if ((pModelData->m_szChassisName != _T("")) && (pModelData->m_szModelName != _T("")))
		{
			if ((sChassis.Compare(pModelData->m_szChassisName) == NULL)
				&& (sModel.Compare(pModelData->m_szModelName) == NULL))
			{
				//				delete pModelData;
				return FALSE;
			}
		}
	}
	if ((szChassisName != _T("")) && (szModelName != _T("")))
	{
		if ((sChassis.Compare(szChassisName) == NULL) && (sModel.Compare(szModelName) == NULL))
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CSelectChassisModelDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: Add extra validation here
	UpdateData(TRUE);

	// TODO: Add extra validation here
	if (m_szSeqFilePath == _T(""))
	{
		AfxMessageBox("Incorrect Sequence File"); return;
	}

	if (m_szModelInfoFilePath == _T(""))
	{
		AfxMessageBox("Incorrect Model Info File"); return;
	}

	if (m_szRefImgFolder == _T(""))
	{
		AfxMessageBox("Incorrect Reference Folder "); return;
	}
	CDialog::OnOK();
}
