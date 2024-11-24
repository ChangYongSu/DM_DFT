// COptFolderPage.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptFolderPage.h"
#include "Global.h"

// COptFolderPage
IMPLEMENT_DYNCREATE(COptFolderPage, CPropertyPage)

//COptFolderPage::COptFolderPage() : CPropertyPage(COptFolderPage::IDD)
//{
//	//{{AFX_DATA_INIT(COptGrabberPage)
//
//	//}}AFX_DATA_INIT
//}
//
//COptFolderPage::~COptFolderPage()
//{
//}
//
//void COptFolderPage::DoDataExchange(CDataExchange* pDX)
//{
//	CPropertyPage::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(COptFolderPage)
//
//	//}}AFX_DATA_MAP
//}
COptFolderPage::COptFolderPage() : CPropertyPage(COptFolderPage::IDD)
{
	//{{AFX_DATA_INIT(COptFolderPage)
	m_szPatternFilePath = _T("");
	m_szRemoteFilePath = _T("");
	m_szTemplateSeqPath = _T("");
	m_szTestParamPath = _T("");
	m_szModelListPath = _T("");
	m_strServerFolder = _T("");
	m_strRefImageFolder = _T("");
	m_strModelInfoFolder = _T("");
	//}}AFX_DATA_INIT
}

COptFolderPage::~COptFolderPage()
{
}

void COptFolderPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptFolderPage)
	DDX_Text(pDX, IDC_EDIT_PATTERN_PATH, m_szPatternFilePath);
	DDX_Text(pDX, IDC_EDIT_REMOTE_PATH, m_szRemoteFilePath);
	DDX_Text(pDX, IDC_EDIT_TEMPLETE_SEQ, m_szTemplateSeqPath);//IDC_EDIT_TEMPLETE_SEQ
	DDX_Text(pDX, IDC_EDIT_TEST_PARAM_PATH, m_szTestParamPath);
	DDX_Text(pDX, IDC_EDIT_MODEL_LIST, m_szModelListPath);
	DDX_Text(pDX, IDC_EDIT_SERVER_FOLDER, m_strServerFolder);
	DDX_Text(pDX, IDC_EDIT_REFIMAGE_FOLDER, m_strRefImageFolder);
	DDX_Text(pDX, IDC_EDIT_MODELINFO_FOLDER, m_strModelInfoFolder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptFolderPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptFolderPage)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PATTERN, OnBtnOpenPattern)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_REMOTE, OnBtnOpenRemote)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_TEST_PARAM, OnBtnOpenTestParam)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_TEMPLETE_SEQ, OnBtnOpenTemplateSeq)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MODEL_LIST, OnBtnOpenModelList)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_SERVER_FOLDER, OnBtnOpenServerFolder)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_REF_FOLDER, OnBtnOpenRefFolder)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MODEL_INFO_FOLDER, OnBtnOpenModelinfoFolder)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &COptFolderPage::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COptFolderPage::OnBnClickedButtonSave)
END_MESSAGE_MAP()
//
//IMPLEMENT_DYNAMIC(COptFolderPage, CMFCPropertyPage)
//
//COptFolderPage::COptFolderPage()
//{
//
//}
//
//COptFolderPage::~COptFolderPage()
//{
//}
//
//
//BEGIN_MESSAGE_MAP(COptFolderPage, CMFCPropertyPage)
//END_MESSAGE_MAP()
//


// COptFolderPage 메시지 처리기




void COptFolderPage::OnBnClickedOk()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void COptFolderPage::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptFolderPage::OnBtnOpenPattern()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "pat", NULL,
		OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"PAT File(*.pat)|*.pat|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_szPatternFilePath = dlg.GetPathName();
		CurrentSet->sPatternTitle = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenRemote()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "rmt", NULL,
		OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"RMT File(*.rmt)|*.rmt|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_szRemoteFilePath = dlg.GetPathName();
		CurrentSet->sRemoconTitle = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenTestParam()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "ini", NULL,
		OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"INI File(*.ini)|*.ini|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_szTemplateSeqPath = dlg.GetPathName();
		CurrentSet->sTestParamIni = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenTemplateSeq()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "seq", NULL,
		OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"SEQ File(*.seq)|*.seq|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_szTemplateSeqPath = dlg.GetPathName();
		CurrentSet->sFullSeqPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

BOOL COptFolderPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_szPatternFilePath = CurrentSet->sPatternTitle;
	m_szRemoteFilePath = CurrentSet->sRemoconTitle;
	m_szTemplateSeqPath = CurrentSet->sFullSeqPath;
	m_szTestParamPath = CurrentSet->sTestParamIni;
	m_szModelListPath = CurrentSet->sModelListPath;

	m_strServerFolder = CurrentSet->sServerFolder;
	m_strRefImageFolder = CurrentSet->sRefRootFolder;
	m_strModelInfoFolder = CurrentSet->sModelInfoFolder;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void COptFolderPage::OnBtnOpenModelList()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "ini", NULL,
		OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY,
		"INI File(*.ini)|*.ini|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_szModelListPath = dlg.GetPathName();
		CurrentSet->sModelListPath = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenServerFolder()
{
	CString strFolderPath;

	if (GetFolder(&strFolderPath, "Select Sequence Server Foler.", this->m_hWnd, NULL, (const char*)m_strServerFolder))
	{
		if (!strFolderPath.IsEmpty())
		{
			m_strServerFolder = strFolderPath;
			CurrentSet->sServerFolder = strFolderPath;

		}
		else
		{
			MessageBox(_T("Invalid Folder Name."), _T("lol"), MB_OKCANCEL | MB_ICONASTERISK);
		}
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenRefFolder()
{
	CString strFolderPath;

	if (GetFolder(&strFolderPath, "Reference Image Root Foler.", this->m_hWnd, NULL, (const char*)m_strRefImageFolder))
	{
		if (!strFolderPath.IsEmpty())
		{
			m_strRefImageFolder = strFolderPath;
			CurrentSet->sRefRootFolder = strFolderPath;

		}
		else
		{
			MessageBox(_T("Invalid Folder Name."), _T("lol"), MB_OKCANCEL | MB_ICONASTERISK);
		}
		UpdateData(FALSE);
	}
}

void COptFolderPage::OnBtnOpenModelinfoFolder()
{
	CString strFolderPath;

	if (GetFolder(&strFolderPath, "Model Info  Root Foler.", this->m_hWnd, NULL, (const char*)m_strModelInfoFolder))
	{
		if (!strFolderPath.IsEmpty())
		{
			m_strModelInfoFolder = strFolderPath;
			CurrentSet->sModelInfoFolder = strFolderPath;

		}
		else
		{
			MessageBox(_T("Invalid Folder Name."), _T("lol"), MB_OKCANCEL | MB_ICONASTERISK);
		}
		UpdateData(FALSE);
	}
}
