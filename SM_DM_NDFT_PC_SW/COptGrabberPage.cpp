// COptGrabberPage.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptGrabberPage.h"
#include "Global.h"


extern CAcqVoltageSamples_IntClkDlg* g_pView;

#if 1
IMPLEMENT_DYNCREATE(COptGrabberPage, CPropertyPage)

COptGrabberPage::COptGrabberPage() : CPropertyPage(COptGrabberPage::IDD)
, m_nGrabCheckArea(0)
, m_nRemoteType(0)
{
	//{{AFX_DATA_INIT(COptGrabberPage)
	
	//}}AFX_DATA_INIT
}

COptGrabberPage::~COptGrabberPage()
{
}

void COptGrabberPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptGrabberPage)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_GRABBER_TYPE, m_cComboGrabberType);
	DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE, m_cComboAI_CardType);
	DDX_Radio(pDX, IDC_GRAB_CHECK_AREA1, m_nGrabCheckArea);
	DDX_Control(pDX, IDC_COMBO_RECOMON, m_cRemoconCombo);
	DDX_Radio(pDX, IDC_REDIO_SIG_CA, m_nRemoteType);
}


BEGIN_MESSAGE_MAP(COptGrabberPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptGrabberPage)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COptGrabberPage::OnBnClickedButtonSave)
END_MESSAGE_MAP()
#else

// COptGrabberPage

IMPLEMENT_DYNAMIC(COptGrabberPage, CMFCPropertyPage)

COptGrabberPage::COptGrabberPage()
{

}

COptGrabberPage::~COptGrabberPage()
{
}


BEGIN_MESSAGE_MAP(COptGrabberPage, CMFCPropertyPage)
	ON_BN_CLICKED(IDOK, &COptGrabberPage::OnBnClickedOk)
END_MESSAGE_MAP()



// COptGrabberPage 메시지 처리기


#endif

void COptGrabberPage:: OnOK()
{
	int  i = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CPropertyPage::OnOK();
}


BOOL COptGrabberPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

		 GetRemoconList();
	 m_cComboGrabberType.SetCurSel(g_nVIDEO_CardSel);
	 m_cComboAI_CardType.SetCurSel(g_nNI_CardSel);
	 
	 m_nGrabCheckArea = CurrentSet->nGrabCheckArea ;
	 m_nRemoteType = CurrentSet->nRemoteType;
	 m_cRemoconCombo.SetCurSel(CurrentSet->nRemoteCustomCode);


	 UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



void COptGrabberPage::GetRemoconList()
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
		fileNameList[nFileCnt] =  fileName;
		//	titleNameList[nFileCnt] = finder.GetFileTitle();

		nFileCnt++;
		if (nFileCnt >= 100)
		{

			break;
		}
		bFileFound = 1;

	}

	finder.Close();


	if (bFileFound)
	{
		/*
		CString m_strRemoconList[100];
		int m_nRecomonCount = 0;
		*/
		g_nRemoconSelNum = 0;//g_strRemoconFileName
		m_nRecomonCount = nFileCnt;
		for (int i = 0; i < nFileCnt; i++)
		{
			m_strRemoconList[i] = fileNameList[i];
			m_cRemoconCombo.AddString(m_strRemoconList[i]);
			str = g_pView->m_szExePath;
			str += "\\Remote\\";
			str += m_strRemoconList[i];
			//CurrentSet->sRemoconTitle = lstrModelName;
			if (str.Compare(CurrentSet->sRemoconTitle) == 0)
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


void COptGrabberPage::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strName, sMsg;
	UpdateData();
	CurrentSet->nGrabCheckArea = m_nGrabCheckArea;

	CurrentSet->nRemoteType = m_nRemoteType  ;
	CurrentSet->nRemoteCustomCode = m_cRemoconCombo.GetCurSel();

	m_cRemoconCombo.GetLBText(CurrentSet->nRemoteCustomCode, strName);
	CurrentSet->sRemoconTitle = g_pView->m_szExePath;
	CurrentSet->sRemoconTitle += "\\Remote\\";
	CurrentSet->sRemoconTitle += strName;
	
	//+move kwmoon 080904
	if (FileExists(CurrentSet->sModelIni))
	{
		SaveModelIniFile(CurrentSet->sModelIni);
	}
	else
	{
		CreateModelIniFile(CurrentSet->sModelIni);
		sMsg.Format("File is created.\n[%s]", CurrentSet->sModelIni);
		AfxMessageBox(sMsg);
	}
	g_pView->SaveRegistrySetting();

}
