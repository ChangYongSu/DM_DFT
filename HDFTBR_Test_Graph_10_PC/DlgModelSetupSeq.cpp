// DlgModelSetupSeq.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgModelSetupSeq.h"
#include "afxdialogex.h"
#include "FileControl.h"
#include "DlgNewModelName.h"
#include "DlgPassword.h"
#include "DlgConfig.h"

//#include "DlgImage.h"


// DlgModelSetupSeq 대화 상자입니다.

IMPLEMENT_DYNAMIC(DlgModelSetupSeq, CDialogEx)

DlgModelSetupSeq::DlgModelSetupSeq(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgModelSetupSeq::IDD, pParent)
	, m_IPaddressGmes(0)
	, m_ServerPortNumber(_T(""))
	, m_EditCheckSum(_T(""))
	//, m_EditFreq[0](_T(""))
{

}

DlgModelSetupSeq::~DlgModelSetupSeq()
{
}

void DlgModelSetupSeq::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TEST_PROCESS, m_CtrlListTestProcess);
	//	DDX_Control(pDX, IDC_COMBO_MODEL, m_cSeqProcessCombo);
	DDX_Control(pDX, IDC_COMBO_RECOMON, m_cRemoconCombo);
	DDX_Control(pDX, IDC_COMBO_RECOMON2, m_cModelComboSeq);
	DDX_Control(pDX, IDC_LABEL_MODEL_NAME, m_TextModelName);


	DDX_Check(pDX, IDC_CHECK_MES_ENABLE, m_CheckMesEnable);	
	//DDX_Control(pDX, IDC_LABEL_MES_TNS, m_TextMesTns);
	//DDX_Control(pDX, IDC_LABEL_MES_AVN, m_TextMesAvn);
	//DDX_Control(pDX, IDC_LABEL_MES_USERID, m_TextMesUserID);
	//DDX_Control(pDX, IDC_LABEL_MES_PASSWORD, m_TextMesPassword);
	//DDX_Control(pDX, IDC_LABEL_MES_LINE, m_TextMesLine);
	//DDX_Control(pDX, IDC_LABEL_MES_INSP_STEP, m_TextMesInspStep);

	DDX_Control(pDX, IDC_COMBO_RMT_SEQ_TYPE, m_cComboRmtType);
	//DDX_IPAddress(pDX, IDC_IPADDRESS_GMES, m_IPaddressGmes);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT1, m_ServerPortNumber);
	DDX_Text(pDX, IDC_EDIT_CHECKSUM, m_EditCheckSum);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET1, m_EditFreq[0]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET2, m_EditFreq[1]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET3, m_EditFreq[2]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET4, m_EditFreq[3]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET5, m_EditFreq[4]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET6, m_EditFreq[5]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET7, m_EditFreq[6]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET8, m_EditFreq[7]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET9, m_EditFreq[8]);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET10, m_EditFreq[9]);

	DDX_Control(pDX, IDC_COMBO_MES_PORT_TYPE, m_cComboPortType);
	DDX_Control(pDX, IDC_COMBO_MODEL_PCB_TYPE, m_cComboModelPcbType);
	DDX_Control(pDX, IDC_COMBO_MODEL_BAUDRATE, m_cComboModelPcbBaud);
	DDX_Control(pDX, IDC_COMBO_MODEL_PARITY, m_cComboModelPcbParity);
	DDX_Control(pDX, IDC_COMBO_MODEL_PCB_PORT, m_cComboPCBModelPort);
	DDX_Control(pDX, IDC_COMBO_NG_RETRY_COUNT, m_cComboNGRetryCount);
}


BEGIN_MESSAGE_MAP(DlgModelSetupSeq, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT_CAMERA_IPADDRESS, &DlgModelSetupSeq::OnEnChangeEditCameraIpaddress)
	ON_CBN_SELCHANGE(IDC_COMBO_RECOMON2, &DlgModelSetupSeq::OnCbnSelchangeComboRecomon2)
	ON_BN_CLICKED(IDOK, &DlgModelSetupSeq::OnBnClickedOk)

	ON_MESSAGE(WM_COMM_RXCHAR_PCB,OnReceiveDataPCB)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &DlgModelSetupSeq::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_MES_PORT_TYPE, &DlgModelSetupSeq::OnCbnSelchangeComboMesPortType)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, &DlgModelSetupSeq::OnBnClickedButtonSaveas)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_PCB_PORT, &DlgModelSetupSeq::OnCbnSelchangeComboModelPcbPort)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_PCB_TYPE, &DlgModelSetupSeq::OnCbnSelchangeComboModelPcbType)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_BAUDRATE, &DlgModelSetupSeq::OnCbnSelchangeComboModelBaudrate)
	ON_CBN_SELCHANGE(IDC_COMBO_MODEL_PARITY, &DlgModelSetupSeq::OnCbnSelchangeComboModelParity)
END_MESSAGE_MAP()


// DlgModelSetupSeq 메시지 처리기입니다.
BOOL DlgModelSetupSeq::OnInitDialog()
{
    CDialog::OnInitDialog();
  
	//::m_bWindowOnly = TRUE;
	int lXpos = 0;
	int lYpos = 0;


	
	CString strTemp;
	CString strTempCom;
	CDlgConfig cfgdlg;
	cfgdlg.GetDeviceInfo();	
	m_cComboPCBModelPort.ResetContent();		

	//m_nPortPcb = g_nPort_Pcb;
	//m_nBaudPcb = gTestSeqData.nBaud_Pcb;
	//m_nParityPcb = gTestSeqData.nParity_Pcb;

	if(cfgdlg.m_PortCnt > 0)
	{
		for(int i = 0; i < cfgdlg.m_PortCnt; i++)
		{		
			strTemp = cfgdlg.strPort[i].Mid(cfgdlg.strPort[i].Find("COM")+3);
			strTemp = strTemp.Left(strTemp.Find(")"));

			strTempCom = cfgdlg.strPort[i].Mid(cfgdlg.strPort[i].Find("COM"));
			strTempCom = strTempCom.Left(strTempCom.Find(")"));				
			
			m_cComboPCBModelPort.AddString(strTempCom);

		
			nNumberPort[i] = _ttoi(strTemp);

			
			if(gTestSeqData.nPort_Pcb == nNumberPort[i])
			{
				m_cComboPCBModelPort.SetCurSel(i);
			}							
	
		}
				
	}
	else
	{
		MessageBox("COM Port NOT DETECTED.");
	}


//
	mbaud_List[0] = 9600;
	mbaud_List[1] = 19200;
	mbaud_List[2] = 38400;
	mbaud_List[3] = 57600;
	mbaud_List[4] = 115200;
	

	m_cComboModelPcbBaud.AddString("9600");
	m_cComboModelPcbBaud.AddString("19200");
	m_cComboModelPcbBaud.AddString("38400");
	m_cComboModelPcbBaud.AddString("57600");
	m_cComboModelPcbBaud.AddString("115200");
	m_cComboModelPcbBaud.SetCurSel(0);
	//for(int i = 0; i < 5; i++)
	//{
	//	if(m_nBaud == mbaud_List[i])
	//	{
	//		m_cComboBaud.SetCurSel(i);
	//	}
	//}

	m_cComboModelPcbParity.AddString("NONE");
	m_cComboModelPcbParity.AddString("EVEN");
	m_cComboModelPcbParity.AddString("ODD");
	m_cComboModelPcbParity.SetCurSel(0);

	



	m_cComboPortType.AddString("CM4/5");
	m_cComboPortType.AddString("CM8/9");
	m_cComboPortType.SetCurSel(0);

	m_cComboRmtType.AddString("IR REMOTE");
	m_cComboRmtType.AddString("CABLE WIRE");
	m_cComboRmtType.SetCurSel(0);

		
	m_cComboModelPcbType.AddString("01 : MCS");//
	m_cComboModelPcbType.AddString("02 : MTK");
	m_cComboModelPcbType.AddString("03 : BCM");
	m_cComboModelPcbType.SetCurSel(0);

	m_cComboNGRetryCount.SetCurSel(0);

	GetModelList();
	GetSeqList();
	GetRemoconList();


	m_TextModelName.put_Caption(gTestSeqData.strModelName);
	SetListControl();

	LoadTestData();

	DisplayTestData();

	SetTimer(1, 30, NULL);
	m_PCB_COM_PROCESS =  COM_MODE_IDLE;

	m_TestOrgSeqData = gTestSeqData;

    return TRUE;
}

void DlgModelSetupSeq::GetModelList()
{
	BOOL rtnValue = 0;
	
	CString pathName;
	CString fileName;

//	int lFileRename = 0;
	//CString PathNameList[200];
	CString fileNameList[2000];
	
	//CString titleNameList[200];
	//CString  accpathName;
	//CString  ukpathName;
	//CString  chkpathName;
	char lBuf[2048];
	char ltmpBuf[2048];


	int nFileCnt = 0;
	CString str;

	CFileFind finder;
	// build a string with wildcards   
	CString strWildcard;
		

	//int nIndexPos = 0;
	BOOL bFileFound = 0;
	//BOOL rtnValue = 0;
	CFileException ex;

   
	strWildcard = PATH_BASE_DIR;
	strWildcard += _T("\\Model\\*.mdl");//"C:\\Program Files\\SM Digital\\nagra\\HDCPKey"
  
	BOOL bWorking = finder.FindFile(strWildcard);
	
	nFileCnt = 0;
	bFileFound = 0;
	while (bWorking)
	{   
		bWorking = finder.FindNextFile();
		
		// skip . and .. files; otherwise, we'd
		// recur infinitely!!
		fileName = finder.GetFileName();
		//str = (LPCTSTR)finder.GetRoot();
		//str = finder.GetFileTitle();
		pathName = finder.GetFilePath();
		//str = finder.GetFileURL();
		//str = finder.GetFileName();

	//	PathNameList[nFileCnt] = pathName;
		fileNameList[nFileCnt] = fileName;
	//	titleNameList[nFileCnt] = finder.GetFileTitle();
			
		nFileCnt++;
		if(nFileCnt >= 1000)
		{
				
			break;
		}
		bFileFound = 1;
				
	}

	finder.Close();


	if(bFileFound)
	{
		int l_nModelSelNum = 0;
	/*	int litemcount = m_cModelComboSeq.GetCount();
		for(int i = 0; i < litemcount; i++)
		{
			m_cModelComboSeq.ResetContent();
		}*/
		
		m_cModelComboSeq.ResetContent();
		
		for(int i = 0 ; i < nFileCnt; i++)
		{
			m_strModelNameList[i] = fileNameList[i].Left(fileNameList[i].GetLength() - 4);

			m_cModelComboSeq.AddString(m_strModelNameList[i]);
		
			if(m_strModelNameList[i].Compare(gTestSeqData.strModelName) == 0)
			{
				l_nModelSelNum = i;
				//break;
			}
		}

		m_cModelComboSeq.SetCurSel(l_nModelSelNum);

	}
	else
	{
		MessageBox("Model Test File(*.mdl) Not Found!!");
	}
}

void DlgModelSetupSeq::GetSeqList()
{
	BOOL rtnValue = 0;
	
	CString pathName;
	CString fileName;

//	int lFileRename = 0;
	//CString PathNameList[200];
	CString fileNameList[1000];
	
	//CString titleNameList[200];
	//CString  accpathName;
	//CString  ukpathName;
	//CString  chkpathName;
	char lBuf[2048];
	char ltmpBuf[2048];


	int nFileCnt = 0;
	CString str;

	CFileFind finder;
	// build a string with wildcards   
	CString strWildcard;
		

	//int nIndexPos = 0;
	BOOL bFileFound = 0;
	//BOOL rtnValue = 0;
	CFileException ex;

   
	strWildcard = PATH_BASE_DIR;
	strWildcard += _T("\\Model\\*.seq");//"C:\\Program Files\\SM Digital\\nagra\\HDCPKey"
  
	BOOL bWorking = finder.FindFile(strWildcard);
	
	nFileCnt = 0;
	bFileFound = 0;
	while (bWorking)
	{   
		bWorking = finder.FindNextFile();
		
		// skip . and .. files; otherwise, we'd
		// recur infinitely!!
		fileName = finder.GetFileName();
		//str = (LPCTSTR)finder.GetRoot();
		//str = finder.GetFileTitle();
		pathName = finder.GetFilePath();
		//str = finder.GetFileURL();
		//str = finder.GetFileName();

	//	PathNameList[nFileCnt] = pathName;
		fileNameList[nFileCnt] = fileName;
	//	titleNameList[nFileCnt] = finder.GetFileTitle();
			
		nFileCnt++;
		if(nFileCnt >= 1000)
		{
				
			break;
		}
		bFileFound = 1;
				
	}

	finder.Close();


	if(bFileFound)
	{
		int l_nModelSelNum = 0;
		
		for(int i = 0 ; i < nFileCnt; i++)
		{
//			m_strModelSeqList[i] = fileNameList[i].Left(fileNameList[i].GetLength() - 4);
			m_strModelSeqList[i] = fileNameList[i];

		/*	m_cSeqProcessCombo.AddString(m_strModelSeqList[i]);
		
			if(m_strModelSeqList[i].Compare(gTestSeqData.strSeqFileName) == 0)
			{
				l_nModelSelNum = i;
			}*/
		}

	//	m_cSeqProcessCombo.SetCurSel(l_nModelSelNum);

	}
	else
	{
		MessageBox("Model Test File(*.seq) Not Found!!");
	}
}


void DlgModelSetupSeq::GetRemoconList()
{

	BOOL rtnValue = 0;
	
	CString pathName;
	CString fileName;

//	int lFileRename = 0;
	//CString PathNameList[200];
	CString fileNameList[1000];
	

//	CString m_strRemoconList[100];
//	int m_nRecomonCount = 0;
	//CString titleNameList[200];
	//CString  accpathName;
	//CString  ukpathName;
	//CString  chkpathName;
	char lBuf[2048];
	char ltmpBuf[2048];


	int nFileCnt = 0;
	CString str;

	CFileFind finder;
	// build a string with wildcards   
	CString strWildcard;
		

		//int nIndexPos = 0;
		BOOL bFileFound = 0;
		//BOOL rtnValue = 0;
		CFileException ex;

   
		strWildcard = PATH_BASE_DIR;
		strWildcard += _T("\\Remote\\*.rmt");//"C:\\Program Files\\SM Digital\\nagra\\HDCPKey"
  
		BOOL bWorking = finder.FindFile(strWildcard);
	
		nFileCnt = 0;
		bFileFound = 0;
		while (bWorking)
		{   
			bWorking = finder.FindNextFile();
		
			// skip . and .. files; otherwise, we'd
			// recur infinitely!!
			fileName = finder.GetFileName();
			//str = (LPCTSTR)finder.GetRoot();
			//str = finder.GetFileTitle();
			pathName = finder.GetFilePath();
			//str = finder.GetFileURL();
			//str = finder.GetFileName();

		//	PathNameList[nFileCnt] = pathName;
			fileNameList[nFileCnt] = fileName;
		//	titleNameList[nFileCnt] = finder.GetFileTitle();
			
			nFileCnt++;
			if(nFileCnt >= 100)
			{
				
				break;
			}
			bFileFound = 1;
				
		}

		finder.Close();


		if(bFileFound)
		{
			/*
			CString m_strRemoconList[100];
			int m_nRecomonCount = 0;
			*/
			g_nRemoconSelNum = 0;//g_strRemoconFileName
			m_nRecomonCount = nFileCnt;
			for(int i = 0 ; i < nFileCnt; i++)
			{
				m_strRemoconList[i] = fileNameList[i];
				m_cRemoconCombo.AddString(m_strRemoconList[i]);
				
				if(m_strRemoconList[i].Compare(gTestSeqData.strRemoconFileName) == 0)
				{
					g_nRemoconSelNum = i;
				}
			}

			m_cRemoconCombo.SetCurSel(g_nRemoconSelNum);
		}
		else
		{
			MessageBox("Remote Control File(*.rmt) Not Found!!");
		}
}


void DlgModelSetupSeq::SetListControl()
{
	
//	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListTestProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);// 리스트 컨트롤 초기화: 열 추가
	m_CtrlListTestProcess.InsertColumn(0, _T("No."), LVCFMT_CENTER, 40); 
	m_CtrlListTestProcess.InsertColumn(1, _T("TEST"), LVCFMT_CENTER, 150);// 리스트 행 추가
	m_CtrlListTestProcess.InsertColumn(2, _T("Discription"), LVCFMT_LEFT, 350);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(3, _T("Wait"), LVCFMT_LEFT, 50);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(4, _T("Time"), LVCFMT_CENTER, 70);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(5, _T("Ref1"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(6, _T("Ref2"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(7, _T("Value"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(8, _T("OK/NG"), LVCFMT_CENTER, 60);// 리스트 행 추가
	//m_CtrlListTestProcess.InsertColumn(9, _T("T/T"), LVCFMT_CENTER, 50);// 리스트 행 추가

	m_CtrlListTestProcess.InsertItem(0, _T("1"));   // 첫째행(0), 첫째열에 삽입
	m_CtrlListTestProcess.SetItem(0, 1, LVIF_TEXT, _T("FM TEST"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	m_CtrlListTestProcess.SetItem(0, 2, LVIF_TEXT, _T("97.8Hz"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 3, LVIF_TEXT, _T("2.5"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 4, LVIF_TEXT, _T("0.0"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 5, LVIF_TEXT, _T("0"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 6, LVIF_TEXT, _T("80%"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 7, LVIF_TEXT, _T("90%"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 
	//m_CtrlListTestProcess.SetItem(0, 8, LVIF_TEXT, _T("OK"), NULL, NULL, NULL, NULL);   // 첫째행(0), 둘째열(1)에 삽입 

	
	
	font = new CFont;
		//font->CreateFontA( 16,                          // nHeight
		//			   0,                          // nWidth
		//			   0,                          // nEscapement
		//			   0,                          // nOrientation
		//			   400,                           // nWeight
		//			   0,                          // bItalic
		//			   0,                          // bUnderline 
		//			   0,                          // cStrikeOut 
		//			   0,                          // nCharSet
		//			   0,           // nOutPrecision 
		//			   0,                          // nClipPrecision 
		//			 PROOF_QUALITY,              // nQuality
		//			 0,  // nPitchAndFamily 
		//			 _T("Arial"));                     // lpszFacename
	font->CreateFontA( 20,                          // nHeight
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
	//font->CreatePointFont(20,_T("Arial"));   
	m_CtrlListTestProcess.SetFont(font);

	delete font;
	
}


void DlgModelSetupSeq::SetSubListControl()//void DlgModelSetupSeq::SetListControl()
{
	
	CSize lSize;
	CString strTemp;

	m_CtrlListTestProcess.DeleteAllItems();
	
	for(int  i = 0; i < gTestSeqData.TestCnt; i++)
	{
		strTemp.Format(_T("%d"), i+1);
		m_CtrlListTestProcess.InsertItem(i, strTemp);   


		strTemp = gTestSeqData.TestStepList[i].strStepName;
		m_CtrlListTestProcess.SetItem(i, 1, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);
		strTemp = gTestSeqData.TestStepList[i].strStepWork;
		m_CtrlListTestProcess.SetItem(i, 2, LVIF_TEXT, strTemp, NULL, NULL, NULL, NULL);

		gTestSeqData.TestStepList[i].bEnable = 1;
		if(gTestSeqData.TestStepList[i].bEnable == 1)
		{
			m_CtrlListTestProcess.SetCheck(i,1);
		}
		else
		{
			m_CtrlListTestProcess.SetCheck(i,0);
		}
			
	}

	
	//gTestSeqData
	//CString lStr;
	//TestListTable_TYPE lTempList;

	//m_CtrlListTestProcess.DeleteAllItems();
	//
	//for(int  i = 0; i < gTestModel.m_ProcessCnt; i++)
	//{
	//	lTempList = gTestModel.m_TestList[i];
	//	lStr.Format(_T("%d"), i+1);
	//	m_CtrlListTestProcess.InsertItem(i, lStr);   // 첫째행(0), 첫째열에 삽입

	//	lTempList.m_Test_Enable = 1;
	//	if(lTempList.m_Test_Enable == 1)
	//	{
	//		m_CtrlListTestProcess.SetCheck(i,1);
	//	}
	//	else
	//	{
	//		m_CtrlListTestProcess.SetCheck(i,0);
	//	}
	//		

	//	m_CtrlListTestProcess.SetItem(i, 1, LVIF_TEXT, lTempList.s_TestName, NULL, NULL, NULL, NULL);  
	//	if(1)//lTempList.m_IPType == IP_TYPE_LAN)		
	//	{
	//		m_CtrlListTestProcess.SetItem(i, 2, LVIF_TEXT, _T("LAN"), NULL, NULL, NULL, NULL);  
	//	}
	//	else
	//	{
	//		m_CtrlListTestProcess.SetItem(i, 2, LVIF_TEXT, _T("Wifi"), NULL, NULL, NULL, NULL);  
	//	}
	//	lStr.Format(_T("%.1f"), lTempList.m_WaitTime/1000.0);
	//	m_CtrlListTestProcess.SetItem(i, 3, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL);   // 

	//	lStr.Format(_T("%.1f"), lTempList.m_TestTime/1000.0);
	//	m_CtrlListTestProcess.SetItem(i, 4, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL);   // 
	//	
	//	lStr.Format(_T("%.1f"), lTempList.m_RefVal_Min);
	//	m_CtrlListTestProcess.SetItem(i, 5, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL);   // 

	//	lStr.Format(_T("%.1f"), lTempList.m_RefVal_Max);		
	//	m_CtrlListTestProcess.SetItem(i, 6, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL); 


	//	//if((lTempList.m_RefVal_Min == 0) && (lTempList.m_RefVal_Min == 0))
	//	//{
	//	//	m_CtrlListTestProcess.SetItem(i, 6, LVIF_TEXT, _T("CHECK"), NULL, NULL, NULL, NULL);   
	//	//}
	//	//else
	//	//{
	//	//	if(0)//lTempList.m_ValueType == REF_TYPE_PERCENT)
	//	//	{
	//	//		lStr.Format(_T("%.1f%%"), lTempList.m_RefVal_Max);		
	//	//		m_CtrlListTestProcess.SetItem(i, 6, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL); 
	//	//	}
	//	//	else
	//	//	{
	//	//		lStr.Format(_T("%.1f"), lTempList.m_RefVal_Max);		
	//	//		m_CtrlListTestProcess.SetItem(i, 6, LVIF_TEXT, lStr, NULL, NULL, NULL, NULL); 
	//	//	}
	//	//}
	//}

	//mCheckAll = 1;
	m_CtrlListTestProcess.Invalidate();
}




BEGIN_EVENTSINK_MAP(DlgModelSetupSeq, CDialogEx)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_SEQ_LOAD, DISPID_CLICK, DlgModelSetupSeq::ClickButtonSeqLoad, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_SEQ_EDIT, DISPID_CLICK, DlgModelSetupSeq::ClickButtonSeqEdit, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_MODEL_CREATE, DISPID_CLICK, DlgModelSetupSeq::ClickButtonModelCreate, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_MODEL_SAVE, DISPID_CLICK, DlgModelSetupSeq::ClickButtonModelSave, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_MODEL_REMOVE, DISPID_CLICK, DlgModelSetupSeq::ClickButtonModelRemove, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_MODEL_CONFIG, DISPID_CLICK, DlgModelSetupSeq::ClickButtonModelConfig, VTS_NONE)
//	ON_EVENT(DlgModelSetupSeq, IDC_BUTTON_IMAGE_SET, DISPID_CLICK, DlgModelSetupSeq::ClickButtonImageSet, VTS_NONE)
	ON_EVENT(DlgModelSetupSeq, IDC_LABEL_CHECKSUM, DISPID_DBLCLICK, DlgModelSetupSeq::DblClickLabelChecksum, VTS_DISPATCH)
END_EVENTSINK_MAP()


void DlgModelSetupSeq::ClickButtonSeqLoad()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//CString lstrModelname  = _T("TEST");
	//CFileControl lFile;
	//lFile.OpenModelSeq(lstrModelname);

	LoadTestData();
	DisplayTestData();
}


void DlgModelSetupSeq::ClickButtonSeqEdit()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	char buf[1024];
	CString lstrModelname  = _T("TEST");
//	m_cSeqProcessCombo.GetLBText(m_cSeqProcessCombo.GetCurSel(), lstrModelname) ;
	
	int lpos = gTestSeqData.strSeqFileName.Find(".seq");
	if(gTestSeqData.strModelName.Compare(gTestSeqData.strSeqFileName.Left(lpos)) != 0)
	{
		if(lpos > 1)
		{
			CString Filename = PATH_BASE_DIR;
			Filename += _T("\\Model\\");
			Filename += gTestSeqData.strSeqFileName;

			CString FilenameNew = PATH_BASE_DIR;
			FilenameNew += _T("\\Model\\");
			FilenameNew += gTestSeqData.strModelName;
			FilenameNew += _T(".seq");

			if(!CopyFile(Filename, FilenameNew, 0))
			{
				//MessageBox("Copy File Fail!!");
			}
		}
		else
		{	
		
		}
		//CopyFile(
		//CFile LCtrfile(
		//CFile::Rename(pOldName, pNewName);
		//	CFile::Duplicate();	
		lstrModelname = gTestSeqData.strModelName;
		lstrModelname += ".seq";
		gTestSeqData.strSeqFileName  = lstrModelname;
		CFileControl lFile;
		if(lFile.SaveModel(gTestSeqData.strModelName))
		{
			MessageBox("File Save Error !!");
		}
	}




	lstrModelname = gTestSeqData.strSeqFileName;


	CString Filename = PATH_BASE_DIR;
	Filename += _T("\\Model\\");
	Filename += lstrModelname;
//	Filename +=  _T(".seq");

	sprintf(buf, "C:\\WINDOWS\\system32\\notepad.exe %s" ,Filename.GetBuffer());
//	sprintf(buf, "%ws" ,m_openFile.GetBuffer());
	WinExec(buf,SW_SHOW);
//	ShellExecute( "open", "http://www.tipssoft.com", "", "", SW_SHOW);

}

void DlgModelSetupSeq::LoadTestData()
{
	//m_cSeqProcessCombo.getm_cSeqProcessCombo.GetCurSel();
	//CString lstrModelname  = _T("TEST");


	CString lstrModelSeqname;
	//m_cModelCombo.GetWindowTextA(lstrModelname, 64);
	//m_cSeqProcessCombo.GetLBText(m_cSeqProcessCombo.GetCurSel(), lstrModelSeqname) ;
	lstrModelSeqname = gTestSeqData.strSeqFileName;


	int lpos = gTestSeqData.strSeqFileName.Find(".seq");
	if(gTestSeqData.strModelName.Compare(gTestSeqData.strSeqFileName.Left(lpos)) != 0)
	{
		if(lpos > 1)
		{
			CString Filename = PATH_BASE_DIR;
			Filename += _T("\\Model\\");
			Filename += gTestSeqData.strSeqFileName;

			CString FilenameNew = PATH_BASE_DIR;
			FilenameNew += _T("\\Model\\");
			FilenameNew += gTestSeqData.strModelName;
			FilenameNew += _T(".seq");

			if(!CopyFile(Filename, FilenameNew, 0))
			{
				//MessageBox("Copy File Fail!!");
			}
		//	CString Filename;
			Filename = gTestSeqData.strModelName;
			Filename += ".seq";
			gTestSeqData.strSeqFileName  = Filename; 
			lstrModelSeqname = gTestSeqData.strSeqFileName;
		}
	
	}

	CFileControl lFile;
	lFile.OpenModelSeq(lstrModelSeqname);

	
}


void DlgModelSetupSeq::DisplayTestData()
{
	SetSubListControl();
	
	for(int i = 0 ; i < m_nRecomonCount; i++)
	{				
		//m_cRemoconCombo.AddString(m_strRemoconList[i]);				
		if(m_strRemoconList[i].Compare(gTestSeqData.strRemoconFileName) == 0)
		{
			g_nRemoconSelNum = i;
		}
	}

	m_cRemoconCombo.SetCurSel(g_nRemoconSelNum);
	m_cComboModelPcbType.SetCurSel(gTestSeqData.nComPcbType);

	//m_cComboPCBModelPort.SetCurSel(gTestSeqData.nPort_Pcb);

	m_cComboNGRetryCount.SetCurSel(gTestSeqData.nNGRetryCount);

	//	m_cComboModelPcbBaud.AddString("9600");
	//m_cComboModelPcbBaud.AddString("19200");
	//m_cComboModelPcbBaud.AddString("38400");
	//m_cComboModelPcbBaud.AddString("57600");
	//m_cComboModelPcbBaud.AddString("115200");
	//m_cComboModelPcbBaud.SetCurSel(0);

	for(int i = 0; i < 5; i++)
	{
		if(gTestSeqData.nBaud_Pcb == mbaud_List[i])
		{
			m_cComboModelPcbBaud.SetCurSel(i);
		}
	}

	//m_cComboModelPcbParity.AddString("NONE");
	//m_cComboModelPcbParity.AddString("EVEN");
	//m_cComboModelPcbParity.AddString("ODD");
	m_cComboModelPcbParity.SetCurSel(gTestSeqData.nParity_Pcb);
	//	sprintf(lbuf,"PCB TYPE= %d\n", gTestSeqData.nComPcbType);// m_cComboModelPcbType

	m_CheckMesEnable = gTestSeqData.bMesEnable;
	m_cComboPortType.SetCurSel( g_nRemotePortType);



	m_TextModelName.put_Caption(gTestSeqData.strModelName);
	if(g_nRemotePortType == 1)
	{
		m_ServerPortNumber.Format(_T("%d"), g_nRemotePortNumberCM89);
	}
	else
	{
		m_ServerPortNumber.Format(_T("%d"), g_nRemotePortNumberCM45);
	}

	for(int i = 0; i < 10; i++)
	{
		m_EditFreq[i].Format(_T("%d"),  gTestSeqData.Frequency[i]);
	}

	if(gTestSeqData.CheckSum[2] == 0)
	{
		m_EditCheckSum.Format(_T("0x%02X 0x%02X"), gTestSeqData.CheckSum[0], gTestSeqData.CheckSum[1]);
	}
	else
	{
		m_EditCheckSum.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), gTestSeqData.CheckSum[0], gTestSeqData.CheckSum[1], gTestSeqData.CheckSum[2], gTestSeqData.CheckSum[3]);
		CString str;
		BYTE lbuf[5];
		lbuf[4] = 0;
		memcpy(lbuf, &(gTestSeqData.CheckSum[0]), 4);
		str = lbuf;
		SetDlgItemText(IDC_DISPLAY_CHECKSUM, str);
	}



	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT_IPADDRESS_GMES1, g_nRemoteIPAddress);	
	//SetDlgItemText( IDC_EDIT_CAMERA_IPADDRESS, gTestSeqData.strCameraIPAddress);
	//SetDlgItemText( IDC_IPADDRESS_CAMERA, gTestSeqData.strCameraIPAddress);
}


//void CDlgModelSetup::ClickButtonModelSave()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//
//	SaveModel(gTestSeqData.strModelName);//gTestSeqData
//}

bool DlgModelSetupSeq::NameListCheckAndADD(CString lCheckName)
{
	CString str;
	for(int i = 0; i <  m_cModelComboSeq.GetCount(); i++)
	{
		m_cModelComboSeq.GetLBText(i, str);
		if(str.Compare(lCheckName) == 0)
		{
			return 1;
		}
	}
	m_cModelComboSeq.AddString(lCheckName);
	
	return 0;
}


void DlgModelSetupSeq::ClickButtonModelCreate()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDlgNewModelName lDlg;

	if(lDlg.DoModal() == IDOK)
	{
		if(lDlg.m_NewName.GetLength() < 3)
		{
			MessageBox("New Name Is Too Short !!");
			return;
		}

		for(int i = 0 ; i < lDlg.m_NewName.GetLength(); i++)
		{
			if((lDlg.m_NewName.GetAt(i) == ' ')||(lDlg.m_NewName.GetAt(i) == '\t'))
			{
				lDlg.m_NewName.SetAt(i, '_');
			}
		}

		if(NameListCheckAndADD(lDlg.m_NewName))
		{
			int lok = MessageBoxA(_T("New Name Is IN MODEL LIST !!") , _T("Used Found"), MB_YESNO |MB_DEFBUTTON2  );
			if(IDYES != lok)
			{
				return;
			}
		}

		SaveModel(lDlg.m_NewName);
		gTestSeqData.strModelName = lDlg.m_NewName;
		m_cModelComboSeq.SetCurSel(m_cModelComboSeq.GetCount()-1);

		LoadTestData();
		DisplayTestData();

	}
}


void DlgModelSetupSeq::ClickButtonModelSave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveModel(gTestSeqData.strModelName);
}


void DlgModelSetupSeq::ClickButtonModelRemove()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int lOk = MessageBox(_T("Remove Current Model and Erase All of Current Model Data!! \r\n\r\nContinue Remove??"), _T("REMOVE MODEL"), MB_YESNO | MB_DEFBUTTON2);
	if(lOk == IDYES)
	{
		CString lstrModelName;
		CFileControl lFile;
		m_cModelComboSeq.GetLBText(m_cModelComboSeq.GetCurSel(),lstrModelName);
		lFile.RemoveModel(lstrModelName);
		m_cModelComboSeq.DeleteString(m_cModelComboSeq.GetCurSel());
		
	
		m_cModelComboSeq.SetCurSel(0);
		LoadTestData();
		DisplayTestData();
	}
	else
	{
		MessageBox(_T("Cancelled Remove Current Model !!"));
	}
}



void DlgModelSetupSeq::SaveModel(CString lFilename)//gTestSeqData
{
	
	int lError = UpdateTestData();
	if(lError)
		return;

	CFileControl lFile;

	if(lFile.SaveModel(lFilename))
	{
		MessageBox("File Save Error!!");
	}
//	CFileControl lFile;
	lFile.SaveINIModel();
	m_TestOrgSeqData = gTestSeqData;
}

int  DlgModelSetupSeq::UpdateTestData()//gTestSeqData
{
	UpdateData();

	CString lstrModelName;	
	m_cModelComboSeq.GetLBText(m_cModelComboSeq.GetCurSel(),lstrModelName);
	gTestSeqData.strModelName = lstrModelName;

	//m_cSeqProcessCombo.GetLBText(m_cSeqProcessCombo.GetCurSel(),lstrModelName);
	int lpos = gTestSeqData.strSeqFileName.Find(".seq");
	if(gTestSeqData.strModelName.Compare(gTestSeqData.strSeqFileName.Left(lpos)) != 0)
	{
		if(lpos > 1)
		{
			CString Filename = PATH_BASE_DIR;
			Filename += _T("\\Model\\");
			Filename += gTestSeqData.strSeqFileName;

			CString FilenameNew = PATH_BASE_DIR;
			FilenameNew += _T("\\Model\\");
			FilenameNew += gTestSeqData.strModelName;
			FilenameNew += _T(".seq");

			if(!CopyFile(Filename, FilenameNew, 0))
			{
			//	MessageBox("Copy File Fail!!");
			}
		}
		else
		{	
		
		}
		//CopyFile(
		//CFile LCtrfile(
		//CFile::Rename(pOldName, pNewName);
		lstrModelName = gTestSeqData.strModelName;
		lstrModelName += ".seq";
		gTestSeqData.strSeqFileName  = lstrModelName;		
	}

	CFileControl lFile;
	//if(lFile.SaveModel(gTestSeqData.strModelName))
	//{
	//	MessageBox("File Save Error !!");
	//}
	CString str1, str2;
	str1 = m_EditCheckSum;
	str1.MakeUpper();
	lpos = str1.Find("0X");
	if(lpos  >= 0)
	{
	//	str1.Find("0/X");				
		gTestSeqData.CheckSum[0] = lFile.ReadHex(str1);
		str1 = str1.Mid(lpos+4);
	}

	lpos = str1.Find("0X");
	if(lpos  >= 0)
	{
	//	str1.Find("0/X");				
		gTestSeqData.CheckSum[1] = lFile.ReadHex(str1);	
		str1 = str1.Mid(lpos+4);
	}

	lpos = str1.Find("0X");
	if(lpos  >= 0)
	{
			
		gTestSeqData.CheckSum[2] = lFile.ReadHex(str1);		
		str1 = str1.Mid(lpos+4);
	
		lpos = str1.Find("0X");
		if(lpos  >= 0)
		{
					
			gTestSeqData.CheckSum[3] = lFile.ReadHex(str1);		
		
		}
		else
		{
			MessageBox("CHECKSUM Error!!");
		}
	}
	else
	{
		gTestSeqData.CheckSum[2] = 0;
		gTestSeqData.CheckSum[3] = 0;
	}

	for(int i = 0; i < 10; i++)
	{
		gTestSeqData.Frequency[i] = _ttoi(m_EditFreq[i]);
	}

	m_cRemoconCombo.GetLBText(m_cRemoconCombo.GetCurSel(),lstrModelName);
	gTestSeqData.strRemoconFileName = lstrModelName;

	gTestSeqData.nRemoconSigType = m_cComboRmtType.GetCurSel();
	gTestSeqData.bMesEnable = m_CheckMesEnable;

	g_nRemotePortType = m_cComboPortType.GetCurSel( );

	
	gTestSeqData.nComPcbType = m_cComboModelPcbType.GetCurSel( );
	gTestSeqData.nNGRetryCount = m_cComboNGRetryCount.GetCurSel( );

	gTestSeqData.nPort_Pcb = 	nNumberPort[m_cComboPCBModelPort.GetCurSel()];
//m_cComboPCBModelPort.GetCurSel( );

	UINT lBaud = mbaud_List[m_cComboModelPcbBaud.GetCurSel()];
	if((lBaud >= 9600)&&(lBaud <= 115200))
	{
		gTestSeqData.nBaud_Pcb = lBaud;	
	}

	UINT lParity = m_cComboModelPcbParity.GetCurSel();
	if((lParity >= 0)&&(lParity <= 2))
	{
		gTestSeqData.nParity_Pcb = lParity;	
	}

	
	//m_cComboModelPcbType.SetCurSel(gTestSeqData.nComPcbType);
	//	sprintf(lbuf,"PCB TYPE= %d\n", gTestSeqData.nComPcbType);// m_cComboModelPcbType



	//CString str;
	//GetDlgItemText(IDC_EDIT_CAMERA_IPADDRESS, gTestSeqData.strCameraIPAddress);
//GetDlgItemText(IDC_EDIT_CAMERA_IPADDRESS, gTestSeqData.strCameraIPAddress);
//	GetDlgItemText(IDC_IPADDRESS_CAMERA, gTestSeqData.strCameraIPAddress);

	//GetDlgItemText(IDC_IPADDRESS_GMES1, g_nRemoteIPAddress);	
	//g_nRemoteIPAddress = m_IPaddressGmes;
	//g_nRemotePortNumber = _ttoi(m_ServerPortNumber);




	return 0;
}

void DlgModelSetupSeq::GetRmtCodeList(CString lRmtFile)//gTestSeqData.strRemoconFileName;
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	FILE *m_fp;
	CString str;
	CString Filename;
	char lbuf[1024];
	char lTemp_Company[64];
	char lTemp_Code[64];
	char lTemp_Repeat[64];
	char lTemp_Name[64];
	char lTemp_Discription[129];

	

	str = PATH_BASE_DIR;
	str += _T("\\Remote\\");
	str += lRmtFile;//gTestSeqData.strRemoconFileName;
	
	// 파일경로 가져오기    
	 
	Filename = str;
		
	fopen_s(&m_fp, (LPCSTR)Filename, "r");
	if(m_fp)
	{
		m_RemoconModel.m_Cnt = 0;
		//memset(&m_RemoconModel, 0, sizeof(Recomon_ModelT));
		while(fgets(lbuf, 1024, m_fp) != NULL) 
		{
			if(lbuf[0] == '[')
			{
				continue;
			}
			if(strlen(lbuf) < 16)
			{
				break;
			}
			sscanf_s(lbuf, "%s %s %s %s", lTemp_Company,32, lTemp_Code,32,lTemp_Repeat,32, lTemp_Name,32);
			if(lTemp_Company[strlen(lTemp_Company)-1] == ',')
			{
				lTemp_Company[strlen(lTemp_Company)-1] = 0 ;
			}
				
			if(lTemp_Code[strlen(lTemp_Code)-1] == ',')
			{
				lTemp_Code[strlen(lTemp_Code)-1] = 0 ;
			}
				
			if(lTemp_Repeat[strlen(lTemp_Repeat)-1] == ',')
			{
				lTemp_Repeat[strlen(lTemp_Repeat)-1] = 0; 
			}

			if(lTemp_Name[strlen(lTemp_Name)-1] == ',')
			{
				lTemp_Name[strlen(lTemp_Name)-1] = 0;
			}

			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Company.Format(_T("%s"),lTemp_Company);
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Code.Format(_T("%s"),lTemp_Code); 
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Repeat = atoi(lTemp_Repeat);
			m_RemoconModel.Data[m_RemoconModel.m_Cnt].m_Name.Format(_T("%s"),lTemp_Name); 
			m_RemoconModel.m_Cnt++;	
			if(m_RemoconModel.m_Cnt >= 200)
			{
				break;
			}
		}
					

		fclose(m_fp);	
		SetDlgItemText(IDC_STATIC_RMT_FILE, Filename);
		
		//m_cComboRmtCode.ResetContent();
		//
		//for(int i = 0; i < m_RemoconModel.m_Cnt; i++)
		//{
		//	/*str = m_RemoconModel.Data[i].m_Company;
		//	str += _T(" : "); */
		//	str = m_RemoconModel.Data[i].m_Name;
		//	m_cComboRmtCode.AddString(str);
		//}
		//m_cComboRmtCode.SetCurSel(0);	
		
	} 
}


void DlgModelSetupSeq::ClickButtonModelConfig()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//#include "DlgPassword.h"
	/*CFileControl lFile;
	#include "DlgConfig.h"
	extern UINT g_nPort_Set;
extern UINT g_nBaud_Set;
extern CString g_strPassword;
extern CString g_strMesTns;
extern CString g_strMesAvn;
extern CString g_strMesUserID;
extern CString g_strMesPassword;
	lFile*/
	CFileControl lFile;


#if 1
	CDlgConfig dlg;
						
	dlg.m_nBaud = g_nBaud_Set;
	dlg.m_nPort = g_nPort_Set;
	dlg.m_nParity = g_nParity_Set;

	dlg.m_nBaudPcb = gTestSeqData.nBaud_Pcb;//, lParityChar[gTestSeqData.nParity_Pcb]g_nBaud_Pcb;
	dlg.m_nPortPcb = gTestSeqData.nPort_Pcb;
	dlg.m_nParityPcb = gTestSeqData.nParity_Pcb;//g_nParity_Pcb;

	dlg.m_nBaudLED = g_nBaud_LED;
	dlg.m_nPortLED = g_nPort_LED;
	dlg.m_nParityLED = g_nParity_LED;

	dlg.m_nPortScan  = g_nPort_Scanner;
	dlg.m_nBaudScan  = g_nBaud_Scanner;
	dlg.m_nParityScan =  g_nParity_Scanner;
	dlg.m_CheckUseUSB_Scanner = g_CheckUseUSB_Scanner;
	dlg.m_nNI_CardSel = g_nNI_CardSel;

	dlg.m_IPaddressGmes = g_nRemoteIPAddress;
	//dlg.m_PortNumber.Format(_T("%d"),g_nLocalPortNumber);
	dlg.m_ServerPortNumberCM45.Format(_T("%d"),g_nRemotePortNumberCM45);
	dlg.m_ServerPortNumberCM89.Format(_T("%d"),g_nRemotePortNumberCM89);
	//dlg.m_EditMesTnsTimeout.Format(_T("%d"),g_nTransTimeOut);
	//dlg.m_EditMesAvnReplyTimeout.Format(_T("%d"),g_nReplyTimeOut);
	//dlg.m_EditMesUserID_CEID =  g_strEQPID;
	//dlg.m_EditMesPswrdRPTID = g_strORGID;
	//dlg.m_EditMesLine =  g_strLineID;
	//dlg.m_EditMesInspStep = g_strProcID;

	if(dlg.DoModal()==IDOK)
	{

		g_nBaud_Set = dlg.m_nBaud     ;
		g_nPort_Set = dlg.m_nPort     ;
		g_nParity_Set = dlg.m_nParity   ;

		//g_nBaud_Pcb = dlg.m_nBaudPcb  ;
		//gTestSeqData.nPort_Pcb = dlg.m_nPortPcb  ;
		//g_nParity_Pcb = dlg.m_nParityPcb;

		g_nBaud_LED = dlg.m_nBaudLED  ;
		g_nPort_LED = dlg.m_nPortLED  ;
		g_nParity_LED = dlg.m_nParityLED;

		g_nPort_Scanner = dlg.m_nPortScan		;
		g_nBaud_Scanner = dlg.m_nBaudScan		;
		g_nParity_Scanner = dlg.m_nParityScan	;
		g_CheckUseUSB_Scanner = dlg.m_CheckUseUSB_Scanner;
		g_nNI_CardSel = dlg.m_nNI_CardSel;


		g_nRemoteIPAddress = dlg.m_IPaddressGmes;
		//g_nLocalPortNumber = _ttoi(dlg.m_PortNumber);
		g_nRemotePortNumberCM45 = _ttoi(dlg.m_ServerPortNumberCM45);
		g_nRemotePortNumberCM89 = _ttoi(dlg.m_ServerPortNumberCM89);
		if(g_nRemotePortType == LINE_CM89)
		{
			g_nRemotePortNumber = g_nRemotePortNumberCM89;
		}
		else
		{
			g_nRemotePortNumber =  g_nRemotePortNumberCM45;
		}
		OnCbnSelchangeComboMesPortType();
		SetDlgItemText(IDC_EDIT_IPADDRESS_GMES1, g_nRemoteIPAddress);	
	
		//g_nTransTimeOut = _ttoi(dlg.m_EditMesTnsTimeout);
		//g_nReplyTimeOut = _ttoi(dlg.m_EditMesAvnReplyTimeout);
		//g_strEQPID = dlg.m_EditMesUserID_CEID  ;
		//g_strORGID = dlg.m_EditMesPswrdRPTID ;
		//g_strLineID = dlg.m_EditMesLine  ;
		//g_strProcID = dlg.m_EditMesInspStep ;

		lFile.SaveConfigSeqData();

		//m_TextMesTns.put_Caption(g_strMesTns);
		//m_TextMesAvn.put_Caption(g_strMesAvn);
		//m_TextMesUserID.put_Caption(g_strMesUserID);
		//m_TextMesPassword.put_Caption(g_strMesPassword);
		//m_TextMesLine.put_Caption(g_strMesLine);
		//m_TextMesInspStep.put_Caption(g_strMesInspStep);
	}	

#else

	CDlgPassword dlgpw;

	dlgpw.m_sPassword = g_strPassword;

	if(dlgpw.DoModal()==IDOK)
	{
		//m_sPassword.Compare(
		//if(strncmp(m_sPassword.GetBuffer(),dlgpw.m_EditCurrentPW.GetBuffer(), m_sPassword.GetLength()) == 0)
	/*	}
		else
		{
			g_strPassword = dlgpw.m_sPassword;
			lFile.SaveConfigSeqData();
		}*/
		if(g_strPassword == dlgpw.m_sPassword)
		{
			CDlgConfig dlg;
						
			dlg.m_nBaud = g_nBaud_Set;
			dlg.m_nPort = g_nPort_Set;
			dlg.m_nParity = g_nParity_Set;

			dlg.m_nBaudPcb = gTestSeqData.nBaud_Pcb;//, lParityChar[gTestSeqData.nParity_Pcb]g_nBaud_Pcb;
			dlg.m_nPortPcb = gTestSeqData.nPort_Pcb;
			dlg.m_nParityPcb = gTestSeqData.nParity_Pcb;//g_nParity_Pcb;

			dlg.m_nBaudLED = g_nBaud_LED;
			dlg.m_nPortLED = g_nPort_LED;
			dlg.m_nParityLED = g_nParity_LED;

			dlg.m_nPortScan  = g_nPort_Scanner;
			dlg.m_nBaudScan  = g_nBaud_Scanner;
			dlg.m_nParityScan =  g_nParity_Scanner;
			dlg.m_CheckUseUSB_Scanner = g_CheckUseUSB_Scanner;
			dlg.m_nNI_CardSel = g_nNI_CardSel;

			dlg.m_IPaddressGmes = g_nRemoteIPAddress;
			//dlg.m_PortNumber.Format(_T("%d"),g_nLocalPortNumber);
			dlg.m_ServerPortNumberCM45.Format(_T("%d"),g_nRemotePortNumberCM45);
			dlg.m_ServerPortNumberCM89.Format(_T("%d"),g_nRemotePortNumberCM89);
			//dlg.m_EditMesTnsTimeout.Format(_T("%d"),g_nTransTimeOut);
			//dlg.m_EditMesAvnReplyTimeout.Format(_T("%d"),g_nReplyTimeOut);
			//dlg.m_EditMesUserID_CEID =  g_strEQPID;
			//dlg.m_EditMesPswrdRPTID = g_strORGID;
			//dlg.m_EditMesLine =  g_strLineID;
			//dlg.m_EditMesInspStep = g_strProcID;

			if(dlg.DoModal()==IDOK)
			{

				g_nBaud_Set = dlg.m_nBaud     ;
				g_nPort_Set = dlg.m_nPort     ;
				g_nParity_Set = dlg.m_nParity   ;

				//g_nBaud_Pcb = dlg.m_nBaudPcb  ;
				//gTestSeqData.nPort_Pcb = dlg.m_nPortPcb  ;
				//g_nParity_Pcb = dlg.m_nParityPcb;

				g_nBaud_LED = dlg.m_nBaudLED  ;
				g_nPort_LED = dlg.m_nPortLED  ;
				g_nParity_LED = dlg.m_nParityLED;

				g_nPort_Scanner = dlg.m_nPortScan		;
				g_nBaud_Scanner = dlg.m_nBaudScan		;
				g_nParity_Scanner = dlg.m_nParityScan	;
				g_CheckUseUSB_Scanner = dlg.m_CheckUseUSB_Scanner;
				g_nNI_CardSel = dlg.m_nNI_CardSel;


				g_nRemoteIPAddress = dlg.m_IPaddressGmes;
				//g_nLocalPortNumber = _ttoi(dlg.m_PortNumber);
				g_nRemotePortNumberCM45 = _ttoi(dlg.m_ServerPortNumberCM45);
				g_nRemotePortNumberCM89 = _ttoi(dlg.m_ServerPortNumberCM89);
				if(g_nRemotePortType == LINE_CM89)
				{
					g_nRemotePortNumber = g_nRemotePortNumberCM89;
				}
				else
				{
					g_nRemotePortNumber =  g_nRemotePortNumberCM45;
				}
				OnCbnSelchangeComboMesPortType();
				SetDlgItemText(IDC_EDIT_IPADDRESS_GMES1, g_nRemoteIPAddress);	
	
				//g_nTransTimeOut = _ttoi(dlg.m_EditMesTnsTimeout);
				//g_nReplyTimeOut = _ttoi(dlg.m_EditMesAvnReplyTimeout);
				//g_strEQPID = dlg.m_EditMesUserID_CEID  ;
				//g_strORGID = dlg.m_EditMesPswrdRPTID ;
				//g_strLineID = dlg.m_EditMesLine  ;
				//g_strProcID = dlg.m_EditMesInspStep ;

				lFile.SaveConfigSeqData();

				//m_TextMesTns.put_Caption(g_strMesTns);
				//m_TextMesAvn.put_Caption(g_strMesAvn);
				//m_TextMesUserID.put_Caption(g_strMesUserID);
				//m_TextMesPassword.put_Caption(g_strMesPassword);
				//m_TextMesLine.put_Caption(g_strMesLine);
				//m_TextMesInspStep.put_Caption(g_strMesInspStep);
			}
		}
		else
		{
			g_strPassword = dlgpw.m_sPassword;
			lFile.SaveConfigSeqData();
		}
	}
#endif
}


//
//void DlgModelSetupSeq::ClickButtonImageSet()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	//if(g_CameraFound == 1)
//	//{
//	//	CDlgImage ldlg;
//	//	ldlg.DoModal();
//	//}
//	//else
//	//{
//	//	//MessageBox("Camrea Not Connected!");
//	//}
//}



void DlgModelSetupSeq::OnCbnSelchangeComboRecomon2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	int lid = m_cModelComboSeq.GetCurSel();

	
	CString lstrModelname;	
	m_cModelComboSeq.GetLBText(m_cModelComboSeq.GetCurSel(), lstrModelname) ;
	gTestSeqData.strModelName = lstrModelname;


	CFileControl lFile;
//	lFile.SaveINIModel();
	m_TextModelName.put_Caption(gTestSeqData.strModelName);

	lFile.OpenModel(lstrModelname);

//	gTestSeqData.bMesEnable = 0;


//	int l_nModelSelNum = 0;
//		
//	for(int i = 0 ; i < m_cSeqProcessCombo.GetCount(); i++)
//	{
////			m_strModelSeqList[i] = fileNameList[i].Left(fileNameList[i].GetLength() - 4);
////		m_strModelSeqList[i] = fileNameList[i];
//
////		m_cSeqProcessCombo.AddString(m_strModelSeqList[i]);
//		m_cSeqProcessCombo.GetLBText(i, lstrModelname) ;
//		if(lstrModelname.Compare(gTestSeqData.strSeqFileName) == 0)
//		{
//			l_nModelSelNum = i;
//		}
//	}
//	if(l_nModelSelNum < m_cSeqProcessCombo.GetCount())
//		m_cSeqProcessCombo.SetCurSel(l_nModelSelNum);

	//GetSeqList();
	//GetRemoconList();


//	m_TextModelName.put_Caption(gTestSeqData.strModelName);
// m_TextModelName.put_Caption(gTestSeqData.strModelName);

	//SetListControl();

//	LoadTestData();

//	DisplayTestData();
	LoadTestData();

	DisplayTestData();
}


/** \file FileOperations.h                   
   Project: FopDemo\n
   Project type: MFC App\n
   Author: Vinnichenko Alexey\n
   E-mail: subj@mail.ru\n
   Description: Declaration of CFileOperation class and CFileExeption class.
*/ 

//#include "resource.h"
//
//#define PATH_ERROR   -1
//#define PATH_NOT_FOUND  0
//#define PATH_IS_FILE  1
//#define PATH_IS_FOLDER  2
//
//
//class CFExeption
//{
//public:
// CFExeption(DWORD dwErrCode);
// CFExeption(CString sErrText);
// CString GetErrorText() {return m_sError;}
// DWORD GetErrorCode() {return m_dwError;}
//
//private:
// CString m_sError;
// DWORD m_dwError;
//};
//
//
////*****************************************************************************************************
//
//class CFileOperation
//{
//public:
// CFileOperation(); // constructor
// bool Delete(CString sPathName); // delete file or folder
// bool Copy(CString sSource, CString sDest); // copy file or folder
// bool Replace(CString sSource, CString sDest); // move file or folder
// bool Rename(CString sSource, CString sDest); // rename file or folder
// CString GetErrorString() {return m_sError;} // return error description
// DWORD GetErrorCode() {return m_dwError;} // return error code
// void ShowError() // show error message
//  {MessageBox(NULL, m_sError, _T("Error"), MB_OK | MB_ICONERROR);}
// void SetAskIfReadOnly(bool bAsk = true) // sets behavior with readonly files(folders)
//  {m_bAskIfReadOnly = bAsk;}
// bool IsAskIfReadOnly() // return current behavior with readonly files(folders)
//  {return m_bAskIfReadOnly;}
// bool CanDelete(CString sPathName); // check attributes
// void SetOverwriteMode(bool bOverwrite = false) // sets overwrite mode on/off
//  {m_bOverwriteMode = bOverwrite;}
// bool IsOverwriteMode() {return m_bOverwriteMode;} // return current overwrite mode
// int CheckPath(CString sPath);
// bool IsAborted() {return m_bAborted;}
//
//protected:
// void DoDelete(CString sPathName);
// void DoCopy(CString sSource, CString sDest, bool bDelteAfterCopy = false);
// void DoFileCopy(CString sSourceFile, CString sDestFile, bool bDelteAfterCopy = false);
// void DoFolderCopy(CString sSourceFolder, CString sDestFolder, bool bDelteAfterCopy = false);
// void DoRename(CString sSource, CString sDest);
// bool IsFileExist(CString sPathName);
// void PreparePath(CString &sPath);
// void Initialize();
// void CheckSelfRecursion(CString sSource, CString sDest);
// bool CheckSelfCopy(CString sSource, CString sDest);
// CString ChangeFileName(CString sFileName);
// CString ParseFolderName(CString sPathName);
//
//private:
// CString m_sError;
// DWORD m_dwError;
// bool m_bAskIfReadOnly;
// bool m_bOverwriteMode;
// bool m_bAborted;
// int m_iRecursionLimit;
//};
//
//
////*****************************************************************************************************
//
// 
//
// 
//
// 
//
// 
//
// 
//
// 
//
// 
//
// 
//
// 
//
///** \file FileOperations.cpp
//   Project: FopDemo\n
//   Project type: MFC App\n
//   Author: Vinnichenko Alexey\n
//   E-mail: subj@mail.ru\n
//   Description: Implementation of CFileOperation class and CFileExeption class.
//*/ 
//
//#include "stdafx.h" 
//#include "resource.h" 
//#include "FileOperations.h" 
//#include "TypeCastFuncs.h"
//
////************************************************************************************************************
//CFExeption::CFExeption(DWORD dwErrCode)
//{
// LPVOID lpMsgBuf;
// FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//         NULL, dwErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
// m_sError = (LPTSTR)lpMsgBuf;
// LocalFree(lpMsgBuf);
// m_dwError = dwErrCode;
//}
//CFExeption::CFExeption(CString sErrText)
//{
// m_sError = sErrText;
// m_dwError = 0;
//}
//
//
////************************************************************************************************************
//
//CFileOperation::CFileOperation()
//{
// Initialize();
//}
//
//
//void CFileOperation::Initialize()
//{
// m_sError = _T("No error");
// m_dwError = 0;
// m_bAskIfReadOnly = true;
// m_bOverwriteMode = false;
// m_bAborted = false;
// m_iRecursionLimit = -1;
//}
//
//
//void CFileOperation::DoDelete(CString sPathName)
//{
// CFileFind ff;
// CString sPath = sPathName;
//
// if (CheckPath(sPath) == PATH_IS_FILE)
// {
//  if (!CanDelete(sPath)) 
//  {
//   m_bAborted = true;
//   return;
//  }
//  if (!DeleteFile(sPath)) throw new CFExeption(GetLastError());
//  return;
// }
//
// PreparePath(sPath);
// sPath += "*.*";
//
// BOOL bRes = ff.FindFile(sPath);
// while(bRes)
// {
//  bRes = ff.FindNextFile();
//  if (ff.IsDots()) continue;
//  if (ff.IsDirectory())
//  {
//   sPath = ff.GetFilePath();
//   DoDelete(sPath);
//  }
//  else DoDelete(ff.GetFilePath());
// }
// ff.Close();
// if (!RemoveDirectory(sPathName) && !m_bAborted) throw new CFExeption(GetLastError());
//}
//
//
//void CFileOperation::DoFolderCopy(CString sSourceFolder, CString sDestFolder, bool bDelteAfterCopy)
//{
// CFileFind ff;
// CString sPathSource = sSourceFolder;
// BOOL bRes = ff.FindFile(sPathSource);
// while (bRes)
// {
//  bRes = ff.FindNextFile();
//  if (ff.IsDots()) continue;
//  if (ff.IsDirectory()) // source is a folder
//  {
//   if (m_iRecursionLimit == 0) continue;
//   sPathSource = ff.GetFilePath() + CString("\\") + CString("*.*");
//   CString sPathDest = sDestFolder + ff.GetFileName() + CString("\\");
//   if (CheckPath(sPathDest) == PATH_NOT_FOUND) 
//   {
//    if (!CreateDirectory(sPathDest, NULL))
//    {
//     ff.Close();
//     throw new CFExeption(GetLastError());
//    }
//   }
//   if (m_iRecursionLimit > 0) m_iRecursionLimit --;
//   DoFolderCopy(sPathSource, sPathDest, bDelteAfterCopy);
//  }
//  else // source is a file
//  {
//   CString sNewFileName = sDestFolder + ff.GetFileName();
//   DoFileCopy(ff.GetFilePath(), sNewFileName, bDelteAfterCopy);
//  }
// }
// ff.Close();
//}
//
//
//bool CFileOperation::Delete(CString sPathName)
//{
// try
// {
//  DoDelete(sPathName);
// }
// catch(CFExeption* e)
// {
//  m_sError = e->GetErrorText();
//  m_dwError = e->GetErrorCode();
//  delete e;
//  if (m_dwError == 0) return true;
//  return false;
// }
// return true;
//}
//
//
//bool CFileOperation::Rename(CString sSource, CString sDest)
//{
// try
// {
//  DoRename(sSource, sDest);
// }
// catch(CFExeption* e)
// {
//  m_sError = e->GetErrorText();
//  m_dwError = e->GetErrorCode();
//  delete e;
//  return false;
// }
// return true;
//}
//
//
//void CFileOperation::DoRename(CString sSource, CString sDest)
//{
// if (!MoveFile(sSource, sDest)) throw new CFExeption(GetLastError());
//}
//
//
//void CFileOperation::DoCopy(CString sSource, CString sDest, bool bDelteAfterCopy)
//{
// CheckSelfRecursion(sSource, sDest);
// // source not found
// if (CheckPath(sSource) == PATH_NOT_FOUND)
// {
//  CString sError = sSource + CString(L" not found");
//  throw new CFExeption(sError);
// }
// // dest not found
// if (CheckPath(sDest) == PATH_NOT_FOUND)
// {
//  CString sError = sDest + CString(L" not found");
//  throw new CFExeption(sError);
// }
// // folder to file
// if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FILE) 
// {
//  throw new CFExeption(L"Wrong operation");
// }
// // folder to folder
// if (CheckPath(sSource) == PATH_IS_FOLDER && CheckPath(sDest) == PATH_IS_FOLDER) 
// {
//  CFileFind ff;
//  CString sError = sSource + CString(L" not found");
//  PreparePath(sSource);
//  PreparePath(sDest);
//  sSource += "*.*";
//  if (!ff.FindFile(sSource)) 
//  {
//   ff.Close();
//   throw new CFExeption(sError);
//  }
//  if (!ff.FindNextFile()) 
//  {
//   ff.Close();
//   throw new CFExeption(sError);
//  }
//  CString sFolderName = ParseFolderName(sSource);
//  if (!sFolderName.IsEmpty()) // the source is not drive
//  {
//   sDest += sFolderName;
//   PreparePath(sDest);
//   if (!CreateDirectory(sDest, NULL))
//   {
//    DWORD dwErr = GetLastError();
//    if (dwErr != 183)
//    {
//     ff.Close();
//     throw new CFExeption(dwErr);
//    }
//   }
//  }
//  ff.Close();
//  DoFolderCopy(sSource, sDest, bDelteAfterCopy);
// }
// // file to file
// if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FILE) 
// {
//  DoFileCopy(sSource, sDest);
// }
//
// CTypeCastUtil typecast;
// // file to folder
// if (CheckPath(sSource) == PATH_IS_FILE && CheckPath(sDest) == PATH_IS_FOLDER) 
// {
//  PreparePath(sDest);
//  char drive[MAX_PATH], dir[MAX_PATH], name[MAX_PATH], ext[MAX_PATH];
//  _splitpath_s(typecast.CStringToChar(sSource), drive, dir, name, ext);
//  sDest = sDest + CString(name) + CString(ext);
//  DoFileCopy(sSource, sDest);
// }
//}
//
//
//void CFileOperation::DoFileCopy(CString sSourceFile, CString sDestFile, bool bDelteAfterCopy)
//{
// BOOL bOvrwriteFails = FALSE;
// if (!m_bOverwriteMode)
// {
//  while (IsFileExist(sDestFile)) 
//  {
//   sDestFile = ChangeFileName(sDestFile);
//  }
//  bOvrwriteFails = TRUE;
// }
// if (!CopyFile(sSourceFile, sDestFile, bOvrwriteFails)) throw new CFExeption(GetLastError());
// if (bDelteAfterCopy)
// {
//  DoDelete(sSourceFile);
// }
//}
//
//
//bool CFileOperation::Copy(CString sSource, CString sDest)
//{
// if (CheckSelfCopy(sSource, sDest)) return true;
// bool bRes;
// try
// {
//  DoCopy(sSource, sDest);
//  bRes = true;
// }
// catch(CFExeption* e)
// {
//  m_sError = e->GetErrorText();
//  m_dwError = e->GetErrorCode();
//  delete e;
//  if (m_dwError == 0) bRes = true;
//  bRes = false;
// }
// m_iRecursionLimit = -1;
// return bRes;
//}
//
//
//bool CFileOperation::Replace(CString sSource, CString sDest)
//{
// if (CheckSelfCopy(sSource, sDest)) return true;
// bool bRes;
// try
// {
//  bool b = m_bAskIfReadOnly;
//  m_bAskIfReadOnly = false;
//  DoCopy(sSource, sDest, true);
//  DoDelete(sSource);
//  m_bAskIfReadOnly = b;
//  bRes = true;
// }
// catch(CFExeption* e)
// {
//  m_sError = e->GetErrorText();
//  m_dwError = e->GetErrorCode();
//  delete e;
//  if (m_dwError == 0) bRes = true;
//  bRes = false;
// }
// m_iRecursionLimit = -1;
// return bRes;
//}
//
//
//CString CFileOperation::ChangeFileName(CString sFileName)
//{
// CString sName, sNewName, sResult;
// char drive[MAX_PATH];
// char dir  [MAX_PATH];
// char name [MAX_PATH];
// char ext  [MAX_PATH];
// 
// CTypeCastUtil typecast;
//
// _splitpath_s(typecast.CStringToChar(sFileName), drive, dir, name, ext);
// sName = name;
//
// int pos = sName.Find(L"Copy ");
// if (pos == -1)
// {
//  sNewName = CString(L"Copy of ") + sName + CString(ext);
// }
// else
// {
//  int pos1 = sName.Find('(');
//  if (pos1 == -1)
//  {
//   sNewName = sName;
//   sNewName.Delete(0, 8);
//   sNewName = CString("Copy (1) of ") + sNewName + CString(ext);
//  }
//  else
//  {
//   CString sCount;
//   int pos2 = sName.Find(')');
//   if (pos2 == -1)
//   {
//    sNewName = CString("Copy of ") + sNewName + CString(ext);
//   }
//   else
//   {
//    sCount = sName.Mid(pos1 + 1, pos2 - pos1 - 1);
//    sName.Delete(0, pos2 + 5);
//    int iCount = atoi(typecast.CStringToChar(sCount));
//    iCount ++;
//    sNewName.Format(L"%s%d%s%s%s", "Copy (", iCount, ") of ", (LPCTSTR)sName, ext);
//   }
//  }
// }
//
// sResult = CString(drive) + CString(dir) + sNewName;
//
// return sResult;
//}
//
//
//bool CFileOperation::IsFileExist(CString sPathName)
//{
// HANDLE hFile;
// hFile = CreateFile(sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
// if (hFile == INVALID_HANDLE_VALUE) return false;
// CloseHandle(hFile);
// return true;
//}
//
//
//int CFileOperation::CheckPath(CString sPath)
//{
// DWORD dwAttr = GetFileAttributes(sPath);
// if (dwAttr == 0xffffffff) 
// {
//  if (GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND) 
//   return PATH_NOT_FOUND;
//  return PATH_ERROR;
// }
// if (dwAttr & FILE_ATTRIBUTE_DIRECTORY) return PATH_IS_FOLDER;
// return PATH_IS_FILE;
//}
//
//
//void CFileOperation::PreparePath(CString &sPath)
//{
// if(sPath.Right(1) != "\\") sPath += "\\";
//}
//
//
//bool CFileOperation::CanDelete(CString sPathName)
//{
// DWORD dwAttr = GetFileAttributes(sPathName);
// if (dwAttr == -1) return false;
// if (dwAttr & FILE_ATTRIBUTE_READONLY)
// {
//  if (m_bAskIfReadOnly)
//  {
//   CString sTmp = sPathName;
//   int pos = sTmp.ReverseFind('\\');
//   if (pos != -1) sTmp.Delete(0, pos + 1);
//   CString sText = sTmp + CString(" is read olny. Do you want delete it?");
//   int iRes = MessageBox(NULL, sText, _T("Warning"), MB_YESNOCANCEL | MB_ICONQUESTION);
//   switch (iRes)
//   {
//    case IDYES:
//    {
//     if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
//     return true;
//    }
//    case IDNO:
//    {
//     return false;
//    }
//    case IDCANCEL:
//    {
//     m_bAborted = true;
//     throw new CFExeption(0);
//     return false;
//    }
//   }
//  }
//  else
//  {
//   if (!SetFileAttributes(sPathName, FILE_ATTRIBUTE_NORMAL)) return false;
//   return true;
//  }
// }
// return true;
//}
//
//
//CString CFileOperation::ParseFolderName(CString sPathName)
//{
// CString sFolderName = sPathName;
// int pos = sFolderName.ReverseFind('\\');
// if (pos != -1) sFolderName.Delete(pos, sFolderName.GetLength() - pos);
// pos = sFolderName.ReverseFind('\\');
// if (pos != -1) sFolderName = sFolderName.Right(sFolderName.GetLength() - pos - 1);
// else sFolderName.Empty();
// return sFolderName;
//}
//
//
//void CFileOperation::CheckSelfRecursion(CString sSource, CString sDest)
//{
// if (sDest.Find(sSource) != -1)
// {
//  int i = 0, count1 = 0, count2 = 0;
//  for(i = 0; i < sSource.GetLength(); i ++) if (sSource[i] == '\\') count1 ++;
//  for(i = 0; i < sDest.GetLength(); i ++) if (sDest[i] == '\\') count2 ++;
//  if (count2 >= count1) m_iRecursionLimit = count2 - count1;
// }
//}
//
//
//bool CFileOperation::CheckSelfCopy(CString sSource, CString sDest)
//{
// bool bRes = false;
// if (CheckPath(sSource) == PATH_IS_FOLDER)
// {
//  CString sTmp = sSource;
//  int pos = sTmp.ReverseFind('\\');
//  if (pos != -1)
//  {
//   sTmp.Delete(pos, sTmp.GetLength() - pos);
//   if (sTmp.CompareNoCase(sDest) == 0) bRes = true;
//  }
// }
// return bRes;
//}



void DlgModelSetupSeq::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();


	SaveModel(gTestSeqData.strModelName);
	CDialogEx::OnOK();
}


long DlgModelSetupSeq::OnReceiveDataPCB(WPARAM wParam, LPARAM lParam )
{

	BYTE lbuf[4096];
	int lcnt;
	lcnt = (int)wParam;

	if((m_RecvCntPCB < 0)||(m_RecvCntPCB > 4095))
		m_RecvCntPCB = 0;

	memcpy(lbuf,(void *)lParam,lcnt);

	for(int i = 0; i < lcnt; i++)
	{
		m_RecvBufPCB[m_RecvCntPCB++] = lbuf[i];
		if(m_RecvCntPCB > 4095)
			m_RecvCntPCB = 0;
	}
		
	

	if(m_RecvCntPCB > 2)
	{
		if(m_RecvBufPCB[0] == 0xBB)
		{
			if(m_RecvCntPCB >= m_RecvBufPCB[1]+2)
			{
			//	memset(lbuf,0,sizeof(lbuf));
				unsigned char lCheckSum = 0;
				for(int i = 0; i < m_RecvBufPCB[1]+1; i++)
				{
					lCheckSum ^= m_RecvBufPCB[i];
				}

				if(m_RecvBufPCB[m_RecvBufPCB[1]+1] == lCheckSum)
				{
					m_PCBComAck = COM_ACK_OK;
					/*for(int i = 0; i < m_UartOkAckDataCnt; i++)
					{
						if(m_RecvBufPCB[4+i] == m_UartOkAckData[i])
						{
							m_PCB_CheckOK = 1;
						}
						else
						{
							m_PCB_CheckOK = 0;
							break;
						}
					}*/

					//m_PCBComAck = 1;
				}
				else
				{
					m_PCBComAck = COM_ACK_BUSY;
				}


				CString strtmp;
				CString strReceive ;

		
				if(m_RecvCntPCB == 9)
				{
					strtmp.Format(_T("0x%02X 0x%02X 0x%02X 0x%02X"), m_RecvBufPCB[4],m_RecvBufPCB[5], m_RecvBufPCB[6],m_RecvBufPCB[7]);
					CString str;
					BYTE lbuf[5];
					lbuf[4] = 0;
					memcpy(lbuf, &(m_RecvBufPCB[4]), 4);
					str = lbuf;
					SetDlgItemText(IDC_DISPLAY_CHECKSUM, str);
				}
				else
				{
					strtmp.Format(_T("0x%02X 0x%02X"), m_RecvBufPCB[4],m_RecvBufPCB[5]);
				}
				strReceive += strtmp;

				m_EditCheckSum = strReceive;
				UpdateData(FALSE);
//#ifdef __MESSAGE_DEBUG_MODE__
//				MessageDisplay(2, strReceive);//SetDlgItemText(IDC_EDIT_READ_DATA,strReceive.GetBuffer());
//#endif
			//	m_PCBComAck = COM_ACK_OK;
				m_RecvCntPCB = 0;
							
			}
		}
		else
		{
			m_RecvCntPCB = 0;
		}
	}



	return 0;
}

void DlgModelSetupSeq::OpenComportPCB()//long CAcqVoltageSamples_IntClkDlg::OnReceiveData(WPARAM wParam, LPARAM lParam )
{

	CString str;
	char lParityChar[3] = {'N', 'E', 'O'};

	if(gTestSeqData.nParity_Pcb > 2)
	{
		gTestSeqData.nParity_Pcb = 0;
	}

	if(m_ComPortPCB.mPort_Opened)
	{
		m_ComPortPCB.ClosePort();
	}
	if(m_ComPortPCB.InitPort(this, gTestSeqData.nPort_Pcb, gTestSeqData.nBaud_Pcb, lParityChar[gTestSeqData.nParity_Pcb], 8, 1, EV_RXCHAR, 4096 ))
	{		
		m_ComPortPCB.StartMonitoring();
	}
	else
	{
		str.Format(_T("MCS/MTK COM Port %d Open FAIL !!"),  gTestSeqData.nPort_Pcb);
		MessageBox(str);
		//MessageDisplay(1, str);
		/*StatusDisplayMsg(str, 1 );*/
		//MessageBox(str);
	}

	m_ComPortPCB.m_RxMessageID = WM_COMM_RXCHAR_PCB;
}


void DlgModelSetupSeq::DblClickLabelChecksum(LPDISPATCH Cancel)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//OpenComportPCB();

	BYTE lbuf[128]; 
	int lcnt;

//	int lType = m_ComboPcbType.GetCurSel();
	CString Str;
	GetDlgItemText(IDC_EDIT_PCB_COMMAND,Str);

	char lchar = 0;
	Str.MakeUpper();

	lbuf[0] = 0xAA;
	lbuf[1] = 0x03;
	lbuf[2] = 0x01;//lType + 1;


	//lchar = Str.GetAt(0);
	//if(lchar > 0x39)
	//{
	//	lchar = lchar - 'A' + 0x0A;
	//}
	//else
	//{
	//	lchar = lchar - 0x30;
	//}
	lbuf[3] = 0x2D;//lchar * 0x10;

	//lchar = Str.GetAt(1);
	//if(lchar > 0x39)
	//{
	//	lchar = lchar - 'A' + 0x0A;
	//}
	//else
	//{
	//	lchar = lchar - 0x30;
	//}
	//lbuf[3] = lbuf[3] + lchar ;



	unsigned char lCheckSum = 0;
	for(int i = 0; i < 4; i++)
	{
		lCheckSum ^= lbuf[i];
	}
	lbuf[4] = lCheckSum;

	memcpy(m_SendBufPCB, lbuf, 5); 	
	m_SendCntPCB = 5;

	//ComPCBSend();

	m_PCB_COM_PROCESS = COM_MODE_WAIT_ACK;
	m_PCBComAck =COM_ACK_WAIT;
	m_PCBWaitCnt = 0;
	m_PCBResendCnt = 0;

	//if(m_SendBufPCB[3] == 0xc1)
	//	m_WaitPCB_Ack_Limit = 500;
	//else
	//	m_WaitPCB_Ack_Limit = 100;


	//MessageDisplay(2, "Command Send!");

	if(m_ComPortPCB.mPort_Opened)
	{
		
		m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
	}
	else
	{
		OpenComportPCB();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPortPCB.mPort_Opened)
		{
			
			m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
		}
	}

}


void DlgModelSetupSeq::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
}


void DlgModelSetupSeq::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_ComPortPCB.mPort_Opened == TRUE)
		m_ComPortPCB.ClosePort();
	CDialogEx::OnClose();
}


void DlgModelSetupSeq::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(1);
	switch(m_PCB_COM_PROCESS)
	{
	case COM_MODE_IDLE:
		break;
	case COM_MODE_WAIT_ACK:

		if(m_PCBComAck == COM_ACK_OK)
		{
			m_PCBComAck = COM_ACK_WAIT;
			m_PCB_COM_PROCESS = COM_MODE_IDLE;
			MessageBox("COM OK !! ");
			//MessageDisplay(0, "COM OK !! ");
		}
		else if(m_PCBComAck == COM_ACK_BUSY)
		{
			MessageBox("COM Fail !! ");
			//MessageDisplay(1, "COM FAIL !! ");
			m_PCB_COM_PROCESS = COM_MODE_IDLE;
		}
		else
		{
			/*
			int m_WaitCnt;
			int m_ResendCnt;
			*/
			m_PCBWaitCnt++;

			if(m_PCBWaitCnt > 150)
			{
			
				m_PCBResendCnt++;
				if(m_PCBResendCnt < 3)
				{
					ComPCBSend();
				}
				else
				{
					MessageBox("COM Time Out !! ");
					//MessageDisplay(1, "COM Time Out !!");
					m_PCB_COM_PROCESS = COM_MODE_IDLE;
				}
			}
		}
		break;
	default:
		break;

	}
	SetTimer(1, 30, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void DlgModelSetupSeq::ComPCBSend()
{
	//SendData(m_SendBuf, m_SendCnt);
	//	void ComSend(BYTE lbuf, int lcnt);
	if(m_ComPortPCB.mPort_Opened)
	{
		
		m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
	}
	else
	{
		OpenComportPCB();
		//MessageBox(_T("Com Port Not Opened !!"));
		if(m_ComPortPCB.mPort_Opened)
		{
			
			m_ComPortPCB.WriteToPort(m_SendBufPCB, m_SendCntPCB);
		}
	}
}



void DlgModelSetupSeq::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();

	gTestSeqData = m_TestOrgSeqData;
}


void DlgModelSetupSeq::OnCbnSelchangeComboMesPortType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int lsel = m_cComboPortType.GetCurSel( );
	
	if(lsel == LINE_CM89)
	{
		m_ServerPortNumber.Format(_T("%d"), g_nRemotePortNumberCM89);
	}
	else
	{
		m_ServerPortNumber.Format(_T("%d"), g_nRemotePortNumberCM45);
	}
	UpdateData(FALSE);
}


void DlgModelSetupSeq::OnBnClickedButtonSaveas()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString lstrPath;
	lstrPath = PATH_BASE_DIR;
	lstrPath += _T("\\Model\\");

	CString InitNewName;
	InitNewName = gTestSeqData.strModelName;
	InitNewName += ".mdl";

	CFileDialog FileDlg(FALSE, _T("mdl"), InitNewName, OFN_OVERWRITEPROMPT, _T("mdl 파일(*.mdl)|*.mdl||")); 
	FileDlg.m_ofn.lpstrInitialDir = lstrPath;

	CString FilenameOrg = PATH_BASE_DIR;
	FilenameOrg += _T("\\Model\\");
	FilenameOrg += gTestSeqData.strModelName;

		
	CString FilenameOrgSeq;
	FilenameOrgSeq = FilenameOrg;
	FilenameOrg += _T(".mdl");
	FilenameOrgSeq += _T(".seq");
	
	if (FileDlg.DoModal() == IDOK) {   
		// 파일경로 가져오기    
		CString Filename = FileDlg.GetPathName();
		CString lModelName =  FileDlg.GetFileName();
		int lpos = lModelName.Find(".mdl");
		lModelName = lModelName.Left(lpos);
		lModelName.MakeUpper();

		if(FilenameOrg.Compare(Filename) == 0)
		{
		}
		else
		{
			//if(!CopyFile(FilenameOrg, Filename, 0))
			//{
			//	if(IDNO == MessageBox("File Exist Update Old File?","Warning", MB_YESNO) )
			//	{
			//		if(!CopyFile(FilenameOrg, Filename, 1))
			//		{
			//			MessageBox("File Copy FAIL!!","Warning") ;
			//			return;
			//		}
			//	}
			//}
			//	
			//if(!CopyFile(FilenameOrg, Filename, 0))
			//{
			//	if(IDNO == MessageBox("File Exist Update Old File?","Warning", MB_YESNO) )
			//	{
			//		if(!CopyFile(FilenameOrg, Filename, 1))
			//		{
			//			MessageBox("File Copy FAIL!!","Warning") ;
			//			return;
			//		}
			//	}
			//}
			//else
			//{

				if(lModelName.GetLength() < 3)
				{
					MessageBox("New Name Is Too Short !!");
					return;
				}

				for(int i = 0 ; i < lModelName.GetLength(); i++)
				{
					if((lModelName.GetAt(i) == ' ')||(lModelName.GetAt(i) == '\t'))
					{
						lModelName.SetAt(i, '_');
					}
				}

				if(NameListCheckAndADD(lModelName))
				{
					int lok = MessageBoxA(_T("New Name Is IN MODEL LIST !!") , _T("Used Found"), MB_YESNO |MB_DEFBUTTON2  );
					if(IDYES != lok)
					{
						return;
					}
				}

			//	m_cModelComboSeq.SetCurSel(m_cModelComboSeq.GetCount()-1);
			//}

			if(!CopyFile(FilenameOrg, Filename, 0))
			{
				MessageBox("File Copy FAIL!!","Warning") ;
				return;
			}
			Filename = Filename.Left(Filename.Find(".mdl"));
			Filename +=  _T(".seq");
			if(!CopyFile(FilenameOrgSeq, Filename, 0))
			{
				MessageBox("File Copy FAIL!!","Warning") ;
				return;
			}
			gTestSeqData.strModelName = lModelName;
		//	gTestSeqData.strSeqFileName = lModelName;
			GetModelList();
			SaveModel(lModelName);

			LoadTestData();

			DisplayTestData();
		}
	} 
}


void DlgModelSetupSeq::OnCbnSelchangeComboModelPcbPort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	gTestSeqData.nPort_Pcb = nNumberPort[m_cComboPCBModelPort.GetCurSel()];
	gTestSeqData.nBaud_Pcb = mbaud_List[m_cComboModelPcbBaud.GetCurSel()];	
	gTestSeqData.nParity_Pcb = m_cComboModelPcbParity.GetCurSel();
	OpenComportPCB();
}


void DlgModelSetupSeq::OnCbnSelchangeComboModelPcbType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	gTestSeqData.nPort_Pcb = nNumberPort[m_cComboPCBModelPort.GetCurSel()];
	gTestSeqData.nBaud_Pcb = mbaud_List[m_cComboModelPcbBaud.GetCurSel()];	
	gTestSeqData.nParity_Pcb = m_cComboModelPcbParity.GetCurSel();
	OpenComportPCB();
}


void DlgModelSetupSeq::OnCbnSelchangeComboModelBaudrate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	gTestSeqData.nPort_Pcb = nNumberPort[m_cComboPCBModelPort.GetCurSel()];
	gTestSeqData.nBaud_Pcb = mbaud_List[m_cComboModelPcbBaud.GetCurSel()];	
	gTestSeqData.nParity_Pcb = m_cComboModelPcbParity.GetCurSel();
	OpenComportPCB();
}


void DlgModelSetupSeq::OnCbnSelchangeComboModelParity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	gTestSeqData.nPort_Pcb = nNumberPort[m_cComboPCBModelPort.GetCurSel()];
	gTestSeqData.nBaud_Pcb = mbaud_List[m_cComboModelPcbBaud.GetCurSel()];	
	gTestSeqData.nParity_Pcb = m_cComboModelPcbParity.GetCurSel();
	OpenComportPCB();
}
